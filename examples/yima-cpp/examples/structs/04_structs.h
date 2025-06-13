#pragma once

// 此文件由 Mota 代码生成器自动生成
// 生成时间: 2025-06-13 21:20:53
// 源文件: .\examples\04_structs.mota

#include <QCborMap>
#include <QCborArray>
#include <QCborValue>
#include <QString>
#include <QStringList>
#include <QVariant>
#include <QVector>
#include <QSharedPointer>
#include <memory>
#include <optional>

#include "framework/IBlock.h"
#include "framework/IModel.h"
#include "framework/IAnnotation.h"
#include "yima.h"

using namespace ymf;

namespace examples {
namespace structs {

// StructAnnotation注解
class MODEL_EXPORT StructAnnotationAnnotation : public IAnnotation {
public:
    StructAnnotationAnnotation() = default;
    
    // 实现IAnnotation接口
    QString name() const override {
        return QLatin1String("StructAnnotation");
    }
    
    virtual QVariant argument(const QString& argumentName) const override {
        if (argumentName == QLatin1String("description")) {
            return QVariant::fromValue(description_);
        }
        return QVariant();
    }
    
    QStringList argumentNames() const override {
        return QStringList{QLatin1String("description")};
    }
    
    // 字段访问器
    QString getDescription() const {
        return description_;
    }
    void setDescription(const QString& value) {
        description_ = value;
    }
private:
    QString description_;
};
Q_DECLARE_METATYPE(StructAnnotationAnnotation)
    
// StructValueAnnotation注解
class MODEL_EXPORT StructValueAnnotationAnnotation : public IAnnotation {
public:
    StructValueAnnotationAnnotation() = default;
    
    // 实现IAnnotation接口
    QString name() const override {
        return QLatin1String("StructValueAnnotation");
    }
    
    virtual QVariant argument(const QString& argumentName) const override {
        if (argumentName == QLatin1String("value")) {
            return QVariant::fromValue(value_);
        }
        return QVariant();
    }
    
    QStringList argumentNames() const override {
        return QStringList{QLatin1String("value")};
    }
    
    // 字段访问器
    QString getValue() const {
        return value_;
    }
    void setValue(const QString& value) {
        value_ = value;
    }
private:
    QString value_;
};
Q_DECLARE_METATYPE(StructValueAnnotationAnnotation)
    
// StructConfigAnnotation注解
class MODEL_EXPORT StructConfigAnnotationAnnotation : public StructAnnotationAnnotation {
public:
    StructConfigAnnotationAnnotation() = default;
    
    // 实现IAnnotation接口
    QString name() const override {
        return QLatin1String("StructConfigAnnotation");
    }
    
    virtual QVariant argument(const QString& argumentName) const override {
        if (argumentName == QLatin1String("required")) {
            return QVariant::fromValue(required_);
        }
        if (argumentName == QLatin1String("priority")) {
            return QVariant::fromValue(priority_);
        }
        return StructAnnotationAnnotation::argument(argumentName);
    }
    
    QStringList argumentNames() const override {
        return QStringList{QLatin1String("required"), QLatin1String("priority")};
    }
    
    // 字段访问器
    bool getRequired() const {
        return required_;
    }
    void setRequired(const bool& value) {
        required_ = value;
    }
    int32_t getPriority() const {
        return priority_;
    }
    void setPriority(const int32_t& value) {
        priority_ = value;
    }
private:
    bool required_;
    int32_t priority_;
};
Q_DECLARE_METATYPE(StructConfigAnnotationAnnotation)
    
[MISSING_MISC:enum][MISSING_MISC:enum][MISSING_MISC:block][MISSING_MISC:block][MISSING_MISC:struct][MISSING_MISC:struct][MISSING_MISC:struct][MISSING_MISC:struct][MISSING_MISC:struct][MISSING_MISC:struct]
} // namespace examples
} // namespace structs
