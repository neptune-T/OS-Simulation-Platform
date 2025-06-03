#ifndef PRIORITY_SCHEDULER_H
#define PRIORITY_SCHEDULER_H

#include "Scheduler.h"

/**
 * @file PriorityScheduler.h
 * @brief 优先级调度算法头文件
 * @author ZTS Operating System Design Team
 * @date 2025
 */

namespace ZTS_OS {

/**
 * @class PriorityScheduler
 * @brief 优先级调度器
 * 
 * 实现基于优先级的调度算法，按照进程优先级进行调度。
 * 支持抢占式和非抢占式两种模式。
 */
class PriorityScheduler : public Scheduler {
public:
    /**
     * @brief 构造函数
     * @param preemptive 是否为抢占式调度
     */
    PriorityScheduler(bool preemptive = false);
    
    /**
     * @brief 执行优先级调度算法
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
     * @return true表示抢占式，false表示非抢占式
     */
    bool isPreemptive() const override;
    
    /**
     * @brief 显示优先级算法的详细信息
     */
    void displayInfo() const override;

private:
    /**
     * @brief 非抢占式优先级调度
     * @param processes 进程列表
     * @return 调度结果
     */
    SchedulingResult scheduleNonPreemptive(ProcessList& processes);
    
    /**
     * @brief 抢占式优先级调度
     * @param processes 进程列表
     * @return 调度结果
     */
    SchedulingResult schedulePreemptive(ProcessList& processes);
    
    /**
     * @brief 按优先级排序进程列表
     * @param processes 进程列表
     */
    void sortByPriority(ProcessList& processes) const;
    
    /**
     * @brief 找到最高优先级的进程
     * @param processes 进程列表
     * @param current_time 当前时间
     * @return 进程索引，如果没有找到返回-1
     */
    int findHighestPriority(const ProcessList& processes, int current_time) const;

private:
    bool preemptive_;  ///< 是否为抢占式调度
};

} // namespace ZTS_OS

#endif // PRIORITY_SCHEDULER_H 