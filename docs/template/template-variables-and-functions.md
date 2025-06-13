# MOTA 模板变量和函数参考

本文档详细描述了MOTA模板系统中可用的所有变量结构和函数，帮助模板开发者正确访问和使用这些功能。

## 概述

MOTA模板系统提供了一个结构化的变量树，包含了编译过程中解析出的所有信息，以及一系列内置函数用于数据处理和格式化。

## 变量结构

### 根级变量 (TemplateVars)

```
TemplateVars (Root)
├── CURRENT_TIME: string
├── SOURCE_FILE: string
├── FILE_NAME: string
├── NAMESPACE: NamespaceInfo
├── INCLUDES: IncludesInfo
└── DECLARATIONS: Declaration[]
```

#### CURRENT_TIME
- **类型**: `string`
- **描述**: 代码生成的当前时间
- **示例**: `"2025-06-10 23:41:33"`
- **用法**: `<%=CURRENT_TIME%>`

#### SOURCE_FILE
- **类型**: `string`
- **描述**: 当前正在处理的源文件路径
- **示例**: `".\\examples\\simple.mota"`
- **用法**: `<%=SOURCE_FILE%>`

#### FILE_NAME
- **类型**: `string`
- **描述**: 不带扩展名的文件名
- **示例**: `"simple"`
- **用法**: `<%=FILE_NAME%>`

### NAMESPACE 对象

命名空间信息，包含完整的层次结构和便利访问方法。

```
NAMESPACE: NamespaceInfo
├── exists: boolean
├── parts: NamespacePart[]
├── path: string
└── parts_count: int
```

#### exists
- **类型**: `boolean`
- **描述**: 是否定义了命名空间
- **用法**: `<%if (NAMESPACE.exists)%>...<%endif%>`

#### parts
- **类型**: `NamespacePart[]`
- **描述**: 命名空间的各个部分，支持多级命名空间

```template
<%foreach NAMESPACE.parts as part%>
    命名空间部分: <%=part.name%>
    索引: <%=part.index%>
    是否首个: <%=part.is_first%>
    是否最后: <%=part.is_last%>
<%endforeach%>
```

**NamespacePart 结构**:
```
NamespacePart
├── name: string        // 部分名称，如 "com"
├── index: int          // 在parts数组中的索引
├── is_first: bool      // 是否是第一个部分
└── is_last: bool       // 是否是最后一个部分
```

#### path
- **类型**: `string`
- **描述**: 完整的命名空间路径
- **示例**: `"com.example.project"`
- **用法**: `<%=NAMESPACE.path%>`

#### parts_count
- **类型**: `int`
- **描述**: 命名空间部分的数量
- **用法**: `<%=NAMESPACE.parts_count%>`

### INCLUDES 对象

包含文件信息，管理依赖的其他MOTA文件。

```
INCLUDES: IncludesInfo
├── files: IncludeFile[]
└── count: int
```

#### files
- **类型**: `IncludeFile[]`
- **描述**: 包含的文件列表

```template
<%foreach INCLUDES.files as file%>
    源文件: <%=file.source%>
    目标文件: <%=file.translated%>
<%endforeach%>
```

**IncludeFile 结构**:
```
IncludeFile
├── source: string      // 原始文件名，如 "yima.mota"
└── translated: string  // 转换后的文件名，如 "yima.h"
```

#### count
- **类型**: `int`
- **描述**: 包含文件的数量
- **用法**: `<%=INCLUDES.count%>`

### DECLARATIONS 数组

声明信息是模板系统的核心，包含所有类型声明。

```
DECLARATIONS: Declaration[]
```

#### Declaration 结构

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

**基本属性**:
- **type**: 声明类型
  - `"annotation_decl"`: 注解声明
  - `"enum"`: 枚举类型  
  - `"block"`: 块类型
  - `"struct"`: 结构体类型
- **name**: 原始声明名称，如 `"Task"`
- **class_name**: 生成的类名，如 `"TaskModel"`
- **parent**: 父类原始名称（继承时）
- **parent_class_name**: 父类生成的类名（继承时）

**使用示例**:
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

#### annotations 数组

每个声明可以有多个注解：

```
Annotation
├── name: string                    // 注解名称
├── class_name: string              // 注解类名
└── arguments: AnnotationArgument[] // 注解参数
```

**AnnotationArgument 结构**:
```
AnnotationArgument
├── name: string                    // 参数名称
└── value: AnnotationValue          // 参数值
```

**AnnotationValue 结构**:
```
AnnotationValue
├── type: string                    // 值类型
├── value: string                   // 字符串表示
├── int_value?: int                 // 整数值（如果适用）
├── bool_value?: bool               // 布尔值（如果适用）
└── array_values?: AnnotationValue[] // 数组值（如果适用）
```

**使用示例**:
```template
<%foreach declaration.annotations as annotation%>
    注解: <%=annotation.name%>
    <%foreach annotation.arguments as arg%>
        参数 <%=arg.name%>: <%=arg.value.value%>
    <%endforeach%>
<%endforeach%>
```

#### fields 数组（Enum除外）

结构体、块、注解声明都有字段：

```
Field
├── name: string                    // 字段原始名称
├── field_name: string              // 字段变量名
├── container_type: string          // "none" | "array" | "map" | "optional"
├── type_name: string               // 类型名称
├── type_namespaces: string[]       // 类型命名空间
├── qualified_type_name: string     // 完全限定类型名
├── default_value?: string          // 默认值
├── annotations: Annotation[]       // 字段注解
├── index: int                      // 字段索引
├── is_first: bool                  // 是否是第一个字段
├── is_last: bool                   // 是否是最后一个字段
└── is_repeated: bool               // 是否是数组类型
```

**使用示例**:
```template
<%foreach declaration.fields as field%>
    字段: <%=field.name%>
    类型: <%=field.qualified_type_name%>
    <%if (field.is_repeated)%>
        这是一个数组字段
    <%endif%>
    <%if (field.default_value)%>
        默认值: <%=field.default_value%>
    <%endif%>
<%endforeach%>
```

#### values 数组（仅Enum）

枚举类型特有的值列表：

```
EnumValue
├── name: string                    // 枚举值名称
├── value: int                      // 枚举值
├── annotations: Annotation[]       // 枚举值注解
├── index: int                      // 值索引
├── is_first: bool                  // 是否是第一个值
└── is_last: bool                   // 是否是最后一个值
```

**使用示例**:
```template
<%if (declaration.type == "enum")%>
enum <%=declaration.name%> {
<%foreach declaration.values as value%>
    <%=value.name%> = <%=value.value%><%if (!value.is_last)%>,<%endif%>
<%endforeach%>
};
<%endif%>
```

## 上下文变量

在特定模板上下文中，还会有额外的变量可用：

### 字段上下文变量

当在字段相关的misc片段中时，可以使用：

- `FIELD_NAME`: 当前字段名称
- `FIELD_TYPE`: 当前字段类型
- `FIELD_ELEMENT_TYPE`: 数组字段的元素类型
- `FIELD_DEFAULT_VALUE`: 字段默认值

### 类型上下文变量

当在类型相关的misc片段中时，可以使用：

- `TYPE`: 当前类型（"struct", "block", "enum", "annotation_decl"）
- `TYPE_NAME`: 当前类型名称
- `PARENT_CLASS_NAME`: 父类类名（如果有继承）

## 内置函数

MOTA模板系统提供了丰富的内置函数用于数据处理和格式化。

### 字符串处理函数

#### pascal_case(string)
将字符串转换为PascalCase格式。

```template
<%=pascal_case("user_name")%>     // 输出: UserName
<%=pascal_case("user-profile")%>  // 输出: UserProfile
```

#### camel_case(string)
将字符串转换为camelCase格式。

```template
<%=camel_case("user_name")%>      // 输出: userName
<%=camel_case("USER_PROFILE")%>   // 输出: userProfile
```

#### snake_case(string)
将字符串转换为snake_case格式。

```template
<%=snake_case("UserName")%>       // 输出: user_name
<%=snake_case("userProfile")%>    // 输出: user_profile
```

#### upper_case(string)
将字符串转换为大写。

```template
<%=upper_case("hello world")%>    // 输出: HELLO WORLD
```

#### lower_case(string)
将字符串转换为小写。

```template
<%=lower_case("HELLO WORLD")%>    // 输出: hello world
```

### 数组处理函数

#### join(separator, array)
使用指定分隔符连接数组元素。

```template
<%=join(", ", ["apple", "banana", "orange"])%>  // 输出: apple, banana, orange
<%=join("::", NAMESPACE.parts)%>                // 输出: com::example::project
```

#### length(array)
获取数组长度。

```template
<%=length(DECLARATIONS)%>         // 输出: 声明数量
<%=length(declaration.fields)%>   // 输出: 字段数量
```

### 类型处理函数

#### map_type(type)
将MOTA类型映射到目标语言类型。

```template
<%=map_type("int32")%>            // 输出: int32_t (C++)
<%=map_type("string")%>           // 输出: QString (C++)
<%=map_type("bool")%>             // 输出: bool
```

#### is_repeated(type)
检查类型是否为数组类型。

```template
<%if (is_repeated(field.type))%>
    // 处理数组类型
<%endif%>
```

#### element_type(type)
获取数组类型的元素类型。

```template
<%if (is_repeated(field.type))%>
    元素类型: <%=map_type(element_type(field.type))%>
<%endif%>
```

### 命名空间函数

#### namespace_path(namespace)
获取命名空间的路径表示。

```template
<%=namespace_path(NAMESPACE)%>     // 输出: com/example/project
```

### 条件函数

#### has_annotation(declaration, annotation_name)
检查声明是否有指定的注解。

```template
<%if (has_annotation(declaration, "Deprecated"))%>
    // 处理已废弃的声明
<%endif%>
```

#### get_annotation(declaration, annotation_name)
获取指定名称的注解。

```template
<%if (has_annotation(declaration, "Description"))%>
    <%=get_annotation(declaration, "Description").arguments[0].value.value%>
<%endif%>
```

## 使用示例

### 完整的类生成示例

```template
<%foreach DECLARATIONS as declaration%>
<%if (declaration.type == "struct")%>
/**
 * Generated from <%=SOURCE_FILE%>
 * Generated at <%=CURRENT_TIME%>
 */
class <%=declaration.class_name%><%if (declaration.parent)%> : public <%=declaration.parent_class_name%><%endif%> {
public:
    <%=declaration.class_name%>() = default;
    
    // 字段访问器
<%foreach declaration.fields as field%>
    <%=map_type(field.qualified_type_name)%> get<%=pascal_case(field.name)%>() const {
        return <%=field.name%>_;
    }
    
    void set<%=pascal_case(field.name)%>(const <%=map_type(field.qualified_type_name)%>& value) {
        <%=field.name%>_ = value;
    }
    
<%endforeach%>
private:
<%foreach declaration.fields as field%>
    <%=map_type(field.qualified_type_name)%> <%=field.name%>_<%if (field.default_value)%> = <%=field.default_value%><%endif%>;
<%endforeach%>
};

<%endif%>
<%endforeach%>
```

### 枚举生成示例

```template
<%foreach DECLARATIONS as declaration%>
<%if (declaration.type == "enum")%>
enum class <%=declaration.name%> {
<%foreach declaration.values as value%>
    <%=value.name%> = <%=value.value%><%if (!value.is_last)%>,<%endif%>
<%endforeach%>
};

<%endif%>
<%endforeach%>
```

### 命名空间处理示例

```template
<%if (NAMESPACE.exists)%>
<%foreach NAMESPACE.parts as part%>
<%if (part.is_first)%>namespace <%else%>::<%endif%><%=part.name%><%if (part.is_last)%> {<%endif%>
<%endforeach%>

<%endif%>
// 声明内容...

<%if (NAMESPACE.exists)%>
<%foreach NAMESPACE.parts as part%>
<%if (part.is_last)%>} // namespace <%=NAMESPACE.path%><%endif%>
<%endforeach%>
<%endif%>
```

## 调试技巧

### 1. 输出变量信息

```template
// Debug: 当前处理文件: <%=SOURCE_FILE%>
// Debug: 声明数量: <%=length(DECLARATIONS)%>
// Debug: 命名空间: <%=NAMESPACE.path%>
<%foreach DECLARATIONS as declaration%>
// Debug: 声明 <%=declaration.name%> 类型: <%=declaration.type%>
<%endforeach%>
```

### 2. 条件调试

```template
<%if (declaration.type == "struct")%>
// Debug: 结构体 <%=declaration.name%> 有 <%=length(declaration.fields)%> 个字段
<%foreach declaration.fields as field%>
// Debug: 字段 <%=field.name%> 类型 <%=field.qualified_type_name%>
<%endforeach%>
<%endif%>
```

### 3. 使用JSON输出调试

生成JSON格式的输出来查看完整的数据结构：

```bash
./bin/mota.exe test.mota -l test -o debug/
```

然后查看生成的JSON文件了解变量结构。

## 注意事项

1. **变量作用域**: 某些变量只在特定上下文中可用
2. **数组访问**: 使用`foreach`循环访问数组，不要直接索引访问
3. **条件检查**: 在访问可选属性前先检查其存在性
4. **函数调用**: 必须使用标准函数签名，不支持方法调用语法
5. **类型安全**: 确保类型映射的完整性，处理未知类型的情况 