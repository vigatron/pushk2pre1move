#include "vhplatform.hpp"
#include "yinput.hpp"
#include "membuff.hpp"
#include "cntblkmv.hpp"
#include "allerrs.hpp"

// Values : 0 - 2
#ifndef DBG_VERBOSE
#define DBG_VERBOSE 0
#endif


// ----------------------------------------------------------------------------------
int error(int errCode, std::string msg, std::string arg="") {
    std::cerr << "Error " << errCode << ", " << msg;
    if(!arg.empty()) { std::cerr << " " << arg; }
    std::cerr << '\n';
    return errCode;
}

// ----------------------------------------------------------------------------------
bool fileExists(const std::string& path) {
    try {
        return std::filesystem::exists(path) &&
            std::filesystem::is_regular_file(path);
    } catch (const std::filesystem::filesystem_error& e) {
        std::cerr << "Ошибка доступа: " << e.what() << '\n';
        return false; } }

// ----------------------------------------------------------------------------------
std::vector<uint8_t> base64_to_vector(const std::string& input) {
    static const std::string base64_chars =
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz"
        "0123456789+/";

    auto is_base64 = [](unsigned char c) {
        return std::isalnum(c) || (c == '+') || (c == '/');
    };

    std::vector<uint8_t> output;
    int val = 0;
    int bits = -8;

    for (unsigned char c : input) {
        if (std::isspace(c)) continue; // пропускаем пробелы/переносы строк
        if (c == '=') break;           // padding
        if (!is_base64(c)) {
            output.clear();
            return output;
        }

        val = (val << 6) + base64_chars.find(c);
        bits += 6;

        if (bits >= 0) {
            output.push_back(static_cast<uint8_t>((val >> bits) & 0xFF));
            bits -= 8;
        }
    }

    return output;
}

// ----------------------------------------------------------------------------------
uint32_t glbAddr(const std::vector<Config::Channel>& chn, uint32_t cnt) {
    uint32_t r = 0;
    std::vector<int> offsets(chn.size());

    // вычисляем смещения битов
    int bts = 0;
    for (int i = chn.size() - 1; i >= 0; --i) {
        offsets[i] = bts;
        bts += chn[i].format; }

    // суммируем значение с учетом масштаба
    for (size_t i = 0; i < chn.size(); ++i) {
        r += ((cnt >> offsets[i]) & ((1 << chn[i].format) - 1)) * chn[i].scaler; }

    return r; }

// ----------------------------------------------------------------------------------
bool Transform( BinaryBuffer & scrbuff , int start_offset , Config & cfg , BinaryBuffer &	dstbuff ) {

    uint32_t vini = cfg.counter.init;
    uint32_t vlim = vini + cfg.counter.volume;
    uint16_t blksz = cfg.counter.unitsz;

    for( int cnt = vini; cnt < vlim ; cnt += cfg.counter.step ) {

        uint32_t addrf = start_offset + glbAddr(cfg.transform.src , cnt);
        uint32_t addrt = start_offset + glbAddr(cfg.transform.dst , cnt);

        // Bounds check
        if( (addrf > ( scrbuff.size() - blksz )) || (addrt > ( dstbuff.size() - blksz )) )
            return appErr_TransformationFailed;

        uint8_t * psrc = scrbuff.raw() + addrf;
        uint8_t * pdst = dstbuff.raw() + addrt;

        #if DBG_VERBOSE >= 2
        std::cout << "Operation #"  << std::setw(6) << std::setfill(' ') << std::dec << cnt;
        std::cout << "   x"         << std::hex << std::setw(6) << std::setfill('0') << addrf;
        std::cout << " > x"         << std::hex << std::setw(6) << std::setfill('0') << addrt;
        std::cout << "    SZ( "     << std::dec << blksz << " )\n";
        #endif

        memcpy( pdst , psrc, blksz ); }

    return true; }

// ----------------------------------------------------------------------------------
int runproc( std::string infile, int start_offset , Config & cfg, std::string outfile ) {

    BinaryBuffer	scrbuff;
    BinaryBuffer	dstbuff;

    // Load Original Source
    if (!scrbuff.loadFromFile( infile )) {
        return error(appErr_ReadSourceFileIO, "invalid source file : ", infile);
    }

    #if DBG_VERBOSE >= 2
    std::cout << "source file size : " << scrbuff.size()  << "\n";
    #endif

    // Clone
    dstbuff = scrbuff.clone();

    // Transform
    if( ! Transform( scrbuff , start_offset , cfg , dstbuff )) {
        return error(appErr_TransformationFailed, "Выход за границы" ); }

    // Save results
    if (!dstbuff.saveToFile( outfile )) {
        return error(appErr_InvalidDestination, "Ошибка записи результата: ", outfile);
    }

    return appErr_AllOk; }

// ----------------------------------------------------------------------------------
int main ( int argc, char * argv[] ) {

    if(argc != 5 ) { return appErr_NotEnoughArgs; }

    // Разбор входных параметров
    std::string     infile	    = argv[1];
    int             inoffs      = std::stoi( argv[2] );
    std::string     cfgparam    = argv[3];
    std::string     outfile     = argv[4];

    // Check Source file
    if( ! fileExists ( infile ) ) {
        return error(appErr_SourceFileMissed, "Отсутствует входной файл: ", infile );
    }

    // Check configuration type : .yaml / base64
    Config cfg;

    if (cfgparam.ends_with(".yaml") || cfgparam.ends_with(".yml")) {
        std::cout << "YAML file detected\n";

        if(!fileExists(cfgparam)) {
            return error(appErr_ConfigFileMissed, "Отсутствует конфигурационный файл: ", cfgparam);
        }

        // Load transformation parameters
        if (!cfg.load( cfgparam.c_str())) {
            return error(appErr_YAMLParserError, "Ошибка параметров конфигурационного файла: ", cfgparam);
        }

    } else {
        auto decoded = base64_to_vector(cfgparam);
        std::cout << decoded.data() << std::endl;
        return error(appErr_Unsupported, "BASE64 in develop");
    }

    #if DBG_VERBOSE > 0
    std::cout << "Input  : "        << infile	<< "\n";
    std::cout << "Offset : "        << inoffs	<< "\n";
    std::cout << "Config : "        << cfgparam	<< "\n";
    std::cout << "Output : "        << outfile	<< "\n";
    std::cout << "SRC channels: "   << cfg.transform.src.size() << "\n";
    std::cout << "DST channels: "   << cfg.transform.dst.size() << "\n";
    #endif

    int r = runproc( infile , inoffs , cfg , outfile );

    #if DBG_VERBOSE > 0
    if( r > 0 ) {
        std::cout << "Error code : "	<< r << "\n";
    }
    else {
        std::cout << "Transformation completed" << "\n";
    }
    #endif

    return r; }
