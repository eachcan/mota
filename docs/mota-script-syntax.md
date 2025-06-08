# Mota 语法文档

Mota 是一个配置文件编译器，类似于 [Protocol Buffers](https://github.com/protocolbuffers/protobuf)，但主要用于配置文件描述类的编译。

Mota 的配置文件使用 `.mota` 为扩展名。

## 1. 指令

指令包括：

- include: 包含其他 Mota 文件
- namespace: 定义命名空间

示例：

```mota
include "task.mota";
namespace a.b.c;
```

### include
`include` 指令用于包含其他 Mota 文件，搜索路径为：

- 包含 Mota 文件所在的目录
- 运行 mota 的当前目录
- mota-config.json 中定义的 include_paths
- 运行 mota 时的命令行参数: `--include-path`
- mota 安装目录下的 `mota-include` 目录

> **注意：** 使用 mota-include 目录时，需要将 mota-include-cpp 目录下的文件复制到 C++ 的搜索目录下，否则 C++ 无法找到 mota-include-cpp 目录下的头文件。
> 其他通过 include-path 指定的包含目录，也需要将对应的生成的文件复制到 C++ 的搜索目录下。

## 2. 数据类型

Mota 的字段支持以下数据类型：

- int8: 8位整数
- int16: 16位整数
- int32: 32位整数
- int64: 64位整数
- uint8: 8位无符号整数
- uint16: 16位无符号整数
- uint32: 32位无符号整数
- uint64: 64位无符号整数
- float32: 32位浮点数
- float64: 64位浮点数
- string: 字符串
- bool: 布尔值
- bytes: 字节数组

示例：

```mota
int32 id = 0;
string name = "";
bool enabled = true;
bytes data = "";
```

### 2.1 默认值

字段可以设置默认值，默认值必须是该字段类型的有效值，示例：

```mota
int32 id = 0;
string name = "";
bool enabled = true;
bytes data = "";
```

## 3. 注解

### 3.1 注解的定义

你可以使用以下结构定义一个注解：

```mota
annotation MyAnnotation {
    int32 id;
    string name;
}
```

如果注解的字段类型可以使用其他注解：

```mota
annotation MyAnnotation {
    int32 id;
    string name;
}

annotation MyAnnotation2 {
    MyAnnotation myAnnotation;
}
```

但注解和字段均不能由注解来修饰。

在使用了 `namespace` 的情况下，注解的名称需要加上 `namespace`，示例：

```mota
// a.mota
namespace a;

annotation MyAnnotation {
    int32 id;
    string name;
}
```

```mota
// b.mota
include "a.mota";
namespace b;

annotation MyAnnotation2 {
    a.MyAnnotation myAnnotation;
}
```

### 3.2 注解的使用

你可以使用以下方式使用注解：

```mota
@MyAnnotation(id = 1, name = "test")
int32 id = 0;
```

你也可以使用注解来修饰结构体：

```mota
@MyAnnotation(id = 1, name = "test")
struct MyStruct {
    int32 id = 0;
    string name = "";
}
```

在有 `namespace` 的情况下，注解的名称需要加上 `namespace`，示例：

```mota
@a.MyAnnotation(id = 1, name = "test")
int32 id = 0;
```

### 3.3 注解的 value 参数

注解有且仅有一个 value 参数时，可以省略参数名，示例：

```mota
annotation MyAnnotation {
    @value
    int32 id;
}
```

使用时可以省略参数名：

```mota
@MyAnnotation(1)
int32 id = 0;
```

### 3.4 无参数注解

如果注解没有参数，可以省略括号，示例：

```mota
annotation MyAnnotation;
```

使用时可以省略括号：

```mota
@MyAnnotation
int32 id = 0;
```

### 3.5 注解参数的数组语法

注解参数支持数组字面量语法，可以传递多个值：

```mota
annotation ModeOption {
    string text;
    string value;
}

annotation ModeSelector {
    ModeOption default;
    repeated ModeOption options;
}

@ModeSelector(
    default = @ModeOption(text = "正常模式", value = "normal"),
    options = [
        @ModeOption(text = "正常模式", value = "normal"),
        @ModeOption(text = "调试模式", value = "debug"),
        @ModeOption(text = "测试模式", value = "test")
    ]
)
struct RunMode {
    string mode;
}
```

数组字面量语法：
- 使用方括号 `[]` 包围数组元素
- 元素之间用逗号 `,` 分隔
- 支持空数组 `[]`
- 支持嵌套数组 `[[1, 2], [3, 4]]`
- 数组元素可以是字面量、表达式或注解

### 3.6 注解的继承

注解可以继承自其他注解，示例：

```mota
annotation MyAnnotation : BaseAnnotation {
    int32 id;
}

annotation BaseAnnotation {
    string name;
}
```

注解的继承仅支持单继承，且只能继承自其他注解。

## 4. 枚举

你可以使用以下方式定义一个枚举：

```mota
enum MyEnum {
    A = 0;
    B = 1;
    C = 2;
}
```

枚举值可以使用注解：

```mota
enum MyEnum {
    @enumValue(value = "a")
    A = 0;
    @enumValue(value = "b")
    B = 1;
    @enumValue(value = "c")
    C = 2;
}
```

枚举可作为字段类型使用，示例：

```mota
enum MyEnum {
    A = 0;
    B = 1;
    C = 2;
}

struct MyStruct {
    MyEnum myEnum = A;
}
```

> **注意：枚举（enum）不支持继承。**

## 5. 块

你可以使用以下方式定义一个块：

```mota
block MyBlock {
    int32 id = 0;
    string name = "";
}
```

### 5.1 块的注解

块可以使用注解：

```mota
@BlockValue(value = "my_block")
block MyBlock {
    @Int(min = 0, max = 10000)
    int32 id = 0;
    @Text(max_length = 64)
    string name = "";
}
```

### 5.2 块作为字段类型

块可作为字段类型使用，示例：

```mota
block MyBlock {
    int32 id = 0;
    string name = "";
}

struct MyStruct {
    MyBlock myBlock;
}
```

块作为字段类型时不允许有默认值。

### 5.3 块的继承

块可以继承自其他块，示例：

```mota
block BaseBlock {
    int32 id = 0;
    string name = "";
}

block MyBlock : BaseBlock {
    int32 position = 0;
    optional int32 refPosition;
}
```

块的继承仅支持单继承，且只能继承自其他 block。

## 6. 结构体

你可以使用以下方式定义一个结构体：

```mota
struct MyStruct {
    int32 id = 0;
    string name = "";
}
```

结构体不能作为字段类型。

### 6.1 结构体的注解

结构体可以使用注解：

```mota
@Storage(
    path = "${app_dir}/config/options.cbor",
    format = "cbor"
)
@Window(title = "我的配置", desc = "这是一个示例配置")
@Scope(value = "global")
struct MyStruct {
    @Int(min = 0, max = 10000)
    int32 id = 0;
    @Text(max_length = 64)
    string name = "";
}
```

### 6.2 结构体的继承

结构体不能继承自其他结构体。但可以继承自 block。

```mota
block BaseBlock {
    int32 id = 0;
    string name = "";
}

struct MyStruct : BaseBlock {
    int32 position = 0;
    optional int32 refPosition;
}
```

## 7. 字段修饰符

### 7.1 optional

可选字段，表示该字段可以不存在，值允许为 null。

```mota
optional int32 id = 0;
```

### 7.2 map

map 类型的字段，键类型固定为 string，值类型为该字段的类型。

```mota
map TaskConfig configs;
```

### 7.3 repeated

repeated 修饰的字段，表示该字段是一个数组，每一项值的类型均为该字段的类型。

```mota
repeated int64 arrayField;
```

repeated 字段支持数组字面量作为默认值：

```mota
repeated int32 numbers = [1, 2, 3, 4, 5];
repeated string names = ["Alice", "Bob", "Charlie"];
repeated MyBlock blocks = [
    @MyBlock(id = 1, name = "first"),
    @MyBlock(id = 2, name = "second")
];
```

## 8. 注释

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

3. UI 注释：使用 `//@`
```mota
//@ 这是一个 UI 注释，可以显示在 UI 界面上，也可以显示到文本型配置文件中
```

## 9. 变量插值

Mota 并不能理解变量插件，变量插值由代码解析，编译器将原样作为字符串保留。

你可以使用 `${...}` 语法：

```mota
string path = "${app_dir}/config/options.cbor";
```

## 10. 命名

相同命名空间下，注解、枚举、结构体、块的名称不能重复。