# Mota 构建说明

本文档说明如何构建和打包 Mota 编译器。

## 构建目标

### 1. 基本构建
```bash
xmake
```
- 编译 `mota.exe` 到 `bin/` 目录
- 这是最基本的构建命令

### 2. 安装包目录 (推荐用于开发)
```bash
xmake run install
```
- 创建 `mota-install/` 目录
- 包含 `mota.exe` 和所有运行时依赖
- 包含 `mota-include/`、`template/`、`examples/` 目录
- 包含文档文件和安装说明
- 适合本地测试和开发使用

### 3. ZIP 压缩包 (推荐用于分发)
```bash
xmake run package
```
- 先运行 install 目标
- 生成 `mota-v0.2.0-windows-x64.zip` (约 0.88 MB)
- 包含完整的可分发安装包
- 用户解压后即可使用

### 4. Windows 安装器 (专业分发)
```bash
xmake run installer
```
- 需要安装 NSIS (Nullsoft Scriptable Install System)
- 生成 `mota-installer-v0.2.0.exe` (约 0.76 MB)
- 专业的 Windows 安装程序，包含以下功能：
  - 安装到 `C:\Program Files\Mota`
  - 自动添加到系统 PATH 环境变量
  - 设置 `MOTA_INCLUDE` 环境变量
  - 创建开始菜单快捷方式
  - 创建桌面快捷方式
  - 在"添加或删除程序"中注册
  - 包含完整的卸载功能

## 生成的文件

### 目录结构
```
mota-install/
├── mota.exe                 # 主程序
├── *.dll                   # 运行时依赖库
├── mota-include/           # 内置类型定义
├── template/               # 代码生成模板
├── examples/               # 示例文件
├── README.md              # 项目说明
├── LICENSE                # 许可证
└── INSTALL.md             # 安装说明
```

### 分发文件
- `mota-v0.2.0-windows-x64.zip` - ZIP 压缩包
- `mota-installer-v0.2.0.exe` - Windows 安装器

## 依赖要求

### 编译依赖
- Visual Studio 2022 (或兼容的 MSVC 编译器)
- xmake 构建系统

### 安装器依赖 (可选)
- NSIS (Nullsoft Scriptable Install System)
  - 下载地址: https://nsis.sourceforge.io/Download
  - 安装到默认位置即可

## 使用建议

1. **开发测试**: 使用 `xmake run install`
2. **简单分发**: 使用 `xmake run package` 生成 ZIP 文件
3. **专业分发**: 使用 `xmake run installer` 生成 Windows 安装器

## 环境变量

安装器会设置以下环境变量：
- `PATH`: 添加 mota.exe 所在目录
- `MOTA_INCLUDE`: 指向 `C:\Program Files\Mota\mota-include`

用户可以在项目中使用：
- mota-config.json: `%MOTA_INCLUDE%`
- CMakeLists.txt: `$ENV{MOTA_INCLUDE}/cpp`
- Makefile: `$(MOTA_INCLUDE)/cpp`

## 版本信息

当前版本: 0.2.0
构建时间: 自动生成 