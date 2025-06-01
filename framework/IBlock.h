#pragma once

#include <QString>
#include <QVariant>
#include <QMap>
#include <QCborValue>
#include <QStringList>
#include <QList>
#include <QSharedPointer>

namespace ymf {

    #if defined(FRAMEWORK_LIBRARY)
    #  define MODEL_EXPORT __declspec(dllexport)
    #else
    #  define MODEL_EXPORT __declspec(dllimport)
    #endif
    
        // BaseBlock 保持独立
        class MODEL_EXPORT IBlock {
            public:
                virtual ~IBlock() = default;
                virtual QCborValue toCbor() const = 0;
                virtual void fromCbor(const QCborValue& cbor) = 0;
        
                // 获取块名称
                virtual QString name() const = 0;
        
                // 获取所有的字段
                virtual QStringList fields() const = 0;
        
                // 获取字段类型
                virtual QString fieldType(const QString& fieldName) const = 0;
        
                // 获取字段注解
                virtual QList<std::shared_ptr<void>> fieldAnnotation(const QString& fieldName) const = 0;
        
                // 获取块的注释
                virtual QString description() const = 0;
        
                // 获取字段的注释
                virtual QString fieldDescription(const QString& fieldName) const = 0;
        
                // 获取字段值
                virtual QVariant value(const QString& fieldName) const = 0;
        
                // 设置字段值
                virtual void value(const QString& fieldName, const QVariant& value) = 0;
            };
        
}