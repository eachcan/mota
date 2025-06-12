# Mota 语言 VSCode 插件

这是一个为 Mota 配置语言和模板语言提供支持的 VSCode 插件。

## 功能

### Mota 配置语言 (.mota)
- 语法高亮
- 代码片段
- 括号匹配
- 注释支持（行注释、块注释和 UI 注释）

### Mota 模板语言 (.template)
- 模板语法高亮（`<%` `%>` 标签）
- **分类颜色高亮**：
  - 🔵 **定义类标签**：`<%misc%>`, `<%endmisc%>` - 类似宏定义
  - 🟢 **控制流标签**：`<%if%>`, `<%foreach%>`, `<%call%>` - 流程控制关键字
  - 🟡 **输出表达式**：`<%=variable%>` - 变量或函数输出
  - 🟠 **内置函数**：`pascal_case()`, `map_type()` - 真正的函数调用
- 变量和表达式高亮
- 代码片段和自动补全
- **🎯 Go to Definition 支持**：
  - Ctrl+Click 或 F12 在 `<%call function_name%>` 上跳转到对应的 `<%misc function_name%>`
  - 支持同文件内和跨文件的定义跳转
  - 自动搜索工作区内所有 `.template` 文件

## 支持的语法

### Mota 配置语言语法

- 指令：`include`, `namespace`, `dir`, `bindir`
- 数据类型：`int8`, `int16`, `int32`, `int64`, `uint8`, `uint16`, `uint32`, `uint64`, `float32`, `float64`, `string`, `bool`, `bytes`
- 修饰符：`optional`, `map`, `repeated`
- 结构定义：`struct`, `block`, `enum`, `annotation`
- 注解系统：`@Annotation(param = value)`
- 注释：`//`, `/**/`, `//@`

> **注意：枚举（enum）和注解（annotation）都不支持继承。**

### Mota 模板语言语法

- **控制结构**：
  - `<%misc name%>...<%endmisc%>` - 定义可重用的代码片段
  - `<%if (condition)%>...<%endif%>` - 条件判断
  - `<%if (condition)%>...<%else%>...<%endif%>` - 条件分支
  - `<%foreach collection as item%>...<%endforeach%>` - 循环遍历
  
- **表达式和调用**：
  - `<%=expression%>` - 输出表达式值
  - `<%call function_name%>` - 调用misc函数
  
- **内置变量**：
  - `CURRENT_TIME` - 当前时间
  - `SOURCE_FILE` - 源文件路径
  - `NAMESPACE` - 命名空间信息
  - `INCLUDES` - 包含文件信息
  - `DECLARATIONS` - 声明列表
  
- **内置函数**：
  - `pascal_case()` - 转换为帕斯卡命名法
  - `map_type()` - 映射类型名称
  - `is_base_type()` - 检查是否为基础类型
  - `escape_string()` - 转义字符串
  - `join()` - 连接数组元素

## 代码片段

插件提供了多种代码片段，帮助您快速编写 Mota 代码：

### Mota 配置语言片段

- `include` - 包含语句
- `namespace` - 命名空间声明
- `dir` - 输出目录设置
- `bindir` - 二进制输出目录设置
- `enum` - 枚举定义
- `struct` - 结构体定义
- `block` - 块定义
- `annotation` - 注解定义
- `@` - 简单注解
- `@(` - 带参数的注解
- `optional` - 可选字段
- `map` - 映射字段
- `repeated` - 重复字段（数组）
- 各种预定义注解：`@Storage`, `@Window`, `@Int`, `@Float`, `@Text`, `@Switcher`, `@Select`, `@EnumValue`, `@IniGroup`

### Mota 模板语言片段

- `misc` - 创建misc代码块
- `if` - 创建if条件块
- `ifelse` - 创建if-else条件块
- `foreach` - 创建foreach循环块
- `call` - 调用misc函数
- `expr` - 插入表达式
- `fieldtype` - 检查字段类型
- `container` - 检查容器类型
- `decltype` - 检查声明类型
- `pascal` - 转换为帕斯卡命名法
- `isbase` - 检查基础类型
- `maptype` - 映射类型名称
- `fieldfor` - 遍历字段
- `declfor` - 遍历声明
- `qstring` - 创建Qt字符串字面量
- `nscheck` - 检查命名空间
- `inccheck` - 处理包含文件
- `islast` - 检查最后元素

## 安装

### 从 VSIX 安装

1. 下载最新的 `.vsix` 文件
2. 在 VSCode 中，选择 "扩展" 视图
3. 点击右上角的 "..." 菜单，选择 "从 VSIX 安装..."
4. 选择下载的 `.vsix` 文件

### 从源码安装

1. 克隆此仓库
2. 进入仓库目录
3. 运行 `npm install`
4. 运行 `npm run package` 生成 `.vsix` 文件
5. 按照上述 "从 VSIX 安装" 的步骤安装

## 使用

- 创建或打开 `.mota` 文件，享受Mota配置语言的语法高亮和代码片段
- 创建或打开 `.template` 文件，享受Mota模板语言的语法高亮和代码片段
- 使用代码片段前缀快速插入常用代码结构
- 支持代码折叠和自动缩进
- 模板文件中的 `<%` `%>` 标签会有特殊高亮，标签外的内容作为普通文本显示
- **在模板文件中，Ctrl+Click 或按 F12 在 `<%call function_name%>` 上可以跳转到对应的 `<%misc function_name%>` 定义**

### 模板语法示例

```template
<%misc getter_method%>
    <%=FIELD_TYPE%> get<%=pascal_case(FIELD_NAME)%>() const {
        return <%=FIELD_NAME%>_;
    }
<%endmisc%>

<%misc class_declaration%>
    class <%=declaration.name%><%call type_suffix%> : <%call inheritance_declaration%> {
    public:
        <%call constructor%>
        <%call accessors%>  <!-- Ctrl+Click这里可以跳转到accessors的定义 -->
    private:
        <%call private_fields%>
    };
<%endmisc%>

<%if (NAMESPACE.exists)%>
namespace <%=NAMESPACE.path%> {
<%endif%>

<%foreach DECLARATIONS as declaration%>
    <%if (declaration.type == "struct")%>
        class <%=declaration.name%>Model : public IModel {
            // 结构体实现
        };
    <%endif%>
<%endforeach%>

<%if (NAMESPACE.exists)%>
}
<%endif%>
```

## 贡献

欢迎提交 Issue 或 Pull Request 来改进此插件。
