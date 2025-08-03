#pragma once
#include "obfuscator.hpp"

// Create a simple macro that returns an object with decrypt() method
#define skCrypt(str) ([]() { \
    static auto obf_str = make_obfuscated(str); \
    struct wrapper { \
        const char* decrypt() const { return obf_str.decrypt(); } \
    }; \
    return wrapper{}; \
}())
