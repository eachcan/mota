# Mota 模型定义指南

本文档描述了 MOTA 项目中使用的模型注解格式。

## 结构体注解

结构体可以使用以下元数据进行注解：

```mota
@storage(
    path = "${app_dir}/device-base.cbor",  // 目标文件路径
    format = "cbor"                         // 数据格式
)

@window(title = "相机配置", desc = "相机配置")
@scope(value = "product")
```

**Storage 注解**

`path`: 指定文件路径，支持变量插值

 - `${app_dir}`: 应用程序安装路径
 - `${config_dir}`: 配置文件路径
 - `${product_config_dir}`: 产品配置文件路径
 - `${temp_dir}`: 临时文件路径
 - `${modules_dir}`: 模块目录
 - `${log_dir}`: 日志目录
 - `${lang_dir}`: 语言目录

`format`: 指定数据格式，支持以下格式：

 - `cbor`
 - `json`
 - `ini`
 - `winreg`

**Window 注解**

`title`: 指定窗口标题

`desc`: 指定窗口描述

**Scope 注解**

`scope`: 指定作用域，支持以下值：

 - `global`: 全局作用域
 - `product`: 产品作用域

## 字段注解

字段注解分为以下几种：

### UI 注解

可以为模型自动生成 UI 界面，没有注解时各类型有默认的 UI 类型，有注解时使用注解指定的 UI 类型。

```mota
@text(max_length = 64)
string name;
```

#### UI 类型

UI 类型不是必须的，系统会根据类型自动选择合适的 UI 类型。如果要指定 UI 类型及其参数，需要使用相应的注解。

支持以下 UI 类型：

- `draw_rectangle`：矩形绘制，仅用于 Rectangle 类型字段
- `draw_circle`：圆形绘制，仅用于 Circle 类型字段
- `draw_ellipse`：椭圆绘制，仅用于 Ellipse 类型字段
- `draw_line`：线段绘制，仅用于 Line 类型字段
- `draw_hline`：水平线绘制，仅用于 HLine 类型字段
- `draw_vline`：垂直线绘制，仅用于 VLine 类型字段
- `draw_polygon`：多边形绘制，仅用于 Polygon 类型字段
- `int`：数值输入，仅用于 int8 / int16 / int32 / int64 类型字段
- `float`：浮点数输入，仅用于 float32 / double64 类型字段
- `int_range`：整数范围输入，仅用于 int8 / int16 / int32 / int64 类型字段
- `float_range`：浮点数范围输入，仅用于 float32 / double64 类型字段
- `text`：文本输入（仅用于字符串），用于 string 类型字段
- `switcher`：布尔开关（仅用于布尔值），用于 bool 类型字段
- `select`：预定义选项选择，用于 string / enum class / int8 / int16 / int32 / int64 类型字段
- `file_dialog`：文件选择，用于 string 类型字段
- `folder_dialog`：文件夹选择，用于 string 类型字段

UI 注解通用字段：

- `label`: 标签，用于显示字段名称
- `desc`: 描述，用于显示字段描述，此字段可以用 `//@` 注释来代替，有此字段时，`//@` 注释将被忽略
- `required`: 是否必填，默认为 false
- `visible`: 是否可见，默认为 true
- `editable`: 是否可编辑，默认为 true

**矩形 draw_rectangle**

此注解将在配置界面中显示为一个按钮，点击后会在图像区域显示一个矩形。

矩形可以拖动、改变大小、旋转。

使用方法：

```mota
@draw_rectangle()
Rectangle rect;
```

类似的还有以下几种绘制：

- `draw_circle`：圆形绘制，仅用于 Circle 类型字段
- `draw_ellipse`：椭圆绘制，仅用于 Ellipse 类型字段
- `draw_line`：线段绘制，仅用于 Line 类型字段
- `draw_polygon`：多边形绘制，仅用于 Polygon 类型字段

这几个注解都没有参数，直接使用即可。

**横线 draw_hline**

此注解将在配置界面中显示为一个按钮，点击后会在图像区域显示横线。可以为 int8 / int16 / int32 / int64 类型字段使用。

横线可以上下拖动。

支持以下参数：

- `min`: 横线的最小值
- `max`: 横线的最大值
- `minField`: 横线的最小值字段，当前 `block` 或 `struct` 的另外的字段名
- `maxField`: 横线的最大值字段，当前 `block` 或 `struct` 的另外的字段名

使用方法：

```mota
@draw_hline(min = 0, max = 100)
HLine hline;

@draw_hline(minField = "highCapLine")
HLine lowCapLine;

@draw_hline(maxField = "lowCapLine")
HLine highCapLine;
```

**纵线 draw_vline**

此注解将在配置界面中显示为一个按钮，点击后会在图像区域显示纵线。可以为 int8 / int16 / int32 / int64 类型字段使用。

纵线可以左右拖动。

支持以下参数：

- `min`: 纵线的最小值
- `max`: 纵线的最大值
- `minField`: 纵线的最小值字段，当前 `block` 或 `struct` 的另外的字段名
- `maxField`: 纵线的最大值字段，当前 `block` 或 `struct` 的另外的字段名

使用方法：

```mota
@draw_vline(min = 0, max = 100)
VLine vline;

@draw_vline(minField = "leftEdge")
VLine rightEdge;

@draw_vline(maxField = "rightEdge")
VLine leftEdge;
```

**整数输入 int**

此注解用于 int8 / int16 / int32 / int64 类型字段，用于显示一个整数输入框，并可扩展显示滑块和预览。

支持以下参数：

- `min`: 最小值
- `max`: 最大值
- `minField`: 最小值字段，当前 `block` 或 `struct` 的另外的字段名
- `maxField`: 最大值字段，当前 `block` 或 `struct` 的另外的字段名
- `step`: 步长
- `mode`: 显示模式，`slider` 表示显示滑块，`preview` 表示显示预览，`slider,preview` 表示同时显示滑块和预览， `input` 表示仅显示输入框，默认值为 `input`

使用方法：

```mota
@int(min = 0, max = 100, mode = "input")
int32 id;
```

**浮点数输入 float**

此注解用于 float32 / double64 类型字段，用于显示一个浮点数输入框，并可扩展显示滑块和预览。

支持以下参数：

- `min`: 最小值
- `max`: 最大值
- `minField`: 最小值字段，当前 `block` 或 `struct` 的另外的字段名
- `maxField`: 最大值字段，当前 `block` 或 `struct` 的另外的字段名
- `step`: 步长
- `precision`: 小数位数
- `mode`: 显示模式，`slider` 表示显示滑块，`preview` 表示显示预览，`slider,preview` 表示同时显示滑块和预览， `input` 表示仅显示输入框，默认值为 `input`

使用方法：

```mota
@float(min = 0.0, max = 100.0, mode = "input")
float64 value;
```

**文本输入 text**

此注解用于 string 类型字段，用于显示一个文本输入框。

支持以下参数：

- `max_length`: 最大长度
- `placeholder`: 占位符
- `regex`: 正则表达式

使用方法：

```mota
@text(max_length = 64, placeholder = "请输入名称", regex = "^\w+$")
string name;
```

**布尔开关 switcher**

此注解用于 bool 类型字段，用于显示一个布尔开关。

有以下几种显示模式：

- `checkbox`: 勾选框（默认）
- `button`: 双态按钮，用于显示两个状态的切换
- `switch`: 滑动开关

使用方法：

```mota
@switcher(mode = "switch")
bool enabled;
```

**选择 select**

此注解用于 string / enum class / int8 / int16 / int32 / int64 类型字段，用于显示一个下拉选择框。

支持以下参数：

- `enumClass`: 枚举类的名字
- `field`: 当前 `block` 或 `struct` 的另外的字段名，字段类型必须为 `repeated Option`

使用方法：

```mota
@select(enumClass = "CameraType")
string option;

repeated Option options;

@select(field = "options")
string option2;
```

**文件选择 file_dialog**

此注解用于 string 类型字段，用于显示一个文件选择框。

支持以下参数：

- `dirPath`: 文件夹路径
- `filter`: 文件过滤器，支持 `*`、`*.*`、`*.txt` 等格式

使用方法：

```mota
@file_dialog(dirPath = "${product_config_dir}/raw", filter = "*.txt")
string path;
```

**文件夹选择 folder_dialog**

此注解用于 string 类型字段，用于显示一个文件夹选择框。

支持以下参数：

- `dirPath`: 文件夹路径，为空则不限制

使用方法：

```mota
@folder_dialog(dirPath = "${config_dir}/raw")
string path;
```

### INI 文件特有注解

ini 文件支持 Group，用于将字段分组，表示为以下形式：

```ini
[MY_BLOCK]
id = 1
name = "test"
```

在 `mota` 中如此定义：

```mota
block MyBlock {
    @int(min = 0, max = 10000)
    int32 id = 0;
    @text(max_length = 64)
    string name = "";
}

@iniGroup(value = "MY_BLOCK")
MyBlock block;
```

INI 中分组，有以下几种情况：

1. **自定义类型**

```ini
[MY_BLOCK]
id = 1
name = "test"
```

在 `mota` 中如此定义：

```mota
block MyBlock {
    @int(min = 0, max = 10000)
    int32 id = 0;
    @text(max_length = 64)
    string name = "";
}

@iniGroup(value = "MY_BLOCK")
MyBlock block;
```

在 CPP 中使用：

```cpp
MyModel model;
model.block.id = 1;
model.block.name = "test";

model.save();
```

2. **map 类型**

```ini
[a]
int id = 1
string name = "test"

[b]
int id = 2
string name = "test2"
```

在 `mota` 中如此定义：

```mota
block MyBlock {
    @int(min = 0, max = 10000)
    int32 id = 0;
    @text(max_length = 64)
    string name = "";
}

@iniGroup()
map MyBlock blocks = ["a", "b"];
```

在 CPP 中使用：

```cpp
MyModel model;
model.blocks["a"].id = 1;
model.blocks["a"].name = "test";
model.blocks["b"].id = 2;
model.blocks["b"].name = "test2";

model.save();
```

3. **简单类型**

```ini
[DebugMode]
enable = true
```

在 `mota` 中如此定义：

```mota
@iniGroup(value = "DebugMode")
bool enable = false;
```

在 CPP 中使用：

```cpp
MyModel model;
model.enable = true;

model.save();
```

4. **数组类型**

数组类型无法定义多个 Group，仍然类似于简单类型

```ini
[camare_sn]
sn[0] = "123456"
sn[1] = "789012"
```

在 `mota` 中如此定义：

```mota
@iniGroup(value = "camera_sn")
repeated string sn;
```

在 CPP 中使用：

```cpp
MyModel model;
model.sn[0] = "123456";
model.sn[1] = "789012";

model.save();
```