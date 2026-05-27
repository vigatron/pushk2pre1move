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
