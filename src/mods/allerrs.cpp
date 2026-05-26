#include "allerrs.hpp"
#include <iostream>

// ----------------------------------------------------------------------------------
int error(int errCode, std::string msg, std::string arg) {
    std::cerr << "Error " << errCode << ", " << msg;
    if(!arg.empty()) { std::cerr << " " << arg; }
    std::cerr << '\n';
    return errCode;
}
