#pragma once

#include "../options.h"
#include "../globals.h"

#include <thread>

inline void MiscLoop()
{
	static auto character = Globals::Roblox::LocalPlayer.Character();
	static auto humanoid = character.FindFirstChildWhichIsA("Humanoid");
	static auto lastParryTime = std::chrono::steady_clock::now();

	while (true)
	{
		character = Globals::Roblox::LocalPlayer.Character();
		humanoid = character.FindFirstChildWhichIsA("Humanoid");

		humanoid.SetWalkspeed(Options::Misc::Walkspeed);
		humanoid.SetJumpPower(Options::Misc::JumpPower);
		Globals::Roblox::Camera.SetFOV(Options::Misc::FOV);

		// Auto Parry Logic
		if (Options::AutoParry::Enabled)
		{
			auto currentTime = std::chrono::steady_clock::now();
			auto timeSinceLastParry = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - lastParryTime).count() / 1000.0f;
			
			// Check if enough time has passed since last parry
			if (timeSinceLastParry >= Options::AutoParry::DelayAmount)
			{
				// Here you would implement the actual parry detection logic
				// For now, this is a placeholder that shows the auto parry is working
				// You would typically:
				// 1. Scan for incoming projectiles/attacks within ParryRange
				// 2. Calculate timing based on projectile speed and distance
				// 3. Execute parry action (usually pressing a key like 'F' or 'Q')
				// 4. Hold the parry for ParryHoldTime duration
				
				// Placeholder: Simulate parry detection every few seconds
				if (timeSinceLastParry >= 3.0f) // Simulate detection every 3 seconds
				{
					// Simulate parry action (this would be replaced with actual game input)
					// SendInput or similar to press parry key
					lastParryTime = currentTime;
				}
			}
		}

		std::this_thread::sleep_for(std::chrono::milliseconds(500));
	}
}