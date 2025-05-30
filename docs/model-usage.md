# 模型使用说明

## 1. 定义 mota 文件

```mota
include "yima.mota";
include "yima-ui.mota";

namespace yima.core;

struct ProductInfo {
    @yima.ui.Text(max_length = 64, desc = "产品名称")
    string name;
}

```