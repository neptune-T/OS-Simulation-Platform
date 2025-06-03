#include "../../include/algorithms/PriorityScheduler.h"
#include <algorithm>
#include <iostream>
#include <iomanip>
#include <climits>

/**
 * @file PriorityScheduler.cpp
 * @brief 优先级调度算法实现
 * @author ZTS Operating System Design Team
 * @date 2025
 */

namespace ZTS_OS {

// 构造函数
PriorityScheduler::PriorityScheduler(bool preemptive) 
    : Scheduler(preemptive ? "抢占式优先级" : "非抢占式优先级", 
                preemptive ? "抢占式优先级调度算法 - 高优先级进程可以抢占低优先级进程" 
                          : "非抢占式优先级调度算法 - 选择优先级最高的进程执行"),
      preemptive_(preemptive) {
}

// 执行优先级调度算法
SchedulingResult PriorityScheduler::schedule(const ProcessList& processes) {
    // 验证输入
    validateProcesses(processes);
    
    if (preemptive_) {
        return schedulePreemptive(const_cast<ProcessList&>(processes));
    } else {
        return scheduleNonPreemptive(const_cast<ProcessList&>(processes));
    }
}

// 获取算法类型
std::string PriorityScheduler::getAlgorithmType() const {
    return preemptive_ ? "抢占式优先级调度 (Preemptive Priority)" : "非抢占式优先级调度 (Non-Preemptive Priority)";
}

// 是否为抢占式调度
bool PriorityScheduler::isPreemptive() const {
    return preemptive_;
}

// 显示优先级算法的详细信息
void PriorityScheduler::displayInfo() const {
    std::cout << "===========================================" << std::endl;
    std::cout << "      " << getAlgorithmType() << "详细信息          " << std::endl;
    std::cout << "===========================================" << std::endl;
    std::cout << "算法名称: " << getName() << std::endl;
    std::cout << "算法类型: " << getAlgorithmType() << std::endl;
    std::cout << "调度方式: " << (isPreemptive() ? "抢占式" : "非抢占式") << std::endl;
    std::cout << "优先级规则: 数字越小优先级越高 (1=最高, 5=最低)" << std::endl;
    std::cout << "===========================================" << std::endl;
    std::cout << "算法描述:" << std::endl;
    std::cout << "  " << getDescription() << std::endl;
    std::cout << "===========================================" << std::endl;
    std::cout << "算法特点:" << std::endl;
    std::cout << "  + 能够区分不同重要性的进程" << std::endl;
    std::cout << "  + 满足系统的紧急性要求" << std::endl;
    if (preemptive_) {
        std::cout << "  + 高优先级进程响应时间短" << std::endl;
        std::cout << "  - 低优先级进程可能饥饿" << std::endl;
        std::cout << "  - 上下文切换开销" << std::endl;
    } else {
        std::cout << "  + 实现简单，开销小" << std::endl;
        std::cout << "  - 响应时间可能较长" << std::endl;
        std::cout << "  - 可能导致优先级反转" << std::endl;
    }
    std::cout << "===========================================" << std::endl;
    std::cout << "适用场景:" << std::endl;
    std::cout << "  * 实时系统" << std::endl;
    std::cout << "  * 有明确优先级需求的系统" << std::endl;
    std::cout << "  * 批处理系统" << std::endl;
    std::cout << "===========================================" << std::endl;
}

// 非抢占式优先级调度
SchedulingResult PriorityScheduler::scheduleNonPreemptive(ProcessList& processes) {
    resetProcesses(processes);
    
    int current_time = 0;
    std::vector<bool> completed(processes.size(), false);
    int completed_count = 0;
    
    std::cout << "\n=== 非抢占式优先级调度过程演示 ===" << std::endl;
    std::cout << "======================================" << std::endl;
    std::cout << "优先级规则: 1(最高) -> 5(最低)" << std::endl;
    std::cout << "======================================" << std::endl;
    
    while (completed_count < static_cast<int>(processes.size())) {
        // 找到当前时间已到达且未完成的最高优先级进程
        int selected_index = findHighestPriority(processes, current_time);
        
        if (selected_index == -1) {
            // 没有可执行的进程，找到下一个到达时间
            int next_arrival = INT_MAX;
            for (size_t i = 0; i < processes.size(); ++i) {
                if (!completed[i] && processes[i].getArrivalTime() > current_time) {
                    next_arrival = std::min(next_arrival, processes[i].getArrivalTime());
                }
            }
            
            if (next_arrival != INT_MAX) {
                std::cout << "时间 " << current_time << "-" << next_arrival 
                          << ": CPU空闲，等待进程到达" << std::endl;
                current_time = next_arrival;
                continue;
            } else {
                break;
            }
        }
        
        Process& process = processes[selected_index];
        
        // 设置进程时间信息
        process.setStartTime(current_time);
        process.setResponseTime(current_time - process.getArrivalTime());
        
        std::cout << "时间 " << current_time << ": 选择进程 P" << process.getPID() 
                  << " (" << process.getName() << ")" << std::endl;
        std::cout << "  到达时间: " << process.getArrivalTime() << std::endl;
        std::cout << "  执行时间: " << process.getBurstTime() << std::endl;
        std::cout << "  优先级: " << static_cast<int>(process.getPriority()) 
                  << " (" << process.getPriorityString() << ")" << std::endl;
        std::cout << "  响应时间: " << process.getResponseTime() << std::endl;
        
        // 执行进程
        process.setState(ProcessState::RUNNING);
        current_time += process.getBurstTime();
        
        // 完成进程
        process.setState(ProcessState::TERMINATED);
        process.setCompletionTime(current_time);
        process.calculateTimes(current_time);
        completed[selected_index] = true;
        completed_count++;
        
        std::cout << "时间 " << current_time << ": 进程 P" << process.getPID() 
                  << " 执行完成" << std::endl;
        std::cout << "  完成时间: " << process.getCompletionTime() << std::endl;
        std::cout << "  周转时间: " << process.getTurnaroundTime() << std::endl;
        std::cout << "  等待时间: " << process.getWaitingTime() << std::endl;
        std::cout << std::endl;
    }
    
    // 计算并返回结果
    SchedulingResult result = calculateStatistics(processes, current_time);
    
    std::cout << "=== 优先级调度完成！总执行时间: " << current_time << " 时间单位 ===" << std::endl;
    std::cout << "======================================" << std::endl;
    
    return result;
}

// 抢占式优先级调度
SchedulingResult PriorityScheduler::schedulePreemptive(ProcessList& processes) {
    resetProcesses(processes);
    
    int current_time = 0;
    std::vector<bool> completed(processes.size(), false);
    int completed_count = 0;
    int current_process = -1;
    
    std::cout << "\n=== 抢占式优先级调度过程演示 ===" << std::endl;
    std::cout << "======================================" << std::endl;
    std::cout << "优先级规则: 1(最高) -> 5(最低)" << std::endl;
    std::cout << "======================================" << std::endl;
    
    while (completed_count < static_cast<int>(processes.size())) {
        // 找到当前时间最高优先级的进程
        int selected_index = findHighestPriority(processes, current_time);
        
        if (selected_index == -1) {
            // 没有可执行的进程，移动到下一个进程到达时间
            int next_arrival = INT_MAX;
            for (size_t i = 0; i < processes.size(); ++i) {
                if (!completed[i] && processes[i].getArrivalTime() > current_time) {
                    next_arrival = std::min(next_arrival, processes[i].getArrivalTime());
                }
            }
            
            if (next_arrival != INT_MAX) {
                std::cout << "时间 " << current_time << "-" << next_arrival 
                          << ": CPU空闲，等待进程到达" << std::endl;
                current_time = next_arrival;
                continue;
            } else {
                break;
            }
        }
        
        Process& process = processes[selected_index];
        
        // 检查是否需要抢占
        if (current_process != selected_index) {
            if (current_process != -1) {
                std::cout << "时间 " << current_time << ": 进程P" << processes[current_process].getPID() 
                          << "(优先级" << static_cast<int>(processes[current_process].getPriority()) << ")"
                          << "被进程P" << process.getPID() 
                          << "(优先级" << static_cast<int>(process.getPriority()) << ")抢占" << std::endl;
            }
            
            // 设置首次运行时间
            if (process.isFirstRun()) {
                process.setStartTime(current_time);
                process.setResponseTime(current_time - process.getArrivalTime());
                process.setFirstRun(false);
            }
            
            std::cout << "时间 " << current_time << ": 开始执行进程 P" << process.getPID() 
                      << " (" << process.getName() << ")" << std::endl;
            std::cout << "  优先级: " << static_cast<int>(process.getPriority()) 
                      << " (" << process.getPriorityString() << ")" << std::endl;
            std::cout << "  剩余时间: " << process.getRemainingTime() << std::endl;
            
            current_process = selected_index;
        }
        
        // 计算下一个关键时间点
        int next_event_time = current_time + 1; // 最小执行1个时间单位
        
        // 查看是否有更高优先级的进程将要到达
        for (size_t i = 0; i < processes.size(); ++i) {
            if (!completed[i] && processes[i].getArrivalTime() > current_time) {
                int arrival_time = processes[i].getArrivalTime();
                if (arrival_time < current_time + process.getRemainingTime() &&
                    processes[i].getPriority() < process.getPriority()) {
                    next_event_time = std::min(next_event_time, arrival_time);
                    break;
                }
            }
        }
        
        // 执行进程直到下一个事件或完成
        int execution_time = std::min(next_event_time - current_time, process.getRemainingTime());
        process.setState(ProcessState::RUNNING);
        process.execute(execution_time);
        current_time += execution_time;
        
        // 检查进程是否完成
        if (process.isCompleted()) {
            process.setState(ProcessState::TERMINATED);
            process.setCompletionTime(current_time);
            process.calculateTimes(current_time);
            completed[selected_index] = true;
            completed_count++;
            current_process = -1;
            
            std::cout << "时间 " << current_time << ": 进程P" << process.getPID() << "执行完成！" << std::endl;
            std::cout << "  完成时间: " << process.getCompletionTime() << std::endl;
            std::cout << "  周转时间: " << process.getTurnaroundTime() << std::endl;
            std::cout << "  等待时间: " << process.getWaitingTime() << std::endl;
            std::cout << std::endl;
        }
    }
    
    // 计算并返回结果
    SchedulingResult result = calculateStatistics(processes, current_time);
    
    std::cout << "=== 抢占式优先级调度完成！总执行时间: " << current_time << " 时间单位 ===" << std::endl;
    std::cout << "======================================" << std::endl;
    
    return result;
}

// 按优先级排序进程列表
void PriorityScheduler::sortByPriority(ProcessList& processes) const {
    std::sort(processes.begin(), processes.end(), Process::comparePriority);
}

// 找到最高优先级的进程
int PriorityScheduler::findHighestPriority(const ProcessList& processes, int current_time) const {
    int selected_index = -1;
    ProcessPriority highest_priority = ProcessPriority::LOWEST;
    
    for (size_t i = 0; i < processes.size(); ++i) {
        if (processes[i].getArrivalTime() <= current_time &&
            processes[i].getState() != ProcessState::TERMINATED &&
            processes[i].getRemainingTime() > 0 &&
            processes[i].getPriority() < highest_priority) {
            highest_priority = processes[i].getPriority();
            selected_index = i;
        }
    }
    
    return selected_index;
}

} // namespace ZTS_OS 