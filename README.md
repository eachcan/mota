# MOTA - Modern Object Type Architecture

MOTA是一个现代化的数据结构定义语言和代码生成器，旨在简化跨语言数据模型的开发和维护。

## 特性

- **简洁的语法**: 类似于Protocol Buffers但更加简洁直观
- **强类型系统**: 支持基础类型、自定义类型、枚举、数组等
- **多语言支持**: 通过模板系统支持生成多种目标语言
- **注解系统**: 丰富的注解支持，用于验证、文档生成等
- **代码生成**: 自动生成包含序列化、反序列化、访问器等完整功能的代码
- **零硬编码**: 完全基于配置的代码生成，易于扩展和自定义

## 快速开始

### 安装

使用xmake构建系统：

```bash
# 克隆项目
git clone https://github.com/your-repo/mota.git
cd mota

# 构建
xmake

# 运行测试
xmake run test_generator
```

### 基本使用

1. **创建MOTA文件** (`user.mota`)：

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
    repeated User friends;
}
```

2. **生成代码**：

```bash
mota user.mota -o output/ -l cpp
```

3. **使用生成的代码**：

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

## 语法指南

### 基础类型

- **整数**: `int8`, `int16`, `int32`, `int64`
- **无符号整数**: `uint8`, `uint16`, `uint32`, `uint64` 
- **浮点数**: `float32`, `float64`
- **其他**: `string`, `bool`, `bytes`

### 自定义类型

#### 结构体 (Struct)
用于数据传输对象：

```mota
struct Point {
    float32 x;
    float32 y;
}
```

#### 块 (Block) 
用于业务实体：

```mota
block User {
    string name;
    int32 age;
    Point location;
}
```

#### 枚举 (Enum)
```mota
enum Status {
    PENDING = 0,
    APPROVED = 1,
    REJECTED = 2
}
```

### 数组
使用 `repeated` 关键字：

```mota
struct Container {
    repeated string items;
    repeated Point coordinates;
}
```

### 注解系统

```mota
annotation Validator {
    string pattern;
    int32 maxLength;
}

struct User {
    @Validator(pattern: "^[a-zA-Z0-9]+$", maxLength: 50)
    string username;
}
```

### 包含文件

```mota
include "common/types.mota";

struct MyType {
    CommonType field;
}
```

## 模板系统

MOTA使用先进的模板系统生成目标语言代码，支持高度自定义和扩展。

### 新模板语法

使用现代化的模板语法：

```template
<%=variable%>                    # 输出变量
<%=function(parameter)%>         # 调用函数
<%if (condition)%>               # 条件语句
    ...
<%elseif (other_condition)%>
    ...
<%else%>
    ...
<%endif%>
<%foreach item in items%>        # 循环语句
    ...
<%endforeach%>
<%for (key, value) in map%>      # Map遍历
    ...
<%endfor%>
```

### 片段系统

通过片段(Misc)系统实现模板模块化：

```template
<%misc getter_method%>           # 定义片段
    <%=FIELD_TYPE%> get<%=pascal_case(FIELD_NAME)%>() const {
        return <%=FIELD_NAME%>_;
    }
<%endmisc%>

<%call getter_method%>           # 调用片段
```

### 配置简化

新版本模板配置更加简洁，专注于核心设置：

```json5
{
  "version": "2.0",
  "templates": {
    "file": "file.template",
    "block_decl": "block_decl.template",
    "struct_decl": "struct_decl.template",
    "enum_decl": "enum_decl.template",
    "annotation_decl": "annotation_decl.template",
    "annotation": "annotation.template"
  },
  "miscs": ["misc.template"],
  "type_mapping": {
    "int32": "int32_t",
    "string": "QString"
  }
}
```

### 格式化通过片段实现

不再需要复杂的格式化配置，全部通过misc片段实现：

- 类型后缀 → `type_suffix` 片段
- 访问器格式 → `getter_prefix`、`setter_prefix` 片段  
- 继承格式 → `inheritance_declaration` 片段
- 接口映射 → `interface_name` 片段

### 创建自定义模板

1. **创建模板集目录**：
```bash
mkdir template/my-language
```

2. **编写配置文件** (`config.json5`)：
```json5
{
  "version": "2.0",
  "templates": { /* 必需的模板映射 */ },
  "miscs": ["misc.template"],
  "type_mapping": { /* 类型映射 */ }
}
```

3. **定义片段** (`misc.template`)：
```template
<%misc class_name%><%=TYPE_NAME%><%call type_suffix%><%endmisc%>
<%misc type_suffix%>
<%if (TYPE == "struct")%>Model<%endif%>
<%if (TYPE == "block")%>Block<%endif%>
<%endmisc%>
```

4. **创建模板文件**：
- `file.template` - 文件结构
- `block_decl.template` - Block声明
- `struct_decl.template` - Struct声明
- `enum_decl.template` - Enum声明
- `annotation_decl.template` - Annotation声明  
- `annotation.template` - 注解实例

### 模板优势

- **零硬编码**: 所有生成逻辑通过配置和模板定义
- **高度模块化**: 片段系统提高代码复用
- **易于维护**: 配置简洁，逻辑清晰
- **灵活扩展**: 创建新语言支持只需新建模板集

详细的模板开发指南请参考：[模板开发指南](docs/template-development-guide.md)

## 命令行工具

### 基本语法
```bash
mota [OPTIONS] [FILE] [...]
```

### 主要选项
- `-h, --help`: 显示帮助信息
- `-V, --version`: 显示版本信息  
- `-v, --verbose`: 显示详细信息
- `-i, --include-path PATH`: 添加包含路径
- `-o, --output-dir PATH`: 设置输出目录 (默认: output)
- `-s, --source-dir PATH`: 设置源文件目录 (默认: 当前目录)
- `-l, --lang LANG`: 设置输出语言 (默认: cpp)
- `-c, --config PATH`: 设置配置文件路径

### 使用示例

```bash
# 编译单个文件
mota user.mota -o generated/

# 编译整个目录
mota src/ -o generated/ -l cpp

# 使用自定义模板
mota user.mota -l my-template

# 添加包含路径
mota user.mota -i common/ -i shared/
```

## 生成的代码特性

### C++ 代码特性

- **完整的CBOR序列化/反序列化支持**
- **类型安全的访问器方法**
- **注解系统支持**
- **反射能力** (字段枚举、类型查询等)
- **Qt框架集成**
- **现代C++特性使用**

### 示例生成代码

```cpp
class MODEL_EXPORT UserModel : public IModel {
public:
    UserModel() = default;
    
    // 访问器
    QString getName() const { return name_; }
    void setName(const QString& value) { name_ = value; }
    
    int32_t getAge() const { return age_; }
    void setAge(int32_t value) { age_ = value; }
    
    // 序列化
    QCborValue toCbor() const override;
    void fromCbor(const QCborValue& cbor) override;
    
    // 反射
    QStringList fields() const override;
    QString fieldType(const QString& fieldName) const override;
    QVariant value(const QString& fieldName) const override;
    
private:
    QString name_;
    int32_t age_;
};
```

## 项目结构

```
mota/
├── src/                    # 源代码
│   ├── generator/         # 代码生成器
│   ├── parser/           # 语法解析器
│   ├── ast/              # 抽象语法树
│   └── main.cpp          # 入口点
├── template/             # 模板集合
│   └── yima-cpp/        # C++模板
│       ├── config.json5 # 配置文件
│       ├── misc.template # 片段定义
│       └── *.template   # 模板文件
├── test/                # 测试文件
├── docs/               # 文档
└── examples/           # 示例
```

## 开发

### 构建系统

项目使用xmake作为构建系统：

```bash
# 配置项目
xmake f -c debug

# 构建
xmake build

# 运行测试
xmake run test_generator

# 清理
xmake clean
```

### 添加新语言支持

1. 在 `template/` 下创建新的模板集目录
2. 按照模板开发指南创建必需的模板文件
3. 定义类型映射和生成规则
4. 通过misc片段实现格式化逻辑
5. 测试验证生成的代码

### 贡献指南

我们欢迎各种形式的贡献：

- **Bug报告**: 通过Issues报告问题
- **功能请求**: 提出新功能建议  
- **代码贡献**: 提交Pull Request
- **文档改进**: 完善文档和示例
- **模板贡献**: 为新语言创建模板

请遵循项目的编码规范和开发流程。

## 许可证

本项目采用 [MIT许可证](LICENSE)。

## 相关资源

- [语法参考](docs/syntax-reference.md)
- [模板开发指南](docs/template-development-guide.md)
- [API文档](docs/api-reference.md)
- [示例项目](examples/)

## 支持

如需帮助或有疑问，请：

- 查看[文档](docs/)和[示例](examples/)
- 在[Issues](https://github.com/your-repo/mota/issues)中搜索或提出问题
- 参与[讨论区](https://github.com/your-repo/mota/discussions)讨论

---

MOTA - 让数据模型定义更简单，让代码生成更智能。

