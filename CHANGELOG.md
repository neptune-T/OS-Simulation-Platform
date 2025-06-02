# 更新日志 | Changelog

本文档记录了ZTS操作系统设计与模拟平台的所有重要更改。

All notable changes to the ZTS Operating System Design & Simulation Platform will be documented in this file.

本项目遵循 [语义化版本控制](https://semver.org/lang/zh-CN/) 规范。

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.0.0/), and this project adheres to [Semantic Versioning](https://semver.org/spec/v2.0.0.html).

## [Unreleased] - 未发布

### 计划添加 | Planned
- 多级反馈队列调度算法
- 虚拟内存页面置换算法（LRU、FIFO、Clock）
- 磁盘调度算法（SCAN、C-SCAN、LOOK）
- 文件系统的图形化界面
- 性能分析和统计功能
- 进程同步经典问题演示

### 计划改进 | Planned Improvements
- 优化内存分配算法性能
- 增强用户界面交互体验
- 添加更多单元测试和集成测试
- 支持配置文件热重载

## [1.0.0-Beta] - 2024-06-02

### 新增功能 | Added
- 🎨 **专业启动界面** - ASCII艺术Logo和系统信息展示
- 🔧 **进程调度算法**
  - FCFS (先来先服务) 调度算法
  - Round Robin (时间片轮转) 调度算法框架
  - SJF (短作业优先) 调度算法框架
  - Priority (优先级) 调度算法框架
- 💾 **内存管理模拟**
  - 基础内存管理器框架
  - 分页内存管理模拟
  - 分段内存管理模拟
- 📋 **进程管理**
  - 进程控制块 (PCB) 实现
  - 进程状态管理
  - 进程队列管理
- 📁 **文件系统模拟**
  - 基础文件系统框架
  - 目录结构管理
  - 文件操作接口
- 🔄 **同步机制**
  - 信号量基础实现
  - 互斥锁框架
  - 条件变量框架
- 🎨 **用户界面**
  - 彩色控制台输出
  - 启动动画和进度条
  - 居中文本显示功能
- 🏗️ **项目基础设施**
  - CMake构建系统
  - 模块化项目结构
  - 完整的文档体系
  - 单元测试框架
  - 构建脚本和工具

### 技术特性 | Technical Features
- ✅ C++17标准支持
- ✅ Windows平台兼容
- ✅ Visual Studio和MinGW编译器支持
- ✅ CMake跨平台构建
- ✅ 模块化代码架构
- ✅ UTF-8编码支持
- ✅ JSON配置文件支持

### 文档 | Documentation
- 📖 完整的项目README
- 📝 贡献指南 (CONTRIBUTING.md)
- 📄 MIT开源许可证
- 🔧 构建说明和环境配置
- 📋 项目结构说明

### 构建和部署 | Build & Deployment
- 🛠️ Windows批处理构建脚本
- ⚙️ CMake配置优化
- 📦 资源文件管理
- 🧪 测试框架集成

## [开发里程碑 | Development Milestones]

### 阶段一：项目基础架构 ✅ (已完成)
- [x] 项目目录结构设计
- [x] CMake构建系统配置
- [x] 基础文档创建
- [x] 代码规范建立
- [x] 专业启动界面实现

### 阶段二：核心算法实现 🚧 (进行中)
- [ ] 进程调度算法完整实现
- [ ] 内存管理算法实现
- [ ] 文件系统基础功能
- [ ] 同步机制实现

### 阶段三：高级功能 📋 (计划中)
- [ ] 图形化用户界面
- [ ] 性能分析工具
- [ ] 实时监控功能
- [ ] 配置管理优化

### 阶段四：测试和优化 📋 (计划中)
- [ ] 完整测试覆盖
- [ ] 性能优化
- [ ] 文档完善
- [ ] 用户体验改进

## [贡献者 | Contributors]

感谢所有为项目做出贡献的开发者！

- **项目创始人**: ZTS Team
- **主要开发者**: [待添加]
- **文档贡献者**: [待添加]
- **测试贡献者**: [待添加]

## [已知问题 | Known Issues]

### v1.0.0-Beta
- [ ] 部分算法仅为框架实现，需要完善具体逻辑
- [ ] 暂无图形化界面，仅支持控制台
- [ ] 测试覆盖率有待提高
- [ ] 跨平台兼容性需要进一步测试

## [反馈和支持 | Feedback & Support]

如果您发现任何问题或有功能建议，请：

1. 📝 在GitHub上创建Issue
2. 📧 发送邮件至 zts.os.design@gmail.com
3. 💬 参与GitHub Discussions讨论

---

**格式说明 | Format Legend:**
- 🎨 用户界面改进
- 🔧 新功能
- 💾 内存/存储相关
- 📋 进程管理
- 📁 文件系统
- 🔄 同步机制
- 🏗️ 基础设施
- 📖 文档
- 🐛 Bug修复
- ⚡ 性能改进
- 🧪 测试
- 🛠️ 构建工具 