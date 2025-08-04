#pragma once

#include <iostream>
#include <string>
#include <thread>
#include <chrono>
#include "../skStr.h"

// KeyAuth integration with proper credentials as provided
namespace KeyAuthConfig
{
    inline std::string name = skCrypt("Flux Ware").decrypt(); // App name
    inline std::string ownerid = skCrypt("pEdaaKQNmZ").decrypt(); // Account ID
    inline std::string version = skCrypt("1.0").decrypt(); // Application version
    inline std::string url = skCrypt("https://keyauth.win/api/1.3/").decrypt(); // API URL
    inline std::string path = skCrypt("").decrypt(); // Optional path
}

// Forward declaration for KeyAuth API class
class api;

// Global KeyAuth instance
extern api* KeyAuthApp;

// Authentication states
enum class AuthState
{
    NotInitialized,
    Initialized,
    LoggedIn,
    Failed
};

class KeyAuthManager
{
private:
    AuthState currentState = AuthState::NotInitialized;
    std::string currentUser;
    bool autoLoginMode = false;
    std::string licenseKey;
    
    // GUI state variables
    bool showAuthWindow = true;
    bool showRegisterWindow = false;
    bool showUpgradeWindow = false;
    char usernameBuffer[256] = "";
    char passwordBuffer[256] = "";
    char keyBuffer[256] = "";
    char upgradeUsernameBuffer[256] = "";
    char upgradeKeyBuffer[256] = "";
    
    std::string statusMessage = "";
    bool isProcessing = false;

public:
    KeyAuthManager();
    ~KeyAuthManager();
    
    // Core authentication functions
    bool Initialize();
    bool Login(const std::string& username, const std::string& password);
    bool Register(const std::string& username, const std::string& password, const std::string& key);
    bool LicenseAuth(const std::string& key);
    bool Upgrade(const std::string& username, const std::string& key);
    bool WebLogin();
    
    // Utility functions
    void Logout();
    bool IsLoggedIn() const { return currentState == AuthState::LoggedIn; }
    bool IsInitialized() const { return currentState != AuthState::NotInitialized; }
    std::string GetCurrentUser() const { return currentUser; }
    
    // User data access
    std::string GetUserIP();
    std::string GetUserHWID();
    std::string GetCreateDate();
    std::string GetLastLogin();
    std::string GetSubscriptions();
    std::string GetExpiry();
    bool HasSubscription(const std::string& subName);
    
    // Application data
    void FetchAppStats();
    std::string GetAppUsers();
    std::string GetAppOnlineUsers();
    std::string GetAppKeys();
    std::string GetAppVersion();
    std::string GetCustomerPanelLink();
    
    // Security functions
    bool CheckBlacklist();
    void BanUser(const std::string& reason = "");
    void LogEvent(const std::string& message);
    
    // Variables
    std::string GetVariable(const std::string& varName);
    std::string GetUserVariable(const std::string& varName);
    void SetUserVariable(const std::string& varName, const std::string& value);
    
    // Files and webhooks
    std::vector<uint8_t> DownloadFile(const std::string& fileId);
    std::string SendWebhook(const std::string& webhookId, const std::string& params);
    
    // GUI functions
    void RenderAuthWindow();
    void ProcessAuthentication();
    
    // Chat functions
    void GetChatMessages(const std::string& channel);
    bool SendChatMessage(const std::string& channel, const std::string& message);
    
    // Status and error handling
    std::string GetLastError();
    void SetStatus(const std::string& message);
    bool HasError();
};

// Authentication window functions
void ShowKeyAuthLogin();
bool ProcessKeyAuthAuth();
void RenderKeyAuthGUI();

// Utility functions for KeyAuth integration
std::string FormatTime(const std::string& timestamp);
bool ValidateCredentials(const std::string& username, const std::string& password);
bool ValidateLicenseKey(const std::string& key);

// Security practices implementation
namespace Security
{
    void InitializeAntiDebug();
    void PerformIntegrityCheck();
    bool DetectVirtualMachine();
    bool DetectDebugger();
    void SecureMemoryWipe(void* ptr, size_t size);
}

// Obfuscation helpers
namespace Obfuscation
{
    std::string ObfuscateString(const std::string& input);
    void InitializeObfuscation();
    std::string DecryptString(const std::string& encrypted);
}