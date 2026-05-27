/* ==========================================================================
 * Application   : pushk2pre1move
 * Description   : PUSHK Archiver: representation-first compression filter
 * Revision      : 1.0.1
 * Source        : https://github.com/vigatron/pushk2pre1move
 * Disclaimer    : Provided "AS IS", without warranty.
 * License       : MIT
 * File          : src/mods/misc.cpp
 * Content size  : 466
 * Date / Time   : 27-05-2026 21:53:56
 * MD5           : eda9373327756925c219fb81af4695e5
 * Notes         : MD5 = file content without header/footer
 * Encoding      : UTF-8
 * Author        : Viktor Glebov / V01G04A81
 * Copyright     : © 2025–2026 Viktor Glebov
 * ========================[ BEGIN FILE CONTENT ]============================ */
#include "misc.hpp"
#include <filesystem>

#include <iostream>

// ----------------------------------------------------------------------------------
bool fileexists(const std::string & path) {
    try {
        return std::filesystem::exists(path) &&
            std::filesystem::is_regular_file(path);
    } catch (const std::filesystem::filesystem_error& e) {
        std::cerr << "Ошибка доступа: " << e.what() << '\n';
        return false;
    }
}
/* ========================[  END FILE CONTENT  ]========================
 * File             : src/mods/misc.cpp
 * Content size     : 466
 * Date / Time      : 27-05-2026 21:53:56
 * MD5              : eda9373327756925c219fb81af4695e5
 * Copyright        : © 2025–2026 Viktor Glebov
 * ====================================================================== */