@echo off
REM ZTS Operating System Design & Simulation Platform
REM Simple Compile Script (No CMake Required)

echo ================================================
echo ZTS OS Design - Simple Compile Script
echo ================================================

REM 设置编码为UTF-8
chcp 65001 >nul

echo.
echo 正在编译 ZTS 操作系统模拟程序...
echo Compiling ZTS Operating System Simulation...
echo.

REM 检查是否有g++编译器
g++ --version >nul 2>&1
if %errorlevel% neq 0 (
    echo 尝试使用MSVC编译器...
    echo Trying MSVC compiler...
    
    REM 尝试使用cl.exe (MSVC)
    cl /nologo /EHsc /std:c++17 /Fe:ZTS_OS_Design.exe main.cpp user32.lib kernel32.lib
    
    if %errorlevel% neq 0 (
        echo.
        echo ❌ 编译失败！请确保已安装以下任一编译器：
        echo ❌ Compilation failed! Please ensure one of the following is installed:
        echo    - MinGW-w64 (g++)
        echo    - Visual Studio Build Tools (cl.exe)
        echo.
        echo 💡 推荐安装 MinGW-w64: https://www.mingw-w64.org/
        echo 💡 或者安装 Visual Studio Community: https://visualstudio.microsoft.com/
        pause
        exit /b 1
    )
) else (
    REM 使用g++编译
    echo 使用 g++ 编译器...
    echo Using g++ compiler...
    
    g++ -std=c++17 -O2 -Wall -Wextra -o ZTS_OS_Design.exe main.cpp -lkernel32 -luser32
    
    if %errorlevel% neq 0 (
        echo.
        echo ❌ g++ 编译失败！
        echo ❌ g++ compilation failed!
        pause
        exit /b 1
    )
)

echo.
echo ================================================
echo ✅ 编译成功！
echo ✅ Compilation successful!
echo ================================================
echo.
echo 🚀 即将启动 ZTS 操作系统模拟平台...
echo 🚀 Starting ZTS Operating System Simulation Platform...
echo.

REM 等待2秒然后运行程序
timeout /t 2 /nobreak >nul

REM 运行编译好的程序
ZTS_OS_Design.exe

echo.
echo 程序已退出，按任意键继续...
echo Program exited, press any key to continue...
pause >nul 