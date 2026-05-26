#include "allerrs.hpp"
#include <iostream>

// ----------------------------------------------------------------------------------
int error(int errCode, std::string msg) {
    std::cerr << "Error " << errCode << ", " << msg << '\n';
    return errCode;
}

// ----------------------------------------------------------------------------------
int error(int errCode, std::string msg, std::string arg) {
    std::cerr << "Error " << errCode << ", " << msg << " " << arg << '\n';
    return errCode;
}
