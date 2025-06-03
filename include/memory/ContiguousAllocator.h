#ifndef CONTIGUOUS_ALLOCATOR_H
#define CONTIGUOUS_ALLOCATOR_H

#include "MemoryManager.h"

/**
 * @file ContiguousAllocator.h
 * @brief 连续内存分配管理器定义
 * @author ZTS Operating System Design Team
 * @date 2025
 */

namespace ZTS_OS {

/**
 * @class ContiguousAllocator
 * @brief 连续内存分配管理器
 * 
 * 实现首次适应、最佳适应、最坏适应和循环首次适应算法
 */
class ContiguousAllocator : public MemoryManager {
public:
    /**
     * @brief 构造函数
     * @param total_size 总内存大小(KB)
     * @param strategy 分配策略
     */
    ContiguousAllocator(size_t total_size, MemoryAllocationStrategy strategy = MemoryAllocationStrategy::FIRST_FIT);
    
    /**
     * @brief 析构函数
     */
    ~ContiguousAllocator() override = default;
    
    /**
     * @brief 分配内存
     * @param size 请求大小
     * @param process_id 进程ID
     * @param name 块名称
     * @return 分配的起始地址，失败返回-1
     */
    int allocateMemory(size_t size, int process_id, const std::string& name = "") override;
    
    /**
     * @brief 释放内存
     * @param process_id 进程ID
     * @return 是否成功释放
     */
    bool deallocateMemory(int process_id) override;
    
    /**
     * @brief 显示内存状态
     */
    void displayMemoryStatus() const override;
    
    /**
     * @brief 显示内存映射图
     */
    void displayMemoryMap() const;
    
    /**
     * @brief 设置分配策略
     * @param strategy 新的分配策略
     */
    void setAllocationStrategy(MemoryAllocationStrategy strategy) { 
        strategy_ = strategy; 
        if (strategy_ == MemoryAllocationStrategy::NEXT_FIT) {
            next_fit_pointer_ = 0;
        }
    }
    
    /**
     * @brief 获取当前分配策略
     * @return 当前分配策略
     */
    MemoryAllocationStrategy getAllocationStrategy() const { return strategy_; }
    
    /**
     * @brief 获取分配策略名称
     * @param strategy 分配策略
     * @return 策略名称
     */
    static std::string getStrategyName(MemoryAllocationStrategy strategy);
    
    /**
     * @brief 获取最大空闲块大小
     * @return 最大空闲块大小
     */
    size_t getLargestFreeBlock() const;
    
    /**
     * @brief 获取空闲块数量
     * @return 空闲块数量
     */
    int getFreeBlockCount() const;

protected:
    /**
     * @brief 查找空闲块
     * @param size 需要的大小
     * @return 块索引，未找到返回-1
     */
    int findFreeBlock(size_t size) override;

private:
    int next_fit_pointer_;  ///< 循环首次适应的指针位置
    
    /**
     * @brief 首次适应算法
     * @param size 需要的大小
     * @return 块索引，未找到返回-1
     */
    int firstFit(size_t size);
    
    /**
     * @brief 最佳适应算法
     * @param size 需要的大小
     * @return 块索引，未找到返回-1
     */
    int bestFit(size_t size);
    
    /**
     * @brief 最坏适应算法
     * @param size 需要的大小
     * @return 块索引，未找到返回-1
     */
    int worstFit(size_t size);
    
    /**
     * @brief 循环首次适应算法
     * @param size 需要的大小
     * @return 块索引，未找到返回-1
     */
    int nextFit(size_t size);
};

} // namespace ZTS_OS

#endif // CONTIGUOUS_ALLOCATOR_H 