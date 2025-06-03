#include "../../include/utils/memory_demo.h"
#include "../../include/memory/ContiguousAllocator.h"
#include <iostream>
#include <iomanip>
#include <limits>

/**
 * @file memory_demo.cpp
 * @brief 内存管理演示器实现
 * @author ZTS Operating System Design Team
 * @date 2025
 */

namespace ZTS_OS {

// 构造函数
MemoryDemo::MemoryDemo() {
    // 初始化预设的内存请求场景
    memory_scenarios_.push_back({
        MemoryRequest(1, "浏览器", 100),
        MemoryRequest(2, "音乐播放器", 50),
        MemoryRequest(3, "文档编辑", 80),
        MemoryRequest(1, "", 0, true),  // 释放浏览器
        MemoryRequest(4, "视频播放", 90),
        MemoryRequest(5, "游戏", 120)
    });
    
    memory_scenarios_.push_back({
        MemoryRequest(1, "操作系统", 200),
        MemoryRequest(2, "编译器", 150),
        MemoryRequest(3, "数据库", 300),
        MemoryRequest(2, "", 0, true),  // 释放编译器
        MemoryRequest(4, "虚拟机", 250),
        MemoryRequest(3, "", 0, true),  // 释放数据库
        MemoryRequest(5, "IDE", 180),
        MemoryRequest(6, "浏览器", 120)
    });
}

// 启动内存管理演示主界面
void MemoryDemo::start() {
    showTitle("内存管理模拟系统");
    
    while (true) {
        showMainMenu();
        
        int choice;
        std::cout << "\n请输入您的选择: ";
        std::cin >> choice;
        
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            ConsoleColor::setColor(ConsoleColor::LIGHT_RED);
            std::cout << "\n❌ 输入无效，请输入数字！" << std::endl;
            ConsoleColor::resetColor();
            pauseForUser();
            continue;
        }
        
        switch (choice) {
            case 1:
                contiguousAllocationDemo();
                break;
            case 2: {
                ConsoleColor::setColor(ConsoleColor::LIGHT_YELLOW);
                std::cout << "\n🔧 分页内存管理正在开发中，敬请期待！" << std::endl;
                ConsoleColor::resetColor();
                pauseForUser();
                break;
            }
            case 3: {
                ConsoleColor::setColor(ConsoleColor::LIGHT_YELLOW);
                std::cout << "\n🔧 页面置换算法演示正在开发中，敬请期待！" << std::endl;
                ConsoleColor::resetColor();
                pauseForUser();
                break;
            }
            case 4:
                allocationComparisonDemo();
                break;
            case 0:
                ConsoleColor::setColor(ConsoleColor::LIGHT_BLUE);
                std::cout << "\n👋 返回主菜单..." << std::endl;
                ConsoleColor::resetColor();
                return;
            default:
                ConsoleColor::setColor(ConsoleColor::LIGHT_RED);
                std::cout << "\n❌ 无效的选择，请重新输入！" << std::endl;
                ConsoleColor::resetColor();
                pauseForUser();
                break;
        }
    }
}

// 显示演示主菜单
void MemoryDemo::showMainMenu() {
    system("cls");
    ConsoleColor::setColor(ConsoleColor::LIGHT_CYAN);
    std::cout << "\n";
    std::cout << "╔════════════════════════════════════════════════════════════════════════════════════════════════════════╗" << std::endl;
    std::cout << "║                                      内存管理模拟系统                                                    ║" << std::endl;
    std::cout << "║                                  Memory Management Simulator                                           ║" << std::endl;
    std::cout << "╚════════════════════════════════════════════════════════════════════════════════════════════════════════╝" << std::endl;
    
    ConsoleColor::setColor(ConsoleColor::WHITE);
    std::cout << "\n请选择演示功能：" << std::endl;
    std::cout << "\n";
    
    ConsoleColor::setColor(ConsoleColor::LIGHT_GREEN);
    std::cout << "1. 💾 连续内存分配演示" << std::endl;
    std::cout << "   └─ 首次适应、最佳适应、最坏适应、循环首次适应" << std::endl;
    std::cout << "\n";
    
    ConsoleColor::setColor(ConsoleColor::LIGHT_YELLOW);
    std::cout << "2. 📄 分页内存管理演示（开发中）" << std::endl;
    std::cout << "   └─ 页表管理、地址转换、页面分配" << std::endl;
    std::cout << "\n";
    std::cout << "3. 🔄 页面置换算法演示（开发中）" << std::endl;
    std::cout << "   └─ FIFO、LRU、LFU、Clock算法" << std::endl;
    std::cout << "\n";
    
    ConsoleColor::setColor(ConsoleColor::LIGHT_GREEN);
    std::cout << "4. 📊 分配算法性能比较" << std::endl;
    std::cout << "   └─ 对比不同分配算法的性能指标" << std::endl;
    std::cout << "\n";
    
    ConsoleColor::setColor(ConsoleColor::LIGHT_YELLOW);
    std::cout << "0. 🚪 返回主菜单" << std::endl;
    
    ConsoleColor::resetColor();
}

// 连续内存分配演示
void MemoryDemo::contiguousAllocationDemo() {
    system("cls");
    showTitle("连续内存分配演示");
    
    // 获取内存大小
    size_t memory_size = getMemorySize();
    
    // 显示分配策略菜单
    showAllocationStrategyMenu();
    
    int strategy_choice;
    std::cout << "\n请选择分配策略: ";
    std::cin >> strategy_choice;
    
    MemoryAllocationStrategy strategy;
    switch (strategy_choice) {
        case 1: strategy = MemoryAllocationStrategy::FIRST_FIT; break;
        case 2: strategy = MemoryAllocationStrategy::BEST_FIT; break;
        case 3: strategy = MemoryAllocationStrategy::WORST_FIT; break;
        case 4: strategy = MemoryAllocationStrategy::NEXT_FIT; break;
        default:
            strategy = MemoryAllocationStrategy::FIRST_FIT;
            ConsoleColor::setColor(ConsoleColor::LIGHT_YELLOW);
            std::cout << "⚠️ 使用默认策略：首次适应" << std::endl;
            ConsoleColor::resetColor();
            break;
    }
    
    // 选择场景
    std::cout << "\n请选择演示场景：" << std::endl;
    std::cout << "1. 🖥️ 轻量级应用场景" << std::endl;
    std::cout << "2. 🏢 服务器应用场景" << std::endl;
    
    int scenario_choice;
    std::cout << "\n请选择场景: ";
    std::cin >> scenario_choice;
    
    if (scenario_choice < 1 || scenario_choice > 2) {
        scenario_choice = 1;
        ConsoleColor::setColor(ConsoleColor::LIGHT_YELLOW);
        std::cout << "⚠️ 使用默认场景：轻量级应用" << std::endl;
        ConsoleColor::resetColor();
    }
    
    auto requests = createMemoryRequests(scenario_choice);
    runContiguousAllocationDemo(strategy, requests);
    
    pauseForUser();
}

// 显示连续分配策略菜单
void MemoryDemo::showAllocationStrategyMenu() {
    ConsoleColor::setColor(ConsoleColor::LIGHT_CYAN);
    std::cout << "\n📋 内存分配策略：" << std::endl;
    ConsoleColor::setColor(ConsoleColor::WHITE);
    std::cout << "1. 🎯 首次适应 (First Fit)" << std::endl;
    std::cout << "2. ✨ 最佳适应 (Best Fit)" << std::endl;
    std::cout << "3. 💥 最坏适应 (Worst Fit)" << std::endl;
    std::cout << "4. 🔄 循环首次适应 (Next Fit)" << std::endl;
    ConsoleColor::resetColor();
}

// 创建预设的内存请求序列
std::vector<MemoryRequest> MemoryDemo::createMemoryRequests(int scenario) {
    if (scenario >= 1 && scenario <= static_cast<int>(memory_scenarios_.size())) {
        return memory_scenarios_[scenario - 1];
    }
    return memory_scenarios_[0];
}

// 执行连续分配演示
void MemoryDemo::runContiguousAllocationDemo(MemoryAllocationStrategy strategy, 
                                           const std::vector<MemoryRequest>& requests) {
    system("cls");
    showTitle("连续内存分配演示 - " + getStrategyName(strategy));
    
    ContiguousAllocator allocator(getMemorySize(), strategy);
    
    std::cout << "🎬 开始内存分配演示..." << std::endl;
    std::cout << "策略: " << getStrategyName(strategy) << std::endl;
    
    for (const auto& request : requests) {
        std::cout << "\n" << std::string(80, '=') << std::endl;
        
        if (request.is_release) {
            std::cout << "🔓 释放操作：进程 " << request.process_id << std::endl;
            allocator.deallocateMemory(request.process_id);
        } else {
            std::cout << "📥 分配请求：进程 " << request.process_id 
                      << " (" << request.name << ") 请求 " << request.size << " KB" << std::endl;
            allocator.allocateMemory(request.size, request.process_id, request.name);
        }
        
        allocator.displayMemoryStatus();
        
        std::cout << "\n💡 按任意键继续下一步..." << std::endl;
        system("pause >nul");
    }
    
    // 最终状态
    std::cout << "\n" << std::string(80, '=') << std::endl;
    std::cout << "🏁 演示完成！最终内存状态：" << std::endl;
    allocator.displayMemoryStatus();
}

// 内存分配算法比较
void MemoryDemo::allocationComparisonDemo() {
    system("cls");
    showTitle("内存分配算法性能比较");
    
    size_t memory_size = getMemorySize();
    auto requests = createMemoryRequests(1);  // 使用场景1
    
    compareAllocationAlgorithms(requests);
    pauseForUser();
}

// 比较不同的分配算法
void MemoryDemo::compareAllocationAlgorithms(const std::vector<MemoryRequest>& requests) {
    struct AlgorithmResult {
        std::string name;
        double final_utilization;
        double final_fragmentation;
        int allocation_failures;
    };
    
    std::vector<AlgorithmResult> results;
    std::vector<MemoryAllocationStrategy> strategies = {
        MemoryAllocationStrategy::FIRST_FIT,
        MemoryAllocationStrategy::BEST_FIT,
        MemoryAllocationStrategy::WORST_FIT,
        MemoryAllocationStrategy::NEXT_FIT
    };
    
    for (auto strategy : strategies) {
        ContiguousAllocator allocator(getMemorySize(), strategy);
        int failures = 0;
        
        ConsoleColor::setColor(ConsoleColor::LIGHT_BLUE);
        std::cout << "\n🔄 测试 " << getStrategyName(strategy) << "..." << std::endl;
        ConsoleColor::resetColor();
        
        for (const auto& request : requests) {
            if (request.is_release) {
                allocator.deallocateMemory(request.process_id);
            } else {
                int result = allocator.allocateMemory(request.size, request.process_id, request.name);
                if (result == -1) {
                    failures++;
                }
            }
        }
        
        results.push_back({
            getStrategyName(strategy),
            allocator.getMemoryUtilization(),
            allocator.getFragmentation(),
            failures
        });
    }
    
    // 显示比较结果
    ConsoleColor::setColor(ConsoleColor::LIGHT_GREEN);
    std::cout << "\n📊 算法性能比较结果：" << std::endl;
    std::cout << "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━" << std::endl;
    
    std::cout << "┌─────────────────────┬────────────────┬────────────────┬────────────────┐" << std::endl;
    std::cout << "│      分配算法       │   内存利用率   │   碎片化程度   │   分配失败次数 │" << std::endl;
    std::cout << "├─────────────────────┼────────────────┼────────────────┼────────────────┤" << std::endl;
    
    for (const auto& result : results) {
        std::cout << "│ " << std::setw(19) << result.name
                  << " │ " << std::setw(13) << std::fixed << std::setprecision(1) << result.final_utilization << "%"
                  << " │ " << std::setw(13) << std::fixed << std::setprecision(1) << result.final_fragmentation << "%"
                  << " │ " << std::setw(14) << result.allocation_failures
                  << " │" << std::endl;
    }
    std::cout << "└─────────────────────┴────────────────┴────────────────┴────────────────┘" << std::endl;
    
    // 找出最优算法
    auto best_utilization = std::max_element(results.begin(), results.end(),
        [](const auto& a, const auto& b) { return a.final_utilization < b.final_utilization; });
    auto least_fragmentation = std::min_element(results.begin(), results.end(),
        [](const auto& a, const auto& b) { return a.final_fragmentation < b.final_fragmentation; });
    auto least_failures = std::min_element(results.begin(), results.end(),
        [](const auto& a, const auto& b) { return a.allocation_failures < b.allocation_failures; });
    
    std::cout << "\n🏆 性能分析：" << std::endl;
    std::cout << "• 最高内存利用率: " << best_utilization->name 
              << " (" << std::fixed << std::setprecision(1) << best_utilization->final_utilization << "%)" << std::endl;
    std::cout << "• 最低碎片化程度: " << least_fragmentation->name 
              << " (" << std::fixed << std::setprecision(1) << least_fragmentation->final_fragmentation << "%)" << std::endl;
    std::cout << "• 最少分配失败: " << least_failures->name 
              << " (" << least_failures->allocation_failures << " 次)" << std::endl;
    
    ConsoleColor::resetColor();
}

// 获取用户输入的内存大小
size_t MemoryDemo::getMemorySize() {
    size_t memory_size;
    ConsoleColor::setColor(ConsoleColor::LIGHT_YELLOW);
    std::cout << "\n💾 请输入总内存大小 (KB，建议512-2048): ";
    ConsoleColor::resetColor();
    std::cin >> memory_size;
    
    if (memory_size < 100 || memory_size > 10000) {
        ConsoleColor::setColor(ConsoleColor::LIGHT_YELLOW);
        std::cout << "⚠️ 使用默认内存大小: 1024 KB" << std::endl;
        ConsoleColor::resetColor();
        return 1024;
    }
    
    return memory_size;
}

// 暂停并等待用户按键
void MemoryDemo::pauseForUser() {
    ConsoleColor::setColor(ConsoleColor::CYAN);
    std::cout << "\n💡 按任意键继续..." << std::endl;
    ConsoleColor::resetColor();
    system("pause >nul");
}

// 清屏并显示标题
void MemoryDemo::showTitle(const std::string& title) {
    system("cls");
    ConsoleColor::setColor(ConsoleColor::LIGHT_CYAN);
    std::cout << "\n" << title << std::endl;
    ConsoleColor::resetColor();
}

// 获取分配策略名称
std::string MemoryDemo::getStrategyName(MemoryAllocationStrategy strategy) {
    return ContiguousAllocator::getStrategyName(strategy);
}

} // namespace ZTS_OS 