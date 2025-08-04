# Flux Ware V2 - Complete Project Structure

This document contains the complete file structure and contents for the enhanced auto parry external.

## Directory Structure
```
FluxWareV2/
├── Auth/
│   └── keyauth_integration.h
├── Caches/
│   ├── playercache.h
│   ├── playerobjectscache.h
│   └── TPHandler.h
├── Hacks/
│   ├── aimbot.h
│   ├── autoparry.h (ENHANCED)
│   ├── AnimationDetection.h (NEW)
│   ├── esp.h
│   └── misc.h
├── Memory/
│   ├── MemoryManager.h
│   ├── DriverIntegration.h (NEW)
│   └── MemCodeLoader.h (NEW)
├── Offsets/
│   └── AutoOffsets.h (NEW)
├── Renderer/
│   ├── renderer.h
│   ├── W2S.h
│   └── imgui/ (folder)
├── SDK/
│   └── SDK.h
├── Utils/
│   ├── colors.h
│   ├── console.h
│   └── ObfuscatedKeyMapper.h (NEW)
├── kdmapper/ (downloaded files)
├── memloader/ (downloaded files)
├── rickowens/ (downloaded files)
├── main.cpp (ENHANCED)
├── globals.h
├── options.h (ENHANCED)
├── build.bat (NEW)
├── package.bat (NEW)
├── README.md (NEW)
├── LICENSE (NEW)
├── .gitignore (NEW)
└── source_stackz.sln
```

## Key Files Created/Modified:

### NEW FILES:
1. Memory/DriverIntegration.h - RickOwens driver integration
2. Memory/MemCodeLoader.h - Memory code loading system
3. Utils/ObfuscatedKeyMapper.h - Stealth input system
4. Hacks/AnimationDetection.h - Animation detection engine
5. Offsets/AutoOffsets.h - Auto offset updating system
6. build.bat - Professional build system
7. package.bat - GitHub packaging script
8. README.md - Comprehensive documentation
9. LICENSE - MIT license with disclaimer
10. .gitignore - Git ignore file

### ENHANCED FILES:
1. main.cpp - Integrated all new systems
2. options.h - Added comprehensive auto parry settings
3. Hacks/autoparry.h - Enhanced with animation detection and obfuscated input
4. Auth/keyauth_integration.h - Updated with provided credentials

## Download Instructions:
1. Create the directory structure above
2. Copy each file content from the respective sections
3. Download the external components (kdmapper, memloader, rickowens) from the provided URLs
4. Run build.bat to compile everything