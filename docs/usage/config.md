# MOTA 项目配置

本文档介绍如何使用配置文件来管理MOTA项目的编译设置。

## 配置文件概述

MOTA支持使用JSON格式的配置文件来管理项目设置，避免每次都需要指定命令行参数。配置文件可以定义包含路径、多个项目配置等。

## 配置文件位置

MOTA会按以下顺序查找配置文件：

1. 命令行参数 `-c` 或 `--config` 指定的文件
2. 当前工作目录下的 `mota-config.json`
3. 如果都没有找到，则使用默认设置

## 配置文件结构

### 基本结构

```json
{
    "include_paths": [
        "path/to/include1",
        "path/to/include2"
    ],
    "projects": [
        {
            "source_dir": "src/",
            "output_dir": "generated/",
            "lang": "yima-cpp"
        }
    ]
}
```

### 字段说明

#### include_paths (可选)

全局包含路径数组，用于查找被包含的MOTA文件。

```json
{
    "include_paths": [
        "common/",
        "shared/types/",
        "mota-include/"
    ]
}
```

**特点：**
- 路径可以是相对路径或绝对路径
- 相对路径相对于配置文件所在目录
- 命令行的 `-i` 参数会追加到这个列表后面

#### projects (必需)

项目配置数组，每个项目定义一组编译设置。

```json
{
    "projects": [
        {
            "source_dir": "src/models/",
            "output_dir": "generated/models/",
            "lang": "yima-cpp"
        },
        {
            "source_dir": "src/api/",
            "output_dir": "generated/api/",
            "lang": "yima-cpp"
        }
    ]
}
```

**项目字段：**

| 字段 | 类型 | 必需 | 说明 | 默认值 |
|------|------|------|------|--------|
| `source_dir` | string | 是 | 源文件目录 | 无 |
| `output_dir` | string | 是 | 输出目录 | 无 |
| `lang` | string | 否 | 目标语言 | `"cpp"` |

## 使用示例

### 单项目配置

```json
{
    "include_paths": [
        "common/",
        "mota-include/"
    ],
    "projects": [
        {
            "source_dir": "src/",
            "output_dir": "generated/",
            "lang": "yima-cpp"
        }
    ]
}
```

### 多项目配置

```json
{
    "include_paths": [
        "common/types/",
        "shared/",
        "mota-include/"
    ],
    "projects": [
        {
            "source_dir": "src/models/",
            "output_dir": "generated/cpp/models/",
            "lang": "yima-cpp"
        },
        {
            "source_dir": "src/api/",
            "output_dir": "generated/cpp/api/",
            "lang": "yima-cpp"
        },
        {
            "source_dir": "test/",
            "output_dir": "generated/test/",
            "lang": "test"
        }
    ]
}
```

### 不同语言配置

```json
{
    "projects": [
        {
            "source_dir": "src/",
            "output_dir": "generated/cpp/",
            "lang": "yima-cpp"
        },
        {
            "source_dir": "src/",
            "output_dir": "generated/json/",
            "lang": "test"
        }
    ]
}
```

## 路径处理

### 相对路径

配置文件中的所有路径都相对于配置文件所在的目录：

```json
{
    "include_paths": [
        "../common/",      // 相对于配置文件的上级目录
        "./types/"         // 相对于配置文件所在目录
    ],
    "projects": [
        {
            "source_dir": "src/",
            "output_dir": "../build/generated/"
        }
    ]
}
```

### 绝对路径

也可以使用绝对路径：

```json
{
    "include_paths": [
        "/usr/local/include/mota/",
        "C:\\Program Files\\MOTA\\include\\"
    ],
    "projects": [
        {
            "source_dir": "/home/user/project/src/",
            "output_dir": "/home/user/project/build/"
        }
    ]
}
```

## 命令行交互

### 参数优先级

当同时使用配置文件和命令行参数时：

1. **互斥参数**：`-c` 与 `-o`、`-s`、`-l` 互斥
   ```bash
   # 错误：不能同时使用
   ./bin/mota.exe -c config.json -o output/
   
   # 正确：使用配置文件
   ./bin/mota.exe -c config.json
   
   # 正确：使用命令行参数
   ./bin/mota.exe src/ -o output/ -l yima-cpp
   ```

2. **包含路径叠加**：命令行的 `-i` 参数会追加到配置文件的 `include_paths` 后面
   ```bash
   # 配置文件中有 include_paths: ["common/"]
   # 命令行添加额外路径
   ./bin/mota.exe -c config.json -i extra/
   # 最终包含路径：["common/", "extra/"]
   ```

### 使用配置文件

```bash
# 使用指定配置文件
./bin/mota.exe -c my-config.json

# 使用当前目录的 mota-config.json（如果存在）
./bin/mota.exe

# 使用配置文件并添加额外包含路径
./bin/mota.exe -c config.json -i additional/path/

# 使用配置文件并显示详细输出
./bin/mota.exe -c config.json -v
```

## 配置验证

MOTA会验证配置文件的格式和内容：

### 常见错误

1. **JSON格式错误**
   ```
   Error: Invalid JSON in config file: mota-config.json
   Syntax error at line 5: missing comma
   ```

2. **缺少必需字段**
   ```
   Error: Missing required field 'projects' in config file
   ```

3. **路径不存在**
   ```
   Error: Source directory does not exist: src/nonexistent/
   ```

4. **语言不支持**
   ```
   Error: Unsupported language: unknown-lang
   ```

### 配置检查

使用详细模式检查配置：

```bash
./bin/mota.exe -c config.json -v
```

输出示例：
```
Loading config: mota-config.json
Include paths: ["common/", "mota-include/"]
Projects: 2
  Project 1: src/models/ -> generated/models/ (yima-cpp)
  Project 2: src/api/ -> generated/api/ (yima-cpp)
```

## 最佳实践

### 1. 项目结构组织

```
project/
├── mota-config.json          # 主配置文件
├── src/
│   ├── models/              # 数据模型
│   ├── api/                 # API定义
│   └── common/              # 公共类型
├── generated/               # 生成的代码
└── include/                 # 外部包含文件
```

### 2. 配置文件模板

```json
{
    "include_paths": [
        "include/",
        "common/",
        "mota-include/"
    ],
    "projects": [
        {
            "source_dir": "src/models/",
            "output_dir": "generated/models/",
            "lang": "yima-cpp"
        },
        {
            "source_dir": "src/api/",
            "output_dir": "generated/api/",
            "lang": "yima-cpp"
        }
    ]
}
```

### 3. 环境特定配置

为不同环境创建不同的配置文件：

```bash
# 开发环境
mota-config.dev.json

# 生产环境
mota-config.prod.json

# 测试环境
mota-config.test.json
```

使用时指定：
```bash
./bin/mota.exe -c mota-config.dev.json
```

### 4. 版本控制

- 将 `mota-config.json` 加入版本控制
- 将 `generated/` 目录加入 `.gitignore`
- 为团队成员提供统一的配置

```gitignore
# .gitignore
generated/
*.generated.*
```

## 集成示例

### 与构建系统集成

**Makefile:**
```makefile
.PHONY: generate clean

generate:
	./bin/mota.exe -c mota-config.json -v

clean:
	rm -rf generated/

build: generate
	# 编译生成的代码
	g++ -I generated/ src/*.cpp generated/**/*.cpp -o app
```

**xmake:**
```lua
-- xmake.lua
task("generate")
    on_run(function ()
        os.exec("./bin/mota.exe -c mota-config.json")
    end)
    set_menu {
        usage = "xmake generate",
        description = "Generate code from MOTA files"
    }

-- 在构建前自动生成代码
before_build(function (target)
    os.exec("./bin/mota.exe -c mota-config.json")
end)
```

### CI/CD 集成

```yaml
# .github/workflows/build.yml
name: Build
on: [push, pull_request]

jobs:
  build:
    runs-on: ubuntu-latest
    steps:
    - uses: actions/checkout@v2
    
    - name: Generate MOTA code
      run: ./bin/mota.exe -c mota-config.json -v
    
    - name: Build project
      run: make build
```

## 故障排除

### 常见问题

1. **配置文件找不到**
   - 检查文件名是否正确（`mota-config.json`）
   - 确认文件在当前工作目录中
   - 使用 `-c` 参数指定完整路径

2. **路径解析错误**
   - 使用正斜杠 `/` 而不是反斜杠 `\`
   - 在Windows上使用双反斜杠 `\\` 或正斜杠 `/`
   - 检查相对路径是否正确

3. **权限问题**
   - 确保对输出目录有写权限
   - 检查包含路径的读权限

4. **编码问题**
   - 确保配置文件使用UTF-8编码
   - 避免在路径中使用特殊字符 