// #include "../../include/algorithms/FCFSScheduler.h"
// #include <algorithm>
// #include <iostream>
// #include <iomanip>

// /**
//  * @file FCFSScheduler.cpp
//  * @brief 先来先服务(FCFS)调度算法实现
//  * @author ZTS Operating System Design Team
//  * @date 2024
//  */

// namespace ZTS_OS {

// // 构造函数
// FCFSScheduler::FCFSScheduler() 
//     : Scheduler("FCFS", "先来先服务调度算法 - 按进程到达时间顺序执行，非抢占式") {
// }

// // 执行FCFS调度算法
// SchedulingResult FCFSScheduler::schedule(const ProcessList& processes) {
//     // 验证输入
//     validateProcesses(processes);
    
//     // 创建进程副本用于调度
//     ProcessList scheduled_processes = processes;
//     resetProcesses(scheduled_processes);
    
//     // 按到达时间排序
//     sortByArrivalTime(scheduled_processes);
    
//     // 执行调度
//     int current_time = 0;
//     std::vector<std::pair<int, std::string>> gantt_chart; // 用于甘特图显示
    
//     std::cout << "\n🔧 FCFS调度过程演示：" << std::endl;
//     std::cout << "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━" << std::endl;
    
//     for (auto& process : scheduled_processes) {
//         // 等待进程到达
//         if (current_time < process.getArrivalTime()) {
//             std::cout << "时间 " << current_time << "-" << process.getArrivalTime() 
//                       << ": CPU空闲，等待进程到达" << std::endl;
//             current_time = process.getArrivalTime();
//         }
        
//         // 设置进程开始时间和响应时间
//         process.setStartTime(current_time);
//         process.setResponseTime(current_time - process.getArrivalTime());
        
//         std::cout << "时间 " << current_time << ": 开始执行进程 P" << process.getPID() 
//                   << " (" << process.getName() << ")" << std::endl;
//         std::cout << "  ├─ 到达时间: " << process.getArrivalTime() << std::endl;
//         std::cout << "  ├─ 执行时间: " << process.getBurstTime() << std::endl;
//         std::cout << "  └─ 响应时间: " << process.getResponseTime() << std::endl;
        
//         // 执行进程
//         process.setState(ProcessState::RUNNING);
//         current_time += process.getBurstTime();
        
//         // 完成进程
//         process.setState(ProcessState::TERMINATED);
//         process.setCompletionTime(current_time);
//         process.calculateTimes(current_time);
        
//         std::cout << "时间 " << current_time << ": 进程 P" << process.getPID() 
//                   << " 执行完成" << std::endl;
//         std::cout << "  ├─ 完成时间: " << process.getCompletionTime() << std::endl;
//         std::cout << "  ├─ 周转时间: " << process.getTurnaroundTime() << std::endl;
//         std::cout << "  └─ 等待时间: " << process.getWaitingTime() << std::endl;
//         std::cout << std::endl;
        
//         // 记录甘特图信息
//         gantt_chart.push_back({process.getBurstTime(), "P" + std::to_string(process.getPID())});
//     }
    
//     // 计算并返回结果
//     SchedulingResult result = calculateStatistics(scheduled_processes, current_time);
    
//     std::cout << "📊 FCFS调度完成！总执行时间: " << current_time << " 时间单位" << std::endl;
//     std::cout << "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━" << std::endl;
    
//     return result;
// }

// // 获取算法类型
// std::string FCFSScheduler::getAlgorithmType() const {
//     return "先来先服务 (First Come First Serve)";
// }

// // 是否为抢占式调度
// bool FCFSScheduler::isPreemptive() const {
//     return false; // FCFS是非抢占式调度
// }

// // 显示FCFS算法的详细信息
// void FCFSScheduler::displayInfo() const {
//     std::cout << "╔══════════════════════════════════════════════════════════════════════════════════════════════════════╗" << std::endl;
//     std::cout << "║                                  FCFS调度算法详细信息                                                  ║" << std::endl;
//     std::cout << "╠══════════════════════════════════════════════════════════════════════════════════════════════════════╣" << std::endl;
//     std::cout << "║ 算法名称: " << std::setw(82) << std::left << getName() << "║" << std::endl;
//     std::cout << "║ 算法类型: " << std::setw(82) << std::left << getAlgorithmType() << "║" << std::endl;
//     std::cout << "║ 调度方式: " << std::setw(82) << std::left << (isPreemptive() ? "抢占式" : "非抢占式") << "║" << std::endl;
//     std::cout << "╠══════════════════════════════════════════════════════════════════════════════════════════════════════╣" << std::endl;
//     std::cout << "║ 算法描述:                                                                                            ║" << std::endl;
//     std::cout << "║   " << std::setw(94) << std::left << getDescription() << "║" << std::endl;
//     std::cout << "╠══════════════════════════════════════════════════════════════════════════════════════════════════════╣" << std::endl;
//     std::cout << "║ 算法特点:                                                                                            ║" << std::endl;
//     std::cout << "║   ✓ 实现简单，易于理解                                                                              ║" << std::endl;
//     std::cout << "║   ✓ 对所有进程公平，无饥饿现象                                                                      ║" << std::endl;
//     std::cout << "║   ✗ 可能导致"护航效应"(长作业阻塞短作业)                                                           ║" << std::endl;
//     std::cout << "║   ✗ 平均等待时间可能较长                                                                            ║" << std::endl;
//     std::cout << "║   ✗ 不适合交互式系统                                                                                ║" << std::endl;
//     std::cout << "╠══════════════════════════════════════════════════════════════════════════════════════════════════════╣" << std::endl;
//     std::cout << "║ 适用场景:                                                                                            ║" << std::endl;
//     std::cout << "║   • 批处理系统                                                                                       ║" << std::endl;
//     std::cout << "║   • 作业执行时间相近的系统                                                                          ║" << std::endl;
//     std::cout << "║   • 对响应时间要求不高的系统                                                                        ║" << std::endl;
//     std::cout << "╚══════════════════════════════════════════════════════════════════════════════════════════════════════╝" << std::endl;
// }

// // 按到达时间排序进程列表
// void FCFSScheduler::sortByArrivalTime(ProcessList& processes) const {
//     std::sort(processes.begin(), processes.end(), Process::compareArrivalTime);
// }

// } // namespace ZTS_OS 