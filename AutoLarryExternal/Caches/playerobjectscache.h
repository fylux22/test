#pragma once
#include <thread>

#include "../globals.h"

inline std::string deobf_bzTyTL() {
    const unsigned char data[] = {0xf4, 0xcf, 0xc1, 0xce, 0xd2, 0x86, 0xea, 0xc3, 0xc1};
    const int key = 166;
    std::string result;
    for (int i = 0; i < 9; i++) {
        result += static_cast<char>(data[i] ^ key);
    }
    return result;
}

inline std::string deobf_dXLgNm() {
    const unsigned char data[] = {0x1c, 0x27, 0x29, 0x26, 0x3a, 0x6e, 0x0f, 0x3c, 0x23};
    const int key = 78;
    std::string result;
    for (int i = 0; i < 9; i++) {
        result += static_cast<char>(data[i] ^ key);
    }
    return result;
}

inline std::string deobf_aWtLQv() {
    const unsigned char data[] = {0xc0, 0xe9, 0xea, 0xf8, 0xac, 0xc0, 0xe9, 0xeb};
    const int key = 140;
    std::string result;
    for (int i = 0; i < 8; i++) {
        result += static_cast<char>(data[i] ^ key);
    }
    return result;
}

inline std::string deobf_sjkMdT() {
    const unsigned char data[] = {0xc3, 0xea, 0xe9, 0xfb, 0xaf, 0xce, 0xfd, 0xe2};
    const int key = 143;
    std::string result;
    for (int i = 0; i < 8; i++) {
        result += static_cast<char>(data[i] ^ key);
    }
    return result;
}

inline void CachePlayerObjects()
{
	std::vector<RobloxPlayer> tempList;

	while (true)
	{
		tempList.clear();

		if (Globals::Caches::CachedPlayers.empty())
			continue;

		for (auto& player : Globals::Caches::CachedPlayers)
		{
			RobloxPlayer p;

			if (!player || player.address == 0)
				continue;

			p.address = player.address;

			p.Name = player.Name();

			p.Team = player.Team();

			p.Character = player.Character();
			p.Humanoid = p.Character.FindFirstChildWhichIsA("Humanoid");

			p.Health = player.Health();
			p.MaxHealth = player.MaxHealth();

			p.RigType = p.Humanoid.RigType();

			p.Head = p.Character.FindFirstChild("Head");
			p.HumanoidRootPart = p.Character.FindFirstChild("HumanoidRootPart");

			switch (p.RigType)
			{
			case 0: // R6
				p.Left_Arm = p.Character.FindFirstChild(deobf_sjkMdT());
				p.Left_Leg = p.Character.FindFirstChild(deobf_aWtLQv());

				p.Right_Arm = p.Character.FindFirstChild(deobf_dXLgNm());
				p.Right_Leg = p.Character.FindFirstChild(deobf_bzTyTL());

				p.Torso = p.Character.FindFirstChild("Torso");

				break;
			case 1: // R15
				p.Upper_Torso = p.Character.FindFirstChild("UpperTorso");
				p.Lower_Torso = p.Character.FindFirstChild("LowerTorso");

				p.Right_Upper_Arm = p.Character.FindFirstChild("RightUpperArm");
				p.Right_Lower_Arm = p.Character.FindFirstChild("RightLowerArm");
				p.Right_Hand = p.Character.FindFirstChild("RightHand");

				p.Left_Upper_Arm = p.Character.FindFirstChild("LeftUpperArm");
				p.Left_Lower_Arm = p.Character.FindFirstChild("LeftLowerArm");
				p.Left_Hand = p.Character.FindFirstChild("LeftHand");

				p.Right_Upper_Leg = p.Character.FindFirstChild("RightUpperLeg");
				p.Right_Lower_Leg = p.Character.FindFirstChild("RightLowerLeg");
				p.Right_Foot = p.Character.FindFirstChild("RightFoot");

				p.Left_Upper_Leg = p.Character.FindFirstChild("LeftUpperLeg");
				p.Left_Lower_Leg = p.Character.FindFirstChild("LeftLowerLeg");
				p.Left_Foot = p.Character.FindFirstChild("LeftFoot");

				break;
			default:
				break;
			}

			tempList.push_back(p);
		}

		Globals::Caches::CachedPlayerObjects.clear();
		Globals::Caches::CachedPlayerObjects = tempList;

		std::this_thread::sleep_for(std::chrono::milliseconds(500));
	}
}