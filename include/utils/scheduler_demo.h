#ifndef SCHEDULER_DEMO_H
#define SCHEDULER_DEMO_H

#include "../core/Process.h"
#include "../algorithms/Scheduler.h"
#include "boot_animation.h"
#include <vector>
#include <memory>

/**
 * @file scheduler_demo.h
 * @brief 进程调度算法演示器
 * @author ZTS Operating System Design Team
 * @date 2024
 */

namespace ZTS_OS {

/**
 * @class SchedulerDemo
 * @brief 调度算法演示器类
 * 
 * 提供交互式的进程调度算法演示功能，包括：
 * - 创建示例进程
 * - 选择调度算法
 * - 执行调度演示
 * - 显示结果分析
 */
class SchedulerDemo {
public:
    /**
     * @brief 构造函数
     */
    SchedulerDemo();
    
    /**
     * @brief 析构函数
     */
    ~SchedulerDemo() = default;
    
    /**
     * @brief 启动调度演示主界面
     */
    void start();

private:
    /**
     * @brief 显示演示主菜单
     */
    void showMainMenu();
    
    /**
     * @brief 显示算法选择菜单
     */
    void showAlgorithmMenu();
    
    /**
     * @brief 创建预设的示例进程集
     * @param scenario 场景编号
     * @return 进程列表
     */
    ProcessList createSampleProcesses(int scenario);
    
    /**
     * @brief 手动创建进程
     * @return 进程列表
     */
    ProcessList createCustomProcesses();
    
    /**
     * @brief 执行指定算法的演示
     * @param algorithm_type 算法类型
     * @param processes 进程列表
     */
    void runAlgorithmDemo(SchedulerFactory::SchedulerType algorithm_type, 
                         const ProcessList& processes);
    
    /**
     * @brief 比较多种算法
     * @param processes 进程列表
     */
    void compareAlgorithms(const ProcessList& processes);
    
    /**
     * @brief 显示进程信息表
     * @param processes 进程列表
     */
    void displayProcessTable(const ProcessList& processes);
    
    /**
     * @brief 显示算法介绍
     * @param algorithm_type 算法类型
     */
    void showAlgorithmDescription(SchedulerFactory::SchedulerType algorithm_type);
    
    /**
     * @brief 动画演示调度过程
     * @param result 调度结果
     * @param algorithm_name 算法名称
     */
    void animateScheduling(const SchedulingResult& result, const std::string& algorithm_name);
    
    /**
     * @brief 获取用户输入的时间片大小
     * @return 时间片大小
     */
    int getTimeQuantum();
    
    /**
     * @brief 暂停并等待用户按键
     */
    void pauseForUser();
    
    /**
     * @brief 清屏并显示标题
     * @param title 标题文本
     */
    void showTitle(const std::string& title);
    
private:
    std::vector<ProcessList> sample_scenarios_;  ///< 预设的进程场景
};

} // namespace ZTS_OS

#endif // SCHEDULER_DEMO_H 