#ifndef ROUND_ROBIN_SCHEDULER_H
#define ROUND_ROBIN_SCHEDULER_H

#include "Scheduler.h"
#include <queue>

/**
 * @file RoundRobinScheduler.h
 * @brief 时间片轮转(Round Robin)调度算法实现
 * @author ZTS Operating System Design Team
 * @date 2024
 */

namespace ZTS_OS {

/**
 * @class RoundRobinScheduler
 * @brief 时间片轮转(Round Robin)调度器
 * 
 * 特点：
 * - 抢占式调度算法
 * - 每个进程分配固定的时间片
 * - 进程在时间片内执行，超时则切换到下一个进程
 * - 适合分时系统，响应时间较好
 * - 时间片大小影响性能：过大退化为FCFS，过小增加切换开销
 */
class RoundRobinScheduler : public Scheduler {
public:
    /**
     * @brief 构造函数
     * @param time_quantum 时间片大小（默认2个时间单位）
     */
    explicit RoundRobinScheduler(int time_quantum = 2);
    
    /**
     * @brief 析构函数
     */
    virtual ~RoundRobinScheduler() = default;
    
    /**
     * @brief 执行Round Robin调度算法
     * @param processes 待调度的进程列表
     * @return 调度结果
     */
    SchedulingResult schedule(const ProcessList& processes) override;
    
    /**
     * @brief 获取算法类型
     * @return 算法类型字符串
     */
    std::string getAlgorithmType() const override;
    
    /**
     * @brief 是否为抢占式调度
     * @return true（Round Robin是抢占式）
     */
    bool isPreemptive() const override;
    
    /**
     * @brief 显示Round Robin算法的详细信息
     */
    void displayInfo() const override;
    
    /**
     * @brief 获取时间片大小
     * @return 时间片大小
     */
    int getTimeQuantum() const { return time_quantum_; }
    
    /**
     * @brief 设置时间片大小
     * @param time_quantum 新的时间片大小
     * @throws std::invalid_argument 如果时间片小于等于0
     */
    void setTimeQuantum(int time_quantum);

private:
    int time_quantum_;  ///< 时间片大小
    
    /**
     * @brief 初始化就绪队列
     * @param processes 进程列表
     * @param ready_queue 就绪队列
     * @param current_time 当前时间
     */
    void initializeReadyQueue(const ProcessList& processes, 
                             std::queue<size_t>& ready_queue, 
                             int current_time) const;
    
    /**
     * @brief 检查并添加新到达的进程到就绪队列
     * @param processes 进程列表
     * @param ready_queue 就绪队列
     * @param current_time 当前时间
     * @param last_check_time 上次检查时间
     */
    void checkAndAddArrivedProcesses(const ProcessList& processes,
                                   std::queue<size_t>& ready_queue,
                                   int current_time,
                                   int& last_check_time) const;
    
    /**
     * @brief 显示当前就绪队列状态
     * @param ready_queue 就绪队列
     * @param processes 进程列表
     * @param current_time 当前时间
     */
    void displayReadyQueue(const std::queue<size_t>& ready_queue,
                          const ProcessList& processes,
                          int current_time) const;
};

} // namespace ZTS_OS

#endif // ROUND_ROBIN_SCHEDULER_H 