// #0 2K = 256 x32 (4bytes) = 2K
// #1 2K = 256 x32 (4bytes) = 2K
// #2 2K = 256 x32 (4bytes) = 2K
// #3 2K = 256 x32 (4bytes) = 2K
// #4 2K = 256 x32 (4bytes) = 2K
// #5 2K = 256 x32 (4bytes) = 2K
// #6 2K = 256 x32 (4bytes) = 2K
// #7 2K = 256 x32 (4bytes) = 2K

// # 0 1K
// # 1 1K
// # 2 1K
// # 3 1K
// # 4 1K
// # 5 1K
// # 6 1K
// # 7 1K
// # 8 1K
// # 9 1K
// #10 1K
// #11 1K
// #12 1K
// #13 1K
// #14 1K
// #15 1K


// outdated

// 2 :  4 segments ( 3 valid )
// 3 :  8 tiles in YSeg
// 5 : 32 cells in line
// 3 :  8 Y-Byte

// ----------------------------------------------------------------------------------

#ifdef CMT_SECTION

uint32_t glbAddr( std::vector<Config::Channel> chn , uint32_t cnt ) {

	uint32_t r = 0;

	std::vector<int> shrd;

	{
		std::vector<int> shrt;

		// calc bts
		int bts = 0;

		for( int i = 0; i < chn.size(); i++ ) {
			shrt.push_back(bts);
			bts += chn[chn.size() - i - 1].format; }

			// reverse
		for( int i = 0; i < chn.size(); i++ ) {
			shrd.push_back( shrt[chn.size() - i - 1] ); }
	}

	for( int i = 0; i < chn.size(); i++ ) {
		int mask = ( 1 << chn[i].format ) - 1;
		int pos  = ( cnt >> shrd[i] ) & mask;
		int scl  = chn[i].scaler;
		int val  = pos * scl;
		r += val; }

	return r; }


#endif
