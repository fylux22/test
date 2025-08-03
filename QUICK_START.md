# Flux Ware - Quick Start Guide

## Your Updated Credentials
✅ **App Name**: "Flux Ware"  
✅ **Owner ID**: "pEdaaKQNmZ"  
✅ **Version**: "1.0"  
✅ **URL**: "https://keyauth.win/api/1.3/"

## Files Updated With Your Credentials:
- `Auth/keyauth_integration.h` - Updated app name to "Flux Ware"
- `keyauth_example_main.cpp` - Complete standalone example with your creds

## Build Instructions:

### On Windows (Recommended):
1. Install MinGW-w64 or use Visual Studio Build Tools
2. Run: `build.bat` (for full project)
3. Or run: `build_keyauth_example.bat` (for simple KeyAuth test)

### On Linux (Cross-compile to Windows):
1. Install MinGW: `sudo apt install mingw-w64 g++-mingw-w64`
2. Run: `./build.sh` (for full project)
3. Or run: `./build_keyauth_example.sh` (for simple KeyAuth test)

## Windows 11 24H2 Compatibility:
✅ **Full Windows 11 24H2 support built-in**  
✅ **Static linking** - no DLL dependencies  
✅ **Modern Windows APIs** enabled  
✅ **Enhanced security features** supported  

## Output:
- Executable: `build/FluxWare_V1.exe` or `build/KeyAuth_Example.exe`
- ZIP Package: Automatically created in build folder

## Test Your KeyAuth Integration:
1. Build the KeyAuth example first: `build_keyauth_example.bat`
2. Run `build/KeyAuth_Example.exe`
3. Test login/license functionality
4. If working, build full project: `build.bat`

## Package Contents:
- ✅ Complete source code
- ✅ Build scripts (Windows .bat & Linux .sh)
- ✅ KeyAuth library with Windows .lib files
- ✅ Updated with your credentials
- ✅ Windows 11 24H2 compatibility
- ✅ Documentation

## Need Help?
- Check `README_BUILD.md` for detailed requirements
- All Windows libraries (.lib files) included
- Build scripts configured for your credentials