@echo off
echo Building Auto Larry External with ESP + Parry...

REM Check if Visual Studio is available
where msbuild >nul 2>&1
if %errorlevel% neq 0 (
    echo MSBuild not found. Please install Visual Studio 2019 or later.
    echo Or run: "C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\MSBuild\Current\Bin\MSBuild.exe" source_stackz.sln /p:Configuration=Release /p:Platform=x64
    pause
    exit /b 1
)

REM Build the project
echo Building project...
msbuild source_stackz.sln /p:Configuration=Release /p:Platform=x64

if %errorlevel% equ 0 (
    echo Build successful!
    echo Executable created at: x64\Release\source_stackz.exe
) else (
    echo Build failed!
)

pause