#pragma once

#include "vhplatform.hpp"

// TODO : bounds check ( filesize vs matrix_params : possible out range ? )

class CntBlkMv {

	public:

		CntBlkMv() { }

		void transform( std::string cfg ) {

		}

	private:

		// Source
		std::string				infile;
		int						infile_offset;	// Start address (offset) 

		// Transformation matrix
		int						cnt_init_val;	// Counter initial value
		int						cnt_step;		// Counter step
		int						cnt_volume;		// Counter max value
		int						cnt_unitsz;		// Unit size in bytes
		int						cnt_format;		// Example:	233 bits = 2:3:3
		std::vector<int>		cnt_src;		// address mul:mul:mul
		std::vector<int>		cnt_dst;		// address mul:mul:mul

		// Result
		std::string 			outfile;


		void DefCfz_ZXOrigLinear() {

		}
};
