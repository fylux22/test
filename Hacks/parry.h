#pragma once

#include "../options.h"
#include "../globals.h"
#include "../Utils/structures.h"
#include <thread>
#include <vector>
#include <chrono>
#include <fstream>
#include <sstream>
#include <map>

namespace ParryDetection
{
    struct AttackInfo
    {
        RobloxInstance attacker;
        Vectors::Vector3 attackPosition;
        Vectors::Vector3 attackDirection;
        float attackRange;
        std::string attackType; // "M1", "M2", "Ability", "Animation"
        std::string animationName;
        std::chrono::steady_clock::time_point attackTime;
        bool isActive;
    };

    struct AnimationData
    {
        std::string name;
        std::string type; // "M1", "M2", "Ability", "Animation"
        float range;
        float duration;
        std::string category; // "Attack", "Ability", "Special"
        bool isAttack;
    };

    struct ParryConfig
    {
        bool enabled = false;
        float detectionRange = 10.0f;
        float parryWindow = 0.3f; // seconds
        bool detectM1 = true;
        bool detectM2 = true;
        bool detectAbilities = true;
        bool detectAnimations = true;
        std::vector<std::string> animationNames = {"Attack", "Swing", "Slash", "Stab", "Punch", "Kick"};
        bool autoParry = false;
        int parryKey = VK_F; // Default parry key
        bool visualFeedback = true;
        float parryColor[3] = {1.0f, 0.0f, 0.0f}; // Red
        bool logAttacks = false;
        std::string animationDataFile = "animations.txt"; // File to load animation data from
    };

    inline ParryConfig config;
    inline std::vector<AttackInfo> activeAttacks;
    inline std::chrono::steady_clock::time_point lastParryTime;
    inline bool parryCooldown = false;
    inline const float PARRY_COOLDOWN_DURATION = 0.5f; // seconds
    inline std::map<std::string, AnimationData> loadedAnimations;

    // Load animation data from file
    inline bool LoadAnimationData(const std::string& filename)
    {
        std::ifstream file(filename);
        if (!file.is_open())
        {
            std::cout << "[Parry] Could not open animation data file: " << filename << std::endl;
            return false;
        }

        loadedAnimations.clear();
        std::string line;
        int lineNumber = 0;

        while (std::getline(file, line))
        {
            lineNumber++;
            if (line.empty() || line[0] == '#') // Skip empty lines and comments
                continue;

            std::istringstream iss(line);
            std::string name, type, category;
            float range, duration;
            bool isAttack;

            if (iss >> name >> type >> range >> duration >> category >> isAttack)
            {
                AnimationData anim;
                anim.name = name;
                anim.type = type;
                anim.range = range;
                anim.duration = duration;
                anim.category = category;
                anim.isAttack = isAttack;
                
                loadedAnimations[name] = anim;
            }
            else
            {
                std::cout << "[Parry] Invalid animation data format at line " << lineNumber << ": " << line << std::endl;
            }
        }

        file.close();
        std::cout << "[Parry] Loaded " << loadedAnimations.size() << " animations from " << filename << std::endl;
        return true;
    }

    // Check if an animation is an attack animation
    inline bool IsAttackAnimation(const std::string& animName)
    {
        // Check loaded animation data first
        auto it = loadedAnimations.find(animName);
        if (it != loadedAnimations.end())
        {
            return it->second.isAttack;
        }

        // Fallback to default attack animation names
        std::vector<std::string> attackKeywords = {"Attack", "Swing", "Slash", "Stab", "Punch", "Kick", "Strike", "Hit"};
        for (const auto& keyword : attackKeywords)
        {
            if (animName.find(keyword) != std::string::npos)
                return true;
        }

        return false;
    }

    // Get animation data for a specific animation
    inline AnimationData GetAnimationData(const std::string& animName)
    {
        auto it = loadedAnimations.find(animName);
        if (it != loadedAnimations.end())
        {
            return it->second;
        }

        // Return default data if not found
        AnimationData defaultData;
        defaultData.name = animName;
        defaultData.type = "Animation";
        defaultData.range = 10.0f;
        defaultData.duration = 1.0f;
        defaultData.category = "Unknown";
        defaultData.isAttack = IsAttackAnimation(animName);
        
        return defaultData;
    }

    // Check if a player is attacking based on animation state
    inline bool IsPlayerAttacking(const RobloxInstance& player)
    {
        if (!player || !player.Character())
            return false;

        auto character = player.Character();
        auto humanoid = character.FindFirstChildWhichIsA("Humanoid");
        
        if (!humanoid)
            return false;

        // Check humanoid state for attacking
        int humanoidState = Memory->read<int>(humanoid.address + offsets::HumanoidState);
        
        // Common attacking states (may need adjustment based on game)
        if (humanoidState == 4 || humanoidState == 5 || humanoidState == 6) // Example states
            return true;

        // Check for animation tracks
        auto animator = character.FindFirstChildWhichIsA("HumanoidAnimator");
        if (animator)
        {
            // Check animation tracks for attack animations
            auto children = animator.GetChildren();
            for (const auto& child : children)
            {
                if (child.Class() == "AnimationTrack")
                {
                    std::string animName = child.Name();
                    
                    // Check if this is an attack animation
                    if (IsAttackAnimation(animName))
                    {
                        // Check if animation is playing
                        float timePosition = Memory->read<float>(child.address + 0x1C); // AnimationTrack time position
                        if (timePosition > 0.0f)
                            return true;
                    }
                }
            }
        }

        return false;
    }

    // Check if a player is using an ability
    inline bool IsPlayerUsingAbility(const RobloxInstance& player)
    {
        if (!player || !player.Character())
            return false;

        auto character = player.Character();
        
        // Check for ability tools/weapons
        auto children = character.GetChildren();
        for (const auto& child : children)
        {
            if (child.Class() == "Tool" || child.Class() == "HopperBin")
            {
                // Check if tool is being used
                bool enabled = Memory->read<bool>(child.address + 0x14A); // Tool enabled
                if (enabled)
                {
                    // Check for ability-specific animations or states
                    std::string toolName = child.Name();
                    if (toolName.find("Ability") != std::string::npos || 
                        toolName.find("Spell") != std::string::npos ||
                        toolName.find("Magic") != std::string::npos)
                    {
                        return true;
                    }
                }
            }
        }

        return false;
    }

    // Calculate distance between two positions
    inline float CalculateDistance(const Vectors::Vector3& pos1, const Vectors::Vector3& pos2)
    {
        return pos1.Distance(pos2);
    }

    // Check if an attack is within parry range
    inline bool IsAttackInRange(const AttackInfo& attack, const Vectors::Vector3& playerPos)
    {
        float distance = CalculateDistance(attack.attackPosition, playerPos);
        return distance <= config.detectionRange;
    }

    // Check if an attack is within parry window
    inline bool IsAttackInParryWindow(const AttackInfo& attack)
    {
        auto now = std::chrono::steady_clock::now();
        auto timeSinceAttack = std::chrono::duration_cast<std::chrono::milliseconds>(now - attack.attackTime).count() / 1000.0f;
        return timeSinceAttack <= config.parryWindow;
    }

    // Detect attacks from all players
    inline void DetectAttacks()
    {
        if (!config.enabled)
            return;

        auto localPlayer = Globals::Roblox::LocalPlayer;
        if (!localPlayer || !localPlayer.Character())
            return;

        auto localCharacter = localPlayer.Character();
        auto localHumanoid = localCharacter.FindFirstChildWhichIsA("Humanoid");
        if (!localHumanoid)
            return;

        Vectors::Vector3 localPos = localCharacter.Position();

        // Clear old attacks
        auto now = std::chrono::steady_clock::now();
        activeAttacks.erase(
            std::remove_if(activeAttacks.begin(), activeAttacks.end(),
                [&](const AttackInfo& attack) {
                    auto timeSinceAttack = std::chrono::duration_cast<std::chrono::milliseconds>(now - attack.attackTime).count() / 1000.0f;
                    return timeSinceAttack > config.parryWindow || !attack.isActive;
                }),
            activeAttacks.end()
        );

        // Check all cached players for attacks
        for (const auto& cachedPlayer : Globals::Caches::CachedPlayerObjects)
        {
            if (!cachedPlayer.Character() || cachedPlayer.Character().address == localCharacter.address)
                continue;

            // Team check (optional)
            if (Options::Parry::TeamCheck)
            {
                if (cachedPlayer.Team.address == localPlayer.Team().address)
                    continue;
            }

            auto character = cachedPlayer.Character();
            auto humanoid = character.FindFirstChildWhichIsA("Humanoid");
            
            if (!humanoid)
                continue;

            // Check if player is alive
            float health = Memory->read<float>(humanoid.address + offsets::Health);
            if (health <= 0)
                continue;

            Vectors::Vector3 attackerPos = character.Position();
            float distance = CalculateDistance(localPos, attackerPos);

            // Only check players within detection range
            if (distance > config.detectionRange * 2.0f) // Double range for detection
                continue;

            AttackInfo newAttack;
            newAttack.attacker = cachedPlayer.Character();
            newAttack.attackPosition = attackerPos;
            newAttack.attackTime = now;
            newAttack.isActive = true;

            // Determine attack direction (from attacker to local player)
            newAttack.attackDirection = (localPos - attackerPos).Normalize();

            // Detect M1 attacks
            if (config.detectM1 && IsPlayerAttacking(cachedPlayer.Character()))
            {
                newAttack.attackType = "M1";
                newAttack.attackRange = 5.0f; // Default M1 range
                newAttack.animationName = "M1_Attack";
                
                // Check if this attack is already tracked
                bool alreadyTracked = false;
                for (const auto& existingAttack : activeAttacks)
                {
                    if (existingAttack.attacker.address == newAttack.attacker.address && 
                        existingAttack.attackType == "M1")
                    {
                        alreadyTracked = true;
                        break;
                    }
                }

                if (!alreadyTracked)
                {
                    activeAttacks.push_back(newAttack);
                    if (config.logAttacks)
                    {
                        std::cout << "[Parry] M1 attack detected from " << cachedPlayer.Name << " at distance " << distance << std::endl;
                    }
                }
            }

            // Detect M2 attacks (secondary attacks)
            if (config.detectM2)
            {
                // Check for secondary attack animations or states
                auto animator = character.FindFirstChildWhichIsA("HumanoidAnimator");
                if (animator)
                {
                    auto children = animator.GetChildren();
                    for (const auto& child : children)
                    {
                        if (child.Class() == "AnimationTrack")
                        {
                            std::string animName = child.Name();
                            if (animName.find("M2") != std::string::npos || 
                                animName.find("Secondary") != std::string::npos ||
                                animName.find("Heavy") != std::string::npos)
                            {
                                newAttack.attackType = "M2";
                                newAttack.attackRange = 8.0f; // Default M2 range
                                newAttack.animationName = animName;
                                
                                bool alreadyTracked = false;
                                for (const auto& existingAttack : activeAttacks)
                                {
                                    if (existingAttack.attacker.address == newAttack.attacker.address && 
                                        existingAttack.attackType == "M2")
                                    {
                                        alreadyTracked = true;
                                        break;
                                    }
                                }

                                if (!alreadyTracked)
                                {
                                    activeAttacks.push_back(newAttack);
                                    if (config.logAttacks)
                                    {
                                        std::cout << "[Parry] M2 attack detected from " << cachedPlayer.Name << " at distance " << distance << std::endl;
                                    }
                                }
                                break;
                            }
                        }
                    }
                }
            }

            // Detect abilities
            if (config.detectAbilities && IsPlayerUsingAbility(cachedPlayer.Character()))
            {
                newAttack.attackType = "Ability";
                newAttack.attackRange = 15.0f; // Default ability range
                newAttack.animationName = "Ability_Cast";
                
                bool alreadyTracked = false;
                for (const auto& existingAttack : activeAttacks)
                {
                    if (existingAttack.attacker.address == newAttack.attacker.address && 
                        existingAttack.attackType == "Ability")
                    {
                        alreadyTracked = true;
                        break;
                    }
                }

                if (!alreadyTracked)
                {
                    activeAttacks.push_back(newAttack);
                    if (config.logAttacks)
                    {
                        std::cout << "[Parry] Ability attack detected from " << cachedPlayer.Name << " at distance " << distance << std::endl;
                    }
                }
            }

            // Detect custom animations using loaded animation data
            if (config.detectAnimations)
            {
                auto animator = character.FindFirstChildWhichIsA("HumanoidAnimator");
                if (animator)
                {
                    auto children = animator.GetChildren();
                    for (const auto& child : children)
                    {
                        if (child.Class() == "AnimationTrack")
                        {
                            std::string animName = child.Name();
                            float timePosition = Memory->read<float>(child.address + 0x1C);
                            
                            // Check if this is an attack animation
                            if (IsAttackAnimation(animName) && timePosition > 0.0f && timePosition < 0.5f)
                            {
                                AnimationData animData = GetAnimationData(animName);
                                
                                newAttack.attackType = animData.type;
                                newAttack.attackRange = animData.range;
                                newAttack.animationName = animName;
                                
                                bool alreadyTracked = false;
                                for (const auto& existingAttack : activeAttacks)
                                {
                                    if (existingAttack.attacker.address == newAttack.attacker.address && 
                                        existingAttack.attackType == animData.type &&
                                        existingAttack.animationName == animName)
                                    {
                                        alreadyTracked = true;
                                        break;
                                    }
                                }

                                if (!alreadyTracked)
                                {
                                    activeAttacks.push_back(newAttack);
                                    if (config.logAttacks)
                                    {
                                        std::cout << "[Parry] Animation attack detected from " << cachedPlayer.Name << " (" << animName << ") at distance " << distance << std::endl;
                                    }
                                }
                                break;
                            }
                        }
                    }
                }
            }
        }
    }

    // Check if parry should be triggered
    inline bool ShouldParry()
    {
        if (!config.enabled || parryCooldown)
            return false;

        auto localPlayer = Globals::Roblox::LocalPlayer;
        if (!localPlayer || !localPlayer.Character())
            return false;

        Vectors::Vector3 localPos = localPlayer.Character().Position();

        for (const auto& attack : activeAttacks)
        {
            if (IsAttackInRange(attack, localPos) && IsAttackInParryWindow(attack))
            {
                return true;
            }
        }

        return false;
    }

    // Execute parry action
    inline void ExecuteParry()
    {
        if (!ShouldParry())
            return;

        // Set parry cooldown
        lastParryTime = std::chrono::steady_clock::now();
        parryCooldown = true;

        // Simulate parry key press
        if (config.autoParry)
        {
            // Send parry key press
            INPUT input[2];
            ZeroMemory(input, sizeof(input));

            // Key down
            input[0].type = INPUT_KEYBOARD;
            input[0].ki.wVk = config.parryKey;
            input[0].ki.dwFlags = 0;

            // Key up
            input[1].type = INPUT_KEYBOARD;
            input[1].ki.wVk = config.parryKey;
            input[1].ki.dwFlags = KEYEVENTF_KEYUP;

            SendInput(2, input, sizeof(INPUT));

            if (config.logAttacks)
            {
                std::cout << "[Parry] Parry executed!" << std::endl;
            }
        }
    }

    // Update parry cooldown
    inline void UpdateParryCooldown()
    {
        if (parryCooldown)
        {
            auto now = std::chrono::steady_clock::now();
            auto timeSinceParry = std::chrono::duration_cast<std::chrono::milliseconds>(now - lastParryTime).count() / 1000.0f;
            
            if (timeSinceParry >= PARRY_COOLDOWN_DURATION)
            {
                parryCooldown = false;
            }
        }
    }

    // Initialize parry system
    inline void InitializeParrySystem()
    {
        // Load animation data if file exists
        LoadAnimationData(config.animationDataFile);
        
        // Update config from options
        config.enabled = Options::Parry::Enabled;
        config.detectionRange = Options::Parry::DetectionRange;
        config.parryWindow = Options::Parry::ParryWindow;
        config.detectM1 = Options::Parry::DetectM1;
        config.detectM2 = Options::Parry::DetectM2;
        config.detectAbilities = Options::Parry::DetectAbilities;
        config.detectAnimations = Options::Parry::DetectAnimations;
        config.autoParry = Options::Parry::AutoParry;
        config.parryKey = Options::Parry::ParryKey;
        config.visualFeedback = Options::Parry::VisualFeedback;
        config.logAttacks = Options::Parry::LogAttacks;
        
        // Copy color values
        config.parryColor[0] = Options::Parry::ParryColor[0];
        config.parryColor[1] = Options::Parry::ParryColor[1];
        config.parryColor[2] = Options::Parry::ParryColor[2];
    }

    // Main parry detection loop
    inline void ParryDetectionLoop()
    {
        InitializeParrySystem();
        
        while (true)
        {
            try
            {
                // Update config from options (in case they changed)
                config.enabled = Options::Parry::Enabled;
                config.detectionRange = Options::Parry::DetectionRange;
                config.parryWindow = Options::Parry::ParryWindow;
                config.autoParry = Options::Parry::AutoParry;
                
                DetectAttacks();
                UpdateParryCooldown();
                
                if (config.autoParry)
                {
                    ExecuteParry();
                }

                std::this_thread::sleep_for(std::chrono::milliseconds(16)); // ~60 FPS
            }
            catch (const std::exception& e)
            {
                std::cout << "[Parry] Error in parry detection loop: " << e.what() << std::endl;
                std::this_thread::sleep_for(std::chrono::milliseconds(100));
            }
        }
    }

    // Get active attacks for rendering
    inline const std::vector<AttackInfo>& GetActiveAttacks()
    {
        return activeAttacks;
    }

    // Manual parry trigger (for key binding)
    inline void TriggerParry()
    {
        if (!parryCooldown && ShouldParry())
        {
            ExecuteParry();
        }
    }

    // Reload animation data
    inline void ReloadAnimationData()
    {
        LoadAnimationData(config.animationDataFile);
    }
}