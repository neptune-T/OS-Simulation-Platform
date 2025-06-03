#ifndef SCHEDULER_H
#define SCHEDULER_H

#include "../core/Process.h"
#include <vector>
#include <string>
#include <memory>

/**
 * @file Scheduler.h
 * @brief 进程调度器基类定义
 * @author ZTS Operating System Design Team
 * @date 2025
 */

namespace ZTS_OS {

/**
 * @class Scheduler
 * @brief 抽象调度器基类
 * 
 * 定义了所有调度算法的通用接口和基础功能。
 * 具体的调度算法继承此类并实现schedule()方法。
 */
class Scheduler {
public:
    /**
     * @brief 构造函数
     * @param name 调度器名称
     * @param description 调度器描述
     */
    Scheduler(const std::string& name, const std::string& description);
    
    /**
     * @brief 虚析构函数
     */
    virtual ~Scheduler() = default;
    
    /**
     * @brief 纯虚函数：执行调度算法
     * @param processes 待调度的进程列表
     * @return 调度结果
     */
    virtual SchedulingResult schedule(const ProcessList& processes) = 0;
    
    /**
     * @brief 获取调度器名称
     * @return 调度器名称
     */
    std::string getName() const { return name_; }
    
    /**
     * @brief 获取调度器描述
     * @return 调度器描述
     */
    std::string getDescription() const { return description_; }
    
    /**
     * @brief 获取调度器算法类型
     * @return 算法类型字符串
     */
    virtual std::string getAlgorithmType() const = 0;
    
    /**
     * @brief 是否为抢占式调度
     * @return true表示抢占式，false表示非抢占式
     */
    virtual bool isPreemptive() const = 0;
    
    /**
     * @brief 显示调度器信息
     */
    virtual void displayInfo() const;
    
    /**
     * @brief 显示调度结果
     * @param result 调度结果
     */
    static void displayResult(const SchedulingResult& result);
    
    /**
     * @brief 显示进程执行甘特图
     * @param result 调度结果
     */
    static void displayGanttChart(const SchedulingResult& result);
    
    /**
     * @brief 显示进程统计表
     * @param result 调度结果
     */
    static void displayStatistics(const SchedulingResult& result);

protected:
    /**
     * @brief 计算调度结果的统计信息
     * @param processes 进程列表
     * @param total_time 总执行时间
     * @return 调度结果
     */
    SchedulingResult calculateStatistics(const ProcessList& processes, int total_time) const;
    
    /**
     * @brief 验证进程列表
     * @param processes 待验证的进程列表
     * @throws std::invalid_argument 如果进程列表无效
     */
    void validateProcesses(const ProcessList& processes) const;
    
    /**
     * @brief 重置所有进程状态
     * @param processes 进程列表
     */
    void resetProcesses(ProcessList& processes) const;
    
    /**
     * @brief 查找下一个可运行的进程
     * @param processes 进程列表
     * @param current_time 当前时间
     * @return 下一个可运行进程的索引，如果没有返回-1
     */
    int findNextProcess(const ProcessList& processes, int current_time) const;

private:
    std::string name_;         ///< 调度器名称
    std::string description_;  ///< 调度器描述
};

/**
 * @typedef SchedulerPtr
 * @brief 调度器智能指针类型
 */
using SchedulerPtr = std::unique_ptr<Scheduler>;

/**
 * @class SchedulerFactory
 * @brief 调度器工厂类
 * 
 * 用于创建不同类型的调度器实例
 */
class SchedulerFactory {
public:
    /**
     * @enum SchedulerType
     * @brief 调度器类型枚举
     */
    enum class SchedulerType {
        FCFS,          ///< 先来先服务
        ROUND_ROBIN,   ///< 时间片轮转
        SJF,           ///< 最短作业优先
        PRIORITY       ///< 优先级调度
    };
    
    /**
     * @brief 创建调度器
     * @param type 调度器类型
     * @param time_quantum 时间片大小（仅用于时间片轮转）
     * @return 调度器智能指针
     */
    static SchedulerPtr createScheduler(SchedulerType type, int time_quantum = 2);
    
    /**
     * @brief 获取调度器类型名称
     * @param type 调度器类型
     * @return 类型名称
     */
    static std::string getSchedulerTypeName(SchedulerType type);
    
    /**
     * @brief 获取所有可用的调度器类型
     * @return 调度器类型列表
     */
    static std::vector<SchedulerType> getAvailableTypes();
};

} // namespace ZTS_OS

#endif // SCHEDULER_H 