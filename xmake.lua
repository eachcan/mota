-- 设置项目名称和版本
set_project("mota")
set_version("0.1.0")

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

-- 主要目标：编译器
target("mota")
    -- 设置为可执行程序
    add_rules("qt.shared")
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
    add_files("src/lexer.cpp")
    
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
    add_files("src/lexer.cpp")
    add_files("src/parser.cpp")
    
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