#ifndef SJF_SCHEDULER_H
#define SJF_SCHEDULER_H

#include "Scheduler.h"

/**
 * @file SJFScheduler.h
 * @brief 最短作业优先(SJF)调度算法头文件
 * @author ZTS Operating System Design Team
 * @date 2025
 */

namespace ZTS_OS {

/**
 * @class SJFScheduler
 * @brief 最短作业优先调度器
 * 
 * 实现SJF调度算法，按照进程的执行时间长短进行调度。
 * 分为抢占式(SRTF)和非抢占式两种模式。
 */
class SJFScheduler : public Scheduler {
public:
    /**
     * @brief 构造函数
     * @param preemptive 是否为抢占式调度(SRTF)
     */
    SJFScheduler(bool preemptive = false);
    
    /**
     * @brief 执行SJF调度算法
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
     * @brief 显示SJF算法的详细信息
     */
    void displayInfo() const override;

private:
    /**
     * @brief 非抢占式SJF调度
     * @param processes 进程列表
     * @return 调度结果
     */
    SchedulingResult scheduleNonPreemptive(ProcessList& processes);
    
    /**
     * @brief 抢占式SJF调度(SRTF)
     * @param processes 进程列表
     * @return 调度结果
     */
    SchedulingResult schedulePreemptive(ProcessList& processes);
    
    /**
     * @brief 按执行时间排序进程列表
     * @param processes 进程列表
     */
    void sortByBurstTime(ProcessList& processes) const;
    
    /**
     * @brief 找到剩余时间最短的进程
     * @param processes 进程列表
     * @param current_time 当前时间
     * @return 进程索引，如果没有找到返回-1
     */
    int findShortestRemainingTime(const ProcessList& processes, int current_time) const;

private:
    bool preemptive_;  ///< 是否为抢占式调度
};

} // namespace ZTS_OS

#endif // SJF_SCHEDULER_H 