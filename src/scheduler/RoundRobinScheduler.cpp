#include "../../include/algorithms/RoundRobinScheduler.h"
#include <algorithm>
#include <iostream>
#include <iomanip>
#include <climits>

/**
 * @file RoundRobinScheduler.cpp
 * @brief 时间片轮转(Round Robin)调度算法实现
 * @author ZTS Operating System Design Team
 * @date 2025
 */

namespace ZTS_OS {

// 构造函数
RoundRobinScheduler::RoundRobinScheduler(int time_quantum) 
    : Scheduler("Round Robin", "时间片轮转调度算法 - 抢占式，每个进程分配固定时间片"), 
      time_quantum_(time_quantum) {
    if (time_quantum <= 0) {
        throw std::invalid_argument("时间片大小必须大于0");
    }
}

// 执行Round Robin调度算法
SchedulingResult RoundRobinScheduler::schedule(const ProcessList& processes) {
    // 验证输入
    validateProcesses(processes);
    
    // 创建进程副本用于调度
    ProcessList scheduled_processes = processes;
    resetProcesses(scheduled_processes);
    
    // 初始化变量
    int current_time = 0;
    int last_check_time = 0;
    std::queue<size_t> ready_queue;
    std::vector<bool> completed(scheduled_processes.size(), false);
    int completed_count = 0;
    
    std::cout << "\n=== Round Robin调度过程演示 (时间片=" << time_quantum_ << ") ===" << std::endl;
    std::cout << "======================================" << std::endl;
    
    // 初始化就绪队列
    initializeReadyQueue(scheduled_processes, ready_queue, current_time);
    
    while (completed_count < static_cast<int>(scheduled_processes.size())) {
        // 检查并添加新到达的进程
        checkAndAddArrivedProcesses(scheduled_processes, ready_queue, current_time, last_check_time);
        
        if (ready_queue.empty()) {
            // 没有就绪进程，CPU空闲
            int next_arrival = INT_MAX;
            for (size_t i = 0; i < scheduled_processes.size(); ++i) {
                if (!completed[i] && scheduled_processes[i].getArrivalTime() > current_time) {
                    next_arrival = std::min(next_arrival, scheduled_processes[i].getArrivalTime());
                }
            }
            
            if (next_arrival != INT_MAX) {
                std::cout << "时间 " << current_time << "-" << next_arrival 
                          << ": CPU空闲，等待进程到达" << std::endl;
                current_time = next_arrival;
                continue;
            } else {
                break; // 所有进程都已完成
            }
        }
        
        // 从就绪队列取出下一个进程
        size_t process_index = ready_queue.front();
        ready_queue.pop();
        Process& process = scheduled_processes[process_index];
        
        // 设置首次运行时间
        if (process.isFirstRun()) {
            process.setStartTime(current_time);
            process.setResponseTime(current_time - process.getArrivalTime());
            process.setFirstRun(false);
        }
        
        // 计算本次执行时间
        int execution_time = std::min(time_quantum_, process.getRemainingTime());
        
        std::cout << "时间 " << current_time << ": 执行进程 P" << process.getPID() 
                  << " (" << process.getName() << ")" << std::endl;
        std::cout << "  剩余时间: " << process.getRemainingTime() 
                  << " -> " << (process.getRemainingTime() - execution_time) << std::endl;
        
        // 执行进程
        process.setState(ProcessState::RUNNING);
        process.execute(execution_time);
        current_time += execution_time;
        
        // 检查进程是否完成
        if (process.isCompleted()) {
            process.setState(ProcessState::TERMINATED);
            process.setCompletionTime(current_time);
            process.calculateTimes(current_time);
            completed[process_index] = true;
            completed_count++;
            
            std::cout << "  进程P" << process.getPID() << "执行完成！" << std::endl;
            std::cout << "  完成时间: " << process.getCompletionTime() << std::endl;
            std::cout << "  周转时间: " << process.getTurnaroundTime() << std::endl;
            std::cout << "  等待时间: " << process.getWaitingTime() << std::endl;
        } else {
            // 时间片用完，进程重新回到就绪队列末尾
            process.setState(ProcessState::READY);
            std::cout << "  时间片用完，进程P" << process.getPID() << "回到就绪队列" << std::endl;
        }
        
        // 检查并添加新到达的进程
        checkAndAddArrivedProcesses(scheduled_processes, ready_queue, current_time, last_check_time);
        
        // 如果进程未完成，重新加入就绪队列
        if (!process.isCompleted()) {
            ready_queue.push(process_index);
        }
        
        // 显示当前就绪队列状态
        if (!ready_queue.empty()) {
            displayReadyQueue(ready_queue, scheduled_processes, current_time);
        }
        std::cout << std::endl;
    }
    
    // 计算并返回结果
    SchedulingResult result = calculateStatistics(scheduled_processes, current_time);
    
    std::cout << "=== Round Robin调度完成！总执行时间: " << current_time << " 时间单位 ===" << std::endl;
    std::cout << "======================================" << std::endl;
    
    return result;
}

// 获取算法类型
std::string RoundRobinScheduler::getAlgorithmType() const {
    return "时间片轮转 (Round Robin)";
}

// 是否为抢占式调度
bool RoundRobinScheduler::isPreemptive() const {
    return true; // Round Robin是抢占式调度
}

// 显示Round Robin算法的详细信息
void RoundRobinScheduler::displayInfo() const {
    std::cout << "===========================================" << std::endl;
    std::cout << "      Round Robin调度算法详细信息          " << std::endl;
    std::cout << "===========================================" << std::endl;
    std::cout << "算法名称: " << getName() << std::endl;
    std::cout << "算法类型: " << getAlgorithmType() << std::endl;
    std::cout << "调度方式: " << (isPreemptive() ? "抢占式" : "非抢占式") << std::endl;
    std::cout << "时间片大小: " << time_quantum_ << " 时间单位" << std::endl;
    std::cout << "===========================================" << std::endl;
    std::cout << "算法描述:" << std::endl;
    std::cout << "  " << getDescription() << std::endl;
    std::cout << "===========================================" << std::endl;
    std::cout << "算法特点:" << std::endl;
    std::cout << "  + 公平性好，所有进程都能得到CPU时间" << std::endl;
    std::cout << "  + 响应时间较好，适合分时系统" << std::endl;
    std::cout << "  + 不会出现饥饿现象" << std::endl;
    std::cout << "  - 时间片大小影响性能" << std::endl;
    std::cout << "  - 上下文切换开销" << std::endl;
    std::cout << "===========================================" << std::endl;
    std::cout << "适用场景:" << std::endl;
    std::cout << "  * 分时操作系统" << std::endl;
    std::cout << "  * 交互式系统" << std::endl;
    std::cout << "  * 多用户系统" << std::endl;
    std::cout << "===========================================" << std::endl;
}

// 设置时间片大小
void RoundRobinScheduler::setTimeQuantum(int time_quantum) {
    if (time_quantum <= 0) {
        throw std::invalid_argument("时间片大小必须大于0");
    }
    time_quantum_ = time_quantum;
}

// 初始化就绪队列
void RoundRobinScheduler::initializeReadyQueue(const ProcessList& processes, 
                                              std::queue<size_t>& ready_queue, 
                                              int current_time) const {
    for (size_t i = 0; i < processes.size(); ++i) {
        if (processes[i].getArrivalTime() <= current_time) {
            ready_queue.push(i);
        }
    }
}

// 检查并添加新到达的进程到就绪队列
void RoundRobinScheduler::checkAndAddArrivedProcesses(const ProcessList& processes,
                                                     std::queue<size_t>& ready_queue,
                                                     int current_time,
                                                     int& last_check_time) const {
    for (size_t i = 0; i < processes.size(); ++i) {
        if (processes[i].getArrivalTime() > last_check_time && 
            processes[i].getArrivalTime() <= current_time &&
            processes[i].getState() == ProcessState::NEW) {
            ready_queue.push(i);
            std::cout << "  进程P" << processes[i].getPID() << "到达，加入就绪队列" << std::endl;
        }
    }
    last_check_time = current_time;
}

// 显示当前就绪队列状态
void RoundRobinScheduler::displayReadyQueue(const std::queue<size_t>& ready_queue,
                                           const ProcessList& processes,
                                           int /* current_time */) const {
    std::cout << "  当前就绪队列: [";
    std::queue<size_t> temp_queue = ready_queue;
    bool first = true;
    while (!temp_queue.empty()) {
        if (!first) std::cout << ", ";
        std::cout << "P" << processes[temp_queue.front()].getPID();
        temp_queue.pop();
        first = false;
    }
    std::cout << "]" << std::endl;
}

} // namespace ZTS_OS 