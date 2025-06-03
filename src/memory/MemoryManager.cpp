#include "../../include/memory/MemoryManager.h"
#include <algorithm>
#include <iostream>
#include <iomanip>

/**
 * @file MemoryManager.cpp
 * @brief 内存管理器基类实现
 * @author ZTS Operating System Design Team
 * @date 2025
 */

namespace ZTS_OS {

// 构造函数
MemoryManager::MemoryManager(size_t total_size) 
    : total_size_(total_size), strategy_(MemoryAllocationStrategy::FIRST_FIT) {
    // 初始化整个内存为一个大的空闲块
    memory_blocks_.emplace_back(0, total_size, true, -1, "空闲");
}

// 获取内存使用率
double MemoryManager::getMemoryUtilization() const {
    size_t used_size = getUsedSize();
    return static_cast<double>(used_size) / total_size_ * 100.0;
}

// 获取碎片化程度
double MemoryManager::getFragmentation() const {
    size_t free_size = getFreeSize();
    if (free_size == 0) return 0.0;
    
    // 计算最大空闲块
    size_t largest_free_block = 0;
    for (const auto& block : memory_blocks_) {
        if (block.is_free && block.size > largest_free_block) {
            largest_free_block = block.size;
        }
    }
    
    // 外部碎片化 = (总空闲空间 - 最大空闲块) / 总空闲空间
    if (largest_free_block >= free_size) return 0.0;
    return static_cast<double>(free_size - largest_free_block) / free_size * 100.0;
}

// 获取已使用内存大小
size_t MemoryManager::getUsedSize() const {
    size_t used = 0;
    for (const auto& block : memory_blocks_) {
        if (!block.is_free) {
            used += block.size;
        }
    }
    return used;
}

// 获取空闲内存大小
size_t MemoryManager::getFreeSize() const {
    return total_size_ - getUsedSize();
}

// 内存压缩（碎片整理）
void MemoryManager::compactMemory() {
    std::cout << "\n🔧 开始内存压缩..." << std::endl;
    
    // 将所有已分配的块移到内存开头
    std::vector<MemoryBlock> new_blocks;
    size_t current_address = 0;
    
    // 先添加所有已分配的块
    for (auto& block : memory_blocks_) {
        if (!block.is_free) {
            block.start_address = current_address;
            new_blocks.push_back(block);
            current_address += block.size;
            
            std::cout << "移动进程 " << block.process_id << " (" << block.name 
                      << ") 到地址 " << block.start_address << std::endl;
        }
    }
    
    // 如果还有剩余空间，添加一个空闲块
    if (current_address < total_size_) {
        new_blocks.emplace_back(current_address, total_size_ - current_address, true, -1, "空闲");
    }
    
    memory_blocks_ = std::move(new_blocks);
    
    std::cout << "✅ 内存压缩完成！" << std::endl;
}

// 合并相邻的空闲块
void MemoryManager::mergeAdjacentFreeBlocks() {
    std::sort(memory_blocks_.begin(), memory_blocks_.end(),
              [](const MemoryBlock& a, const MemoryBlock& b) {
                  return a.start_address < b.start_address;
              });
    
    std::vector<MemoryBlock> merged_blocks;
    
    for (const auto& block : memory_blocks_) {
        if (merged_blocks.empty()) {
            merged_blocks.push_back(block);
        } else {
            auto& last_block = merged_blocks.back();
            
            // 如果当前块和上一个块都是空闲且相邻，则合并
            if (last_block.is_free && block.is_free &&
                last_block.end_address() + 1 == block.start_address) {
                last_block.size += block.size;
            } else {
                merged_blocks.push_back(block);
            }
        }
    }
    
    memory_blocks_ = std::move(merged_blocks);
}

// 分割内存块
int MemoryManager::splitBlock(int block_index, size_t size) {
    if (block_index < 0 || block_index >= static_cast<int>(memory_blocks_.size())) {
        return -1;
    }
    
    MemoryBlock& block = memory_blocks_[block_index];
    
    if (!block.is_free || block.size < size) {
        return -1;
    }
    
    // 如果块大小正好等于请求大小，不需要分割
    if (block.size == size) {
        return block_index;
    }
    
    // 创建新的空闲块
    MemoryBlock new_block(block.start_address + size, 
                         block.size - size, 
                         true, -1, "空闲");
    
    // 调整原块大小
    block.size = size;
    
    // 插入新块
    memory_blocks_.insert(memory_blocks_.begin() + block_index + 1, new_block);
    
    return block_index;
}

} // namespace ZTS_OS 