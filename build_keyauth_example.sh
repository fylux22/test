#!/bin/bash
echo "Building KeyAuth Example..."
echo

# Create build directory
mkdir -p build

# Build with MinGW x64 - Windows Libraries
x86_64-w64-mingw32-g++ -std=c++17 -O2 -DNDEBUG -DCURL_STATICLIB \
    -I. -Ikeyauth-cpp-library-1.3API-main -Ikeyauth-cpp-library-1.3API-main/curl -Ikeyauth-cpp-library-1.3API-main/libsodium -Ikeyauth-cpp-library-1.3API-main/nlohmann \
    -static-libgcc -static-libstdc++ \
    -Wl,--subsystem,console \
    keyauth_example_main.cpp \
    auth.cpp \
    utils.cpp \
    -Lkeyauth-cpp-library-1.3API-main/curl -Lkeyauth-cpp-library-1.3API-main/libsodium \
    keyauth-cpp-library-1.3API-main/curl/libcurl.lib \
    keyauth-cpp-library-1.3API-main/libsodium/libsodium.lib \
    keyauth-cpp-library-1.3API-main/curl/zlib.lib \
    -lws2_32 -lcrypt32 -lwininet -luser32 -lkernel32 -ladvapi32 -lnormaliz -lwldap32 \
    -o build/KeyAuth_Example.exe

if [ $? -eq 0 ]; then
    echo
    echo "Build successful! Executable created: build/KeyAuth_Example.exe"
    echo
    echo "Creating release package..."
    cd build
    if [ -f "KeyAuth_Example.zip" ]; then
        rm "KeyAuth_Example.zip"
    fi
    zip -9 "KeyAuth_Example.zip" KeyAuth_Example.exe
    echo "Package created: KeyAuth_Example.zip"
    cd ..
else
    echo
    echo "Build failed!"
fi