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
