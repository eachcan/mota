-- 设置项目名称和版本
set_project("mota")
set_version("0.1.0")

-- 添加构建模式
add_rules("mode.debug", "mode.release")

-- 设置C++标准
set_languages("c++20")

-- 添加包依赖
add_requires("qt6core", {optional = true})
add_requires("gtest")
add_requires("cxxopts")

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
    
    -- 排除测试文件和add_bom工具
    remove_files("src/test_*.cpp")
    remove_files("src/add_bom.cpp")
    remove_files("src/install.cpp")
    
    -- 添加头文件目录
    add_includedirs("include", "framework")
    
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

-- 测试目标：解析器测试
target("test_parser")
    -- 设置为可执行程序
    set_kind("binary")
    
    -- 添加源文件
    add_files("test/test_parser.cpp")
    add_files("src/lexer.cpp")
    add_files("src/parser.cpp")
    add_files("src/ast.cpp")
    add_files("src/config.cpp")
    
    -- 添加头文件目录
    add_includedirs("include", "framework")
    
    -- 设置输出目录
    set_targetdir("bin")
    
    -- 添加测试定义
    add_defines("TESTING")

-- 测试目标：生成器测试
target("test_generator")
    -- 设置为可执行程序
    set_kind("binary")
    
    -- 添加源文件
    add_files("test/test_generator.cpp")
    add_files("src/lexer.cpp")
    add_files("src/parser.cpp")
    add_files("src/generator.cpp")
    add_files("src/ast.cpp")
    add_files("src/config.cpp")
    
    -- 添加头文件目录
    add_includedirs("include", "framework")
    
    -- 添加测试框架 (包括gtest_main)
    add_packages("gtest", {configs = {main = true}})
    
    -- 设置输出目录
    set_targetdir("bin")
    
    -- 添加测试定义
    add_defines("TESTING")
    
-- 添加BOM工具
target("add_bom")
    -- 设置为可执行程序
    set_kind("binary")
    -- 添加源文件（只添加add_bom.cpp，不包含其他源文件）
    add_files("src/add_bom.cpp")
    -- 添加C++17标准支持
    set_languages("c++17")
    -- 设置输出目录
    set_targetdir("bin")

-- 安装配置
target("install")
    -- 设置为可执行程序
    set_kind("binary")
    -- 添加一个简单的main函数
    add_files("src/install.cpp")
    -- 设置输出目录
    set_targetdir("bin")
    -- 添加对主目标的依赖
    add_deps("mota")
    
    after_build(function (target)
        import("core.project.config")
        
        -- 使用 path.join 来处理路径
        local function install_file(src, dst)
            os.cp(path.join("$(projectdir)", src), 
                 path.join("$(installdir)", dst))
        end
        
        -- 复制可执行文件
        install_file("bin/mota.exe", "bin")
        
        -- 复制头文件
        install_file("include/*.h", "include")
        
        -- 复制框架文件
        install_file("framework/*.h", "include/framework")
        
        -- 复制示例
        install_file("examples/*.mota", "examples")
    end)
