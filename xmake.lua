-- 设置项目名称和版本
set_project("mota")
set_version("0.1.0")

-- 添加构建模式
add_rules("mode.debug", "mode.release")

-- 设置C++标准
set_languages("c++17")

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
    
    -- 排除测试文件
    remove_files("src/test_*.cpp")
    
    -- 添加头文件目录
    add_includedirs("include")
    
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

-- 框架库目标
target("mota_framework")
    -- 设置为静态库
    add_rules("qt.static")
    
    -- 添加源文件
    add_files("framework/*.cpp")
    
    -- 添加头文件目录
    add_includedirs("framework")
    
    -- 添加依赖包
    add_frameworks("QtCore")

-- 测试目标
target("mota_test")
    -- 设置为可执行程序
    set_kind("binary")
    
    -- 添加源文件
    add_files("test/*.cpp")
    add_files("src/*.cpp")
    remove_files("src/main.cpp")
    
    -- 添加头文件目录
    add_includedirs("include", "framework")
    
    -- 添加测试框架
    add_packages("gtest")
    
    -- 设置输出目录
    set_targetdir("bin")
    
    -- 添加测试定义
    add_defines("TESTING")

-- 安装配置
target("install")
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
