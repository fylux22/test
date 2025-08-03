#pragma once
#include <string>
#include <windows.h>
#include <winhttp.h>
#include <iostream>
#include <sstream>
#include <tlhelp32.h>
#include <psapi.h>
#include <filesystem>
#include <vector>
#include <unordered_set>

namespace offsets {

    // Static offsets that CANNOT be fetched from the API
    inline constexpr uintptr_t RenderToFakeDataModel = 0x128;
    inline constexpr uintptr_t CFrame = 0x128;
    inline constexpr uintptr_t Anchored = 0x309; // Note: This is a mask/flag, not a direct offset
    inline constexpr uintptr_t CanCollide = 0x309; // Note: This is a mask/flag, not a direct offset

    // Dynamic offsets that CAN be fetched from the API
    inline uintptr_t Adornee;
    inline uintptr_t AnchoredMask;
    inline uintptr_t AnimationId;
    inline uintptr_t AttributeList;
    inline uintptr_t AttributeToNext;
    inline uintptr_t AttributeToValue;
    inline uintptr_t AutoJumpEnabled;
    inline uintptr_t BeamBrightness;
    inline uintptr_t BeamColor;
    inline uintptr_t BeamLightEmission;
    inline uintptr_t BeamLightInfuence;
    inline uintptr_t Camera;
    inline uintptr_t CameraMaxZoomDistance;
    inline uintptr_t CameraMinZoomDistance;
    inline uintptr_t CameraMode;
    inline uintptr_t CameraPos;
    inline uintptr_t CameraRotation;
    inline uintptr_t CameraSubject;
    inline uintptr_t CameraType;
    inline uintptr_t CanCollideMask;
    inline uintptr_t CanTouchMask;
    inline uintptr_t CharacterAppearanceId;
    inline uintptr_t Children;
    inline uintptr_t ChildrenEnd;
    inline uintptr_t ClassDescriptor;
    inline uintptr_t ClassDescriptorToClassName;
    inline uintptr_t ClickDetectorMaxActivationDistance;
    inline uintptr_t ClockTime;
    inline uintptr_t CreatorId;
    inline uintptr_t DataModelDeleterPointer;
    inline uintptr_t DataModelPrimitiveCount;
    inline uintptr_t DataModelToRenderView1;
    inline uintptr_t DataModelToRenderView2;
    inline uintptr_t DataModelToRenderView3;
    inline uintptr_t DecalTexture;
    inline uintptr_t Deleter;
    inline uintptr_t DeleterBack;
    inline uintptr_t Dimensions;
    inline uintptr_t DisplayName;
    inline uintptr_t EvaluateStateMachine;
    inline uintptr_t FOV;
    inline uintptr_t FakeDataModelPointer;
    inline uintptr_t FakeDataModelToDataModel;
    inline uintptr_t FogColor;
    inline uintptr_t FogEnd;
    inline uintptr_t FogStart;
    inline uintptr_t ForceNewAFKDuration;
    inline uintptr_t FramePositionOffsetX;
    inline uintptr_t FramePositionOffsetY;
    inline uintptr_t FramePositionX;
    inline uintptr_t FramePositionY;
    inline uintptr_t FrameRotation;
    inline uintptr_t FrameSizeX;
    inline uintptr_t FrameSizeY;
    inline uintptr_t GameId;
    inline uintptr_t GameLoaded;
    inline uintptr_t Gravity;
    inline uintptr_t Health;
    inline uintptr_t HealthDisplayDistance;
    inline uintptr_t HipHeight;
    inline uintptr_t HumanoidDisplayName;
    inline uintptr_t HumanoidState;
    inline uintptr_t HumanoidStateId;
    inline uintptr_t InputObject;
    inline uintptr_t InsetMaxX;
    inline uintptr_t InsetMaxY;
    inline uintptr_t InsetMinX;
    inline uintptr_t InsetMinY;
    inline uintptr_t InstanceCapabilities;
    inline uintptr_t JobEnd;
    inline uintptr_t JobId;
    inline uintptr_t JobStart;
    inline uintptr_t Job_Name;
    inline uintptr_t JobsPointer;
    inline uintptr_t JumpPower;
    inline uintptr_t LocalPlayer;
    inline uintptr_t LocalScriptByteCode;
    inline uintptr_t LocalScriptBytecodePointer;
    inline uintptr_t LocalScriptHash;
    inline uintptr_t MaterialType;
    inline uintptr_t MaxHealth;
    inline uintptr_t MaxSlopeAngle;
    inline uintptr_t MeshPartColor3;
    inline uintptr_t ModelInstance;
    inline uintptr_t ModuleScriptByteCode;
    inline uintptr_t ModuleScriptBytecodePointer;
    inline uintptr_t ModuleScriptHash;
    inline uintptr_t MoonTextureId;
    inline uintptr_t MousePosition;
    inline uintptr_t MouseSensitivity;
    inline uintptr_t MoveDirection;
    inline uintptr_t Name;
    inline uintptr_t NameDisplayDistance;
    inline uintptr_t NameSize;
    inline uintptr_t OnDemandInstance;
    inline uintptr_t OutdoorAmbient;
    inline uintptr_t Parent;
    inline uintptr_t PartSize;
    inline uintptr_t Ping;
    inline uintptr_t PlaceId;
    inline uintptr_t PlayerConfigurerPointer;
    inline uintptr_t PlayerMouse;
    inline uintptr_t Position;
    inline uintptr_t Primitive;
    inline uintptr_t PrimitiveGravity;
    inline uintptr_t PrimitiveValidateValue;
    inline uintptr_t PrimitivesPointer1;
    inline uintptr_t PrimitivesPointer2;
    inline uintptr_t ProximityPromptActionText;
    inline uintptr_t ProximityPromptEnabled;
    inline uintptr_t ProximityPromptGamepadKeyCode;
    inline uintptr_t ProximityPromptHoldDuraction;
    inline uintptr_t ProximityPromptMaxActivationDistance;
    inline uintptr_t ProximityPromptMaxObjectText;
    inline uintptr_t RenderJobToDataModel;
    inline uintptr_t RenderJobToFakeDataModel;
    inline uintptr_t RenderJobToRenderView;
    inline uintptr_t RequireBypass;
    inline uintptr_t RigType;
    inline uintptr_t Rotation;
    inline uintptr_t RunContext;
    inline uintptr_t ScriptContext;
    inline uintptr_t Sit;
    inline uintptr_t SkyboxBk;
    inline uintptr_t SkyboxDn;
    inline uintptr_t SkyboxFt;
    inline uintptr_t SkyboxLf;
    inline uintptr_t SkyboxRt;
    inline uintptr_t SkyboxUp;
    inline uintptr_t SoundId;
    inline uintptr_t StarCount;
    inline uintptr_t StringLength;
    inline uintptr_t SunTextureId;
    inline uintptr_t TagList;
    inline uintptr_t TaskSchedulerMaxFPS;
    inline uintptr_t TaskSchedulerPointer;
    inline uintptr_t Team;
    inline uintptr_t TeamColor;
    inline uintptr_t Tool_Grip_Position;
    inline uintptr_t Transparency;
    inline uintptr_t UserId;
    inline uintptr_t Value;
    inline uintptr_t Velocity;
    inline uintptr_t ViewportSize;
    inline uintptr_t VisualEngine;
    inline uintptr_t VisualEnginePointer;
    inline uintptr_t VisualEngineToDataModel1;
    inline uintptr_t VisualEngineToDataModel2;
    inline uintptr_t WalkSpeed;
    inline uintptr_t WalkSpeedCheck;
    inline uintptr_t WhitelistedThreads;
    inline uintptr_t Workspace;
    inline uintptr_t WorkspaceToWorld;
    inline uintptr_t viewmatrix;

    // Version tracking
    inline std::string CurrentRobloxVersion;
    inline std::string CurrentByfronVersion;

    // Error tracking
    inline std::vector<std::string> UpdateErrors;
    inline int LastUpdateStatus = 0; // 0 = not updated, 1 = success, -1 = failed

    static bool GetHttpResponse(const std::wstring& host, const std::wstring& path, std::string& outResponse) {
        bool success = false;
        HINTERNET hSession = nullptr;
        HINTERNET hConnect = nullptr;
        HINTERNET hRequest = nullptr;

        try {
            hSession = WinHttpOpen(L"OffsetUpdater/2.0", WINHTTP_ACCESS_TYPE_DEFAULT_PROXY, nullptr, nullptr, 0);
            if (!hSession) {
                std::cerr << "[HTTP] Failed to open session. Error: " << GetLastError() << std::endl;
                return false;
            }

            hConnect = WinHttpConnect(hSession, host.c_str(), INTERNET_DEFAULT_HTTPS_PORT, 0);
            if (!hConnect) {
                std::cerr << "[HTTP] Failed to connect to host. Error: " << GetLastError() << std::endl;
                goto cleanup;
            }

            hRequest = WinHttpOpenRequest(hConnect, L"GET", path.c_str(), nullptr, 
                                        WINHTTP_NO_REFERER, WINHTTP_DEFAULT_ACCEPT_TYPES, 
                                        WINHTTP_FLAG_SECURE);
            if (!hRequest) {
                std::cerr << "[HTTP] Failed to open request. Error: " << GetLastError() << std::endl;
                goto cleanup;
            }

            // Set timeout (10 seconds)
            DWORD timeout = 10000;
            WinHttpSetOption(hRequest, WINHTTP_OPTION_CONNECT_TIMEOUT, &timeout, sizeof(timeout));
            WinHttpSetOption(hRequest, WINHTTP_OPTION_RECEIVE_TIMEOUT, &timeout, sizeof(timeout));

            if (WinHttpSendRequest(hRequest, WINHTTP_NO_ADDITIONAL_HEADERS, 0,
                WINHTTP_NO_REQUEST_DATA, 0, 0, 0) &&
                WinHttpReceiveResponse(hRequest, nullptr))
            {
                // Check status code
                DWORD statusCode = 0;
                DWORD statusCodeSize = sizeof(statusCode);
                if (WinHttpQueryHeaders(hRequest, WINHTTP_QUERY_STATUS_CODE | WINHTTP_QUERY_FLAG_NUMBER,
                    nullptr, &statusCode, &statusCodeSize, nullptr)) {
                    if (statusCode != 200) {
                        std::cerr << "[HTTP] Bad status code: " << statusCode << std::endl;
                        goto cleanup;
                    }
                }

                DWORD dwSize = 0;
                outResponse.clear();
                outResponse.reserve(8192); // Pre-allocate

                do {
                    DWORD dwDownloaded = 0;
                    if (!WinHttpQueryDataAvailable(hRequest, &dwSize)) break;
                    if (dwSize == 0) break;

                    std::vector<char> buffer(dwSize + 1);
                    if (!WinHttpReadData(hRequest, buffer.data(), dwSize, &dwDownloaded)) {
                        break;
                    }
                    buffer[dwDownloaded] = 0;
                    outResponse.append(buffer.data(), dwDownloaded);
                } while (dwSize > 0);
                
                success = !outResponse.empty();
            }
        }
        catch (...) {
            std::cerr << "[HTTP] Exception occurred during HTTP request" << std::endl;
        }

    cleanup:
        if (hRequest) WinHttpCloseHandle(hRequest);
        if (hConnect) WinHttpCloseHandle(hConnect);
        if (hSession) WinHttpCloseHandle(hSession);

        return success;
    }

    static std::string GetJsonStringValue(const std::string& json, const std::string& key) {
        std::string search = "\"" + key + "\"";
        size_t pos = json.find(search);
        if (pos == std::string::npos) return "";

        pos = json.find(':', pos);
        if (pos == std::string::npos) return "";

        pos++;
        while (pos < json.size() && std::isspace(json[pos])) pos++;

        if (pos >= json.size() || json[pos] != '"') return "";
        pos++;

        size_t start = pos;
        size_t end = start;
        while (end < json.size() && json[end] != '"') {
            if (json[end] == '\\' && end + 1 < json.size()) {
                end += 2; // Skip escaped character
            } else {
                end++;
            }
        }
        if (end >= json.size()) return "";

        return json.substr(start, end - start);
    }

    static uintptr_t HexStringToUIntPtr(const std::string& hex) {
        if (hex.empty()) return 0;
        
        try {
            uintptr_t result = 0;
            std::istringstream iss(hex);
            iss >> std::hex >> result;
            return result;
        }
        catch (...) {
            std::cerr << "[PARSE] Failed to parse hex string: " << hex << std::endl;
            return 0;
        }
    }

    // Enhanced macro with error tracking
    #define UPDOFFSET_SAFE(name) \
    { \
        std::string valStr = GetJsonStringValue(jsonData, #name); \
        if (!valStr.empty()) { \
            uintptr_t newValue = HexStringToUIntPtr(valStr); \
            if (newValue != 0 || valStr == "0x0") { \
                offsets::name = newValue; \
                updatedCount++; \
            } else { \
                UpdateErrors.push_back("Failed to parse " #name ": " + valStr); \
            } \
        } else { \
            UpdateErrors.push_back("Missing offset: " #name); \
        } \
    }

    inline bool IsRobloxRunning() {
        HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
        if (snapshot == INVALID_HANDLE_VALUE) return false;

        PROCESSENTRY32W entry{};
        entry.dwSize = sizeof(PROCESSENTRY32W);

        bool found = false;
        if (Process32FirstW(snapshot, &entry)) {
            do {
                if (_wcsicmp(entry.szExeFile, L"RobloxPlayerBeta.exe") == 0) {
                    found = true;
                    break;
                }
            } while (Process32NextW(snapshot, &entry));
        }
        CloseHandle(snapshot);
        return found;
    }

    inline std::string GetRobloxVersion() {
        DWORD pid = 0;
        HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
        if (snapshot == INVALID_HANDLE_VALUE) return "";

        PROCESSENTRY32W entry{};
        entry.dwSize = sizeof(PROCESSENTRY32W);

        bool found = false;
        if (Process32FirstW(snapshot, &entry)) {
            do {
                if (_wcsicmp(entry.szExeFile, L"RobloxPlayerBeta.exe") == 0) {
                    pid = entry.th32ProcessID;
                    found = true;
                    break;
                }
            } while (Process32NextW(snapshot, &entry));
        }
        CloseHandle(snapshot);

        if (!found) return "";

        HANDLE process = OpenProcess(PROCESS_QUERY_LIMITED_INFORMATION, FALSE, pid);
        if (!process) return "";

        wchar_t pathBuffer[MAX_PATH];
        DWORD pathSize = MAX_PATH;
        std::string version;
        
        if (QueryFullProcessImageNameW(process, 0, pathBuffer, &pathSize)) {
            std::filesystem::path exePath(pathBuffer);
            std::wstring folderName = exePath.parent_path().filename().wstring();
            version = std::string(folderName.begin(), folderName.end());
        }
        
        CloseHandle(process);
        return version;
    }

    inline void checkversion() {
        constexpr auto host = L"clientsettingscdn.roblox.com";
        constexpr auto path = L"/v2/client-version/WindowsPlayer";

        std::cout << "[VERSION] Checking Roblox version..." << std::endl;

        std::string jsonData;
        if (!GetHttpResponse(host, path, jsonData)) {
            std::cout << " [-] Failed to fetch version data from Roblox API" << std::endl;
            return;
        }

        std::string expectedVersion = GetJsonStringValue(jsonData, "clientVersionUpload");
        if (expectedVersion.empty()) {
            std::cout << " [-] Failed to parse version from API response" << std::endl;
            return;
        }

        if (!IsRobloxRunning()) {
            std::cout << " [-] RobloxPlayerBeta.exe is not running" << std::endl;
            std::cout << " [!] Expected version: " << expectedVersion << std::endl;
            return;
        }

        std::string actualVersion = GetRobloxVersion();
        if (actualVersion.empty()) {
            std::cout << " [-] Failed to get local Roblox version" << std::endl;
            return;
        }

        if (expectedVersion == actualVersion) {
            std::cout << " [+] Version matches: " << expectedVersion << std::endl;
        } else {
            std::cout << " [-] Version mismatch!" << std::endl;
            std::cout << "     Expected: " << expectedVersion << std::endl;
            std::cout << "     Found:    " << actualVersion << std::endl;
            std::cout << " [!] Offsets may be outdated!" << std::endl;
        }
    }

    inline bool autoupdate(bool verbose = true) {
        constexpr auto host = L"offsets.ntgetwritewatch.workers.dev";
        constexpr auto path = L"/offsets.json";

        UpdateErrors.clear();
        LastUpdateStatus = 0;
        int updatedCount = 0;

        if (verbose) {
            std::cout << "[AUTOUPDATE] Fetching offsets from API..." << std::endl;
        }

        std::string jsonData;
        if (!GetHttpResponse(host, path, jsonData)) {
            std::string error = "Failed to fetch offsets from API";
            UpdateErrors.push_back(error);
            LastUpdateStatus = -1;
            if (verbose) {
                std::cout << " [-] " << error << std::endl;
            }
            return false;
        }

        // Update version tracking
        CurrentRobloxVersion = GetJsonStringValue(jsonData, "RobloxVersion");
        CurrentByfronVersion = GetJsonStringValue(jsonData, "ByfronVersion");

        if (verbose && !CurrentRobloxVersion.empty()) {
            std::cout << " [+] " << CurrentRobloxVersion << std::endl;
        }

        // Update all offsets using the enhanced macro
        UPDOFFSET_SAFE(Adornee)
        UPDOFFSET_SAFE(AnchoredMask)
        UPDOFFSET_SAFE(AnimationId)
        UPDOFFSET_SAFE(AttributeList)
        UPDOFFSET_SAFE(AttributeToNext)
        UPDOFFSET_SAFE(AttributeToValue)
        UPDOFFSET_SAFE(AutoJumpEnabled)
        UPDOFFSET_SAFE(BeamBrightness)
        UPDOFFSET_SAFE(BeamColor)
        UPDOFFSET_SAFE(BeamLightEmission)
        UPDOFFSET_SAFE(BeamLightInfuence)
        UPDOFFSET_SAFE(Camera)
        UPDOFFSET_SAFE(CameraMaxZoomDistance)
        UPDOFFSET_SAFE(CameraMinZoomDistance)
        UPDOFFSET_SAFE(CameraMode)
        UPDOFFSET_SAFE(CameraPos)
        UPDOFFSET_SAFE(CameraRotation)
        UPDOFFSET_SAFE(CameraSubject)
        UPDOFFSET_SAFE(CameraType)
        UPDOFFSET_SAFE(CanCollideMask)
        UPDOFFSET_SAFE(CanTouchMask)
        UPDOFFSET_SAFE(CharacterAppearanceId)
        UPDOFFSET_SAFE(Children)
        UPDOFFSET_SAFE(ChildrenEnd)
        UPDOFFSET_SAFE(ClassDescriptor)
        UPDOFFSET_SAFE(ClassDescriptorToClassName)
        UPDOFFSET_SAFE(ClickDetectorMaxActivationDistance)
        UPDOFFSET_SAFE(ClockTime)
        UPDOFFSET_SAFE(CreatorId)
        UPDOFFSET_SAFE(DataModelDeleterPointer)
        UPDOFFSET_SAFE(DataModelPrimitiveCount)
        UPDOFFSET_SAFE(DataModelToRenderView1)
        UPDOFFSET_SAFE(DataModelToRenderView2)
        UPDOFFSET_SAFE(DataModelToRenderView3)
        UPDOFFSET_SAFE(DecalTexture)
        UPDOFFSET_SAFE(Deleter)
        UPDOFFSET_SAFE(DeleterBack)
        UPDOFFSET_SAFE(Dimensions)
        UPDOFFSET_SAFE(DisplayName)
        UPDOFFSET_SAFE(EvaluateStateMachine)
        UPDOFFSET_SAFE(FOV)
        UPDOFFSET_SAFE(FakeDataModelPointer)
        UPDOFFSET_SAFE(FakeDataModelToDataModel)
        UPDOFFSET_SAFE(FogColor)
        UPDOFFSET_SAFE(FogEnd)
        UPDOFFSET_SAFE(FogStart)
        UPDOFFSET_SAFE(ForceNewAFKDuration)
        UPDOFFSET_SAFE(FramePositionOffsetX)
        UPDOFFSET_SAFE(FramePositionOffsetY)
        UPDOFFSET_SAFE(FramePositionX)
        UPDOFFSET_SAFE(FramePositionY)
        UPDOFFSET_SAFE(FrameRotation)
        UPDOFFSET_SAFE(FrameSizeX)
        UPDOFFSET_SAFE(FrameSizeY)
        UPDOFFSET_SAFE(GameId)
        UPDOFFSET_SAFE(GameLoaded)
        UPDOFFSET_SAFE(Gravity)
        UPDOFFSET_SAFE(Health)
        UPDOFFSET_SAFE(HealthDisplayDistance)
        UPDOFFSET_SAFE(HipHeight)
        UPDOFFSET_SAFE(HumanoidDisplayName)
        UPDOFFSET_SAFE(HumanoidState)
        UPDOFFSET_SAFE(HumanoidStateId)
        UPDOFFSET_SAFE(InputObject)
        UPDOFFSET_SAFE(InsetMaxX)
        UPDOFFSET_SAFE(InsetMaxY)
        UPDOFFSET_SAFE(InsetMinX)
        UPDOFFSET_SAFE(InsetMinY)
        UPDOFFSET_SAFE(InstanceCapabilities)
        UPDOFFSET_SAFE(JobEnd)
        UPDOFFSET_SAFE(JobId)
        UPDOFFSET_SAFE(JobStart)
        UPDOFFSET_SAFE(Job_Name)
        UPDOFFSET_SAFE(JobsPointer)
        UPDOFFSET_SAFE(JumpPower)
        UPDOFFSET_SAFE(LocalPlayer)
        UPDOFFSET_SAFE(LocalScriptByteCode)
        UPDOFFSET_SAFE(LocalScriptBytecodePointer)
        UPDOFFSET_SAFE(LocalScriptHash)
        UPDOFFSET_SAFE(MaterialType)
        UPDOFFSET_SAFE(MaxHealth)
        UPDOFFSET_SAFE(MaxSlopeAngle)
        UPDOFFSET_SAFE(MeshPartColor3)
        UPDOFFSET_SAFE(ModelInstance)
        UPDOFFSET_SAFE(ModuleScriptByteCode)
        UPDOFFSET_SAFE(ModuleScriptBytecodePointer)
        UPDOFFSET_SAFE(ModuleScriptHash)
        UPDOFFSET_SAFE(MoonTextureId)
        UPDOFFSET_SAFE(MousePosition)
        UPDOFFSET_SAFE(MouseSensitivity)
        UPDOFFSET_SAFE(MoveDirection)
        UPDOFFSET_SAFE(Name)
        UPDOFFSET_SAFE(NameDisplayDistance)
        UPDOFFSET_SAFE(NameSize)
        UPDOFFSET_SAFE(OnDemandInstance)
        UPDOFFSET_SAFE(OutdoorAmbient)
        UPDOFFSET_SAFE(Parent)
        UPDOFFSET_SAFE(PartSize)
        UPDOFFSET_SAFE(Ping)
        UPDOFFSET_SAFE(PlaceId)
        UPDOFFSET_SAFE(PlayerConfigurerPointer)
        UPDOFFSET_SAFE(PlayerMouse)
        UPDOFFSET_SAFE(Position)
        UPDOFFSET_SAFE(Primitive)
        UPDOFFSET_SAFE(PrimitiveGravity)
        UPDOFFSET_SAFE(PrimitiveValidateValue)
        UPDOFFSET_SAFE(PrimitivesPointer1)
        UPDOFFSET_SAFE(PrimitivesPointer2)
        UPDOFFSET_SAFE(ProximityPromptActionText)
        UPDOFFSET_SAFE(ProximityPromptEnabled)
        UPDOFFSET_SAFE(ProximityPromptGamepadKeyCode)
        UPDOFFSET_SAFE(ProximityPromptHoldDuraction)
        UPDOFFSET_SAFE(ProximityPromptMaxActivationDistance)
        UPDOFFSET_SAFE(ProximityPromptMaxObjectText)
        UPDOFFSET_SAFE(RenderJobToDataModel)
        UPDOFFSET_SAFE(RenderJobToFakeDataModel)
        UPDOFFSET_SAFE(RenderJobToRenderView)
        UPDOFFSET_SAFE(RequireBypass)
        UPDOFFSET_SAFE(RigType)
        UPDOFFSET_SAFE(Rotation)
        UPDOFFSET_SAFE(RunContext)
        UPDOFFSET_SAFE(ScriptContext)
        UPDOFFSET_SAFE(Sit)
        UPDOFFSET_SAFE(SkyboxBk)
        UPDOFFSET_SAFE(SkyboxDn)
        UPDOFFSET_SAFE(SkyboxFt)
        UPDOFFSET_SAFE(SkyboxLf)
        UPDOFFSET_SAFE(SkyboxRt)
        UPDOFFSET_SAFE(SkyboxUp)
        UPDOFFSET_SAFE(SoundId)
        UPDOFFSET_SAFE(StarCount)
        UPDOFFSET_SAFE(StringLength)
        UPDOFFSET_SAFE(SunTextureId)
        UPDOFFSET_SAFE(TagList)
        UPDOFFSET_SAFE(TaskSchedulerMaxFPS)
        UPDOFFSET_SAFE(TaskSchedulerPointer)
        UPDOFFSET_SAFE(Team)
        UPDOFFSET_SAFE(TeamColor)
        UPDOFFSET_SAFE(Tool_Grip_Position)
        UPDOFFSET_SAFE(Transparency)
        UPDOFFSET_SAFE(UserId)
        UPDOFFSET_SAFE(Value)
        UPDOFFSET_SAFE(Velocity)
        UPDOFFSET_SAFE(ViewportSize)
        UPDOFFSET_SAFE(VisualEngine)
        UPDOFFSET_SAFE(VisualEnginePointer)
        UPDOFFSET_SAFE(VisualEngineToDataModel1)
        UPDOFFSET_SAFE(VisualEngineToDataModel2)
        UPDOFFSET_SAFE(WalkSpeed)
        UPDOFFSET_SAFE(WalkSpeedCheck)
        UPDOFFSET_SAFE(WhitelistedThreads)
        UPDOFFSET_SAFE(Workspace)
        UPDOFFSET_SAFE(WorkspaceToWorld)
        UPDOFFSET_SAFE(viewmatrix)

        // Set status based on results
        if (UpdateErrors.empty()) {
            LastUpdateStatus = 1;
            if (verbose) {
                std::cout << " [+] Successfully updated " << updatedCount << " offsets" << std::endl;
            }
            return true;
        } else {
            LastUpdateStatus = -1;
            if (verbose) {
                std::cout << " [!] Updated " << updatedCount << " offsets with " 
                         << UpdateErrors.size() << " errors" << std::endl;
                
                if (UpdateErrors.size() <= 10) { // Don't spam too many errors
                    for (const auto& error : UpdateErrors) {
                        std::cout << " [-] " << error << std::endl;
                    }
                } else {
                    std::cout << " [-] Too many errors to display (showing first 5):" << std::endl;
                    for (size_t i = 0; i < 5; ++i) {
                        std::cout << " [-] " << UpdateErrors[i] << std::endl;
                    }
                }
            }
            return false;
        }
    }

    #undef UPDOFFSET_SAFE

    // Utility functions for diagnostics
    inline void PrintUpdateStatus() {
        switch (LastUpdateStatus) {
            case 0:
                std::cout << "[STATUS] Offsets not updated yet" << std::endl;
                break;
            case 1:
                std::cout << "[STATUS] Last update: SUCCESS" << std::endl;
                break;
            case -1:
                std::cout << "[STATUS] Last update: FAILED with " << UpdateErrors.size() << " errors" << std::endl;
                break;
        }
        
        if (!CurrentRobloxVersion.empty()) {
            std::cout << "[STATUS] Current Roblox Version: " << CurrentRobloxVersion << std::endl;
        }
    }

    inline std::vector<std::string> GetUpdateErrors() {
        return UpdateErrors;
    }

    // Auto-update with retry mechanism
    inline bool autoupdate_with_retry(int maxRetries = 3, bool verbose = true) {
        for (int attempt = 1; attempt <= maxRetries; ++attempt) {
            if (verbose && attempt > 1) {
                std::cout << "[RETRY] Attempt " << attempt << "/" << maxRetries << std::endl;
            }
            
            if (autoupdate(verbose)) {
                return true;
            }
            
            if (attempt < maxRetries) {
                Sleep(1000); // Wait 1 second before retry
            }
        }
        
        if (verbose) {
            std::cout << "[FAILED] All retry attempts exhausted" << std::endl;
        }
        return false;
    }
}