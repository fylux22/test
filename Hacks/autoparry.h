#pragma once

#include "../options.h"
#include "../globals.h"
#include "../Renderer/W2S.h"
#include "../Renderer/imgui/imgui.h"

#include <thread>
#include <chrono>
#include <vector>
#include <string>
#include <deque>

struct ParryDebugInfo
{
    std::chrono::high_resolution_clock::time_point timestamp;
    std::string message;
    bool isSuccess;
    float distance;
    float timing;
    std::string targetName;
};

struct AttackData
{
    std::string attackerName;
    Vectors::Vector3 attackerPos;
    Vectors::Vector3 localPos;
    float distance;
    float angle;
    std::chrono::high_resolution_clock::time_point detectionTime;
    bool isValid;
    bool hasParried;
};

class AutoParryDebugger
{
private:
    std::deque<ParryDebugInfo> debugLog;
    std::vector<AttackData> detectedAttacks;
    std::chrono::high_resolution_clock::time_point lastParryTime;
    std::chrono::high_resolution_clock::time_point lastDebugUpdate;
    
    // Performance metrics
    int totalDetections = 0;
    int successfulParries = 0;
    int missedParries = 0;
    int falsePositives = 0;
    
    // Timing analysis
    std::vector<float> parryTimings;
    float averageParryTime = 0.0f;
    float bestParryTime = 999.0f;
    float worstParryTime = 0.0f;

public:
    void AddDebugEntry(const std::string& message, bool isSuccess = false, float distance = 0.0f, float timing = 0.0f, const std::string& targetName = "")
    {
        if (!Options::AutoParry::AutoParryDebugger) return;
        
        ParryDebugInfo info;
        info.timestamp = std::chrono::high_resolution_clock::now();
        info.message = message;
        info.isSuccess = isSuccess;
        info.distance = distance;
        info.timing = timing;
        info.targetName = targetName;
        
        debugLog.push_back(info);
        
        // Keep only last 50 entries
        if (debugLog.size() > 50)
            debugLog.pop_front();
    }
    
    void UpdateMetrics(float parryTime, bool success)
    {
        totalDetections++;
        
        if (success)
        {
            successfulParries++;
            parryTimings.push_back(parryTime);
            
            if (parryTime < bestParryTime) bestParryTime = parryTime;
            if (parryTime > worstParryTime) worstParryTime = parryTime;
            
            // Calculate average
            float sum = 0.0f;
            for (float time : parryTimings) sum += time;
            averageParryTime = sum / parryTimings.size();
            
            // Keep only last 100 timing samples
            if (parryTimings.size() > 100)
                parryTimings.erase(parryTimings.begin());
        }
        else
        {
            missedParries++;
        }
    }
    
    void RenderDebugOverlay(ImDrawList* drawList)
    {
        if (!Options::AutoParry::AutoParryDebugger || !Options::AutoParry::ShowDebugOverlay) return;
        
        auto now = std::chrono::high_resolution_clock::now();
        
        // Only update display every 100ms for performance
        if (std::chrono::duration_cast<std::chrono::milliseconds>(now - lastDebugUpdate).count() < 100)
            return;
            
        lastDebugUpdate = now;
        
        ImVec2 screenSize = ImGui::GetIO().DisplaySize;
        float overlayX = screenSize.x - 400.0f;
        float overlayY = 50.0f;
        
        // Background panel
        ImVec2 panelMin(overlayX - 10, overlayY - 10);
        ImVec2 panelMax(overlayX + 390, overlayY + 350);
        drawList->AddRectFilled(panelMin, panelMax, IM_COL32(0, 0, 0, 180));
        drawList->AddRect(panelMin, panelMax, IM_COL32(255, 255, 255, 100));
        
        // Title
        ImU32 titleColor = IM_COL32(100, 200, 255, 255);
        drawList->AddText(ImVec2(overlayX, overlayY), titleColor, "AUTO PARRY DEBUGGER");
        overlayY += 25;
        
        // Status
        std::string status = Options::AutoParry::AutoParry ? "ACTIVE" : "INACTIVE";
        ImU32 statusColor = Options::AutoParry::AutoParry ? IM_COL32(0, 255, 0, 255) : IM_COL32(255, 0, 0, 255);
        drawList->AddText(ImVec2(overlayX, overlayY), statusColor, ("Status: " + status).c_str());
        overlayY += 20;
        
        // Performance metrics
        if (Options::AutoParry::ShowTimingAnalysis && totalDetections > 0)
        {
            drawList->AddText(ImVec2(overlayX, overlayY), IM_COL32(255, 255, 255, 255), "=== PERFORMANCE METRICS ===");
            overlayY += 20;
            
            float successRate = (float)successfulParries / (float)totalDetections * 100.0f;
            drawList->AddText(ImVec2(overlayX, overlayY), IM_COL32(255, 255, 255, 255), 
                ("Total Detections: " + std::to_string(totalDetections)).c_str());
            overlayY += 15;
            
            drawList->AddText(ImVec2(overlayX, overlayY), IM_COL32(0, 255, 0, 255), 
                ("Successful: " + std::to_string(successfulParries)).c_str());
            overlayY += 15;
            
            drawList->AddText(ImVec2(overlayX, overlayY), IM_COL32(255, 0, 0, 255), 
                ("Missed: " + std::to_string(missedParries)).c_str());
            overlayY += 15;
            
            drawList->AddText(ImVec2(overlayX, overlayY), IM_COL32(255, 255, 0, 255), 
                ("Success Rate: " + std::to_string((int)successRate) + "%").c_str());
            overlayY += 20;
            
            if (parryTimings.size() > 0)
            {
                char timingStr[64];
                sprintf_s(timingStr, "Avg Timing: %.3fs", averageParryTime);
                drawList->AddText(ImVec2(overlayX, overlayY), IM_COL32(255, 255, 255, 255), timingStr);
                overlayY += 15;
                
                sprintf_s(timingStr, "Best: %.3fs | Worst: %.3fs", bestParryTime, worstParryTime);
                drawList->AddText(ImVec2(overlayX, overlayY), IM_COL32(255, 255, 255, 255), timingStr);
                overlayY += 20;
            }
        }
        
        // Recent log entries
        if (Options::AutoParry::LogDetections && !debugLog.empty())
        {
            drawList->AddText(ImVec2(overlayX, overlayY), IM_COL32(255, 255, 255, 255), "=== RECENT LOG ===");
            overlayY += 20;
            
            int count = 0;
            for (auto it = debugLog.rbegin(); it != debugLog.rend() && count < 8; ++it, ++count)
            {
                auto timeSince = std::chrono::duration_cast<std::chrono::milliseconds>(now - it->timestamp).count();
                
                ImU32 textColor = it->isSuccess ? IM_COL32(0, 255, 0, 255) : IM_COL32(255, 255, 255, 255);
                
                std::string logEntry = "[" + std::to_string(timeSince) + "ms] " + it->message;
                if (logEntry.length() > 45) logEntry = logEntry.substr(0, 42) + "...";
                
                drawList->AddText(ImVec2(overlayX, overlayY), textColor, logEntry.c_str());
                overlayY += 15;
            }
        }
        
        // Range indicator
        if (Options::AutoParry::ShowRangeIndicator)
        {
            auto localChar = Globals::Roblox::LocalPlayer.Character();
            if (localChar.address != 0)
            {
                auto localPos = localChar.FindFirstChild("HumanoidRootPart").Position();
                auto localPos2D = WorldToScreen(localPos);
                
                if (localPos2D.x != -1 && localPos2D.y != -1)
                {
                    float rangePixels = Options::AutoParry::ParryRange * 10.0f; // Approximate conversion
                    ImU32 rangeColor = IM_COL32((int)(Options::AutoParry::RangeColor[0] * 255), 
                                               (int)(Options::AutoParry::RangeColor[1] * 255), 
                                               (int)(Options::AutoParry::RangeColor[2] * 255), 100);
                    
                    drawList->AddCircle(ImVec2(localPos2D.x, localPos2D.y), rangePixels, rangeColor, 32, 2.0f);
                }
            }
        }
    }
    
    void Clear()
    {
        debugLog.clear();
        detectedAttacks.clear();
        totalDetections = 0;
        successfulParries = 0;
        missedParries = 0;
        falsePositives = 0;
        parryTimings.clear();
        averageParryTime = 0.0f;
        bestParryTime = 999.0f;
        worstParryTime = 0.0f;
    }
};

// Global debugger instance
inline AutoParryDebugger g_ParryDebugger;

inline bool IsPlayerFacingLocal(const RobloxPlayer& player)
{
    auto localChar = Globals::Roblox::LocalPlayer.Character();
    if (localChar.address == 0) return false;
    
    auto localPos = localChar.FindFirstChild("HumanoidRootPart").Position();
    auto playerPos = player.HumanoidRootPart.Position();
    auto playerCFrame = player.HumanoidRootPart.CFrame();
    
    // Get player's forward vector
    Vectors::Vector3 forwardVector = playerCFrame.GetForwardVector();
    
    // Vector from player to local player
    Vectors::Vector3 toLocal = (localPos - playerPos).Unit();
    
    // Calculate angle between forward vector and direction to local player
    float dotProduct = forwardVector.Dot(toLocal);
    float angle = acos(std::clamp(dotProduct, -1.0f, 1.0f)) * (180.0f / 3.14159f);
    
    return angle <= Options::AutoParry::FacingAngleTolerance;
}

inline bool ShouldParryPlayer(const RobloxPlayer& player)
{
    if (!Options::AutoParry::AutoParry) return false;
    
    auto localChar = Globals::Roblox::LocalPlayer.Character();
    if (localChar.address == 0) return false;
    
    auto localPos = localChar.FindFirstChild("HumanoidRootPart").Position();
    auto playerPos = player.HumanoidRootPart.Position();
    
    float distance = (localPos - playerPos).Magnitude();
    
    // Check range
    if (distance > Options::AutoParry::ParryRange)
    {
        if (Options::AutoParry::AutoParryDebugger)
            g_ParryDebugger.AddDebugEntry("Player " + player.Name + " out of range (" + std::to_string((int)distance) + " studs)");
        return false;
    }
    
    // Check if player is facing us (if enabled)
    if (Options::AutoParry::OnlyParryWhenFacing && !IsPlayerFacingLocal(player))
    {
        if (Options::AutoParry::AutoParryDebugger)
            g_ParryDebugger.AddDebugEntry("Player " + player.Name + " not facing us");
        return false;
    }
    
    // Check if player has a tool equipped (weapon detection)
    auto character = player.Character;
    auto tool = character.FindFirstChildOfClass("Tool");
    if (tool.address == 0)
    {
        if (Options::AutoParry::AutoParryDebugger)
            g_ParryDebugger.AddDebugEntry("Player " + player.Name + " has no weapon equipped");
        return false;
    }
    
    // Enhanced animation-based detection
    extern std::unique_ptr<AnimationDetection> g_AnimationDetection;
    if (g_AnimationDetection) {
        // Update animation state for this player
        g_AnimationDetection->UpdatePlayerAnimation(player);
        
        // Check if player is in attack animation
        if (!g_AnimationDetection->IsPlayerAttacking(player)) {
            if (Options::AutoParry::AutoParryDebugger)
                g_ParryDebugger.AddDebugEntry("Player " + player.Name + " not in attack animation");
            return false;
        }
        
        // Check if we're in the optimal parry window
        if (!g_AnimationDetection->IsInParryWindow(player)) {
            if (Options::AutoParry::AutoParryDebugger) {
                std::string animName = g_AnimationDetection->GetCurrentAnimationName(player);
                float progress = g_AnimationDetection->GetAnimationProgress(player);
                g_ParryDebugger.AddDebugEntry("Player " + player.Name + " not in parry window (" + animName + " " + std::to_string((int)(progress * 100)) + "%)");
            }
            return false;
        }
        
        if (Options::AutoParry::AutoParryDebugger) {
            std::string animName = g_AnimationDetection->GetCurrentAnimationName(player);
            float priority = g_AnimationDetection->GetAnimationPriority(player);
            g_ParryDebugger.AddDebugEntry("Animation detected: " + animName + " (Priority: " + std::to_string(priority) + ")");
        }
    }
    
    return true;
}

inline void PerformParry()
{
    static auto lastParryTime = std::chrono::high_resolution_clock::now();
    auto now = std::chrono::high_resolution_clock::now();
    
    // Cooldown check
    auto timeSinceLastParry = std::chrono::duration_cast<std::chrono::milliseconds>(now - lastParryTime).count();
    if (timeSinceLastParry < 200) // 200ms cooldown
        return;
    
    lastParryTime = now;
    
    // Perform the parry input using obfuscated key mapper
    std::thread([=]() {
        // Add prediction delay if smart timing is enabled
        if (Options::AutoParry::SmartTiming)
            std::this_thread::sleep_for(std::chrono::milliseconds((int)(Options::AutoParry::PredictionTime * 1000)));
        
        // Add configured delay
        std::this_thread::sleep_for(std::chrono::milliseconds((int)(Options::AutoParry::ParryDelay * 1000)));
        
        // Use obfuscated key mapper for stealth
        extern std::unique_ptr<ObfuscatedKeyMapper> g_KeyMapper;
        if (g_KeyMapper) {
            g_KeyMapper->HumanizedKeyPress("PARRY", Options::AutoParry::HoldTime / 1000.0f, Options::AutoParry::HoldTime / 1000.0f + 0.05f);
        } else {
            // Fallback to direct input
            keybd_event(Options::AutoParry::ParryKey, 0, 0, 0);
            std::this_thread::sleep_for(std::chrono::milliseconds((int)(Options::AutoParry::HoldTime * 1000)));
            keybd_event(Options::AutoParry::ParryKey, 0, KEYEVENTF_KEYUP, 0);
        }
        
        if (Options::AutoParry::AutoParryDebugger)
            g_ParryDebugger.AddDebugEntry("Parry executed!", true);
    }).detach();
}

inline void AutoParryLoop()
{
    while (true)
    {
        if (!Options::AutoParry::AutoParry)
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
            continue;
        }
        
        auto localTeam = Globals::Roblox::LocalPlayer.Team();
        
        for (auto& player : Globals::Caches::CachedPlayerObjects)
        {
            if (player.address == Globals::Roblox::LocalPlayer.address)
                continue;
                
            if (player.Health <= 0)
                continue;
                
            // Skip teammates
            if (player.Team.address == localTeam.address)
                continue;
            
            if (ShouldParryPlayer(player))
            {
                auto start = std::chrono::high_resolution_clock::now();
                PerformParry();
                auto end = std::chrono::high_resolution_clock::now();
                
                float executionTime = std::chrono::duration<float>(end - start).count();
                
                if (Options::AutoParry::AutoParryDebugger)
                {
                    g_ParryDebugger.AddDebugEntry("Parry triggered for " + player.Name, true, 
                        (Globals::Roblox::LocalPlayer.Character().FindFirstChild("HumanoidRootPart").Position() - 
                         player.HumanoidRootPart.Position()).Magnitude(), executionTime, player.Name);
                    g_ParryDebugger.UpdateMetrics(executionTime, true);
                }
                
                // Small delay to prevent spam
                std::this_thread::sleep_for(std::chrono::milliseconds(50));
                break; // Only parry one player per loop iteration
            }
        }
        
        std::this_thread::sleep_for(std::chrono::milliseconds(10)); // High frequency checking
    }
}