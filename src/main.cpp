
#include "allerrs.hpp"
#include "base64.hpp"
#include "cntblkmv.hpp"
#include "membuff.hpp"
#include "misc.hpp"
#include "vhplatform.hpp"
#include "yinput.hpp"

#include <iomanip>
#include <iostream>

// ----------------------------------------------------------------------------------
uint32_t
glbaddr(const std::vector<Config::Channel>& chn, uint32_t cnt)
{
    uint32_t r = 0;
    std::vector<int> offsets(chn.size());

    // Bits offsets
    int bts = 0;
    for (int i = chn.size() - 1; i >= 0; --i) {
        offsets[i] = bts;
        bts += chn[i].format;
    }

    // Summ
    for (size_t i = 0; i < chn.size(); ++i) {
        r += ((cnt >> offsets[i]) & ((1 << chn[i].format) - 1)) * chn[i].scaler;
    }

    return r;
}

// ----------------------------------------------------------------------------------
bool transform(BinaryBuffer& scrbuff,
    int offs,
    const Config& cfg,
    BinaryBuffer& dstbuff)
{
    const uint32_t vini = cfg.counter.init;
    const uint32_t vlim = vini + cfg.counter.volume;
    const uint16_t blksz = cfg.counter.unitsz;

    for (uint32_t cnt = vini; cnt < vlim; cnt += cfg.counter.step) {
        const uint32_t addrf = offs + glbaddr(cfg.transform.src, cnt);
        const uint32_t addrt = offs + glbaddr(cfg.transform.dst, cnt);

        // Bounds check
        if ((addrf > (scrbuff.size() - blksz)) || (addrt > (dstbuff.size() - blksz)))
            return false;

        uint8_t* psrc = scrbuff.raw() + addrf;
        uint8_t* pdst = dstbuff.raw() + addrt;

#if DBG_VERBOSE >= 2

        std::cout << "Operation #";
        std::cout << std::setw(6) << std::setfill(' ');
        std::cout << std::dec << cnt;

        std::cout << "   x";
        std::cout << std::hex << std::setw(6) << std::setfill('0');
        std::cout << addrf;

        std::cout << " > x" << std::hex << std::setw(6) << std::setfill('0');
        std::cout << addrt;
        std::cout << "    SZ( " << std::dec << blksz << " )\n";

#endif

        memcpy(pdst, psrc, blksz);
    }

    return true;
}

// ----------------------------------------------------------------------------------
int runproc(const std::string& infile,
    int offs,
    const Config& cfg,
    const std::string& outfile)
{
    BinaryBuffer scrbuff;
    BinaryBuffer dstbuff;

    // Load Original Source
    if (!scrbuff.loadFromFile(infile)) {
        return error(appErr_ReadSourceFileIO, "invalid source file : ", infile);
    }

#if DBG_VERBOSE >= 2
    std::cout << "source file size : " << scrbuff.size() << "\n";
#endif

    // Clone
    dstbuff = scrbuff.clone();

    // Transform
    if (!transform(scrbuff, offs, cfg, dstbuff)) {
        return error(appErr_TransformationFailed, "Выход за границы");
    }

    // Save results
    if (!dstbuff.saveToFile(outfile)) {
        return error(
            appErr_InvalidDestination, "Ошибка записи результата: ", outfile);
    }

    return appErr_AllOk;
}

// ----------------------------------------------------------------------------------
int main(int argc, char* argv[])
{

    if (argc > 1 && std::string(argv[1]) == "--version") {
        std::cout << "pushk2pre1move version " << APP_VERSION
                  << " (C) 2026 V01G04A81" << std::endl;
        return 0;
    }

    if (argc != 5) {
        return error(appErr_NotEnoughArgs,
            "Недостаточное количество входных параметров");
    }

    // Разбор входных параметров
    std::string infile = argv[1];
    int inoffs = std::stoi(argv[2]);
    std::string cfgparam = argv[3];
    std::string outfile = argv[4];

    // Check Source file
    if (!fileexists(infile)) {
        return error(appErr_SourceFileMissed, "Отсутствует входной файл: ", infile);
    }

    // Check configuration type : .yaml / base64
    Config cfg;

    if (cfgparam.ends_with(".yaml") || cfgparam.ends_with(".yml")) {
        std::cout << "YAML file detected\n";

        if (!fileexists(cfgparam)) {
            return error(appErr_ConfigFileMissed,
                "Отсутствует конфигурационный файл: ",
                cfgparam);
        }

        // Load transformation parameters
        if (!cfg.InitFromFile(cfgparam.c_str())) {
            return error(appErr_YAMLParserError,
                "Ошибка параметров конфигурационного файла: ",
                cfgparam);
        }
    } else {
        auto decoded = base64_to_vector(cfgparam);
        if (decoded.empty()) {
            return error(appErr_Base64Decode, "BASE64 conversion issue");
        }

        const char* cstr = reinterpret_cast<const char*>(decoded.data());
        if (!cfg.InitFromText(cstr)) {
            return error(appErr_Unsupported, "Ошибка параметров конфигурации BASE64");
        }
    }

#if DBG_VERBOSE > 0
    std::cout << "Input  : " << infile << "\n";
    std::cout << "Offset : " << inoffs << "\n";
    std::cout << "Config : " << cfgparam << "\n";
    std::cout << "Output : " << outfile << "\n";
    std::cout << "SRC channels: " << cfg.transform.src.size() << "\n";
    std::cout << "DST channels: " << cfg.transform.dst.size() << "\n";
#endif

    int r = runproc(infile, inoffs, cfg, outfile);

#if DBG_VERBOSE > 0
    if (r > 0) {
        std::cout << "Error code : " << r << "\n";
    } else {
        std::cout << "Transformation completed" << "\n";
    }
#endif

    return r;
}
