#ifndef PAGING_MANAGER_H
#define PAGING_MANAGER_H

#include "MemoryManager.h"
#include <queue>
#include <list>

/**
 * @file PagingManager.h
 * @brief 分页内存管理器定义
 * @author ZTS Operating System Design Team
 * @date 2025
 */

namespace ZTS_OS {

/**
 * @struct PageFrame
 * @brief 页框结构
 */
struct PageFrame {
    int frame_number;       ///< 页框号
    bool is_free;          ///< 是否空闲
    int process_id;        ///< 占用进程ID
    int page_number;       ///< 页号
    int reference_bit;     ///< 引用位（时钟算法用）
    int access_time;       ///< 访问时间
    int access_count;      ///< 访问次数
    
    PageFrame(int fn) : frame_number(fn), is_free(true), process_id(-1), 
                       page_number(-1), reference_bit(0), access_time(0), access_count(0) {}
};

/**
 * @struct PageTableEntry
 * @brief 页表项
 */
struct PageTableEntry {
    int frame_number;      ///< 页框号
    bool valid;           ///< 有效位
    bool present;         ///< 在内存位
    bool referenced;      ///< 访问位
    bool modified;        ///< 修改位
    
    PageTableEntry() : frame_number(-1), valid(false), present(false), 
                      referenced(false), modified(false) {}
};

/**
 * @class PagingManager
 * @brief 分页内存管理器
 */
class PagingManager {
public:
    /**
     * @brief 构造函数
     * @param total_memory 总内存大小(KB)
     * @param page_size 页面大小(KB)
     * @param replacement_algorithm 页面置换算法
     */
    PagingManager(size_t total_memory, size_t page_size = 4, 
                  PageReplacementAlgorithm replacement_algorithm = PageReplacementAlgorithm::FIFO);
    
    /**
     * @brief 析构函数
     */
    ~PagingManager() = default;
    
    /**
     * @brief 分配页面给进程
     * @param process_id 进程ID
     * @param pages_needed 需要的页面数
     * @return 是否分配成功
     */
    bool allocatePages(int process_id, size_t pages_needed);
    
    /**
     * @brief 释放进程的所有页面
     * @param process_id 进程ID
     * @return 释放的页面数
     */
    int deallocatePages(int process_id);
    
    /**
     * @brief 访问页面（地址转换）
     * @param process_id 进程ID
     * @param virtual_address 虚拟地址
     * @param is_write 是否为写操作
     * @return 物理地址，页错误返回-1
     */
    int accessPage(int process_id, size_t virtual_address, bool is_write = false);
    
    /**
     * @brief 处理页错误
     * @param process_id 进程ID
     * @param page_number 页号
     * @return 分配的页框号，失败返回-1
     */
    int handlePageFault(int process_id, int page_number);
    
    /**
     * @brief 页面置换
     * @return 被置换的页框号
     */
    int replaceePage();
    
    /**
     * @brief 显示内存状态
     */
    void displayMemoryStatus() const;
    
    /**
     * @brief 显示页表
     * @param process_id 进程ID
     */
    void displayPageTable(int process_id) const;
    
    /**
     * @brief 显示页框状态
     */
    void displayPageFrames() const;
    
    /**
     * @brief 获取内存使用率
     * @return 使用率百分比
     */
    double getMemoryUtilization() const;
    
    /**
     * @brief 获取页错误次数
     * @return 页错误次数
     */
    int getPageFaultCount() const { return page_fault_count_; }
    
    /**
     * @brief 获取页框总数
     * @return 页框总数
     */
    size_t getTotalFrames() const { return page_frames_.size(); }
    
    /**
     * @brief 获取页面大小
     * @return 页面大小
     */
    size_t getPageSize() const { return page_size_; }
    
    /**
     * @brief 设置页面置换算法
     * @param algorithm 置换算法
     */
    void setReplacementAlgorithm(PageReplacementAlgorithm algorithm) { 
        replacement_algorithm_ = algorithm; 
    }

private:
    size_t total_memory_;                  ///< 总内存大小
    size_t page_size_;                     ///< 页面大小
    size_t total_frames_;                  ///< 总页框数
    PageReplacementAlgorithm replacement_algorithm_; ///< 页面置换算法
    
    std::vector<PageFrame> page_frames_;   ///< 页框数组
    std::unordered_map<int, std::vector<PageTableEntry>> page_tables_; ///< 进程页表
    std::queue<int> free_frames_;          ///< 空闲页框队列
    
    // 页面置换算法相关
    std::queue<int> fifo_queue_;           ///< FIFO队列
    std::list<int> lru_list_;             ///< LRU链表
    std::unordered_map<int, int> lfu_count_; ///< LFU计数
    int clock_pointer_;                    ///< 时钟指针
    
    int page_fault_count_;                 ///< 页错误计数
    int current_time_;                     ///< 当前时间
    
    /**
     * @brief FIFO页面置换
     * @return 被置换的页框号
     */
    int fifoReplacement();
    
    /**
     * @brief LRU页面置换
     * @return 被置换的页框号
     */
    int lruReplacement();
    
    /**
     * @brief LFU页面置换
     * @return 被置换的页框号
     */
    int lfuReplacement();
    
    /**
     * @brief 时钟页面置换
     * @return 被置换的页框号
     */
    int clockReplacement();
    
    /**
     * @brief 更新页面访问信息
     * @param frame_number 页框号
     * @param is_write 是否为写操作
     */
    void updatePageAccess(int frame_number, bool is_write);
    
    /**
     * @brief 获取虚拟地址的页号
     * @param virtual_address 虚拟地址
     * @return 页号
     */
    int getPageNumber(size_t virtual_address) const {
        return virtual_address / page_size_;
    }
    
    /**
     * @brief 获取虚拟地址的页内偏移
     * @param virtual_address 虚拟地址
     * @return 页内偏移
     */
    int getPageOffset(size_t virtual_address) const {
        return virtual_address % page_size_;
    }
};

} // namespace ZTS_OS

#endif // PAGING_MANAGER_H 