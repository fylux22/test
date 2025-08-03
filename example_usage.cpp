#include "enhanced_offsets.hpp"
#include <iostream>

int main() {
    std::cout << "=== Enhanced Roblox Offset Updater Example ===" << std::endl;
    
    // Check current Roblox version vs expected
    offsets::checkversion();
    
    std::cout << "\n=== Updating Offsets ===" << std::endl;
    
    // Attempt to update offsets with retry mechanism
    if (offsets::autoupdate_with_retry(3, true)) {
        std::cout << "\n [+] Offset update completed successfully!" << std::endl;
        
        // Example of using some updated offsets
        std::cout << "\n=== Sample Offset Values ===" << std::endl;
        std::cout << "LocalPlayer: 0x" << std::hex << offsets::LocalPlayer << std::endl;
        std::cout << "WalkSpeed: 0x" << std::hex << offsets::WalkSpeed << std::endl;
        std::cout << "Health: 0x" << std::hex << offsets::Health << std::endl;
        std::cout << "Position: 0x" << std::hex << offsets::Position << std::endl;
        std::cout << "Camera: 0x" << std::hex << offsets::Camera << std::endl;
        
    } else {
        std::cout << "\n [-] Failed to update offsets!" << std::endl;
        
        // Display errors
        auto errors = offsets::GetUpdateErrors();
        if (!errors.empty()) {
            std::cout << "\nErrors encountered:" << std::endl;
            for (const auto& error : errors) {
                std::cout << " - " << error << std::endl;
            }
        }
    }
    
    std::cout << "\n=== Status Information ===" << std::endl;
    offsets::PrintUpdateStatus();
    
    // Example of silent update (for use in production code)
    std::cout << "\n=== Silent Update Example ===" << std::endl;
    bool success = offsets::autoupdate(false); // verbose = false
    std::cout << "Silent update result: " << (success ? "SUCCESS" : "FAILED") << std::endl;
    
    return 0;
}