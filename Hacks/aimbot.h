#pragma once

#include <algorithm>
#include <cmath>
#include <chrono>
#include <unordered_set>
#include <vector>
#include <string>

#include "../renderer/W2S.h"
#include "../renderer/imgui/imgui.h"
#include "../options.h"
#include "../Renderer/imgui/KeyBind.h"
#include "animations.h"

inline float GetCurrentTime() {
    static auto start = std::chrono::high_resolution_clock::now();
    auto now = std::chrono::high_resolution_clock::now();
    return std::chrono::duration<float>(now - start).count();
}

inline std::vector<RobloxInstance> GetPlayingAnimationTracks(const RobloxPlayer& player) {
    std::vector<RobloxInstance> animationTracks;
    
    if (!player.Character.address || !player.Humanoid.address) {
        return animationTracks;
    }
    
    // Try to find the Animator object
    auto animator = player.Character.FindFirstChildWhichIsA("Animator");
    if (!animator.address) {
        animator = player.Humanoid.FindFirstChild("Animator");
    }
    
    if (!animator.address) {
        return animationTracks;
    }
    
    // Get all children of the animator (which should be AnimationTracks)
    auto children = animator.GetChildren();
    for (const auto& child : children) {
        // Check if this is an AnimationTrack and if it's playing
        if (child.ClassName() == "AnimationTrack") {
            // You would need to check if the track is playing here
            // For now, we'll add all tracks as potential candidates
            animationTracks.push_back(child);
        }
    }
    
    return animationTracks;
}

inline std::string GetAnimationId(const RobloxInstance& animationTrack) {
    if (!animationTrack.address) return "";
    
    // Try to get the Animation object from the track
    auto animation = animationTrack.FindFirstChild("Animation");
    if (!animation.address) return "";
    
    // Get the AnimationId
    auto animationId = Memory->read<std::string>(animation.address + offsets::AnimationId);
    return animationId;
}

inline bool IsAttackAnimation(const std::string& animationId) {
    return AnimationDatabase::IsAttackAnimation(animationId);
}

inline RobloxPlayer GetClosestThreat() {
    RobloxPlayer closestThreat;
    float closestDistance = FLT_MAX;
    
    auto localCharacter = Globals::Roblox::LocalPlayer.Character();
    auto localHRP = localCharacter.FindFirstChild("HumanoidRootPart");
    
    if (!localHRP.address) return closestThreat;
    
    auto localPosition = localHRP.Position();
    
    for (auto& player : Globals::Caches::CachedPlayerObjects) {
        if (player.address == Globals::Roblox::LocalPlayer.address) continue;
        if (player.Health <= 0) continue;
        
        auto playerHRP = player.HumanoidRootPart;
        if (!playerHRP.address) continue;
        
        auto playerPosition = playerHRP.Position();
        auto distance = (localPosition - playerPosition).Magnitude();
        
        if (distance > Options::AutoParry::DetectionRange) continue;
        
        // Check if player is performing an attack animation
        auto animationTracks = GetPlayingAnimationTracks(player);
        bool hasAttackAnimation = false;
        
        for (const auto& track : animationTracks) {
            std::string animId = GetAnimationId(track);
            if (IsAttackAnimation(animId)) {
                hasAttackAnimation = true;
                Options::AutoParry::LastDetectedAnimation = animId;
                
                // Additional check: prioritize ability attacks over M1s
                if (AnimationDatabase::IsAbilityAttack(animId)) {
                    break; // Ability attacks have higher priority
                }
            }
        }
        
        if (hasAttackAnimation && distance < closestDistance) {
            closestDistance = distance;
            closestThreat = player;
        }
    }
    
    return closestThreat;
}

inline void ExecuteParry() {
    if (!Options::AutoParry::Enabled) return;
    
    float currentTime = GetCurrentTime();
    
    // Check cooldown
    if (currentTime - Options::AutoParry::LastParryTime < 0.5f) return; // 500ms cooldown
    
    // Simulate key press
    keybd_event(Options::AutoParry::ParryKey, 0, 0, 0);
    std::this_thread::sleep_for(std::chrono::milliseconds(static_cast<int>(Options::AutoParry::HoldTime * 1000)));
    keybd_event(Options::AutoParry::ParryKey, 0, KEYEVENTF_KEYUP, 0);
    
    Options::AutoParry::LastParryTime = currentTime;
    Options::AutoParry::IsParrying = true;
    
    // Reset parrying status after hold time
    std::thread([currentTime]() {
        std::this_thread::sleep_for(std::chrono::milliseconds(static_cast<int>(Options::AutoParry::HoldTime * 1000 + 100)));
        Options::AutoParry::IsParrying = false;
    }).detach();
}

inline void RunAutoParry(ImDrawList* drawList) {
    if (!Options::AutoParry::Enabled) return;
    
    float currentTime = GetCurrentTime();
    
    // Find closest threatening player
    auto threat = GetClosestThreat();
    Options::AutoParry::TargetPlayer = threat;
    
    if (threat.address) {
        // Add range delay before parrying
        if (currentTime - Options::AutoParry::LastParryTime > Options::AutoParry::RangeDelay) {
            ExecuteParry();
        }
        
        // Visual feedback - draw warning indicator
        if (Options::AutoParry::ShowStatus) {
            auto displaySize = ImGui::GetIO().DisplaySize;
            std::string warningText = "THREAT DETECTED: " + threat.Name;
            
            ImVec2 textSize = ImGui::CalcTextSize(warningText.c_str());
            ImVec2 pos = ImVec2((displaySize.x - textSize.x) / 2, 100);
            
            // Background
            drawList->AddRectFilled(
                ImVec2(pos.x - 10, pos.y - 5),
                ImVec2(pos.x + textSize.x + 10, pos.y + textSize.y + 5),
                IM_COL32(255, 0, 0, 100)
            );
            
            // Text
            drawList->AddText(pos, IM_COL32(255, 255, 255, 255), warningText.c_str());
        }
    }
    
    // Status indicator
    if (Options::AutoParry::ShowStatus && Options::AutoParry::IsParrying) {
        auto displaySize = ImGui::GetIO().DisplaySize;
        std::string statusText = "PARRYING...";
        
        ImVec2 textSize = ImGui::CalcTextSize(statusText.c_str());
        ImVec2 pos = ImVec2((displaySize.x - textSize.x) / 2, 130);
        
        drawList->AddText(pos, IM_COL32(0, 255, 0, 255), statusText.c_str());
    }
}



