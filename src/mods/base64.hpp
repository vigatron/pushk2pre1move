/* ==========================================================================
 * Application   : pushk2pre1move
 * Description   : PUSHK Archiver: representation-first compression filter
 * Revision      : 1.0.1
 * Source        : https://github.com/vigatron/pushk2pre1move
 * Disclaimer    : Provided "AS IS", without warranty.
 * License       : MIT
 * File          : src/mods/base64.hpp
 * Content size  : 135
 * Date / Time   : 27-05-2026 21:53:56
 * MD5           : 8c7788b41eefb05ca395cab0be167fd2
 * Notes         : MD5 = file content without header/footer
 * Encoding      : UTF-8
 * Author        : Viktor Glebov / V01G04A81
 * Copyright     : © 2025–2026 Viktor Glebov
 * ========================[ BEGIN FILE CONTENT ]============================ */
#pragma once

#include <stdint.h>
#include <vector>
#include <string>

std::vector<uint8_t> base64_to_vector(const std::string& input);
/* ========================[  END FILE CONTENT  ]========================
 * File             : src/mods/base64.hpp
 * Content size     : 135
 * Date / Time      : 27-05-2026 21:53:56
 * MD5              : 8c7788b41eefb05ca395cab0be167fd2
 * Copyright        : © 2025–2026 Viktor Glebov
 * ====================================================================== */