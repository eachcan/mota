# MOTA 模板开发指南

## 概述

MOTA模板系统为代码生成提供了灵活且强大的框架。本指南将帮助您理解模板语法、配置选项，以及如何创建自定义模板。

## 模板语法

### 基本语法

MOTA使用类似于EJS的模板语法，但有一些特殊的扩展：

#### 输出值
```
<%=variable%>
```
输出变量的值。

#### 调用函数
```
<%=function(parameter)%>
```
调用函数并输出结果。

**重要**: 函数调用必须使用规范的签名格式，例如：
- `join(separator, array)` - 连接数组元素
- `pascal_case(string)` - 转换为PascalCase
- `map_type(type)` - 映射类型

**不允许**使用如 `array.join(separator)` 这样的方法调用语法。

#### 条件语句
```
<%if (condition)%>
    执行的内容
<%elseif (another_condition)%>
    其他条件的内容
<%else%>
    默认内容
<%endif%>
```

#### 循环语句
```
<%foreach item in items%>
    为每个项目执行的内容
<%endforeach%>
```

#### Map遍历
```
<%for (key, value) in map%>
    键：<%=key%>，值：<%=value%>
<%endfor%>
```

### 片段(Misc)系统

片段系统允许您定义可重用的模板代码块，提高了模板的模块化程度。

#### 定义片段
```
<%misc fragment_name%>
    模板内容
    可以使用变量：<%=VARIABLE%>
    可以调用其他片段：<%call other_fragment%>
<%endmisc%>
```

#### 调用片段
```
<%call fragment_name%>
```

**重要特性**：
- 片段会继承调用区域的所有变量
- 片段可以调用其他片段
- 片段支持递归调用（需谨慎使用避免无限循环）

### 示例：使用片段

```template
<%misc getter_method%>
    <%=FIELD_TYPE%> get<%=pascal_case(FIELD_NAME)%>() const {
        return <%=FIELD_NAME%>_;
    }
<%endmisc%>

<%misc class_name%><%=TYPE_NAME%><%call type_suffix%><%endmisc%>

<%misc type_suffix%>
<%if (TYPE == "struct")%>Model<%endif%>
<%if (TYPE == "block")%>Block<%endif%>
<%endmisc%>

// 使用片段
<%call getter_method%>
```

## 配置文件结构

配置文件使用JSON5格式，支持注释和更灵活的语法。

### 基本结构

```json5
{
  "version": "2.0",
  "encoding": "UTF-8 with BOM",
  "templates": {
    "file": "file.template",
    "block_decl": "block_decl.template",
    "struct_decl": "struct_decl.template",
    "enum_decl": "enum_decl.template",
    "annotation_decl": "annotation_decl.template",
    "annotation": "annotation.template"
  },
  "miscs": [
    "misc.template"
  ],
  // 其他配置项...
}
```

### 必需的模板

每个模板集合必须包含以下模板：
- `file` - 文件结构模板
- `block_decl` - Block声明模板
- `struct_decl` - Struct声明模板
- `enum_decl` - Enum声明模板
- `annotation_decl` - Annotation声明模板
- `annotation` - 注解实例模板

### Misc片段系统

从版本2.0开始，大部分格式化配置被misc片段系统替代，提供了更高的灵活性。

#### 被替代的配置项

以下配置项已被misc片段替代：

- **`accessor_format`** → 直接在模板中硬编码 "get"/"set" 前缀
- **`identifier_format`** → `type_suffix`、`class_name` 片段
- **`inheritance_format`** → `inheritance_declaration` 片段
- **`field_type_templates`** → `field_type_template` 片段
- **`type_interface_mapping`** → `interface_name` 片段
- **`syntax_elements`** → 各种语法元素片段（如 `private_field_suffix`、`field_name_variable` 等）
- **`code_generation`** → 代码生成片段（如 `container_template`、`variant_template` 等）

#### 保留的配置项

以下配置项继续保留，用于基础设置：

- **`type_mapping`** - 基础类型映射
- **`file_path`** - 输出文件路径规则
- **`include_directive`** - 包含指令格式

### 配置项详解

#### type_mapping
定义基础类型的映射关系：
```json5
"type_mapping": {
  "int32": "int32_t",
  "string": "QString",
  "bool": "bool"
}
```

#### file_path
定义输出文件的路径规则：
```json5
"file_path": [
  {
    "path": "<%=namespace_path(NAMESPACE)%>/<%=FILE_NAME%>.h",
    "type": "file"
  }
]
```

#### include_directive
定义包含指令的格式：
```json5
"include_directive": {
  "pattern": "#include \"<%=INCLUDE_PATH%>\"",
  "source_extension": ".mota",
  "target_extension": ".h"
}
```

## 必需的Misc片段

在misc文件中，必须定义以下片段以替代原有的配置项：

### 语法元素片段（替代syntax_elements配置）
- `private_field_suffix` - 私有字段后缀（"_"）
- `empty_variant` - 空的QVariant值
- `repeated_keyword` - 重复关键字（"repeated"）
- `namespace_path_separator` - 命名空间路径分隔符（"/"）
- `namespace_separator_replacement` - 命名空间分隔符替换规则
- `argument_name_variable` - 参数名变量（"argumentName"）
- `field_name_variable` - 字段名变量（"fieldName"）
- `enum_value_separator` - 枚举值分隔符（",\n    "）
- `enum_case_separator` - 枚举case分隔符
- `enum_condition_separator` - 枚举条件分隔符（" else "）
- `enum_string_value_separator` - 枚举字符串值分隔符
- `enum_display_name_separator` - 枚举显示名分隔符
- `enum_annotation_case_separator` - 枚举注解case分隔符
- `enum_annotation_condition_separator` - 枚举注解条件分隔符
- `enum_value_annotation_names` - 枚举值注解名称
- `desc_param_name` - 描述参数名（"desc"）

### 代码生成片段（替代code_generation配置）
- `container_template` - 容器模板（如 "QVector<ELEMENT_TYPE>"）
- `string_literal_template` - 字符串字面量模板
- `variant_template` - QVariant模板
- `collection_separator` - 集合分隔符（"|"）

### 格式化片段（替代配置）
- `type_suffix` - 类型后缀（Block、Model、Annotation等）
- `interface_name` - 接口名称（IBlock、IModel、IAnnotation等）
- `field_type_template` - 字段类型模板标识

### 基础片段
- `class_name` - 类名生成
- `private_field_name` - 私有字段名
- `private_field_declaration` - 私有字段声明
- `field_name_pascal` - Pascal格式字段名
- `field_name_camel` - Camel格式字段名
- `field_type_mapped` - 映射后的字段类型

### 访问器片段
- `getter_method` - Getter方法（直接使用"get"前缀）
- `setter_method` - Setter方法（直接使用"set"前缀）
- `accessors` - 所有访问器

### 序列化片段
- `serialize_int/float/string/bool/bytes/array/complex` - 各类型序列化
- `deserialize_int/float/string/bool/bytes/array/complex` - 各类型反序列化
- `serialize_fields` - 所有字段序列化
- `deserialize_fields` - 所有字段反序列化

### 注解相关片段
- `annotation_arg_literal_string/int/float/bool_true/bool_false` - 字面量参数
- `annotation_arg_array/map/custom/identifier` - 复合类型参数
- `annotation_arg_value` - 通用参数值处理
- `model_annotation_logic` - 模型注解逻辑
- `block_annotation_logic` - Block注解逻辑
- `enum_annotation_logic` - 枚举注解逻辑
- `field_annotation_logic` - 字段注解逻辑

### 枚举相关片段
- `enum_values` - 枚举值定义
- `enum_to_string_cases` - 枚举转字符串
- `string_to_enum_conditions` - 字符串转枚举
- `enum_value_annotation_cases` - 枚举值注解

### 其他必需片段
- `inheritance_declaration` - 继承声明（单继承 + 接口）
- `constructor` - 构造函数
- `includes` - 包含文件
- `field_names` - 字段名列表
- `field_type_logic` - 字段类型逻辑
- `value_getter_logic/value_setter_logic` - 值访问逻辑
- `private_fields` - 私有字段定义

## 继承规则

MOTA遵循以下继承规则：

1. **不支持多继承**: 一个类只能有一个基类
2. **必须实现接口**: 所有生成的类都必须实现对应的接口（IModel、IBlock、IAnnotation）
3. **继承语法**: 
   - 有基类: `public BaseClass, public IInterface`
   - 无基类: `public IInterface`

示例：
```cpp
// 有基类的情况
class UserModel : public BaseModel, public IModel {
    // ...
};

// 无基类的情况  
class UserModel : public IModel {
    // ...
};
```

## 模板变量

### 全局变量
在所有模板中都可以使用的变量：
- `NAMESPACE` - 命名空间
- `FILE_NAME` - 文件名
- `INCLUDES` - 包含的文件列表

### Block/Struct变量
- `TYPE_NAME` - 类型名称
- `DESCRIPTION` - 描述信息
- `FIELDS` - 字段列表
- `ANNOTATIONS` - 注解列表
- `HAS_ANNOTATIONS` - 是否有注解
- `HAS_BASE_CLASS` - 是否有基类
- `BASE_CLASS` - 基类名称（单个）

### Enum变量
- `ENUM_NAME` - 枚举名称
- `ENUM_VALUES` - 枚举值列表
- `DESCRIPTION` - 描述信息

### Field变量
在字段相关的上下文中：
- `FIELD_NAME` - 字段名
- `FIELD_TYPE` - 字段类型
- `IS_REPEATED` - 是否为数组
- `IS_CUSTOM_TYPE` - 是否为自定义类型
- `HAS_DEFAULT_VALUE` - 是否有默认值
- `DEFAULT_VALUE` - 默认值

## 内置函数

### 字符串处理函数
- `pascal_case(str)` - 转换为PascalCase
- `camel_case(str)` - 转换为camelCase
- `snake_case(str)` - 转换为snake_case
- `escape_string(str)` - 转义字符串

### 类型处理函数
- `map_type(type)` - 映射类型
- `namespace_path(namespace)` - 生成命名空间路径

### 数组处理函数
- `join(separator, array)` - 连接数组元素，例如：`join(", ", CONSTRUCTOR_PARAMS)`

### 辅助函数
- `field_type_template(type)` - 获取字段类型模板标识

## 创建新模板

### 1. 创建配置文件
```json5
{
  "version": "2.0",
  "encoding": "UTF-8 with BOM",
  "templates": {
    "file": "file.template",
    "block_decl": "block_decl.template",
    "struct_decl": "struct_decl.template",
    "enum_decl": "enum_decl.template",
    "annotation_decl": "annotation_decl.template",
    "annotation": "annotation.template"
  },
  "miscs": [
    "misc.template"
  ],
  "type_mapping": {
    // 定义类型映射
  },
  "file_path": [
    // 定义输出路径
  ]
  // 其他配置项...
}
```

### 2. 创建Misc片段文件
在 `misc.template` 中定义所有必需的片段，特别是格式化相关的片段。

### 3. 创建模板文件
为每个必需的模板创建对应的 `.template` 文件。

### 4. 使用新语法
确保所有模板文件都使用新的模板语法，遵循函数调用规范。

## 最佳实践

### 函数调用规范
1. **标准签名**: 使用 `function(param1, param2)` 格式
2. **避免方法调用**: 不使用 `object.method()` 语法
3. **参数顺序**: 遵循既定的参数顺序，如 `join(separator, array)`

### 片段设计原则
1. **单一职责** - 每个片段应该有明确的单一功能
2. **可复用性** - 设计通用的片段，避免重复代码
3. **参数传递** - 利用变量继承机制传递参数
4. **命名规范** - 使用清晰的命名，便于理解和维护

### 继承设计
1. **单继承原则** - 每个类最多只有一个基类
2. **接口实现** - 所有类都必须实现对应接口
3. **明确层次** - 基类在前，接口在后

### 模板组织
1. **模块化** - 将复杂的逻辑分解为多个小片段
2. **分层设计** - 基础片段、组合片段、业务片段分层设计
3. **文档注释** - 在模板中添加适当的注释说明

### 配置简化
1. **避免冗余** - 不要在配置中重复定义可以通过片段实现的内容
2. **专注核心** - 配置文件应专注于类型映射等核心设置
3. **灵活扩展** - 通过片段系统而非配置项实现扩展

## 迁移指南

### 从1.0到2.0
如果您有基于1.0版本的模板，需要进行以下迁移：

1. **移除格式化配置** - 删除 `accessor_format`、`identifier_format` 等配置项
2. **创建Misc片段** - 将格式化逻辑转换为misc片段
3. **更新函数调用** - 将 `array.join()` 改为 `join(separator, array)`
4. **修正继承逻辑** - 使用单继承 + 接口的模式
5. **更新版本号** - 将配置文件的版本号改为 "2.0"

### 配置映射表
| 1.0配置项 | 2.0替代方案 |
|----------|------------|
| `accessor_format.getter_prefix` | 硬编码"get"前缀 |
| `accessor_format.setter_prefix` | 硬编码"set"前缀 |
| `identifier_format.suffix` | `type_suffix` 片段 |
| `inheritance_format` | `inheritance_declaration` 片段 |
| `field_type_templates` | `field_type_template` 片段 |
| `type_interface_mapping` | `interface_name` 片段 |
| `syntax_elements.PRIVATE_FIELD_SUFFIX` | `private_field_suffix` 片段 |
| `syntax_elements.EMPTY_VARIANT` | `empty_variant` 片段 |
| `syntax_elements.FIELD_NAME_VARIABLE` | `field_name_variable` 片段 |
| `syntax_elements.*` | 对应的语法元素片段 |
| `code_generation.container_template` | `container_template` 片段 |
| `code_generation.variant_template` | `variant_template` 片段 |
| `code_generation.*` | 对应的代码生成片段 |

## 调试和测试

### 调试技巧
1. **分步测试** - 先测试简单的片段，再测试复杂的组合
2. **输出调试** - 使用 `<%=DEBUG_VARIABLE%>` 输出调试信息
3. **语法检查** - 确保生成的代码语法正确
4. **函数验证** - 确保函数调用使用正确的签名

### 常见问题
1. **片段未定义** - 确保所有调用的片段都已定义
2. **变量未传递** - 检查变量的作用域和传递
3. **循环引用** - 避免片段间的循环调用
4. **函数签名错误** - 使用标准的函数调用语法

## 示例

完整的模板示例请参考 `template/yima-cpp` 目录，这是一个使用新语法系统的完整C++模板实现。

## 总结

新的模板系统通过引入片段机制和简化配置，提供了更高的灵活性和更好的维护性。开发者可以通过自定义片段来实现特定的代码生成需求，而无需修改核心配置。重要的是要遵循正确的函数调用语法和继承规则，确保生成的代码符合预期。 