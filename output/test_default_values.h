#pragma once

#include <QCborMap>
#include <QCborArray>
#include <QCborValue>
#include <QString>
#include <QStringList>
#include <QVariant>
#include <QVector>
#include <QSharedPointer>
#include <memory>

#include "framework/IBlock.h"
#include "framework/IModel.h"
#include "framework/IAnnotation.h"



// 此文件由 Mota 代码生成器自动生成
// 生成时间: 2025-06-08 20:14:23
// 源文件: test_default_values

using namespace ymf;



// TestAnnotation注解
class MODEL_EXPORT TestAnnotationAnnotation : public IAnnotation {
public:
    TestAnnotationAnnotation() = default;
    
    
    // 实现IAnnotation接口
    QString name() const override {
        return "TestAnnotation";
    }
    
    QVariant argument(const QString& argumentName) const override {
        if (argumentName == QLatin1String("name")) return QVariant::fromValue(name_);
        if (argumentName == QLatin1String("count")) return QVariant::fromValue(count_);
        if (argumentName == QLatin1String("enabled")) return QVariant::fromValue(enabled_);
        return QVariant();
    }
    
    QStringList argumentNames() const override {
        return QStringList{QLatin1String("name"), QLatin1String("count"), QLatin1String("enabled")};
    }
    
    // 特定于TestAnnotation的访问器
        // name字段的访问器
    QString getName() const {
        return name_;
    }
    
    void setName(const QString& value) {
        name_ = value;
    } 

        // count字段的访问器
    int32_t getCount() const {
        return count_;
    }
    
    void setCount(const int32_t& value) {
        count_ = value;
    } 

        // enabled字段的访问器
    bool getEnabled() const {
        return enabled_;
    }
    
    void setEnabled(const bool& value) {
        enabled_ = value;
    } 
    
private:
    QString name_;
    int32_t count_;
    bool enabled_;
}; 

// TestStruct结构体

class MODEL_EXPORT TestStructModel : public IModel {
public:
    TestStructModel() = default;
    
    
    // 实现IModel接口
    QCborValue toCbor() const override {
        QCborMap map;
        map.insert(QLatin1String("field1"), QCborValue(getField1()));
        map.insert(QLatin1String("field2"), QCborValue(getField2()));
        return map;
    }
    
    void fromCbor(const QCborValue& cbor) override {
        QCborMap map = cbor.toMap();
        setField1(map.value(QLatin1String("field1")).toString());
        setField2(static_cast<int32_t>(map.value(QLatin1String("field2")).toInteger()));
    }
    
    QStringList fields() const override {
        return QStringList{QLatin1String("field1"), QLatin1String("field2")};
    }
    
    QString fieldOriginTypeName(const QString& fieldName) const override {
        if (fieldName == QLatin1String("field1")) return QLatin1String("string");
        if (fieldName == QLatin1String("field2")) return QLatin1String("int32");
        return QLatin1String("");
    }
    
    QList<QSharedPointer<IAnnotation>> annotations() const override {
        
        return QList<QSharedPointer<IAnnotation>>();
    }
    
    QList<QSharedPointer<void>> fieldAnnotations(const QString& fieldName) const override {
        if (fieldName == QLatin1String("field1")) {
            return QList<QSharedPointer<void>>();
        }
        if (fieldName == QLatin1String("field2")) {
            return QList<QSharedPointer<void>>();
        }
        return QList<QSharedPointer<void>>();
    }
    
    QString description() const override {
        return "Generated from struct TestStruct";
    }
    
    QString fieldDescription(const QString& fieldName) const override {
        
        return QString();
    }
    
    QVariant value(const QString& fieldName) const override {
        if (fieldName == QLatin1String("field1")) return QVariant::fromValue(field1_);
        if (fieldName == QLatin1String("field2")) return QVariant::fromValue(field2_);
        return QVariant();
    }
    
    void value(const QString& fieldName, const QVariant& value) override {
        if (fieldName == QLatin1String("field1")) {
            field1_ = value.value<QString>();
            return;
        }
        if (fieldName == QLatin1String("field2")) {
            field2_ = value.value<int32_t>();
            return;
        }
    }
    
    // 特定于TestStruct的访问器
        // field1字段的访问器
    QString getField1() const {
        return field1_;
    }
    
    void setField1(const QString& value) {
        field1_ = value;
    } 

        // field2字段的访问器
    int32_t getField2() const {
        return field2_;
    }
    
    void setField2(const int32_t& value) {
        field2_ = value;
    } 
    
protected:
    QString modelName() const override {
        return "TestStruct";
    }
    
private:
    QString field1_;
    int32_t field2_;
};



