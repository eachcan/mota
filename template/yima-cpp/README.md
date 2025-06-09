# Yima C++ 模板

这是用于生成 C++ 代码的 Mota 模板集合，使用新的模板语法系统。

## 模板语法

### 基本语法

- **输出值**: `<%=variable%>`
- **调用函数**: `<%=function(variable)%>`
- **条件语句**: 
  ```
  <%if (condition)%>
      ...
  <%elseif (condition)%>
      ...
  <%else%>
      ...
  <%endif%>
  ```
- **循环语句**:
  ```
  <%foreach item in items%>
      ...
  <%endforeach%>
  ```
- **Map遍历**:
  ```
  <%for (key, value) in map%>
      ...
  <%endfor%>
  ```

### 函数调用规范

**重要**: 模板中的函数调用必须使用规范的签名格式：

- ✅ 正确: `join(", ", CONSTRUCTOR_PARAMS)`
- ❌ 错误: `CONSTRUCTOR_PARAMS.join(", ")`

常用函数：
- `join(separator, array)` - 连接数组元素
- `pascal_case(string)` - 转换为PascalCase  
- `map_type(type)` - 映射类型
- `escape_string(string)` - 转义字符串

### 片段(Misc)系统

- **定义片段**: 
  ```
  <%misc name%>
      模板内容
  <%endmisc%>
  ```
- **调用片段**: `<%call name%>`

片段会继承调用区域的全部变量，实现了模板的模块化和复用。

## 文件结构

### 配置文件
- `config.json5` - 主配置文件，定义类型映射等基础设置
- `misc.template` - 片段定义文件，包含所有可复用的模板片段

### 模板文件
- `file.template` - 文件结构模板（头文件框架）
- `block_decl.template` - Block声明模板
- `struct_decl.template` - Struct声明模板  
- `enum_decl.template` - Enum声明模板
- `annotation_decl.template` - Annotation声明模板
- `annotation.template` - 注解实例模板

## 配置说明

新版本的配置文件极度简洁，移除了几乎所有格式化和语法配置，这些配置现在通过misc片段实现：

### 保留的配置项

- `type_mapping` - 基础类型映射
- `file_path` - 输出文件路径规则
- `include_directive` - 包含指令格式

### 通过Misc片段实现的功能

以下配置项已被misc片段替代，提供了更灵活的自定义能力：

- ~~`accessor_format`~~ → 直接在模板中硬编码 "get"/"set" 前缀
- ~~`identifier_format`~~ → `type_suffix`、`class_name` 片段
- ~~`inheritance_format`~~ → `inheritance_declaration` 片段
- ~~`field_type_templates`~~ → `field_type_template` 片段
- ~~`type_interface_mapping`~~ → `interface_name` 片段
- ~~`syntax_elements`~~ → 各种语法元素片段（如 `private_field_suffix`、`field_name_variable` 等）
- ~~`code_generation`~~ → 代码生成片段（如 `container_template`、`variant_template` 等）

## 继承规则

本模板遵循以下继承规则：

1. **不支持多继承**: 一个类只能有一个基类
2. **必须实现接口**: 所有生成的类都必须实现对应的接口
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

## 必需的Misc片段

在 `misc.template` 中定义了以下必需的片段：

### 语法元素片段（替代syntax_elements配置）
- `private_field_suffix` - 私有字段后缀（"_"）
- `empty_variant` - 空的QVariant值
- `repeated_keyword` - 重复关键字（"repeated"）
- `namespace_path_separator` - 命名空间路径分隔符（"/"）
- `argument_name_variable` - 参数名变量（"argumentName"）
- `field_name_variable` - 字段名变量（"fieldName"）
- `enum_value_separator` - 枚举值分隔符（",\n    "）
- 以及其他枚举相关的分隔符片段

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
- `getter_method` - Getter方法（硬编码"get"前缀）
- `setter_method` - Setter方法（硬编码"set"前缀）
- `accessors` - 所有访问器

### 序列化片段
- `serialize_int/float/string/bool/bytes/array/complex` - 各类型序列化
- `deserialize_int/float/string/bool/bytes/array/complex` - 各类型反序列化
- `serialize_fields` - 所有字段序列化
- `deserialize_fields` - 所有字段反序列化

### 注解参数片段
- `annotation_arg_literal_string/int/float/bool_true/bool_false` - 字面量参数
- `annotation_arg_array/map/custom/identifier` - 复合类型参数
- `annotation_arg_value` - 通用参数值处理

### 注解逻辑片段
- `model_annotation_logic` - 模型注解逻辑
- `block_annotation_logic` - Block注解逻辑
- `enum_annotation_logic` - 枚举注解逻辑
- `field_annotation_logic` - 字段注解逻辑

### 枚举相关片段
- `enum_values` - 枚举值定义
- `enum_to_string_cases` - 枚举转字符串
- `string_to_enum_conditions` - 字符串转枚举
- `enum_value_annotation_cases` - 枚举值注解

### 其他片段
- `inheritance_declaration` - 继承声明（单继承 + 接口）
- `constructor` - 构造函数
- `includes` - 包含文件
- `field_names` - 字段名列表
- `field_type_logic` - 字段类型逻辑
- `value_getter_logic/value_setter_logic` - 值访问逻辑
- `private_fields` - 私有字段定义

## 类型映射

支持以下基本类型的映射：
- `int8/16/32/64` → `int8_t/16_t/32_t/64_t`
- `uint8/16/32/64` → `uint8_t/16_t/32_t/64_t`
- `float32/64` → `float/double`
- `string` → `QString`
- `bool` → `bool`
- `bytes` → `QByteArray`

## 生成的代码特性

- 完整的CBOR序列化/反序列化支持
- 类型安全的访问器方法
- 注解系统支持
- 反射能力（字段枚举、类型查询等）
- Qt框架集成
- 现代C++特性使用

## 设计优势

### 配置简化
移除了冗余的格式化配置，使配置文件更加简洁，专注于核心的类型映射和生成规则。

### 灵活性提升
通过misc片段实现格式化逻辑，开发者可以：
- 自定义命名规则
- 修改生成的代码结构
- 添加新的代码片段
- 实现特定的业务逻辑

### 维护性增强
- 片段化的代码更易于理解和维护
- 逻辑集中在misc.template中，便于统一管理
- 避免了配置和模板之间的耦合
- 遵循统一的函数调用规范

### 继承模型清晰
- 单继承 + 接口实现的清晰模型
- 避免了多继承的复杂性
- 确保所有类都实现必要的接口

## 扩展

开发者可以通过以下方式扩展模板：

1. 在 `misc.template` 中添加自定义片段
2. 修改 `config.json5` 中的基础配置项
3. 创建额外的misc文件并在配置中引用
4. 自定义模板文件以支持新的代码结构

所有的格式化和生成逻辑都可以通过修改对应的misc片段来自定义，无需修改配置文件。记住要遵循正确的函数调用语法和继承规则。
