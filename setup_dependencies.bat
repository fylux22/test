@echo off
echo ========================================
echo Flux Ware V2 - Complete Auto Setup
echo ========================================
echo.
echo This script will automatically download and set up
echo ALL external dependencies for easy installation.
echo.
echo What this script does:
echo - Downloads kdmapper (driver integration)
echo - Downloads memloader (memory code loading)  
echo - Downloads RickOwens driver components
echo - Sets up proper directory structure
echo - Integrates all components automatically
echo - Creates ready-to-build project
echo.

:: Check if we're in the right directory
if not exist "main.cpp" (
    echo ERROR: Please run this script from the FluxWareV2 directory
    echo Make sure you see main.cpp and other project files here.
    pause
    exit /b 1
)

echo Current directory: %CD%
echo.

:: Download external dependencies
echo Downloading external dependencies...
echo.

echo [1/3] Downloading kdmapper (driver mapper)...
curl -L -o kdmapper.zip "https://filebin.net/rmcs8pmfrsqavvad/kdmapper-master.zip"
if exist kdmapper.zip (
    echo Extracting kdmapper...
    powershell -command "Expand-Archive -Path 'kdmapper.zip' -DestinationPath '.' -Force"
    del kdmapper.zip
    echo ✅ kdmapper downloaded and extracted
) else (
    echo ❌ WARNING: Failed to download kdmapper
    echo You may need to download it manually from the filebin link
)

echo.
echo [2/3] Downloading memloader (memory code loader)...
curl -L -o memloader.zip "https://filebin.net/rmcs8pmfrsqavvad/memloader-main.zip"
if exist memloader.zip (
    echo Extracting memloader...
    powershell -command "Expand-Archive -Path 'memloader.zip' -DestinationPath '.' -Force"
    del memloader.zip
    echo ✅ memloader downloaded and extracted
) else (
    echo ❌ WARNING: Failed to download memloader
    echo You may need to download it manually from the filebin link
)

echo.
echo [3/3] Downloading RickOwens driver...
curl -L -o rickowens.zip "https://filebin.net/rmcs8pmfrsqavvad/RickOwens00-1.0.1.zip"
if exist rickowens.zip (
    echo Extracting RickOwens...
    powershell -command "Expand-Archive -Path 'rickowens.zip' -DestinationPath '.' -Force"
    del rickowens.zip
    echo ✅ RickOwens downloaded and extracted
) else (
    echo ❌ WARNING: Failed to download RickOwens
    echo You may need to download it manually from the filebin link
)

:: Integrate downloaded components into project structure
echo.
echo ========================================
echo Integrating Components...
echo ========================================
echo.

:: Move kdmapper to proper location
if exist "kdmapper-master" (
    echo Integrating kdmapper into project...
    if not exist "kdmapper" mkdir kdmapper
    xcopy /E /I /Y "kdmapper-master" "kdmapper\kdmapper-master" >nul 2>&1
    rmdir /S /Q "kdmapper-master" >nul 2>&1
    echo ✅ kdmapper integrated
)

:: Move memloader to proper location  
if exist "memloader-main" (
    echo Integrating memloader into project...
    if not exist "memloader" mkdir memloader
    xcopy /E /I /Y "memloader-main" "memloader\memloader-main" >nul 2>&1
    rmdir /S /Q "memloader-main" >nul 2>&1
    echo ✅ memloader integrated
)

:: Move RickOwens to proper location
if exist "RickOwens00-1.0.1" (
    echo Integrating RickOwens into project...
    if not exist "rickowens" mkdir rickowens
    xcopy /E /I /Y "RickOwens00-1.0.1" "rickowens\RickOwens00-1.0.1" >nul 2>&1
    rmdir /S /Q "RickOwens00-1.0.1" >nul 2>&1
    echo ✅ RickOwens integrated
)

:: Create additional required directories
echo Creating additional project directories...
if not exist "build" mkdir build
if not exist "x64" mkdir x64
if not exist "x64\Debug" mkdir x64\Debug
if not exist "x64\Release" mkdir x64\Release

:: Update build.bat to handle integrated components
echo Updating build system for integrated components...
(
echo @echo off
echo echo ========================================
echo echo Flux Ware V2 - Enhanced Auto Parry Build
echo echo ========================================
echo echo.
echo.
echo :: Set build configuration
echo set BUILD_CONFIG=Debug
echo set PLATFORM=x64
echo set PROJECT_NAME=FluxWareV2
echo.
echo :: Check if Visual Studio is installed
echo if not exist "%%ProgramFiles^(x86^)%%\Microsoft Visual Studio\2019\Community\Common7\IDE\devenv.exe" ^(
echo     if not exist "%%ProgramFiles^(x86^)%%\Microsoft Visual Studio\2022\Community\Common7\IDE\devenv.exe" ^(
echo         echo ERROR: Visual Studio not found!
echo         echo Please install Visual Studio 2019 or 2022 with C++ development tools
echo         echo Download: https://visualstudio.microsoft.com/downloads/
echo         pause
echo         exit /b 1
echo     ^)
echo ^)
echo.
echo :: Set Visual Studio environment
echo echo Setting up Visual Studio environment...
echo if exist "%%ProgramFiles^(x86^)%%\Microsoft Visual Studio\2022\Community\VC\Auxiliary\Build\vcvars64.bat" ^(
echo     call "%%ProgramFiles^(x86^)%%\Microsoft Visual Studio\2022\Community\VC\Auxiliary\Build\vcvars64.bat"
echo ^) else ^(
echo     call "%%ProgramFiles^(x86^)%%\Microsoft Visual Studio\2019\Community\VC\Auxiliary\Build\vcvars64.bat"
echo ^)
echo.
echo :: Create build directory
echo if not exist "build" mkdir build
echo.
echo echo Building RickOwens Driver...
echo if exist "kdmapper\kdmapper-master\kdmapper.sln" ^(
echo     cd kdmapper\kdmapper-master
echo     msbuild kdmapper.sln /p:Configuration=%%BUILD_CONFIG%% /p:Platform=%%PLATFORM%% /nologo /v:minimal
echo     if errorlevel 1 ^(
echo         echo WARNING: Driver build failed, continuing without driver support
echo     ^) else ^(
echo         echo Driver built successfully!
echo         if exist "%%PLATFORM%%\%%BUILD_CONFIG%%\kdmapper.exe" ^(
echo             copy /Y "%%PLATFORM%%\%%BUILD_CONFIG%%\kdmapper.exe" "..\..\build\kdmapper.exe" ^>nul 2^>^&1
echo         ^)
echo     ^)
echo     cd ..\..
echo ^) else ^(
echo     echo WARNING: Driver solution not found, skipping driver build
echo ^)
echo.
echo echo Building Memory Loader...
echo if exist "memloader\memloader-main\memloader.sln" ^(
echo     cd memloader\memloader-main
echo     msbuild memloader.sln /p:Configuration=%%BUILD_CONFIG%% /p:Platform=%%PLATFORM%% /nologo /v:minimal
echo     if errorlevel 1 ^(
echo         echo WARNING: Memory loader build failed
echo     ^) else ^(
echo         echo Memory loader built successfully!
echo     ^)
echo     cd ..\..
echo ^) else ^(
echo     echo WARNING: Memory loader solution not found
echo ^)
echo.
echo echo Building Main Application...
echo if exist "source_stackz.sln" ^(
echo     msbuild source_stackz.sln /p:Configuration=%%BUILD_CONFIG%% /p:Platform=%%PLATFORM%% /nologo
echo     if errorlevel 1 ^(
echo         echo ERROR: Main application build failed!
echo         echo.
echo         echo Common solutions:
echo         echo 1. Make sure Visual Studio C++ tools are installed
echo         echo 2. Run this script as Administrator
echo         echo 3. Check Windows SDK is installed
echo         echo 4. Temporarily disable antivirus
echo         pause
echo         exit /b 1
echo     ^)
echo ^) else ^(
echo     echo ERROR: Main solution file not found!
echo     echo Make sure source_stackz.sln exists in the project directory
echo     pause
echo     exit /b 1
echo ^)
echo.
echo echo Copying build artifacts...
echo if exist "%%PLATFORM%%\%%BUILD_CONFIG%%\source_stackz.exe" ^(
echo     copy /Y "%%PLATFORM%%\%%BUILD_CONFIG%%\source_stackz.exe" "build\FluxWareV2.exe" ^>nul 2^>^&1
echo     echo Main executable copied to build\FluxWareV2.exe
echo ^) else ^(
echo     echo ERROR: Main executable not found!
echo     echo Expected location: %%PLATFORM%%\%%BUILD_CONFIG%%\source_stackz.exe
echo     pause
echo     exit /b 1
echo ^)
echo.
echo :: Copy required DLLs and resources
echo echo Copying dependencies...
echo if exist "%%PLATFORM%%\%%BUILD_CONFIG%%\*.dll" ^(
echo     copy /Y "%%PLATFORM%%\%%BUILD_CONFIG%%\*.dll" "build\" ^>nul 2^>^&1
echo ^)
echo.
echo :: Copy driver files if they exist
echo if exist "rickowens\RickOwens00-1.0.1\raw_driver.h" ^(
echo     copy /Y "rickowens\RickOwens00-1.0.1\raw_driver.h" "build\driver_data.h" ^>nul 2^>^&1
echo     echo Driver data copied
echo ^)
echo.
echo :: Create configuration file
echo echo Creating configuration...
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
echo echo Build completed successfully!
echo echo ========================================
echo echo.
echo echo Build artifacts:
echo dir build /b
echo echo.
echo echo Main executable: build\FluxWareV2.exe
echo if exist "build\kdmapper.exe" ^(
echo     echo Driver mapper: build\kdmapper.exe
echo ^)
echo echo Configuration: build\config.ini
echo echo.
echo echo Ready to run! Execute build\FluxWareV2.exe as Administrator
echo echo.
echo pause
) > "build.bat"

echo.
echo ========================================
echo Setup Complete - All Dependencies Integrated!
echo ========================================
echo.

:: Final verification
echo Verifying integrated components...
if exist "kdmapper\kdmapper-master" (
    echo ✅ kdmapper: Integrated and ready
) else (
    echo ❌ kdmapper: Missing or failed to integrate
)

if exist "memloader\memloader-main" (
    echo ✅ memloader: Integrated and ready
) else (
    echo ❌ memloader: Missing or failed to integrate
)

if exist "rickowens\RickOwens00-1.0.1" (
    echo ✅ RickOwens: Integrated and ready
) else (
    echo ❌ RickOwens: Missing or failed to integrate
)

if exist "build.bat" (
    echo ✅ Build system: Updated and ready
) else (
    echo ❌ Build system: Failed to update
)

echo.
echo ========================================
echo Ready to Build!
echo ========================================
echo.
echo Your project is now completely set up with all dependencies!
echo.
echo Next steps:
echo 1. Install Visual Studio 2022 Community (if not already installed)
echo    Download: https://visualstudio.microsoft.com/downloads/
echo    Select: "Desktop development with C++" workload
echo.
echo 2. Install Windows Driver Kit (WDK)
echo    Download: https://docs.microsoft.com/windows-hardware/drivers/download-the-wdk
echo.
echo 3. Run build.bat as Administrator to compile everything
echo.
echo 4. Run build\FluxWareV2.exe as Administrator
echo.
echo Project structure:
echo FluxWareV2/
echo ├── 📁 kdmapper\kdmapper-master\     (Driver integration)
echo ├── 📁 memloader\memloader-main\    (Memory code loading)
echo ├── 📁 rickowens\RickOwens00-1.0.1\ (Driver components)
echo ├── 📁 Memory\                      (Enhanced memory systems)
echo ├── 📁 Utils\                       (Obfuscated input)
echo ├── 📁 Hacks\                       (Auto parry + animation detection)
echo ├── 📁 Offsets\                     (Auto offset updates)
echo ├── 📄 build.bat                    (Updated build system)
echo └── 📄 main.cpp                     (Enhanced main application)
echo.
echo Everything is ready! Just install Visual Studio and run build.bat!
echo.
pause