#include "../../include/memory/ContiguousAllocator.h"
#include <algorithm>
#include <iostream>
#include <iomanip>
#include <climits>

/**
 * @file ContiguousAllocator.cpp
 * @brief 连续内存分配管理器实现
 * @author ZTS Operating System Design Team
 * @date 2025
 */

namespace ZTS_OS {

// 构造函数
ContiguousAllocator::ContiguousAllocator(size_t total_size, MemoryAllocationStrategy strategy)
    : MemoryManager(total_size), next_fit_pointer_(0) {
    strategy_ = strategy;
}

// 分配内存
int ContiguousAllocator::allocateMemory(size_t size, int process_id, const std::string& name) {
    if (size == 0) return -1;
    
    // 查找合适的空闲块
    int block_index = findFreeBlock(size);
    if (block_index == -1) {
        std::cout << "❌ 无法为进程 " << process_id << " 分配 " << size 
                  << "KB 内存：空间不足" << std::endl;
        return -1;
    }
    
    // 分割块（如果需要）
    splitBlock(block_index, size);
    
    // 标记块为已分配
    MemoryBlock& block = memory_blocks_[block_index];
    block.is_free = false;
    block.process_id = process_id;
    block.name = name.empty() ? ("进程" + std::to_string(process_id)) : name;
    
    std::cout << "✅ 成功为进程 " << process_id << " (" << block.name 
              << ") 分配 " << size << "KB 内存，起始地址: " << block.start_address << std::endl;
    
    return static_cast<int>(block.start_address);
}

// 释放内存
bool ContiguousAllocator::deallocateMemory(int process_id) {
    bool found = false;
    
    for (auto& block : memory_blocks_) {
        if (!block.is_free && block.process_id == process_id) {
            std::cout << "✅ 释放进程 " << process_id << " (" << block.name 
                      << ") 的内存：" << block.size << "KB" << std::endl;
            
            block.is_free = true;
            block.process_id = -1;
            block.name = "空闲";
            found = true;
        }
    }
    
    if (found) {
        // 合并相邻的空闲块
        mergeAdjacentFreeBlocks();
    } else {
        std::cout << "❌ 未找到进程 " << process_id << " 的内存分配" << std::endl;
    }
    
    return found;
}

// 显示内存状态
void ContiguousAllocator::displayMemoryStatus() const {
    std::cout << "\n📊 内存状态信息：" << std::endl;
    std::cout << "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━" << std::endl;
    std::cout << "总内存大小: " << total_size_ << " KB" << std::endl;
    std::cout << "已使用: " << getUsedSize() << " KB (" 
              << std::fixed << std::setprecision(1) << getMemoryUtilization() << "%)" << std::endl;
    std::cout << "空闲: " << getFreeSize() << " KB" << std::endl;
    std::cout << "碎片化程度: " << std::fixed << std::setprecision(1) << getFragmentation() << "%" << std::endl;
    std::cout << "分配策略: " << getStrategyName(strategy_) << std::endl;
    std::cout << "最大空闲块: " << getLargestFreeBlock() << " KB" << std::endl;
    std::cout << "空闲块数量: " << getFreeBlockCount() << std::endl;
    
    displayMemoryMap();
}

// 显示内存映射图
void ContiguousAllocator::displayMemoryMap() const {
    std::cout << "\n🗺️ 内存映射图：" << std::endl;
    std::cout << "┌─────────────┬─────────────┬─────────────┬─────────────┬─────────────────────┐" << std::endl;
    std::cout << "│   起始地址  │   结束地址  │    大小     │   状态      │      进程/名称      │" << std::endl;
    std::cout << "├─────────────┼─────────────┼─────────────┼─────────────┼─────────────────────┤" << std::endl;
    
    for (const auto& block : memory_blocks_) {
        std::cout << "│ " << std::setw(11) << block.start_address
                  << " │ " << std::setw(11) << block.end_address()
                  << " │ " << std::setw(9) << block.size << " KB"
                  << " │ " << std::setw(11) << (block.is_free ? "空闲" : "已分配")
                  << " │ " << std::setw(19) << block.name
                  << " │" << std::endl;
    }
    std::cout << "└─────────────┴─────────────┴─────────────┴─────────────┴─────────────────────┘" << std::endl;
}

// 获取分配策略名称
std::string ContiguousAllocator::getStrategyName(MemoryAllocationStrategy strategy) {
    switch (strategy) {
        case MemoryAllocationStrategy::FIRST_FIT:
            return "首次适应 (First Fit)";
        case MemoryAllocationStrategy::BEST_FIT:
            return "最佳适应 (Best Fit)";
        case MemoryAllocationStrategy::WORST_FIT:
            return "最坏适应 (Worst Fit)";
        case MemoryAllocationStrategy::NEXT_FIT:
            return "循环首次适应 (Next Fit)";
        default:
            return "未知策略";
    }
}

// 获取最大空闲块大小
size_t ContiguousAllocator::getLargestFreeBlock() const {
    size_t largest = 0;
    for (const auto& block : memory_blocks_) {
        if (block.is_free && block.size > largest) {
            largest = block.size;
        }
    }
    return largest;
}

// 获取空闲块数量
int ContiguousAllocator::getFreeBlockCount() const {
    int count = 0;
    for (const auto& block : memory_blocks_) {
        if (block.is_free) {
            count++;
        }
    }
    return count;
}

// 查找空闲块
int ContiguousAllocator::findFreeBlock(size_t size) {
    switch (strategy_) {
        case MemoryAllocationStrategy::FIRST_FIT:
            return firstFit(size);
        case MemoryAllocationStrategy::BEST_FIT:
            return bestFit(size);
        case MemoryAllocationStrategy::WORST_FIT:
            return worstFit(size);
        case MemoryAllocationStrategy::NEXT_FIT:
            return nextFit(size);
        default:
            return firstFit(size);
    }
}

// 首次适应算法
int ContiguousAllocator::firstFit(size_t size) {
    for (size_t i = 0; i < memory_blocks_.size(); ++i) {
        if (memory_blocks_[i].is_free && memory_blocks_[i].size >= size) {
            return static_cast<int>(i);
        }
    }
    return -1;
}

// 最佳适应算法
int ContiguousAllocator::bestFit(size_t size) {
    int best_index = -1;
    size_t best_size = SIZE_MAX;
    
    for (size_t i = 0; i < memory_blocks_.size(); ++i) {
        if (memory_blocks_[i].is_free && 
            memory_blocks_[i].size >= size && 
            memory_blocks_[i].size < best_size) {
            best_index = static_cast<int>(i);
            best_size = memory_blocks_[i].size;
        }
    }
    
    return best_index;
}

// 最坏适应算法
int ContiguousAllocator::worstFit(size_t size) {
    int worst_index = -1;
    size_t worst_size = 0;
    
    for (size_t i = 0; i < memory_blocks_.size(); ++i) {
        if (memory_blocks_[i].is_free && 
            memory_blocks_[i].size >= size && 
            memory_blocks_[i].size > worst_size) {
            worst_index = static_cast<int>(i);
            worst_size = memory_blocks_[i].size;
        }
    }
    
    return worst_index;
}

// 循环首次适应算法
int ContiguousAllocator::nextFit(size_t size) {
    size_t block_count = memory_blocks_.size();
    
    // 从上次分配位置开始查找
    for (size_t i = 0; i < block_count; ++i) {
        size_t index = (next_fit_pointer_ + i) % block_count;
        
        if (memory_blocks_[index].is_free && memory_blocks_[index].size >= size) {
            next_fit_pointer_ = (index + 1) % block_count;
            return static_cast<int>(index);
        }
    }
    
    return -1;
}

} // namespace ZTS_OS 