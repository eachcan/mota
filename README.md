# Mota 语言解析器与生成器

Mota 是一种自定义的配置文件语言，旨在为开发人员提供灵活、可扩展的方式来定义和管理配置文件，特别是在硬件和嵌入式开发中。它支持结构化的配置文件定义，注解、继承、数据类型、注释等特性，适用于多种输出格式（如 CBOR、JSON、INI 等）。本项目提供了 Mota 语言的解析器和生成器，可以根据 `.mota` 配置文件自动生成相应的 C++ 代码和配置文件处理逻辑。

## 项目目标

1. **语言设计**：定义一种简洁的配置文件语言，支持字段定义、继承、注解、默认值等特性。
2. **解析器**：将 `.mota` 文件解析为抽象语法树（AST），并提供相应的字段与结构体映射。
3. **生成器**：根据 AST 生成对应的 C++ 类代码，能够读取和写入配置文件（如 CBOR 格式）。

## 主要功能

- **结构体（Struct）与块（Block）定义**：支持 `struct` 和 `block` 类型，可以包含多种字段和复杂的嵌套关系。
- **注解（Annotation）**：支持用户自定义注解，用于描述配置文件的格式和元数据（如 `file`, `level`, `format` 等）。
- **继承（Inheritance）**：支持结构体继承其他结构体或块，块继承其他块。继承时会忽略父级注解。
- **字段类型**：支持 `int32`, `int64`, `string`, `bool`, `float32`, `bytes` 等基础类型，`map`, `enum`, `repeated` 等复合类型。
- **注释**：支持行注释和块注释，仅块注释内容会保存并用于代码生成或文档生成。
- **支持多种格式**：可以输出为不同格式的配置文件（如 CBOR、INI、JSON 等）。
- **模块化**：支持文件的 `include` 和 `namespace` 机制，便于文件拆分与组织。

## 语法示例

### 定义结构体和字段

```mota
@[file = "camera_config.cbor", level = global, format = cbor]
struct CameraConfig {
    int32 cam1Position = 0;
    optional int32 cam1RefPosition = 0;
    repeated string params;
    map<string, Task> tasks = ["task1", "task2"];
}
```

### 定义枚举类型

```mota
enum CameraType {
    DSLR = 0;
    Mirrorless;
    PointAndShoot;
}
```

### 定义继承

```mota
@[file = "camera_model.cbor", level = product, format = json]
struct AdvancedCamera : struct Camera {
    int32 isoRange;
    int32 maxShutterSpeed;
}

@[file = "camera_basic.cbor", level = product, format = cbor]
block BasicCamera : block CameraIn {
    bool hasLensCap;
}
```

### 定义包含其他文件（`include`）

```mota
include "camera_settings.mota";
```

### 定义命名空间（`namespace`）

```mota
namespace myapp.config;
```

详细的语法规则请见： [Mota 语法](docs/mota-script-syntax.md)

## 项目结构

```
/mota
├── README.md            # 项目的介绍文档
├── src/                 # 源代码文件夹
│   ├── lexer.cpp        # 词法分析器实现
│   ├── parser.cpp       # 语法分析器实现
│   ├── ast.cpp          # 抽象语法树实现
│   ├── generator.cpp    # 代码生成器（计划）
│   └── main.cpp         # 主程序，运行解析器和生成器
├── include/             # 头文件
│   ├── lexer.h          # 词法分析器头文件
│   ├── parser.h         # 语法分析器头文件
│   ├── ast.h            # 抽象语法树头文件
│   └── generator.h      # 代码生成器头文件
├── test/                # 测试文件夹
│   ├── test_parser.cpp  # 语法分析器单元测试
│   ├── test_lexer.cpp   # 词法分析器单元测试
│   └── test_generator.cpp # 代码生成器单元测试（计划）
├── xmake.lua            # xmake 构建脚本
└── examples/            # 示例文件夹
    └── example.mota     # 示例 Mota 配置文件
```

## 编译和使用

### 依赖项

- C++20 或更高版本的编译器
- xmake 2.9.0 或更高版本

### 克隆项目并构建

```bash
# 克隆项目
git clone git@gitlab.bj-yima.com:inspector/architecture/mota.git
cd mota

# 使用 XMake 配置构建
xmake


# 运行解析器
xmake run mota examples/example.mota

# 使用配置文件批量运行
xmake run mota -c examples/config.yaml
```

### 单元测试

项目包含了单元测试，使用 xmake 构建时自动运行。你可以通过以下命令手动运行测试：

```bash
# 运行测试
xmake test
```

### 示例

项目中包含了 `examples/` 文件夹，其中有一个简单的 `example.mota` 文件，展示了如何使用 Mota 语言定义配置文件。你可以在 `test/` 文件夹中找到相关的单元测试代码。

## 贡献

欢迎为本项目贡献代码或提出建议！以下是贡献的流程：

1. Fork 本仓库。
2. 创建新的功能分支 (`git checkout -b feature-branch`)。
3. 提交修改 (`git commit -am 'Add new feature'`)。
4. 推送到分支 (`git push origin feature-branch`)。
5. 提交 pull request。

## 联系方式

如果你有任何问题或建议，可以通过以下方式联系我们：

- 电子邮件：eachcan@qq.com
