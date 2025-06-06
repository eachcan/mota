# MOTA 模板制作指南

本文档详细介绍如何为 MOTA 代码生成器创建和维护模板，实现从 MOTA 语言定义到目标语言代码的自动生成。

## 目录

1. [模板系统概述](#模板系统概述)
2. [配置文件详解](#配置文件详解)
3. [模板语法](#模板语法)
4. [模板文件类型](#模板文件类型)
5. [模板变量系统](#模板变量系统)
6. [模板函数](#模板函数)
7. [字段类型处理](#字段类型处理)
8. [创建新模板](#创建新模板)
9. [最佳实践](#最佳实践)
10. [调试与测试](#调试与测试)

## 模板系统概述

MOTA 代码生成器采用完全基于配置的模板系统，所有代码生成逻辑都通过模板文件和配置文件定义，确保：

- **零硬编码**：所有生成规则都在配置和模板中定义
- **高度可配置**：类型映射、命名规则、输出格式都可配置
- **易于扩展**：添加新语言支持只需创建新的模板集
- **类型安全**：正确处理类型后缀和接口映射

### 模板集结构

每个目标语言对应一个模板集，存放在 `template/{language}/` 目录下：

```
template/
└── yima-cpp/                    # C++ 模板集
    ├── generator_config.json5   # 配置文件
    ├── header.template          # 头文件模板
    ├── block.template           # 块类模板
    ├── struct.template          # 结构体模板
    ├── enum.template            # 枚举模板
    ├── annotation.template      # 注解模板
    ├── field_types.template     # 字段类型处理模板
    ├── accessor.template        # 访问器模板
    ├── serialize.template       # 序列化模板
    ├── deserialize.template     # 反序列化模板
    └── README.md               # 说明文档
```

## 配置文件详解

`generator_config.json5` 是模板集的核心配置文件，控制整个代码生成过程。

### 基本信息

```json5
{
  "version": "1.0",
  "encoding": "UTF-8 with BOM",  // 输出文件编码
}
```

### 模板文件映射

```json5
{
  "templates": {
    "header": "header.template",
    "block": "block.template",
    "struct": "struct.template",
    "enum": "enum.template",
    "annotation": "annotation.template",
    "field_types": "field_types.template",
    "accessor": "accessor.template",
    "serialize": "serialize.template",
    "deserialize": "deserialize.template"
  }
}
```

### 类型映射

定义 MOTA 基础类型到目标语言类型的映射：

```json5
{
  "type_mapping": {
    "int8": "int8_t",
    "int16": "int16_t",
    "int32": "int32_t",
    "int64": "int64_t",
    "uint8": "uint8_t",
    "uint16": "uint16_t", 
    "uint32": "uint32_t",
    "uint64": "uint64_t",
    "float32": "float",
    "float64": "double",
    "string": "QString",
    "bool": "bool",
    "bytes": "QByteArray"
  }
}
```

### 访问器格式

控制getter/setter的命名规则：

```json5
{
  "accessor_format": {
    "getter_prefix": "get",     // getter前缀
    "setter_prefix": "set",     // setter前缀
    "pascal_case": true         // 是否使用PascalCase
  }
}
```

### 标识符格式

控制类名、字段名等的命名规则：

```json5
{
  "identifier_format": {
    "style": "pascal_case",     // 命名风格
    "prefix": {},               // 前缀规则
    "suffix": {                 // 后缀规则
      "block": "Block",
      "struct": "",
      "enum": "Enum", 
      "annotation": "Annotation"
    }
  }
}
```

### 字段类型模板映射

将字段类型映射到对应的模板片段：

```json5
{
  "field_type_templates": {
    "int8": "INT",
    "int16": "INT",
    "string": "STRING", 
    "bool": "BOOL",
    "repeated": "ARRAY",        // 数组类型
    "custom": "COMPLEX"         // 复合类型
  }
}
```

### 模板变量定义

定义可在模板中使用的动态变量：

```json5
{
  "template_variables": {
    "CLASS_NAME": "{{TYPE_NAME}}{{TYPE_SUFFIX}}",
    "PRIVATE_FIELD_NAME": "{{FIELD_NAME}}_",
    "FIELD_NAME_PASCAL": "{{FIELD_NAME | pascal_case}}",
    "FIELD_TYPE_MAPPED": "{{FIELD_TYPE | map_type}}",
    "SERIALIZE_TEMPLATE": "{{FIELD_TYPE | field_template}}_SERIALIZE"
  }
}
```

### 类型接口映射

定义类型到接口的映射关系：

```json5
{
  "type_interface_mapping": {
    "block": "IBlock",
    "struct": "IModel",
    "annotation": "IAnnotation"
  }
}
```

## 模板语法

模板使用双花括号 `{{}}` 语法进行变量替换和函数调用。

### 基本变量替换

```cpp
class {{CLASS_NAME}} : public {{INTERFACE_NAME}} {
    // 生成: class UserBlock : public IBlock {
```

### 条件渲染

```cpp
{{#HAS_FIELDS}}
private:
    {{#FIELDS}}
    {{FIELD_TYPE}} {{PRIVATE_FIELD_NAME}};
    {{/FIELDS}}
{{/HAS_FIELDS}}
```

### 循环渲染

```cpp
{{#FIELDS}}
    {{FIELD_TYPE}} get{{FIELD_NAME_PASCAL}}() const { return {{PRIVATE_FIELD_NAME}}; }
    void set{{FIELD_NAME_PASCAL}}(const {{FIELD_TYPE}}& value) { {{PRIVATE_FIELD_NAME}} = value; }
{{/FIELDS}}
```

### 模板函数调用

```cpp
{{FIELD_NAME | pascal_case}}     // 转换为PascalCase
{{FIELD_TYPE | map_type}}        // 类型映射
{{FIELD_TYPE | field_template}}  // 获取字段模板
```

## 模板文件类型

### 1. 头文件模板 (header.template)

定义生成文件的头部内容：

```cpp
#pragma once

#include <QtCore/QString>
#include <QtCore/QList>
#include <QtCBor/QCborMap>
#include <QtCBor/QCborValue>

{{#CUSTOM_INCLUDES}}
#include "{{.}}"
{{/CUSTOM_INCLUDES}}

{{#NAMESPACE}}
namespace {{.}} {
{{/NAMESPACE}}
```

### 2. 类型模板 (block.template, struct.template, etc.)

定义具体类型的生成模板：

```cpp
class {{CLASS_NAME}} : public {{INTERFACE_NAME}} {
public:
    {{CLASS_NAME}}() = default;
    virtual ~{{CLASS_NAME}}() = default;

{{#HAS_FIELDS}}
    // 访问器方法
{{#FIELDS}}
    {{>accessor}}
{{/FIELDS}}

    // 序列化方法
    QCborValue toCbor() const override {
        QCborMap map;
{{#FIELDS}}
        {{>SERIALIZE_TEMPLATE}}
{{/FIELDS}}
        return map;
    }

    // 反序列化方法
    void fromCbor(const QCborValue& value) override {
        QCborMap map = value.toMap();
{{#FIELDS}}
        {{>DESERIALIZE_TEMPLATE}}
{{/FIELDS}}
    }

private:
{{#FIELDS}}
    {{FIELD_TYPE}} {{PRIVATE_FIELD_NAME}};
{{/FIELDS}}
{{/HAS_FIELDS}}
};
```

### 3. 字段类型处理模板 (field_types.template)

定义不同字段类型的处理逻辑：

```cpp
{{#INT_SERIALIZE}}
map.insert(QLatin1String("{{FIELD_NAME}}"), {{PRIVATE_FIELD_NAME}});
{{/INT_SERIALIZE}}

{{#INT_DESERIALIZE}}
{{PRIVATE_FIELD_NAME}} = map.value(QLatin1String("{{FIELD_NAME}}")).toInteger();
{{/INT_DESERIALIZE}}

{{#STRING_SERIALIZE}}
map.insert(QLatin1String("{{FIELD_NAME}}"), {{PRIVATE_FIELD_NAME}});
{{/STRING_SERIALIZE}}

{{#STRING_DESERIALIZE}}
{{PRIVATE_FIELD_NAME}} = map.value(QLatin1String("{{FIELD_NAME}}")).toString();
{{/STRING_DESERIALIZE}}

{{#COMPLEX_SERIALIZE}}
map.insert(QLatin1String("{{FIELD_NAME}}"), {{PRIVATE_FIELD_NAME}}.toCbor());
{{/COMPLEX_SERIALIZE}}

{{#COMPLEX_DESERIALIZE}}
{
    {{FIELD_TYPE}} temp;
    temp.fromCbor(map.value(QLatin1String("{{FIELD_NAME}}")));
    set{{FIELD_NAME_PASCAL}}(temp);
}
{{/COMPLEX_DESERIALIZE}}

{{#ARRAY_SERIALIZE}}
{
    QCborArray array;
    for (const auto& item : {{PRIVATE_FIELD_NAME}}) {
        {{#IS_BASIC_ARRAY}}
        array.append(item);
        {{/IS_BASIC_ARRAY}}
        {{#IS_COMPLEX_ARRAY}}
        array.append(item.toCbor());
        {{/IS_COMPLEX_ARRAY}}
    }
    map.insert(QLatin1String("{{FIELD_NAME}}"), array);
}
{{/ARRAY_SERIALIZE}}

{{#ARRAY_DESERIALIZE}}
{
    QCborArray array = map.value(QLatin1String("{{FIELD_NAME}}")).toArray();
    {{ARRAY_ELEMENT_TYPE}} list;
    for (const auto& item : array) {
        {{#IS_BASIC_ARRAY}}
        list.append(item.{{CONVERT_METHOD}}());
        {{/IS_BASIC_ARRAY}}
        {{#IS_COMPLEX_ARRAY}}
        {{ELEMENT_TYPE}} element;
        element.fromCbor(item);
        list.append(element);
        {{/IS_COMPLEX_ARRAY}}
    }
    set{{FIELD_NAME_PASCAL}}(list);
}
{{/ARRAY_DESERIALIZE}}
```

### 4. 访问器模板 (accessor.template)

定义访问器方法的生成模板：

```cpp
{{FIELD_TYPE}} get{{FIELD_NAME_PASCAL}}() const { return {{PRIVATE_FIELD_NAME}}; }
void set{{FIELD_NAME_PASCAL}}(const {{FIELD_TYPE}}& value) { {{PRIVATE_FIELD_NAME}} = value; }
```

## 模板变量系统

模板变量分为以下几类：

### 1. 内置变量

由生成器自动提供的变量：

- `TYPE_NAME`: 类型名称 (如 "User")
- `TYPE_SUFFIX`: 类型后缀 (如 "Block")
- `INTERFACE_NAME`: 接口名称 (如 "IBlock")
- `FIELD_NAME`: 字段名称
- `FIELD_TYPE`: 字段类型
- `NAMESPACE`: 命名空间

### 2. 配置变量

在 `template_variables` 中定义的变量：

```json5
{
  "template_variables": {
    "CLASS_NAME": "{{TYPE_NAME}}{{TYPE_SUFFIX}}",
    "PRIVATE_FIELD_NAME": "{{FIELD_NAME}}_",
    "FIELD_NAME_PASCAL": "{{FIELD_NAME | pascal_case}}"
  }
}
```

### 3. 条件变量

用于条件渲染的布尔变量：

- `HAS_FIELDS`: 是否有字段
- `IS_REPEATED`: 是否为数组类型
- `IS_BASIC_TYPE`: 是否为基础类型
- `IS_COMPLEX_TYPE`: 是否为复合类型

## 模板函数

模板函数用于对变量进行转换处理：

### 可用函数

1. **pascal_case**: 转换为PascalCase
   ```
   {{FIELD_NAME | pascal_case}}  // userName -> UserName
   ```

2. **camel_case**: 转换为camelCase
   ```
   {{FIELD_NAME | camel_case}}   // user_name -> userName
   ```

3. **map_type**: 进行类型映射
   ```
   {{FIELD_TYPE | map_type}}     // int32 -> int32_t
   ```

4. **field_template**: 获取字段模板标识
   ```
   {{FIELD_TYPE | field_template}}  // string -> STRING
   ```

### 扩展函数

可以在生成器中添加新的模板函数：

```cpp
// 在 applyTemplateFunction 中添加
if (function == "upper_case") {
    return value.toUpper();
} else if (function == "lower_case") {
    return value.toLower();
}
```

## 字段类型处理

字段类型处理是模板系统的核心功能，需要正确处理：

### 基础类型

直接使用类型映射：

```json5
{
  "type_mapping": {
    "int32": "int32_t",
    "string": "QString"
  }
}
```

### 复合类型

使用类型后缀：

```cpp
// User block -> UserBlock
{{FIELD_TYPE}}Block {{PRIVATE_FIELD_NAME}};
```

### 数组类型

需要区分基础类型数组和复合类型数组：

```cpp
// 基础类型数组
QList<int32_t> numbers_;

// 复合类型数组  
QList<UserBlock> users_;
```

### 序列化处理

不同类型有不同的序列化方式：

```cpp
// 基础类型
map.insert(QLatin1String("field"), value);

// 复合类型
map.insert(QLatin1String("field"), value.toCbor());

// 数组类型
QCborArray array;
for (const auto& item : list) {
    array.append(item.toCbor());  // 或直接 append(item)
}
map.insert(QLatin1String("field"), array);
```

## 创建新模板

### 1. 创建模板集目录

```bash
mkdir template/new-language
cd template/new-language
```

### 2. 创建配置文件

复制现有配置文件并修改：

```bash
cp ../yima-cpp/generator_config.json5 .
```

修改类型映射、命名规则等：

```json5
{
  "type_mapping": {
    "int32": "int",      // 修改为目标语言类型
    "string": "string"
  },
  "accessor_format": {
    "getter_prefix": "",  // 修改为目标语言风格
    "setter_prefix": "set",
    "pascal_case": false
  }
}
```

### 3. 创建模板文件

为每种类型创建对应的模板：

```bash
touch header.template
touch class.template
touch field_types.template
# ... 其他模板
```

### 4. 实现模板内容

根据目标语言特性编写模板：

```cpp
// 例如：Java 类模板
public class {{CLASS_NAME}} implements {{INTERFACE_NAME}} {
    {{#FIELDS}}
    private {{FIELD_TYPE}} {{FIELD_NAME}};
    {{/FIELDS}}
    
    {{#FIELDS}}
    public {{FIELD_TYPE}} get{{FIELD_NAME_PASCAL}}() {
        return {{FIELD_NAME}};
    }
    
    public void set{{FIELD_NAME_PASCAL}}({{FIELD_TYPE}} value) {
        this.{{FIELD_NAME}} = value;
    }
    {{/FIELDS}}
}
```

### 5. 测试验证

创建测试用例验证模板：

```bash
# 创建测试MOTA文件
echo 'block TestUser { string name; int32 age; }' > test.mota

# 运行生成器
mota-compiler --template new-language test.mota
```

## 最佳实践

### 1. 模板组织

- **保持模板简洁**: 每个模板专注单一职责
- **使用部分模板**: 将公共代码抽取为部分模板
- **合理命名**: 模板文件名要清晰表达用途

### 2. 配置管理

- **完整性**: 确保所有必要的类型映射都已定义
- **一致性**: 命名规则要在整个模板集中保持一致
- **可扩展性**: 预留扩展空间，便于后续添加新特性

### 3. 类型处理

- **正确映射**: 确保MOTA类型到目标语言类型的映射正确
- **后缀处理**: 正确处理类型后缀，避免类型引用错误
- **数组支持**: 正确区分基础类型数组和复合类型数组

### 4. 代码质量

- **格式化**: 生成的代码要符合目标语言的格式规范
- **注释**: 适当添加生成说明注释
- **错误处理**: 在模板中添加必要的错误检查

### 5. 文档维护

- **及时更新**: 模板修改后要同步更新文档
- **示例丰富**: 提供充分的使用示例
- **版本管理**: 记录模板变更历史

## 调试与测试

### 1. 模板语法检查

```bash
# 检查模板语法
mota-compiler --check-template template/new-language
```

### 2. 生成测试

创建完整的测试用例：

```mota
// test_all_types.mota
namespace test;

enum UserRole {
    ADMIN = 1,
    USER = 2,
    GUEST = 3
}

block User {
    string name;
    int32 age;
    UserRole role;
    repeated string tags;
}

struct Profile {
    User user;
    string bio;
    repeated User friends;
}

annotation Validator {
    string pattern;
    int32 maxLength;
}
```

### 3. 输出验证

检查生成的代码：

- **语法正确性**: 能否编译通过
- **功能完整性**: 是否包含所有必要的方法
- **类型安全性**: 类型引用是否正确
- **序列化正确性**: 序列化/反序列化是否正常工作

### 4. 性能测试

对于大型MOTA文件进行性能测试：

```bash
# 生成大型测试文件
mota-generate-test --types 100 --fields 20 > large_test.mota

# 测试生成性能
time mota-compiler --template new-language large_test.mota
```

### 5. 回归测试

建立回归测试套件：

```bash
#!/bin/bash
# test_regression.sh

for template in template/*/; do
    echo "Testing $template..."
    mota-compiler --template "$template" test/regression.mota
    if [ $? -ne 0 ]; then
        echo "FAILED: $template"
        exit 1
    fi
done
echo "All tests passed!"
```

## 结语

MOTA模板系统提供了强大而灵活的代码生成能力。通过合理的配置和精心设计的模板，可以实现从MOTA定义到任何目标语言的自动化代码生成。

在开发新模板时，请始终遵循配置驱动的原则，避免硬编码，确保生成的代码质量和一致性。同时，完善的测试和文档是维护模板系统的重要保障。

如有疑问或需要帮助，请参考现有的`yima-cpp`模板集作为参考实现，或联系项目维护者。 