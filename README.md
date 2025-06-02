# ZTS 操作系统设计与模拟平台
# ZTS Operating System Design & Simulation Platform

![Version](https://img.shields.io/badge/version-v1.0.0--Beta-blue)
![Platform](https://img.shields.io/badge/platform-Windows%20x64-lightgrey)
![Language](https://img.shields.io/badge/language-C++17-orange)
![License](https://img.shields.io/badge/license-MIT-green)

## 项目简介 | Project Overview

ZTS操作系统设计与模拟平台是一个专业级的C++项目，旨在模拟现代操作系统的核心功能和算法。本项目提供了完整的进程调度、内存管理、文件系统、同步机制等模拟实现，是学习操作系统原理和算法的绝佳工具。

The ZTS Operating System Design & Simulation Platform is a professional-grade C++ project designed to simulate core functionalities and algorithms of modern operating systems. This project provides comprehensive implementations of process scheduling, memory management, file systems, synchronization mechanisms, and more.

## ✨ 主要特性 | Key Features

### 🔧 进程调度算法 | Process Scheduling Algorithms
- **FCFS** (First Come First Served) - 先来先服务
- **Round Robin** - 时间片轮转
- **SJF** (Shortest Job First) - 短作业优先
- **Priority Scheduling** - 优先级调度
- **Multi-level Queue** - 多级队列调度

### 💾 内存管理 | Memory Management
- **分页管理** (Paging) - 固定分区内存管理
- **分段管理** (Segmentation) - 可变分区内存管理
- **虚拟内存** (Virtual Memory) - 页面置换算法
- **内存碎片管理** - 内存合并与回收

### 📁 文件系统模拟 | File System Simulation
- **目录结构管理** - 层次化目录树
- **文件分配算法** - 连续、链式、索引分配
- **磁盘调度算法** - FCFS、SSTF、SCAN、C-SCAN

### 🔄 进程同步 | Process Synchronization
- **信号量机制** (Semaphores)
- **互斥锁** (Mutexes)
- **条件变量** (Condition Variables)
- **经典同步问题** - 生产者消费者、读者写者、哲学家进餐

### 🎨 用户界面 | User Interface
- **专业启动界面** - ASCII艺术Logo和系统信息
- **交互式命令行** - 模拟操作系统Shell
- **实时状态监控** - 进程、内存、文件系统状态
- **彩色输出支持** - 增强用户体验

## 📁 项目结构 | Project Structure

```
ZTS_OS_Design/
├── src/                    # 源代码目录
│   ├── scheduler/          # 进程调度模块
│   ├── memory/             # 内存管理模块
│   ├── filesystem/         # 文件系统模块
│   ├── process/            # 进程管理模块
│   ├── synchronization/    # 同步机制模块
│   └── ui/                 # 用户界面模块
├── include/                # 头文件目录
│   ├── core/               # 核心头文件
│   ├── algorithms/         # 算法头文件
│   └── utils/              # 工具头文件
├── tests/                  # 测试目录
│   ├── unit/               # 单元测试
│   └── integration/        # 集成测试
├── docs/                   # 文档目录
│   ├── api/                # API文档
│   └── design/             # 设计文档
├── examples/               # 示例程序
│   ├── scheduler_demo/     # 调度算法演示
│   └── memory_demo/        # 内存管理演示
├── resources/              # 资源文件
│   ├── configs/            # 配置文件
│   └── logs/               # 日志文件
├── scripts/                # 构建和工具脚本
├── config/                 # 项目配置
└── build/                  # 构建输出目录
```

## 🚀 快速开始 | Quick Start

### 环境要求 | Prerequisites

- **操作系统**: Windows 10/11 (x64)
- **编译器**: MSVC 2019+ 或 MinGW-w64
- **C++标准**: C++17 或更高
- **构建工具**: CMake 3.16+
- **可选**: Visual Studio 2019+ 或 Visual Studio Code

### 编译构建 | Build Instructions

#### 方法一：使用CMake (推荐)
```bash
# 克隆或下载项目
cd ZTS_OS_Design

# 创建构建目录
mkdir build
cd build

# 配置项目
cmake .. -G "Visual Studio 16 2019" -A x64

# 编译项目
cmake --build . --config Release

# 运行程序
cd bin
./ZTS_OS_Design.exe
```

#### 方法二：使用Visual Studio
1. 用Visual Studio打开项目文件夹
2. 选择CMakeLists.txt作为项目配置
3. 按F5运行或Ctrl+F5编译运行

#### 方法三：直接编译
```bash
# 使用g++直接编译（需要MinGW-w64）
g++ -std=c++17 -O2 -Wall -I./include src/**/*.cpp main.cpp -o ZTS_OS_Design.exe
```

## 📖 使用说明 | Usage Guide

### 启动程序
运行程序后，您将看到专业的启动界面，包含：
- ZTS操作系统Logo
- 系统信息和版本
- 启动动画和进度条

### 主要功能模块

1. **进程调度器演示**
   - 创建多个模拟进程
   - 选择不同调度算法
   - 观察调度结果和性能指标

2. **内存管理演示**
   - 模拟内存分配和释放
   - 查看内存使用情况
   - 测试不同分配策略

3. **文件系统操作**
   - 创建、删除文件和目录
   - 模拟文件读写操作
   - 查看磁盘使用情况

4. **同步机制测试**
   - 运行经典同步问题
   - 观察竞态条件和死锁
   - 测试同步解决方案

## 🧪 测试 | Testing

项目包含完整的测试套件：

```bash
# 运行所有测试
cd build
ctest -C Release

# 运行特定测试
ctest -R scheduler_test
ctest -R memory_test
```

## 📚 文档 | Documentation

- **API文档**: [docs/api/](docs/api/) - 详细的API参考
- **设计文档**: [docs/design/](docs/design/) - 系统架构和设计说明
- **用户指南**: [docs/user_guide.md](docs/user_guide.md) - 详细使用说明
- **开发指南**: [docs/developer_guide.md](docs/developer_guide.md) - 开发和贡献指南

## 🤝 贡献 | Contributing

我们欢迎社区贡献！请查看 [CONTRIBUTING.md](CONTRIBUTING.md) 了解如何参与项目开发。

### 贡献方式
- 🐛 报告Bug
- 💡 提出新功能建议
- 📝 改进文档
- 🔧 提交代码修复
- ✨ 添加新功能

## 📄 许可证 | License

本项目采用 MIT 许可证 - 查看 [LICENSE](LICENSE) 文件了解详情。


## 🔖 版本历史 | Version History

- **v1.0.0-Beta** - 初始发布版本
  - 基础进程调度算法实现
  - 内存管理模拟
  - 专业启动界面
  - 完整项目结构

---

⭐ **臭要饭的来要Star来了！**

🚀 **Happy Coding with Operating System Simulation!** 