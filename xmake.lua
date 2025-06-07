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

-- 添加一个测试组，方便一键运行所有测试
target("test")
    set_kind("phony")
    on_run(function ()
        -- 构建所有测试
        os.exec("xmake build test_lexer")
        os.exec("xmake build test_parser")
        
        -- 运行所有测试
        print("\nRunning lexer tests...")
        os.exec("xmake run test_lexer")
        
        print("\nRunning parser tests...")
        os.exec("xmake run test_parser")
    end)

-- syntax_checker 测试
target("test_syntax_checker")
    set_kind("binary")
    add_files("test/test_syntax_checker.cpp")
    add_includedirs("include")
    add_files("src/*.cpp")
    remove_files("src/main.cpp")  -- 排除主程序的main函数
    add_packages("gtest")
    set_encodings("utf-8")

-- 生成器测试
target("test_generator")
    set_kind("binary")
    add_files("test/test_generator.cpp")
    add_files("src/lexer_*.cpp")
    add_files("src/parser_*.cpp")  
    add_files("src/generator.cpp")
    add_includedirs("include")
    add_packages("gtest", {configs = {main = true}})
    set_encodings("utf-8")

-- 打包目标：生成压缩包
target("package")
    set_kind("phony")
    on_run(function ()
        -- 首先运行install目标
        print("Creating installation package...")
        os.exec("xmake run install")
        
        -- 创建压缩包
        local install_dir = "mota-install"
        local package_name = "mota-v0.2.0-windows-x64.zip"
        
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
        local installer_file = "installer/mota-installer-v0.2.0.exe"
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
            local final_name = "mota-installer-v0.2.0.exe"
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

