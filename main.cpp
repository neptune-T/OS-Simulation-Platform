#include <iostream>
#include <windows.h>
#include "include/utils/boot_animation.h"
#include "include/utils/scheduler_demo.h"
#include "include/utils/memory_demo.h"

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
                case 1: {
                    // 启动进程调度算法演示模块
                    ConsoleColor::setColor(ConsoleColor::LIGHT_GREEN);
                    std::cout << "\n🔧 正在启动进程调度算法演示模块..." << std::endl;
                    Sleep(1000);
                    
                    // 创建并启动调度演示器
                    ZTS_OS::SchedulerDemo demo;
                    demo.start();
                    break;
                }
                case 2: {
                    // 启动内存管理模拟模块
                    ConsoleColor::setColor(ConsoleColor::LIGHT_GREEN);
                    std::cout << "\n💾 正在启动内存管理模拟模块..." << std::endl;
                    Sleep(1000);
                    
                    // 创建并启动内存演示器
                    ZTS_OS::MemoryDemo demo;
                    demo.start();
                    break;
                }
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