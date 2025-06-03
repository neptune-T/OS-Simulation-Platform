#ifndef MEMORY_DEMO_H
#define MEMORY_DEMO_H

#include "../memory/MemoryManager.h"
#include "../memory/ContiguousAllocator.h"
#include "../memory/PagingManager.h"
#include "boot_animation.h"
#include <memory>

/**
 * @file memory_demo.h
 * @brief 内存管理演示器
 * @author ZTS Operating System Design Team
 * @date 2025
 */

namespace ZTS_OS {

/**
 * @struct MemoryRequest
 * @brief 内存请求结构
 */
struct MemoryRequest {
    int process_id;     ///< 进程ID
    std::string name;   ///< 进程名称
    size_t size;        ///< 请求大小
    bool is_release;    ///< 是否为释放操作
    
    MemoryRequest(int pid, const std::string& n, size_t s, bool release = false)
        : process_id(pid), name(n), size(s), is_release(release) {}
};

/**
 * @class MemoryDemo
 * @brief 内存管理演示器类
 * 
 * 提供交互式的内存管理演示功能，包括：
 * - 连续内存分配演示
 * - 分页内存管理演示
 * - 页面置换算法演示
 * - 内存分配算法比较
 */
class MemoryDemo {
public:
    /**
     * @brief 构造函数
     */
    MemoryDemo();
    
    /**
     * @brief 析构函数
     */
    ~MemoryDemo() = default;
    
    /**
     * @brief 启动内存管理演示主界面
     */
    void start();

private:
    /**
     * @brief 显示演示主菜单
     */
    void showMainMenu();
    
    /**
     * @brief 连续内存分配演示
     */
    void contiguousAllocationDemo();
    
    /**
     * @brief 分页内存管理演示
     */
    void pagingManagementDemo();
    
    /**
     * @brief 页面置换算法演示
     */
    void pageReplacementDemo();
    
    /**
     * @brief 内存分配算法比较
     */
    void allocationComparisonDemo();
    
    /**
     * @brief 显示连续分配策略菜单
     */
    void showAllocationStrategyMenu();
    
    /**
     * @brief 显示页面置换算法菜单
     */
    void showPageReplacementMenu();
    
    /**
     * @brief 创建预设的内存请求序列
     * @param scenario 场景编号
     * @return 内存请求列表
     */
    std::vector<MemoryRequest> createMemoryRequests(int scenario);
    
    /**
     * @brief 执行连续分配演示
     * @param strategy 分配策略
     * @param requests 内存请求列表
     */
    void runContiguousAllocationDemo(MemoryAllocationStrategy strategy, 
                                   const std::vector<MemoryRequest>& requests);
    
    /**
     * @brief 执行分页演示
     * @param algorithm 页面置换算法
     */
    void runPagingDemo(PageReplacementAlgorithm algorithm);
    
    /**
     * @brief 执行页面置换演示
     * @param algorithm 置换算法
     * @param access_sequence 页面访问序列
     */
    void runPageReplacementDemo(PageReplacementAlgorithm algorithm,
                              const std::vector<int>& access_sequence);
    
    /**
     * @brief 比较不同的分配算法
     * @param requests 内存请求列表
     */
    void compareAllocationAlgorithms(const std::vector<MemoryRequest>& requests);
    
    /**
     * @brief 比较不同的页面置换算法
     * @param access_sequence 页面访问序列
     */
    void comparePageReplacementAlgorithms(const std::vector<int>& access_sequence);
    
    /**
     * @brief 显示内存可视化
     * @param allocator 内存分配器
     */
    void displayMemoryVisualization(const ContiguousAllocator& allocator);
    
    /**
     * @brief 显示页面访问过程
     * @param access_sequence 访问序列
     * @param algorithm_name 算法名称
     */
    void displayPageAccessProcess(const std::vector<int>& access_sequence,
                                const std::string& algorithm_name);
    
    /**
     * @brief 获取用户输入的内存大小
     * @return 内存大小
     */
    size_t getMemorySize();
    
    /**
     * @brief 获取用户输入的页面大小
     * @return 页面大小
     */
    size_t getPageSize();
    
    /**
     * @brief 暂停并等待用户按键
     */
    void pauseForUser();
    
    /**
     * @brief 清屏并显示标题
     * @param title 标题文本
     */
    void showTitle(const std::string& title);
    
    /**
     * @brief 获取分配策略名称
     * @param strategy 分配策略
     * @return 策略名称
     */
    std::string getStrategyName(MemoryAllocationStrategy strategy);
    
    /**
     * @brief 获取置换算法名称
     * @param algorithm 置换算法
     * @return 算法名称
     */
    std::string getAlgorithmName(PageReplacementAlgorithm algorithm);

private:
    std::vector<std::vector<MemoryRequest>> memory_scenarios_;  ///< 预设的内存请求场景
    std::vector<std::vector<int>> page_access_scenarios_;       ///< 预设的页面访问场景
};

} // namespace ZTS_OS

#endif // MEMORY_DEMO_H 