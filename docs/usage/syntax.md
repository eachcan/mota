# MOTA 语法规则

本文档详细介绍MOTA语言的语法规则和使用方法。

## 概述

MOTA是一个数据结构定义语言，类似于Protocol Buffers，但语法更加简洁直观。MOTA文件使用`.mota`扩展名。

## 文件结构

一个典型的MOTA文件结构如下：

```mota
// 包含其他文件
include "common/types.mota";

// 定义命名空间
namespace com.example;

// 定义注解
annotation Validator {
    string pattern;
    int32 maxLength;
}

// 定义枚举
enum UserRole {
    ADMIN = 1,
    USER = 2,
    GUEST = 3
}

// 定义结构体
struct User {
    @Validator(pattern: "^[a-zA-Z0-9]+$", maxLength: 50)
    string name;
    int32 age;
    UserRole role;
}

// 定义块
block UserProfile {
    User user;
    string bio;
    repeated string tags;
}
```

## 指令

### include 指令

用于包含其他MOTA文件：

```mota
include "path/to/file.mota";
include "common/types.mota";
```

**搜索路径顺序：**
1. 当前MOTA文件所在目录
2. 运行mota命令的当前目录
3. 配置文件中定义的`include_paths`
4. 命令行参数`--include-path`指定的路径
5. mota安装目录下的`mota-include`目录

### namespace 指令

定义命名空间：

```mota
namespace com.example;
namespace a.b.c;
```

命名空间影响：
- 生成代码的目录结构
- 类型的完全限定名
- 跨文件引用时的类型名称

## 数据类型

### 基础类型

| 类型 | 说明 | 示例 |
|------|------|------|
| `int8` | 8位有符号整数 | `-128` 到 `127` |
| `int16` | 16位有符号整数 | `-32768` 到 `32767` |
| `int32` | 32位有符号整数 | `-2147483648` 到 `2147483647` |
| `int64` | 64位有符号整数 | 大范围整数 |
| `uint8` | 8位无符号整数 | `0` 到 `255` |
| `uint16` | 16位无符号整数 | `0` 到 `65535` |
| `uint32` | 32位无符号整数 | `0` 到 `4294967295` |
| `uint64` | 64位无符号整数 | 大范围无符号整数 |
| `float32` | 32位浮点数 | 单精度浮点数 |
| `float64` | 64位浮点数 | 双精度浮点数 |
| `string` | 字符串 | UTF-8编码字符串 |
| `bool` | 布尔值 | `true` 或 `false` |
| `bytes` | 字节数组 | 二进制数据 |

### 数组类型

使用`repeated`关键字定义数组：

```mota
struct Container {
    repeated string items;
    repeated int32 numbers;
    repeated User users;
}
```

### 自定义类型

可以使用其他定义的类型：

```mota
struct Address {
    string street;
    string city;
}

struct User {
    string name;
    Address address;  // 使用自定义类型
}
```

### 跨命名空间引用

引用其他命名空间的类型需要使用完全限定名：

```mota
// common/types.mota
namespace common;
enum Status {
    ACTIVE = 1,
    INACTIVE = 2
}

// user.mota
include "common/types.mota";
namespace app;

struct User {
    string name;
    common.Status status;  // 跨命名空间引用
}
```

## 默认值

字段可以设置默认值：

```mota
struct Config {
    int32 port = 8080;
    string host = "localhost";
    bool enabled = true;
    repeated string tags = [];
}
```

**默认值规则：**
- 数值类型：任何有效的数值
- 字符串类型：使用双引号包围
- 布尔类型：`true` 或 `false`
- 数组类型：使用 `[]` 表示空数组
- 自定义类型：不支持默认值

## 注解系统

### 定义注解

```mota
annotation Validator {
    string pattern;
    int32 maxLength;
    bool required = true;
}

annotation Description {
    string value;
}
```

**注解字段类型限制：**
- 可以使用基础类型
- 可以使用其他注解类型
- 不能使用enum、struct、block类型

### 使用注解

#### 修饰字段

```mota
struct User {
    @Validator(pattern: "^[a-zA-Z0-9]+$", maxLength: 50)
    string username;
    
    @Description("用户的年龄")
    int32 age;
}
```

#### 修饰类型

```mota
@Description("用户信息结构")
struct User {
    string name;
    int32 age;
}

@Description("用户角色枚举")
enum UserRole {
    ADMIN = 1,
    USER = 2
}
```

#### 简化语法

**单一value字段：**
```mota
annotation Description {
    string value;
}

// 可以省略参数名
@Description("这是描述")
struct User {
    string name;
}
```

**无参数注解：**
```mota
annotation Required;

// 可以省略括号
@Required
string name;
```

#### 数组参数

```mota
annotation Options {
    repeated string values;
}

@Options(values: ["option1", "option2", "option3"])
string mode;
```

#### 嵌套注解

```mota
annotation Option {
    string text;
    string value;
}

annotation Selector {
    Option default;
    repeated Option options;
}

@Selector(
    default: @Option(text: "默认", value: "default"),
    options: [
        @Option(text: "选项1", value: "option1"),
        @Option(text: "选项2", value: "option2")
    ]
)
string selection;
```

## 枚举 (Enum)

### 基本语法

```mota
enum Status {
    PENDING = 0,
    APPROVED = 1,
    REJECTED = 2
}
```

### 枚举特性

- 必须指定数值
- 数值可以不连续
- 支持负数
- 支持注解修饰

```mota
@Description("用户状态枚举")
enum UserStatus {
    @Description("未激活")
    INACTIVE = 0,
    
    @Description("已激活")
    ACTIVE = 1,
    
    @Description("已禁用")
    DISABLED = -1
}
```

## 结构体 (Struct)

结构体用于定义数据传输对象：

```mota
struct Point {
    float32 x = 0.0;
    float32 y = 0.0;
}

struct Rectangle {
    Point topLeft;
    Point bottomRight;
    string color = "black";
}
```

### 结构体特性

- 用于纯数据传输
- 支持字段默认值
- 支持注解修饰
- 可以包含其他结构体、枚举
- 不能包含注解类型字段

## 块 (Block)

块用于定义业务实体，包含完整的CRUD功能：

```mota
block User {
    string name;
    int32 age;
    repeated string tags;
}

block UserProfile {
    User user;
    string bio;
    repeated User friends;
}
```

### 块特性

- 用于业务实体建模
- 生成完整的访问器方法
- 支持序列化/反序列化
- 支持反射功能
- 可以继承其他块

### 块继承

```mota
block BaseEntity {
    int64 id;
    string createdAt;
}

block User : BaseEntity {
    string name;
    string email;
}
```

## 注释

支持单行和多行注释：

```mota
// 这是单行注释
struct User {
    string name;  // 字段注释
    
    /*
     * 这是多行注释
     * 可以跨越多行
     */
    int32 age;
}
```

## 语法规则总结

### 命名规则

- 类型名：使用PascalCase（如：`UserProfile`）
- 字段名：使用camelCase（如：`userName`）
- 枚举值：使用UPPER_CASE（如：`USER_ACTIVE`）
- 命名空间：使用小写，点分隔（如：`com.example`）

### 语句终结

- 字段声明必须以分号结尾
- 类型定义的大括号后不需要分号
- 指令（include、namespace）必须以分号结尾

### 类型使用限制

| 上下文 | 可用类型 |
|--------|----------|
| struct字段 | 基础类型、enum、其他struct、block |
| block字段 | 基础类型、enum、struct、其他block |
| enum值 | 仅整数字面量 |
| 注解字段 | 基础类型、其他注解 |

## 示例文件

完整的示例文件请参考项目的`examples/`目录：

- [`01_annotations.mota`](../../examples/01_annotations.mota) - 注解系统示例
- [`02_enums.mota`](../../examples/02_enums.mota) - 枚举定义示例
- [`03_blocks.mota`](../../examples/03_blocks.mota) - 块定义示例
- [`04_structs.mota`](../../examples/04_structs.mota) - 结构体定义示例
- [`05_cross_references.mota`](../../examples/05_cross_references.mota) - 跨文件引用示例

## 最佳实践

1. **文件组织**：按功能模块组织文件，使用清晰的目录结构
2. **命名空间**：使用有意义的命名空间，避免冲突
3. **注解使用**：合理使用注解添加元数据和验证规则
4. **类型选择**：
   - 数据传输使用struct
   - 业务实体使用block
   - 常量集合使用enum
5. **默认值**：为可选字段提供合理的默认值
6. **文档**：使用注释和注解为代码添加文档

## 错误处理

常见语法错误及解决方法：

1. **缺少分号**：字段声明后必须添加分号
2. **类型未定义**：确保引用的类型已定义或已包含
3. **循环引用**：避免文件间的循环包含
4. **命名空间错误**：跨命名空间引用时使用完全限定名
5. **注解参数错误**：确保注解参数类型和名称正确 