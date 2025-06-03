#ifndef MEMORY_MANAGER_H
#define MEMORY_MANAGER_H

#include <vector>
#include <string>
#include <memory>
#include <unordered_map>

/**
 * @file MemoryManager.h
 * @brief 内存管理器基类定义
 * @author ZTS Operating System Design Team
 * @date 2025
 */

namespace ZTS_OS {

/**
 * @enum MemoryAllocationStrategy
 * @brief 内存分配策略枚举
 */
enum class MemoryAllocationStrategy {
    FIRST_FIT,    ///< 首次适应算法
    BEST_FIT,     ///< 最佳适应算法
    WORST_FIT,    ///< 最坏适应算法
    NEXT_FIT      ///< 循环首次适应算法
};

/**
 * @enum PageReplacementAlgorithm
 * @brief 页面置换算法枚举
 */
enum class PageReplacementAlgorithm {
    FIFO,    ///< 先进先出
    LRU,     ///< 最近最少使用
    LFU,     ///< 最少使用频率
    CLOCK    ///< 时钟算法
};

/**
 * @struct MemoryBlock
 * @brief 内存块结构
 */
struct MemoryBlock {
    size_t start_address;  ///< 起始地址
    size_t size;          ///< 块大小
    bool is_free;         ///< 是否空闲
    int process_id;       ///< 占用进程ID（-1表示空闲）
    std::string name;     ///< 块名称
    
    MemoryBlock(size_t start, size_t sz, bool free = true, int pid = -1, const std::string& n = "")
        : start_address(start), size(sz), is_free(free), process_id(pid), name(n) {}
    
    size_t end_address() const { return start_address + size - 1; }
};

/**
 * @struct Page
 * @brief 页面结构
 */
struct Page {
    int page_number;        ///< 页号
    int frame_number;       ///< 帧号（物理页框号）
    int process_id;         ///< 所属进程ID
    bool valid;            ///< 有效位
    bool referenced;       ///< 访问位
    bool modified;         ///< 修改位
    int access_count;      ///< 访问次数
    int last_access_time;  ///< 最后访问时间
    
    Page(int pn = -1, int fn = -1, int pid = -1)
        : page_number(pn), frame_number(fn), process_id(pid), 
          valid(false), referenced(false), modified(false),
          access_count(0), last_access_time(0) {}
};

/**
 * @class MemoryManager
 * @brief 内存管理器基类
 */
class MemoryManager {
public:
    /**
     * @brief 构造函数
     * @param total_size 总内存大小
     */
    explicit MemoryManager(size_t total_size);
    
    /**
     * @brief 虚析构函数
     */
    virtual ~MemoryManager() = default;
    
    /**
     * @brief 分配内存
     * @param size 请求大小
     * @param process_id 进程ID
     * @param name 块名称
     * @return 分配的起始地址，失败返回-1
     */
    virtual int allocateMemory(size_t size, int process_id, const std::string& name = "") = 0;
    
    /**
     * @brief 释放内存
     * @param process_id 进程ID
     * @return 是否成功释放
     */
    virtual bool deallocateMemory(int process_id) = 0;
    
    /**
     * @brief 获取内存使用率
     * @return 内存使用率百分比
     */
    double getMemoryUtilization() const;
    
    /**
     * @brief 获取碎片化程度
     * @return 碎片化百分比
     */
    double getFragmentation() const;
    
    /**
     * @brief 显示内存状态
     */
    virtual void displayMemoryStatus() const = 0;
    
    /**
     * @brief 获取内存块列表
     * @return 内存块列表
     */
    const std::vector<MemoryBlock>& getMemoryBlocks() const { return memory_blocks_; }
    
    /**
     * @brief 获取总内存大小
     * @return 总内存大小
     */
    size_t getTotalSize() const { return total_size_; }
    
    /**
     * @brief 获取已使用内存大小
     * @return 已使用内存大小
     */
    size_t getUsedSize() const;
    
    /**
     * @brief 获取空闲内存大小
     * @return 空闲内存大小
     */
    size_t getFreeSize() const;
    
    /**
     * @brief 内存压缩（碎片整理）
     */
    virtual void compactMemory();
    
protected:
    size_t total_size_;                    ///< 总内存大小
    std::vector<MemoryBlock> memory_blocks_; ///< 内存块列表
    MemoryAllocationStrategy strategy_;     ///< 分配策略
    
    /**
     * @brief 合并相邻的空闲块
     */
    void mergeAdjacentFreeBlocks();
    
    /**
     * @brief 分割内存块
     * @param block_index 块索引
     * @param size 分割大小
     * @return 新块的索引
     */
    int splitBlock(int block_index, size_t size);
    
    /**
     * @brief 查找空闲块
     * @param size 需要的大小
     * @return 块索引，未找到返回-1
     */
    virtual int findFreeBlock(size_t size) = 0;
};

} // namespace ZTS_OS

#endif // MEMORY_MANAGER_H 