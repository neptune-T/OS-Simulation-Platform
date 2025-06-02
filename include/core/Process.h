#ifndef PROCESS_H
#define PROCESS_H

#include <string>
#include <chrono>
#include <vector>

/**
 * @file Process.h
 * @brief 进程控制块(PCB)定义和相关枚举
 * @author ZTS Operating System Design Team
 * @date 2024
 */

namespace ZTS_OS {

// 进程状态枚举
enum class ProcessState {
    NEW,        // 新建状态 - 进程刚被创建
    READY,      // 就绪状态 - 进程准备运行，等待CPU
    RUNNING,    // 运行状态 - 进程正在CPU上执行
    WAITING,    // 等待状态 - 进程等待某个事件发生
    TERMINATED  // 终止状态 - 进程执行完毕
};

// 进程优先级枚举
enum class ProcessPriority {
    HIGHEST = 1,    // 最高优先级
    HIGH = 2,       // 高优先级
    NORMAL = 3,     // 普通优先级
    LOW = 4,        // 低优先级
    LOWEST = 5      // 最低优先级
};

/**
 * @class Process
 * @brief 进程控制块(PCB)类
 * 
 * 包含了操作系统管理进程所需的所有信息：
 * - 进程标识信息
 * - 进程状态信息
 * - 进程控制信息
 * - 资源分配信息
 */
class Process {
public:
    // 构造函数
    Process(int pid, const std::string& name, int arrival_time, int burst_time, 
            ProcessPriority priority = ProcessPriority::NORMAL);
    
    // 拷贝构造函数
    Process(const Process& other);
    
    // 赋值操作符
    Process& operator=(const Process& other);
    
    // 析构函数
    ~Process() = default;
    
    // Getter 方法
    int getPID() const { return pid_; }
    std::string getName() const { return name_; }
    ProcessState getState() const { return state_; }
    ProcessPriority getPriority() const { return priority_; }
    int getArrivalTime() const { return arrival_time_; }
    int getBurstTime() const { return burst_time_; }
    int getRemainingTime() const { return remaining_time_; }
    int getWaitingTime() const { return waiting_time_; }
    int getTurnaroundTime() const { return turnaround_time_; }
    int getResponseTime() const { return response_time_; }
    int getStartTime() const { return start_time_; }
    int getCompletionTime() const { return completion_time_; }
    bool isFirstRun() const { return first_run_; }
    
    // Setter 方法
    void setState(ProcessState state) { state_ = state; }
    void setPriority(ProcessPriority priority) { priority_ = priority; }
    void setWaitingTime(int time) { waiting_time_ = time; }
    void setTurnaroundTime(int time) { turnaround_time_ = time; }
    void setResponseTime(int time) { response_time_ = time; }
    void setStartTime(int time) { start_time_ = time; }
    void setCompletionTime(int time) { completion_time_ = time; }
    void setFirstRun(bool first_run) { first_run_ = first_run; }
    
    // 操作方法
    void execute(int time_slice = 1);  // 执行进程指定时间片
    void reset();                      // 重置进程状态（用于多次调度演示）
    bool isCompleted() const;          // 检查进程是否完成
    
    // 计算性能指标
    void calculateTimes(int current_time);
    
    // 优先级比较函数
    static bool comparePriority(const Process& a, const Process& b);
    static bool compareBurstTime(const Process& a, const Process& b);
    static bool compareArrivalTime(const Process& a, const Process& b);
    
    // 获取优先级描述
    std::string getPriorityString() const;
    std::string getStateString() const;
    
    // 显示进程信息
    void displayInfo() const;
    
private:
    // 进程标识信息
    int pid_;                        // 进程ID
    std::string name_;               // 进程名称
    
    // 进程状态信息
    ProcessState state_;             // 当前状态
    ProcessPriority priority_;       // 优先级
    
    // 时间信息
    int arrival_time_;               // 到达时间
    int burst_time_;                 // 服务时间（总执行时间）
    int remaining_time_;             // 剩余执行时间
    int waiting_time_;               // 等待时间
    int turnaround_time_;            // 周转时间
    int response_time_;              // 响应时间
    int start_time_;                 // 首次运行时间
    int completion_time_;            // 完成时间
    
    // 状态标志
    bool first_run_;                 // 是否首次运行
};

/**
 * @typedef ProcessList
 * @brief 进程列表类型定义
 */
using ProcessList = std::vector<Process>;

/**
 * @struct SchedulingResult
 * @brief 调度结果统计结构
 */
struct SchedulingResult {
    std::vector<Process> processes;     // 调度后的进程列表
    double average_waiting_time;        // 平均等待时间
    double average_turnaround_time;     // 平均周转时间
    double average_response_time;       // 平均响应时间
    double cpu_utilization;             // CPU利用率
    double throughput;                  // 吞吐率
    int total_time;                     // 总执行时间
    
    // 构造函数
    SchedulingResult() : average_waiting_time(0), average_turnaround_time(0),
                        average_response_time(0), cpu_utilization(0),
                        throughput(0), total_time(0) {}
};

} // namespace ZTS_OS

#endif // PROCESS_H 