#pragma once

// @completed

#include "framework_global.h"
#include <QString>
#include <QSet>
#include <QObject>

namespace ymf {

    class ApplicationContext;

    #if defined(FRAMEWORK_LIBRARY)
    #  define MODULE_EXPORT_QOBJECT Q_DECL_EXPORT
    #else
    #  define MODULE_EXPORT_QOBJECT Q_DECL_IMPORT
    #endif

    class MODULE_EXPORT_QOBJECT IModule {
    public:
        virtual ~IModule() = default;
        
        // 获取模块名称
        virtual QString getName() const = 0;
        
        // 获取模块版本
        virtual QString getVersion() const = 0;
        
        // 获取依赖的模块列表
        virtual QSet<QString> getDependencies() const = 0;
        
        // 模块加载时调用
        virtual void onLoad(ApplicationContext* context) = 0;
        
        // 模块卸载时调用
        virtual void onUnload(ApplicationContext* context) = 0;

        virtual void changeLanguage(QString language) = 0;
    };

} // namespace ymf

QT_BEGIN_NAMESPACE
Q_DECLARE_INTERFACE(ymf::IModule, "com.yima.framework.IModule/1.0")
QT_END_NAMESPACE