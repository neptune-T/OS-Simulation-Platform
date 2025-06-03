#include "../../include/utils/boot_animation.h"

// SystemInfo类实现
std::string SystemInfo::getCurrentTime() {
    auto now = std::chrono::system_clock::now();
    auto time_t = std::chrono::system_clock::to_time_t(now);
    std::stringstream ss;
    ss << std::put_time(std::localtime(&time_t), "%Y-%m-%d %H:%M:%S");
    return ss.str();
}

std::string SystemInfo::getVersion() { 
    return "v1.0.0-Beta"; 
}

std::string SystemInfo::getBuildDate() { 
    return __DATE__; 
}

std::string SystemInfo::getPlatform() { 
    return "Windows x64"; 
}

std::string SystemInfo::getArchitecture() { 
    return "x86_64"; 
}

// ConsoleColor类实现
void ConsoleColor::setColor(Color color) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
}

void ConsoleColor::resetColor() {
    setColor(WHITE);
}

// BootAnimation类实现
void BootAnimation::clearScreen() {
    system("cls");
}

void BootAnimation::moveCursor(int x, int y) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD pos = {static_cast<SHORT>(x), static_cast<SHORT>(y)};
    SetConsoleCursorPosition(hConsole, pos);
}

void BootAnimation::printCentered(const std::string& text, int y) {
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

// 显示ZTS操作系统Logo
void BootAnimation::showLogo() {
    clearScreen();
    ConsoleColor::setColor(ConsoleColor::LIGHT_CYAN);
    
    std::vector<std::string> logo = {
        "███████╗████████╗███████╗        ██████╗ ███████╗",
        "╚══███╔╝╚══██╔══╝██╔════╝        ██╔═══██╗██╔════╝",
        "  ███╔╝    ██║   ███████╗        ██║   ██║███████╗",
        " ███╔╝     ██║   ╚════██║        ██║   ██║╚════██║",
        "███████╗   ██║   ███████║        ╚██████╔╝███████║",
        "╚══════╝   ╚═╝   ╚══════╝         ╚═════╝ ╚══════╝",
        "",
        "██████╗ ███████╗███████╗██╗ ██████╗ ███╗   ██╗",
        "██╔══██╗██╔════╝██╔════╝██║██╔════╝ ████╗  ██║", 
        "██║  ██║█████╗  ███████╗██║██║  ███╗██╔██╗ ██║",
        "██║  ██║██╔══╝  ╚════██║██║██║   ██║██║╚██╗██║",
        "██████╔╝███████╗███████║██║╚██████╔╝██║ ╚████║",
        "╚═════╝ ╚══════╝╚══════╝╚═╝ ╚═════╝ ╚═╝  ╚═══╝",
        "",
        "███████╗██╗███╗   ███╗██╗   ██╗██╗      █████╗ ████████╗██╗ ██████╗ ███╗   ██╗",
        "██╔════╝██║████╗ ████║██║   ██║██║     ██╔══██╗╚══██╔══╝██║██╔═══██╗████╗  ██║",
        "███████╗██║██╔████╔██║██║   ██║██║     ███████║   ██║   ██║██║   ██║██╔██╗ ██║",
        "╚════██║██║██║╚██╔╝██║██║   ██║██║     ██╔══██║   ██║   ██║██║   ██║██║╚██╗██║",
        "███████║██║██║ ╚═╝ ██║╚██████╔╝███████╗██║  ██║   ██║   ██║╚██████╔╝██║ ╚████║",
        "╚══════╝╚═╝╚═╝     ╚═╝ ╚═════╝ ╚══════╝╚═╝  ╚═╝   ╚═╝   ╚═╝ ╚═════╝ ╚═╝  ╚═══╝"
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
void BootAnimation::showSystemInfo() {
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
void BootAnimation::showLoadingAnimation() {
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
void BootAnimation::showMainMenu() {
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
