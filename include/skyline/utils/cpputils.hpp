#pragma once

#include "types.h"
#include "operator.h"

#include "nn/fs.h"
#include "nn/settings.h"

#include <cstring>
#include <functional>
#include <string>
#include <memory>

namespace skyline::utils {

    enum region : u8
    {
        Text,
        Rodata,
        Data,
        Bss,
        Heap
    };

    extern std::string g_RomMountStr;

    extern nn::os::EventType g_RomMountedEvent;

    extern u64 g_MainTextAddr;
    extern u64 g_MainRodataAddr;
    extern u64 g_MainDataAddr;
    extern u64 g_MainBssAddr;
    extern u64 g_MainHeapAddr;

    extern nn::settings::system::FirmwareVersion g_CachedFwVer;

    void init();

    Result walkDirectory(std::string const&, std::function<void(nn::fs::DirectoryEntry const&,  std::shared_ptr<std::string>)>, bool recursive = true);
    Result readEntireFile(std::string const&, void**, size_t*);
    Result readFile(std::string const&, s64, void*, size_t);
    Result writeFile(std::string const&, s64, void*, size_t);
    Result entryCount(u64*, std::string const&, nn::fs::DirectoryEntryType);
    extern "C" void* getRegionAddress(skyline::utils::region);
    
    struct Sha256Hash {
        u8 hash[0x20];

        bool operator==(const Sha256Hash &o) const {
            return std::memcmp(this, &o, sizeof(*this)) == 0;
        }
        bool operator!=(const Sha256Hash &o) const {
            return std::memcmp(this, &o, sizeof(*this)) != 0;
        }
        bool operator<(const Sha256Hash &o) const {
            return std::memcmp(this, &o, sizeof(*this)) < 0;
        }
        bool operator>(const Sha256Hash &o) const {
            return std::memcmp(this, &o, sizeof(*this)) > 0;
        }
    };
};