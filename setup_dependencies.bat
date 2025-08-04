@echo off
echo ========================================
echo Flux Ware V2 - Dependency Setup
echo ========================================
echo.
echo This script downloads the external dependencies
echo that are not included in the GitHub repository.
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

echo.
echo ========================================
echo Dependency Setup Complete!
echo ========================================
echo.

:: Check what we have now
echo Checking downloaded components...
if exist "kdmapper-master" (
    echo ✅ kdmapper: Found
) else (
    echo ❌ kdmapper: Missing
)

if exist "memloader-main" (
    echo ✅ memloader: Found
) else (
    echo ❌ memloader: Missing
)

if exist "RickOwens00-1.0.1" (
    echo ✅ RickOwens: Found
) else (
    echo ❌ RickOwens: Missing
)

echo.
echo Next Steps:
echo 1. Install Visual Studio 2019/2022 with C++ development tools
echo 2. Install Windows SDK and WDK
echo 3. Run build.bat to compile everything
echo 4. Run the compiled FluxWareV2.exe as Administrator
echo.

echo Current project structure:
dir /b
echo.

echo Ready to build! Run build.bat when you have Visual Studio installed.
echo.
pause