add_rules("mode.debug", "mode.release")

set_version("1.0.0")
set_project("mota")

add_requires("cxxopts")  -- 添加 cxxopts 依赖
add_requires("yaml-cpp") -- 添加 yaml-cpp 依赖

add_includedirs("include")

-- 生成版本头文件
before_build(function (target)
    local version = target:version()
    local version_h = io.readfile("include/version.h.in")
    version_h = version_h:gsub("${VERSION}", version)
    io.writefile("include/version.h", version_h)
end)

target("mota")
    set_kind("binary")
    add_files("src/*.cpp")
    set_languages("c++20")
    set_encodings("utf-8")
    add_defines("UNICODE", "_UNICODE")
    add_packages("cxxopts", "yaml-cpp")  -- 添加包到目标
    set_installdir(".")
--    add_cxflags("/execution-charset:utf-8")

add_rules("mode.debug", "mode.release")

for _, file in ipairs(os.files("test/test_*.cpp")) do
    local name = path.basename(file)
    target(name)
        set_kind("binary")
        set_default(false)
        add_files("test/" .. name .. ".cpp")
        add_tests("default")
end
--
-- If you want to known more usage about xmake, please see https://xmake.io
--
-- ## FAQ
--
-- You can enter the project directory firstly before building project.
--
--   $ cd projectdir
--
-- 1. How to build project?
--
--   $ xmake
--
-- 2. How to configure project?
--
--   $ xmake f -p [macosx|linux|iphoneos ..] -a [x86_64|i386|arm64 ..] -m [debug|release]
--
-- 3. Where is the build output directory?
--
--   The default output directory is `./build` and you can configure the output directory.
--
--   $ xmake f -o outputdir
--   $ xmake
--
-- 4. How to run and debug target after building project?
--
--   $ xmake run [targetname]
--   $ xmake run -d [targetname]
--
-- 5. How to install target to the system directory or other output directory?
--
--   $ xmake install
--   $ xmake install -o installdir
--
-- 6. Add some frequently-used compilation flags in xmake.lua
--
-- @code
--    -- add debug and release modes
--    add_rules("mode.debug", "mode.release")
--
--    -- add macro definition
--    add_defines("NDEBUG", "_GNU_SOURCE=1")
--
--    -- set warning all as error
--    set_warnings("all", "error")
--
--    -- set language: c99, c++11
--    set_languages("c99", "c++11")
--
--    -- set optimization: none, faster, fastest, smallest
--    set_optimize("fastest")
--
--    -- add include search directories
--    add_includedirs("/usr/include", "/usr/local/include")
--
--    -- add link libraries and search directories
--    add_links("tbox")
--    add_linkdirs("/usr/local/lib", "/usr/lib")
--
--    -- add system link libraries
--    add_syslinks("z", "pthread")
--
--    -- add compilation and link flags
--    add_cxflags("-stdnolib", "-fno-strict-aliasing")
--    add_ldflags("-L/usr/local/lib", "-lpthread", {force = true})
--
-- @endcode
--
