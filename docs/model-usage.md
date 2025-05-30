# 模型使用说明

## 1. 定义 mota 文件

**product.mota**
```mota
include "yima.mota";
include "yima-ui.mota";

namespace yima.core;

struct ProductInfo {
    @yima.ui.Text(max_length = 64, desc = "产品名称")
    string name;
}

```

## 2. 生成 C++ 代码

```bash
mota -i examples/product.mota -o examples/generated -b examples/generated
```

mota 将每个 .mota 文件生成对应的 .h 和 .cpp 文件。

以上代码会生成以下文件：

- examples/generated/product.h
- examples/generated/product.cpp

**product.h**
```cpp
#include "yima.h"
#include "yima-ui.h"

namespace yima.core;

class ProductInfo : public Model {
public:
   QString name;
};
```