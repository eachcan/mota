# Mota 语法文档

## 1. 基本概念

### 1.1 文件引入

使用 `include` 语句引入其他 Mota 文件：

```mota
include "task.mota";
```

### 1.2 命名空间

使用 `namespace` 定义命名空间，可以使用点号进行层级划分：

```mota
namespace a.b.c;
```

## 2. 数据类型定义

### 2.1 枚举类型 (enum)

枚举类型可以包含元数据注解，为每个枚举值添加额外信息：

```mota
enum MyEnum {
    @[ title = "策略A", desc = "这是一个简单的策略" ]
    A;
    @[ title = "策略B" ]
    B;
    @[ title = "策略C" ]
    C;
}
```

### 2.2 块类型 (block)

块类型用于定义可重用的数据结构：

```mota
block Task {
    int32 cam1Position = 0;
    optional int32 cam1RefPosition = 0;
}
```

特点：
- 支持基本数据类型（如 int32）
- 支持可选字段（optional）
- 可以设置默认值

### 2.3 结构体类型 (struct)

结构体可以通过注解指定序列化相关的配置：

```mota
@[ 
    file = "${app_path}/${qualifier}-camera.cbor",
    level = global,
    format = cbor 
]
struct Camera {
    int32 cam1Position;
    optional int32 cam1RefPosition;
}
```

特点：
- 支持文件级注解
- 支持变量插值（如 ${app_path}）
- 可以指定序列化格式和配置

### 2.4 Map 类型

可以在结构体中定义 map 类型的字段：

```mota
struct TaskConfigs {
    map Task tasks = ["task1", "task2"];
}
```

## 3. 数据类型特性

### 3.1 基本数据类型
- `int8`: 8位整数
- `int16`: 16位整数
- `int32`: 32位整数
- `int64`: 64位整数
- `float32`: 32位浮点数
- `double64`: 64位浮点数
- `string`: 字符串
- `bool`: 布尔值
- `bytes`: 字节数组

### 3.2 字段修饰符
- `optional`: 可选字段，表示该字段可以不存在
- `map`: 键值对类型，键类型固定为 string
- `repeated`: 数组类型，表示该字段是一个数组

示例：
```mota
struct Example {
    int32 normalField = 0;
    optional string optionalField;
    repeated int64 arrayField;
    map TaskConfig configs = ["default"];
}
```

### 3.3 注解系统
注解使用 `@[ ]` 语法，可以包含：
- title：标题
- desc：描述
- file：文件路径
- level：级别（如 global）
- format：序列化格式（如 cbor）

注解可以用于 `enum`、`struct`、`block` 等数据类型， 也可用于字段上，用于描述数据的格式和元数据信息。例如：

```mota
enum MyEnum {
    A;
    B;
    C;
    @[ title = "策略A", desc = "这是一个简单的策略" ]
    A;
    @[ title = "策略B" ]
    B;
    @[ title = "策略C" ]
    C;
}

@[ 
    file = "${app_path}/${qualifier}-camera.cbor",
    level = global,
    format = cbor 
]
struct Camera {
    int32 cam1Position;
    @[ title = "相机1参考位置" ]
    optional int32 cam1RefPosition;
}
```

### 3.4 注释系统
Mota 支持两种注释方式：行注释和块注释。

#### 行注释
使用 `//` 开始的行注释在编译时会被丢弃：
```mota
// 这是一个行注释，编译时会被丢弃
struct MyStruct {
    int32 value;  // 这个注释也会被丢弃
}
```

#### 块注释
使用 `/* */` 的块注释会作为字段或类型的注释信息被保留：
```mota
/* 这个注释会作为 MyStruct 的注释被保留 */
struct MyStruct {
    /* 这个注释会作为 value 字段的注释被保留 */
    int32 value;
    
    /* 第一个注释会被丢弃 */
    /* 只有这个注释会被保留，因为它最接近字段 */
    int64 count;
}
```

注意：当存在多个连续的块注释时，只会保留最接近注释对象（字段或类型）的那个注释。

### 3.5 默认值
- 基本类型可以指定默认值
- Map 类型可以指定初始键值对

## 4. 最佳实践

### 4.1 文件组织
- 使用 include 引入依赖的文件
- 使用命名空间避免名称冲突
- 合理组织代码结构

### 4.2 类型选择
- 使用 enum 定义枚举常量
- 使用 block 定义可重用数据结构
- 使用 struct 定义需要序列化的配置
- 使用 map 定义键值对集合

### 4.3 注解使用
- 为枚举值添加描述性注解
- 为结构体指定序列化配置
- 使用变量插值使配置更灵活
