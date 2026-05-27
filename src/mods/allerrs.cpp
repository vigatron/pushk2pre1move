/* ==========================================================================
 * Application   : pushk2pre1move
 * Description   : PUSHK Archiver: representation-first compression filter
 * Revision      : 1.0.1
 * Source        : https://github.com/vigatron/pushk2pre1move
 * Disclaimer    : Provided "AS IS", without warranty.
 * License       : MIT
 * File          : src/mods/allerrs.cpp
 * Content size  : 1156
 * Date / Time   : 27-05-2026 21:53:56
 * MD5           : 28052d50eb11b82bfff895d53a7cbf70
 * Notes         : MD5 = file content without header/footer
 * Encoding      : UTF-8
 * Author        : Viktor Glebov / V01G04A81
 * Copyright     : © 2025–2026 Viktor Glebov
 * ========================[ BEGIN FILE CONTENT ]============================ */
#include "allerrs.hpp"
#include <iomanip>
#include <iostream>

// ----------------------------------------------------------------------------------
void info(const std::string &str) {
    std::cout << str << "\n";
}

// ----------------------------------------------------------------------------------
void info(const std::string &str, int val) {
    std::cout << str << " " << val << "\n";
}

// ----------------------------------------------------------------------------------
void info(const std::string &str, const std::string &param) {
    std::cout << str << " " << param << "\n";
}

// ----------------------------------------------------------------------------------
int verr(const appErrs &errCode) {
    auto msg = appErrTable[(int)errCode].msg;
    std::cerr << "Error " << (int)errCode << ", " << msg << '\n';
    return (int)errCode;
}

// ----------------------------------------------------------------------------------
int verr(const appErrs &errCode, const std::string &param) {
    auto msg = appErrTable[(int)errCode].msg;
    std::cerr << "Error " << (int)errCode << ", " << msg << " " << param << '\n';
    return (int)errCode;
}

/* ========================[  END FILE CONTENT  ]========================
 * File             : src/mods/allerrs.cpp
 * Content size     : 1156
 * Date / Time      : 27-05-2026 21:53:56
 * MD5              : 28052d50eb11b82bfff895d53a7cbf70
 * Copyright        : © 2025–2026 Viktor Glebov
 * ====================================================================== */