# Mota 语法

## 1. 文件结构

### 1.1 引用其他文件

`include` 语句用于包含其他 `.mota` 文件，这样可以在当前文件中使用其他文件中定义的类型。

```mota
include "path/to/file.mota";
```

- `include` 可以引用相对路径或绝对路径。
- 每个文件只会被解析一次，防止重复解析。

### 1.2 命名空间

命名空间 `namespace` 用于组织和隔离不同文件中定义的类型和结构，避免命名冲突。

```mota
namespace a.b.c;
```

- 命名空间可以是任意合法的标识符，用 `.` 来分隔不同层次的命名空间。

## 2. 数据类型

Mota 支持多种数据类型，包括基本类型、枚举类型、结构体类型、块类型等。

### 2.1 基本类型

以下是支持的基本数据类型：

- `int32`：32位整数类型。
- `int64`：64位整数类型。
- `bool`：布尔类型（`true` 或 `false`）。
- `string`：字符串类型。
- `float32`：32位浮点数类型。
- `float64`：64位浮点数类型。
- `bytes`：字节数组类型。

#### 示例：

```mota
int32 field1;
int64 field2;
bool isActive;
string name;
float32 temperature;
bytes data;
```

### 2.2 修饰符

- `optional`：表示该字段为可选的。如果字段的值是默认值，则该字段不会被写入配置文件（例如 `.cbor` 文件）。如果字段没有值或者值是默认值，它将不会出现在生成的配置文件中，但在程序中可以保持为 `null` 或 `空`。
- `repeated`：表示该字段是一个数组，可以包含多个值。
- `map`：表示键值对类型。键为 `string` 类型，值为任何合法的数据类型。键值对的集合可以动态解析。

#### 示例：

```mota
optional int32 cam1RefPosition = 0;
repeated string params;
map Task tasks;
```

### 2.3 枚举类型

枚举（`enum`）是用来表示一组命名的常量。它支持指定枚举项的值，如果没有显式指定值，则会自动递增。

```mota
enum MyEnum {
    A = 0;
    B;
    C;
}
```

- `A` 显式指定了值为 `0`，`B` 和 `C` 将分别自动分配为 `1` 和 `2`。

### 2.4 字段类型

字段可以是以下类型：
- 基本数据类型（`int32`, `bool`, `string`, `float32`, `bytes` 等）。
- 继承自 `block` 的类型。

#### 注意：
- `struct` 类型不能作为其他字段的类型。
- `block` 类型可以作为其他字段的类型。

## 3. 数据结构

### 3.1 `block` 类型定义

`block` 用于定义结构较为简单的顶层数据块，它可以包含字段，字段的类型可以是基本类型或继承自 `block` 的类型。`block` 无法包含注解，且只能继承其他 `block`。

```mota
block Task {
    int32 cam1Position;
    optional int32 cam1RefPosition;
}
```

- `Task` 是一个 `block` 类型，包含两个字段：`cam1Position` 和 `cam1RefPosition`。
- `block` 类型不能继承 `struct` 类型。

### 3.2 `struct` 类型定义

`struct` 用于定义复杂的数据结构，可以包含字段，字段的类型可以是基本类型或其他 `block` 类型。`struct` 类型支持注解，并且可以继承其他 `struct` 类型或 `block` 类型。

```mota
@[ 
    file = "${app_path}/camera.cbor",
    level = global,
    format = cbor 
]
struct Camera {
    int32 cam1Position;
    optional int32 cam1RefPosition;
}
```

- `Camera` 是一个 `struct` 类型，包含两个字段：`cam1Position` 和 `cam1RefPosition`。
- `struct` 类型可以使用注解（如 `@[ ... ]`），而 `block` 类型不能。

### 3.3 `struct` 继承

`struct` 可以继承其他 `struct` 或 `block` 类型。继承时，子类型会继承父类型的字段，但不会继承父类型的注解。

```mota
@[ 
    file = "${app_path}/camera-basler.cbor",
    level = product,
    format = cbor 
]
struct BaslerCamera : struct Camera {
    int32 additionalCameraField;
}
```

- `BaslerCamera` 继承自 `Camera`，并扩展了一个新的字段：`additionalCameraField`。
- `BaslerCamera` 会继承 `Camera` 的所有字段，但不会继承 `Camera` 的注解（如 `@[ ... ]`）。

### 3.4 `block` 继承

`block` 只能继承其他 `block` 类型，不能继承 `struct` 类型。

```mota
block CameraIn {
    string camName;
    int32 camId;
}

block BaslerCameraIn : block CameraIn {
    int32 additionalInputField;
}
```

- `BaslerCameraIn` 继承自 `CameraIn`，并扩展了一个新的字段：`additionalInputField`。

### 3.5 继承注意事项

- `struct` 可以继承其他 `struct` 或 `block`，`block` 只能继承其他 `block`。
- 继承时，子类型会继承父类型的字段，但注解（`@[ ... ]`）不会被继承。
- 每个结构体或块类型都需要单独定义注解。

## 4. 注解

注解用于在结构体或块类型上定义额外的元数据，例如文件路径、级别、格式等。注解只适用于 `struct` 类型，`block` 类型不能有注解。

### 4.1 注解语法

注解使用 `@[ ... ]` 的格式，在结构体或块类型定义之前声明。

```mota
@[ 
    file = "${app_path}/camera.cbor",
    level = global,
    format = cbor 
]
struct Camera {
    int32 cam1Position;
    optional int32 cam1RefPosition;
}
```

- `file`：定义生成的配置文件路径。
- `level`：定义配置文件的级别，可以是 `global` 或 `product`。
- `format`：定义配置文件的格式，支持的格式包括 `cbor`, `ini`, `registry`, `json`。

### 4.2 注解继承规则

- **继承时注解不被继承**：当一个 `struct` 继承自另一个 `struct` 时，子类型不会继承父类型的注解。
- 每个结构体或块类型都需要单独定义注解。

## 5. 字段定义规则

字段由类型、字段名、以及可选的默认值和修饰符组成。字段的类型可以是以下几种：

- 基本类型（`int32`, `int64`, `bool`, `string`, `float32`, `float64`, `bytes` 等）。
- 继承自 `block` 的类型（仅限 `block` 类型字段）。

### 5.1 字段语法

字段定义的语法格式如下：

```mota
<类型> <字段名> [= <默认值>];
```

- `optional`：表示字段是可选的，如果为默认值则不会存储。
- `repeated`：表示字段为数组类型。
- `map`：表示键值对类型，键为 `string` 类型。默认值是 key 的默认值，指的是这些 key 会始终存在。但值不一定存在

#### 示例：

```mota
int32 cam1Position = 0;
optional int32 cam1RefPosition = 0;
repeated string params;
map Task tasks = ["task1", "task2"];
```

## 6. 示例文件

```Mota
// 引入其他 Mota 文件
include "task.mota";

// 定义命名空间
namespace a.b.c;

// 定义枚举类型
enum MyEnum {
    A = 0;
    B;
    C;
}

// 定义 Block 类型
block Task {
    int32 cam1Position = 0;
    optional int32 cam1Ref

Position = 0;
}

// 定义 Struct 类型
@[ 
    file = "${app_path}/camera.cbor",
    level = global,
    format = cbor 
]
struct Camera {
    int32 cam1Position;
    optional int32 cam1RefPosition;
}

// 定义继承的 Struct 类型
@[ 
    file = "${app_path}/camera-basler.cbor",
    level = product,
    format = cbor 
]
struct BaslerCamera : struct Camera {
    int32 additionalCameraField;
}

// 定义继承的 Block 类型
block CameraIn {
    string camName;
    int32 camId;
}

@[ 
    file = "${app_path}/camera-in-basler.cbor",
    level = global,
    format = json 
]
block BaslerCameraIn : block CameraIn {
    int32 additionalInputField;
}
```
