#ifndef BOOT_ANIMATION_H
#define BOOT_ANIMATION_H

#include <iostream>
#include <string>
#include <vector>
#include <chrono>
#include <iomanip>
#include <ctime>
#include <sstream>
#include <algorithm>
#include <windows.h>

// 系统信息类
class SystemInfo {
public:
    static std::string getCurrentTime();
    static std::string getVersion();
    static std::string getBuildDate();
    static std::string getPlatform();
    static std::string getArchitecture();
};

// 控制台颜色控制类
class ConsoleColor {
public:
    enum Color {
        BLACK = 0, BLUE = 1, GREEN = 2, CYAN = 3,
        RED = 4, MAGENTA = 5, YELLOW = 6, WHITE = 7,
        GRAY = 8, LIGHT_BLUE = 9, LIGHT_GREEN = 10,
        LIGHT_CYAN = 11, LIGHT_RED = 12, LIGHT_MAGENTA = 13,
        LIGHT_YELLOW = 14, BRIGHT_WHITE = 15
    };
    
    static void setColor(Color color);
    static void resetColor();
};

// 启动动画类
class BootAnimation {
private:
    static void clearScreen();
    static void moveCursor(int x, int y);
    static void printCentered(const std::string& text, int y = -1);
    
public:
    // 显示ZTS操作系统Logo
    static void showLogo();
    
    // 显示系统信息
    static void showSystemInfo();
    
    // 启动加载动画
    static void showLoadingAnimation();
    
    // 显示主菜单
    static void showMainMenu();
};

#endif // BOOT_ANIMATION_H 