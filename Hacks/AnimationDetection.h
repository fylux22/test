#pragma once
#include "../SDK/SDK.h"
#include "../globals.h"
#include "../options.h"
#include "../xorstr.hpp"
#include <unordered_map>
#include <vector>
#include <string>
#include <chrono>

// Animation detection system for auto parry
class AnimationDetection {
private:
    // Animation hashes for common attack animations
    struct AnimationData {
        std::string name;
        uint64_t hash;
        float parryTiming; // Optimal parry timing in seconds
        float duration;    // Animation duration
        bool isAttack;     // Whether this is an attack animation
        float priority;    // Priority for multiple simultaneous animations
    };
    
    // Precomputed animation hashes (these would be from dumped animations)
    std::unordered_map<uint64_t, AnimationData> knownAnimations = {
        // Sword animations
        {0x1A2B3C4D5E6F7890, {xorstr_("SwordSlash1"), 0x1A2B3C4D5E6F7890, 0.15f, 0.8f, true, 1.0f}},
        {0x2B3C4D5E6F789012, {xorstr_("SwordSlash2"), 0x2B3C4D5E6F789012, 0.12f, 0.9f, true, 1.0f}},
        {0x3C4D5E6F78901234, {xorstr_("SwordThrust"), 0x3C4D5E6F78901234, 0.10f, 0.6f, true, 1.2f}},
        {0x4D5E6F7890123456, {xorstr_("SwordCombo1"), 0x4D5E6F7890123456, 0.08f, 1.2f, true, 0.8f}},
        
        // Axe animations
        {0x5E6F789012345678, {xorstr_("AxeSwing"), 0x5E6F789012345678, 0.20f, 1.0f, true, 1.1f}},
        {0x6F78901234567890, {xorstr_("AxeOverhead"), 0x6F78901234567890, 0.25f, 1.3f, true, 1.3f}},
        
        // Spear animations
        {0x789012345678901A, {xorstr_("SpearThrust"), 0x789012345678901A, 0.12f, 0.7f, true, 1.0f}},
        {0x89012345678901AB, {xorstr_("SpearSweep"), 0x89012345678901AB, 0.18f, 1.1f, true, 0.9f}},
        
        // Dagger animations
        {0x9012345678901ABC, {xorstr_("DaggerStab"), 0x9012345678901ABC, 0.08f, 0.4f, true, 1.4f}},
        {0xA12345678901ABCD, {xorstr_("DaggerSlash"), 0xA12345678901ABCD, 0.10f, 0.5f, true, 1.2f}},
        
        // Special/Magic animations
        {0xB2345678901ABCDE, {xorstr_("MagicCast"), 0xB2345678901ABCDE, 0.30f, 2.0f, true, 0.7f}},
        {0xC345678901ABCDEF, {xorstr_("SpecialAttack"), 0xC345678901ABCDEF, 0.15f, 1.5f, true, 1.5f}},
        
        // Defensive animations (for reference)
        {0xD45678901ABCDEF0, {xorstr_("Block"), 0xD45678901ABCDEF0, 0.0f, 0.3f, false, 0.0f}},
        {0xE5678901ABCDEF01, {xorstr_("Parry"), 0xE5678901ABCDEF01, 0.0f, 0.4f, false, 0.0f}},
    };
    
    // Currently detected animations per player
    struct PlayerAnimationState {
        uint64_t currentAnimationHash = 0;
        std::string currentAnimationName;
        std::chrono::high_resolution_clock::time_point animationStartTime;
        float animationProgress = 0.0f;
        bool isAttacking = false;
        float parryWindow = 0.0f;
        float priority = 0.0f;
    };
    
    std::unordered_map<uintptr_t, PlayerAnimationState> playerStates;
    
    // Animation hash calculation (simplified)
    uint64_t CalculateAnimationHash(const std::string& animationId) {
        uint64_t hash = 0xCBF29CE484222325; // FNV-1a basis
        for (char c : animationId) {
            hash ^= static_cast<uint64_t>(c);
            hash *= 0x100000001B3; // FNV-1a prime
        }
        return hash;
    }
    
    // Get animation progress (0.0 to 1.0)
    float GetAnimationProgress(const RobloxPlayer& player) {
        try {
            auto character = player.Character;
            if (character.address == 0) return 0.0f;
            
            auto humanoid = character.FindFirstChild("Humanoid");
            if (humanoid.address == 0) return 0.0f;
            
            auto animator = humanoid.FindFirstChild("Animator");
            if (animator.address == 0) return 0.0f;
            
            // This would need to be implemented based on Roblox's animation system
            // For now, we'll use a time-based estimation
            auto& state = playerStates[player.address];
            if (state.currentAnimationHash != 0) {
                auto now = std::chrono::high_resolution_clock::now();
                auto elapsed = std::chrono::duration<float>(now - state.animationStartTime).count();
                
                auto it = knownAnimations.find(state.currentAnimationHash);
                if (it != knownAnimations.end()) {
                    return std::min(1.0f, elapsed / it->second.duration);
                }
            }
            
            return 0.0f;
        }
        catch (...) {
            return 0.0f;
        }
    }
    
public:
    // Update animation detection for a player
    void UpdatePlayerAnimation(const RobloxPlayer& player) {
        try {
            auto character = player.Character;
            if (character.address == 0) return;
            
            auto humanoid = character.FindFirstChild("Humanoid");
            if (humanoid.address == 0) return;
            
            // Get current animation (this would need proper implementation)
            // For now, we'll simulate based on equipped tools and player state
            auto tool = character.FindFirstChildOfClass("Tool");
            if (tool.address == 0) {
                // No tool equipped, clear animation state
                playerStates[player.address] = PlayerAnimationState{};
                return;
            }
            
            // Simulate animation detection based on tool name and player movement
            std::string toolName = tool.Name();
            auto& state = playerStates[player.address];
            
            // Check if player is likely attacking (this is simplified)
            auto velocity = player.HumanoidRootPart.Velocity();
            bool isMovingFast = velocity.Magnitude() > 5.0f;
            
            // Simulate animation hash based on tool type
            uint64_t newAnimationHash = 0;
            if (toolName.find("Sword") != std::string::npos) {
                newAnimationHash = 0x1A2B3C4D5E6F7890; // SwordSlash1
            } else if (toolName.find("Axe") != std::string::npos) {
                newAnimationHash = 0x5E6F789012345678; // AxeSwing
            } else if (toolName.find("Spear") != std::string::npos) {
                newAnimationHash = 0x789012345678901A; // SpearThrust
            } else if (toolName.find("Dagger") != std::string::npos) {
                newAnimationHash = 0x9012345678901ABC; // DaggerStab
            }
            
            // Update animation state if changed
            if (newAnimationHash != state.currentAnimationHash && newAnimationHash != 0) {
                auto it = knownAnimations.find(newAnimationHash);
                if (it != knownAnimations.end()) {
                    state.currentAnimationHash = newAnimationHash;
                    state.currentAnimationName = it->second.name;
                    state.animationStartTime = std::chrono::high_resolution_clock::now();
                    state.isAttacking = it->second.isAttack;
                    state.parryWindow = it->second.parryTiming;
                    state.priority = it->second.priority;
                }
            }
            
            // Update animation progress
            state.animationProgress = GetAnimationProgress(player);
            
        } catch (...) {
            // Clear state on error
            playerStates[player.address] = PlayerAnimationState{};
        }
    }
    
    // Check if player is in attack animation
    bool IsPlayerAttacking(const RobloxPlayer& player) {
        auto it = playerStates.find(player.address);
        if (it == playerStates.end()) return false;
        
        return it->second.isAttacking && it->second.animationProgress < 0.8f;
    }
    
    // Get optimal parry timing for player
    float GetParryTiming(const RobloxPlayer& player) {
        auto it = playerStates.find(player.address);
        if (it == playerStates.end()) return 0.15f; // Default timing
        
        return it->second.parryWindow;
    }
    
    // Get animation priority (higher = more dangerous)
    float GetAnimationPriority(const RobloxPlayer& player) {
        auto it = playerStates.find(player.address);
        if (it == playerStates.end()) return 0.0f;
        
        return it->second.priority;
    }
    
    // Get current animation name
    std::string GetCurrentAnimationName(const RobloxPlayer& player) {
        auto it = playerStates.find(player.address);
        if (it == playerStates.end()) return xorstr_("None");
        
        return it->second.currentAnimationName;
    }
    
    // Get animation progress (0.0 to 1.0)
    float GetAnimationProgress(const RobloxPlayer& player) {
        auto it = playerStates.find(player.address);
        if (it == playerStates.end()) return 0.0f;
        
        return it->second.animationProgress;
    }
    
    // Check if animation is in parry window
    bool IsInParryWindow(const RobloxPlayer& player) {
        auto it = playerStates.find(player.address);
        if (it == playerStates.end()) return false;
        
        if (!it->second.isAttacking) return false;
        
        float progress = it->second.animationProgress;
        float parryWindow = it->second.parryWindow;
        
        // Parry window is typically before the damage frame
        return progress >= (parryWindow - 0.05f) && progress <= (parryWindow + 0.05f);
    }
    
    // Add custom animation hash (for user-defined animations)
    void AddCustomAnimation(uint64_t hash, const std::string& name, float parryTiming, float duration, bool isAttack, float priority = 1.0f) {
        knownAnimations[hash] = {name, hash, parryTiming, duration, isAttack, priority};
    }
    
    // Clear player state
    void ClearPlayerState(uintptr_t playerAddress) {
        playerStates.erase(playerAddress);
    }
    
    // Get all attacking players sorted by priority
    std::vector<std::pair<const RobloxPlayer*, float>> GetAttackingPlayersByPriority(const std::vector<RobloxPlayer>& players) {
        std::vector<std::pair<const RobloxPlayer*, float>> attacking;
        
        for (const auto& player : players) {
            if (IsPlayerAttacking(player)) {
                float priority = GetAnimationPriority(player);
                attacking.emplace_back(&player, priority);
            }
        }
        
        // Sort by priority (highest first)
        std::sort(attacking.begin(), attacking.end(), 
                  [](const auto& a, const auto& b) { return a.second > b.second; });
        
        return attacking;
    }
};

// Global animation detection instance
extern std::unique_ptr<AnimationDetection> g_AnimationDetection;