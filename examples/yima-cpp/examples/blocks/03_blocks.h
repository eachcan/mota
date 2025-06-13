#pragma once

// 此文件由 Mota 代码生成器自动生成
// 生成时间: 2025-06-13 21:20:53
// 源文件: .\examples\03_blocks.mota

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
namespace blocks {

// BlockAnnotation注解
class MODEL_EXPORT BlockAnnotationAnnotation : public IAnnotation {
public:
    BlockAnnotationAnnotation() = default;
    
    // 实现IAnnotation接口
    QString name() const override {
        return QLatin1String("BlockAnnotation");
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
Q_DECLARE_METATYPE(BlockAnnotationAnnotation)
    
// BlockValueAnnotation注解
class MODEL_EXPORT BlockValueAnnotationAnnotation : public IAnnotation {
public:
    BlockValueAnnotationAnnotation() = default;
    
    // 实现IAnnotation接口
    QString name() const override {
        return QLatin1String("BlockValueAnnotation");
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
Q_DECLARE_METATYPE(BlockValueAnnotationAnnotation)
    
[MISSING_MISC:enum][MISSING_MISC:enum][MISSING_MISC:block][MISSING_MISC:block][MISSING_MISC:block][MISSING_MISC:block][MISSING_MISC:block]
} // namespace examples
} // namespace blocks
