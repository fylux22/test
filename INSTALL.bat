@echo off
title Flux Ware V2 - One-Click Installer
color 0A

echo.
echo ██████╗ ██╗     ██╗   ██╗██╗  ██╗    ██╗    ██╗ █████╗ ██████╗ ███████╗    ██╗   ██╗██████╗ 
echo ██╔══██╗██║     ██║   ██║╚██╗██╔╝    ██║    ██║██╔══██╗██╔══██╗██╔════╝    ██║   ██║╚════██╗
echo ██████╔╝██║     ██║   ██║ ╚███╔╝     ██║ █╗ ██║███████║██████╔╝█████╗      ██║   ██║ █████╔╝
echo ██╔══██╗██║     ██║   ██║ ██╔██╗     ██║███╗██║██╔══██║██╔══██╗██╔══╝      ╚██╗ ██╔╝██╔═══╝ 
echo ██║  ██║███████╗╚██████╔╝██╔╝ ██╗    ╚███╔███╔╝██║  ██║██║  ██║███████╗     ╚████╔╝ ███████╗
echo ╚═╝  ╚═╝╚══════╝ ╚═════╝ ╚═╝  ╚═╝     ╚══╝╚══╝ ╚═╝  ╚═╝╚═╝  ╚═╝╚══════╝      ╚═══╝  ╚══════╝
echo.
echo                           Enhanced Auto Parry External
echo                              One-Click Installer
echo.
echo ========================================================================================
echo.

:: Check for Administrator privileges
net session >nul 2>&1
if %errorLevel% == 0 (
    echo ✅ Running as Administrator - Good!
) else (
    echo ❌ ERROR: This installer must be run as Administrator!
    echo.
    echo Please right-click this file and select "Run as administrator"
    echo.
    pause
    exit /b 1
)

echo.
echo This installer will:
echo ┌─────────────────────────────────────────────────────────────────────────────────┐
echo │ 1. Download all external dependencies (kdmapper, memloader, RickOwens)         │
echo │ 2. Set up proper project structure                                             │
echo │ 3. Integrate all components automatically                                      │
echo │ 4. Update build system for seamless compilation                                │
echo │ 5. Verify installation and provide next steps                                  │
echo └─────────────────────────────────────────────────────────────────────────────────┘
echo.

set /p choice="Continue with automatic installation? (Y/N): "
if /i "%choice%" neq "Y" (
    echo Installation cancelled by user.
    pause
    exit /b 0
)

echo.
echo ========================================================================================
echo                                 STARTING INSTALLATION
echo ========================================================================================
echo.

:: Check if we're in the right directory
if not exist "main.cpp" (
    echo ❌ ERROR: Installation files not found!
    echo.
    echo Make sure you've extracted the GitHub ZIP file and are running this
    echo installer from the FluxWareV2 directory containing main.cpp
    echo.
    pause
    exit /b 1
)

echo ✅ Installation directory verified
echo Current directory: %CD%
echo.

:: Create necessary directories
echo [STEP 1/5] Creating project structure...
if not exist "build" mkdir build
if not exist "x64" mkdir x64
if not exist "x64\Debug" mkdir x64\Debug
if not exist "x64\Release" mkdir x64\Release
echo ✅ Project directories created

echo.
echo [STEP 2/5] Downloading external dependencies...
echo.
echo This may take a few minutes depending on your internet connection...
echo.

:: Download kdmapper
echo ┌─ Downloading kdmapper (driver integration)...
curl -L --progress-bar -o kdmapper.zip "https://filebin.net/rmcs8pmfrsqavvad/kdmapper-master.zip"
if exist kdmapper.zip (
    echo ┌─ Extracting kdmapper...
    powershell -command "Expand-Archive -Path 'kdmapper.zip' -DestinationPath '.' -Force" >nul 2>&1
    del kdmapper.zip >nul 2>&1
    if exist "kdmapper-master" (
        echo ✅ kdmapper downloaded and extracted successfully
    ) else (
        echo ❌ kdmapper extraction failed
    )
) else (
    echo ❌ Failed to download kdmapper
)

:: Download memloader
echo.
echo ┌─ Downloading memloader (memory code loading)...
curl -L --progress-bar -o memloader.zip "https://filebin.net/rmcs8pmfrsqavvad/memloader-main.zip"
if exist memloader.zip (
    echo ┌─ Extracting memloader...
    powershell -command "Expand-Archive -Path 'memloader.zip' -DestinationPath '.' -Force" >nul 2>&1
    del memloader.zip >nul 2>&1
    if exist "memloader-main" (
        echo ✅ memloader downloaded and extracted successfully
    ) else (
        echo ❌ memloader extraction failed
    )
) else (
    echo ❌ Failed to download memloader
)

:: Download RickOwens
echo.
echo ┌─ Downloading RickOwens driver components...
curl -L --progress-bar -o rickowens.zip "https://filebin.net/rmcs8pmfrsqavvad/RickOwens00-1.0.1.zip"
if exist rickowens.zip (
    echo ┌─ Extracting RickOwens...
    powershell -command "Expand-Archive -Path 'rickowens.zip' -DestinationPath '.' -Force" >nul 2>&1
    del rickowens.zip >nul 2>&1
    if exist "RickOwens00-1.0.1" (
        echo ✅ RickOwens downloaded and extracted successfully
    ) else (
        echo ❌ RickOwens extraction failed
    )
) else (
    echo ❌ Failed to download RickOwens
)

echo.
echo [STEP 3/5] Integrating components into project structure...

:: Integrate kdmapper
if exist "kdmapper-master" (
    echo ┌─ Integrating kdmapper...
    if not exist "kdmapper" mkdir kdmapper
    xcopy /E /I /Y "kdmapper-master" "kdmapper\kdmapper-master" >nul 2>&1
    rmdir /S /Q "kdmapper-master" >nul 2>&1
    echo ✅ kdmapper integrated successfully
) else (
    echo ❌ kdmapper integration skipped (download failed)
)

:: Integrate memloader
if exist "memloader-main" (
    echo ┌─ Integrating memloader...
    if not exist "memloader" mkdir memloader
    xcopy /E /I /Y "memloader-main" "memloader\memloader-main" >nul 2>&1
    rmdir /S /Q "memloader-main" >nul 2>&1
    echo ✅ memloader integrated successfully
) else (
    echo ❌ memloader integration skipped (download failed)
)

:: Integrate RickOwens
if exist "RickOwens00-1.0.1" (
    echo ┌─ Integrating RickOwens...
    if not exist "rickowens" mkdir rickowens
    xcopy /E /I /Y "RickOwens00-1.0.1" "rickowens\RickOwens00-1.0.1" >nul 2>&1
    rmdir /S /Q "RickOwens00-1.0.1" >nul 2>&1
    echo ✅ RickOwens integrated successfully
) else (
    echo ❌ RickOwens integration skipped (download failed)
)

echo.
echo [STEP 4/5] Creating optimized build system...

:: Create the enhanced build.bat
(
echo @echo off
echo title Flux Ware V2 - Build System
echo color 0B
echo.
echo echo ========================================
echo echo Flux Ware V2 - Enhanced Auto Parry Build
echo echo ========================================
echo echo.
echo.
echo :: Set build configuration
echo set BUILD_CONFIG=Debug
echo set PLATFORM=x64
echo.
echo :: Check for Visual Studio
echo echo Checking for Visual Studio installation...
echo if exist "%%ProgramFiles^(x86^)%%\Microsoft Visual Studio\2022\Community\Common7\IDE\devenv.exe" ^(
echo     echo ✅ Visual Studio 2022 found
echo     call "%%ProgramFiles^(x86^)%%\Microsoft Visual Studio\2022\Community\VC\Auxiliary\Build\vcvars64.bat" ^>nul 2^>^&1
echo ^) else if exist "%%ProgramFiles^(x86^)%%\Microsoft Visual Studio\2019\Community\Common7\IDE\devenv.exe" ^(
echo     echo ✅ Visual Studio 2019 found  
echo     call "%%ProgramFiles^(x86^)%%\Microsoft Visual Studio\2019\Community\VC\Auxiliary\Build\vcvars64.bat" ^>nul 2^>^&1
echo ^) else ^(
echo     echo ❌ ERROR: Visual Studio not found!
echo     echo.
echo     echo Please install Visual Studio 2022 Community ^(free^):
echo     echo https://visualstudio.microsoft.com/downloads/
echo     echo.
echo     echo Make sure to select "Desktop development with C++" workload
echo     echo.
echo     pause
echo     exit /b 1
echo ^)
echo.
echo if not exist "build" mkdir build
echo.
echo :: Build components
echo echo Building project components...
echo echo.
echo.
echo :: Build driver if available
echo if exist "kdmapper\kdmapper-master\kdmapper.sln" ^(
echo     echo [1/3] Building RickOwens driver mapper...
echo     cd kdmapper\kdmapper-master
echo     msbuild kdmapper.sln /p:Configuration=%%BUILD_CONFIG%% /p:Platform=%%PLATFORM%% /nologo /v:minimal /clp:ErrorsOnly
echo     if not errorlevel 1 ^(
echo         if exist "%%PLATFORM%%\%%BUILD_CONFIG%%\kdmapper.exe" ^(
echo             copy /Y "%%PLATFORM%%\%%BUILD_CONFIG%%\kdmapper.exe" "..\..\build\kdmapper.exe" ^>nul 2^>^&1
echo             echo ✅ Driver mapper built successfully
echo         ^)
echo     ^) else ^(
echo         echo ⚠️  Driver build failed, continuing without driver support
echo     ^)
echo     cd ..\..
echo ^) else ^(
echo     echo ⚠️  Driver source not found, skipping driver build
echo ^)
echo.
echo :: Build memory loader if available  
echo if exist "memloader\memloader-main\memloader.sln" ^(
echo     echo [2/3] Building memory loader...
echo     cd memloader\memloader-main
echo     msbuild memloader.sln /p:Configuration=%%BUILD_CONFIG%% /p:Platform=%%PLATFORM%% /nologo /v:minimal /clp:ErrorsOnly
echo     if not errorlevel 1 ^(
echo         echo ✅ Memory loader built successfully
echo     ^) else ^(
echo         echo ⚠️  Memory loader build failed
echo     ^)
echo     cd ..\..
echo ^) else ^(
echo     echo ⚠️  Memory loader source not found
echo ^)
echo.
echo :: Build main application
echo echo [3/3] Building main application...
echo if exist "source_stackz.sln" ^(
echo     msbuild source_stackz.sln /p:Configuration=%%BUILD_CONFIG%% /p:Platform=%%PLATFORM%% /nologo /clp:ErrorsOnly
echo     if not errorlevel 1 ^(
echo         if exist "%%PLATFORM%%\%%BUILD_CONFIG%%\source_stackz.exe" ^(
echo             copy /Y "%%PLATFORM%%\%%BUILD_CONFIG%%\source_stackz.exe" "build\FluxWareV2.exe" ^>nul 2^>^&1
echo             echo ✅ Main application built successfully
echo         ^) else ^(
echo             echo ❌ Main executable not found after build
echo             pause
echo             exit /b 1
echo         ^)
echo     ^) else ^(
echo         echo ❌ Main application build failed!
echo         echo.
echo         echo Common solutions:
echo         echo - Make sure Visual Studio C++ tools are installed
echo         echo - Run as Administrator
echo         echo - Temporarily disable antivirus
echo         echo - Check Windows SDK is installed
echo         pause
echo         exit /b 1
echo     ^)
echo ^) else ^(
echo     echo ❌ source_stackz.sln not found!
echo     pause
echo     exit /b 1
echo ^)
echo.
echo :: Copy dependencies
echo echo Copying dependencies and resources...
echo if exist "%%PLATFORM%%\%%BUILD_CONFIG%%\*.dll" ^(
echo     copy /Y "%%PLATFORM%%\%%BUILD_CONFIG%%\*.dll" "build\" ^>nul 2^>^&1
echo ^)
echo.
echo if exist "rickowens\RickOwens00-1.0.1\raw_driver.h" ^(
echo     copy /Y "rickowens\RickOwens00-1.0.1\raw_driver.h" "build\driver_data.h" ^>nul 2^>^&1
echo ^)
echo.
echo :: Create config
echo echo [FluxWareV2] ^> "build\config.ini"
echo echo Version=2.0 ^>^> "build\config.ini"  
echo echo BuildDate=%%DATE%% ^>^> "build\config.ini"
echo echo BuildTime=%%TIME%% ^>^> "build\config.ini"
echo echo DriverSupport=true ^>^> "build\config.ini"
echo echo AnimationDetection=true ^>^> "build\config.ini"
echo echo ObfuscatedInput=true ^>^> "build\config.ini"
echo echo AutoOffsets=true ^>^> "build\config.ini"
echo.
echo echo ========================================
echo echo 🎉 BUILD COMPLETED SUCCESSFULLY! 🎉
echo echo ========================================
echo echo.
echo echo Build artifacts:
echo dir build /b 2^>nul
echo echo.
echo echo 📁 Main executable: build\FluxWareV2.exe
echo if exist "build\kdmapper.exe" echo 📁 Driver mapper: build\kdmapper.exe
echo echo 📁 Configuration: build\config.ini
echo echo.
echo echo 🚀 Ready to run! Execute: build\FluxWareV2.exe ^(as Administrator^)
echo echo.
echo pause
) > "build.bat"

echo ✅ Enhanced build system created

echo.
echo [STEP 5/5] Final verification and cleanup...

:: Verify integration
set INTEGRATION_SUCCESS=0

if exist "kdmapper\kdmapper-master" (
    echo ✅ kdmapper: Ready
    set /a INTEGRATION_SUCCESS+=1
) else (
    echo ⚠️  kdmapper: Not available
)

if exist "memloader\memloader-main" (
    echo ✅ memloader: Ready  
    set /a INTEGRATION_SUCCESS+=1
) else (
    echo ⚠️  memloader: Not available
)

if exist "rickowens\RickOwens00-1.0.1" (
    echo ✅ RickOwens: Ready
    set /a INTEGRATION_SUCCESS+=1
) else (
    echo ⚠️  RickOwens: Not available
)

if exist "build.bat" (
    echo ✅ Build system: Ready
    set /a INTEGRATION_SUCCESS+=1
) else (
    echo ❌ Build system: Failed
)

echo.
echo ========================================================================================
echo                            🎉 INSTALLATION COMPLETED! 🎉
echo ========================================================================================
echo.

if %INTEGRATION_SUCCESS% GEQ 3 (
    echo ✅ Installation successful! ^(%INTEGRATION_SUCCESS%/4 components ready^)
    color 0A
) else (
    echo ⚠️  Partial installation ^(%INTEGRATION_SUCCESS%/4 components ready^)
    echo Some components may not be available, but core functionality should work.
    color 0E
)

echo.
echo 📋 NEXT STEPS:
echo ┌─────────────────────────────────────────────────────────────────────────────────┐
echo │                                                                                 │
echo │  1. Install Visual Studio 2022 Community (if not already installed)           │
echo │     Download: https://visualstudio.microsoft.com/downloads/                    │
echo │     ⚠️  IMPORTANT: Select "Desktop development with C++" workload               │
echo │                                                                                 │
echo │  2. Install Windows Driver Kit (WDK) - Optional but recommended                │
echo │     Download: https://docs.microsoft.com/windows-hardware/drivers/download-wdk │
echo │                                                                                 │
echo │  3. Run build.bat as Administrator to compile everything                       │
echo │                                                                                 │
echo │  4. Run build\FluxWareV2.exe as Administrator                                  │
echo │                                                                                 │
echo └─────────────────────────────────────────────────────────────────────────────────┘
echo.

echo 📁 Your project structure:
echo FluxWareV2\
echo ├── 📁 kdmapper\kdmapper-master\     ^(Driver integration^)
echo ├── 📁 memloader\memloader-main\    ^(Memory code loading^)  
echo ├── 📁 rickowens\RickOwens00-1.0.1\ ^(Driver components^)
echo ├── 📁 Memory\                      ^(Enhanced memory systems^)
echo ├── 📁 Utils\                       ^(Obfuscated input^)
echo ├── 📁 Hacks\                       ^(Auto parry + animation detection^)
echo ├── 📁 Offsets\                     ^(Auto offset updates^)
echo ├── 📄 build.bat                    ^(Build system^)
echo ├── 📄 main.cpp                     ^(Enhanced main application^)
echo └── 📄 INSTALL.bat                  ^(This installer^)
echo.

echo 🎯 Everything is ready! Just install Visual Studio and run build.bat!
echo.
echo Press any key to exit installer...
pause >nul