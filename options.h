#pragma once
#include "globals.h"

namespace Options
{
	namespace Misc
	{
		inline bool Bypass;
		inline float FOV = 70.f;
	}
	namespace ESP
	{
		inline bool TeamCheck;
		inline bool Box;
		inline bool Tracers;
		inline int TracersStart;
		inline bool Skeleton;
		inline bool Name;
		inline bool Distance;
		inline bool Health;
		inline bool ESP3D;
		inline bool HeadCircle;
		inline bool CornerESP;

		inline float Color[3];
		inline float BoxColor[3];
		inline float CornerColor[3];
		inline float BoxFillColor[4] = {1.0f, 1.0f, 1.0f, 0.2f};
		inline float SkeletonColor[3];
		inline float DistanceColor[3];
		inline float TracerColor[3];
		inline float TracerThickness = 1.0f;
		inline bool RemoveBorders = false;
		inline float ESP3DColor[3];
		inline float HeadCircleColor[3];
		inline float HeadCircleMaxScale = 2.5f;
	}
	namespace AutoParry
	{
		inline bool Enabled = false;
		inline float RangeDelay = 0.1f;  // Range delay time in seconds
		inline float HoldTime = 0.3f;    // Hold time in seconds
		inline int ParryKey = VK_SPACE;  // Default parry key (Space)
		inline bool ShowStatus = true;   // Show parry status in GUI
		inline float DetectionRange = 15.0f; // Detection range in studs
		
		// Internal state
		inline bool IsParrying = false;
		inline float LastParryTime = 0.0f;
		inline std::string LastDetectedAnimation = "";
		inline RobloxPlayer TargetPlayer;
	}
}