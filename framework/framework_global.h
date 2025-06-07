#pragma once

// @completed

#if defined(_MSC_VER) || defined(WIN64) || defined(_WIN64) || defined(__WIN64__) || defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
#  define DECL_EXPORT __declspec(dllexport)
#  define DECL_IMPORT __declspec(dllimport)
#else
#  define DECL_EXPORT     __attribute__((visibility("default")))
#  define DECL_IMPORT     __attribute__((visibility("default")))
#endif

// Framework API 导出宏（用于主程序）
#ifdef FRAMEWORK_LIBRARY
#  define FRAMEWORK_EXPORT DECL_EXPORT
#else
#  define FRAMEWORK_EXPORT DECL_IMPORT
#endif

// Module API 导出宏（用于模块开发）
#ifdef FRAMEWORK_MODULE
#  define MODULE_EXPORT DECL_EXPORT
#else
#  define MODULE_EXPORT DECL_IMPORT
#endif
