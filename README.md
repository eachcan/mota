# MOTA - Modern Object Type Architecture

MOTA是一个现代化的数据结构定义语言和代码生成器，旨在简化跨语言数据模型的开发和维护。

## 什么是MOTA？

MOTA提供了一种简洁的语法来定义数据结构，然后自动生成多种编程语言的代码。它类似于Protocol Buffers，但语法更加直观，扩展性更强。

**核心概念：**
- **Struct（结构体）**: 用于数据传输对象
- **Block（块）**: 用于业务实体，包含完整的CRUD功能
- **Enum（枚举）**: 定义常量集合
- **Annotation（注解）**: 为类型添加元数据和验证规则

## 快速开始

### 1. 安装

```bash
# 克隆项目
git clone https://github.com/your-repo/mota.git
cd mota

# 构建（需要xmake）
xmake
```

### 2. 创建第一个MOTA文件

创建 `user.mota`：

```mota
namespace com.example;

enum UserRole {
    ADMIN = 1,
    USER = 2,
    GUEST = 3
}

struct User {
    string name;
    int32 age;
    UserRole role;
    repeated string tags;
}

block UserProfile {
    User user;
    string bio;
}
```

### 3. 生成代码

```bash
# 生成C++代码
./bin/mota.exe user.mota -o output/ -l yima-cpp

# 生成JSON（用于测试）
./bin/mota.exe user.mota -o output/ -l test
```

### 4. 使用生成的代码

```cpp
#include "com/example/user.h"

// 创建用户
UserModel user;
user.setName("张三");
user.setAge(25);
user.setRole(UserRole::USER);

// 序列化
QCborValue cbor = user.toCbor();

// 反序列化
UserModel user2;
user2.fromCbor(cbor);
```

## 工作原理

MOTA采用三层架构：

1. **语法解析器**: 将`.mota`文件解析为抽象语法树(AST)
2. **模板引擎**: 使用模板系统将AST转换为目标语言代码
3. **代码生成器**: 输出完整的、可直接使用的代码文件

```
.mota文件 → 语法解析 → AST → 模板渲染 → 目标语言代码
```

## 如何新增一种生成语言

MOTA使用基于模板的代码生成系统，添加新语言支持只需要创建相应的模板文件：

### 1. 创建模板目录

```
template/
└── your-lang/
    ├── config.json          # 语言配置
    ├── struct.template      # 结构体模板
    ├── block.template       # 块模板
    ├── enum.template        # 枚举模板
    ├── annotation.template  # 注解模板
    └── misc.template        # 通用代码片段
```

### 2. 配置语言参数

在 `config.json` 中定义：

```json
{
    "version": "2.0",
    "encoding": "utf-8",
    "templates": {
        "struct": "struct.template",
        "block": "block.template",
        "enum": "enum.template",
        "annotation_decl": "annotation.template"
    },
    "miscs": "misc.template"
}
```

### 3. 编写模板文件

使用MOTA模板语法编写代码生成模板。详细信息请参考 [模板开发文档](docs/template/README.md)。

## 文档

### 使用者文档
- [命令行使用](docs/usage/command-line.md) - 命令行工具的详细使用方法
- [语法规则](docs/usage/syntax.md) - MOTA语言的完整语法说明
- [项目配置](docs/usage/config.md) - 项目配置文件的使用方法

### 扩展者文档
- [模板开发指南](docs/template/README.md) - 如何创建新的语言模板
- [模板变量和函数](docs/template/template-variables-and-functions.md) - 模板系统的变量结构和可用函数

## 示例

查看 `examples/` 目录获取完整的使用示例：
- `01_annotations.mota` - 注解系统示例
- `02_enums.mota` - 枚举定义示例
- `03_blocks.mota` - 块定义示例
- `04_structs.mota` - 结构体定义示例
- `05_cross_references.mota` - 跨文件引用示例

## 许可证

本项目采用 [MIT License](LICENSE) 开源许可证。

## 贡献

欢迎提交Issue和Pull Request来帮助改进MOTA！

---

**注意**: 本项目目前主要支持C++代码生成，其他语言支持正在开发中。

