# Mota - 现代配置语言与工具链

[![License](https://img.shields.io/badge/license-MIT-blue.svg)](LICENSE)
[![C++](https://img.shields.io/badge/language-C%2B%2B20-blue.svg)](https://en.cppreference.com/w/cpp/20)
[![VSCode Extension](https://img.shields.io/badge/VSCode-Extension-007ACC?logo=visualstudiocode)](https://marketplace.visualstudio.com/)
[![Build Status](https://github.com/eachcan/mota/actions/workflows/build.yml/badge.svg)](https://github.com/eachcan/mota/actions)

## 简介

Mota 是一个专为工业自动化和嵌入式系统设计的现代配置语言及工具链。它结合了强大的类型系统、灵活的注解机制和直观的模块化设计，使配置管理变得简单而高效。

### ✨ 主要特性

- **完整的语言工具链**
  - 高性能的词法分析器和语法分析器
  - 丰富的抽象语法树(AST)支持
  - 全面的错误处理和恢复机制
  - 跨平台支持（Windows/Linux/macOS）

- **强大的类型系统**
  - 基础类型：`int8`/`int16`/`int32`/`int64`/`float32`/`float64`/`string`/`bool`/`bytes`
  - 复合类型：`struct`/`block`/`enum`/`annotation`
  - 类型修饰符：`optional`/`repeated`/`map`
  - 完整的类型推导和验证

- **企业级注解系统**
  - 存储配置：`@storage(path, format)`
  - UI 集成：`@window`, `@text`, `@int`, `@float`, `@switcher`
  - 验证规则：`@min`, `@max`, `@pattern`, `@required`
  - 文档生成：`@desc`, `@example`

- **开发工具支持**
  - VSCode 插件：语法高亮、代码补全、定义跳转
  - 代码片段：快速生成常用结构
  - 实时错误检查：即时反馈语法和语义错误
  - 文档悬停：显示类型定义和文档注释

- **多格式输出**
  - 二进制：`CBOR`（紧凑高效）
  - 文本：`JSON`（人类可读）
  - 配置：`INI`（兼容旧系统）
  - 可扩展：支持自定义格式

## 🚀 快速开始

### 系统要求

- Windows/Linux/macOS
- C++20 兼容编译器 (GCC 10+/Clang 12+/MSVC 2019+)
- [xmake](https://xmake.io/) 构建工具
- Node.js 16+ (仅开发 VSCode 插件需要)

### 安装

#### 方式一：使用预编译二进制文件（推荐）

1. 从 [GitHub Releases](https://github.com/eachcan/mota/releases) 下载最新版本
2. 解压到任意目录
3. 将可执行文件所在目录添加到系统 PATH 环境变量

#### 方式二：从源码构建

```bash
# 克隆仓库
git clone --recursive https://github.com/eachcan/mota.git
cd mota

# 安装依赖并构建
xmake f -p windows -a x64  # 或 -p linux/macos
xmake -j$(nproc)

# 安装到系统路径 (可选)
xmake install -o /usr/local
```

#### 方式三：VSCode 插件

1. 在 VSCode 中搜索并安装 "Mota Language" 插件
2. 或从 [发布页面](https://github.com/eachcan/mota/releases) 下载 .vsix 文件并手动安装


## 🛠️ 基本用法

### 1. 创建 Mota 配置文件

创建一个名为 `camera.mota` 的配置文件：

```mota
// 文件: camera.mota
namespace example.vision;

/**
 * 相机类型定义
 * 支持多种工业相机类型
 */
enum CameraType {
    @enumValue(title = "面阵相机", desc = "标准工业面阵相机")
    AREA_SCAN = 0;
    
    @enumValue(title = "线阵相机", desc = "高精度线扫描相机")
    LINE_SCAN = 1;
    
    @enumValue(title = "3D相机", desc = "三维点云采集相机")
    DEPTH = 2;
}

/**
 * 相机配置块
 * 定义相机的通用参数
 */
block CameraConfig {
    // 相机位置 (单位: mm)
    @int(min = 0, max = 10000, step = 1, desc = "X轴坐标")
    int32 x = 0;
    
    @int(min = 0, max = 10000, step = 1, desc = "Y轴坐标")
    int32 y = 0;
    
    // 相机类型选择
    @select(desc = "选择相机类型")
    CameraType type = AREA_SCAN;
    
    // 曝光时间 (微秒)
    @float(min = 10.0, max = 100000.0, step = 100.0, desc = "曝光时间(μs)")
    float64 exposure = 1000.0;
    
    // 是否启用触发模式
    @switcher(desc = "启用硬件触发")
    bool triggerEnabled = false;
    
    // 可选参数
    optional string serialNumber;
    
    // 相机参数映射
    map<string, string> parameters = {
        "Gain": "1.0",
        "PixelFormat": "Mono8"
    };
}

/**
 * 视觉系统配置
 */
@storage(
    path = "config/vision_system.cbor",
    format = "cbor"
)
@window(title = "视觉系统配置", desc = "配置视觉系统中的所有相机")
@scope("system")
struct VisionSystem {
    // 系统名称
    @text(maxLength = 50, desc = "系统标识名称")
    string name = "DefaultSystem";
    
    // 可用相机列表
    @group("相机列表")
    repeated CameraConfig cameras;
    
    // 网络配置
    @group("网络设置")
    struct Network {
        @text(desc = "IP地址")
        string ip = "192.168.1.100";
        
        @int(min = 1024, max = 65535, desc = "端口号")
        int32 port = 8080;
    } network;
}
```

### 2. 编译配置

使用 Mota 编译器处理配置文件：

```bash
# 生成 C++ 头文件和序列化代码
mota compile camera.mota --output generated/

# 或者直接生成目标格式
mota build camera.mota --format cbor --output config/
```

### 3. 在代码中使用

```cpp
#include "generated/vision_system.h"

int main() {
    // 从文件加载配置
    auto config = example::vision::VisionSystem::load("config/vision_system.cbor");
    
    // 访问配置项
    std::cout << "System name: " << config.name << std::endl;
    
    // 修改配置
    config.cameras[0].exposure = 2000.0;
    
    // 保存配置
    config.save("config/vision_system_updated.cbor");
    
    return 0;
}
```

### 4. 在 VSCode 中编辑

1. 安装 Mota 语言插件
2. 打开 `.mota` 文件
3. 享受语法高亮、代码补全和实时错误检查
4. 使用 `Ctrl+Click` 跳转到定义
5. 使用 `F2` 重命名符号

## 📚 语法参考

### 1. 类型系统

#### 1.1 基础类型

| 类型 | 描述 | 默认值 | 示例 |
|------|------|--------|------|
| `int8` | 8位有符号整数 | 0 | `int8 value = -128;` |
| `int16` | 16位有符号整数 | 0 | `int16 port = 8080;` |
| `int32` | 32位有符号整数 | 0 | `int32 counter = 0;` |
| `int64` | 64位有符号整数 | 0 | `int64 timestamp = 0;` |
| `float32` | 32位浮点数 | 0.0 | `float32 ratio = 1.5f;` |
| `float64` | 64位浮点数 | 0.0 | `float64 pi = 3.14159;` |
| `string` | UTF-8 字符串 | `""` | `string name = "test";` |
| `bool` | 布尔值 | `false` | `bool enabled = true;` |
| `bytes` | 二进制数据 | `[]` | `bytes data = [0x01, 0x02];` |

#### 1.2 复合类型

**枚举 (Enum)**
```mota
enum LogLevel {
    @enumValue(title = "调试")
    DEBUG = 0;
    
    @enumValue(title = "信息")
    INFO = 1;
    
    @enumValue(title = "警告")
    WARNING = 2;
    
    @enumValue(title = "错误")
    ERROR = 3;
}
```

**结构体 (Struct)**
```mota
struct Point {
    int32 x = 0;
    int32 y = 0;
    int32 z = 0;
}
```

**块 (Block)**
```mota
block SensorConfig {
    string name = "";
    float64 minValue = 0.0;
    float64 maxValue = 100.0;
}
```

#### 1.3 类型修饰符

| 修饰符 | 描述 | 示例 |
|--------|------|------|
| `optional` | 可选字段 | `optional string description;` |
| `repeated` | 动态数组 | `repeated int32 values;` |
| `map<K,V>` | 键值映射 | `map<string, int32> scores;` |

### 2. 注解系统

#### 2.1 存储注解

```mota
@storage(
    path = "config/app.cbor",  // 输出路径
    format = "cbor"              // 输出格式 (cbor/json/ini)
)
```

#### 2.2 UI 控件注解

```mota
// 文本输入
@text(maxLength = 100, desc = "用户名称")
string username = "admin";

// 整数输入
@int(min = 0, max = 100, step = 1, desc = "质量 (0-100)")
int32 quality = 80;

// 浮点数输入
@float(min = 0.0, max = 1.0, step = 0.1, desc = "阈值")
float64 threshold = 0.5;

// 开关控件
@switcher(desc = "启用高级功能")
bool advancedMode = false;

// 下拉选择
@select(desc = "选择算法")
AlgorithmType algorithm = ALGO_FAST;
```

#### 2.3 验证注解

```mota
// 必填字段
@required(desc = "名称不能为空")
string name;

// 正则验证
@pattern(regex = "^[a-zA-Z0-9_]+$", 
         message = "只能包含字母、数字和下划线")
string id;

// 自定义验证
@validate(expr = "value >= min && value <= max", 
          message = "值必须在 {min} 和 {max} 之间")
int32 value;
```

### 3. 模块系统

#### 3.1 命名空间

```mota
namespace com.example.vision;

// 定义类型...
```

#### 3.2 文件包含

```mota
// 引入其他 Mota 文件
include "common/types.mota";
include "config/network.mota";
```

#### 3.3 继承

```mota
// 基础配置
struct BaseConfig {
    string name;
    string description;
}

// 扩展配置
struct ExtendedConfig : BaseConfig {
    int32 timeout = 5000;
    repeated string options;
}
```

## 📂 项目结构

```
mota/
├── docs/                    # 项目文档
│   ├── design/              # 设计文档
│   ├── examples/            # 示例代码
│   └── api/                 # API 参考
│
├── include/                # 公共头文件
│   ├── ast.h               # 抽象语法树定义
│   ├── lexer.h             # 词法分析器接口
│   └── parser.h            # 语法分析器接口
│
├── src/                   # 源代码
│   ├── ast.cpp             # AST 实现
│   ├── lexer.cpp           # 词法分析器实现
│   ├── parser.cpp          # 语法分析器实现
│   └── main.cpp            # 主程序入口
│
├── test/                  # 单元测试
│   ├── test_lexer.cpp      # 词法分析器测试
│   └── test_parser.cpp     # 语法分析器测试
│
├── vsc-plugin/            # VSCode 插件
│   ├── syntaxes/           # 语法高亮规则
│   ├── snippets/           # 代码片段
│   └── src/                # 插件源代码
│
├── xmake.lua              # 构建配置
└── README.md               # 项目说明
```

## 🤝 贡献指南

我们欢迎任何形式的贡献！以下是参与项目的步骤：

1. **报告问题**
   - 在 [Issues](https://github.com/eachcan/mota/issues) 中搜索是否已存在相关问题
   - 创建新 issue 描述问题或建议

2. **开发环境设置**
   ```bash
   # 克隆仓库
   git clone --recursive https://github.com/eachcan/mota.git
   cd mota
   
   # 安装依赖
   xmake f -p windows -a x64  # 或 -p linux/macos
   xmake -j$(nproc)
   
   # 运行测试
   xmake run test_lexer
   xmake run test_parser
   ```

3. **提交更改**
   ```bash
   # 创建特性分支
   git checkout -b feature/your-feature
   
   # 提交更改
   git add .
   git commit -m "feat: 添加新功能"
   
   # 推送到远程仓库
   git push origin feature/your-feature
   ```

4. **创建 Pull Request**
   - 在 GitHub 上创建 Pull Request
   - 描述变更内容和动机
   - 等待代码审查

### 提交信息规范

我们遵循 [Conventional Commits](https://www.conventionalcommits.org/) 规范：

- `feat:` 新功能
- `fix:` 修复 bug
- `docs:` 文档更新
- `style:` 代码格式调整
- `refactor:` 代码重构
- `test:` 测试相关
- `chore:` 构建过程或辅助工具的变动

## 📄 许可证

本项目采用 [MIT 许可证](LICENSE) 发布。

### 注解系统

注解用于为类型和字段添加元数据：

```mota
@storage(
    path = "config/${name}.cbor",  // 输出文件路径
    format = "cbor"                // 输出格式
)
@window(title = "配置窗口", desc = "配置描述")
@scope(value = "global")           // 配置级别
```

### 注释系统

支持两种注释风格：

```mota
// 单行注释：编译时会被忽略

/* 块注释：
   会被保留用于文档生成
   支持多行 */
```

### 继承系统

```mota
// 基础配置
struct BaseConfig {
    int32 version;
}

// 扩展配置
struct ExtendedConfig : struct BaseConfig {
    string name;
}
```

## 开发计划

- [x] 词法分析器
- [x] 语法分析器
- [x] 抽象语法树
- [ ] 代码生成器
- [ ] 配置验证器
- [x] IDE 插件支持, [visual studio code](https://github.com/eachcan/mota-vsc-plugin)

## 许可证

本项目采用 MIT 许可证 - 详见 [LICENSE](LICENSE) 文件

## 联系方式

- 维护者：eachcan
- 邮箱：eachcan@qq.com
- 项目主页：[Mota Project](https://github.com/eachcan/mota)

