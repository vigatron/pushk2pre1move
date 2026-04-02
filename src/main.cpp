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

uint32_t srcAddr( Config & cfg , uint32_t cnt ) {
	return glbAddr( cfg.transform.src , cnt ) ; }

// ----------------------------------------------------------------------------------

uint32_t dstAddr( Config & cfg , uint32_t cnt ) {
	return glbAddr( cfg.transform.dst , cnt ) ; }

// ----------------------------------------------------------------------------------

bool Transform( BinaryBuffer & scrbuff , int start_offset , Config & cfg , BinaryBuffer &	dstbuff ) {

	uint32_t vini = cfg.counter.init;
	uint32_t vlim = vini + cfg.counter.volume;
	uint16_t blksz = cfg.counter.unit_size;

	for( int cnt = vini; cnt < vlim ; cnt += cfg.counter.step ) {

		uint32_t addrf = start_offset + srcAddr( cfg , cnt );
		uint32_t addrt = start_offset + dstAddr( cfg , cnt );

		// Bounds check
		if( addrf > ( scrbuff.size() - blksz ) ) return appErr_TransformationFailed;
		if( addrt > ( dstbuff.size() - blksz ) ) return appErr_TransformationFailed;

		uint8_t * psrc = scrbuff.raw() + addrf;
		uint8_t * pdst = dstbuff.raw() + addrt;

		#if DBG_VERBOSE >= 2
		std::cout << "Operation #" << std::setw(6) << std::setfill(' ') << std::dec << cnt;
		std::cout << "   x" << std::hex << std::setw(6) << std::setfill('0') << addrf;
		std::cout << " > x" << std::hex << std::setw(6) << std::setfill('0') << addrt;
		std::cout << "    SZ( " << std::dec << blksz << " )\n";
		#endif

		memcpy( pdst , psrc, blksz ); }

	return true; }

// ----------------------------------------------------------------------------------

int runproc( std::string infile, int start_offset , Config & cfg, std::string outfile ) {

	BinaryBuffer	scrbuff;
	BinaryBuffer	dstbuff;

	// Load Original Source

	if (!scrbuff.loadFromFile( infile )) {
		std::cout << "invalid source file : " << infile << "\n";
		return appErr_ReadSourceFileIO; }

	#if DBG_VERBOSE >= 2
	std::cout << "source file size : " << scrbuff.size()  << "\n";
	#endif

	// Clone
	dstbuff = scrbuff.clone();

	// Transform
	if( ! Transform( scrbuff , start_offset , cfg , dstbuff )) {
		return appErr_TransformationFailed; }

	// Save results
	if (!dstbuff.saveToFile( outfile )) {
		return appErr_InvalidDestination; }

	return appErr_AllOk; }

// ----------------------------------------------------------------------------------

bool fileExists(const std::string& path) {
	try {
		return std::filesystem::exists(path) &&
			std::filesystem::is_regular_file(path);
	} catch (const std::filesystem::filesystem_error& e) {
		std::cerr << "Ошибка доступа: " << e.what() << '\n';
		return false; } }

// ----------------------------------------------------------------------------------
 
int main ( int argc, char * argv[] ) {

	if(argc != 5 ) { return appErr_NotEnoughArgs; }

	// Разбор входных параметров
	std::string 	infile	= argv[1];
	int				inoffs  = std::stoi( argv[2] );
	std::string 	cfgfile = argv[3];
	std::string 	outfile = argv[4];

	// Check Source file
	if( ! fileExists ( infile ) ) {
		return appErr_SourceFileMissed; }

	// Check Config File
	if( ! fileExists ( cfgfile ) ) {
		return appErr_ConfigFileMissed; }

	#if DBG_VERBOSE > 0
	std::cout << "Input  : "	<< infile	<< "\n";
	std::cout << "Offset : "	<< inoffs	<< "\n";
	std::cout << "Config : "	<< cfgfile	<< "\n";
	std::cout << "Output : "	<< outfile	<< "\n";
	#endif

	// Load transformation parameters
	Config cfg;

	if ( ! cfg.load( cfgfile.c_str() ) ) {
		return appErr_YAMLParserError; }

	#if DBG_VERBOSE > 0
	std::cout << "SRC channels: "	<< cfg.transform.src.size() << "\n";
	std::cout << "DST channels: "	<< cfg.transform.dst.size() << "\n";
	#endif

	int r = runproc( infile , inoffs , cfg , outfile );

	#if DBG_VERBOSE > 0
	if( r > 0 ) { std::cout << "Error code : "	<< r << "\n"; }
	else 		{ std::cout << "Transformation completed" << "\n"; }
	#endif

	return r; }
