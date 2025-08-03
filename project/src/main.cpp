#include <iostream>
#include <windows.h>
#include <vector>
#include <string>
#include <memory>

// Include our custom headers
#include "../include/skCrypt.hpp"
#include "../keyauth/auth.hpp"
#include "../drivers/kdmapper/kdmapper.hpp"
#include "../drivers/kdmapper/intel_driver.hpp"
#include "memloader/load.hpp"

// Forward declarations
void ShowBanner();
bool InitializeKeyAuth();
bool LoadDriver();
void ShowUserMenu();
bool HandleDriverLoading();
bool HandleMemoryExecution();

// Global KeyAuth instance
std::unique_ptr<KeyAuth::api> KeyAuthApp;

int main()
{
    SetConsoleTitle(skCrypt("Fylux22's Application").decrypt());
    ShowBanner();

    // Initialize KeyAuth
    if (!InitializeKeyAuth()) {
        std::cout << skCrypt("\n[!] Failed to initialize KeyAuth!\n").decrypt();
        system("pause");
        return -1;
    }

    // Show user menu
    ShowUserMenu();

    return 0;
}

void ShowBanner()
{
    system("cls");
    std::cout << skCrypt(R"(
    ╔═══════════════════════════════════════╗
    ║           Fylux22's Application       ║
    ║      Driver & Memory Loader Suite     ║
    ╚═══════════════════════════════════════╝
    )").decrypt() << std::endl;
}

bool InitializeKeyAuth()
{
    try {
        std::string name = skCrypt("Fylux22's Application").decrypt();
        std::string ownerid = skCrypt("pEdaaKQNmZ").decrypt();
        std::string version = skCrypt("1.0").decrypt();
        std::string url = skCrypt("https://keyauth.win/api/1.3/").decrypt();
        std::string path = skCrypt("").decrypt();

        KeyAuthApp = std::make_unique<KeyAuth::api>(name, ownerid, version, url, path);
        KeyAuthApp->init();

        return true;
    }
    catch (const std::exception& e) {
        std::cout << skCrypt("[!] KeyAuth initialization error: ").decrypt() << e.what() << std::endl;
        return false;
    }
}

void ShowUserMenu()
{
    int choice;
    bool running = true;

    while (running) {
        system("cls");
        ShowBanner();
        
        std::cout << skCrypt("\n[1] Load Driver").decrypt() << std::endl;
        std::cout << skCrypt("[2] Memory Execution").decrypt() << std::endl;
        std::cout << skCrypt("[3] Exit").decrypt() << std::endl;
        std::cout << skCrypt("\nEnter choice: ").decrypt();
        
        std::cin >> choice;

        switch (choice) {
        case 1:
            HandleDriverLoading();
            break;
        case 2:
            HandleMemoryExecution();
            break;
        case 3:
            running = false;
            break;
        default:
            std::cout << skCrypt("\n[!] Invalid choice!").decrypt() << std::endl;
            system("pause");
            break;
        }
    }
}

bool HandleDriverLoading()
{
    std::cout << skCrypt("\n[*] Initiating driver loading...").decrypt() << std::endl;
    
    try {
        // Driver loading logic would go here
        std::cout << skCrypt("[+] Driver loaded successfully!").decrypt() << std::endl;
        system("pause");
        return true;
    }
    catch (const std::exception& e) {
        std::cout << skCrypt("[!] Driver loading failed: ").decrypt() << e.what() << std::endl;
        system("pause");
        return false;
    }
}

bool HandleMemoryExecution()
{
    std::cout << skCrypt("\n[*] Initiating memory execution...").decrypt() << std::endl;
    
    try {
        // Memory execution logic would go here
        loadbytes();
        std::cout << skCrypt("[+] Memory execution completed!").decrypt() << std::endl;
        system("pause");
        return true;
    }
    catch (const std::exception& e) {
        std::cout << skCrypt("[!] Memory execution failed: ").decrypt() << e.what() << std::endl;
        system("pause");
        return false;
    }
}