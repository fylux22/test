#pragma once
#include "globals.h"

namespace Options
{
	namespace Misc
	{
		inline bool Bypass;
		inline float Walkspeed = 16.f;
		inline float JumpPower = 50.f;
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
		inline bool Chams;
		inline bool BoxFilled;
		inline bool SkeletonAdvanced;

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
		inline float ChamsColor[4] = {1.0f, 0.0f, 0.0f, 0.5f};
		inline float ChamsVisibleColor[4] = {0.0f, 1.0f, 0.0f, 0.7f};
		inline float ChamsOpacity = 0.5f;
		inline float BoxOpacity = 0.2f;
		inline float SkeletonOpacity = 1.0f;
		inline bool ChamsThroughWalls = true;
		inline bool GlowEffect = false;
		inline float GlowColor[4] = {1.0f, 1.0f, 1.0f, 0.3f};
		inline float GlowIntensity = 1.0f;
	}
	namespace Aimbot
	{
		inline int AimbotKey = VK_RBUTTON;
		inline int AimingType;

		inline int ToggleType;

		inline bool Aimbot;
		inline bool TeamCheck;
		inline bool DownedCheck;
		inline bool StickyAim;
		inline float FOV;
		inline float Smoothness;
		inline bool ShowFOV;
		inline float Range = 100.f;

		inline float FOVColor[3];
		inline float FOVFillColor[4];
		
		inline int TargetBone = 0;
		
		inline RobloxPlayer CurrentTarget;
		inline bool Toggled;
	}
	namespace AutoParry
	{
		inline bool AutoParry = false;
		inline bool AutoParryDebugger = false;
		inline bool ShowDebugOverlay = true;
		inline bool LogDetections = true;
		inline bool ShowTimingAnalysis = true;
		inline bool ShowRangeIndicator = false;
		inline float ParryRange = 15.0f;
		inline float ParryDelay = 0.15f;
		inline float HoldTime = 0.1f;
		inline int ParryKey = VK_F;
		inline bool SmartTiming = true;
		inline float PredictionTime = 0.05f;
		inline bool OnlyParryWhenFacing = true;
		inline float FacingAngleTolerance = 45.0f;
		
		// Debug colors
		inline float DebugTextColor[3] = {1.0f, 1.0f, 1.0f};
		inline float DetectionColor[3] = {1.0f, 0.0f, 0.0f};
		inline float SuccessColor[3] = {0.0f, 1.0f, 0.0f};
		inline float RangeColor[3] = {1.0f, 1.0f, 0.0f};
	}
}