# Roblox Auto Parry System

A Roblox external tool with advanced auto parry functionality for competitive gameplay.

## Features

### 🛡️ Auto Parry System
- **Intelligent Animation Detection**: Detects M1/M2 and ability attack animations from nearby players
- **Configurable Range**: Set detection range in studs (5-50 range)
- **Timing Controls**: 
  - Range delay time (0-1 seconds) - delay before parrying after threat detection
  - Hold time (0.1-2 seconds) - how long to hold the parry key
- **Visual Feedback**: Real-time threat detection and parry status indicators
- **Customizable Parry Key**: Set any key for parrying (default: Space)

### 👁️ ESP (Enhanced Player Visualization)
- Box ESP with customizable colors and fill
- Skeleton ESP for full body tracking  
- Name and distance display
- Health bars
- 3D ESP boxes
- Head circle indicators
- Tracers with multiple start positions
- Team check support

### 🎯 Camera Controls
- FOV adjustment (1-120)
- Improved visibility options

### ⚙️ Configuration System
- Save and load custom configurations
- JSON-based config files
- Multiple profile support

## Animation Database

The system includes a comprehensive database of attack animations covering:
- **M1 Attacks**: Fists, Trained Fists, Void Hands, BL, Spire, Cutlass, Meowmere
- **Ability Attacks**: Witch Doctor, Daemon Smith, Monster abilities
- **Special Moves**: Res, Shikai, Volt moves and other special abilities

## Installation

1. Extract all files to a folder
2. Ensure you have the `fonts` folder in the same directory
3. Run the executable
4. Launch Roblox
5. The tool will automatically attach when Roblox is detected

## Usage

### Auto Parry Setup
1. Open the menu (default key varies)
2. Navigate to "Auto Parry" tab
3. Enable "Auto Parry Enabled"
4. Configure your settings:
   - **Range Delay**: Time to wait before parrying (prevents spam)
   - **Hold Time**: Duration to hold parry key
   - **Detection Range**: Distance to scan for threats
   - **Parry Key**: Key to use for parrying

### Configuration
- Use the "Configurations" tab to save/load settings
- Create multiple profiles for different scenarios
- Configs are saved as JSON files

## Settings Explanation

### Auto Parry Settings
- **Enabled**: Master toggle for auto parry system
- **Range Delay**: Prevents instant parrying, adds realistic timing
- **Hold Time**: Duration of parry action - adjust based on game mechanics
- **Detection Range**: How far to scan for threats (affects performance)
- **Show Status**: Display threat detection and parry status on screen

## Technical Features

- **External Memory Reading**: Safe external approach
- **Animation Tracking**: Real-time monitoring of player animations
- **Smart Threat Detection**: Only parries actual attack animations
- **Performance Optimized**: Efficient scanning and detection algorithms
- **Anti-Detection**: External approach reduces detection risk

## Safety Notes

- This is an external tool that reads game memory
- Use responsibly and in accordance with game rules
- The tool includes safety measures to prevent false positives
- Recommended for practice and training scenarios

## Troubleshooting

### Common Issues
1. **Tool not attaching**: Ensure Roblox is running and visible
2. **No threat detection**: Check detection range and ensure players are performing attacks
3. **Parry not working**: Verify parry key setting and key bindings
4. **Performance issues**: Reduce detection range or disable visual feedback

### Requirements
- Windows 10/11
- DirectX 11 compatible graphics
- Administrative privileges (for memory access)

## Credits

- Original base by @Kam546 & @redstoneprojrjr  
- Animation database compiled from game data
- Auto parry system implementation

## Disclaimer

This tool is for educational and practice purposes. Use responsibly and respect game terms of service.