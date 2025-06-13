# MOTA 命令行使用指南

本文档详细介绍MOTA命令行工具的使用方法。

## 安装

### 从源码构建

```bash
# 克隆项目
git clone https://github.com/your-repo/mota.git
cd mota

# 使用xmake构建
xmake

# 构建完成后，可执行文件位于 bin/mota.exe
```

### 使用预编译版本

前往 [Releases](https://github.com/eachcan/mota/releases) 页面下载最新版本的mota命令行工具。

将下载的文件解压到任意目录，然后将该目录添加到系统PATH环境变量中。

## 基本语法

```bash
mota [OPTIONS] [FILE] [...]
```

## 命令行选项

### 基本选项

| 选项 | 长选项 | 说明 |
|------|--------|------|
| `-h` | `--help` | 显示帮助信息 |
| `-V` | `--version` | 显示版本信息 |
| `-v` | `--verbose` | 显示详细信息（调试输出） |

### 路径选项

| 选项 | 长选项 | 说明 | 默认值 |
|------|--------|------|--------|
| `-i PATH` | `--include-path PATH` | 添加包含路径，可指定多次 | 无 |
| `-o PATH` | `--output-dir PATH` | 设置输出目录 | `output` |
| `-s PATH` | `--source-dir PATH` | 设置源文件目录 | 当前目录 |

### 生成选项

| 选项 | 长选项 | 说明 | 默认值 |
|------|--------|------|--------|
| `-l LANG` | `--lang LANG` | 设置输出语言 | `cpp` |
| `-c PATH` | `--config PATH` | 设置配置文件路径 | 自动查找 |

### 文件参数

`FILE` - 指定要编译的MOTA文件或目录路径
- 如果未指定，则从当前目录开始搜索
- 不会递归搜索子目录
- 可以指定多个文件或目录

## 使用示例

### 基本使用

```bash
# 编译单个文件，输出到默认目录
./bin/mota.exe user.mota

# 编译单个文件，指定输出目录
./bin/mota.exe user.mota -o generated/

# 编译整个目录
./bin/mota.exe src/ -o output/
```

### 指定语言

```bash
# 生成C++代码
./bin/mota.exe user.mota -l yima-cpp -o cpp_output/

# 生成JSON（用于测试）
./bin/mota.exe user.mota -l test -o json_output/
```

### 使用包含路径

```bash
# 添加单个包含路径
./bin/mota.exe user.mota -i common/

# 添加多个包含路径
./bin/mota.exe user.mota -i common/ -i shared/ -i libs/
```

### 详细输出

```bash
# 显示详细的编译过程信息
./bin/mota.exe user.mota -v -o output/
```

### 使用配置文件

```bash
# 使用指定的配置文件
./bin/mota.exe -c my-config.json

# 如果当前目录存在 mota-config.json，会自动加载
./bin/mota.exe user.mota
```

## 输出控制

### 默认输出

默认情况下，MOTA只显示关键信息：
- 错误信息
- 正在处理的文件名
- 处理结果
- 完成统计

```
Language: yima-cpp
Processing: examples/user.mota
Generated: output/com/example/user.h
Processing: examples/store.mota
Generated: output/com/example/store.h
Completed: 2/2 files processed successfully.
```

### 详细输出

使用 `-v` 或 `--verbose` 参数显示详细的调试信息：
- 包含文件处理过程
- 语法检查状态
- 模板引擎初始化
- 代码生成详细步骤

```bash
./bin/mota.exe user.mota -v
```

输出示例：
```
Starting mota compiler...
Arguments count: 3
  arg[0]: ./bin/mota.exe
  arg[1]: user.mota
  arg[2]: -v
Parsed options:
  outputDir: output
  lang: yima-cpp
  files count: 1
    file: user.mota
exeDir: D:\project\eachcan\mota\bin
处理文件: user.mota
输出目录: output
模板目录: D:\project\eachcan\mota\bin\template\yima-cpp
[DEBUG] 开始构建声明注册表...
[DEBUG] 声明注册表构建完成，包含 5 个声明
[DEBUG] 开始设置声明注册表...
[DEBUG] 声明注册表设置完成
[DEBUG] 命名空间设置完成
[DEBUG] 准备获取配置...
[DEBUG] 配置获取成功
[DEBUG] 找到 1 个文件路径配置
[DEBUG] 处理文件路径: file
[DEBUG] 开始构建模板变量...
[DEBUG] 模板变量构建完成
[DEBUG] 开始渲染模板: file
Loaded 25 misc fragments from misc-common.template
Loaded 2 misc fragments from misc-namespace.template
Loaded 13 misc fragments from misc-accessors.template
Loaded 1 misc fragments from misc-serialization.template
Loaded 4 misc fragments from misc-declarations.template
Total misc fragments loaded: 45
[DEBUG] 模板渲染完成，结果长度: 8234
[DEBUG] generateCode 返回，长度: 8234
已生成到: output/com/example/user.h
生成完成: user.mota
Completed: 1/1 files processed successfully.
```

## 错误处理

### 常见错误

1. **文件不存在**
   ```
   Error: File not found: user.mota
   ```

2. **语法错误**
   ```
   Error: Syntax error in user.mota:15:3
   Expected ';' after field declaration
   ```

3. **类型未定义**
   ```
   Error: Unknown type 'CustomType' in user.mota:10:5
   ```

4. **循环引用**
   ```
   Error: Circular include detected: a.mota -> b.mota -> a.mota
   ```

### 调试技巧

1. **使用详细输出**：添加 `-v` 参数查看详细的处理过程
2. **检查包含路径**：确保所有依赖文件都在包含路径中
3. **验证语法**：使用简单的测试文件验证语法规则
4. **查看生成的JSON**：使用 `-l test` 生成JSON格式查看解析结果

## 配置文件

当使用 `-c` 参数或当前目录存在 `mota-config.json` 时，MOTA会使用配置文件。

配置文件的详细说明请参考：[项目配置](config.md)

## 注意事项

1. **命名空间不影响输出目录**：输出目录结构由命名空间决定，不受 `-o` 参数影响
2. **包含路径优先级**：命令行指定的包含路径会添加到配置文件指定的路径之后
3. **参数互斥**：`-c` 参数与 `-o`、`-s`、`-l` 参数互斥
4. **文件搜索**：如果不指定文件，只搜索当前目录，不递归搜索子目录

## 性能优化

1. **并行处理**：MOTA会自动并行处理多个文件
2. **增量编译**：只重新生成修改过的文件（计划中的功能）
3. **缓存机制**：模板和配置会被缓存以提高性能

## 集成到构建系统

### Makefile

```makefile
# 生成代码
generate:
	./bin/mota.exe src/ -o generated/ -l yima-cpp

# 清理生成的文件
clean-generated:
	rm -rf generated/

.PHONY: generate clean-generated
```

### CMake

```cmake
# 添加自定义命令生成代码
add_custom_command(
    OUTPUT ${CMAKE_BINARY_DIR}/generated/timestamp
    COMMAND ${CMAKE_SOURCE_DIR}/bin/mota.exe 
            ${CMAKE_SOURCE_DIR}/src/ 
            -o ${CMAKE_BINARY_DIR}/generated/ 
            -l yima-cpp
    COMMAND ${CMAKE_COMMAND} -E touch ${CMAKE_BINARY_DIR}/generated/timestamp
    DEPENDS ${CMAKE_SOURCE_DIR}/src/*.mota
    COMMENT "Generating code from MOTA files"
)

add_custom_target(generate_mota DEPENDS ${CMAKE_BINARY_DIR}/generated/timestamp)
```

### xmake

```lua
-- 添加MOTA代码生成任务
task("generate")
    on_run(function ()
        os.exec("./bin/mota.exe src/ -o generated/ -l yima-cpp")
    end)
    set_menu {
        usage = "xmake generate",
        description = "Generate code from MOTA files"
    }
``` 