# Mota Windows 安装器

这个目录包含用于生成 Mota Windows 安装程序的脚本和配置。

## 前置要求

### 安装 NSIS

1. 下载 NSIS：https://nsis.sourceforge.io/Download
2. 安装到默认位置（通常是 `C:\Program Files (x86)\NSIS\` 或 `C:\Program Files\NSIS\`）
3. 确保 `makensis.exe` 可以在命令行中访问

### 验证安装

```bash
# 检查 NSIS 是否正确安装
where makensis
```

## 生成安装器

在项目根目录运行：

```bash
# 生成 Windows 安装器
xmake run installer
```

这个命令会：

1. 构建 mota.exe
2. 创建安装包目录结构
3. 使用 NSIS 编译安装器
4. 生成 `mota-installer-v0.2.0.exe`

## 安装器功能

生成的安装器具有以下功能：

### 安装功能
- ✅ 安装到 `C:\Program Files\Mota`
- ✅ 复制 `mota.exe` 和相关 DLL
- ✅ 复制 `mota-include/` 目录（内置类型定义）
- ✅ 复制 `template/` 目录（代码生成模板）
- ✅ 复制 `examples/` 目录（示例文件）
- ✅ 添加 mota.exe 到系统 PATH 环境变量
- ✅ 设置 MOTA_INCLUDE 环境变量指向 mota-include 目录
- ✅ 创建开始菜单快捷方式
- ✅ 创建桌面快捷方式
- ✅ 在"添加或删除程序"中注册

### 卸载功能
- ✅ 从系统 PATH 中移除
- ✅ 删除 MOTA_INCLUDE 环境变量
- ✅ 删除所有安装的文件和目录
- ✅ 删除快捷方式
- ✅ 清理注册表项
- ✅ 完全卸载确认

## 文件说明

- `mota-installer.nsi` - NSIS 安装脚本
- `LICENSE` - 许可证文件（安装时复制）

## 安装器特性

### 用户界面
- 现代化的安装界面
- 中文界面支持
- 许可证协议页面
- 安装目录选择
- 安装进度显示
- 完成页面（可选择立即运行）

### 系统集成
- 管理员权限要求
- 系统环境变量修改
- 注册表集成
- 开始菜单集成
- 桌面快捷方式

### 安全性
- 数字签名支持（需要代码签名证书）
- 文件完整性检查
- 覆盖安装保护

## 故障排除

### NSIS 未找到
```
❌ NSIS not found!
💡 Please install NSIS from https://nsis.sourceforge.io/
```

**解决方案：**
1. 从官网下载并安装 NSIS
2. 确保安装到标准位置
3. 重启命令行窗口

### 权限错误
如果安装器需要管理员权限，请：
1. 右键点击安装器
2. 选择"以管理员身份运行"

### PATH 环境变量
安装后，您可能需要：
1. 重启命令行窗口
2. 或者注销并重新登录
3. 验证：`mota --help`

### MOTA_INCLUDE 环境变量
安装器会自动设置 `MOTA_INCLUDE` 环境变量，用于：

**在 mota-config.json 中使用：**
```json
{
  "includePath": [
    "%MOTA_INCLUDE%",
    "custom/include/path"
  ]
}
```

**在 C++ 项目中使用：**
```cmake
# CMakeLists.txt
include_directories($ENV{MOTA_INCLUDE}/cpp)
```

```makefile
# Makefile
CPPFLAGS += -I$(MOTA_INCLUDE)/cpp
```

**验证环境变量：**
```cmd
echo %MOTA_INCLUDE%
# 应该输出: C:\Program Files\Mota\mota-include
```

## 开发说明

### 修改安装器
1. 编辑 `mota-installer.nsi`
2. 运行 `xmake run installer` 重新生成
3. 测试安装和卸载过程

### 版本更新
更新版本号时，需要修改：
1. `xmake.lua` 中的版本号
2. `mota-installer.nsi` 中的 `PRODUCT_VERSION`

### 添加文件
要添加新文件到安装器：
1. 在 `mota-installer.nsi` 的 `Section "主程序"` 中添加 `File` 指令
2. 在 `Section Uninstall` 中添加对应的 `Delete` 指令 