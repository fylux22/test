# Auto Larry External - ESP + Parry

A Roblox external cheat with ESP and auto parry functionality.

## Features

### ESP (Visuals)
- Box ESP with customizable colors
- Skeleton ESP
- Name ESP with distance
- Health bars
- 3D ESP
- Head circles
- Tracers
- Team check support

### Auto Parry
- Hold time control (0.01s - 5.0s)
- Delay time control (0.001s - 1.0s)
- Parry window control (0.01s - 1.0s)
- Auto parry mode
- Customizable parry key (default: F)

### Misc
- Walk speed modification
- Jump power modification
- FOV modification
- Configuration save/load system

## Building

### Requirements
- Visual Studio 2019 or later
- Windows 10/11
- DirectX 11 compatible graphics card

### Build Steps
1. Open Command Prompt as Administrator
2. Navigate to the project directory
3. Run: `build.bat`
4. Or manually run: `msbuild source_stackz.sln /p:Configuration=Release /p:Platform=x64`

## Usage

1. **Start Roblox** and join a game
2. **Run the executable** as Administrator: `x64\Release\source_stackz.exe`
3. **Press INSERT** to toggle the menu
4. **Configure settings** in the GUI:
   - Visuals tab: Configure ESP settings
   - Parry tab: Configure auto parry timing
   - Misc tab: Configure movement settings
   - Configurations tab: Save/load your settings

## Controls

- **INSERT**: Toggle menu
- **F** (default): Parry key (customizable)
- **Mouse**: Navigate GUI

## Parry Timing

- **Hold Time**: How long you must hold the parry key before it activates
- **Delay Time**: Minimum time between parry attempts
- **Parry Window**: How long the parry key is held when auto parry triggers

## Safety Notes

- Run as Administrator for proper functionality
- Use at your own risk
- May be detected by anti-cheat systems
- Keep the executable and fonts folder together

## Files Structure

```
├── main.cpp                 # Main entry point
├── options.h               # Configuration options
├── globals.h               # Global variables
├── Renderer/
│   ├── renderer.h          # GUI and rendering
│   └── W2S.h              # World to screen conversion
├── Hacks/
│   ├── esp.h              # ESP functionality
│   ├── parry.h            # Auto parry system
│   └── misc.h             # Miscellaneous features
├── Utils/
│   └── configs.h          # Configuration save/load
├── Caches/                # Player caching system
├── Memory/                # Memory management
├── fonts/                 # Required font files
└── x64/Release/           # Compiled executable
```

## Troubleshooting

1. **"Roblox not found"**: Make sure Roblox is running
2. **"Failed to attach"**: Run as Administrator
3. **GUI not showing**: Press INSERT to toggle
4. **Build errors**: Install Visual Studio 2019+ with C++ workload

## Disclaimer

This software is for educational purposes only. Use at your own risk. The authors are not responsible for any consequences of using this software.