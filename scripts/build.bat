@echo off
REM ZTS Operating System Design & Simulation Platform
REM Build Script for Windows + MinGW

echo ================================================
echo ZTS OS Design - Build Script (MinGW Edition)
echo ================================================

REM 设置编码为 UTF-8
chcp 65001 >nul

REM 检查 CMake 是否可用
cmake --version >nul 2>&1
if %errorlevel% neq 0 (
    echo Error: CMake not found. Please install CMake 3.16 or later.
    echo Download from: https://cmake.org/download/
    pause
    exit /b 1
)

REM 删除旧构建目录（强制干净构建）
if exist build (
    echo Cleaning previous build...
    rmdir /s /q build
)
mkdir build
cd build

echo.
echo Configuring project using MinGW Makefiles...
echo.

REM 使用 MinGW 构建
cmake .. -G "MinGW Makefiles" -DCMAKE_BUILD_TYPE=Release
if %errorlevel% neq 0 (
    echo.
    echo Error: CMake configuration with MinGW failed!
    pause
    exit /b 1
)

echo.
echo Building project...
echo.

cmake --build . --config Release
if %errorlevel% neq 0 (
    echo.
    echo Error: Build failed!
    pause
    exit /b 1
)

echo.
echo ================================================
echo ✅ Build completed successfully!
echo ================================================
echo.
echo Run the following command to execute:
echo   .\zts_os.exe
echo.
pause
