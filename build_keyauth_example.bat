@echo off
echo Building KeyAuth Example...
echo.

REM Create build directory
if not exist "build" mkdir build

REM Build with MinGW x64
x86_64-w64-mingw32-g++ -std=c++17 -O2 -DNDEBUG ^
    -I. -Ikeyauth-cpp-library-1.3API-main -Ikeyauth-cpp-library-1.3API-main/curl -Ikeyauth-cpp-library-1.3API-main/libsodium -Ikeyauth-cpp-library-1.3API-main/nlohmann ^
    -static-libgcc -static-libstdc++ ^
    -Wl,--subsystem,console ^
    keyauth_example_main.cpp ^
    auth.cpp ^
    utils.cpp ^
    -lws2_32 -lcrypt32 -lwininet -luser32 -lkernel32 -ladvapi32 -lnormaliz -lwldap32 ^
    -o build/KeyAuth_Example.exe

if %ERRORLEVEL% == 0 (
    echo.
    echo Build successful! Executable created: build/KeyAuth_Example.exe
    echo.
    echo Creating release package...
    cd build
    if exist "KeyAuth_Example.zip" del "KeyAuth_Example.zip"
    tar -czf "KeyAuth_Example.zip" KeyAuth_Example.exe
    echo Package created: KeyAuth_Example.zip
) else (
    echo.
    echo Build failed!
    pause
)

pause