/* ==========================================================================
 * Application   : pushk2pre1move
 * Description   : PUSHK Archiver: representation-first compression filter
 * Revision      : 1.0.1
 * Source        : https://github.com/vigatron/pushk2pre1move
 * Disclaimer    : Provided "AS IS", without warranty.
 * License       : MIT
 * File          : src/mods/allerrs.hpp
 * Content size  : 2095
 * Date / Time   : 27-05-2026 21:53:56
 * MD5           : d410a3d31964b465c1558f1ace1287c6
 * Notes         : MD5 = file content without header/footer
 * Encoding      : UTF-8
 * Author        : Viktor Glebov / V01G04A81
 * Copyright     : © 2025–2026 Viktor Glebov
 * ========================[ BEGIN FILE CONTENT ]============================ */
#pragma once

#include <array>
#include <string>
#include <string_view>

enum class appErrs {
    AllOk = 0,               // Successful result
    NotEnoughArgs,           // Not enough input arguments
    InvalidArgument,         // Invalid Argument
    SourceFileMissed,        // Source file missing / wrong path
    ReadSourceFileIO,        // I/O error while reading source
    ConfigFileMissed,        // Configuration file missing or invalid
    YAMLParserError,         // YAML parser error
    InvalidDestination,      // Invalid destination (filename)
    TransformationFailed,    // Transformation failed (bounds check)
    Base64Decode,            // Base64 decode error
    Unsupported,             // Unsupported operation
    Count                    // Always last, for array size
};

struct ErrInfo {
    int id;
    std::string_view msg;
};

#define vok ((int)(appErrs::AllOk))

constexpr std::array<ErrInfo, static_cast<int>(appErrs::Count)> appErrTable{
    {{static_cast<int>(appErrs::AllOk), "Successful result"},
     {static_cast<int>(appErrs::NotEnoughArgs), "Not enough input arguments"},
     {static_cast<int>(appErrs::InvalidArgument), "int conversion error"},
     {static_cast<int>(appErrs::SourceFileMissed), "Source file missing / wrong path"},
     {static_cast<int>(appErrs::ReadSourceFileIO), "I/O error while reading source"},
     {static_cast<int>(appErrs::ConfigFileMissed), "Configuration file missing or invalid"},
     {static_cast<int>(appErrs::YAMLParserError), "YAML parser error"},
     {static_cast<int>(appErrs::InvalidDestination), "Invalid destination (filename)"},
     {static_cast<int>(appErrs::TransformationFailed), "Transformation failed (bounds check)"},
     {static_cast<int>(appErrs::Base64Decode), "Base64 decode error"},
     {static_cast<int>(appErrs::Unsupported), "Unsupported operation"}}};

void info(const std::string &str);
void info(const std::string &str, int val);
void info(const std::string &str, const std::string &param);

int verr(const appErrs &errCode);
int verr(const appErrs &errCode, const std::string &param);

/* ========================[  END FILE CONTENT  ]========================
 * File             : src/mods/allerrs.hpp
 * Content size     : 2095
 * Date / Time      : 27-05-2026 21:53:56
 * MD5              : d410a3d31964b465c1558f1ace1287c6
 * Copyright        : © 2025–2026 Viktor Glebov
 * ====================================================================== */