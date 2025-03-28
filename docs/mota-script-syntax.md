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

### 1.3 类文件保存路径

当前文件中的所有的 struct 生成的 CPP 或其他语言的代码文件的输出目录

```mota
dir = "src/";
```

### 1.4 二进制文件存储路径

对于 bytes 类型的字段，可以存储为二进制文件，但需要全局指定文件存放路径。文件名会自动生成，文件名会作为相应字段的值，无法手动指定（仅可指定前缀）。

```mota
bindir = "${app_dir}/config/bindb/";
```

### 1.5 文件结构

```mota
include "./options.mota";

namespace a.b.c;

dir = "src/";

bindir = "${app_dir}/config/bindb/";

enum MyType {
    @enumValue(value = "a")
    A = 0;
    @enumValue(value = "b")
    B = 1;
    @enumValue(value = "c")
    C = 2;
}

block MyBlock {
    @int(min = 0, max = 10000)
    int32 id = 0;
    @text(max_length = 64)
    string name = "";
}

@storage(
    path = "${app_dir}/config/options.cbor",
    format = "cbor"
)
@window(title = "我的配置", desc = "这是一个示例配置")
@scope(value = "global")
struct MyStruct {
    // 自定义类型
    @select()
    MyType type = A;

    // 自定义结构
    @iniGroup(value = "MY_BLOCK")
    MyBlock block;
}

## 2. 数据类型

### 2.1 基本数据类型

基本数据类型可修改字段：

- `int8`: 8位整数
- `int16`: 16位整数
- `int32`: 32位整数
- `int64`: 64位整数
- `float32`: 32位浮点数
- `double64`: 64位浮点数
- `string`: 字符串
- `bool`: 布尔值
- `bytes`: 字节数组

### 2.2 枚举类型 (enum)

枚举类型可以包含元数据注解，为每个枚举值添加额外信息。枚举值支持显式指定数值，未指定时会从0开始自增：

```mota
enum CameraType {
    @enumValue(title = "普通相机", desc = "基础的相机类型", value = "normal")
    Normal = 0;  // 显式指定值为 0
    @enumValue(title = "高速相机", desc = "高速拍摄的相机", value = "high-speed")
    HighSpeed = 1;  // 显式指定值为 1
    @enumValue(title = "高清相机", desc = "高清成像的相机", value = "hd")
    HD;  // 自动取值为 2
}
```

枚举值支持以下形式的数值：
- 十进制整数：`123`
- 十六进制整数：`0xFF`
- 二进制整数：`0b1010`
- 八进制整数：`0777`

### 2.3 块类型 (block)

块类型用于定义可重用的数据结构，支持继承：

```mota
block BaseTask {
    int32 taskId = 0;
    string name;
}

// 从 BaseTask 继承
block CameraTask : BaseTask {
    int32 position = 0;
    optional int32 refPosition;
}
```

特点：
- 支持基本数据类型（如 int32）
- 支持可选字段（optional）
- 可以设置默认值
- 支持单继承，且只能继承自其他 block

### 2.4 结构体类型 (struct)

结构体可以通过注解指定序列化相关的配置，也支持继承，但仅能从 block 继承，也不支持多继承：

```mota
block Device {
    int32 id;
    string name;
}

// 从 Device 继承
@storage(
    path = "${app_dir}/device-base.cbor",
    format = "cbor"
)
@window(title = "相机配置", desc = "相机配置")
@scope(value = "product")
struct CameraDevice : Device {
    @int(min = 0, max = 10000)
    int32 resolution = 1920;
    @float(min = 0.0, max = 100.0)
    float32 exposureTime = 1.0;
}
```

特点：
- 支持变量插值（如 ${app_dir}）
- 可以指定序列化格式和配置
- 支持单继承，可以继承自 block

### 2.5 Map 类型

可以在结构体中定义 map 类型的字段：

```mota
struct TaskConfigs {
    map Task tasks = ["task1", "task2"];
}
```

## 3. 字段修饰符
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

## 4. 注解系统

### 4.1 结构体注解

结构体注解可以用于为结构体添加元数据信息：

```mota
@storage(
    path = "${app_dir}/device-base.cbor",
    format = "cbor"
)
@window(title = "相机配置", desc = "相机配置")
@scope(value = "product")
struct CameraDevice : Device {
    @int(min = 0, max = 10000)
    int32 resolution = 1920;
    @float(min = 0.0, max = 100.0)
    float32 exposureTime = 1.0;
}
```

### 4.2 字段注解

字段注解可以用于为字段添加元数据信息：

```mota
struct Example {
    @int(min = 0, max = 10000)
    int32 id;
    
    @int(min = 0, max = 10000)
    int32 name;
    
    @int(min = 0, max = 10000)
    int32 resolution = 1920;
}
```

## 5. 注释系统
Mota 支持两种注释方式：

1. 行注释：使用 `//`
```mota
// 这是一个行注释
```

2. 块注释：使用 `/* */`
```mota
/* 这是一个
   多行块注释 */
```

3. UI 注释： 使用 `//@`
```mota
//@ 这是一个 UI 注释，可以显示在 UI 界面上
```

## 6. 默认值

枚举类型支持为枚举值指定默认值：

```mota
enum MyEnum {
    A = 0;
    B = 1;
    C = 2;
}
```

结构体和块类型支持为字段指定默认值：

```mota
struct Example {
    int32 id = 0;
    string name = "default";
}
```

map 类型支持默认键名，指定了默认键名则本 map 一定会包含这个键：

```mota
map TaskConfig configs = ["default"];
```

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

### 4.4 继承使用
- 使用继承减少代码重复
- 避免深度继承
- 使用继承实现代码复用
