#include "keyauth_integration.h"
#include "../auth.hpp"
#include "../Renderer/imgui/imgui.h"
#include "../Utils/colors.h"
#include "../Utils/console.h"
#include <Windows.h>
#include <vector>
#include <ctime>
#include <sstream>
#include <iomanip>

// Global KeyAuth instance
api* KeyAuthApp = nullptr;

// Global KeyAuth manager instance
KeyAuthManager g_KeyAuthManager;

KeyAuthManager::KeyAuthManager()
{
    // Initialize KeyAuth application instance
    KeyAuthApp = new api(
        KeyAuthConfig::name,
        KeyAuthConfig::ownerid,
        "", // secret will be handled by KeyAuth library
        KeyAuthConfig::version,
        KeyAuthConfig::url,
        KeyAuthConfig::path
    );
    
    // Initialize security measures
    Security::InitializeAntiDebug();
    Obfuscation::InitializeObfuscation();
    
    statusMessage = skCrypt("Ready to authenticate...").decrypt();
}

KeyAuthManager::~KeyAuthManager()
{
    if (KeyAuthApp)
    {
        delete KeyAuthApp;
        KeyAuthApp = nullptr;
    }
}

bool KeyAuthManager::Initialize()
{
    if (currentState != AuthState::NotInitialized)
        return true;
        
    log(skCrypt("Initializing KeyAuth...").decrypt(), 0);
    
    // Initialize KeyAuth
    KeyAuthApp->init();
    
    if (!KeyAuthApp->response.success)
    {
        statusMessage = skCrypt("Failed to initialize: ").decrypt() + KeyAuthApp->response.message;
        log(statusMessage, 2);
        currentState = AuthState::Failed;
        return false;
    }
    
    log(skCrypt("KeyAuth initialized successfully!").decrypt(), 1);
    currentState = AuthState::Initialized;
    
    // Fetch application statistics
    FetchAppStats();
    
    // Check blacklist status
    if (CheckBlacklist())
    {
        statusMessage = skCrypt("Access denied: Blacklisted").decrypt();
        log(statusMessage, 2);
        return false;
    }
    
    statusMessage = skCrypt("Authentication ready. Please login or register.").decrypt();
    return true;
}

bool KeyAuthManager::Login(const std::string& username, const std::string& password)
{
    if (currentState != AuthState::Initialized)
    {
        if (!Initialize())
            return false;
    }
    
    isProcessing = true;
    statusMessage = skCrypt("Logging in...").decrypt();
    
    log(skCrypt("Attempting login for user: ").decrypt() + username, 0);
    
    KeyAuthApp->login(username, password);
    
    if (!KeyAuthApp->response.success)
    {
        statusMessage = skCrypt("Login failed: ").decrypt() + KeyAuthApp->response.message;
        log(statusMessage, 2);
        isProcessing = false;
        return false;
    }
    
    currentUser = username;
    currentState = AuthState::LoggedIn;
    statusMessage = skCrypt("Successfully logged in as: ").decrypt() + currentUser;
    
    log(skCrypt("Login successful! Welcome ").decrypt() + currentUser, 1);
    LogEvent(skCrypt("User logged in: ").decrypt() + currentUser);
    
    isProcessing = false;
    showAuthWindow = false;
    return true;
}

bool KeyAuthManager::Register(const std::string& username, const std::string& password, const std::string& key)
{
    if (currentState != AuthState::Initialized)
    {
        if (!Initialize())
            return false;
    }
    
    isProcessing = true;
    statusMessage = skCrypt("Registering account...").decrypt();
    
    log(skCrypt("Attempting registration for user: ").decrypt() + username, 0);
    
    KeyAuthApp->regstr(username, password, key);
    
    if (!KeyAuthApp->response.success)
    {
        statusMessage = skCrypt("Registration failed: ").decrypt() + KeyAuthApp->response.message;
        log(statusMessage, 2);
        isProcessing = false;
        return false;
    }
    
    currentUser = username;
    currentState = AuthState::LoggedIn;
    statusMessage = skCrypt("Successfully registered and logged in as: ").decrypt() + currentUser;
    
    log(skCrypt("Registration successful! Welcome ").decrypt() + currentUser, 1);
    LogEvent(skCrypt("New user registered: ").decrypt() + currentUser);
    
    isProcessing = false;
    showAuthWindow = false;
    return true;
}

bool KeyAuthManager::LicenseAuth(const std::string& key)
{
    if (currentState != AuthState::Initialized)
    {
        if (!Initialize())
            return false;
    }
    
    isProcessing = true;
    statusMessage = skCrypt("Authenticating with license key...").decrypt();
    licenseKey = key;
    
    log(skCrypt("Attempting license authentication...").decrypt(), 0);
    
    KeyAuthApp->license(key);
    
    if (!KeyAuthApp->response.success)
    {
        statusMessage = skCrypt("License authentication failed: ").decrypt() + KeyAuthApp->response.message;
        log(statusMessage, 2);
        isProcessing = false;
        return false;
    }
    
    currentUser = KeyAuthApp->user_data.username;
    currentState = AuthState::LoggedIn;
    statusMessage = skCrypt("Successfully authenticated with license key!").decrypt();
    
    log(skCrypt("License authentication successful! Welcome ").decrypt() + currentUser, 1);
    LogEvent(skCrypt("User authenticated via license: ").decrypt() + currentUser);
    
    isProcessing = false;
    showAuthWindow = false;
    return true;
}

bool KeyAuthManager::Upgrade(const std::string& username, const std::string& key)
{
    if (currentState != AuthState::Initialized)
    {
        if (!Initialize())
            return false;
    }
    
    isProcessing = true;
    statusMessage = skCrypt("Upgrading account...").decrypt();
    
    log(skCrypt("Attempting account upgrade for: ").decrypt() + username, 0);
    
    KeyAuthApp->upgrade(username, key);
    
    if (!KeyAuthApp->response.success)
    {
        statusMessage = skCrypt("Upgrade failed: ").decrypt() + KeyAuthApp->response.message;
        log(statusMessage, 2);
        isProcessing = false;
        return false;
    }
    
    statusMessage = skCrypt("Account upgraded successfully!").decrypt();
    log(skCrypt("Account upgrade successful for: ").decrypt() + username, 1);
    LogEvent(skCrypt("Account upgraded: ").decrypt() + username);
    
    isProcessing = false;
    return true;
}

bool KeyAuthManager::WebLogin()
{
    if (currentState != AuthState::Initialized)
    {
        if (!Initialize())
            return false;
    }
    
    statusMessage = skCrypt("Opening web login... Please complete authentication in browser.").decrypt();
    log(skCrypt("Initiating web login...").decrypt(), 0);
    
    KeyAuthApp->web_login();
    
    // Wait for web login completion
    while (true)
    {
        KeyAuthApp->check();
        if (KeyAuthApp->response.success)
        {
            currentUser = KeyAuthApp->user_data.username;
            currentState = AuthState::LoggedIn;
            statusMessage = skCrypt("Web login successful! Welcome ").decrypt() + currentUser;
            log(statusMessage, 1);
            LogEvent(skCrypt("User logged in via web: ").decrypt() + currentUser);
            showAuthWindow = false;
            return true;
        }
        
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }
    
    return false;
}

void KeyAuthManager::Logout()
{
    currentState = AuthState::Initialized;
    currentUser.clear();
    licenseKey.clear();
    statusMessage = skCrypt("Logged out successfully.").decrypt();
    showAuthWindow = true;
    log(skCrypt("User logged out.").decrypt(), 0);
}

std::string KeyAuthManager::GetUserIP()
{
    if (currentState != AuthState::LoggedIn) return "";
    return KeyAuthApp->user_data.ip;
}

std::string KeyAuthManager::GetUserHWID()
{
    if (currentState != AuthState::LoggedIn) return "";
    return KeyAuthApp->user_data.hwid;
}

std::string KeyAuthManager::GetCreateDate()
{
    if (currentState != AuthState::LoggedIn) return "";
    return FormatTime(KeyAuthApp->user_data.createdate);
}

std::string KeyAuthManager::GetLastLogin()
{
    if (currentState != AuthState::LoggedIn) return "";
    return FormatTime(KeyAuthApp->user_data.lastlogin);
}

std::string KeyAuthManager::GetSubscriptions()
{
    if (currentState != AuthState::LoggedIn) return "";
    
    std::string subs = "";
    for (const auto& sub : KeyAuthApp->user_data.subscriptions)
    {
        if (!subs.empty()) subs += ", ";
        subs += sub;
    }
    return subs;
}

std::string KeyAuthManager::GetExpiry()
{
    if (currentState != AuthState::LoggedIn) return "";
    return FormatTime(KeyAuthApp->user_data.expiry);
}

bool KeyAuthManager::HasSubscription(const std::string& subName)
{
    if (currentState != AuthState::LoggedIn) return false;
    
    for (const auto& sub : KeyAuthApp->user_data.subscriptions)
    {
        if (sub == subName)
            return true;
    }
    return false;
}

void KeyAuthManager::FetchAppStats()
{
    if (currentState == AuthState::NotInitialized) return;
    
    KeyAuthApp->fetchstats();
    if (KeyAuthApp->response.success)
    {
        log(skCrypt("App Stats:").decrypt(), 1);
        log(skCrypt("  Users: ").decrypt() + KeyAuthApp->app_data.numUsers, 1);
        log(skCrypt("  Online: ").decrypt() + KeyAuthApp->app_data.numOnlineUsers, 1);
        log(skCrypt("  Keys: ").decrypt() + KeyAuthApp->app_data.numKeys, 1);
        log(skCrypt("  Version: ").decrypt() + KeyAuthApp->app_data.version, 1);
    }
}

bool KeyAuthManager::CheckBlacklist()
{
    if (currentState == AuthState::NotInitialized) return false;
    
    bool isBlacklisted = KeyAuthApp->checkblack();
    if (isBlacklisted)
    {
        log(skCrypt("HWID/IP is blacklisted!").decrypt(), 2);
        LogEvent(skCrypt("Blacklisted access attempt").decrypt());
    }
    
    return isBlacklisted;
}

void KeyAuthManager::BanUser(const std::string& reason)
{
    if (currentState != AuthState::LoggedIn) return;
    
    if (reason.empty())
        KeyAuthApp->ban();
    else
        KeyAuthApp->ban(reason);
        
    log(skCrypt("User banned: ").decrypt() + reason, 2);
    Logout();
}

void KeyAuthManager::LogEvent(const std::string& message)
{
    KeyAuthApp->log(message);
}

std::string KeyAuthManager::GetVariable(const std::string& varName)
{
    return KeyAuthApp->var(varName);
}

std::string KeyAuthManager::GetUserVariable(const std::string& varName)
{
    if (currentState != AuthState::LoggedIn) return "";
    return KeyAuthApp->getvar(varName);
}

void KeyAuthManager::SetUserVariable(const std::string& varName, const std::string& value)
{
    if (currentState != AuthState::LoggedIn) return;
    KeyAuthApp->setvar(varName, value);
}

std::vector<uint8_t> KeyAuthManager::DownloadFile(const std::string& fileId)
{
    if (currentState != AuthState::LoggedIn) return {};
    return KeyAuthApp->download(fileId);
}

std::string KeyAuthManager::SendWebhook(const std::string& webhookId, const std::string& params)
{
    return KeyAuthApp->webhook(webhookId, params);
}

void KeyAuthManager::RenderAuthWindow()
{
    if (!showAuthWindow || currentState == AuthState::LoggedIn)
        return;
        
    ImGui::SetNextWindowSize(ImVec2(500, 400), ImGuiCond_FirstUseEver);
    ImGui::SetNextWindowPos(ImVec2(100, 100), ImGuiCond_FirstUseEver);
    
    if (ImGui::Begin(skCrypt("Flux Ware V1 - Authentication").decrypt().c_str(), &showAuthWindow, 
        ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse))
    {
        // Status display
        ImGui::TextColored(isProcessing ? ImVec4(1,1,0,1) : ImVec4(1,1,1,1), statusMessage.c_str());
        ImGui::Separator();
        
        if (ImGui::BeginTabBar("AuthTabs"))
        {
            if (ImGui::BeginTabItem(skCrypt("Login").decrypt().c_str()))
            {
                ImGui::Text(skCrypt("Username:").decrypt().c_str());
                ImGui::InputText("##username", usernameBuffer, sizeof(usernameBuffer));
                
                ImGui::Text(skCrypt("Password:").decrypt().c_str());
                ImGui::InputText("##password", passwordBuffer, sizeof(passwordBuffer), ImGuiInputTextFlags_Password);
                
                if (ImGui::Button(skCrypt("Login").decrypt().c_str(), ImVec2(100, 30)) && !isProcessing)
                {
                    std::thread([this]() {
                        Login(usernameBuffer, passwordBuffer);
                    }).detach();
                }
                
                ImGui::SameLine();
                if (ImGui::Button(skCrypt("Web Login").decrypt().c_str(), ImVec2(100, 30)) && !isProcessing)
                {
                    std::thread([this]() {
                        WebLogin();
                    }).detach();
                }
                
                ImGui::EndTabItem();
            }
            
            if (ImGui::BeginTabItem(skCrypt("Register").decrypt().c_str()))
            {
                ImGui::Text(skCrypt("Username:").decrypt().c_str());
                ImGui::InputText("##reg_username", usernameBuffer, sizeof(usernameBuffer));
                
                ImGui::Text(skCrypt("Password:").decrypt().c_str());
                ImGui::InputText("##reg_password", passwordBuffer, sizeof(passwordBuffer), ImGuiInputTextFlags_Password);
                
                ImGui::Text(skCrypt("License Key:").decrypt().c_str());
                ImGui::InputText("##reg_key", keyBuffer, sizeof(keyBuffer));
                
                if (ImGui::Button(skCrypt("Register").decrypt().c_str(), ImVec2(100, 30)) && !isProcessing)
                {
                    std::thread([this]() {
                        Register(usernameBuffer, passwordBuffer, keyBuffer);
                    }).detach();
                }
                
                ImGui::EndTabItem();
            }
            
            if (ImGui::BeginTabItem(skCrypt("License Only").decrypt().c_str()))
            {
                ImGui::Text(skCrypt("License Key:").decrypt().c_str());
                ImGui::InputText("##license_key", keyBuffer, sizeof(keyBuffer));
                
                if (ImGui::Button(skCrypt("Authenticate").decrypt().c_str(), ImVec2(100, 30)) && !isProcessing)
                {
                    std::thread([this]() {
                        LicenseAuth(keyBuffer);
                    }).detach();
                }
                
                ImGui::EndTabItem();
            }
            
            if (ImGui::BeginTabItem(skCrypt("Upgrade").decrypt().c_str()))
            {
                ImGui::Text(skCrypt("Username:").decrypt().c_str());
                ImGui::InputText("##upgrade_username", upgradeUsernameBuffer, sizeof(upgradeUsernameBuffer));
                
                ImGui::Text(skCrypt("License Key:").decrypt().c_str());
                ImGui::InputText("##upgrade_key", upgradeKeyBuffer, sizeof(upgradeKeyBuffer));
                
                if (ImGui::Button(skCrypt("Upgrade Account").decrypt().c_str(), ImVec2(120, 30)) && !isProcessing)
                {
                    std::thread([this]() {
                        Upgrade(upgradeUsernameBuffer, upgradeKeyBuffer);
                    }).detach();
                }
                
                ImGui::EndTabItem();
            }
            
            ImGui::EndTabBar();
        }
        
        // Application info section
        if (currentState >= AuthState::Initialized)
        {
            ImGui::Separator();
            ImGui::Text(skCrypt("Application Information:").decrypt().c_str());
            ImGui::Text((skCrypt("App: ").decrypt() + KeyAuthConfig::name).c_str());
            ImGui::Text((skCrypt("Version: ").decrypt() + KeyAuthConfig::version).c_str());
            
            if (KeyAuthApp && KeyAuthApp->response.success)
            {
                ImGui::Text((skCrypt("Users: ").decrypt() + KeyAuthApp->app_data.numUsers).c_str());
                ImGui::Text((skCrypt("Online: ").decrypt() + KeyAuthApp->app_data.numOnlineUsers).c_str());
            }
        }
    }
    ImGui::End();
}

void KeyAuthManager::GetChatMessages(const std::string& channel)
{
    if (currentState != AuthState::LoggedIn) return;
    KeyAuthApp->chatget(channel);
}

bool KeyAuthManager::SendChatMessage(const std::string& channel, const std::string& message)
{
    if (currentState != AuthState::LoggedIn) return false;
    return KeyAuthApp->chatsend(channel, message);
}

std::string KeyAuthManager::GetLastError()
{
    if (!KeyAuthApp) return "KeyAuth not initialized";
    return KeyAuthApp->response.message;
}

void KeyAuthManager::SetStatus(const std::string& message)
{
    statusMessage = message;
}

bool KeyAuthManager::HasError()
{
    return !KeyAuthApp || !KeyAuthApp->response.success;
}

// Utility functions
std::string FormatTime(const std::string& timestamp)
{
    // Simple timestamp formatting
    return timestamp; // Could be enhanced with proper time formatting
}

bool ValidateCredentials(const std::string& username, const std::string& password)
{
    return !username.empty() && !password.empty() && 
           username.length() >= 3 && password.length() >= 6;
}

bool ValidateLicenseKey(const std::string& key)
{
    return !key.empty() && key.length() >= 10;
}

// Security implementation
namespace Security
{
    void InitializeAntiDebug()
    {
        // Basic anti-debug measures
        #ifdef _WIN32
        if (IsDebuggerPresent())
        {
            log(skCrypt("Debugger detected!").decrypt(), 2);
            ExitProcess(0);
        }
        #endif
    }
    
    void PerformIntegrityCheck()
    {
        // Perform basic integrity checks
        // This would be enhanced in a production environment
    }
    
    bool DetectVirtualMachine()
    {
        // Basic VM detection
        return false; // Simplified for this example
    }
    
    bool DetectDebugger()
    {
        #ifdef _WIN32
        return IsDebuggerPresent();
        #else
        return false;
        #endif
    }
    
    void SecureMemoryWipe(void* ptr, size_t size)
    {
        volatile char* p = (volatile char*)ptr;
        while (size--) *p++ = 0;
    }
}

// Obfuscation implementation
namespace Obfuscation
{
    void InitializeObfuscation()
    {
        // Initialize obfuscation systems
        // This would use advanced obfuscation in production
    }
    
    std::string ObfuscateString(const std::string& input)
    {
        // Simple obfuscation for example
        return input;
    }
    
    std::string DecryptString(const std::string& encrypted)
    {
        // Simple decryption for example
        return encrypted;
    }
}

// Global functions for easy access
void ShowKeyAuthLogin()
{
    g_KeyAuthManager.RenderAuthWindow();
}

bool ProcessKeyAuthAuth()
{
    if (!g_KeyAuthManager.IsInitialized())
    {
        return g_KeyAuthManager.Initialize();
    }
    return g_KeyAuthManager.IsLoggedIn();
}

void RenderKeyAuthGUI()
{
    g_KeyAuthManager.RenderAuthWindow();
}