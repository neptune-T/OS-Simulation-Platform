#include "../../include/utils/scheduler_demo.h"
#include "../../include/algorithms/FCFSScheduler.h"
#include "../../include/algorithms/RoundRobinScheduler.h"
#include "../../include/algorithms/SJFScheduler.h"
#include "../../include/algorithms/PriorityScheduler.h"
#include <iostream>
#include <iomanip>
#include <limits>

/**
 * @file scheduler_demo.cpp
 * @brief 进程调度算法演示器实现
 * @author ZTS Operating System Design Team
 * @date 2024
 */

namespace ZTS_OS {

// 构造函数
SchedulerDemo::SchedulerDemo() {
    // 初始化预设的进程场景
    sample_scenarios_.push_back({
        Process(1, "记事本", 0, 5, ProcessPriority::NORMAL),
        Process(2, "计算器", 1, 3, ProcessPriority::HIGH),
        Process(3, "浏览器", 2, 8, ProcessPriority::LOW),
        Process(4, "音乐播放器", 3, 6, ProcessPriority::NORMAL)
    });
    
    sample_scenarios_.push_back({
        Process(1, "系统更新", 0, 10, ProcessPriority::LOW),
        Process(2, "杀毒软件", 2, 4, ProcessPriority::HIGHEST),
        Process(3, "文档编辑", 4, 6, ProcessPriority::NORMAL),
        Process(4, "视频播放", 5, 3, ProcessPriority::HIGH),
        Process(5, "文件下载", 7, 8, ProcessPriority::LOW)
    });
}

// 启动调度演示主界面
void SchedulerDemo::start() {
    showTitle("进程调度算法演示系统");
    
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
            case 1: {
                // 使用预设场景1
                ProcessList processes = createSampleProcesses(1);
                showAlgorithmMenu();
                int algo_choice;
                std::cout << "\n请选择调度算法: ";
                std::cin >> algo_choice;
                
                switch(algo_choice) {
                    case 1:
                        runAlgorithmDemo(SchedulerFactory::SchedulerType::FCFS, processes);
                        break;
                    case 2:
                        runAlgorithmDemo(SchedulerFactory::SchedulerType::ROUND_ROBIN, processes);
                        break;
                    case 3:
                        runAlgorithmDemo(SchedulerFactory::SchedulerType::SJF, processes);
                        break;
                    case 4:
                        runAlgorithmDemo(SchedulerFactory::SchedulerType::PRIORITY, processes);
                        break;
                    case 5:
                        compareAlgorithms(processes);
                        break;
                    default:
                        ConsoleColor::setColor(ConsoleColor::LIGHT_RED);
                        std::cout << "\n❌ 无效的选择！" << std::endl;
                        ConsoleColor::resetColor();
                        break;
                }
                pauseForUser();
                break;
            }
            case 2: {
                // 使用预设场景2
                ProcessList processes = createSampleProcesses(2);
                showAlgorithmMenu();
                int algo_choice;
                std::cout << "\n请选择调度算法: ";
                std::cin >> algo_choice;
                
                switch(algo_choice) {
                    case 1:
                        runAlgorithmDemo(SchedulerFactory::SchedulerType::FCFS, processes);
                        break;
                    case 2:
                        runAlgorithmDemo(SchedulerFactory::SchedulerType::ROUND_ROBIN, processes);
                        break;
                    case 3:
                        runAlgorithmDemo(SchedulerFactory::SchedulerType::SJF, processes);
                        break;
                    case 4:
                        runAlgorithmDemo(SchedulerFactory::SchedulerType::PRIORITY, processes);
                        break;
                    case 5:
                        compareAlgorithms(processes);
                        break;
                    default:
                        ConsoleColor::setColor(ConsoleColor::LIGHT_RED);
                        std::cout << "\n❌ 无效的选择！" << std::endl;
                        ConsoleColor::resetColor();
                        break;
                }
                pauseForUser();
                break;
            }
            case 3: {
                ConsoleColor::setColor(ConsoleColor::LIGHT_YELLOW);
                std::cout << "\n🔧 自定义进程功能正在开发中，敬请期待！" << std::endl;
                ConsoleColor::resetColor();
                pauseForUser();
                break;
            }
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
void SchedulerDemo::showMainMenu() {
    system("cls");
    ConsoleColor::setColor(ConsoleColor::LIGHT_CYAN);
    std::cout << "\n";
    std::cout << "╔════════════════════════════════════════════════════════════════════════════════════════════════════════╗" << std::endl;
    std::cout << "║                                      进程调度算法演示系统                                                  ║" << std::endl;
    std::cout << "║                                  Process Scheduling Algorithm Demo                                     ║" << std::endl;
    std::cout << "╚════════════════════════════════════════════════════════════════════════════════════════════════════════╝" << std::endl;
    
    ConsoleColor::setColor(ConsoleColor::WHITE);
    std::cout << "\n请选择演示场景：" << std::endl;
    std::cout << "\n";
    
    ConsoleColor::setColor(ConsoleColor::LIGHT_GREEN);
    std::cout << "1. 📱 场景一：轻量级应用调度" << std::endl;
    std::cout << "   └─ 包含4个进程：记事本、计算器、浏览器、音乐播放器" << std::endl;
    std::cout << "\n";
    std::cout << "2. 🖥️  场景二：混合负载调度" << std::endl;
    std::cout << "   └─ 包含5个进程：系统更新、杀毒软件、文档编辑、视频播放、文件下载" << std::endl;
    std::cout << "\n";
    std::cout << "3. ⚙️  自定义进程（开发中）" << std::endl;
    std::cout << "   └─ 手动创建和配置进程参数" << std::endl;
    std::cout << "\n";
    
    ConsoleColor::setColor(ConsoleColor::LIGHT_YELLOW);
    std::cout << "0. 🚪 返回主菜单" << std::endl;
    
    ConsoleColor::resetColor();
}

// 显示算法选择菜单
void SchedulerDemo::showAlgorithmMenu() {
    system("cls");
    ConsoleColor::setColor(ConsoleColor::LIGHT_CYAN);
    std::cout << "\n";
    std::cout << "╔════════════════════════════════════════════════════════════════════════════════════════════════════════╗" << std::endl;
    std::cout << "║                                        选择调度算法                                                      ║" << std::endl;
    std::cout << "║                                     Select Scheduling Algorithm                                         ║" << std::endl;
    std::cout << "╚════════════════════════════════════════════════════════════════════════════════════════════════════════╝" << std::endl;
    
    ConsoleColor::setColor(ConsoleColor::LIGHT_GREEN);
    std::cout << "\n1. 🔄 FCFS (先来先服务)" << std::endl;
    std::cout << "   └─ 非抢占式，按到达时间顺序执行" << std::endl;
    std::cout << "\n";
    
    std::cout << "2. ⏰ Round Robin (时间片轮转)" << std::endl;
    std::cout << "   └─ 抢占式，固定时间片循环执行" << std::endl;
    std::cout << "\n";
    
    std::cout << "3. ⚡ SJF (最短作业优先)" << std::endl;
    std::cout << "   └─ 非抢占式，选择执行时间最短的进程" << std::endl;
    std::cout << "\n";
    
    std::cout << "4. 🎯 Priority (优先级调度)" << std::endl;
    std::cout << "   └─ 非抢占式，按优先级顺序执行" << std::endl;
    std::cout << "\n";
    
    ConsoleColor::setColor(ConsoleColor::LIGHT_YELLOW);
    std::cout << "5. 📊 算法比较演示" << std::endl;
    std::cout << "   └─ 对比所有算法的性能" << std::endl;
    
    ConsoleColor::resetColor();
}

// 创建预设的示例进程集
ProcessList SchedulerDemo::createSampleProcesses(int scenario) {
    if (scenario >= 1 && scenario <= static_cast<int>(sample_scenarios_.size())) {
        return sample_scenarios_[scenario - 1];
    }
    return ProcessList();
}

// 执行指定算法的演示
void SchedulerDemo::runAlgorithmDemo(SchedulerFactory::SchedulerType algorithm_type, 
                                   const ProcessList& processes) {
    system("cls");
    ConsoleColor::setColor(ConsoleColor::LIGHT_CYAN);
    std::cout << "\n";
    std::cout << "╔════════════════════════════════════════════════════════════════════════════════════════════════════════╗" << std::endl;
    std::cout << "║                                        调度算法演示                                                      ║" << std::endl;
    std::cout << "╚════════════════════════════════════════════════════════════════════════════════════════════════════════╝" << std::endl;
    
    // 显示进程信息表
    displayProcessTable(processes);
    
    // 创建调度器并执行调度
    SchedulingResult result;
    
    switch(algorithm_type) {
        case SchedulerFactory::SchedulerType::FCFS: {
            FCFSScheduler scheduler;
            ConsoleColor::setColor(ConsoleColor::LIGHT_BLUE);
            std::cout << "\n🎯 开始执行 FCFS 调度算法..." << std::endl;
            ConsoleColor::resetColor();
            result = scheduler.schedule(processes);
            break;
        }
        case SchedulerFactory::SchedulerType::ROUND_ROBIN: {
            int time_quantum = getTimeQuantum();
            RoundRobinScheduler scheduler(time_quantum);
            ConsoleColor::setColor(ConsoleColor::LIGHT_BLUE);
            std::cout << "\n🎯 开始执行 Round Robin 调度算法..." << std::endl;
            ConsoleColor::resetColor();
            result = scheduler.schedule(processes);
            break;
        }
        case SchedulerFactory::SchedulerType::SJF: {
            SJFScheduler scheduler(false); // 非抢占式
            ConsoleColor::setColor(ConsoleColor::LIGHT_BLUE);
            std::cout << "\n🎯 开始执行 SJF 调度算法..." << std::endl;
            ConsoleColor::resetColor();
            result = scheduler.schedule(processes);
            break;
        }
        case SchedulerFactory::SchedulerType::PRIORITY: {
            PriorityScheduler scheduler(false); // 非抢占式
            ConsoleColor::setColor(ConsoleColor::LIGHT_BLUE);
            std::cout << "\n🎯 开始执行 Priority 调度算法..." << std::endl;
            ConsoleColor::resetColor();
            result = scheduler.schedule(processes);
            break;
        }
    }
    
    // 显示结果
    ConsoleColor::setColor(ConsoleColor::LIGHT_GREEN);
    std::cout << "\n📊 调度结果统计：" << std::endl;
    std::cout << "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━" << std::endl;
    std::cout << "平均等待时间: " << std::fixed << std::setprecision(2) << result.average_waiting_time << " 时间单位" << std::endl;
    std::cout << "平均周转时间: " << std::fixed << std::setprecision(2) << result.average_turnaround_time << " 时间单位" << std::endl;
    std::cout << "平均响应时间: " << std::fixed << std::setprecision(2) << result.average_response_time << " 时间单位" << std::endl;
    std::cout << "CPU利用率: " << std::fixed << std::setprecision(2) << result.cpu_utilization << "%" << std::endl;
    std::cout << "总执行时间: " << result.total_time << " 时间单位" << std::endl;
    ConsoleColor::resetColor();
}

// 显示进程信息表
void SchedulerDemo::displayProcessTable(const ProcessList& processes) {
    ConsoleColor::setColor(ConsoleColor::WHITE);
    std::cout << "\n📋 进程信息表：" << std::endl;
    std::cout << "┌─────┬──────────────┬──────────┬──────────┬──────────┐" << std::endl;
    std::cout << "│ PID │    进程名    │ 到达时间 │ 执行时间 │  优先级  │" << std::endl;
    std::cout << "├─────┼──────────────┼──────────┼──────────┼──────────┤" << std::endl;
    
    for (const auto& process : processes) {
        std::cout << "│ " << std::setw(3) << process.getPID() 
                  << " │ " << std::setw(12) << process.getName()
                  << " │ " << std::setw(8) << process.getArrivalTime()
                  << " │ " << std::setw(8) << process.getBurstTime()
                  << " │ " << std::setw(8) << process.getPriorityString()
                  << " │" << std::endl;
    }
    std::cout << "└─────┴──────────────┴──────────┴──────────┴──────────┘" << std::endl;
    ConsoleColor::resetColor();
}

// 暂停并等待用户按键
void SchedulerDemo::pauseForUser() {
    ConsoleColor::setColor(ConsoleColor::CYAN);
    std::cout << "\n💡 按任意键继续..." << std::endl;
    ConsoleColor::resetColor();
    system("pause >nul");
}

// 清屏并显示标题
void SchedulerDemo::showTitle(const std::string& title) {
    system("cls");
    ConsoleColor::setColor(ConsoleColor::LIGHT_CYAN);
    std::cout << "\n" << title << std::endl;
    ConsoleColor::resetColor();
}

// 获取用户输入的时间片大小
int SchedulerDemo::getTimeQuantum() {
    int time_quantum;
    ConsoleColor::setColor(ConsoleColor::LIGHT_YELLOW);
    std::cout << "\n⏰ 请输入时间片大小 (建议1-5): ";
    ConsoleColor::resetColor();
    std::cin >> time_quantum;
    
    if (time_quantum <= 0 || time_quantum > 20) {
        ConsoleColor::setColor(ConsoleColor::LIGHT_YELLOW);
        std::cout << "⚠️ 使用默认时间片大小: 2" << std::endl;
        ConsoleColor::resetColor();
        return 2;
    }
    
    return time_quantum;
}

// 比较多种算法
void SchedulerDemo::compareAlgorithms(const ProcessList& processes) {
    system("cls");
    ConsoleColor::setColor(ConsoleColor::LIGHT_CYAN);
    std::cout << "\n";
    std::cout << "╔════════════════════════════════════════════════════════════════════════════════════════════════════════╗" << std::endl;
    std::cout << "║                                      算法性能比较                                                       ║" << std::endl;
    std::cout << "╚════════════════════════════════════════════════════════════════════════════════════════════════════════╝" << std::endl;
    
    // 显示进程信息表
    displayProcessTable(processes);
    
    std::vector<std::pair<std::string, SchedulingResult>> results;
    
    // FCFS
    {
        FCFSScheduler scheduler;
        ConsoleColor::setColor(ConsoleColor::LIGHT_BLUE);
        std::cout << "\n🔄 正在执行 FCFS 算法..." << std::endl;
        ConsoleColor::resetColor();
        auto result = scheduler.schedule(processes);
        results.push_back({"FCFS", result});
    }
    
    // Round Robin
    {
        RoundRobinScheduler scheduler(2); // 使用默认时间片2
        ConsoleColor::setColor(ConsoleColor::LIGHT_BLUE);
        std::cout << "\n⏰ 正在执行 Round Robin 算法..." << std::endl;
        ConsoleColor::resetColor();
        auto result = scheduler.schedule(processes);
        results.push_back({"Round Robin", result});
    }
    
    // SJF
    {
        SJFScheduler scheduler(false);
        ConsoleColor::setColor(ConsoleColor::LIGHT_BLUE);
        std::cout << "\n⚡ 正在执行 SJF 算法..." << std::endl;
        ConsoleColor::resetColor();
        auto result = scheduler.schedule(processes);
        results.push_back({"SJF", result});
    }
    
    // Priority
    {
        PriorityScheduler scheduler(false);
        ConsoleColor::setColor(ConsoleColor::LIGHT_BLUE);
        std::cout << "\n🎯 正在执行 Priority 算法..." << std::endl;
        ConsoleColor::resetColor();
        auto result = scheduler.schedule(processes);
        results.push_back({"Priority", result});
    }
    
    // 显示比较结果
    ConsoleColor::setColor(ConsoleColor::LIGHT_GREEN);
    std::cout << "\n📊 算法性能比较结果：" << std::endl;
    std::cout << "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━" << std::endl;
    
    std::cout << "┌─────────────┬──────────────┬──────────────┬──────────────┬──────────────┬──────────────┐" << std::endl;
    std::cout << "│   算法名称  │  平均等待时间│  平均周转时间│  平均响应时间│   CPU利用率  │   总执行时间 │" << std::endl;
    std::cout << "├─────────────┼──────────────┼──────────────┼──────────────┼──────────────┼──────────────┤" << std::endl;
    
    for (const auto& pair : results) {
        const std::string& name = pair.first;
        const SchedulingResult& result = pair.second;
        std::cout << "│ " << std::setw(11) << name
                  << " │ " << std::setw(12) << std::fixed << std::setprecision(2) << result.average_waiting_time
                  << " │ " << std::setw(12) << std::fixed << std::setprecision(2) << result.average_turnaround_time
                  << " │ " << std::setw(12) << std::fixed << std::setprecision(2) << result.average_response_time
                  << " │ " << std::setw(11) << std::fixed << std::setprecision(1) << result.cpu_utilization << "%"
                  << " │ " << std::setw(12) << result.total_time
                  << " │" << std::endl;
    }
    std::cout << "└─────────────┴──────────────┴──────────────┴──────────────┴──────────────┴──────────────┘" << std::endl;
    
    // 找出最优算法
    std::cout << "\n🏆 性能分析：" << std::endl;
    
    // 最短平均等待时间
    auto min_wait = std::min_element(results.begin(), results.end(),
        [](const auto& a, const auto& b) { return a.second.average_waiting_time < b.second.average_waiting_time; });
    std::cout << "• 最短平均等待时间: " << min_wait->first << " (" << std::fixed << std::setprecision(2) 
              << min_wait->second.average_waiting_time << ")" << std::endl;
    
    // 最短平均周转时间
    auto min_turnaround = std::min_element(results.begin(), results.end(),
        [](const auto& a, const auto& b) { return a.second.average_turnaround_time < b.second.average_turnaround_time; });
    std::cout << "• 最短平均周转时间: " << min_turnaround->first << " (" << std::fixed << std::setprecision(2) 
              << min_turnaround->second.average_turnaround_time << ")" << std::endl;
    
    // 最短平均响应时间
    auto min_response = std::min_element(results.begin(), results.end(),
        [](const auto& a, const auto& b) { return a.second.average_response_time < b.second.average_response_time; });
    std::cout << "• 最短平均响应时间: " << min_response->first << " (" << std::fixed << std::setprecision(2) 
              << min_response->second.average_response_time << ")" << std::endl;
    
    ConsoleColor::resetColor();
}

} // namespace ZTS_OS 