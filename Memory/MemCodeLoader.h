#pragma once
#include <Windows.h>
#include <vector>
#include <memory>
#include <iostream>
#include "../memloader/memloader-main/memloader/load.hpp"
#include "../xorstr.hpp"

// Memory code loader for stealth execution
class MemCodeLoader {
private:
    // Obfuscated PE data storage
    struct ObfuscatedPE {
        std::vector<uint8_t> data;
        size_t size;
        uint32_t checksum;
        
        ObfuscatedPE(const uint8_t* peData, size_t peSize) : size(peSize) {
            data.resize(peSize);
            
            // Simple XOR obfuscation
            uint8_t key = 0xCC;
            for (size_t i = 0; i < peSize; ++i) {
                data[i] = peData[i] ^ key;
                key = (key + 1) % 256; // Rotating key
            }
            
            // Calculate checksum
            checksum = CalculateChecksum();
        }
        
        std::vector<uint8_t> Decrypt() const {
            std::vector<uint8_t> decrypted(size);
            uint8_t key = 0xCC;
            
            for (size_t i = 0; i < size; ++i) {
                decrypted[i] = data[i] ^ key;
                key = (key + 1) % 256;
            }
            
            return decrypted;
        }
        
        uint32_t CalculateChecksum() const {
            uint32_t sum = 0;
            for (const auto& byte : data) {
                sum += byte;
            }
            return sum;
        }
        
        bool IsValid() const {
            return CalculateChecksum() == checksum;
        }
    };
    
    std::vector<ObfuscatedPE> loadedModules;
    
    // Anti-analysis techniques
    void AntiDebugCheck() {
        // Simple anti-debugging check
        if (IsDebuggerPresent()) {
            ExitProcess(0);
        }
        
        // Timing check
        DWORD start = GetTickCount();
        Sleep(1);
        DWORD end = GetTickCount();
        if (end - start > 10) { // Suspicious delay
            ExitProcess(0);
        }
    }
    
    // Memory protection for loaded code
    bool ProtectMemory(void* address, size_t size, DWORD protection) {
        DWORD oldProtect;
        return VirtualProtect(address, size, protection, &oldProtect);
    }
    
public:
    MemCodeLoader() {
        AntiDebugCheck();
    }
    
    // Load PE from memory
    bool LoadFromMemory(const uint8_t* peData, size_t peSize, const std::string& moduleName = "") {
        try {
            AntiDebugCheck();
            
            // Store obfuscated copy
            ObfuscatedPE obfPE(peData, peSize);
            if (!obfPE.IsValid()) {
                std::cout << xorstr_("[-] Invalid PE data") << std::endl;
                return false;
            }
            
            // Decrypt for loading
            auto decrypted = obfPE.Decrypt();
            
            // Use memloader to load the PE
            if (loadbytes(decrypted.data(), decrypted.size())) {
                loadedModules.push_back(std::move(obfPE));
                std::cout << xorstr_("[+] Module loaded from memory: ") << moduleName << std::endl;
                return true;
            }
            
            std::cout << xorstr_("[-] Failed to load module: ") << moduleName << std::endl;
            return false;
        }
        catch (const std::exception& e) {
            std::cout << xorstr_("[-] Exception loading module: ") << e.what() << std::endl;
            return false;
        }
    }
    
    // Load embedded module (compile-time embedded)
    template<size_t N>
    bool LoadEmbeddedModule(const uint8_t (&embeddedData)[N], const std::string& moduleName) {
        return LoadFromMemory(embeddedData, N, moduleName);
    }
    
    // Execute shellcode from memory
    bool ExecuteShellcode(const uint8_t* shellcode, size_t size) {
        try {
            AntiDebugCheck();
            
            // Allocate executable memory
            void* execMem = VirtualAlloc(nullptr, size, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);
            if (!execMem) {
                std::cout << xorstr_("[-] Failed to allocate executable memory") << std::endl;
                return false;
            }
            
            // Copy shellcode
            memcpy(execMem, shellcode, size);
            
            // Change protection to execute-only
            if (!ProtectMemory(execMem, size, PAGE_EXECUTE_READ)) {
                VirtualFree(execMem, 0, MEM_RELEASE);
                return false;
            }
            
            // Execute in separate thread
            HANDLE hThread = CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)execMem, nullptr, 0, nullptr);
            if (hThread) {
                WaitForSingleObject(hThread, INFINITE);
                CloseHandle(hThread);
            }
            
            // Clean up
            VirtualFree(execMem, 0, MEM_RELEASE);
            return true;
        }
        catch (const std::exception& e) {
            std::cout << xorstr_("[-] Exception executing shellcode: ") << e.what() << std::endl;
            return false;
        }
    }
    
    // Get number of loaded modules
    size_t GetLoadedModuleCount() const {
        return loadedModules.size();
    }
    
    // Clear all loaded modules
    void ClearModules() {
        loadedModules.clear();
    }
    
    // Integrity check for loaded modules
    bool VerifyIntegrity() {
        for (const auto& module : loadedModules) {
            if (!module.IsValid()) {
                std::cout << xorstr_("[-] Module integrity check failed") << std::endl;
                return false;
            }
        }
        return true;
    }
};

// Global memcode loader instance
extern std::unique_ptr<MemCodeLoader> g_MemCodeLoader;