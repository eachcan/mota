# MOTA 模板开发指南

本文档介绍如何为MOTA创建新的语言模板，包括模板语法、配置文件结构和开发最佳实践。

## 模板系统概述

MOTA使用基于模板的代码生成系统，支持为任何编程语言创建代码生成器。模板系统包含以下组件：

- **模板文件** - 定义代码生成的结构和格式
- **配置文件** - 指定模板映射和语言特定设置
- **Misc片段** - 可重用的代码片段，提高模板的模块化程度

## 模板组成

一个完整的语言模板包含以下文件：

```
template/
└── your-lang/
    ├── config.json          # 配置文件
    ├── file.template        # 文件结构模板
    ├── struct.template      # 结构体模板
    ├── block.template       # 块模板
    ├── enum.template        # 枚举模板
    ├── annotation.template  # 注解模板
    └── misc.template        # 通用代码片段
```

### 入口文件 (config.json)

配置文件定义了模板的基本信息和文件映射：

```json
{
    "version": "2.0",
    "encoding": "utf-8",
    "templates": {
        "file": "file.template",
        "struct": "struct.template",
        "block": "block.template",
        "enum": "enum.template",
        "annotation_decl": "annotation.template"
    },
    "miscs": "misc.template",
    "type_mapping": {
        "int32": "int",
        "string": "std::string",
        "bool": "bool"
    },
    "file_path": [
        {
            "path": "<%=namespace_path(NAMESPACE)%>/<%=snake_case(FILE_NAME)%>.h",
            "type": "file"
        }
    ],
    "include_directive": {
        "pattern": "#include \"<%=INCLUDE_PATH%>\"",
        "source_extension": ".mota",
        "target_extension": ".h"
    }
}
```

### 模板文件

每个模板文件负责生成特定类型的代码：

- **file.template** - 整个文件的结构（头部、包含、命名空间等）
- **struct.template** - 结构体定义
- **block.template** - 块定义（业务实体）
- **enum.template** - 枚举定义
- **annotation.template** - 注解定义

### Misc片段文件

Misc文件包含可重用的代码片段，用于：
- 类型转换和映射
- 代码格式化
- 通用代码生成逻辑
- 语法元素定义

## 模板语法

### 基本语法

MOTA使用类似EJS的模板语法：

#### 输出变量
```template
<%=VARIABLE_NAME%>
```

#### 函数调用
```template
<%=function_name(parameter1, parameter2)%>
```

**重要**：必须使用标准函数签名，不支持方法调用语法。

#### 条件语句
```template
<%if (condition)%>
    内容
<%elseif (other_condition)%>
    其他内容
<%else%>
    默认内容
<%endif%>
```

#### 循环语句
```template
<%foreach item in array%>
    <%=item.name%>
<%endforeach%>
```

#### 键值对遍历
```template
<%for (key, value) in map%>
    <%=key%>: <%=value%>
<%endfor%>
```

### Misc片段系统

片段系统是MOTA模板的核心特性，允许定义可重用的代码块。

#### 定义片段
```template
<%misc fragment_name%>
    模板内容
    可以使用变量：<%=VARIABLE%>
    可以调用其他片段：<%call other_fragment%>
<%endmisc%>
```

#### 调用片段
```template
<%call fragment_name%>
```

#### 片段特性
- 继承调用上下文的所有变量
- 支持嵌套调用
- 支持递归调用（需谨慎使用）

### 示例：C++模板片段

```template
<%misc class_name%><%=TYPE_NAME%><%call type_suffix%><%endmisc%>

<%misc type_suffix%>
<%if (TYPE == "struct")%>Model<%endif%>
<%if (TYPE == "block")%>Block<%endif%>
<%if (TYPE == "enum")%><%endif%>
<%endmisc%>

<%misc getter_method%>
    <%=map_type(FIELD_TYPE)%> get<%=pascal_case(FIELD_NAME)%>() const {
        return <%=FIELD_NAME%>_;
    }
<%endmisc%>

<%misc setter_method%>
    void set<%=pascal_case(FIELD_NAME)%>(const <%=map_type(FIELD_TYPE)%>& value) {
        <%=FIELD_NAME%>_ = value;
    }
<%endmisc%>

<%misc private_field%>
    <%=map_type(FIELD_TYPE)%> <%=FIELD_NAME%>_;
<%endmisc%>
```

## 配置文件详解

### 版本和编码

```json
{
    "version": "2.0",
    "encoding": "utf-8"
}
```

- `version`: 模板系统版本，当前为"2.0"
- `encoding`: 输出文件编码格式

### 模板映射

```json
{
    "templates": {
        "file": "file.template",
        "struct": "struct.template",
        "block": "block.template",
        "enum": "enum.template",
        "annotation_decl": "annotation.template"
    }
}
```

定义每种类型对应的模板文件。

### Misc片段

```json
{
    "miscs": "misc.template"
}
```

或者使用数组指定多个misc文件：

```json
{
    "miscs": [
        "misc.template",
        "helpers.template"
    ]
}
```

### 类型映射

```json
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
        "string": "std::string",
        "bool": "bool",
        "bytes": "std::vector<uint8_t>"
    }
}
```

定义MOTA基础类型到目标语言类型的映射。

### 文件路径规则

```json
{
    "file_path": [
        {
            "path": "<%=namespace_path(NAMESPACE)%>/<%=snake_case(FILE_NAME)%>.h",
            "type": "file"
        },
        {
            "path": "<%=namespace_path(NAMESPACE)%>/<%=snake_case(FILE_NAME)%>.cpp",
            "type": "file"
        }
    ]
}
```

定义生成文件的路径和命名规则。

### 包含指令

```json
{
    "include_directive": {
        "pattern": "#include \"<%=INCLUDE_PATH%>\"",
        "source_extension": ".mota",
        "target_extension": ".h"
    }
}
```

定义如何处理include指令。

## 必需的Misc片段

为了确保模板正常工作，必须在misc文件中定义以下片段：

### 语法元素片段

```template
<%misc private_field_suffix%>_<%endmisc%>
<%misc empty_variant%>QVariant()<%endmisc%>
<%misc repeated_keyword%>repeated<%endmisc%>
<%misc namespace_path_separator%>/<%endmisc%>
```

### 类型相关片段

```template
<%misc class_name%><%=TYPE_NAME%><%call type_suffix%><%endmisc%>

<%misc type_suffix%>
<%if (TYPE == "struct")%>Model<%endif%>
<%if (TYPE == "block")%>Block<%endif%>
<%endmisc%>

<%misc interface_name%>
<%if (TYPE == "struct")%>IModel<%endif%>
<%if (TYPE == "block")%>IBlock<%endif%>
<%endmisc%>
```

### 继承相关片段

```template
<%misc inheritance_declaration%>
<%if (PARENT_CLASS_NAME)%>public <%=PARENT_CLASS_NAME%>, <%endif%>public <%call interface_name%>
<%endmisc%>
```

### 字段相关片段

```template
<%misc field_name_variable%><%=FIELD_NAME%>_<%endmisc%>

<%misc getter_prefix%>get<%endmisc%>
<%misc setter_prefix%>set<%endmisc%>

<%misc field_type_template%>
<%if (FIELD_TYPE == "repeated")%>QList<<%=map_type(FIELD_ELEMENT_TYPE)%>><%else%><%=map_type(FIELD_TYPE)%><%endif%>
<%endmisc%>
```

## 创建新语言模板

### 步骤1：创建目录结构

```bash
mkdir template/my-lang
cd template/my-lang
```

### 步骤2：创建配置文件

创建 `config.json`：

```json
{
    "version": "2.0",
    "encoding": "utf-8",
    "templates": {
        "file": "file.template",
        "struct": "struct.template",
        "block": "block.template",
        "enum": "enum.template",
        "annotation_decl": "annotation.template"
    },
    "miscs": "misc.template",
    "type_mapping": {
        "int32": "int",
        "string": "string",
        "bool": "boolean"
    },
    "file_path": [
        {
            "path": "<%=namespace_path(NAMESPACE)%>/<%=FILE_NAME%>.ext",
            "type": "file"
        }
    ]
}
```

### 步骤3：创建模板文件

#### file.template
```template
// 文件头部注释
// Generated by MOTA at <%=CURRENT_TIME%>

<%if (INCLUDES.count > 0)%>
<%foreach include in INCLUDES.files%>
// Include: <%=include.path%>
<%endforeach%>

<%endif%>
<%if (NAMESPACE.exists)%>
namespace <%=NAMESPACE.path%> {

<%endif%>
<%foreach declaration in DECLARATIONS%>
<%if (declaration.type == "struct")%>
<%call struct_declaration%>
<%endif%>
<%if (declaration.type == "block")%>
<%call block_declaration%>
<%endif%>
<%if (declaration.type == "enum")%>
<%call enum_declaration%>
<%endif%>
<%endforeach%>
<%if (NAMESPACE.exists)%>

} // namespace <%=NAMESPACE.path%>
<%endif%>
```

#### struct.template
```template
struct <%call class_name%> {
<%foreach field in FIELDS%>
    <%=map_type(field.type)%> <%=field.name%>;
<%endforeach%>
};
```

#### misc.template
```template
<%misc class_name%><%=TYPE_NAME%><%endmisc%>

<%misc struct_declaration%>
struct <%call class_name%> {
<%foreach field in FIELDS%>
    <%=map_type(field.type)%> <%=field.name%>;
<%endforeach%>
};
<%endmisc%>

<%misc block_declaration%>
class <%call class_name%> {
<%foreach field in FIELDS%>
private:
    <%=map_type(field.type)%> <%=field.name%>_;
public:
    <%=map_type(field.type)%> get<%=pascal_case(field.name)%>() const { return <%=field.name%>_; }
    void set<%=pascal_case(field.name)%>(const <%=map_type(field.type)%>& value) { <%=field.name%>_ = value; }
<%endforeach%>
};
<%endmisc%>

<%misc enum_declaration%>
enum <%=TYPE_NAME%> {
<%foreach value in VALUES%>
    <%=value.name%> = <%=value.value%><%if (!value.is_last)%>,<%endif%>
<%endforeach%>
};
<%endmisc%>
```

### 步骤4：测试模板

```bash
# 测试生成
./bin/mota.exe examples/01_annotations.mota -l my-lang -o test_output/
```

## 可用函数

模板中可以使用以下内置函数：

### 字符串处理函数

- `pascal_case(string)` - 转换为PascalCase
- `camel_case(string)` - 转换为camelCase
- `snake_case(string)` - 转换为snake_case
- `upper_case(string)` - 转换为大写
- `lower_case(string)` - 转换为小写

### 数组处理函数

- `join(separator, array)` - 连接数组元素
- `length(array)` - 获取数组长度

### 类型处理函数

- `map_type(type)` - 映射类型到目标语言类型
- `is_repeated(type)` - 检查是否为数组类型
- `element_type(type)` - 获取数组元素类型

### 命名空间函数

- `namespace_path(namespace)` - 获取命名空间路径

## 最佳实践

### 1. 模块化设计

使用misc片段将复杂的逻辑分解为小的、可重用的片段：

```template
<%misc field_declaration%>
    <%call field_type%> <%call field_name%><%call field_default_value%>;
<%endmisc%>

<%misc field_type%><%=map_type(FIELD_TYPE)%><%endmisc%>
<%misc field_name%><%=FIELD_NAME%><%endmisc%>
<%misc field_default_value%><%if (FIELD_DEFAULT_VALUE)%> = <%=FIELD_DEFAULT_VALUE%><%endif%><%endmisc%>
```

### 2. 错误处理

在模板中添加适当的错误检查：

```template
<%if (!TYPE_NAME)%>
// Error: TYPE_NAME is not defined
<%else%>
class <%=TYPE_NAME%> {
    // 类定义
};
<%endif%>
```

### 3. 注释和文档

为生成的代码添加有用的注释：

```template
/**
 * Generated from <%=SOURCE_FILE%>
 * Type: <%=TYPE%>
 * Generated at: <%=CURRENT_TIME%>
 */
class <%call class_name%> {
    // 实现
};
```

### 4. 条件生成

根据不同条件生成不同的代码：

```template
<%if (TYPE == "struct")%>
// 结构体不需要访问器方法
<%else%>
// 为块生成访问器方法
<%foreach field in FIELDS%>
<%call getter_method%>
<%call setter_method%>
<%endforeach%>
<%endif%>
```

### 5. 类型安全

确保类型映射的完整性：

```template
<%misc safe_map_type%>
<%if (map_type(FIELD_TYPE))%>
<%=map_type(FIELD_TYPE)%>
<%else%>
// Warning: Unknown type <%=FIELD_TYPE%>
void*
<%endif%>
<%endmisc%>
```

## 调试模板

### 1. 使用详细输出

```bash
./bin/mota.exe test.mota -l your-lang -v
```

### 2. 生成JSON查看数据结构

```bash
./bin/mota.exe test.mota -l test -o debug/
```

### 3. 在模板中添加调试信息

```template
// Debug: TYPE=<%=TYPE%>, TYPE_NAME=<%=TYPE_NAME%>
// Debug: FIELDS count=<%=length(FIELDS)%>
<%foreach field in FIELDS%>
// Debug: Field <%=field.name%> type=<%=field.type%>
<%endforeach%>
```

## 常见问题

### 1. 模板变量未定义

确保在正确的上下文中使用变量。某些变量只在特定模板中可用。

### 2. 函数调用失败

检查函数签名是否正确，避免使用方法调用语法。

### 3. 片段递归调用

避免无限递归，在片段中添加适当的条件检查。

### 4. 类型映射缺失

确保在`type_mapping`中定义了所有需要的类型映射。

## 示例模板

完整的模板示例请参考：
- `template/yima-cpp/` - C++模板实现
- `template/test/` - JSON测试模板

这些示例展示了如何实现完整的语言模板，包括所有必需的片段和配置。 