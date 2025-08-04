#pragma once
#include <Windows.h>
#include <winhttp.h>
#include <iostream>
#include <sstream>
#include <tlhelp32.h>
#include <psapi.h>
#include <filesystem>
#include <string>
#include <thread>
#include <chrono>
#include "../xorstr.hpp"

// Auto offset updating system
namespace AutoOffsets {

    // offsets that u CANT get from https://offsets.ntgetwritewatch.workers.dev/offsets.hpp
    inline constexpr uintptr_t RenderToFakeDataModel = 0x128;
    inline constexpr uintptr_t CFrame = 0x128;
    inline constexpr uintptr_t Anchored = 0x309; // unsure if this is correct
    inline constexpr uintptr_t CanCollide = 0x309; // unsure if this is correct

    // offsets that u CAN get from https://offsets.ntgetwritewatch.workers.dev/offsets.hpp
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

    // Obfuscated HTTP client
    class ObfuscatedHttpClient {
    private:
        HINTERNET hSession = nullptr;
        
    public:
        ObfuscatedHttpClient() {
            hSession = WinHttpOpen(xorstr_(L"FluxWare/1.0").crypt_get(), WINHTTP_ACCESS_TYPE_DEFAULT_PROXY, nullptr, nullptr, 0);
        }
        
        ~ObfuscatedHttpClient() {
            if (hSession) {
                WinHttpCloseHandle(hSession);
            }
        }
        
        bool GetHttpResponse(const std::wstring& host, const std::wstring& path, std::string& outResponse) {
            if (!hSession) return false;
            
            bool success = false;
            HINTERNET hConnect = WinHttpConnect(hSession, host.c_str(), INTERNET_DEFAULT_HTTPS_PORT, 0);
            if (!hConnect) return false;

            HINTERNET hRequest = WinHttpOpenRequest(hConnect, L"GET", path.c_str(), nullptr, WINHTTP_NO_REFERER, WINHTTP_DEFAULT_ACCEPT_TYPES, WINHTTP_FLAG_SECURE);
            if (!hRequest) {
                WinHttpCloseHandle(hConnect);
                return false;
            }

            if (WinHttpSendRequest(hRequest, WINHTTP_NO_ADDITIONAL_HEADERS, 0,
                WINHTTP_NO_REQUEST_DATA, 0, 0, 0) &&
                WinHttpReceiveResponse(hRequest, nullptr))
            {
                DWORD dwSize = 0;
                do {
                    DWORD dwDownloaded = 0;
                    if (!WinHttpQueryDataAvailable(hRequest, &dwSize)) break;
                    if (dwSize == 0) break;

                    char* buffer = new char[dwSize + 1];
                    if (!WinHttpReadData(hRequest, buffer, dwSize, &dwDownloaded)) {
                        delete[] buffer;
                        break;
                    }
                    buffer[dwDownloaded] = 0;
                    outResponse.append(buffer);
                    delete[] buffer;
                } while (dwSize > 0);
                success = true;
            }

            WinHttpCloseHandle(hRequest);
            WinHttpCloseHandle(hConnect);
            return success;
        }
    };

    // JSON parser for offset data
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
        while (pos < json.size() && json[pos] != '"') pos++;
        if (pos >= json.size()) return "";

        return json.substr(start, pos - start);
    }

    static uintptr_t HexStringToUIntPtr(const std::string& hex) {
        uintptr_t result = 0;
        std::istringstream iss(hex);
        iss >> std::hex >> result;
        return result;
    }

    // Enhanced version checker with obfuscation
    class VersionChecker {
    private:
        ObfuscatedHttpClient httpClient;
        
    public:
        bool CheckRobloxVersion() {
            try {
                std::wstring host = xorstr_(L"clientsettingscdn.roblox.com").crypt_get();
                std::wstring path = xorstr_(L"/v2/client-version/WindowsPlayer").crypt_get();

                std::string jsonData;
                if (!httpClient.GetHttpResponse(host, path, jsonData)) {
                    std::cout << xorstr_(" [-] failed to fetch version data") << std::endl;
                    return false;
                }

                std::string version = GetJsonStringValue(jsonData, xorstr_("clientVersionUpload"));
                if (version.empty()) {
                    std::cout << xorstr_(" [-] failed to get version") << std::endl;
                    return false;
                }

                return VerifyRobloxProcess(version);
            }
            catch (const std::exception& e) {
                std::cout << xorstr_(" [-] Exception in version check: ") << e.what() << std::endl;
                return false;
            }
        }
        
    private:
        bool VerifyRobloxProcess(const std::string& expectedVersion) {
            DWORD pid = 0;
            HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
            if (snapshot == INVALID_HANDLE_VALUE) return false;

            PROCESSENTRY32W entry{};
            entry.dwSize = sizeof(PROCESSENTRY32W);

            bool found = false;
            if (Process32FirstW(snapshot, &entry)) {
                do {
                    if (_wcsicmp(entry.szExeFile, xorstr_(L"RobloxPlayerBeta.exe").crypt_get()) == 0) {
                        pid = entry.th32ProcessID;
                        found = true;
                        break;
                    }
                } while (Process32NextW(snapshot, &entry));
            }
            CloseHandle(snapshot);

            if (!found) {
                std::cout << xorstr_(" [-] RobloxPlayerBeta.exe not found") << std::endl;
                return false;
            }

            HANDLE process = OpenProcess(PROCESS_QUERY_LIMITED_INFORMATION, FALSE, pid);
            if (!process) return false;

            wchar_t pathBuffer[MAX_PATH];
            DWORD pathSize = MAX_PATH;
            if (!QueryFullProcessImageNameW(process, 0, pathBuffer, &pathSize)) {
                CloseHandle(process);
                return false;
            }
            CloseHandle(process);

            std::filesystem::path exePath(pathBuffer);
            std::wstring folderName = exePath.parent_path().filename().wstring();
            std::wstring Wversion(expectedVersion.begin(), expectedVersion.end());

            if (_wcsicmp(folderName.c_str(), Wversion.c_str()) == 0) {
                std::cout << xorstr_(" [+] version matches: ") << expectedVersion << std::endl;
                return true;
            } else {
                std::wcout << xorstr_(" [-] version mismatch, expected: ") << Wversion << xorstr_(", found: ") << folderName << std::endl;
                return false;
            }
        }
    };

    // Offset updater with enhanced security
    class OffsetUpdater {
    private:
        ObfuscatedHttpClient httpClient;
        std::chrono::steady_clock::time_point lastUpdate;
        bool offsetsValid = false;
        
    public:
        bool UpdateOffsets(bool forceUpdate = false) {
            auto now = std::chrono::steady_clock::now();
            auto timeSinceUpdate = std::chrono::duration_cast<std::chrono::minutes>(now - lastUpdate).count();
            
            // Update every 30 minutes or on force
            if (!forceUpdate && offsetsValid && timeSinceUpdate < 30) {
                return true;
            }
            
            try {
                std::wstring host = xorstr_(L"offsets.ntgetwritewatch.workers.dev").crypt_get();
                std::wstring path = xorstr_(L"/offsets.json").crypt_get();

                std::string jsonData;
                if (!httpClient.GetHttpResponse(host, path, jsonData)) {
                    std::cout << xorstr_("[autoupdate] failed to get offsets") << std::endl;
                    return false;
                }

                if (ParseAndUpdateOffsets(jsonData)) {
                    lastUpdate = now;
                    offsetsValid = true;
                    std::cout << xorstr_("[+] Offsets updated successfully") << std::endl;
                    return true;
                }
                
                return false;
            }
            catch (const std::exception& e) {
                std::cout << xorstr_("[autoupdate] Exception: ") << e.what() << std::endl;
                return false;
            }
        }
        
    private:
        bool ParseAndUpdateOffsets(const std::string& jsonData) {
            try {
                // Update all offsets using macro
                #define UPDOFFSET(name) \
                { \
                    std::string valStr = GetJsonStringValue(jsonData, #name); \
                    if (!valStr.empty()) { \
                        AutoOffsets::name = HexStringToUIntPtr(valStr); \
                    } \
                }

                UPDOFFSET(Adornee)
                UPDOFFSET(AnchoredMask)
                UPDOFFSET(AnimationId)
                UPDOFFSET(AttributeList)
                UPDOFFSET(AttributeToNext)
                UPDOFFSET(AttributeToValue)
                UPDOFFSET(AutoJumpEnabled)
                UPDOFFSET(BeamBrightness)
                UPDOFFSET(BeamColor)
                UPDOFFSET(BeamLightEmission)
                UPDOFFSET(BeamLightInfuence)
                UPDOFFSET(Camera)
                UPDOFFSET(CameraMaxZoomDistance)
                UPDOFFSET(CameraMinZoomDistance)
                UPDOFFSET(CameraMode)
                UPDOFFSET(CameraPos)
                UPDOFFSET(CameraRotation)
                UPDOFFSET(CameraSubject)
                UPDOFFSET(CameraType)
                UPDOFFSET(CanCollideMask)
                UPDOFFSET(CanTouchMask)
                UPDOFFSET(CharacterAppearanceId)
                UPDOFFSET(Children)
                UPDOFFSET(ChildrenEnd)
                UPDOFFSET(ClassDescriptor)
                UPDOFFSET(ClassDescriptorToClassName)
                UPDOFFSET(ClickDetectorMaxActivationDistance)
                UPDOFFSET(ClockTime)
                UPDOFFSET(CreatorId)
                UPDOFFSET(DataModelDeleterPointer)
                UPDOFFSET(DataModelPrimitiveCount)
                UPDOFFSET(DataModelToRenderView1)
                UPDOFFSET(DataModelToRenderView2)
                UPDOFFSET(DataModelToRenderView3)
                UPDOFFSET(DecalTexture)
                UPDOFFSET(Deleter)
                UPDOFFSET(DeleterBack)
                UPDOFFSET(Dimensions)
                UPDOFFSET(DisplayName)
                UPDOFFSET(EvaluateStateMachine)
                UPDOFFSET(FOV)
                UPDOFFSET(FakeDataModelPointer)
                UPDOFFSET(FakeDataModelToDataModel)
                UPDOFFSET(FogColor)
                UPDOFFSET(FogEnd)
                UPDOFFSET(FogStart)
                UPDOFFSET(ForceNewAFKDuration)
                UPDOFFSET(FramePositionOffsetX)
                UPDOFFSET(FramePositionOffsetY)
                UPDOFFSET(FramePositionX)
                UPDOFFSET(FramePositionY)
                UPDOFFSET(FrameRotation)
                UPDOFFSET(FrameSizeX)
                UPDOFFSET(FrameSizeY)
                UPDOFFSET(GameId)
                UPDOFFSET(GameLoaded)
                UPDOFFSET(Gravity)
                UPDOFFSET(Health)
                UPDOFFSET(HealthDisplayDistance)
                UPDOFFSET(HipHeight)
                UPDOFFSET(HumanoidDisplayName)
                UPDOFFSET(HumanoidState)
                UPDOFFSET(HumanoidStateId)
                UPDOFFSET(InputObject)
                UPDOFFSET(InsetMaxX)
                UPDOFFSET(InsetMaxY)
                UPDOFFSET(InsetMinX)
                UPDOFFSET(InsetMinY)
                UPDOFFSET(InstanceCapabilities)
                UPDOFFSET(JobEnd)
                UPDOFFSET(JobId)
                UPDOFFSET(JobStart)
                UPDOFFSET(Job_Name)
                UPDOFFSET(JobsPointer)
                UPDOFFSET(JumpPower)
                UPDOFFSET(LocalPlayer)
                UPDOFFSET(LocalScriptByteCode)
                UPDOFFSET(LocalScriptBytecodePointer)
                UPDOFFSET(LocalScriptHash)
                UPDOFFSET(MaterialType)
                UPDOFFSET(MaxHealth)
                UPDOFFSET(MaxSlopeAngle)
                UPDOFFSET(MeshPartColor3)
                UPDOFFSET(ModelInstance)
                UPDOFFSET(ModuleScriptByteCode)
                UPDOFFSET(ModuleScriptBytecodePointer)
                UPDOFFSET(ModuleScriptHash)
                UPDOFFSET(MoonTextureId)
                UPDOFFSET(MousePosition)
                UPDOFFSET(MouseSensitivity)
                UPDOFFSET(MoveDirection)
                UPDOFFSET(Name)
                UPDOFFSET(NameDisplayDistance)
                UPDOFFSET(NameSize)
                UPDOFFSET(OnDemandInstance)
                UPDOFFSET(OutdoorAmbient)
                UPDOFFSET(Parent)
                UPDOFFSET(PartSize)
                UPDOFFSET(Ping)
                UPDOFFSET(PlaceId)
                UPDOFFSET(PlayerConfigurerPointer)
                UPDOFFSET(PlayerMouse)
                UPDOFFSET(Position)
                UPDOFFSET(Primitive)
                UPDOFFSET(PrimitiveGravity)
                UPDOFFSET(PrimitiveValidateValue)
                UPDOFFSET(PrimitivesPointer1)
                UPDOFFSET(PrimitivesPointer2)
                UPDOFFSET(ProximityPromptActionText)
                UPDOFFSET(ProximityPromptEnabled)
                UPDOFFSET(ProximityPromptGamepadKeyCode)
                UPDOFFSET(ProximityPromptHoldDuraction)
                UPDOFFSET(ProximityPromptMaxActivationDistance)
                UPDOFFSET(ProximityPromptMaxObjectText)
                UPDOFFSET(RenderJobToDataModel)
                UPDOFFSET(RenderJobToFakeDataModel)
                UPDOFFSET(RenderJobToRenderView)
                UPDOFFSET(RequireBypass)
                UPDOFFSET(RigType)
                UPDOFFSET(Rotation)
                UPDOFFSET(RunContext)
                UPDOFFSET(ScriptContext)
                UPDOFFSET(Sit)
                UPDOFFSET(SkyboxBk)
                UPDOFFSET(SkyboxDn)
                UPDOFFSET(SkyboxFt)
                UPDOFFSET(SkyboxLf)
                UPDOFFSET(SkyboxRt)
                UPDOFFSET(SkyboxUp)
                UPDOFFSET(SoundId)
                UPDOFFSET(StarCount)
                UPDOFFSET(StringLength)
                UPDOFFSET(SunTextureId)
                UPDOFFSET(TagList)
                UPDOFFSET(TaskSchedulerMaxFPS)
                UPDOFFSET(TaskSchedulerPointer)
                UPDOFFSET(Team)
                UPDOFFSET(TeamColor)
                UPDOFFSET(Tool_Grip_Position)
                UPDOFFSET(Transparency)
                UPDOFFSET(UserId)
                UPDOFFSET(Value)
                UPDOFFSET(Velocity)
                UPDOFFSET(ViewportSize)
                UPDOFFSET(VisualEngine)
                UPDOFFSET(VisualEnginePointer)
                UPDOFFSET(VisualEngineToDataModel1)
                UPDOFFSET(VisualEngineToDataModel2)
                UPDOFFSET(WalkSpeed)
                UPDOFFSET(WalkSpeedCheck)
                UPDOFFSET(WhitelistedThreads)
                UPDOFFSET(Workspace)
                UPDOFFSET(WorkspaceToWorld)
                UPDOFFSET(viewmatrix)

                #undef UPDOFFSET
                return true;
            }
            catch (const std::exception& e) {
                std::cout << xorstr_("[autoupdate] Parse error: ") << e.what() << std::endl;
                return false;
            }
        }
    };

    // Global instances
    extern std::unique_ptr<VersionChecker> g_VersionChecker;
    extern std::unique_ptr<OffsetUpdater> g_OffsetUpdater;

    // Initialization function
    inline bool Initialize() {
        try {
            g_VersionChecker = std::make_unique<VersionChecker>();
            g_OffsetUpdater = std::make_unique<OffsetUpdater>();
            
            // Check version and update offsets
            if (g_VersionChecker->CheckRobloxVersion()) {
                return g_OffsetUpdater->UpdateOffsets(true);
            }
            
            return false;
        }
        catch (const std::exception& e) {
            std::cout << xorstr_("AutoOffsets initialization failed: ") << e.what() << std::endl;
            return false;
        }
    }

    // Background update thread
    inline void StartBackgroundUpdater() {
        std::thread([]() {
            while (true) {
                std::this_thread::sleep_for(std::chrono::minutes(30));
                if (g_OffsetUpdater) {
                    g_OffsetUpdater->UpdateOffsets();
                }
            }
        }).detach();
    }
}

// Global instances
std::unique_ptr<AutoOffsets::VersionChecker> AutoOffsets::g_VersionChecker;
std::unique_ptr<AutoOffsets::OffsetUpdater> AutoOffsets::g_OffsetUpdater;