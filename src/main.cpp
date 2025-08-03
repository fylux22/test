#include <iostream>
#include <Windows.h>
#include <vector>
#include <string>
#include <memory>

// Include our custom headers
#include "../include/skCrypt.hpp"
#include "../keyauth/auth.hpp"
#include "../keyauth/utils.hpp"
#include "../drivers/kdmapper/include/kdmapper.hpp"
#include "../drivers/kdmapper/include/intel_driver.hpp"
#include "load.hpp"

// Forward declarations
void ShowBanner();
bool InitializeKeyAuth();
bool LoadDriver();
void ShowUserMenu();
bool HandleDriverLoading();
bool HandleMemoryExecution();

// Global KeyAuth instance
std::unique_ptr<api> KeyAuthApp;

int main()
{
    SetConsoleTitle(skCrypt("Fylux22's Application"));
    ShowBanner();

    // Initialize KeyAuth
    if (!InitializeKeyAuth()) {
        std::cout << skCrypt("\n[!] Failed to initialize KeyAuth\n");
        system("pause");
        return -1;
    }

    // Show user menu
    ShowUserMenu();

    return 0;
}

void ShowBanner()
{
    std::cout << skCrypt(R"(
 ______   _                 ___   ___        _                 
|  ____| | |               |__ \ |__ \      (_)                
| |__    | | _   _  __  __     ) |   ) |      _   ___           
|  __|   | || | | | \ \/ /    / /   / /      | | / __|          
| |      | || |_| |  >  <    / /_  / /_      | | \__ \          
|_|      |_| \__, | /_/\_\  |____||____|     |_| |___/          
              __/ |                                             
             |___/                                              
        Advanced Driver & Memory Loader with KeyAuth
)");
    std::cout << skCrypt("\n[+] Starting application...\n");
}

bool InitializeKeyAuth()
{
    std::string name = skCrypt("Fylux22's Application").decrypt();
    std::string ownerid = skCrypt("pEdaaKQNmZ").decrypt();
    std::string version = skCrypt("1.0").decrypt();
    std::string url = skCrypt("https://keyauth.win/api/1.3/").decrypt();
    std::string path = skCrypt("").decrypt();

    try {
        KeyAuthApp = std::make_unique<api>(name, ownerid, "", version, url);
        
        std::cout << skCrypt("\n[+] Initializing KeyAuth...\n");
        KeyAuthApp->init();
        
        if (!KeyAuthApp->response.success) {
            std::cout << skCrypt("\n[!] KeyAuth Error: ") << KeyAuthApp->response.message << std::endl;
            return false;
        }

        std::cout << skCrypt("\n[+] KeyAuth initialized successfully!\n");
        std::cout << skCrypt("[+] Application: ") << name << std::endl;
        std::cout << skCrypt("[+] Version: ") << version << std::endl;

        return true;
    }
    catch (const std::exception& e) {
        std::cout << skCrypt("\n[!] Exception during KeyAuth initialization: ") << e.what() << std::endl;
        return false;
    }
}

void ShowUserMenu()
{
    std::string choice;
    bool authenticated = false;

    while (true) {
        std::cout << skCrypt("\n================ MENU ================\n");
        
        if (!authenticated) {
            std::cout << skCrypt("[1] Login with Username/Password\n");
            std::cout << skCrypt("[2] Register Account\n");
            std::cout << skCrypt("[3] Login with License Key\n");
        } else {
            std::cout << skCrypt("[4] Load Driver via kdmapper\n");
            std::cout << skCrypt("[5] Execute Memory Loader\n");
            std::cout << skCrypt("[6] Show User Information\n");
            std::cout << skCrypt("[7] Application Variables\n");
        }
        
        std::cout << skCrypt("[0] Exit\n");
        std::cout << skCrypt("=======================================\n");
        std::cout << skCrypt("Enter choice: ");
        
        std::getline(std::cin, choice);

        if (choice == "0") {
            std::cout << skCrypt("\n[+] Goodbye!\n");
            break;
        }
        else if (choice == "1" && !authenticated) {
            std::string username, password;
            std::cout << skCrypt("\nEnter username: ");
            std::getline(std::cin, username);
            std::cout << skCrypt("Enter password: ");
            std::getline(std::cin, password);

            KeyAuthApp->login(username, password);
            if (KeyAuthApp->response.success) {
                std::cout << skCrypt("\n[+] Login successful!\n");
                authenticated = true;
            } else {
                std::cout << skCrypt("\n[!] Login failed: ") << KeyAuthApp->response.message << std::endl;
            }
        }
        else if (choice == "2" && !authenticated) {
            std::string username, password, license;
            std::cout << skCrypt("\nEnter username: ");
            std::getline(std::cin, username);
            std::cout << skCrypt("Enter password: ");
            std::getline(std::cin, password);
            std::cout << skCrypt("Enter license key: ");
            std::getline(std::cin, license);

            KeyAuthApp->regstr(username, password, license);
            if (KeyAuthApp->response.success) {
                std::cout << skCrypt("\n[+] Registration successful!\n");
                authenticated = true;
            } else {
                std::cout << skCrypt("\n[!] Registration failed: ") << KeyAuthApp->response.message << std::endl;
            }
        }
        else if (choice == "3" && !authenticated) {
            std::string license;
            std::cout << skCrypt("\nEnter license key: ");
            std::getline(std::cin, license);

            KeyAuthApp->license(license);
            if (KeyAuthApp->response.success) {
                std::cout << skCrypt("\n[+] License authentication successful!\n");
                authenticated = true;
            } else {
                std::cout << skCrypt("\n[!] License authentication failed: ") << KeyAuthApp->response.message << std::endl;
            }
        }
        else if (choice == "4" && authenticated) {
            HandleDriverLoading();
        }
        else if (choice == "5" && authenticated) {
            HandleMemoryExecution();
        }
        else if (choice == "6" && authenticated) {
            std::cout << skCrypt("\n========== USER INFORMATION ==========\n");
            std::cout << skCrypt("Username: ") << KeyAuthApp->response.username << std::endl;
            std::cout << skCrypt("Hardware ID: ") << KeyAuthApp->user_data.hwid << std::endl;
            std::cout << skCrypt("IP Address: ") << KeyAuthApp->user_data.ip << std::endl;
            std::cout << skCrypt("Create Date: ") << KeyAuthApp->user_data.createdate << std::endl;
            std::cout << skCrypt("Last Login: ") << KeyAuthApp->user_data.lastlogin << std::endl;
            
            if (!KeyAuthApp->user_data.subscriptions.empty()) {
                std::cout << skCrypt("Subscriptions: ");
                for (const auto& sub : KeyAuthApp->user_data.subscriptions) {
                    std::cout << sub << " ";
                }
                std::cout << std::endl;
                std::cout << skCrypt("Expiry: ") << KeyAuthApp->user_data.expiry << std::endl;
            }
            std::cout << skCrypt("======================================\n");
        }
        else if (choice == "7" && authenticated) {
            std::cout << skCrypt("\n[+] Fetching application variables...\n");
            try {
                std::string status = KeyAuthApp->var("status");
                std::cout << skCrypt("Status: ") << status << std::endl;
            } catch (...) {
                std::cout << skCrypt("[!] Error fetching variables\n");
            }
        }
        else {
            std::cout << skCrypt("\n[!] Invalid choice or not authenticated!\n");
        }
    }
}

bool HandleDriverLoading()
{
    std::cout << skCrypt("\n========== DRIVER LOADING ==========\n");
    std::cout << skCrypt("[+] Initializing kdmapper...\n");
    
    try {
        // Initialize Intel driver
        HANDLE device_handle = intel_driver::Load();
        if (device_handle == INVALID_HANDLE_VALUE) {
            std::cout << skCrypt("[!] Failed to load vulnerable driver\n");
            return false;
        }

        std::cout << skCrypt("[+] Vulnerable driver loaded successfully\n");
        std::cout << skCrypt("[!] Note: This is for educational purposes only\n");
        std::cout << skCrypt("[!] Ensure you have a valid driver file to load\n");

        // Clean up
        intel_driver::Unload(device_handle);
        std::cout << skCrypt("[+] Driver unloaded\n");
        
        // Log activity
        KeyAuthApp->log("Driver loading functionality accessed");
        
        return true;
    }
    catch (const std::exception& e) {
        std::cout << skCrypt("[!] Exception during driver loading: ") << e.what() << std::endl;
        return false;
    }
}

bool HandleMemoryExecution()
{
    std::cout << skCrypt("\n========== MEMORY EXECUTION ==========\n");
    std::cout << skCrypt("[+] Initializing memory loader...\n");
    
    try {
        // Note: The actual bytes would need to be embedded or loaded
        std::cout << skCrypt("[!] Memory loader ready\n");
        std::cout << skCrypt("[!] Note: No payload embedded for security\n");
        std::cout << skCrypt("[!] Replace EXEbytes with your actual payload\n");
        
        // Here you would call loadbytes() if you had actual bytes to load
        // loadbytes();
        
        // Log activity
        KeyAuthApp->log("Memory execution functionality accessed");
        
        return true;
    }
    catch (const std::exception& e) {
        std::cout << skCrypt("[!] Exception during memory execution: ") << e.what() << std::endl;
        return false;
    }
}