# Mota - 现代配置语言解析器与生成器

[![License](https://img.shields.io/badge/license-MIT-blue.svg)](LICENSE)
[![C++](https://img.shields.io/badge/language-C%2B%2B20-blue.svg)](https://en.cppreference.com/w/cpp/20)
[![Build Status](https://img.shields.io/badge/build-passing-brightgreen.svg)](https://github.com/eachcan/mota)

## 简介

Mota 是一个专为工业自动化和嵌入式系统设计的现代配置语言。它提供了强大的类型系统、灵活的注解机制和清晰的模块化设计，使得配置管理变得简单而高效。

### 主要特性

- **强大的类型系统**
  - 基础类型：`int32`, `int64`, `float32`, `string`, `bool`, `bytes`
  - 修饰类型：`map`, `repeated`, `optional`
  - 自定义类型：`struct`, `block`, `enum`
  - 完整的类型检查和验证

- **灵活的注解系统**
  - 文件级注解：指定输出格式和路径
  - 字段级注解：添加元数据和验证规则
  - 枚举值注解：提供额外的描述信息

- **模块化设计**
  - 命名空间支持：避免名称冲突
  - 文件包含机制：复用配置定义
  - 继承系统：共享通用配置

- **多格式支持**
  - CBOR：紧凑的二进制格式
  - JSON：人类可读的文本格式
  - INI：简单的键值对格式
  - 自定义格式扩展

## 快速开始

### 安装

#### 自主编译

1. 克隆仓库：
```bash
git clone git@github.com:eachcan/mota.git
cd mota
```

2. 构建项目：
```bash
xmake
```

#### 使用预编译包

1. 下载 mota

发布地址： https://github.com/eachcan/mota/releases

2. 安装 mota

将 mota.exe 放到你命令行可访问到的地方


### 基本用法

1. 创建 Mota 配置文件 (`config.mota`):

```mota
namespace myapp.config;

// 定义相机类型枚举
enum CameraType {
    @enumValue(title = "DSLR相机", desc = "专业单反相机")
    DSLR = 0;
    @enumValue(title = "无反相机", desc = "专业微单相机")
    Mirrorless = 1;
}

// 定义相机配置结构
@storage(
    path = "camera_config.cbor",
    format = "cbor" 
)
@window(title = "相机配置", desc = "相机配置")
@scope(value = "product")
struct CameraList {
  @iniGroup(value = "AvaiableSn")
  repeated string availableSn;

  @iniGroup(value = "TASK1_CAM1")
  CameraConfig task1Cam1;
}

block CameraConfig {
    /* 相机位置参数 */
    @int(min = 5, max = 10000)
    int32 position = 0;
    
    /* 相机类型设置 */
    @select()
    CameraType type = DSLR;
    
    /* 可选的参考位置 */
    optional int32 refPosition;
    
    /* 相机参数列表 */
    repeated string params;
    
    /* 任务配置映射 */
    map Task tasks = ["default", "custom"];
}
```

2. 运行解析器：
```bash
mota config.mota
```

## 语法文档

[Mota 语法文档](docs/mota-script-syntax.md)
[模型定义指南](docs/model-definition.md)

### 类型系统

#### 基础类型
- `int8`: 8位整数
- `int16`: 16位整数
- `int32`: 32位整数
- `int64`: 64位整数
- `float32`: 32位浮点数
- `string`: 字符串
- `bool`: 布尔值
- `bytes`: 字节数组

#### 自定义类型
- `block`: 块类型
- `enum`: 枚举类型
- `struct`: 结构体类型

#### 修饰符
- `optional`: 可选字段
- `repeated`: 数组字段
- `map`: 映射字段

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

## 项目结构

```
mota/
├── docs/                 # 文档
│   └── mota-script-syntax.md  # 语法详细说明
├── src/                  # 源代码
│   ├── lexer.cpp         # 词法分析器
│   ├── parser.cpp        # 语法分析器
│   ├── ast.cpp           # 抽象语法树
│   └── main.cpp          # 主程序
├── include/              # 头文件
│   ├── lexer.h
│   ├── parser.h
│   └── ast.h
├── test/                 # 测试文件
│   └── test_parser.cpp
├── examples/             # 示例
│   └── example.mota
└── xmake.lua            # 构建配置
```

## 开发计划

- [x] 词法分析器
- [x] 语法分析器
- [x] 抽象语法树
- [ ] 代码生成器
- [ ] 配置验证器
- [x] IDE 插件支持, [visual studio code](https://github.com/eachcan/mota-vsc-plugin)

## 贡献指南

1. Fork 本仓库
2. 创建特性分支 (`git checkout -b feature/amazing-feature`)
3. 提交更改 (`git commit -m 'Add some amazing feature'`)
4. 推送到分支 (`git push origin feature/amazing-feature`)
5. 提交 Pull Request

## 许可证

本项目采用 MIT 许可证 - 详见 [LICENSE](LICENSE) 文件

## 联系方式

- 维护者：eachcan
- 邮箱：eachcan@qq.com
- 项目主页：[Mota Project](https://github.com/eachcan/mota)

## 致谢

感谢所有为本项目做出贡献的开发者！
