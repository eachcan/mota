# Mota 语言 VSCode 插件

这是一个为 Mota 配置语言提供支持的 VSCode 插件。

## 功能

- 语法高亮
- 代码片段
- 括号匹配
- 注释支持（行注释、块注释和 UI 注释）

## 支持的语法

- 指令：`include`, `namespace`, `dir`, `bindir`
- 数据类型：`int8`, `int16`, `int32`, `int64`, `uint8`, `uint16`, `uint32`, `uint64`, `float32`, `float64`, `string`, `bool`, `bytes`
- 修饰符：`optional`, `map`, `repeated`
- 结构定义：`struct`, `block`, `enum`, `annotation`
- 注解系统：`@Annotation(param = value)`
- 注释：`//`, `/**/`, `//@`

## 代码片段

插件提供了多种代码片段，帮助您快速编写 Mota 代码：

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

创建或打开 `.mota` 文件，插件将自动激活。

## 贡献

欢迎提交 Issue 或 Pull Request 来改进此插件。
