/* ==========================================================================
 * Application   : pushk2pre1move
 * Description   : PUSHK Archiver: representation-first compression filter
 * Revision      : 1.0.1
 * Source        : https://github.com/vigatron/pushk2pre1move
 * Disclaimer    : Provided "AS IS", without warranty.
 * License       : MIT
 * File          : src/main.cpp
 * Content size  : 5275
 * Date / Time   : 27-05-2026 21:53:56
 * MD5           : 564898a1c29637b6410e2dbb201d8f08
 * Notes         : MD5 = file content without header/footer
 * Encoding      : UTF-8
 * Author        : Viktor Glebov / V01G04A81
 * Copyright     : © 2025–2026 Viktor Glebov
 * ========================[ BEGIN FILE CONTENT ]============================ */

#include "allerrs.hpp"
#include "base64.hpp"
#include "cntblkmv.hpp"
#include "membuff.hpp"
#include "misc.hpp"
#include "vhplatform.hpp"
#include "yinput.hpp"

#include <algorithm>
#include <iomanip>
#include <iostream>

// ----------------------------------------------------------------------------------
uint32_t
glbaddr(const std::vector<Config::Channel> &chn, uint32_t cnt) {

    uint32_t r = 0;
    std::vector<int> offsets(chn.size());

    // Bits offsets
    int bts = 0;
    for (int i = chn.size() - 1; i >= 0; --i) {
        offsets[i] = bts;
        bts += chn[i].format;
    }

    // Summ
    for (size_t i = 0; i < chn.size(); ++i) {
        r += ((cnt >> offsets[i]) & ((1 << chn[i].format) - 1)) * chn[i].scaler;
    }

    return r;
}

// ----------------------------------------------------------------------------------
bool transform(BinaryBuffer &scrbuff,
               int offs,
               const Config &cfg,
               BinaryBuffer &dstbuff) {

    const uint32_t vini = cfg.counter.init;
    const uint32_t vlim = vini + cfg.counter.volume;
    const uint16_t blksz = cfg.counter.unitsz;

    for (uint32_t cnt = vini; cnt < vlim; cnt += cfg.counter.step) {

        const uint32_t addrf = offs + glbaddr(cfg.transform.src, cnt);
        const uint32_t addrt = offs + glbaddr(cfg.transform.dst, cnt);

        // Bounds check

        if (blksz >= scrbuff.size() || blksz >= dstbuff.size())
            return false;

        size_t srcavail = scrbuff.size() - blksz;
        size_t dstavail = dstbuff.size() - blksz;

        if (addrf > srcavail || addrt > dstavail)
            return false;

        uint8_t *psrc = scrbuff.raw() + addrf;
        uint8_t *pdst = dstbuff.raw() + addrt;

#if DBG_VERBOSE >= 2

        std::cout << "Operation #";
        std::cout << std::setw(6) << std::setfill(' ');
        std::cout << std::dec << cnt;

        std::cout << "   x";
        std::cout << std::hex << std::setw(6) << std::setfill('0');
        std::cout << addrf;

        std::cout << " > x" << std::hex << std::setw(6) << std::setfill('0');
        std::cout << addrt;
        std::cout << "    SZ( " << std::dec << blksz << " )\n";

#endif

        std::copy_n(psrc, blksz, pdst);
    }

    return true;
}

// ----------------------------------------------------------------------------------
int runproc(const std::string &infile,
            int offs,
            const Config &cfg,
            const std::string &outfile) {
    BinaryBuffer scrbuff;
    BinaryBuffer dstbuff;

    // Load Original Source
    if (!scrbuff.loadFromFile(infile)) {
        return verr(appErrs::ReadSourceFileIO, infile);
    }

#if DBG_VERBOSE >= 2
    std::cout << "source file size : " << scrbuff.size() << "\n";
#endif

    // Clone
    dstbuff = scrbuff.clone();

    // Transform
    if (!transform(scrbuff, offs, cfg, dstbuff)) {
        return verr(appErrs::TransformationFailed);
    }

    // Save results
    if (!dstbuff.saveToFile(outfile)) {
        return verr(appErrs::InvalidDestination, outfile);
    }

    return vok;
}

// ----------------------------------------------------------------------------------
int main(int argc, char *argv[]) {

    if (argc > 1 && std::string(argv[1]) == "--version") {
        std::cout << "pushk2pre1move version " << APP_VERSION
                  << " (C) 2026 V01G04A81" << std::endl;
        return 0;
    }

    if (argc != 5) {
        return verr(appErrs::NotEnoughArgs);
    }

    // Разбор входных параметров
    std::string infile = argv[1];

    int inoffs;
    try {
        inoffs = std::stoi(argv[2]);
    } catch (const std::invalid_argument &e) {
        return verr(appErrs::InvalidArgument, "offset");
    }
    if (inoffs < 0) {
        return verr(appErrs::InvalidArgument, "offset must be >= 0");
    }

    std::string cfgparam = argv[3];
    std::string outfile = argv[4];

    // Check Source file
    if (!fileexists(infile)) {
        return verr(appErrs::SourceFileMissed, infile);
    }

    // Check configuration type : .yaml / base64
    Config cfg;

    if (cfgparam.ends_with(".yaml") || cfgparam.ends_with(".yml")) {
        std::cout << "YAML file detected\n";

        if (!fileexists(cfgparam)) {
            return verr(appErrs::ConfigFileMissed, cfgparam);
        }

        // Load transformation parameters
        if (!cfg.InitFromFile(cfgparam.c_str())) {
            return verr(appErrs::YAMLParserError, cfgparam);
        }

    } else {

        auto decoded = base64_to_vector(cfgparam);
        if (decoded.empty()) {
            return verr(appErrs::Base64Decode);
        }

        const char *cstr = reinterpret_cast<const char *>(decoded.data());
        if (!cfg.InitFromText(cstr)) {
            return verr(appErrs::Unsupported);
        }
    }

#if DBG_VERBOSE > 0
    info("Input  :", infile);
    info("Offset :", inoffs);
    info("Config :", cfgparam);
    info("Output :", outfile);
    info("SRC channels:", cfg.transform.src.size());
    info("DST channels:", cfg.transform.dst.size());
#endif

    int r = runproc(infile, inoffs, cfg, outfile);

#if DBG_VERBOSE > 0
    if (r > 0) {
        info("Error code :", r);
    } else {
        info("Transformation completed");
    }
#endif

    return r;
}
/* ========================[  END FILE CONTENT  ]========================
 * File             : src/main.cpp
 * Content size     : 5275
 * Date / Time      : 27-05-2026 21:53:56
 * MD5              : 564898a1c29637b6410e2dbb201d8f08
 * Copyright        : © 2025–2026 Viktor Glebov
 * ====================================================================== */