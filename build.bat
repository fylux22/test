@echo off
echo ========================================
echo Flux Ware V2 - Enhanced Auto Parry Build
echo ========================================
echo.

:: Set build configuration
set BUILD_CONFIG=Debug
set PLATFORM=x64
set PROJECT_NAME=FluxWareV2

:: Check if Visual Studio is installed
if not exist "%ProgramFiles(x86)%\Microsoft Visual Studio\2019\Community\Common7\IDE\devenv.exe" (
    if not exist "%ProgramFiles(x86)%\Microsoft Visual Studio\2022\Community\Common7\IDE\devenv.exe" (
        echo ERROR: Visual Studio not found!
        echo Please install Visual Studio 2019 or 2022 with C++ development tools
        pause
        exit /b 1
    )
)

:: Set Visual Studio environment
echo Setting up Visual Studio environment...
if exist "%ProgramFiles(x86)%\Microsoft Visual Studio\2022\Community\VC\Auxiliary\Build\vcvars64.bat" (
    call "%ProgramFiles(x86)%\Microsoft Visual Studio\2022\Community\VC\Auxiliary\Build\vcvars64.bat"
) else (
    call "%ProgramFiles(x86)%\Microsoft Visual Studio\2019\Community\VC\Auxiliary\Build\vcvars64.bat"
)

:: Create build directory
if not exist "build" mkdir build
cd build

echo.
echo Building RickOwens Driver...
cd ..\kdmapper\kdmapper-master
if exist "kdmapper.sln" (
    msbuild kdmapper.sln /p:Configuration=%BUILD_CONFIG% /p:Platform=%PLATFORM%
    if errorlevel 1 (
        echo WARNING: Driver build failed, continuing without driver support
    ) else (
        echo Driver built successfully!
        copy /Y "%PLATFORM%\%BUILD_CONFIG%\kdmapper.exe" "..\..\build\kdmapper.exe" >nul 2>&1
    )
) else (
    echo WARNING: Driver solution not found, skipping driver build
)

cd ..\..

echo.
echo Building Memory Loader...
cd memloader\memloader-main
if exist "memloader.sln" (
    msbuild memloader.sln /p:Configuration=%BUILD_CONFIG% /p:Platform=%PLATFORM%
    if errorlevel 1 (
        echo WARNING: Memory loader build failed
    ) else (
        echo Memory loader built successfully!
    )
) else (
    echo WARNING: Memory loader solution not found
)

cd ..\..

echo.
echo Building Main Application...
if exist "source_stackz.sln" (
    msbuild source_stackz.sln /p:Configuration=%BUILD_CONFIG% /p:Platform=%PLATFORM%
    if errorlevel 1 (
        echo ERROR: Main application build failed!
        pause
        exit /b 1
    )
) else (
    echo ERROR: Main solution file not found!
    pause
    exit /b 1
)

echo.
echo Copying build artifacts...
if exist "%PLATFORM%\%BUILD_CONFIG%\source_stackz.exe" (
    copy /Y "%PLATFORM%\%BUILD_CONFIG%\source_stackz.exe" "build\FluxWareV2.exe" >nul 2>&1
    echo Main executable copied to build\FluxWareV2.exe
) else (
    echo ERROR: Main executable not found!
    pause
    exit /b 1
)

:: Copy required DLLs and resources
echo Copying dependencies...
if exist "%PLATFORM%\%BUILD_CONFIG%\*.dll" (
    copy /Y "%PLATFORM%\%BUILD_CONFIG%\*.dll" "build\" >nul 2>&1
)

:: Copy driver files if they exist
if exist "rickowens\RickOwens00-1.0.1\raw_driver.h" (
    copy /Y "rickowens\RickOwens00-1.0.1\raw_driver.h" "build\driver_data.h" >nul 2>&1
    echo Driver data copied
)

:: Create configuration file
echo Creating configuration...
echo [FluxWareV2] > "build\config.ini"
echo Version=2.0 >> "build\config.ini"
echo BuildDate=%DATE% >> "build\config.ini"
echo BuildTime=%TIME% >> "build\config.ini"
echo DriverSupport=true >> "build\config.ini"
echo AnimationDetection=true >> "build\config.ini"
echo ObfuscatedInput=true >> "build\config.ini"
echo AutoOffsets=true >> "build\config.ini"

:: Create README
echo Creating documentation...
echo # Flux Ware V2 - Enhanced Auto Parry External > "build\README.md"
echo. >> "build\README.md"
echo ## Features >> "build\README.md"
echo - Advanced animation detection system >> "build\README.md"
echo - Driver integration for enhanced memory access >> "build\README.md"
echo - Obfuscated input system for stealth >> "build\README.md"
echo - Automatic offset updating >> "build\README.md"
echo - Enhanced GUI with detailed settings >> "build\README.md"
echo - KeyAuth authentication integration >> "build\README.md"
echo - Memory code loading for stealth execution >> "build\README.md"
echo. >> "build\README.md"
echo ## Usage >> "build\README.md"
echo 1. Run FluxWareV2.exe as Administrator >> "build\README.md"
echo 2. Complete authentication process >> "build\README.md"
echo 3. Start Roblox >> "build\README.md"
echo 4. Configure auto parry settings in the GUI >> "build\README.md"
echo 5. Enable auto parry and enjoy! >> "build\README.md"
echo. >> "build\README.md"
echo ## Requirements >> "build\README.md"
echo - Windows 10/11 x64 >> "build\README.md"
echo - Administrator privileges >> "build\README.md"
echo - Valid KeyAuth license >> "build\README.md"
echo - Roblox installed >> "build\README.md"

:: Calculate file sizes and create manifest
echo Creating build manifest...
echo Build Manifest - %DATE% %TIME% > "build\manifest.txt"
echo ================================== >> "build\manifest.txt"
for %%f in (build\*.*) do (
    echo %%~nxf - %%~zf bytes >> "build\manifest.txt"
)

echo.
echo ========================================
echo Build completed successfully!
echo ========================================
echo.
echo Build artifacts:
dir build /b
echo.
echo Main executable: build\FluxWareV2.exe
if exist "build\kdmapper.exe" (
    echo Driver mapper: build\kdmapper.exe
)
echo Configuration: build\config.ini
echo Documentation: build\README.md
echo.
echo Ready for GitHub upload!
echo.
pause