/* ==========================================================================
 * Application   : pushk2pre1move
 * Description   : PUSHK Archiver: representation-first compression filter
 * Revision      : 1.0.1
 * Source        : https://github.com/vigatron/pushk2pre1move
 * Disclaimer    : Provided "AS IS", without warranty.
 * License       : MIT
 * File          : src/mods/yinput.hpp
 * Content size  : 6112
 * Date / Time   : 27-05-2026 21:53:56
 * MD5           : ca0789239103924197b033996c1b3e55
 * Notes         : MD5 = file content without header/footer
 * Encoding      : UTF-8
 * Author        : Viktor Glebov / V01G04A81
 * Copyright     : © 2025–2026 Viktor Glebov
 * ========================[ BEGIN FILE CONTENT ]============================ */
#pragma once

#include <vector>
#include <fstream>
#include <cstdint>
#include <cstring>
#include <iostream>

class Config
{
public:

#pragma pack(push, 1)
    struct Channel {
        uint8_t  format = 0;
        uint16_t scaler = 0;
    };
#pragma pack(pop)

    struct Counter {
        uint32_t init = 0;
        uint32_t step = 0;
        uint32_t volume = 0;
        uint32_t unitsz = 0;
    };

    struct Transform {
        std::vector<Channel> src;
        std::vector<Channel> dst;
    };

public:
    Counter counter;
    Transform transform;

private:
    std::vector<char> buffer;

    enum Section {
        NONE,
        COUNTER,
        TRANSFORM
    };

public:

    bool InitFromFile(const char* filename) {
        if(!loadFile(filename)) return false;
        return Parse();
    }

    bool InitFromText(const char* text) {
        int tlen = strlen(text);
        buffer.resize( tlen + 1);
        memcpy(buffer.data(), text, tlen);
        buffer[tlen] = 0;
        return Parse();
    }

    bool Parse() {

        char* p = buffer.data();
        char* end = p + buffer.size();

        Section section = NONE;

        std::vector<Channel>* currentList = nullptr;
        Channel* currentChannel = nullptr;

        while (p < end)
        {
            char* line = p;

            while (p < end && *p != '\n') p++;
            if (p < end) *p++ = 0;

            trimLeft(line);
            if (*line == 0 || *line == '#')
                continue;

            // ===== LIST ITEM =====
            if (*line == '-') {
                line++;
                trimLeft(line);

                if (!currentList) {
                    std::cerr << "Error: List not selected\n";
                    return false;
                }

                currentList->emplace_back();
                currentChannel = &currentList->back();

                parseChannelKV(line, currentChannel);
                continue;
            }

            // ===== SECTION =====
            if (endsWith(line, ":")) {
                currentChannel = nullptr;
                if (eq(line, "counter:"))           { section = COUNTER; currentList = nullptr; }
                else if (eq(line, "transform:"))    { section = TRANSFORM; currentList = nullptr; }
                else if (eq(line, "src:"))          { if (section == TRANSFORM) currentList = &transform.src; }
                else if (eq(line, "dst:"))          { if (section == TRANSFORM) currentList = &transform.dst; }
                continue;
            }

            // ===== CHANNEL FIELD =====
            if (currentChannel) {
                parseChannelKV(line, currentChannel);
                continue;
            }

            // ===== GLOBAL =====
            parseGlobal(line, section);
        }

        return validate();
    }

    // catch (const std::exception& e) {
    //     std::cerr << "Config load error: " << e.what() << std::endl;
    //     return false;
    // }


private:

    bool loadFile(const char* filename) {

        std::ifstream f(filename, std::ios::binary);
        if (!f) return false;

        f.seekg(0, std::ios::end);
        size_t sz = f.tellg();
        f.seekg(0);

        buffer.resize(sz + 1);
        f.read(buffer.data(), sz);
        buffer[sz] = 0;

        return true;
    }

    static void trimLeft(char*& s) {
        while (*s == ' ' || *s == '\t') s++;
    }

    static bool startsWith(const char* s, const char* pref, int *plen=nullptr) {
        bool m = strncmp(s, pref, strlen(pref)) == 0;
        if(m && plen) { *plen = strlen(pref); }
        return m;
    }

    static bool endsWith(const char* s, const char* suffix) {
        size_t ls = strlen(s);
        size_t lf = strlen(suffix);
        if (ls < lf) return false;
        return strcmp(s + ls - lf, suffix) == 0;
    }

    static bool eq(const char* a, const char* b) {
        return strcmp(a, b) == 0;
    }

    static uint32_t parseInt(const char* s) {
        while (*s == ' ') s++;
        uint32_t v = 0;
        while (*s >= '0' && *s <= '9') { v = v * 10 + (*s - '0'); s++; }
        return v;
    }

    bool parseChannelKV(char* line, Channel* ch) {

        if (startsWith(line, "format:")) {
            line += 7;
            ch->format = (uint8_t)parseInt(line);
            return true;
        }
        if (startsWith(line, "scaler:")) {
            line += 7;
            ch->scaler = (uint16_t)parseInt(line);
            return true;
        }
        return false;
    }

    void parseGlobal(char* line, Section section) {

        int  dlen;
        bool pfxInit        = startsWith(line, "init:", &dlen);
        bool pfxStep        = startsWith(line, "step:", &dlen);
        bool pfxVolume      = startsWith(line, "volume:", &dlen);
        bool pfxUnitSize    = startsWith(line, "unit_size:", &dlen) || startsWith(line, "unitsz:", &dlen);

        if (section == COUNTER) {
            if (pfxInit)                { counter.init      = parseInt(line + dlen); }
            else if (pfxStep)           { counter.step      = parseInt(line + dlen); }
            else if (pfxVolume)         { counter.volume    = parseInt(line + dlen); }
            else if (pfxUnitSize)       { counter.unitsz    = parseInt(line + dlen); }
        }
    }

    bool validate() {

        if (transform.src.empty()) { std::cerr << "Error: src empty\n"; return false; }
        if (transform.dst.empty()) { std::cerr << "Error: dst empty\n"; return false; }

        for (auto& c : transform.src) if (!validateChannel(c)) return false;
        for (auto& c : transform.dst) if (!validateChannel(c)) return false;

        return counter.volume;
    }

    static bool validateChannel(const Channel& c) {

        if (c.format == 0) {
            std::cerr << "Error: format=0 invalid\n";
            return false;
        }

        if (!isPowerOfTwo(c.scaler)) {
            std::cerr << "Error: scaler must be power of two\n";
            return false;
        }

        return true;
    }

    static bool isPowerOfTwo(uint32_t v)
    {
        return v && ((v & (v - 1)) == 0);
    }
};
/* ========================[  END FILE CONTENT  ]========================
 * File             : src/mods/yinput.hpp
 * Content size     : 6112
 * Date / Time      : 27-05-2026 21:53:56
 * MD5              : ca0789239103924197b033996c1b3e55
 * Copyright        : © 2025–2026 Viktor Glebov
 * ====================================================================== */