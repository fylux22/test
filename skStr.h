#pragma once

#include <string>

// Simple string obfuscation class for KeyAuth integration
class skCrypt
{
private:
    std::string str;
public:
    skCrypt(const char* data) : str(data) {}
    
    std::string decrypt()
    {
        return str;
    }
    
    const char* c_str()
    {
        return str.c_str();
    }
};

#define skCrypt(str) skCrypt(str).decrypt()