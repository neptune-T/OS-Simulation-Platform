#include "../../include/algorithms/Scheduler.h"
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <stdexcept>

/**
 * @file Scheduler.cpp
 * @brief 调度器基类实现
 * @author ZTS Operating System Design Team
 * @date 2024
 */

namespace ZTS_OS {

// 构造函数
Scheduler::Scheduler(const std::string& name, const std::string& description)
    : name_(name), description_(description) {
}

// 显示调度器信息
void Scheduler::displayInfo() const {
    std::cout << "╔══════════════════════════════════════════════════════════════════════════════════════════════════════╗" << std::endl;
    std::cout << "║                                      调度器信息                                                      ║" << std::endl;
    std::cout << "╠══════════════════════════════════════════════════════════════════════════════════════════════════════╣" << std::endl;
    std::cout << "║ 名称: " << std::setw(90) << std::left << name_ << "║" << std::endl;
    std::cout << "║ 类型: " << std::setw(90) << std::left << getAlgorithmType() << "║" << std::endl;
    std::cout << "║ 描述: " << std::setw(90) << std::left << description_ << "║" << std::endl;
    std::cout << "║ 抢占: " << std::setw(90) << std::left << (isPreemptive() ? "是" : "否") << "║" << std::endl;
    std::cout << "╚══════════════════════════════════════════════════════════════════════════════════════════════════════╝" << std::endl;
}

// 显示调度结果
void Scheduler::displayResult(const SchedulingResult& result) {
    std::cout << "\n📊 调度结果统计：" << std::endl;
    std::cout << "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━" << std::endl;
    
    // 显示统计信息
    std::cout << std::fixed << std::setprecision(2);
    std::cout << "平均等待时间: " << result.average_waiting_time << " 时间单位" << std::endl;
    std::cout << "平均周转时间: " << result.average_turnaround_time << " 时间单位" << std::endl;
    std::cout << "平均响应时间: " << result.average_response_time << " 时间单位" << std::endl;
    std::cout << "CPU利用率: " << result.cpu_utilization << "%" << std::endl;
    std::cout << "吞吐率: " << result.throughput << " 进程/时间单位" << std::endl;
    std::cout << "总执行时间: " << result.total_time << " 时间单位" << std::endl;
    
    // 显示进程详细信息
    displayStatistics(result);
}

// 显示进程统计表
void Scheduler::displayStatistics(const SchedulingResult& result) {
    std::cout << "\n📋 进程执行统计表：" << std::endl;
    std::cout << "┌──────┬──────────────────────┬──────────┬──────────┬──────────┬──────────┬──────────┬──────────┐" << std::endl;
    std::cout << "│ PID  │        名称          │ 到达时间 │ 执行时间 │ 开始时间 │ 完成时间 │ 等待时间 │ 周转时间 │" << std::endl;
    std::cout << "├──────┼──────────────────────┼──────────┼──────────┼──────────┼──────────┼──────────┼──────────┤" << std::endl;
    
    for (const auto& process : result.processes) {
        std::cout << "│ " << std::setw(4) << std::right << process.getPID() 
                  << " │ " << std::setw(20) << std::left << process.getName()
                  << " │ " << std::setw(8) << std::right << process.getArrivalTime()
                  << " │ " << std::setw(8) << std::right << process.getBurstTime()
                  << " │ " << std::setw(8) << std::right << process.getStartTime()
                  << " │ " << std::setw(8) << std::right << process.getCompletionTime()
                  << " │ " << std::setw(8) << std::right << process.getWaitingTime()
                  << " │ " << std::setw(8) << std::right << process.getTurnaroundTime() << " │" << std::endl;
    }
    
    std::cout << "└──────┴──────────────────────┴──────────┴──────────┴──────────┴──────────┴──────────┴──────────┘" << std::endl;
}

// 显示甘特图
void Scheduler::displayGanttChart(const SchedulingResult& result) {
    std::cout << "\n📈 甘特图：" << std::endl;
    std::cout << "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━" << std::endl;
    
    // 简化的甘特图显示
    std::cout << "时间轴: ";
    int current_time = 0;
    for (const auto& process : result.processes) {
        if (current_time < process.getStartTime()) {
            std::cout << "[空闲:" << (process.getStartTime() - current_time) << "]";
            current_time = process.getStartTime();
        }
        std::cout << "[P" << process.getPID() << ":" << process.getBurstTime() << "]";
        current_time = process.getCompletionTime();
    }
    std::cout << std::endl;
}

// 计算调度结果统计信息
SchedulingResult Scheduler::calculateStatistics(const ProcessList& processes, int total_time) const {
    SchedulingResult result;
    result.processes = processes;
    result.total_time = total_time;
    
    double total_waiting_time = 0;
    double total_turnaround_time = 0;
    double total_response_time = 0;
    int completed_processes = 0;
    
    for (const auto& process : processes) {
        if (process.isCompleted()) {
            total_waiting_time += process.getWaitingTime();
            total_turnaround_time += process.getTurnaroundTime();
            total_response_time += process.getResponseTime();
            completed_processes++;
        }
    }
    
    if (completed_processes > 0) {
        result.average_waiting_time = total_waiting_time / completed_processes;
        result.average_turnaround_time = total_turnaround_time / completed_processes;
        result.average_response_time = total_response_time / completed_processes;
        result.throughput = static_cast<double>(completed_processes) / total_time;
        
        // 计算CPU利用率（假设没有空闲时间，简化计算）
        int total_burst_time = 0;
        for (const auto& process : processes) {
            total_burst_time += process.getBurstTime();
        }
        result.cpu_utilization = (static_cast<double>(total_burst_time) / total_time) * 100.0;
    }
    
    return result;
}

// 验证进程列表
void Scheduler::validateProcesses(const ProcessList& processes) const {
    if (processes.empty()) {
        throw std::invalid_argument("进程列表不能为空");
    }
    
    for (const auto& process : processes) {
        if (process.getBurstTime() <= 0) {
            throw std::invalid_argument("进程执行时间必须大于0");
        }
        if (process.getArrivalTime() < 0) {
            throw std::invalid_argument("进程到达时间不能为负数");
        }
    }
}

// 重置所有进程状态
void Scheduler::resetProcesses(ProcessList& processes) const {
    for (auto& process : processes) {
        process.reset();
    }
}

// 查找下一个可运行的进程
int Scheduler::findNextProcess(const ProcessList& processes, int current_time) const {
    for (size_t i = 0; i < processes.size(); ++i) {
        const auto& process = processes[i];
        if (process.getArrivalTime() <= current_time && 
            process.getState() == ProcessState::READY) {
            return static_cast<int>(i);
        }
    }
    return -1;
}

} // namespace ZTS_OS 