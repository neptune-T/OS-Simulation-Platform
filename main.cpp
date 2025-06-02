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
    static std::string getCurrentTime() {
        auto now = std::chrono::system_clock::now();
        auto time_t = std::chrono::system_clock::to_time_t(now);
        std::stringstream ss;
        ss << std::put_time(std::localtime(&time_t), "%Y-%m-%d %H:%M:%S");
        return ss.str();
    }
    
    static std::string getVersion() { return "v1.0.0-Beta"; }
    static std::string getBuildDate() { return __DATE__; }
    static std::string getPlatform() { return "Windows x64"; }
    static std::string getArchitecture() { return "x86_64"; }
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
    
    static void setColor(Color color) {
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hConsole, color);
    }
    
    static void resetColor() {
        setColor(WHITE);
    }
};

// 启动动画类
class BootAnimation {
private:
    static void clearScreen() {
        system("cls");
    }
    
    static void moveCursor(int x, int y) {
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        COORD pos = {static_cast<SHORT>(x), static_cast<SHORT>(y)};
        SetConsoleCursorPosition(hConsole, pos);
    }
    
    static void printCentered(const std::string& text, int y = -1) {
        CONSOLE_SCREEN_BUFFER_INFO csbi;
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        GetConsoleScreenBufferInfo(hConsole, &csbi);
        int width = csbi.srWindow.Right - csbi.srWindow.Left + 1;
        
        int x = std::max(0, (width - static_cast<int>(text.length())) / 2);
        if (y != -1) moveCursor(x, y);
        else std::cout << std::string(x, ' ');
        std::cout << text;
        if (y == -1) std::cout << std::endl;
    }
    
public:
    // 显示ZTS操作系统Logo
    static void showLogo() {
        clearScreen();
        ConsoleColor::setColor(ConsoleColor::LIGHT_CYAN);
        
        std::vector<std::string> logo = {

 "SSSSSSSbs   SSSSSSSSSbs     sSSs   SsxsSSs      sSs  "
 "SSSSSSSsS   YSSssSsSSSS    dsSP   sSPxYSbsx    dSP  "
 "      sS       SsS       dsSs    ss      xb   Sx    "
 "     sS        SsS       Sss     ss      sS  ss     "
 "    sS         SsS       SsS     sS      xS  sS    "
 "   sS          SsS       YsSs    sS      xS  sSs   "
 "   sS          SsS        ssS    sS      xS   SsS   "
 "  sS           SsS         sSsS  sS      xS    SsS "
 " ssSsS         SsS          lsS  sb      xS     lsS "
 " sssssS        SsS         sSsP  sS      xS     SsP "
 " sYsSSSSP      SsS       sSSsS    SbsxsdSSS   SSsS  "                                       
        };
        
        std::cout << "\n\n";
        for (const auto& line : logo) {
            printCentered(line);
            Sleep(100);  // 使用Windows Sleep函数
        }
        
        ConsoleColor::setColor(ConsoleColor::LIGHT_YELLOW);
        std::cout << "\n\n";
        printCentered("╔═══════════════════════════════════════════════════════════════════════════════════════════════════════╗");
        printCentered("║                              ZTS 操作系统设计与模拟平台                                                  ║");
        printCentered("║                                ZTS Operating System Design & Simulation                              ║");
        printCentered("╚═══════════════════════════════════════════════════════════════════════════════════════════════════════╝");
    }
    
    // 显示系统信息
    static void showSystemInfo() {
        ConsoleColor::setColor(ConsoleColor::LIGHT_GREEN);
        std::cout << "\n\n";
        printCentered("━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━");
        printCentered("系统信息 | System Information");
        printCentered("━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━");
        
        ConsoleColor::setColor(ConsoleColor::WHITE);
        std::cout << "\n";
        printCentered("版本号 (Version): " + SystemInfo::getVersion());
        printCentered("构建日期 (Build Date): " + SystemInfo::getBuildDate());
        printCentered("运行平台 (Platform): " + SystemInfo::getPlatform());
        printCentered("系统架构 (Architecture): " + SystemInfo::getArchitecture());
        printCentered("启动时间 (Boot Time): " + SystemInfo::getCurrentTime());
        
        ConsoleColor::setColor(ConsoleColor::LIGHT_BLUE);
        std::cout << "\n";
        printCentered("🔧 支持的调度算法 (Supported Scheduling Algorithms): FCFS, Round Robin, SJF, Priority");
        printCentered("💾 内存管理模拟 (Memory Management Simulation): 分页、分段算法");
        printCentered("📁 文件系统模拟 (File System Simulation): 基础目录结构管理");
        printCentered("🔄 进程同步模拟 (Process Synchronization): 信号量、互斥锁");
    }
    
    // 启动加载动画
    static void showLoadingAnimation() {
        ConsoleColor::setColor(ConsoleColor::YELLOW);
        std::cout << "\n\n";
        printCentered("━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━");
        printCentered("系统启动中 | System Initializing");
        printCentered("━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━");
        
        std::vector<std::string> loadingSteps = {
            "🔧 初始化系统内核...",
            "💾 加载内存管理模块...",
            "📋 初始化进程调度器...",
            "📁 挂载文件系统...",
            "🔐 配置安全策略...",
            "🌐 启动系统服务...",
            "✅ 系统启动完成！"
        };
        
        for (const auto& step : loadingSteps) {
            std::cout << "\n";
            printCentered(step);
            
            // 进度条动画
            std::string progressBar = "[";
            for (int i = 0; i < 30; i++) {
                progressBar += "=";
                std::cout << "\r";
                printCentered(progressBar + std::string(30-i-1, '-') + "]");
                Sleep(50);  // 使用Windows Sleep函数
            }
            
            Sleep(300);  // 使用Windows Sleep函数
        }
        
        ConsoleColor::setColor(ConsoleColor::LIGHT_GREEN);
        std::cout << "\n\n";
        printCentered("🎉 欢迎使用 ZTS 操作系统模拟平台！");
        printCentered("🎉 Welcome to ZTS Operating System Simulation Platform!");
    }
    
    // 显示主菜单
    static void showMainMenu() {
        clearScreen();
        ConsoleColor::setColor(ConsoleColor::LIGHT_CYAN);
        std::cout << "\n";
        printCentered("╔══════════════════════════════════════════════════════════════════════════════════════════════════════╗");
        printCentered("║                                    ZTS 操作系统模拟平台 - 主菜单                                        ║");
        printCentered("║                                 ZTS Operating System Simulation - Main Menu                         ║");
        printCentered("╚══════════════════════════════════════════════════════════════════════════════════════════════════════╝");
        
        ConsoleColor::setColor(ConsoleColor::WHITE);
        std::cout << "\n";
        printCentered("请选择要体验的功能模块：");
        printCentered("Please select the module you want to experience:");
        std::cout << "\n";
        
        ConsoleColor::setColor(ConsoleColor::LIGHT_YELLOW);
        printCentered("━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━");
        
        ConsoleColor::setColor(ConsoleColor::LIGHT_GREEN);
        std::cout << "\n";
        printCentered("1. 🔧 进程调度算法演示 (Process Scheduling Algorithms Demo)");
        printCentered("2. 💾 内存管理模拟 (Memory Management Simulation)");
        printCentered("3. 📁 文件系统操作 (File System Operations)");
        printCentered("4. 🔄 进程同步机制 (Process Synchronization)");
        printCentered("5. 📊 系统性能监控 (System Performance Monitor)");
        printCentered("6. ⚙️  系统配置管理 (System Configuration)");
        printCentered("0. 🚪 退出系统 (Exit System)");
        
        std::cout << "\n";
        ConsoleColor::setColor(ConsoleColor::LIGHT_YELLOW);
        printCentered("━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━");
        
        ConsoleColor::setColor(ConsoleColor::CYAN);
        std::cout << "\n";
        printCentered("💡 提示：输入对应数字选择功能，按回车确认");
        printCentered("💡 Tip: Enter the corresponding number and press Enter to confirm");
    }
};

// 主程序入口
int main() {
    // 设置控制台窗口标题
    SetConsoleTitleA("ZTS Operating System Design & Simulation Platform");
    
    // 设置控制台编码为UTF-8
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
    
    try {
        // 显示启动界面
        BootAnimation::showLogo();
        Sleep(1500);
        
        BootAnimation::showSystemInfo();
        Sleep(2000);
        
        BootAnimation::showLoadingAnimation();
        Sleep(2000);
        
        // 显示主菜单
        BootAnimation::showMainMenu();
        
        // 用户交互循环
        int choice;
        ConsoleColor::setColor(ConsoleColor::WHITE);
        std::cout << "\n请输入您的选择 (Enter your choice): ";
        
        while (std::cin >> choice) {
            switch (choice) {
                case 1:
                    ConsoleColor::setColor(ConsoleColor::LIGHT_GREEN);
                    std::cout << "\n🔧 正在启动进程调度算法演示模块..." << std::endl;
                    std::cout << "📋 该功能将在后续版本中实现，敬请期待！" << std::endl;
                    break;
                case 2:
                    ConsoleColor::setColor(ConsoleColor::LIGHT_GREEN);
                    std::cout << "\n💾 正在启动内存管理模拟模块..." << std::endl;
                    std::cout << "🧠 该功能将在后续版本中实现，敬请期待！" << std::endl;
                    break;
                case 3:
                    ConsoleColor::setColor(ConsoleColor::LIGHT_GREEN);
                    std::cout << "\n📁 正在启动文件系统操作模块..." << std::endl;
                    std::cout << "💽 该功能将在后续版本中实现，敬请期待！" << std::endl;
                    break;
                case 4:
                    ConsoleColor::setColor(ConsoleColor::LIGHT_GREEN);
                    std::cout << "\n🔄 正在启动进程同步机制模块..." << std::endl;
                    std::cout << "🔗 该功能将在后续版本中实现，敬请期待！" << std::endl;
                    break;
                case 5:
                    ConsoleColor::setColor(ConsoleColor::LIGHT_GREEN);
                    std::cout << "\n📊 正在启动系统性能监控模块..." << std::endl;
                    std::cout << "📈 该功能将在后续版本中实现，敬请期待！" << std::endl;
                    break;
                case 6:
                    ConsoleColor::setColor(ConsoleColor::LIGHT_GREEN);
                    std::cout << "\n⚙️ 正在启动系统配置管理模块..." << std::endl;
                    std::cout << "🔧 该功能将在后续版本中实现，敬请期待！" << std::endl;
                    break;
                case 0:
                    ConsoleColor::setColor(ConsoleColor::LIGHT_YELLOW);
                    std::cout << "\n🚪 正在退出ZTS操作系统模拟平台..." << std::endl;
                    std::cout << "👋 感谢使用，再见！" << std::endl;
                    std::cout << "👋 Thank you for using ZTS OS Simulation Platform!" << std::endl;
                    ConsoleColor::resetColor();
                    Sleep(2000);
                    return 0;
                default:
                    ConsoleColor::setColor(ConsoleColor::LIGHT_RED);
                    std::cout << "\n❌ 无效的选择，请输入0-6之间的数字！" << std::endl;
                    std::cout << "❌ Invalid choice, please enter a number between 0-6!" << std::endl;
                    break;
            }
            
            ConsoleColor::setColor(ConsoleColor::WHITE);
            std::cout << "\n按任意键返回主菜单..." << std::endl;
            system("pause >nul");
            
            BootAnimation::showMainMenu();
            std::cout << "\n请输入您的选择 (Enter your choice): ";
        }
    }
    catch (const std::exception& e) {
        ConsoleColor::setColor(ConsoleColor::LIGHT_RED);
        std::cout << "\n❌ 程序运行出错: " << e.what() << std::endl;
        ConsoleColor::resetColor();
        system("pause");
        return 1;
    }
    
    // 重置颜色
    ConsoleColor::resetColor();
    return 0;
} 