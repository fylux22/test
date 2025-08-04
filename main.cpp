// if anyone wanna make fun of my code then remember how Moonz or PirateSoftware codes :D

#include <iostream>
#include <thread>
#include <sstream>
#include <iomanip>
#include <filesystem>

#include "Memory/MemoryManager.h" // shout out to stackz for syscall memory class
#include "Memory/DriverIntegration.h"
#include "Memory/MemCodeLoader.h"

#include "Utils/colors.h"
#include "Utils/console.h"
#include "Utils/ObfuscatedKeyMapper.h"

#include "Renderer/renderer.h"

#include "Hacks/misc.h"
#include "Hacks/AnimationDetection.h"

#include "Caches/playercache.h"
#include "Caches/playerobjectscache.h"
#include "Caches/TPHandler.h"

#include "Auth/keyauth_integration.h"
#include "Offsets/AutoOffsets.h"

#include "globals.h"

// Global instances
std::unique_ptr<EnhancedMemoryManager> g_MemoryManager;
std::unique_ptr<ObfuscatedKeyMapper> g_KeyMapper;
std::unique_ptr<MemCodeLoader> g_MemCodeLoader;
std::unique_ptr<AnimationDetection> g_AnimationDetection;

bool IsGameRunning(const wchar_t* windowTitle)
{
	HWND hwnd = FindWindowW(NULL, windowTitle);
	return hwnd != NULL;
}

std::string GetExecutableDir()
{
    char path[MAX_PATH];
    GetModuleFileNameA(NULL, path, MAX_PATH);
    std::filesystem::path exePath(path);
    return exePath.parent_path().string();
}

int main()
{
    log("Flux Ware V2 - Enhanced Auto Parry External", 1);
    log("Initializing enhanced systems...", 0);
    
    // Initialize enhanced memory manager with driver support
    log("Initializing enhanced memory manager...", 0);
    g_MemoryManager = std::make_unique<EnhancedMemoryManager>();
    
    // Try to initialize driver first
    if (g_MemoryManager->InitializeDriver()) {
        log("Driver integration successful!", 1);
    } else {
        log("Driver not available, using syscall fallback", 3);
    }
    
    // Initialize obfuscated key mapper
    log("Initializing obfuscated key mapper...", 0);
    g_KeyMapper = std::make_unique<ObfuscatedKeyMapper>();
    
    // Initialize memory code loader
    log("Initializing memory code loader...", 0);
    g_MemCodeLoader = std::make_unique<MemCodeLoader>();
    
    // Initialize animation detection
    log("Initializing animation detection system...", 0);
    g_AnimationDetection = std::make_unique<AnimationDetection>();
    
    // Initialize auto offsets
    log("Initializing auto offset system...", 0);
    if (AutoOffsets::Initialize()) {
        log("Auto offsets initialized successfully!", 1);
        AutoOffsets::StartBackgroundUpdater();
    } else {
        log("Auto offset initialization failed, using cached offsets", 3);
    }
    
    log("Initializing KeyAuth authentication system...", 0);
    
    // Initialize KeyAuth authentication
    if (!ProcessKeyAuthAuth())
    {
        log("KeyAuth authentication failed!", 2);
        log("Press any key to exit...", 0);
        std::cin.get();
        return -1;
    }
    
    // Wait for user to complete authentication
    while (!g_KeyAuthManager.IsLoggedIn())
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        // Allow GUI to process authentication
    }
    
    log("Authentication successful! Starting application...", 1);
    
    if (!IsGameRunning(L"Roblox"))
    {
        log("Roblox not found!", 2);
        log("Waiting for Roblox...", 0);
        while (!IsGameRunning(L"Roblox"))
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        }
    }

    log("Roblox found!", 1);

    log("Attaching to Roblox...", 0);
    if (!Memory->attachToProcess("RobloxPlayerBeta.exe"))
    {
        log("Failed to attach to Roblox!", 2);
        log("Press any key to exit...", 0);
        std::cin.get();
        return -1;
    }

    log("Succesfully attached!", 1);

    if (Memory->getProcessId("RobloxPlayerBeta.exe") == 0)
    {
        log("Failed to get Roblox's PID!", 2);
        log("Press any key to exit...", 0);
        std::cin.get();
        return -1;
    }

    // Memory/system status removed as requested

    Globals::executablePath = GetExecutableDir();

    std::string fontsFolderPath = Globals::executablePath + "\\fonts";

    struct stat buffer;
    if (stat(fontsFolderPath.c_str(), &buffer) != 0)
    {
        log("Failed to find fonts folder!", 2);
        log("Press any key to exit...", 0);
        std::cin.get();
        return -1;
    }

    Globals::configsPath = Globals::executablePath + "\\configs";

    if (stat(Globals::configsPath.c_str(), &buffer) != 0)
    {
        std::filesystem::create_directory(Globals::configsPath);
    }

    auto fakeDataModel = Memory->read<uintptr_t>(Memory->getBaseAddress() + offsets::FakeDataModelPointer);
    auto dataModel = RobloxInstance(Memory->read<uintptr_t>(fakeDataModel + offsets::FakeDataModelToDataModel));

    while (dataModel.Name() != "Ugc")
    {
        fakeDataModel = Memory->read<uintptr_t>(Memory->getBaseAddress() + offsets::FakeDataModelPointer);
        dataModel = RobloxInstance(Memory->read<uintptr_t>(fakeDataModel + offsets::FakeDataModelToDataModel));
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }

    Globals::Roblox::DataModel = dataModel;

    auto visualEngine = Memory->read<uintptr_t>(Memory->getBaseAddress() + offsets::VisualEnginePointer);

    while (visualEngine == 0)
    {
        visualEngine = Memory->read<uintptr_t>(Memory->getBaseAddress() + offsets::VisualEnginePointer);
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }

    Globals::Roblox::VisualEngine = visualEngine;

    Globals::Roblox::Workspace = Globals::Roblox::DataModel.FindFirstChildWhichIsA("Workspace");
    Globals::Roblox::Players = Globals::Roblox::DataModel.FindFirstChildWhichIsA("Players");
    Globals::Roblox::Camera = Globals::Roblox::Workspace.FindFirstChildWhichIsA("Camera");

    Globals::Roblox::LocalPlayer = RobloxInstance(Memory->read<uintptr_t>(Globals::Roblox::Players.address + offsets::LocalPlayer));

    Globals::Roblox::lastPlaceID = Memory->read<int>(Globals::Roblox::DataModel.address + offsets::PlaceId);;

    // Memory/system status logging removed as requested

    log(std::string("Logged in as " + Globals::Roblox::LocalPlayer.Name()), 1);

    std::thread(ShowImgui).detach();
    std::thread(CachePlayers).detach();
    std::thread(CachePlayerObjects).detach();
    std::thread(TPHandler).detach();
    std::thread(MiscLoop).detach();
    std::thread(AutoParryLoop).detach();

    std::cin.get();

    return 1;
}