/* ==========================================================================
 * Application   : pushk2pre1move
 * Description   : PUSHK Archiver: representation-first compression filter
 * Revision      : 1.0.1
 * Source        : https://github.com/vigatron/pushk2pre1move
 * Disclaimer    : Provided "AS IS", without warranty.
 * License       : MIT
 * File          : src/mods/base64.cpp
 * Content size  : 952
 * Date / Time   : 27-05-2026 21:53:56
 * MD5           : 478ada2d83a4d9ba969b7f9aee1530d7
 * Notes         : MD5 = file content without header/footer
 * Encoding      : UTF-8
 * Author        : Viktor Glebov / V01G04A81
 * Copyright     : © 2025–2026 Viktor Glebov
 * ========================[ BEGIN FILE CONTENT ]============================ */
#include "base64.hpp"

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
        if (std::isspace(c)) continue;
        if (c == '=') break;
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

    output.push_back(0);

    return output;
}
/* ========================[  END FILE CONTENT  ]========================
 * File             : src/mods/base64.cpp
 * Content size     : 952
 * Date / Time      : 27-05-2026 21:53:56
 * MD5              : 478ada2d83a4d9ba969b7f9aee1530d7
 * Copyright        : © 2025–2026 Viktor Glebov
 * ====================================================================== */