#ifndef FCFS_SCHEDULER_H
#define FCFS_SCHEDULER_H

#include "Scheduler.h"

/**
 * @file FCFSScheduler.h
 * @brief 先来先服务(FCFS)调度算法实现
 * @author ZTS Operating System Design Team
 * @date 2025
 */

namespace ZTS_OS {

/**
 * @class FCFSScheduler
 * @brief 先来先服务(First Come First Serve)调度器
 * 
 * 特点：
 * - 非抢占式调度
 * - 按进程到达时间顺序执行
 * - 简单公平，但可能导致长作业阻塞短作业
 * - 平均等待时间较长
 */
class FCFSScheduler : public Scheduler {
public:
    /**
     * @brief 构造函数
     */
    FCFSScheduler();
    
    /**
     * @brief 析构函数
     */
    virtual ~FCFSScheduler() = default;
    
    /**
     * @brief 执行FCFS调度算法
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
     * @return false（FCFS是非抢占式）
     */
    bool isPreemptive() const override;
    
    /**
     * @brief 显示FCFS算法的详细信息
     */
    void displayInfo() const override;

private:
    /**
     * @brief 按到达时间排序进程列表
     * @param processes 进程列表
     */
    void sortByArrivalTime(ProcessList& processes) const;
};

} // namespace ZTS_OS

#endif // FCFS_SCHEDULER_H 