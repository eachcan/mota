# MOTA模板变量结构参考

本文档详细描述了MOTA模板系统中可用的所有变量结构，帮助模板开发者正确访问和使用这些变量。

## 概述

MOTA模板系统提供了一个结构化的变量树，包含了编译过程中解析出的所有信息。主要包括：
- 元数据信息（时间、源文件）
- 命名空间信息
- 包含文件信息  
- 声明信息（类、结构体、枚举、注解等）

## 根级变量 (TemplateVars)

```
TemplateVars (Root)
├── CURRENT_TIME: string
├── SOURCE_FILE: string
├── NAMESPACE
├── INCLUDES  
└── DECLARATIONS: Declaration[]
```

### CURRENT_TIME
- **类型**: `string`
- **描述**: 代码生成的当前时间
- **示例**: `"2025-06-10 23:41:33"`
- **用法**: `<%=CURRENT_TIME%>`

### SOURCE_FILE
- **类型**: `string`
- **描述**: 当前正在处理的源文件路径
- **示例**: `".\\examples\\simple.mota"`
- **用法**: `<%=SOURCE_FILE%>`

## NAMESPACE 对象

命名空间信息，包含完整的层次结构和便利访问方法。

```
NAMESPACE
├── exists: boolean
├── parts: NamespacePart[]
├── path: string
└── parts_count: int
```

### exists
- **类型**: `boolean`
- **描述**: 是否定义了命名空间
- **用法**: `<%if (NAMESPACE.exists)%>...<%endif%>`

### parts
- **类型**: `NamespacePart[]`
- **描述**: 命名空间的各个部分，支持多级命名空间
- **用法**: 
```template
<%foreach NAMESPACE.parts as part%>
    命名空间部分: <%=part.name%>
    索引: <%=part.index%>
    是否首个: <%=part.is_first%>
    是否最后: <%=part.is_last%>
<%endforeach%>
```

#### NamespacePart 结构
```
NamespacePart
├── name: string        // 部分名称，如 "com"
├── index: int          // 在parts数组中的索引
├── is_first: bool      // 是否是第一个部分
└── is_last: bool       // 是否是最后一个部分
```

### path
- **类型**: `string`
- **描述**: 完整的命名空间路径
- **示例**: `"com.example.project"`
- **用法**: `<%=NAMESPACE.path%>`

### parts_count
- **类型**: `int`
- **描述**: 命名空间部分的数量
- **用法**: `<%=NAMESPACE.parts_count%>`

## INCLUDES 对象

包含文件信息，管理依赖的其他MOTA文件。

```
INCLUDES
├── files: IncludeFile[]
└── count: int
```

### files
- **类型**: `IncludeFile[]`
- **描述**: 包含的文件列表
- **用法**:
```template
<%foreach INCLUDES.files as file%>
    源文件: <%=file.source%>
    目标文件: <%=file.translated%>
<%endforeach%>
```

#### IncludeFile 结构
```
IncludeFile
├── source: string      // 原始文件名，如 "yima.mota"
└── translated: string  // 转换后的文件名，如 "yima.h"
```

### count
- **类型**: `int`
- **描述**: 包含文件的数量
- **用法**: `<%=INCLUDES.count%>`

## DECLARATIONS 数组

声明信息是模板系统的核心，包含所有类型声明（注解、枚举、块、结构体）。

```
DECLARATIONS: Declaration[]
```

### Declaration 结构

每个声明都有以下通用属性：

```
Declaration
├── type: string                    // "annotation_decl" | "enum" | "block" | "struct"
├── name: string                    // 声明名称
├── class_name: string              // 类名（带后缀）
├── parent: string                  // 父类名称（可选）
├── parent_class_name: string       // 父类类名（可选）
├── annotations: Annotation[]       // 注解列表
├── fields?: Field[]                // 字段列表（Enum不适用）
└── values?: EnumValue[]            // 枚举值列表（仅Enum适用）
```

#### 基本属性

- **type**: 声明类型，决定了其他可用属性
  - `"annotation_decl"`: 注解声明
  - `"enum"`: 枚举类型  
  - `"block"`: 块类型
  - `"struct"`: 结构体类型

- **name**: 原始声明名称，如 `"Task"`
- **class_name**: 生成的类名，如 `"TaskModel"`
- **parent**: 父类原始名称（继承时）
- **parent_class_name**: 父类生成的类名（继承时）

#### 使用示例
```template
<%foreach DECLARATIONS as declaration%>
    <%if (declaration.type == "struct")%>
        生成结构体: <%=declaration.class_name%>
        <%if (declaration.parent)%>
            继承自: <%=declaration.parent_class_name%>
        <%endif%>
    <%endif%>
<%endforeach%>
```

### annotations 数组

每个声明可以有多个注解：

```
Annotation
├── name: string                    // 注解名称
├── class_name: string              // 注解类名
└── arguments: AnnotationArgument[] // 注解参数
```

#### 使用示例
```template
<%foreach declaration.annotations as annotation%>
    注解: <%=annotation.name%>
    <%foreach annotation.arguments as arg%>
        参数 <%=arg.name%>: <%=arg.value.value%>
    <%endforeach%>
<%endforeach%>
```

### fields 数组（Enum除外）

结构体、块、注解声明都有字段：

```
Field
├── name: string                    // 字段原始名称
├── field_name: string              // 字段变量名
├── container_type: string          // "none" | "array" | "map" | "optional"
├── type_name: string               // 类型名称
├── type_namespaces: string[]       // 类型命名空间
├── qualified_type_name: string     // 完全限定类型名
├── default_value?: ExprValue       // 默认值（可选）
├── default_values?: ExprValue[]    // 默认数组值（可选）
└── annotations: Annotation[]       // 字段注解
```

#### 使用示例
```template
<%foreach declaration.fields as field%>
    字段名: <%=field.name%>
    类型: <%=field.type_name%>
    <%if (field.container_type == "array")%>
        这是一个数组字段
    <%endif%>
    <%if (field.default_value)%>
        默认值: <%=field.default_value.value%>
    <%endif%>
<%endforeach%>
```

### values 数组（仅Enum）

枚举类型有值列表：

```
EnumValue  
├── name: string                    // 枚举值名称
├── field_name: string              // 枚举值变量名
├── value?: ExprValue               // 枚举值（可选）
└── annotations: Annotation[]       // 枚举值注解
```

#### 使用示例
```template
<%if (declaration.type == "enum")%>
    <%foreach declaration.values as value%>
        枚举值: <%=value.name%>
        <%if (value.value)%>
            = <%=value.value.value%>
        <%endif%>
    <%endforeach%>
<%endif%>
```

## AnnotationArgument 结构

注解参数包含完整的类型和值信息：

```
AnnotationArgument
├── name: string                    // 参数名称
├── field_name: string              // 参数字段名
├── container_type: string          // "none" | "array" | "map" | "optional"
├── type_name: string               // 类型名称
├── type_namespaces: string[]       // 类型命名空间
├── qualified_type_name: string     // 完全限定类型名
├── value?: ExprValue               // 单个值（可选）
├── values?: ExprValue[]            // 数组值（可选）
└── value_map?: KeyValuePair[]      // 映射值（可选）
```

### KeyValuePair 结构
```
KeyValuePair
├── key: string                     // 键
└── value: ExprValue                // 值
```

## ExprValue 联合类型

表达式值是一个联合类型，可以是字符串、数字、布尔值或注解：

```
ExprValue (联合类型)
├── StringValue
├── NumberValue  
├── BooleanValue
└── AnnotationValue
```

### StringValue
```
StringValue
├── type: "string"
└── value: string                   // 格式: '"' + addslashes(原值) + '"'
```

### NumberValue
```
NumberValue  
├── type: "number"
└── value: string                   // 数字转字符串
```

### BooleanValue
```
BooleanValue
├── type: "boolean" 
└── value: string                   // "true" 或 "false"
```

### AnnotationValue
```
AnnotationValue (仅注解中可用)
├── type: "annotation"
└── value: Annotation               // 递归引用Annotation结构
```

## 常用访问模式

### 1. 类型判断和处理
```template
<%foreach DECLARATIONS as declaration%>
    <%if (declaration.type == "struct")%>
        // 处理结构体
    <%endif%>
    <%if (declaration.type == "enum")%>
        // 处理枚举
    <%endif%>
    <%if (declaration.type == "block")%>
        // 处理块
    <%endif%>
    <%if (declaration.type == "annotation_decl")%>
        // 处理注解声明
    <%endif%>
<%endforeach%>
```

### 2. 字段类型映射
```template
<%foreach declaration.fields as field%>
    <%if (field.container_type == "array")%>
        QVector<<%=field.type_name%>>
    <%else%>
        <%=field.type_name%>
    <%endif%>
<%endforeach%>
```

### 3. 命名空间处理
```template
<%if (NAMESPACE.exists)%>
namespace <%=NAMESPACE.path%> {
    // 内容
}
<%endif%>
```

### 4. 包含文件处理  
```template
<%if (INCLUDES.count > 0)%>
    <%foreach INCLUDES.files as file%>
        #include "<%=file.translated%>"
    <%endforeach%>
<%endif%>
```

## 注意事项

1. **可选字段**: 标记为`?`的字段可能不存在，使用前需要检查
2. **类型安全**: 根据`declaration.type`来访问对应的字段（如`fields`或`values`）
3. **递归结构**: `Annotation`结构可以递归嵌套
4. **数组访问**: 使用`foreach`循环遍历所有数组类型的字段
5. **表达式值**: 通过`ExprValue.type`判断值类型，然后访问对应的`value`字段

这个结构设计提供了完整的类型信息访问能力，支持复杂的模板逻辑实现。 