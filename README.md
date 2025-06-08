# Mota - 配置文件编译器与代码生成工具

[![License](https://img.shields.io/badge/license-MIT-blue.svg)](LICENSE)
[![C++](https://img.shields.io/badge/language-C%2B%2B20-blue.svg)](https://en.cppreference.com/w/cpp/20)
[![VSCode Extension](https://img.shields.io/badge/VSCode-Extension-007ACC?logo=visualstudiocode)](https://marketplace.visualstudio.com/)
[![Build Status](https://github.com/eachcan/mota/actions/workflows/build.yml/badge.svg)](https://github.com/eachcan/mota/actions)

## 简介

Mota 是一个现代化的配置文件编译器，类似于 Protocol Buffer，但专为配置管理而设计。它将 `.mota` 配置文件编译为 C++ 或其他语言的源代码，让开发者能够基于注解实现各种功能模块，而无需重复处理底层数据操作。

### 🎯 核心理念

**像 Protocol Buffer 一样简单**：
- 定义一次配置结构 (`.mota` 文件)
- 编译生成目标语言代码
- 在应用中直接使用生成的类

**基于注解的模块化开发**：
- **存储模块**：根据 `@Storage` 注解决定存储位置和格式
- **验证模块**：根据 `@Int`、`@Validator` 等注解自动验证数据
- **UI 模块**：根据 `@Switcher`、`@Int` 等注解自动生成界面
- **文档模块**：根据 `@Desc` 等注解自动生成文档

**开发者只需关注业务逻辑**：
- 无需手写序列化/反序列化代码
- 无需手写数据验证逻辑
- 无需手写UI绑定代码
- 无需手写存储管理代码

### ✨ 主要特性

- **强大的类型系统**
  - 基础类型：`int8`/`int16`/`int32`/`int64`/`float32`/`float64`/`string`/`bool`/`bytes`
  - 复合类型：`struct`/`block`/`enum`/`annotation`
  - 类型修饰符：`optional`/`repeated`/`map`
  - 完整的类型推导和验证

- **丰富的注解系统**
  - **存储注解**：`@storage(path, format)` - 自动处理文件存储
  - **UI注解**：`@window`, `@text`, `@int`, `@float`, `@switcher` - 自动生成界面
  - **验证注解**：`@min`, `@max`, `@pattern`, `@required` - 自动数据验证
  - **文档注解**：`@desc`, `@example` - 自动生成文档

- **多语言代码生成**
  - C++ (完整支持)
  - Java (计划中)
  - Python (计划中)
  - TypeScript (计划中)

- **多格式序列化**
  - 二进制：`CBOR`（紧凑高效）
  - 文本：`JSON`（人类可读）
  - 配置：`INI`（兼容旧系统）

- **开发工具支持**
  - VSCode 插件：语法高亮、代码补全、错误检查
  - 实时预览：配置变更即时反馈
  - 调试支持：配置值追踪和验证

## 🚀 快速开始

### 安装

#### Windows 安装器（推荐）
1. 下载 `mota-installer-v0.2.0.exe`
2. 运行安装器，自动配置环境变量
3. 打开新的命令行窗口，运行 `mota --help`

#### ZIP 压缩包
1. 下载 `mota-v0.2.0-windows-x64.zip`
2. 解压到任意目录
3. 将 `mota.exe` 所在目录添加到 PATH 环境变量

#### 从源码构建
```bash
git clone --recursive https://github.com/eachcan/mota.git
cd mota
xmake build
```

### 验证安装
```bash
mota --help
mota --version  # 输出: mota version 1.0.0
```

## 🛠️ 使用方式

### 1. 定义配置结构

创建 `camera_config.mota` 文件：

```mota
namespace vision;

// 相机类型枚举
enum CameraType {
    @desc("标准工业面阵相机")
    AREA_SCAN = 0;
    
    @desc("高精度线扫描相机") 
    LINE_SCAN = 1;
    
    @desc("三维点云采集相机")
    DEPTH = 2;
}

// 相机配置结构
@storage(path = "config/camera.cbor", format = "cbor")
@window(title = "相机配置", width = 800, height = 600)
struct CameraConfig {
    // 基本信息
    @text(maxLength = 50, placeholder = "请输入相机名称")
    @desc("相机标识名称")
    string name = "Camera_01";
    
    // 相机类型
    @select(options = ["AREA_SCAN", "LINE_SCAN", "DEPTH"])
    @desc("选择相机类型")
    CameraType type = AREA_SCAN;
    
    // 位置参数
    @group("位置设置")
    struct Position {
        @int(min = 0, max = 10000, step = 1, unit = "mm")
        @desc("X轴坐标")
        int32 x = 0;
        
        @int(min = 0, max = 10000, step = 1, unit = "mm") 
        @desc("Y轴坐标")
        int32 y = 0;
        
        @float(min = 0.0, max = 360.0, step = 0.1, unit = "度")
        @desc("旋转角度")
        float64 rotation = 0.0;
    } position;
    
    // 成像参数
    @group("成像参数")
    struct Imaging {
        @float(min = 10.0, max = 100000.0, step = 100.0, unit = "μs")
        @desc("曝光时间")
        float64 exposure = 1000.0;
        
        @float(min = 0.1, max = 10.0, step = 0.1)
        @desc("增益值")
        float64 gain = 1.0;
        
        @switcher
        @desc("启用硬件触发")
        bool triggerEnabled = false;
    } imaging;
    
    // 网络设置
    @group("网络设置")
    struct Network {
        @text(pattern = "^\\d{1,3}\\.\\d{1,3}\\.\\d{1,3}\\.\\d{1,3}$")
        @desc("IP地址")
        string ip = "192.168.1.100";
        
        @int(min = 1024, max = 65535)
        @desc("端口号")
        int32 port = 8080;
    } network;
    
    // 高级参数
    @group("高级参数")
    map<string, string> parameters = {
        "PixelFormat": "Mono8",
        "AcquisitionMode": "Continuous"
    };
}
```

### 2. 编译生成代码

```bash
# 基本用法：编译当前目录下的所有.mota文件
mota

# 编译指定文件
mota camera_config.mota

# 指定输出目录
mota camera_config.mota -o output

# 指定模板语言（目前只支持cpp）
mota camera_config.mota -l cpp -o output

# 添加包含路径
mota camera_config.mota -i include_path1 -i include_path2 -o output

# 使用配置文件
mota -c mota-config.json

# 查看帮助
mota --help

# 查看版本
mota --version
```

### 命令行选项说明

```
mota [OPTIONS] [FILE] [...]

Options:
  -h, --help              显示帮助信息
  -V, --version           显示版本信息
  -v, --verbose           显示详细信息
  -i, --include-path PATH 添加包含路径，可以指定多次
  -o, --output-dir PATH   设置输出目录，默认为 output
  -s, --source-dir PATH   设置源文件目录，默认为当前目录
  -l, --lang LANG         设置输出语言，可选值：cpp[默认]
  -c, --config PATH       设置配置文件路径

FILE:
  指定要编译的 Mota 文件或目录路径
  如果未指定，则从当前目录搜索所有.mota文件
```

### 3. 在应用中使用

```cpp
#include "camera_config.h"

int main() {
    // 创建配置实例
    vision::CameraConfig config;
    
    // 设置配置值
    config.setName("MainCamera");
    config.setType(vision::CameraType::AREA_SCAN);
    config.getPosition().setX(1000);
    config.getPosition().setY(2000);
    config.getImaging().setExposure(1500.0);
    
    // 自动验证（基于注解）
    if (!config.validate()) {
        std::cout << "配置验证失败: " << config.getValidationErrors() << std::endl;
        return -1;
    }
    
    // 自动保存（基于 @storage 注解）
    config.save();  // 保存到 config/camera.cbor
    
    // 从文件加载
    auto loaded_config = vision::CameraConfig::load("config/camera.cbor");
    
    return 0;
}
```

### 4. 基于注解的模块开发

#### 存储模块示例
```cpp
// 存储模块根据 @storage 注解自动处理文件操作
class StorageModule {
public:
    template<typename T>
    static void autoSave(const T& config) {
        // 根据 @storage 注解获取路径和格式
        auto storage_info = T::getStorageInfo();
        
        if (storage_info.format == "cbor") {
            saveToCbor(config, storage_info.path);
        } else if (storage_info.format == "json") {
            saveToJson(config, storage_info.path);
        }
    }
};
```

#### 验证模块示例
```cpp
// 验证模块根据 @int, @float, @text 等注解自动验证
class ValidationModule {
public:
    template<typename T>
    static ValidationResult validate(const T& config) {
        ValidationResult result;
        
        // 根据字段注解自动验证
        for (auto& field : T::getFields()) {
            if (field.hasAnnotation("@int")) {
                auto int_anno = field.getAnnotation("@int");
                if (!validateIntRange(field.getValue(), int_anno.min, int_anno.max)) {
                    result.addError(field.name + " 超出范围");
                }
            }
            
            if (field.hasAnnotation("@text")) {
                auto text_anno = field.getAnnotation("@text");
                if (!validateTextLength(field.getValue(), text_anno.maxLength)) {
                    result.addError(field.name + " 长度超限");
                }
            }
        }
        
        return result;
    }
};
```

#### UI模块示例
```cpp
// UI模块根据 @window, @group, @int, @switcher 等注解自动生成界面
class UIModule {
public:
    template<typename T>
    static QWidget* createConfigWidget(T& config) {
        auto window_info = T::getWindowInfo();
        auto widget = new QWidget();
        widget->setWindowTitle(window_info.title);
        widget->resize(window_info.width, window_info.height);
        
        auto layout = new QVBoxLayout(widget);
        
        // 根据字段注解创建控件
        for (auto& field : T::getFields()) {
            if (field.hasAnnotation("@int")) {
                auto spinbox = createIntSpinBox(field);
                layout->addWidget(spinbox);
            } else if (field.hasAnnotation("@switcher")) {
                auto checkbox = createCheckBox(field);
                layout->addWidget(checkbox);
            } else if (field.hasAnnotation("@text")) {
                auto lineedit = createLineEdit(field);
                layout->addWidget(lineedit);
            }
        }
        
        return widget;
    }
};
```

## 📚 注解参考

### 存储注解
- `@storage(path, format)` - 指定存储路径和格式

### UI注解
- `@window(title, width, height)` - 窗口属性
- `@group(title)` - 分组显示
- `@text(maxLength, placeholder, pattern)` - 文本输入
- `@int(min, max, step, unit)` - 整数输入
- `@float(min, max, step, unit)` - 浮点数输入
- `@switcher` - 开关控件
- `@select(options)` - 下拉选择

### 验证注解
- `@min(value)` - 最小值限制
- `@max(value)` - 最大值限制
- `@pattern(regex)` - 正则表达式验证
- `@required` - 必填字段

### 文档注解
- `@desc(text)` - 字段描述
- `@example(value)` - 示例值

## 🔧 构建和分发

```bash
# 开发构建
xmake build

# 运行程序
xmake run mota

# 运行测试
xmake run test_generator

# 创建安装包
xmake run install

# 创建ZIP分发包
xmake run package

# 创建Windows安装器（需要NSIS）
xmake run installer
```

## 📖 更多资源

- [完整文档](docs/)
- [示例项目](examples/)
- [VSCode插件](vscode-extension/)
- [API参考](docs/api/)

## 🤝 贡献

欢迎提交 Issue 和 Pull Request！

## 📄 许可证

本项目采用 MIT 许可证 - 查看 [LICENSE](LICENSE) 文件了解详情。

