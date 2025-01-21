# Mota 模型定义指南

本文档描述了 MOTA 项目中使用的模型注解格式。

## 结构体注解

结构体可以使用以下元数据进行注解：

```cpp
@[
    file = "${app_path}/device-base.cbor",  // 目标文件路径
    level = "global",                       // 作用域级别
    format = "cbor"                         // 数据格式
]
```

## 字段注解

结构体内的字段可以使用各种 UI 和验证元数据进行注解：

```cpp
@[
    ui = "draw_rectangle",     // UI 渲染类型
    max = 1.0,                // 最大值（用于数值类型）
    min = 0.3,                // 最小值（用于数值类型）
    max_length = 255,         // 最大长度（用于文本字段）
    min_field = "minHeight",  // 最小值引用字段（用于范围类型）
    max_field = "maxHeight",  // 最大值引用字段（用于范围类型）
    visible = true,           // 可见性标志（默认为 true）
    
    // 用于选择类型字段
    options = [
        {
            "value": "v1",
            "text": "1级",
            "help": "当级别是1级时选择",
            "enabled": true
        }
    ],
    options_field = "options" // 选项字段引用（必须是 `repeated OPTIONS` 类型）
]
```

### UI 类型

支持以下 UI 类型：

- `draw_rectangle`：矩形绘制
- `draw_circle`：圆形绘制
- `draw_hline`：水平线绘制
- `draw_vline`：垂直线绘制
- `range`：范围输入
- `number`：数值输入
- `text`：文本输入（仅用于字符串）
- `switcher`：布尔开关（仅用于布尔值）
- `select`：预定义选项选择

### 选项类型定义

对于使用动态选项的选择字段，OPTIONS 类型定义如下：

```cpp
// file: options.mota 不要忘记！！！

block OPTIONS {
    string value;    // 选项值
    string text;     // 显示文本
    string help;     // 帮助文本/描述
}
```