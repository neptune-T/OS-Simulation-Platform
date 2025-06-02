# 贡献指南 | Contributing Guide

感谢您对ZTS操作系统设计与模拟平台的关注！我们欢迎社区的贡献和参与。

Thank you for your interest in the ZTS Operating System Design & Simulation Platform! We welcome contributions from the community.

## 🤝 如何贡献 | How to Contribute

### 报告问题 | Reporting Issues

如果您发现了Bug或有功能建议，请：

1. 在提交问题前，先搜索现有的issues
2. 使用清晰、描述性的标题
3. 提供详细的复现步骤（对于Bug）
4. 包含您的环境信息（操作系统、编译器版本等）

### 提交代码 | Submitting Code

1. **Fork项目**
   ```bash
   git fork https://github.com/ZTS-Team/OS-Design-Simulation
   ```

2. **创建功能分支**
   ```bash
   git checkout -b feature/amazing-feature
   ```

3. **提交更改**
   ```bash
   git commit -m "Add some amazing feature"
   ```

4. **推送分支**
   ```bash
   git push origin feature/amazing-feature
   ```

5. **创建Pull Request**

## 📝 代码规范 | Code Standards

### C++编码规范

- 使用C++17标准
- 遵循Google C++编码规范
- 使用4个空格缩进，不使用Tab
- 类名使用帕斯卡命名法（PascalCase）
- 函数和变量使用驼峰命名法（camelCase）
- 常量使用全大写加下划线（UPPER_CASE）

### 代码示例

```cpp
// 类定义
class ProcessScheduler {
private:
    std::vector<Process> processQueue_;
    int timeQuantum_;
    
public:
    ProcessScheduler(int timeQuantum);
    void addProcess(const Process& process);
    Process getNextProcess();
    
    // 常量定义
    static const int DEFAULT_TIME_QUANTUM = 10;
};

// 函数实现
void ProcessScheduler::addProcess(const Process& process) {
    processQueue_.push_back(process);
}
```

### 注释规范

- 使用中文注释（如项目要求）
- 类和函数必须有详细的注释
- 复杂算法需要行内注释说明

```cpp
/**
 * @brief 轮转调度算法实现类
 * @details 实现时间片轮转调度，支持动态时间片调整
 */
class RoundRobinScheduler : public SchedulerBase {
private:
    int timeQuantum_;  // 时间片大小
    
public:
    /**
     * @brief 构造函数
     * @param timeQuantum 时间片大小，默认为10ms
     */
    explicit RoundRobinScheduler(int timeQuantum = 10);
    
    /**
     * @brief 调度下一个进程
     * @return 下一个要执行的进程，如果队列为空返回nullptr
     */
    Process* scheduleNext() override;
};
```

## 🧪 测试要求 | Testing Requirements

### 单元测试

- 所有新功能必须包含单元测试
- 测试覆盖率应达到80%以上
- 使用描述性的测试名称

```cpp
TEST(RoundRobinSchedulerTest, ShouldScheduleProcessesInCorrectOrder) {
    // Given
    RoundRobinScheduler scheduler(10);
    Process p1("Process1", 0, 20);
    Process p2("Process2", 0, 15);
    
    // When
    scheduler.addProcess(p1);
    scheduler.addProcess(p2);
    
    // Then
    EXPECT_EQ(scheduler.scheduleNext()->getName(), "Process1");
    EXPECT_EQ(scheduler.scheduleNext()->getName(), "Process2");
}
```

### 集成测试

- 测试模块间的交互
- 验证完整的用户场景

## 📚 文档要求 | Documentation Requirements

### API文档

- 所有公共接口必须有详细文档
- 使用Doxygen格式注释
- 包含使用示例

### 设计文档

- 新功能需要设计文档
- 说明设计思路和架构决策
- 包含类图和时序图

## 🔍 代码审查 | Code Review

### Pull Request要求

1. **清晰的标题和描述**
   - 说明更改的内容和原因
   - 引用相关的issue编号

2. **小而专注的更改**
   - 每个PR应该专注于一个功能或修复
   - 避免大量无关的更改

3. **完整的测试**
   - 包含单元测试和集成测试
   - 所有测试必须通过

4. **文档更新**
   - 更新相关的API文档
   - 更新用户指南（如需要）

### 审查检查清单

- [ ] 代码遵循项目规范
- [ ] 包含适当的测试
- [ ] 文档已更新
- [ ] 没有引入新的编译警告
- [ ] 性能影响已评估

## 🚀 开发环境设置 | Development Environment

### 必需工具

- Visual Studio 2019+ 或 MinGW-w64
- CMake 3.16+
- Git

### 推荐工具

- Visual Studio Code
- ClangFormat（代码格式化）
- Doxygen（文档生成）

### 环境配置

1. **克隆项目**
   ```bash
   git clone https://github.com/ZTS-Team/OS-Design-Simulation.git
   cd OS-Design-Simulation
   ```

2. **配置构建**
   ```bash
   mkdir build
   cd build
   cmake .. -G "Visual Studio 16 2019" -A x64
   ```

3. **编译项目**
   ```bash
   cmake --build . --config Debug
   ```

4. **运行测试**
   ```bash
   ctest -C Debug
   ```

## 📋 发布流程 | Release Process

### 版本命名

- 使用语义化版本控制（Semantic Versioning）
- 格式：`MAJOR.MINOR.PATCH`
- 示例：`1.0.0`, `1.1.0`, `1.1.1`

### 发布检查清单

- [ ] 所有测试通过
- [ ] 文档已更新
- [ ] 版本号已更新
- [ ] CHANGELOG已更新
- [ ] 性能基准测试通过

## 🎯 优先级领域 | Priority Areas

我们特别欢迎以下领域的贡献：

1. **算法优化** - 改进调度算法的性能
2. **新功能** - 添加新的操作系统概念模拟
3. **用户界面** - 改进CLI和可视化
4. **文档** - 改进代码注释和用户文档
5. **测试** - 增加测试覆盖率
6. **性能** - 优化程序性能

## 🏆 贡献者认可 | Contributor Recognition

我们会在以下方式认可贡献者：

- 在README中列出贡献者
- 在发布说明中提及重要贡献
- 为活跃贡献者提供项目徽章

## 📞 联系方式 | Contact

如果您有任何问题或需要帮助：

- 📧 邮箱：zts.os.design@gmail.com
- 💬 Issues：在GitHub上创建issue
- 📱 讨论：使用GitHub Discussions

---

再次感谢您的贡献！让我们一起构建更好的操作系统学习平台！

Thank you for contributing! Let's build a better OS learning platform together! 