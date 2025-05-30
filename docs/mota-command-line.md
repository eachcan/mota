# MOTA 命令行

目前 mota 仅支持 Windows 10 及以上版本。


## 1. 安装

前往 [Releases](https://github.com/eachcan/mota/releases) 页面下载最新版本的 mota 命令行工具。

将下载的 mota-{version}.zip 解压到任意目录，然后将该目录添加到系统 PATH 环境变量中。

示例：

```cmd
set PATH=%PATH%;C:\path\to\mota-{version}
```

## 2. 使用

```cmd
mota --help
```

输出：

```
mota [OPTIONS] [FILE] [...]

  mota 是一个配置文件编译器，类似于 Protocol Buffers，但主要用于配置文件描述类的编译。

Options:
  -h, --help      显示帮助信息
  -v, --version   显示版本信息
  -i, --include-path PATH
                  添加包含路径，可以指定多次。如果使用了 mota-config.json，本参数会在 mota-config.json 的 include_paths 基础上增加。
  -o, --output-dir PATH
                  设置输出目录，默认为 `output`，指定则忽略 -c 参数
  -s, --source-dir PATH
                  设置源文件目录，默认为当前目录，指定则忽略 -c 参数
  -l, --lang LANG
                  设置输出语言，可选值：cpp[默认]
  -c, --config PATH
                  设置配置文件路径。
                  本参数和 -o / -s / -l 互斥，配置文件中源文件和输出目录是可以多组的。
                  如果当前目录存在 mota-config.json，则会自动加载。

FILE
    指定要编译的 Mota 文件或目录路径，如果未指定，则从当前目录开始搜索，不会递归搜索。
```

**include-path**

添加包含路径，可以指定多次。

示例：

```cmd
mota --include-path C:\path\to\include --include-path C:\path\to\include2
```

**output-dir**

设置输出目录。

注意： `namespace` 不会影响输出目录。如果有多个 `namespace`，并按照 `namespace` 选择目录，需要执行多次。或通过配置文件指定。

示例：

```cmd
mota --output-dir C:\path\to\output
```
