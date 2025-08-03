# Flux Ware Build Requirements - Windows 11 24H2 Compatible

## Build System Requirements

### 1. **Windows 11 24H2 Compatibility**
- **WINVER=0x0A00** - Windows 10/11 target
- **_WIN32_WINNT=0x0A00** - Windows 10/11 API level
- **NTDDI_VERSION=0x0A00000F** - Windows 11 24H2 specific version
- **OS Version Targeting**: Major 10, Minor 0 (Windows 11 uses internal version 10.0)

### 2. **Required Libraries (Windows .lib files)**
- **libcurl.lib** - HTTP/HTTPS requests to KeyAuth API
- **libsodium.lib** - Cryptographic operations 
- **zlib.lib** - Compression support for curl
- **Windows System Libraries**:
  - ws2_32.lib (Winsock2)
  - crypt32.lib (Cryptography API)
  - wininet.lib (Internet API)
  - user32.lib (User Interface)
  - kernel32.lib (Core Windows)
  - advapi32.lib (Advanced API)
  - normaliz.lib (Unicode normalization)
  - wldap32.lib (LDAP)
  - gdi32.lib (Graphics)
  - d3d11.lib (DirectX 11)
  - dxgi.lib (DirectX Graphics Infrastructure)
  - dwmapi.lib (Desktop Window Manager)

### 3. **Compiler Flags**
- **C++17 Standard** (-std=c++17)
- **Optimization Level 2** (-O2)
- **NDEBUG** for release builds
- **CURL_STATICLIB** for static curl linking
- **Static Runtime** (-static-libgcc -static-libstdc++)

### 4. **Include Directories**
- Main project directory (.)
- Renderer/imgui
- keyauth-cpp-library-1.3API-main
- keyauth-cpp-library-1.3API-main/curl
- keyauth-cpp-library-1.3API-main/libsodium  
- keyauth-cpp-library-1.3API-main/nlohmann

### 5. **Library Directories**
- keyauth-cpp-library-1.3API-main/curl
- keyauth-cpp-library-1.3API-main/libsodium

## Build Scripts

### For KeyAuth Example (Console App):
```batch
build_keyauth_example.bat  # Windows batch
build_keyauth_example.sh   # Linux shell (cross-compile)
```

### For Full Flux Ware (GUI App):
```batch
build.bat                  # Windows batch  
build.sh                   # Linux shell (cross-compile)
```

## Windows 11 24H2 Specific Features Supported:
- Modern Windows API compatibility
- Enhanced security features
- Latest cryptographic standards
- DirectX 11 graphics support
- Desktop Window Manager integration
- Unicode normalization support

## File Structure Requirements:
```
project_root/
├── keyauth-cpp-library-1.3API-main/
│   ├── curl/
│   │   ├── libcurl.lib
│   │   └── zlib.lib
│   ├── libsodium/
│   │   └── libsodium.lib
│   └── nlohmann/
├── Auth/
│   ├── keyauth_integration.h
│   └── keyauth_integration.cpp
├── main.cpp
├── auth.cpp
├── utils.cpp
└── build/ (output directory)
```

## Deployment:
- Executable will be statically linked (no DLL dependencies)
- Compatible with Windows 11 24H2 and newer
- Package as ZIP file for distribution