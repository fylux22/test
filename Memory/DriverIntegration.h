#pragma once
#include <Windows.h>
#include <string>
#include <memory>
#include <iostream>
#include "MemoryManager.h"
#include "../rickowens/RickOwens00-1.0.1/Communication.h"
#include "../rickowens/RickOwens00-1.0.1/Definitions.h"

// Enhanced memory manager with driver integration
class EnhancedMemoryManager : public MemoryManager {
private:
    std::unique_ptr<Communication> driverComm;
    bool useDriver = false;
    bool driverInitialized = false;
    
    // Obfuscated strings for stealth
    std::string GetObfuscatedDriverName() {
        // Simple XOR obfuscation - can be enhanced further
        std::string obfuscated = "\x52\x69\x63\x6B\x4F\x77\x65\x6E\x73\x30\x30"; // "RickOwens00"
        for (auto& c : obfuscated) c ^= 0x42;
        return obfuscated;
    }
    
public:
    EnhancedMemoryManager() : MemoryManager() {
        driverComm = std::make_unique<Communication>();
    }
    
    ~EnhancedMemoryManager() = default;
    
    // Initialize driver communication
    bool InitializeDriver() {
        try {
            if (!driverComm) {
                driverComm = std::make_unique<Communication>();
            }
            
            if (driverComm->isConnected()) {
                driverInitialized = true;
                useDriver = true;
                std::cout << "[+] Driver communication established" << std::endl;
                return true;
            }
            
            std::cout << "[-] Failed to establish driver communication" << std::endl;
            return false;
        }
        catch (const std::exception& e) {
            std::cout << "[-] Driver initialization error: " << e.what() << std::endl;
            return false;
        }
    }
    
    // Enhanced process attachment with driver fallback
    bool attachToProcess(const std::string& processName) override {
        // Try driver method first if available
        if (useDriver && driverInitialized) {
            try {
                int32_t pid = driverComm->findProcess(processName.c_str());
                if (pid != 0) {
                    if (driverComm->virtualAttach(pid)) {
                        std::cout << "[+] Attached to process using driver: " << processName << " (PID: " << pid << ")" << std::endl;
                        return true;
                    }
                }
            }
            catch (const std::exception& e) {
                std::cout << "[-] Driver attachment failed: " << e.what() << std::endl;
            }
        }
        
        // Fallback to syscall method
        bool result = MemoryManager::attachToProcess(processName);
        if (result) {
            std::cout << "[+] Attached to process using syscalls: " << processName << std::endl;
        }
        return result;
    }
    
    // Enhanced read with driver support
    template <typename T>
    T read(uintptr_t address) {
        if (useDriver && driverInitialized) {
            try {
                return driverComm->virtualRead<T>(address);
            }
            catch (const std::exception& e) {
                // Fallback to syscall method
                return MemoryManager::read<T>(address);
            }
        }
        return MemoryManager::read<T>(address);
    }
    
    // Enhanced write with driver support
    template <typename T>
    void write(uintptr_t address, T value) {
        if (useDriver && driverInitialized) {
            try {
                driverComm->virtualWrite<T>(address, value);
                return;
            }
            catch (const std::exception& e) {
                // Fallback to syscall method
                MemoryManager::write<T>(address, value);
            }
        }
        MemoryManager::write<T>(address, value);
    }
    
    // Enhanced string reading
    std::string readString(uintptr_t address) override {
        if (useDriver && driverInitialized) {
            try {
                return driverComm->readString(address);
            }
            catch (const std::exception& e) {
                return MemoryManager::readString(address);
            }
        }
        return MemoryManager::readString(address);
    }
    
    // Driver status check
    bool IsDriverActive() const {
        return useDriver && driverInitialized && driverComm && driverComm->isConnected();
    }
    
    // Get base address through driver
    uintptr_t getImageBase() {
        if (useDriver && driverInitialized) {
            try {
                return driverComm->findImage();
            }
            catch (const std::exception& e) {
                return getModuleAddress("RobloxPlayerBeta.exe");
            }
        }
        return getModuleAddress("RobloxPlayerBeta.exe");
    }
};

// Global enhanced memory manager instance
extern std::unique_ptr<EnhancedMemoryManager> g_MemoryManager;