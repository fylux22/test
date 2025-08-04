#pragma once
#include <Windows.h>
#include <vector>
#include <map>
#include <thread>
#include <chrono>
#include <random>
#include "../xorstr.hpp"

// Obfuscated key mapping system
class ObfuscatedKeyMapper {
private:
    // XOR key for obfuscation
    static constexpr uint8_t XOR_KEY = 0xAB;
    
    // Obfuscated virtual key codes
    struct ObfuscatedKey {
        uint8_t obfuscated_code;
        uint8_t original_code;
        
        ObfuscatedKey(uint8_t code) : original_code(code) {
            obfuscated_code = code ^ XOR_KEY;
        }
        
        uint8_t GetKey() const {
            return obfuscated_code ^ XOR_KEY;
        }
    };
    
    std::map<std::string, ObfuscatedKey> keyMap;
    std::random_device rd;
    std::mt19937 gen;
    
    // Anti-debugging timing randomization
    void RandomDelay() {
        std::uniform_int_distribution<> dis(1, 5);
        std::this_thread::sleep_for(std::chrono::microseconds(dis(gen)));
    }
    
    // Obfuscated key press simulation
    void ObfuscatedKeyPress(uint8_t vKey, bool keyDown) {
        RandomDelay();
        
        // Multiple methods to avoid detection
        static int method = 0;
        method = (method + 1) % 3;
        
        switch (method) {
            case 0:
                keybd_event(vKey, 0, keyDown ? 0 : KEYEVENTF_KEYUP, 0);
                break;
            case 1: {
                INPUT input = {};
                input.type = INPUT_KEYBOARD;
                input.ki.wVk = vKey;
                input.ki.dwFlags = keyDown ? 0 : KEYEVENTF_KEYUP;
                SendInput(1, &input, sizeof(INPUT));
                break;
            }
            case 2: {
                // Hardware scan code method
                UINT scanCode = MapVirtualKey(vKey, MAPVK_VK_TO_VSC);
                keybd_event(vKey, scanCode, keyDown ? 0 : KEYEVENTF_KEYUP, 0);
                break;
            }
        }
        
        RandomDelay();
    }
    
public:
    ObfuscatedKeyMapper() : gen(rd()) {
        InitializeKeyMap();
    }
    
    void InitializeKeyMap() {
        // Initialize with obfuscated key mappings
        keyMap[xorstr_("PARRY")] = ObfuscatedKey(VK_F);
        keyMap[xorstr_("BLOCK")] = ObfuscatedKey(VK_G);
        keyMap[xorstr_("ATTACK")] = ObfuscatedKey(VK_LBUTTON);
        keyMap[xorstr_("SPECIAL")] = ObfuscatedKey(VK_R);
        keyMap[xorstr_("DODGE")] = ObfuscatedKey(VK_SPACE);
        keyMap[xorstr_("MENU")] = ObfuscatedKey(VK_INSERT);
    }
    
    // Secure key press with timing obfuscation
    void PressKey(const std::string& keyName, int holdTimeMs = 50) {
        auto it = keyMap.find(keyName);
        if (it == keyMap.end()) return;
        
        uint8_t vKey = it->second.GetKey();
        
        std::thread([this, vKey, holdTimeMs]() {
            // Random pre-delay
            std::uniform_int_distribution<> preDis(0, 5);
            std::this_thread::sleep_for(std::chrono::milliseconds(preDis(gen)));
            
            // Key down
            ObfuscatedKeyPress(vKey, true);
            
            // Hold time with randomization
            std::uniform_int_distribution<> holdDis(holdTimeMs - 10, holdTimeMs + 10);
            std::this_thread::sleep_for(std::chrono::milliseconds(holdDis(gen)));
            
            // Key up
            ObfuscatedKeyPress(vKey, false);
            
            // Random post-delay
            std::uniform_int_distribution<> postDis(0, 3);
            std::this_thread::sleep_for(std::chrono::milliseconds(postDis(gen)));
        }).detach();
    }
    
    // Update key mapping dynamically
    void UpdateKeyMapping(const std::string& keyName, uint8_t newKey) {
        keyMap[keyName] = ObfuscatedKey(newKey);
    }
    
    // Get current key for a mapping
    uint8_t GetCurrentKey(const std::string& keyName) {
        auto it = keyMap.find(keyName);
        return (it != keyMap.end()) ? it->second.GetKey() : 0;
    }
    
    // Advanced key sequence
    void ExecuteKeySequence(const std::vector<std::pair<std::string, int>>& sequence) {
        std::thread([this, sequence]() {
            for (const auto& [keyName, delay] : sequence) {
                PressKey(keyName);
                if (delay > 0) {
                    std::this_thread::sleep_for(std::chrono::milliseconds(delay));
                }
            }
        }).detach();
    }
    
    // Check if key is currently pressed
    bool IsKeyPressed(const std::string& keyName) {
        auto it = keyMap.find(keyName);
        if (it == keyMap.end()) return false;
        
        return (GetAsyncKeyState(it->second.GetKey()) & 0x8000) != 0;
    }
    
    // Humanized key press with variable timing
    void HumanizedKeyPress(const std::string& keyName, float minHold = 0.05f, float maxHold = 0.15f) {
        auto it = keyMap.find(keyName);
        if (it == keyMap.end()) return;
        
        uint8_t vKey = it->second.GetKey();
        
        std::thread([this, vKey, minHold, maxHold]() {
            // Human-like pre-delay
            std::uniform_real_distribution<float> preDis(0.001f, 0.020f);
            std::this_thread::sleep_for(std::chrono::duration<float>(preDis(gen)));
            
            ObfuscatedKeyPress(vKey, true);
            
            // Human-like hold time
            std::uniform_real_distribution<float> holdDis(minHold, maxHold);
            std::this_thread::sleep_for(std::chrono::duration<float>(holdDis(gen)));
            
            ObfuscatedKeyPress(vKey, false);
            
            // Human-like post-delay
            std::uniform_real_distribution<float> postDis(0.001f, 0.010f);
            std::this_thread::sleep_for(std::chrono::duration<float>(postDis(gen)));
        }).detach();
    }
};

// Global obfuscated key mapper instance
extern std::unique_ptr<ObfuscatedKeyMapper> g_KeyMapper;