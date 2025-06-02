#include "../../include/core/Process.h"
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <stdexcept>

/**
 * @file Process.cpp
 * @brief 进程控制块(PCB)类的实现
 * @author ZTS Operating System Design Team
 * @date 2024
 */

namespace ZTS_OS {

// 构造函数
Process::Process(int pid, const std::string& name, int arrival_time, int burst_time, 
                ProcessPriority priority)
    : pid_(pid), name_(name), state_(ProcessState::NEW), priority_(priority),
      arrival_time_(arrival_time), burst_time_(burst_time), remaining_time_(burst_time),
      waiting_time_(0), turnaround_time_(0), response_time_(-1), 
      start_time_(-1), completion_time_(-1), first_run_(true) {
    
    // 参数验证
    if (pid < 0) {
        throw std::invalid_argument("进程ID不能为负数");
    }
    if (arrival_time < 0) {
        throw std::invalid_argument("到达时间不能为负数");
    }
    if (burst_time <= 0) {
        throw std::invalid_argument("执行时间必须大于0");
    }
    if (name.empty()) {
        throw std::invalid_argument("进程名称不能为空");
    }
}

// 拷贝构造函数
Process::Process(const Process& other)
    : pid_(other.pid_), name_(other.name_), state_(other.state_), 
      priority_(other.priority_), arrival_time_(other.arrival_time_),
      burst_time_(other.burst_time_), remaining_time_(other.remaining_time_),
      waiting_time_(other.waiting_time_), turnaround_time_(other.turnaround_time_),
      response_time_(other.response_time_), start_time_(other.start_time_),
      completion_time_(other.completion_time_), first_run_(other.first_run_) {
}

// 赋值操作符
Process& Process::operator=(const Process& other) {
    if (this != &other) {
        pid_ = other.pid_;
        name_ = other.name_;
        state_ = other.state_;
        priority_ = other.priority_;
        arrival_time_ = other.arrival_time_;
        burst_time_ = other.burst_time_;
        remaining_time_ = other.remaining_time_;
        waiting_time_ = other.waiting_time_;
        turnaround_time_ = other.turnaround_time_;
        response_time_ = other.response_time_;
        start_time_ = other.start_time_;
        completion_time_ = other.completion_time_;
        first_run_ = other.first_run_;
    }
    return *this;
}

// 执行进程指定时间片
void Process::execute(int time_slice) {
    if (state_ == ProcessState::TERMINATED) {
        return; // 已终止的进程不能再执行
    }
    
    // 如果是首次运行，记录开始时间
    if (first_run_) {
        first_run_ = false;
        state_ = ProcessState::RUNNING;
    }
    
    // 执行时间片
    int actual_time = std::min(time_slice, remaining_time_);
    remaining_time_ -= actual_time;
    
    // 检查是否完成
    if (remaining_time_ <= 0) {
        state_ = ProcessState::TERMINATED;
        remaining_time_ = 0;
    } else {
        state_ = ProcessState::READY; // 时间片用完，返回就绪状态
    }
}

// 重置进程状态（用于多次调度演示）
void Process::reset() {
    state_ = ProcessState::NEW;
    remaining_time_ = burst_time_;
    waiting_time_ = 0;
    turnaround_time_ = 0;
    response_time_ = -1;
    start_time_ = -1;
    completion_time_ = -1;
    first_run_ = true;
}

// 检查进程是否完成
bool Process::isCompleted() const {
    return state_ == ProcessState::TERMINATED;
}

// 计算性能指标
void Process::calculateTimes(int current_time) {
    if (state_ == ProcessState::TERMINATED) {
        completion_time_ = current_time;
        turnaround_time_ = completion_time_ - arrival_time_;
        waiting_time_ = turnaround_time_ - burst_time_;
        
        // 响应时间已经在首次运行时设置
        if (response_time_ == -1) {
            response_time_ = start_time_ - arrival_time_;
        }
    }
}

// 优先级比较函数（数值越小优先级越高）
bool Process::comparePriority(const Process& a, const Process& b) {
    if (static_cast<int>(a.priority_) == static_cast<int>(b.priority_)) {
        return a.arrival_time_ < b.arrival_time_; // 优先级相同时按到达时间排序
    }
    return static_cast<int>(a.priority_) < static_cast<int>(b.priority_);
}

// 按执行时间比较（最短作业优先）
bool Process::compareBurstTime(const Process& a, const Process& b) {
    if (a.burst_time_ == b.burst_time_) {
        return a.arrival_time_ < b.arrival_time_; // 执行时间相同时按到达时间排序
    }
    return a.burst_time_ < b.burst_time_;
}

// 按到达时间比较（先来先服务）
bool Process::compareArrivalTime(const Process& a, const Process& b) {
    if (a.arrival_time_ == b.arrival_time_) {
        return a.pid_ < b.pid_; // 到达时间相同时按PID排序
    }
    return a.arrival_time_ < b.arrival_time_;
}

// 获取优先级描述
std::string Process::getPriorityString() const {
    switch (priority_) {
        case ProcessPriority::HIGHEST: return "最高 (1)";
        case ProcessPriority::HIGH:    return "高 (2)";
        case ProcessPriority::NORMAL:  return "普通 (3)";
        case ProcessPriority::LOW:     return "低 (4)";
        case ProcessPriority::LOWEST:  return "最低 (5)";
        default: return "未知";
    }
}

// 获取状态描述
std::string Process::getStateString() const {
    switch (state_) {
        case ProcessState::NEW:        return "新建";
        case ProcessState::READY:      return "就绪";
        case ProcessState::RUNNING:    return "运行";
        case ProcessState::WAITING:    return "等待";
        case ProcessState::TERMINATED: return "终止";
        default: return "未知";
    }
}

// 显示进程信息
void Process::displayInfo() const {
    std::cout << "进程信息 [PID: " << pid_ << "]" << std::endl;
    std::cout << "┌─────────────────────────────────────────┐" << std::endl;
    std::cout << "│ 名称: " << std::setw(32) << std::left << name_ << "│" << std::endl;
    std::cout << "│ 状态: " << std::setw(32) << std::left << getStateString() << "│" << std::endl;
    std::cout << "│ 优先级: " << std::setw(30) << std::left << getPriorityString() << "│" << std::endl;
    std::cout << "│ 到达时间: " << std::setw(28) << std::left << arrival_time_ << "│" << std::endl;
    std::cout << "│ 执行时间: " << std::setw(28) << std::left << burst_time_ << "│" << std::endl;
    std::cout << "│ 剩余时间: " << std::setw(28) << std::left << remaining_time_ << "│" << std::endl;
    
    if (waiting_time_ >= 0) {
        std::cout << "│ 等待时间: " << std::setw(28) << std::left << waiting_time_ << "│" << std::endl;
    }
    if (turnaround_time_ >= 0) {
        std::cout << "│ 周转时间: " << std::setw(28) << std::left << turnaround_time_ << "│" << std::endl;
    }
    if (response_time_ >= 0) {
        std::cout << "│ 响应时间: " << std::setw(28) << std::left << response_time_ << "│" << std::endl;
    }
    if (start_time_ >= 0) {
        std::cout << "│ 开始时间: " << std::setw(28) << std::left << start_time_ << "│" << std::endl;
    }
    if (completion_time_ >= 0) {
        std::cout << "│ 完成时间: " << std::setw(28) << std::left << completion_time_ << "│" << std::endl;
    }
    
    std::cout << "└─────────────────────────────────────────┘" << std::endl;
}

} // namespace ZTS_OS 