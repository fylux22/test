#pragma once

#include <algorithm>
#include <cmath>
#include <chrono>
#include <Windows.h>

#include "../options.h"
#include "../Renderer/imgui/KeyBind.h"

inline void RunParry()
{
    while (true)
    {
        if (!Options::Parry::Enabled)
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
            continue;
        }

        static auto lastParryTime = std::chrono::steady_clock::now();
        static auto lastDelayTime = std::chrono::steady_clock::now();
        static bool isHolding = false;
        
        auto currentTime = std::chrono::steady_clock::now();
        
        // Handle hold time logic
        if (KeyBind::IsPressed(Options::Parry::ParryKey))
        {
            if (!isHolding)
            {
                isHolding = true;
                lastParryTime = currentTime;
            }
            
            auto holdElapsed = std::chrono::duration<float>(currentTime - lastParryTime).count();
            
            if (holdElapsed < Options::Parry::HoldTime)
            {
                std::this_thread::sleep_for(std::chrono::milliseconds(10));
                continue; // Wait for hold time
            }
        }
        else
        {
            isHolding = false;
        }

        // Handle delay time logic
        auto delayElapsed = std::chrono::duration<float>(currentTime - lastDelayTime).count();
        if (delayElapsed < Options::Parry::DelayTime)
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
            continue; // Wait for delay time
        }
        lastDelayTime = currentTime;

        // Auto parry logic
        if (Options::Parry::AutoParry)
        {
            // Simulate parry key press
            INPUT input[2];
            ZeroMemory(input, sizeof(input));
            
            // Key down
            input[0].type = INPUT_KEYBOARD;
            input[0].ki.wVk = Options::Parry::ParryKey;
            input[0].ki.dwFlags = 0;
            
            // Key up
            input[1].type = INPUT_KEYBOARD;
            input[1].ki.wVk = Options::Parry::ParryKey;
            input[1].ki.dwFlags = KEYEVENTF_KEYUP;
            
            SendInput(2, input, sizeof(INPUT));
            
            // Wait for parry window
            std::this_thread::sleep_for(std::chrono::milliseconds(static_cast<int>(Options::Parry::ParryWindow * 1000)));
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
}