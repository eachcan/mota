#pragma once

// @completed

#include "framework_global.h"
#include <QString>
#include <QStringList>

namespace ymf {

    class MODULE_EXPORT IFactory {
    public:
        virtual ~IFactory() = default;
        
        // 获取工厂支持的驱动类型名称
        virtual QString getDriverTypeName() const = 0;
        
        // 注册驱动
        virtual void registerDriver(void* driver, const QString& name) = 0;
        
        // 取消注册驱动
        virtual void unregisterDriver(const QString& name) = 0;
        
        // 获取驱动实例
        virtual void* getDriver(const QString& name) const = 0;
        
        // 获取所有已注册的驱动名称
        virtual QStringList getDriverList() const = 0;
        
        // 检查驱动是否存在
        virtual bool hasDriver(const QString& name) const = 0;
    };

} // namespace ymf
