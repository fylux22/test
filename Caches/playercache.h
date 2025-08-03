#pragma once
#include "../globals.h"

#include <thread>
#include <vector>


inline void CachePlayers()
{
	std::vector<RobloxInstance> tempList;

	while (true)
	{
		tempList.clear();

		auto children = Globals::Roblox::Players.GetChildren();
		if (children.empty())
			continue;

		for (auto& player : Globals::Roblox::Players.GetChildren())
		{
			tempList.push_back(player);
		}

		{
			std::lock_guard<std::mutex> lock(Globals::Caches::PlayerCacheMutex);
			Globals::Caches::CachedPlayers.clear();
			Globals::Caches::CachedPlayers = tempList;
		}

		std::this_thread::sleep_for(std::chrono::milliseconds(5000));

	}
}

