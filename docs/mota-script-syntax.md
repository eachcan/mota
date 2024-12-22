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

枚举类型可以包含元数据注解，为每个枚举值添加额外信息。枚举值支持显式指定数值，未指定时会从0开始自增：

```mota
enum CameraType {
    @[ title = "普通相机", desc = "基础的相机类型" ]
    Normal = 0;  // 显式指定值为 0
    @[ title = "高速相机" ]
    HighSpeed = 1;  // 显式指定值为 1
    @[ title = "高清相机" ]
    HD;  // 自动取值为 2
}
```

枚举值支持以下形式的数值：
- 十进制整数：`123`
- 十六进制整数：`0xFF`
- 二进制整数：`0b1010`
- 八进制整数：`0777`

### 2.2 块类型 (block)

块类型用于定义可重用的数据结构，支持继承：

```mota
block BaseTask {
    int32 taskId = 0;
    string name;
}

// 从 BaseTask 继承
block CameraTask : BaseTask {
    int32 position = 0;
    @[ title = "参考位置", desc = "用于校准的参考点位置" ]
    optional int32 refPosition;
}
```

特点：
- 支持基本数据类型（如 int32）
- 支持可选字段（optional）
- 可以设置默认值
- 支持单继承，且只能继承自其他 block

### 2.3 结构体类型 (struct)

结构体可以通过注解指定序列化相关的配置，也支持继承：

```mota
@[ 
    file = "${app_path}/device-base.cbor",
    level = "global",
    format = "cbor"
]
struct Device {
    int32 id;
    string name;
}

// 从 Device 继承
struct CameraDevice : Device {
    @[ title = "分辨率", desc = "相机分辨率，单位为像素" ]
    int32 resolution = 1920;
    float exposureTime = 1.0;
}
```

特点：
- 支持文件级注解
- 支持变量插值（如 ${app_path}）
- 可以指定序列化格式和配置
- 支持单继承，可以继承自 struct 或 block

### 2.4 字段注解

字段注解可以用于为字段添加元数据信息：

```mota
struct Example {
    @[ title = "设备ID", desc = "唯一标识设备的ID" ]
    int32 id;
    
    @[ title = "设备名称", 
       desc = "设备的显示名称",
       max_length = 32 ]
    string name;
    
    @[ title = "分辨率",
       desc = "相机分辨率，单位为像素",
       min = 640,
       max = 3840 ]
    int32 resolution = 1920;
}
```

字段注解支持的属性：
- `title`: 字段标题
- `desc`: 字段描述
- `max_length`: 字符串最大长度
- `min`: 数值最小值
- `max`: 数值最大值
- `pattern`: 字符串匹配模式（正则表达式）
- `unit`: 数值单位
- `format`: 特殊格式（如日期、时间等）

### 2.5 Map 类型

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

注解可以用于：
- 枚举类型和枚举值
- 结构体和块类型
- 字段
- 继承关系

### 3.4 继承规则

Mota 支持单继承，遵循以下规则：

1. block 类型：
   - 只能继承自其他 block
   - 语法：`block Child : Parent`

2. struct 类型：
   - 可以继承自 struct 或 block
   - 语法：`struct Child : Parent`

3. 继承特性：
   - 子类继承父类的所有字段
   - 子类可以添加新字段
   - 子类可以为继承的字段指定新的默认值
   - 子类不能改变继承字段的类型

### 3.5 注释系统
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

### 3.6 默认值

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

### 3.7 枚举值的显式指定

枚举值支持显式指定数值：

```mota
enum CameraType {
    Normal = 0;
    HighSpeed = 1;
    HD = 2;
}
```

枚举值支持以下形式的数值：
- 十进制整数：`123`
- 十六进制整数：`0xFF`
- 二进制整数：`0b1010`
- 八进制整数：`0777`

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
