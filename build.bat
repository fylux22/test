@echo off
echo Building Flux Ware V1...
echo.

REM Create build directory
if not exist "build" mkdir build

REM Build with MinGW x64
x86_64-w64-mingw32-g++ -std=c++17 -O2 -DNDEBUG ^
    -I. -IRenderer/imgui -Ikeyauth-cpp-library-1.3API-main ^
    -static-libgcc -static-libstdc++ ^
    -Wl,--subsystem,windows ^
    main.cpp ^
    Hacks/misc.cpp ^
    Auth/keyauth_integration.cpp ^
    Caches/playercache.cpp ^
    Caches/playerobjectscache.cpp ^
    Caches/TPHandler.cpp ^
    Memory/MemoryManager.cpp ^
    SDK/sdk.cpp ^
    Utils/colors.cpp ^
    Utils/console.cpp ^
    Renderer/renderer.cpp ^
    Renderer/W2S.cpp ^
    auth.cpp ^
    utils.cpp ^
    -lgdi32 -luser32 -lkernel32 -ld3d11 -ldxgi -ldwmapi ^
    -o build/FluxWare_V1.exe

if %ERRORLEVEL% == 0 (
    echo.
    echo Build successful! Executable created: build/FluxWare_V1.exe
    echo.
    echo Creating release package...
    cd build
    if exist "FluxWare_V1.zip" del "FluxWare_V1.zip"
    tar -czf "Flux Ware V1.zip" FluxWare_V1.exe
    echo Package created: Flux Ware V1.zip
) else (
    echo.
    echo Build failed!
    pause
)

pause