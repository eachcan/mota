-- 设置项目名称和版本
set_version("0.2.0")

-- 添加构建模式
add_rules("mode.debug", "mode.release")

-- 设置C++标准
set_languages("c++20")

-- 设置UTF-8编码
add_defines("_UNICODE", "UNICODE")
add_cxxflags("/utf-8")
add_cxflags("/utf-8")

-- 添加包依赖
add_requires("gtest")
add_requires("cxxopts")
add_requires("nlohmann_json")
set_encodings("utf-8")

-- 主要目标：编译器
target("mota")
    -- 设置为可执行程序
    set_kind("binary")
    -- 生成版本头文件
    before_build(function (target)
        local version = target:version()
        local version_h = io.readfile("include/version.h.in")
        version_h = version_h:gsub("${VERSION}", version)
        io.writefile("include/version.h", version_h)
    end)
    -- 添加源文件
    add_files("src/*.cpp")
    
    -- 添加头文件目录
    add_includedirs("include", "framework", "mota-include/cpp")
    add_frameworks("QtCore", "QtGui", "QtWidgets")
    
    -- 添加依赖包
    add_packages("cxxopts")
    add_packages("nlohmann_json")
    
    -- Debug模式下添加调试信息
    if is_mode("debug") then
        add_defines("DEBUG")
        set_symbols("debug")
        set_optimize("none")
    end
    
    -- Release模式下开启优化
    if is_mode("release") then
        set_symbols("hidden")
        set_optimize("fastest")
        set_strip("all")
    end
    
    -- 设置输出目录
    set_targetdir("bin")
    

-- 测试目标：词法分析器测试
target("test_lexer")
    -- 设置为可执行程序
    set_kind("binary")
    
    -- 添加源文件
    add_files("test/test_lexer.cpp")
    add_files("src/lexer_core.cpp")
    add_files("src/lexer_utils.cpp")
    add_files("src/lexer_tokens.cpp")
    add_files("src/lexer_literals.cpp")
    add_files("src/lexer_comments.cpp")
    
    -- 添加头文件目录
    add_includedirs("include", "framework")
    
    -- 添加Google Test依赖
    add_packages("gtest", {configs = {main = true}})
    
    -- 设置输出目录
    set_targetdir("bin")
    
    -- 添加测试定义
    add_defines("TESTING")

-- 测试目标：解析器测试
target("test_parser")
    -- 设置为可执行程序
    set_kind("binary")
    
    -- 添加源文件
    add_files("test/test_parser.cpp")
    add_files("src/lexer_core.cpp")
    add_files("src/lexer_utils.cpp")
    add_files("src/lexer_tokens.cpp")
    add_files("src/lexer_literals.cpp")
    add_files("src/lexer_comments.cpp")
    add_files("src/parser_core.cpp")
    add_files("src/parser_declarations.cpp")
    add_files("src/parser_types.cpp")
    add_files("src/parser_expressions.cpp")
    
    -- 添加头文件目录
    add_includedirs("include", "framework")
    
    -- 添加Google Test依赖
    add_packages("gtest", {configs = {main = true}})
    
    -- 设置输出目录
    set_targetdir("bin")
    
    -- 添加测试定义
    add_defines("TESTING")

-- 测试目标：数组字面量测试
target("test_array_literal")
    -- 设置为可执行程序
    set_kind("binary")
    
    -- 添加源文件
    add_files("test/test_array_literal.cpp")
    add_files("src/lexer_core.cpp")
    add_files("src/lexer_utils.cpp")
    add_files("src/lexer_tokens.cpp")
    add_files("src/lexer_literals.cpp")
    add_files("src/lexer_comments.cpp")
    add_files("src/parser_core.cpp")
    add_files("src/parser_declarations.cpp")
    add_files("src/parser_types.cpp")
    add_files("src/parser_expressions.cpp")
    
    -- 添加头文件目录
    add_includedirs("include", "framework")
    
    -- 添加Google Test依赖
    add_packages("gtest", {configs = {main = true}})
    
    -- 设置输出目录
    set_targetdir("bin")
    
    -- 添加测试定义
    add_defines("TESTING")

-- 测试目标：注解字段类型验证测试
target("test_annotation_field_type_validation")
    -- 设置为可执行程序
    set_kind("binary")
    
    -- 添加源文件
    add_files("test/test_annotation_field_type_validation.cpp")
    add_files("src/lexer_core.cpp")
    add_files("src/lexer_utils.cpp")
    add_files("src/lexer_tokens.cpp")
    add_files("src/lexer_literals.cpp")
    add_files("src/lexer_comments.cpp")
    add_files("src/parser_core.cpp")
    add_files("src/parser_declarations.cpp")
    add_files("src/parser_types.cpp")
    add_files("src/parser_expressions.cpp")
    add_files("src/syntax_checker.cpp")
    
    -- 添加头文件目录
    add_includedirs("include", "framework")
    
    -- 添加Google Test依赖
    add_packages("gtest", {configs = {main = true}})
    
    -- 设置输出目录
    set_targetdir("bin")
    
    -- 添加测试定义
    add_defines("TESTING")

-- 添加一个测试组，方便一键运行所有测试
target("test")
    set_kind("phony")
    on_run(function ()
        -- 构建所有测试
        os.exec("xmake build test_lexer")
        os.exec("xmake build test_parser")
        os.exec("xmake build test_array_literal")
        os.exec("xmake build test_annotation_field_type_validation")
        
        -- 运行所有测试
        print("\nRunning lexer tests...")
        os.exec("xmake run test_lexer")
        
        print("\nRunning parser tests...")
        os.exec("xmake run test_parser")
        
        print("\nRunning array literal tests...")
        os.exec("xmake run test_array_literal")
        
        print("\nRunning annotation field type validation tests...")
        os.exec("xmake run test_annotation_field_type_validation")
    end)

-- syntax_checker 测试
target("test_syntax_checker")
    set_kind("binary")
    add_files("test/test_syntax_checker.cpp")
    add_includedirs("include")
    add_files("src/*.cpp")
    remove_files("src/main.cpp")  -- 排除主程序的main函数
    add_packages("gtest")
    add_packages("nlohmann_json")
    set_encodings("utf-8")
    set_targetdir("bin")

-- 生成器测试
target("test_generator")
    set_kind("binary")
    add_files("test/test_generator.cpp")
    add_files("src/lexer_*.cpp")
    add_files("src/parser_*.cpp")  
    add_files("src/generator_*.cpp")
    add_files("src/config.cpp")
    add_files("src/template_engine.cpp")
    add_includedirs("include")
    add_packages("gtest", {configs = {main = true}})
    add_packages("nlohmann_json")
    set_encodings("utf-8")
    set_targetdir("bin")

-- 安装目标：生成完整的安装包
target("install")
    set_kind("phony")
    on_run(function ()
        import("core.project.config")
        import("lib.detect.find_tool")
        
        -- 确保主程序已构建
        print("Building mota.exe...")
        os.exec("xmake build mota")
        
        -- 创建安装目录
        local install_dir = "mota-install"
        print("Creating install directory: " .. install_dir)
        os.rm(install_dir)  -- 清理旧的安装目录
        os.mkdir(install_dir)
        
        -- 复制主程序
        print("Copying mota.exe...")
        os.cp("bin/mota.exe", install_dir .. "/")
        
        -- 复制相关DLL（如果存在）
        print("Copying DLL files...")
        local dll_patterns = {"*.dll", "Qt*.dll", "msvcp*.dll", "vcruntime*.dll"}
        for _, pattern in ipairs(dll_patterns) do
            local dll_files = os.files("bin/" .. pattern)
            for _, dll_file in ipairs(dll_files) do
                local filename = path.filename(dll_file)
                print("  Copying " .. filename)
                os.cp(dll_file, install_dir .. "/" .. filename)
            end
        end
        
        -- 检查系统DLL依赖（Windows）
        if is_plat("windows") then
            print("Checking for system DLL dependencies...")
            -- 可以使用dependency walker或类似工具来检查依赖
            -- 这里我们手动复制一些常见的运行时库
            local system_paths = {
                "C:/Windows/System32/",
                "C:/Windows/SysWOW64/",
                os.getenv("VCINSTALLDIR") and (os.getenv("VCINSTALLDIR") .. "Redist/MSVC/*/x64/Microsoft.VC*.CRT/"),
                os.getenv("PROGRAMFILES") and (os.getenv("PROGRAMFILES") .. "/Microsoft Visual Studio/*/VC/Redist/MSVC/*/x64/Microsoft.VC*.CRT/")
            }
            
            local runtime_dlls = {
                "msvcp140.dll",
                "vcruntime140.dll", 
                "vcruntime140_1.dll",
                "api-ms-win-crt-runtime-l1-1-0.dll"
            }
            
            for _, dll in ipairs(runtime_dlls) do
                for _, sys_path in ipairs(system_paths) do
                    if sys_path then
                        local dll_path = sys_path .. dll
                        if os.isfile(dll_path) then
                            print("  Copying system DLL: " .. dll)
                            os.cp(dll_path, install_dir .. "/" .. dll)
                            break
                        end
                    end
                end
            end
        end
        
        -- 复制mota-include目录
        print("Copying mota-include directory...")
        os.cp("mota-include", install_dir .. "/mota-include")
        
        -- 复制template目录
        print("Copying template directory...")
        os.cp("template", install_dir .. "/template")
        
        -- 复制examples目录
        print("Copying examples directory...")
        os.cp("examples", install_dir .. "/examples")
        
        -- 复制README和LICENSE
        print("Copying documentation...")
        if os.isfile("README.md") then
            os.cp("README.md", install_dir .. "/README.md")
        end
        if os.isfile("LICENSE") then
            os.cp("LICENSE", install_dir .. "/LICENSE")
        end

        local project = import("core.project.project")
        -- 创建安装说明文件
        print("Creating installation guide...")
        local install_guide = [[
# Mota 安装包

这是 Mota 编译器的完整安装包。

## 目录结构

- `mota.exe` - 主程序
- `*.dll` - 运行时依赖库
- `mota-include/` - 内置类型定义文件
- `template/` - 代码生成模板
- `examples/` - 示例文件

## 使用方法

1. 将整个目录复制到您希望安装的位置
2. 可以将 mota.exe 所在目录添加到系统 PATH 环境变量中
3. 运行 `mota.exe --help` 查看使用说明

## 示例

```bash
# 编译示例文件
mota.exe examples/simple.mota

# 指定输出目录
mota.exe examples/simple.mota -o my_output

# 查看帮助
mota.exe --help
```

## 版本信息

版本: ]] .. project:version() .. [[

构建时间: ]] .. os.date("%Y-%m-%d %H:%M:%S") .. [[

]]
        
        io.writefile(install_dir .. "/INSTALL.md", install_guide)
        
        print("\n✅ Installation package created successfully!")
        print("📁 Location: " .. path.absolute(install_dir))
        print("📦 Contents:")
        print("   - mota.exe (main executable)")
        print("   - Runtime DLL files")
        print("   - mota-include/ (built-in type definitions)")
        print("   - template/ (code generation templates)")
        print("   - examples/ (example files)")
        print("   - Documentation files")
        print("\n🚀 You can now distribute the '" .. install_dir .. "' directory as a complete installation package.")
    end)

-- 打包目标：生成压缩包
target("package")
    set_kind("phony")
    on_run(function ()
        -- 首先运行install目标
        print("Creating installation package...")
        os.exec("xmake run install")
        
        local project = import("core.project.project")
        -- 创建压缩包
        local install_dir = "mota-install"
        local package_name = "mota-v" .. project:version() .. "-windows-x64.zip"
        
        print("\nCreating ZIP package...")
        
        -- 使用PowerShell创建ZIP文件
        local powershell_cmd = string.format(
            "Compress-Archive -Path '%s\\*' -DestinationPath '%s' -Force",
            install_dir, package_name
        )
        
        print("Running: powershell -Command \"" .. powershell_cmd .. "\"")
        local ret = os.exec("powershell -Command \"" .. powershell_cmd .. "\"")
        
        -- 检查文件是否实际创建成功，而不依赖返回值
        if os.isfile(package_name) then
            print("✅ ZIP package created successfully!")
            print("📦 Package: " .. package_name)
            
            -- 显示文件大小
            if os.isfile(package_name) then
                local file_size = os.filesize(package_name)
                if file_size then
                    local size_mb = math.floor(file_size / 1024 / 1024 * 100) / 100
                    print("📏 Size: " .. size_mb .. " MB")
                end
            end
            
            print("\n🚀 Ready for distribution!")
        else
            print("❌ Failed to create ZIP package")
            print("💡 You can manually create a ZIP file from the '" .. install_dir .. "' directory")
                 end
     end)

-- 安装器目标：生成Windows安装程序
target("installer")
    set_kind("phony")
    on_run(function ()
        -- 首先运行install目标
        print("Creating installation package...")
        os.exec("xmake run install")
        
        -- 检查NSIS是否可用
        local nsis_path = nil
        local possible_paths = {
            "C:\\Program Files (x86)\\NSIS\\makensis.exe",
            "C:\\Program Files\\NSIS\\makensis.exe",
            "makensis.exe"  -- 如果在PATH中
        }
        
        for _, path in ipairs(possible_paths) do
            if os.isfile(path) then
                nsis_path = path
                break
            end
        end
        
        -- 如果在固定路径中没找到，跳过PATH检查，直接显示错误信息
        
        if not nsis_path then
            print("\n❌ NSIS (Nullsoft Scriptable Install System) not found!")
            print("💡 To create Windows installer, please install NSIS:")
            print("   1. Download from: https://nsis.sourceforge.io/Download")
            print("   2. Install to default location")
            print("   3. Restart command prompt")
            print("   4. Run 'xmake run installer' again")
            print("\n📋 Alternative: Use 'xmake run package' to create ZIP distribution")
            print("📁 Current install package available at: mota-install/")
            return
        end
        
        print("✅ Found NSIS: " .. nsis_path)
        
        -- 确保installer目录存在
        if not os.isfile("installer\\mota-installer-en.nsi") then
            print("❌ installer directory not found!")
            print("💡 Please ensure installer/mota-installer-en.nsi exists")
            return
        end
        
        -- 复制LICENSE文件到installer目录（NSIS需要）
        if os.isfile("LICENSE") then
            os.cp("LICENSE", "installer/LICENSE")
        end
        
        -- 编译NSIS脚本
        print("Building Windows installer...")
        local nsis_script = "installer\\mota-installer-en.nsi"
        local nsis_cmd = string.format('"%s" "%s"', nsis_path, nsis_script)
        print("Running: " .. nsis_cmd)
        
        local ret = os.exec(nsis_cmd)
        
        -- 检查安装程序是否实际生成，而不依赖返回值
        local project = import("core.project.project")
        local installer_file = "installer/mota-installer-v" .. project:version() .. ".exe"
        if os.isfile(installer_file) then
            print("✅ Windows installer created successfully!")
            print("📦 Installer: " .. installer_file)
            
            -- 显示文件大小
            local file_size = os.filesize(installer_file)
            if file_size then
                local size_mb = math.floor(file_size / 1024 / 1024 * 100) / 100
                print("📏 Size: " .. size_mb .. " MB")
            end
            
            -- 移动到项目根目录
            local final_name = "mota-installer-v" .. project:version() .. ".exe"
            os.cp(installer_file, final_name)
            print("📁 Final location: " .. path.absolute(final_name))
            
            print("\n🚀 Windows installer ready for distribution!")
            print("📋 Features:")
            print("   ✓ Installs to C:\\Program Files\\Mota")
            print("   ✓ Adds mota.exe to system PATH")
            print("   ✓ Sets MOTA_INCLUDE environment variable")
            print("   ✓ Creates Start Menu shortcuts")
            print("   ✓ Creates Desktop shortcut")
            print("   ✓ Includes uninstaller")
            print("   ✓ Registers in Add/Remove Programs")
        else
            print("❌ Failed to build installer")
            print("💡 Check the NSIS script for errors")
            print("💡 NSIS command returned: " .. tostring(ret))
        end
    end)