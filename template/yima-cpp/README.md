# Yima C++ 代码生成器模板

这个目录包含用于从 Mota 语言定义生成 C++ 代码的模板文件。模板遵循 Mota 项目规范，生成的代码符合项目的编码风格和 Qt CBOR API 使用规范。

## 模板文件说明

- `header.template`: 头文件模板，包含必要的包含文件和命名空间定义
- `block.template`: 块类模板，用于生成继承自 `IBlock` 的类
- `struct.template`: 结构体模板，用于生成继承自 `IModel` 的类
- `enum.template`: 枚举模板，用于生成枚举类型及其辅助函数
- `field_types.template`: 字段类型处理模板，包含不同类型字段的序列化和反序列化代码片段
- `generator_config.json`: 生成器配置文件，定义类型映射、输出设置和访问器格式等

## 生成规则

1. 所有生成的类都使用 `getX()`/`setX()` 格式的访问器
2. 序列化时使用 `map.insert(QLatin1String("fieldName"), value)` 方法
3. 反序列化时使用 `map.value(QLatin1String("fieldName"))` 方法
4. 复合类型字段序列化时调用其 `toCbor()` 方法
5. 复合类型字段反序列化时先创建临时对象，调用其 `fromCbor()` 方法，再通过访问器设置
6. 生成的文件编码为 UTF-8 with BOM

## 使用方法

1. 将 Mota 语言定义文件（如 `yima-blocks.mota`）作为输入
2. 使用生成器工具读取模板和 Mota 定义，生成对应的 C++ 代码
3. 生成的代码将保存到配置文件中指定的输出目录

## 示例

从 `yima-blocks.mota` 定义：

```
block Rectangle {
    int16 x;
    int16 y;
    int16 width;
    int16 height;
}
```

生成的 C++ 代码将包含 `getX()`/`setX()` 等访问器，以及正确实现的 `toCbor()` 和 `fromCbor()` 方法。
