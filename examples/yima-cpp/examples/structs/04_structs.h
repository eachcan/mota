#pragma once

// 此文件由 Mota 代码生成器自动生成
// 生成时间: 2025-06-13 16:19:37
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
    
    QVariant argument(const QString& argumentName) const override {
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
    void setDescription(
        const QString& value) {
        description_ = value;
    }
private:
    QString description_ = "";
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
    
    QVariant argument(const QString& argumentName) const override {
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
    void setValue(
        const QString& value) {
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
    
    QVariant argument(const QString& argumentName) const override {
        if (argumentName == QLatin1String("required")) {
            return QVariant::fromValue(required_);
        }
        if (argumentName == QLatin1String("priority")) {
            return QVariant::fromValue(priority_);
        }
        return QVariant();
    }
    
    QStringList argumentNames() const override {
        return QStringList{QLatin1String("required"), QLatin1String("priority")};
    }
    
    // 字段访问器
    bool getRequired() const {
        return required_; 
    }
    void setRequired(
        const bool& value) {
        required_ = value;
    }
    int32_t getPriority() const {
        return priority_; 
    }
    void setPriority(
        const int32_t& value) {
        priority_ = value;
    }
private:
    bool required_ = false;
    int32_t priority_ = 1;
};
Q_DECLARE_METATYPE(StructConfigAnnotationAnnotation)


// StructStatus枚举
enum class StructStatus {
    DRAFT = 1,
    PUBLISHED = 2,
    ARCHIVED = 3
};


// StructCategory枚举
enum class StructCategory {
    BASIC,
    ADVANCED,
    PREMIUM
};


// StructBaseBlock块定义
class MODEL_EXPORT StructBaseBlockBlock : public IBlock {
public:
    StructBaseBlockBlock() = default;
    
    // 实现 IBlock 接口
    QCborMap toCbor() const override {
        QCborMap map;
                map.insert(QLatin1String("id"), id_.toCbor());
                map.insert(QLatin1String("name"), name_.toCbor());
        return map;
    }
    
    void fromCbor(const QCborMap& map) override {
        QCborValue tmpValue;
        tmpValue = map.value(QLatin1String("id"));
        if (!tmpValue.isNull()) {
            id_.fromCbor(tmpValue.toMap());
        }
        tmpValue = map.value(QLatin1String("name"));
        if (!tmpValue.isNull()) {
            name_ = tmpValue.toString();name_.fromCbor(tmpValue.toMap());
        }
    }
    
    QString name() const override {
        return QLatin1String("StructBaseBlock");
    }
    
    QStringList fields() const override {
        return QStringList{QLatin1String("id"), QLatin1String("name")};
    }
    
    QString fieldType(const QString& fieldName) const override {
        if (fieldName == QLatin1String("id")) return QLatin1String("int32");
        if (fieldName == QLatin1String("name")) return QLatin1String("string");
        return QString();
    }
    
    QString fieldContainerType(const QString& fieldName) const override {
        if (fieldName == QLatin1String("id")) return QLatin1String("none");
        if (fieldName == QLatin1String("name")) return QLatin1String("none");
        return QLatin1String("none");
    }
    
    QList<QSharedPointer<IAnnotation>> annotations() const override {
        QList<QSharedPointer<IAnnotation>> result;
        return result;
    }
    
    QList<QSharedPointer<IAnnotation>> fieldAnnotation(const QString& fieldName) const override {
        if (fieldName == QLatin1String("id")) {
            QList<QSharedPointer<IAnnotation>> result;
            return result;
        }
        if (fieldName == QLatin1String("name")) {
            QList<QSharedPointer<IAnnotation>> result;
            return result;
        }
        return QList<QSharedPointer<IAnnotation>>();
    }
    
    QString description() const override {
        return QLatin1String("StructBaseBlock");
    }
    
    QString fieldDescription(const QString& fieldName) const override {
        if (fieldName == QLatin1String("id")) return QLatin1String("id");
        if (fieldName == QLatin1String("name")) return QLatin1String("name");
        return QString();
    }
    
    QVariant value(const QString& fieldName) const override {
        if (fieldName == QLatin1String("id")) return QVariant::fromValue(id_);
        if (fieldName == QLatin1String("name")) return QVariant::fromValue(name_);
        return QVariant();
    }
    
    void value(const QString& fieldName, const QVariant& value) override {
        if (fieldName == QLatin1String("id")) {
            id_ = value.value<int32_t>();
            return;
        }
        if (fieldName == QLatin1String("name")) {
            name_ = value.value<QString>();
            return;
        }
    }
    
    // 字段访问器
    int32_t getId() const { return id_; }
    void setId(const int32_t& value) { id_ = value; }
    QString getName() const { return name_; }
    void setName(const QString& value) { name_ = value; }
private:
    int32_t id_ = 0;
    QString name_ = "";
};
Q_DECLARE_METATYPE(StructBaseBlockBlock)


// StructExtendedBlock块定义
class MODEL_EXPORT StructExtendedBlockBlock : public StructBaseBlockBlock, public IBlock {
public:
    StructExtendedBlockBlock() = default;
    
    // 实现 IBlock 接口
    QCborMap toCbor() const override {
        QCborMap map = StructBaseBlockBlock::toCbor();
                map.insert(QLatin1String("enabled"), enabled_.toCbor());
                map.insert(QLatin1String("status"), status_.toCbor());
        return map;
    }
    
    void fromCbor(const QCborMap& map) override {
        StructBaseBlockBlock::fromCbor(map);
        QCborValue tmpValue;
        tmpValue = map.value(QLatin1String("enabled"));
        if (!tmpValue.isNull()) {
            enabled_ = tmpValue.toBool();enabled_.fromCbor(tmpValue.toMap());
        }
        tmpValue = map.value(QLatin1String("status"));
        if (!tmpValue.isNull()) {
            status_.fromCbor(tmpValue.toMap());
        }
    }
    
    QString name() const override {
        return QLatin1String("StructExtendedBlock");
    }
    
    QStringList fields() const override {
        return QStringList{QLatin1String("enabled"), QLatin1String("status")};
    }
    
    QString fieldType(const QString& fieldName) const override {
        if (fieldName == QLatin1String("enabled")) return QLatin1String("bool");
        if (fieldName == QLatin1String("status")) return QLatin1String("StructStatus");
        return QString();
    }
    
    QString fieldContainerType(const QString& fieldName) const override {
        if (fieldName == QLatin1String("enabled")) return QLatin1String("none");
        if (fieldName == QLatin1String("status")) return QLatin1String("none");
        return QLatin1String("none");
    }
    
    QList<QSharedPointer<IAnnotation>> annotations() const override {
        QList<QSharedPointer<IAnnotation>> result;
        return result;
    }
    
    QList<QSharedPointer<IAnnotation>> fieldAnnotation(const QString& fieldName) const override {
        if (fieldName == QLatin1String("enabled")) {
            QList<QSharedPointer<IAnnotation>> result;
            return result;
        }
        if (fieldName == QLatin1String("status")) {
            QList<QSharedPointer<IAnnotation>> result;
            return result;
        }
        return QList<QSharedPointer<IAnnotation>>();
    }
    
    QString description() const override {
        return QLatin1String("StructExtendedBlock");
    }
    
    QString fieldDescription(const QString& fieldName) const override {
        if (fieldName == QLatin1String("enabled")) return QLatin1String("enabled");
        if (fieldName == QLatin1String("status")) return QLatin1String("status");
        return QString();
    }
    
    QVariant value(const QString& fieldName) const override {
        if (fieldName == QLatin1String("enabled")) return QVariant::fromValue(enabled_);
        if (fieldName == QLatin1String("status")) return QVariant::fromValue(status_);
        return QVariant();
    }
    
    void value(const QString& fieldName, const QVariant& value) override {
        if (fieldName == QLatin1String("enabled")) {
            enabled_ = value.value<bool>();
            return;
        }
        if (fieldName == QLatin1String("status")) {
            status_ = value.value<StructStatus>();
            return;
        }
    }
    
    // 字段访问器
    bool getEnabled() const { return enabled_; }
    void setEnabled(const bool& value) { enabled_ = value; }
    StructStatus getStatus() const { return status_; }
    void setStatus(const StructStatus& value) { status_ = value; }
private:
    bool enabled_ = true;
    StructStatus status_ = /* complex expression */;
};
Q_DECLARE_METATYPE(StructExtendedBlockBlock)


// BasicStruct结构体
class MODEL_EXPORT BasicStructModel : public IModel {
public:
    BasicStructModel() = default;
    
    // 实现 IModel 接口
    QCborMap toCbor() const override {
        QCborMap map;
                map.insert(QLatin1String("id"), id_.toCbor());
                map.insert(QLatin1String("name"), name_.toCbor());
        return map;
    }
    
    void fromCbor(const QCborMap& map) override {
        QCborValue tmpValue;
        tmpValue = map.value(QLatin1String("id"));
        if (!tmpValue.isNull()) {
            id_.fromCbor(tmpValue.toMap());
        }
        tmpValue = map.value(QLatin1String("name"));
        if (!tmpValue.isNull()) {
            name_ = tmpValue.toString();name_.fromCbor(tmpValue.toMap());
        }
    }
    
    QString name() const override {
        return QLatin1String("BasicStruct");
    }
    
    QStringList fields() const override {
        return QStringList{QLatin1String("id"), QLatin1String("name")};
    }
    
    QString fieldType(const QString& fieldName) const override {
        if (fieldName == QLatin1String("id")) return QLatin1String("int32");
        if (fieldName == QLatin1String("name")) return QLatin1String("string");
        return QString();
    }
    
    QString fieldContainerType(const QString& fieldName) const override {
        if (fieldName == QLatin1String("id")) return QLatin1String("none");
        if (fieldName == QLatin1String("name")) return QLatin1String("none");
        return QLatin1String("none");
    }

    // 字段访问器
    int32_t getId() const { return id_; }
    void setId(const int32_t& value) { id_ = value; }
    QString getName() const { return name_; }
    void setName(const QString& value) { name_ = value; }
private:
    int32_t id_ = 0;
    QString name_ = "";
};
Q_DECLARE_METATYPE(BasicStructModel)


// InheritedStruct结构体
class MODEL_EXPORT InheritedStructModel : public StructBaseBlockModel, public IModel {
public:
    InheritedStructModel() = default;
    
    // 实现 IModel 接口
    QCborMap toCbor() const override {
        QCborMap map = StructBaseBlockModel::toCbor();
                map.insert(QLatin1String("score"), score_.toCbor());
                map.insert(QLatin1String("category"), category_.toCbor());
        return map;
    }
    
    void fromCbor(const QCborMap& map) override {
        StructBaseBlockModel::fromCbor(map);
        QCborValue tmpValue;
        tmpValue = map.value(QLatin1String("score"));
        if (!tmpValue.isNull()) {
            score_.fromCbor(tmpValue.toMap());
        }
        tmpValue = map.value(QLatin1String("category"));
        if (!tmpValue.isNull()) {
            category_.fromCbor(tmpValue.toMap());
        }
    }
    
    QString name() const override {
        return QLatin1String("InheritedStruct");
    }
    
    QStringList fields() const override {
        return QStringList{QLatin1String("score"), QLatin1String("category")};
    }
    
    QString fieldType(const QString& fieldName) const override {
        if (fieldName == QLatin1String("score")) return QLatin1String("float64");
        if (fieldName == QLatin1String("category")) return QLatin1String("StructCategory");
        return QString();
    }
    
    QString fieldContainerType(const QString& fieldName) const override {
        if (fieldName == QLatin1String("score")) return QLatin1String("none");
        if (fieldName == QLatin1String("category")) return QLatin1String("none");
        return QLatin1String("none");
    }

    // 字段访问器
    double getScore() const { return score_; }
    void setScore(const double& value) { score_ = value; }
    StructCategory getCategory() const { return category_; }
    void setCategory(const StructCategory& value) { category_ = value; }
private:
    double score_ = 0.000000;
    StructCategory category_ = /* complex expression */;
};
Q_DECLARE_METATYPE(InheritedStructModel)


// AnnotatedStruct结构体
class MODEL_EXPORT AnnotatedStructModel : public IModel {
public:
    AnnotatedStructModel() = default;
    
    // 实现 IModel 接口
    QCborMap toCbor() const override {
        QCborMap map;
                map.insert(QLatin1String("title"), title_.toCbor());
                map.insert(QLatin1String("priority"), priority_.toCbor());
        return map;
    }
    
    void fromCbor(const QCborMap& map) override {
        QCborValue tmpValue;
        tmpValue = map.value(QLatin1String("title"));
        if (!tmpValue.isNull()) {
            title_ = tmpValue.toString();title_.fromCbor(tmpValue.toMap());
        }
        tmpValue = map.value(QLatin1String("priority"));
        if (!tmpValue.isNull()) {
            priority_.fromCbor(tmpValue.toMap());
        }
    }
    
    QString name() const override {
        return QLatin1String("AnnotatedStruct");
    }
    
    QStringList fields() const override {
        return QStringList{QLatin1String("title"), QLatin1String("priority")};
    }
    
    QString fieldType(const QString& fieldName) const override {
        if (fieldName == QLatin1String("title")) return QLatin1String("string");
        if (fieldName == QLatin1String("priority")) return QLatin1String("int32");
        return QString();
    }
    
    QString fieldContainerType(const QString& fieldName) const override {
        if (fieldName == QLatin1String("title")) return QLatin1String("none");
        if (fieldName == QLatin1String("priority")) return QLatin1String("none");
        return QLatin1String("none");
    }

    // 字段访问器
    QString getTitle() const { return title_; }
    void setTitle(const QString& value) { title_ = value; }
    int32_t getPriority() const { return priority_; }
    void setPriority(const int32_t& value) { priority_ = value; }
private:
    QString title_ = "";
    int32_t priority_ = 1;
};
Q_DECLARE_METATYPE(AnnotatedStructModel)


// AllTypesStruct结构体
class MODEL_EXPORT AllTypesStructModel : public IModel {
public:
    AllTypesStructModel() = default;
    
    // 实现 IModel 接口
    QCborMap toCbor() const override {
        QCborMap map;
                map.insert(QLatin1String("int8Field"), int8Field_.toCbor());
                map.insert(QLatin1String("int16Field"), int16Field_.toCbor());
                map.insert(QLatin1String("int32Field"), int32Field_.toCbor());
                map.insert(QLatin1String("int64Field"), int64Field_.toCbor());
                map.insert(QLatin1String("uint8Field"), uint8Field_.toCbor());
                map.insert(QLatin1String("uint16Field"), uint16Field_.toCbor());
                map.insert(QLatin1String("uint32Field"), uint32Field_.toCbor());
                map.insert(QLatin1String("uint64Field"), uint64Field_.toCbor());
                map.insert(QLatin1String("float32Field"), float32Field_.toCbor());
                map.insert(QLatin1String("float64Field"), float64Field_.toCbor());
                map.insert(QLatin1String("boolField"), boolField_.toCbor());
                map.insert(QLatin1String("stringField"), stringField_.toCbor());
                map.insert(QLatin1String("bytesField"), bytesField_.toCbor());
                map.insert(QLatin1String("status"), status_.toCbor());
                map.insert(QLatin1String("category"), category_.toCbor());
                map.insert(QLatin1String("baseBlock"), baseBlock_.toCbor());
                map.insert(QLatin1String("extendedBlock"), extendedBlock_.toCbor());
        return map;
    }
    
    void fromCbor(const QCborMap& map) override {
        QCborValue tmpValue;
        tmpValue = map.value(QLatin1String("int8Field"));
        if (!tmpValue.isNull()) {
            int8Field_.fromCbor(tmpValue.toMap());
        }
        tmpValue = map.value(QLatin1String("int16Field"));
        if (!tmpValue.isNull()) {
            int16Field_.fromCbor(tmpValue.toMap());
        }
        tmpValue = map.value(QLatin1String("int32Field"));
        if (!tmpValue.isNull()) {
            int32Field_.fromCbor(tmpValue.toMap());
        }
        tmpValue = map.value(QLatin1String("int64Field"));
        if (!tmpValue.isNull()) {
            int64Field_.fromCbor(tmpValue.toMap());
        }
        tmpValue = map.value(QLatin1String("uint8Field"));
        if (!tmpValue.isNull()) {
            uint8Field_.fromCbor(tmpValue.toMap());
        }
        tmpValue = map.value(QLatin1String("uint16Field"));
        if (!tmpValue.isNull()) {
            uint16Field_.fromCbor(tmpValue.toMap());
        }
        tmpValue = map.value(QLatin1String("uint32Field"));
        if (!tmpValue.isNull()) {
            uint32Field_.fromCbor(tmpValue.toMap());
        }
        tmpValue = map.value(QLatin1String("uint64Field"));
        if (!tmpValue.isNull()) {
            uint64Field_.fromCbor(tmpValue.toMap());
        }
        tmpValue = map.value(QLatin1String("float32Field"));
        if (!tmpValue.isNull()) {
            float32Field_.fromCbor(tmpValue.toMap());
        }
        tmpValue = map.value(QLatin1String("float64Field"));
        if (!tmpValue.isNull()) {
            float64Field_.fromCbor(tmpValue.toMap());
        }
        tmpValue = map.value(QLatin1String("boolField"));
        if (!tmpValue.isNull()) {
            boolField_ = tmpValue.toBool();boolField_.fromCbor(tmpValue.toMap());
        }
        tmpValue = map.value(QLatin1String("stringField"));
        if (!tmpValue.isNull()) {
            stringField_ = tmpValue.toString();stringField_.fromCbor(tmpValue.toMap());
        }
        tmpValue = map.value(QLatin1String("bytesField"));
        if (!tmpValue.isNull()) {
            bytesField_ = tmpValue.toByteArray();bytesField_.fromCbor(tmpValue.toMap());
        }
        tmpValue = map.value(QLatin1String("status"));
        if (!tmpValue.isNull()) {
            status_.fromCbor(tmpValue.toMap());
        }
        tmpValue = map.value(QLatin1String("category"));
        if (!tmpValue.isNull()) {
            category_.fromCbor(tmpValue.toMap());
        }
        tmpValue = map.value(QLatin1String("baseBlock"));
        if (!tmpValue.isNull()) {
            baseBlock_.fromCbor(tmpValue.toMap());
        }
        tmpValue = map.value(QLatin1String("extendedBlock"));
        if (!tmpValue.isNull()) {
            extendedBlock_.fromCbor(tmpValue.toMap());
        }
    }
    
    QString name() const override {
        return QLatin1String("AllTypesStruct");
    }
    
    QStringList fields() const override {
        return QStringList{QLatin1String("int8Field"), QLatin1String("int16Field"), QLatin1String("int32Field"), QLatin1String("int64Field"), QLatin1String("uint8Field"), QLatin1String("uint16Field"), QLatin1String("uint32Field"), QLatin1String("uint64Field"), QLatin1String("float32Field"), QLatin1String("float64Field"), QLatin1String("boolField"), QLatin1String("stringField"), QLatin1String("bytesField"), QLatin1String("status"), QLatin1String("category"), QLatin1String("baseBlock"), QLatin1String("extendedBlock")};
    }
    
    QString fieldType(const QString& fieldName) const override {
        if (fieldName == QLatin1String("int8Field")) return QLatin1String("int8");
        if (fieldName == QLatin1String("int16Field")) return QLatin1String("int16");
        if (fieldName == QLatin1String("int32Field")) return QLatin1String("int32");
        if (fieldName == QLatin1String("int64Field")) return QLatin1String("int64");
        if (fieldName == QLatin1String("uint8Field")) return QLatin1String("uint8");
        if (fieldName == QLatin1String("uint16Field")) return QLatin1String("uint16");
        if (fieldName == QLatin1String("uint32Field")) return QLatin1String("uint32");
        if (fieldName == QLatin1String("uint64Field")) return QLatin1String("uint64");
        if (fieldName == QLatin1String("float32Field")) return QLatin1String("float32");
        if (fieldName == QLatin1String("float64Field")) return QLatin1String("float64");
        if (fieldName == QLatin1String("boolField")) return QLatin1String("bool");
        if (fieldName == QLatin1String("stringField")) return QLatin1String("string");
        if (fieldName == QLatin1String("bytesField")) return QLatin1String("bytes");
        if (fieldName == QLatin1String("status")) return QLatin1String("StructStatus");
        if (fieldName == QLatin1String("category")) return QLatin1String("StructCategory");
        if (fieldName == QLatin1String("baseBlock")) return QLatin1String("StructBaseBlock");
        if (fieldName == QLatin1String("extendedBlock")) return QLatin1String("StructExtendedBlock");
        return QString();
    }
    
    QString fieldContainerType(const QString& fieldName) const override {
        if (fieldName == QLatin1String("int8Field")) return QLatin1String("none");
        if (fieldName == QLatin1String("int16Field")) return QLatin1String("none");
        if (fieldName == QLatin1String("int32Field")) return QLatin1String("none");
        if (fieldName == QLatin1String("int64Field")) return QLatin1String("none");
        if (fieldName == QLatin1String("uint8Field")) return QLatin1String("none");
        if (fieldName == QLatin1String("uint16Field")) return QLatin1String("none");
        if (fieldName == QLatin1String("uint32Field")) return QLatin1String("none");
        if (fieldName == QLatin1String("uint64Field")) return QLatin1String("none");
        if (fieldName == QLatin1String("float32Field")) return QLatin1String("none");
        if (fieldName == QLatin1String("float64Field")) return QLatin1String("none");
        if (fieldName == QLatin1String("boolField")) return QLatin1String("none");
        if (fieldName == QLatin1String("stringField")) return QLatin1String("none");
        if (fieldName == QLatin1String("bytesField")) return QLatin1String("none");
        if (fieldName == QLatin1String("status")) return QLatin1String("none");
        if (fieldName == QLatin1String("category")) return QLatin1String("none");
        if (fieldName == QLatin1String("baseBlock")) return QLatin1String("none");
        if (fieldName == QLatin1String("extendedBlock")) return QLatin1String("none");
        return QLatin1String("none");
    }

    // 字段访问器
    int8_t getInt8Field() const { return int8Field_; }
    void setInt8Field(const int8_t& value) { int8Field_ = value; }
    int16_t getInt16Field() const { return int16Field_; }
    void setInt16Field(const int16_t& value) { int16Field_ = value; }
    int32_t getInt32Field() const { return int32Field_; }
    void setInt32Field(const int32_t& value) { int32Field_ = value; }
    int64_t getInt64Field() const { return int64Field_; }
    void setInt64Field(const int64_t& value) { int64Field_ = value; }
    uint8_t getUint8Field() const { return uint8Field_; }
    void setUint8Field(const uint8_t& value) { uint8Field_ = value; }
    uint16_t getUint16Field() const { return uint16Field_; }
    void setUint16Field(const uint16_t& value) { uint16Field_ = value; }
    uint32_t getUint32Field() const { return uint32Field_; }
    void setUint32Field(const uint32_t& value) { uint32Field_ = value; }
    uint64_t getUint64Field() const { return uint64Field_; }
    void setUint64Field(const uint64_t& value) { uint64Field_ = value; }
    float getFloat32Field() const { return float32Field_; }
    void setFloat32Field(const float& value) { float32Field_ = value; }
    double getFloat64Field() const { return float64Field_; }
    void setFloat64Field(const double& value) { float64Field_ = value; }
    bool getBoolField() const { return boolField_; }
    void setBoolField(const bool& value) { boolField_ = value; }
    QString getStringField() const { return stringField_; }
    void setStringField(const QString& value) { stringField_ = value; }
    QByteArray getBytesField() const { return bytesField_; }
    void setBytesField(const QByteArray& value) { bytesField_ = value; }
    StructStatus getStatus() const { return status_; }
    void setStatus(const StructStatus& value) { status_ = value; }
    StructCategory getCategory() const { return category_; }
    void setCategory(const StructCategory& value) { category_ = value; }
    StructBaseBlockBlock getBaseBlock() const { return baseBlock_; }
    void setBaseBlock(const StructBaseBlockBlock& value) { baseBlock_ = value; }
    StructExtendedBlockBlock getExtendedBlock() const { return extendedBlock_; }
    void setExtendedBlock(const StructExtendedBlockBlock& value) { extendedBlock_ = value; }
private:
    int8_t int8Field_ = 1;
    int16_t int16Field_ = 2;
    int32_t int32Field_ = 3;
    int64_t int64Field_ = 4;
    uint8_t uint8Field_ = 5;
    uint16_t uint16Field_ = 6;
    uint32_t uint32Field_ = 7;
    uint64_t uint64Field_ = 8;
    float float32Field_ = 1.000000;
    double float64Field_ = 2.000000;
    bool boolField_ = true;
    QString stringField_ = "test";
    QByteArray bytesField_ = "data";
    StructStatus status_ = /* complex expression */;
    StructCategory category_ = /* complex expression */;
    StructBaseBlockBlock baseBlock_;
    StructExtendedBlockBlock extendedBlock_;
};
Q_DECLARE_METATYPE(AllTypesStructModel)


// ContainerStruct结构体
class MODEL_EXPORT ContainerStructModel : public IModel {
public:
    ContainerStructModel() = default;
    
    // 实现 IModel 接口
    QCborMap toCbor() const override {
        QCborMap map;
        QCborArray intArrayArray;
        for (const auto& item : intArray_) {
            intArrayArray.append(item.toCbor());
        }
        map.insert(QLatin1String("intArray"), intArrayArray);
        QCborArray stringArrayArray;
        for (const auto& item : stringArray_) {
            stringArrayArray.append(item.toCbor());
        }
        map.insert(QLatin1String("stringArray"), stringArrayArray);
        QCborArray statusArrayArray;
        for (const auto& item : statusArray_) {
            statusArrayArray.append(item.toCbor());
        }
        map.insert(QLatin1String("statusArray"), statusArrayArray);
        QCborArray categoryArrayArray;
        for (const auto& item : categoryArray_) {
            categoryArrayArray.append(item.toCbor());
        }
        map.insert(QLatin1String("categoryArray"), categoryArrayArray);
        QCborArray blockArrayArray;
        for (const auto& item : blockArray_) {
            blockArrayArray.append(item.toCbor());
        }
        map.insert(QLatin1String("blockArray"), blockArrayArray);
                if (optionalInt_) {
            map.insert(QLatin1String("optionalInt"), optionalInt_->toCbor());
        }
                if (optionalString_) {
            map.insert(QLatin1String("optionalString"), optionalString_->toCbor());
        }
                if (optionalStatus_) {
            map.insert(QLatin1String("optionalStatus"), optionalStatus_->toCbor());
        }
                if (optionalCategory_) {
            map.insert(QLatin1String("optionalCategory"), optionalCategory_->toCbor());
        }
                if (optionalBlock_) {
            map.insert(QLatin1String("optionalBlock"), optionalBlock_->toCbor());
        }
        QCborMap intMapMap;
        for (auto it = intMap_.cbegin(); it != intMap_.cend(); ++it) {
            intMapMap.insert(it.key(), it.value().toCbor());
        }
        map.insert(QLatin1String("intMap"), intMapMap);
        QCborMap stringMapMap;
        for (auto it = stringMap_.cbegin(); it != stringMap_.cend(); ++it) {
            stringMapMap.insert(it.key(), it.value().toCbor());
        }
        map.insert(QLatin1String("stringMap"), stringMapMap);
        QCborMap statusMapMap;
        for (auto it = statusMap_.cbegin(); it != statusMap_.cend(); ++it) {
            statusMapMap.insert(it.key(), it.value().toCbor());
        }
        map.insert(QLatin1String("statusMap"), statusMapMap);
        QCborMap categoryMapMap;
        for (auto it = categoryMap_.cbegin(); it != categoryMap_.cend(); ++it) {
            categoryMapMap.insert(it.key(), it.value().toCbor());
        }
        map.insert(QLatin1String("categoryMap"), categoryMapMap);
        QCborMap blockMapMap;
        for (auto it = blockMap_.cbegin(); it != blockMap_.cend(); ++it) {
            blockMapMap.insert(it.key(), it.value().toCbor());
        }
        map.insert(QLatin1String("blockMap"), blockMapMap);
        return map;
    }
    
    void fromCbor(const QCborMap& map) override {
        QCborValue tmpValue;
        tmpValue = map.value(QLatin1String("intArray"));
        if (tmpValue.isArray()) {
            QCborArray intArrayArray = tmpValue.toArray();
            QVector<int32_t> intArrayList;
            for (const auto& item : intArrayArray) {
                int32_t itemValue;
                itemValue.fromCbor(item.toMap());
                intArrayList.append(itemValue);
            }
            intArray_ = intArrayList;
        }
        tmpValue = map.value(QLatin1String("stringArray"));
        if (tmpValue.isArray()) {
            QCborArray stringArrayArray = tmpValue.toArray();
            QVector<QString> stringArrayList;
            for (const auto& item : stringArrayArray) {
                stringArrayList.append(item.toString());QString itemValue;
                itemValue.fromCbor(item.toMap());
                stringArrayList.append(itemValue);
            }
            stringArray_ = stringArrayList;
        }
        tmpValue = map.value(QLatin1String("statusArray"));
        if (tmpValue.isArray()) {
            QCborArray statusArrayArray = tmpValue.toArray();
            QVector<StructStatus> statusArrayList;
            for (const auto& item : statusArrayArray) {
                StructStatus itemValue;
                itemValue.fromCbor(item.toMap());
                statusArrayList.append(itemValue);
            }
            statusArray_ = statusArrayList;
        }
        tmpValue = map.value(QLatin1String("categoryArray"));
        if (tmpValue.isArray()) {
            QCborArray categoryArrayArray = tmpValue.toArray();
            QVector<StructCategory> categoryArrayList;
            for (const auto& item : categoryArrayArray) {
                StructCategory itemValue;
                itemValue.fromCbor(item.toMap());
                categoryArrayList.append(itemValue);
            }
            categoryArray_ = categoryArrayList;
        }
        tmpValue = map.value(QLatin1String("blockArray"));
        if (tmpValue.isArray()) {
            QCborArray blockArrayArray = tmpValue.toArray();
            QVector<StructBaseBlockBlock> blockArrayList;
            for (const auto& item : blockArrayArray) {
                StructBaseBlockBlock itemValue;
                itemValue.fromCbor(item.toMap());
                blockArrayList.append(itemValue);
            }
            blockArray_ = blockArrayList;
        }
        tmpValue = map.value(QLatin1String("optionalInt"));
        if (!tmpValue.isNull()) {
            int32_t itemValue;
            itemValue.fromCbor(tmpValue.toMap());
            optionalInt_ = itemValue;
        }
        tmpValue = map.value(QLatin1String("optionalString"));
        if (!tmpValue.isNull()) {
            optionalString_ = tmpValue.toString();QString itemValue;
            itemValue.fromCbor(tmpValue.toMap());
            optionalString_ = itemValue;
        }
        tmpValue = map.value(QLatin1String("optionalStatus"));
        if (!tmpValue.isNull()) {
            StructStatus itemValue;
            itemValue.fromCbor(tmpValue.toMap());
            optionalStatus_ = itemValue;
        }
        tmpValue = map.value(QLatin1String("optionalCategory"));
        if (!tmpValue.isNull()) {
            StructCategory itemValue;
            itemValue.fromCbor(tmpValue.toMap());
            optionalCategory_ = itemValue;
        }
        tmpValue = map.value(QLatin1String("optionalBlock"));
        if (!tmpValue.isNull()) {
            StructBaseBlockBlock itemValue;
            itemValue.fromCbor(tmpValue.toMap());
            optionalBlock_ = itemValue;
        }
        tmpValue = map.value(QLatin1String("intMap"));
        if (tmpValue.isMap()) {
            QCborMap intMapMap = tmpValue.toMap();
            QMap<QString, int32_t> intMapResult;
            for (auto it = intMapMap.cbegin(); it != intMapMap.cend(); ++it) {
                int32_t itemValue;
                itemValue.fromCbor(it.value().toMap());
                intMapResult.insert(it.key().toString(), itemValue);
            }
            intMap_ = intMapResult;
        }
        tmpValue = map.value(QLatin1String("stringMap"));
        if (tmpValue.isMap()) {
            QCborMap stringMapMap = tmpValue.toMap();
            QMap<QString, QString> stringMapResult;
            for (auto it = stringMapMap.cbegin(); it != stringMapMap.cend(); ++it) {
                stringMapResult.insert(it.key().toString(), it.value().toString());QString itemValue;
                itemValue.fromCbor(it.value().toMap());
                stringMapResult.insert(it.key().toString(), itemValue);
            }
            stringMap_ = stringMapResult;
        }
        tmpValue = map.value(QLatin1String("statusMap"));
        if (tmpValue.isMap()) {
            QCborMap statusMapMap = tmpValue.toMap();
            QMap<QString, StructStatus> statusMapResult;
            for (auto it = statusMapMap.cbegin(); it != statusMapMap.cend(); ++it) {
                StructStatus itemValue;
                itemValue.fromCbor(it.value().toMap());
                statusMapResult.insert(it.key().toString(), itemValue);
            }
            statusMap_ = statusMapResult;
        }
        tmpValue = map.value(QLatin1String("categoryMap"));
        if (tmpValue.isMap()) {
            QCborMap categoryMapMap = tmpValue.toMap();
            QMap<QString, StructCategory> categoryMapResult;
            for (auto it = categoryMapMap.cbegin(); it != categoryMapMap.cend(); ++it) {
                StructCategory itemValue;
                itemValue.fromCbor(it.value().toMap());
                categoryMapResult.insert(it.key().toString(), itemValue);
            }
            categoryMap_ = categoryMapResult;
        }
        tmpValue = map.value(QLatin1String("blockMap"));
        if (tmpValue.isMap()) {
            QCborMap blockMapMap = tmpValue.toMap();
            QMap<QString, StructBaseBlockBlock> blockMapResult;
            for (auto it = blockMapMap.cbegin(); it != blockMapMap.cend(); ++it) {
                StructBaseBlockBlock itemValue;
                itemValue.fromCbor(it.value().toMap());
                blockMapResult.insert(it.key().toString(), itemValue);
            }
            blockMap_ = blockMapResult;
        }
    }
    
    QString name() const override {
        return QLatin1String("ContainerStruct");
    }
    
    QStringList fields() const override {
        return QStringList{QLatin1String("intArray"), QLatin1String("stringArray"), QLatin1String("statusArray"), QLatin1String("categoryArray"), QLatin1String("blockArray"), QLatin1String("optionalInt"), QLatin1String("optionalString"), QLatin1String("optionalStatus"), QLatin1String("optionalCategory"), QLatin1String("optionalBlock"), QLatin1String("intMap"), QLatin1String("stringMap"), QLatin1String("statusMap"), QLatin1String("categoryMap"), QLatin1String("blockMap")};
    }
    
    QString fieldType(const QString& fieldName) const override {
        if (fieldName == QLatin1String("intArray")) return QLatin1String("int32");
        if (fieldName == QLatin1String("stringArray")) return QLatin1String("string");
        if (fieldName == QLatin1String("statusArray")) return QLatin1String("StructStatus");
        if (fieldName == QLatin1String("categoryArray")) return QLatin1String("StructCategory");
        if (fieldName == QLatin1String("blockArray")) return QLatin1String("StructBaseBlock");
        if (fieldName == QLatin1String("optionalInt")) return QLatin1String("int32");
        if (fieldName == QLatin1String("optionalString")) return QLatin1String("string");
        if (fieldName == QLatin1String("optionalStatus")) return QLatin1String("StructStatus");
        if (fieldName == QLatin1String("optionalCategory")) return QLatin1String("StructCategory");
        if (fieldName == QLatin1String("optionalBlock")) return QLatin1String("StructBaseBlock");
        if (fieldName == QLatin1String("intMap")) return QLatin1String("int32");
        if (fieldName == QLatin1String("stringMap")) return QLatin1String("string");
        if (fieldName == QLatin1String("statusMap")) return QLatin1String("StructStatus");
        if (fieldName == QLatin1String("categoryMap")) return QLatin1String("StructCategory");
        if (fieldName == QLatin1String("blockMap")) return QLatin1String("StructBaseBlock");
        return QString();
    }
    
    QString fieldContainerType(const QString& fieldName) const override {
        if (fieldName == QLatin1String("intArray")) return QLatin1String("array");
        if (fieldName == QLatin1String("stringArray")) return QLatin1String("array");
        if (fieldName == QLatin1String("statusArray")) return QLatin1String("array");
        if (fieldName == QLatin1String("categoryArray")) return QLatin1String("array");
        if (fieldName == QLatin1String("blockArray")) return QLatin1String("array");
        if (fieldName == QLatin1String("optionalInt")) return QLatin1String("optional");
        if (fieldName == QLatin1String("optionalString")) return QLatin1String("optional");
        if (fieldName == QLatin1String("optionalStatus")) return QLatin1String("optional");
        if (fieldName == QLatin1String("optionalCategory")) return QLatin1String("optional");
        if (fieldName == QLatin1String("optionalBlock")) return QLatin1String("optional");
        if (fieldName == QLatin1String("intMap")) return QLatin1String("map");
        if (fieldName == QLatin1String("stringMap")) return QLatin1String("map");
        if (fieldName == QLatin1String("statusMap")) return QLatin1String("map");
        if (fieldName == QLatin1String("categoryMap")) return QLatin1String("map");
        if (fieldName == QLatin1String("blockMap")) return QLatin1String("map");
        return QLatin1String("none");
    }

    // 字段访问器
    QVector<int32_t> getIntArray() const { return intArray_; }
    void setIntArray(const QVector<int32_t>& value) { intArray_ = value; }
    QVector<QString> getStringArray() const { return stringArray_; }
    void setStringArray(const QVector<QString>& value) { stringArray_ = value; }
    QVector<StructStatus> getStatusArray() const { return statusArray_; }
    void setStatusArray(const QVector<StructStatus>& value) { statusArray_ = value; }
    QVector<StructCategory> getCategoryArray() const { return categoryArray_; }
    void setCategoryArray(const QVector<StructCategory>& value) { categoryArray_ = value; }
    QVector<StructBaseBlockBlock> getBlockArray() const { return blockArray_; }
    void setBlockArray(const QVector<StructBaseBlockBlock>& value) { blockArray_ = value; }
    std::optional<int32_t> getOptionalInt() const { return optionalInt_; }
    void setOptionalInt(const std::optional<int32_t>& value) { optionalInt_ = value; }
    std::optional<QString> getOptionalString() const { return optionalString_; }
    void setOptionalString(const std::optional<QString>& value) { optionalString_ = value; }
    std::optional<StructStatus> getOptionalStatus() const { return optionalStatus_; }
    void setOptionalStatus(const std::optional<StructStatus>& value) { optionalStatus_ = value; }
    std::optional<StructCategory> getOptionalCategory() const { return optionalCategory_; }
    void setOptionalCategory(const std::optional<StructCategory>& value) { optionalCategory_ = value; }
    std::optional<StructBaseBlockBlock> getOptionalBlock() const { return optionalBlock_; }
    void setOptionalBlock(const std::optional<StructBaseBlockBlock>& value) { optionalBlock_ = value; }
    QMap<QString, int32_t> getIntMap() const { return intMap_; }
    void setIntMap(const QMap<QString, int32_t>& value) { intMap_ = value; }
    QMap<QString, QString> getStringMap() const { return stringMap_; }
    void setStringMap(const QMap<QString, QString>& value) { stringMap_ = value; }
    QMap<QString, StructStatus> getStatusMap() const { return statusMap_; }
    void setStatusMap(const QMap<QString, StructStatus>& value) { statusMap_ = value; }
    QMap<QString, StructCategory> getCategoryMap() const { return categoryMap_; }
    void setCategoryMap(const QMap<QString, StructCategory>& value) { categoryMap_ = value; }
    QMap<QString, StructBaseBlockBlock> getBlockMap() const { return blockMap_; }
    void setBlockMap(const QMap<QString, StructBaseBlockBlock>& value) { blockMap_ = value; }
private:
    QVector<int32_t> intArray_ = [
    "1",
    "2",
    "3"
];
    QVector<QString> stringArray_;
    QVector<StructStatus> statusArray_ = [
    "/* complex expression */",
    "/* complex expression */"
];
    QVector<StructCategory> categoryArray_;
    QVector<StructBaseBlockBlock> blockArray_;
    std::optional<int32_t> optionalInt_ = 42;
    std::optional<QString> optionalString_;
    std::optional<StructStatus> optionalStatus_;
    std::optional<StructCategory> optionalCategory_ = /* complex expression */;
    std::optional<StructBaseBlockBlock> optionalBlock_;
    QMap<QString, int32_t> intMap_;
    QMap<QString, QString> stringMap_;
    QMap<QString, StructStatus> statusMap_;
    QMap<QString, StructCategory> categoryMap_;
    QMap<QString, StructBaseBlockBlock> blockMap_;
};
Q_DECLARE_METATYPE(ContainerStructModel)


// ComprehensiveStruct结构体
class MODEL_EXPORT ComprehensiveStructModel : public IModel {
public:
    ComprehensiveStructModel() = default;
    
    // 实现 IModel 接口
    QCborMap toCbor() const override {
        QCborMap map;
                map.insert(QLatin1String("name"), name_.toCbor());
                map.insert(QLatin1String("status"), status_.toCbor());
                map.insert(QLatin1String("baseBlock"), baseBlock_.toCbor());
                map.insert(QLatin1String("extendedBlock"), extendedBlock_.toCbor());
        QCborArray blockListArray;
        for (const auto& item : blockList_) {
            blockListArray.append(item.toCbor());
        }
        map.insert(QLatin1String("blockList"), blockListArray);
                if (optionalCategory_) {
            map.insert(QLatin1String("optionalCategory"), optionalCategory_->toCbor());
        }
        QCborMap configMapMap;
        for (auto it = configMap_.cbegin(); it != configMap_.cend(); ++it) {
            configMapMap.insert(it.key(), it.value().toCbor());
        }
        map.insert(QLatin1String("configMap"), configMapMap);
        return map;
    }
    
    void fromCbor(const QCborMap& map) override {
        QCborValue tmpValue;
        tmpValue = map.value(QLatin1String("name"));
        if (!tmpValue.isNull()) {
            name_ = tmpValue.toString();name_.fromCbor(tmpValue.toMap());
        }
        tmpValue = map.value(QLatin1String("status"));
        if (!tmpValue.isNull()) {
            status_.fromCbor(tmpValue.toMap());
        }
        tmpValue = map.value(QLatin1String("baseBlock"));
        if (!tmpValue.isNull()) {
            baseBlock_.fromCbor(tmpValue.toMap());
        }
        tmpValue = map.value(QLatin1String("extendedBlock"));
        if (!tmpValue.isNull()) {
            extendedBlock_.fromCbor(tmpValue.toMap());
        }
        tmpValue = map.value(QLatin1String("blockList"));
        if (tmpValue.isArray()) {
            QCborArray blockListArray = tmpValue.toArray();
            QVector<StructBaseBlockBlock> blockListList;
            for (const auto& item : blockListArray) {
                StructBaseBlockBlock itemValue;
                itemValue.fromCbor(item.toMap());
                blockListList.append(itemValue);
            }
            blockList_ = blockListList;
        }
        tmpValue = map.value(QLatin1String("optionalCategory"));
        if (!tmpValue.isNull()) {
            StructCategory itemValue;
            itemValue.fromCbor(tmpValue.toMap());
            optionalCategory_ = itemValue;
        }
        tmpValue = map.value(QLatin1String("configMap"));
        if (tmpValue.isMap()) {
            QCborMap configMapMap = tmpValue.toMap();
            QMap<QString, QString> configMapResult;
            for (auto it = configMapMap.cbegin(); it != configMapMap.cend(); ++it) {
                configMapResult.insert(it.key().toString(), it.value().toString());QString itemValue;
                itemValue.fromCbor(it.value().toMap());
                configMapResult.insert(it.key().toString(), itemValue);
            }
            configMap_ = configMapResult;
        }
    }
    
    QString name() const override {
        return QLatin1String("ComprehensiveStruct");
    }
    
    QStringList fields() const override {
        return QStringList{QLatin1String("name"), QLatin1String("status"), QLatin1String("baseBlock"), QLatin1String("extendedBlock"), QLatin1String("blockList"), QLatin1String("optionalCategory"), QLatin1String("configMap")};
    }
    
    QString fieldType(const QString& fieldName) const override {
        if (fieldName == QLatin1String("name")) return QLatin1String("string");
        if (fieldName == QLatin1String("status")) return QLatin1String("StructStatus");
        if (fieldName == QLatin1String("baseBlock")) return QLatin1String("StructBaseBlock");
        if (fieldName == QLatin1String("extendedBlock")) return QLatin1String("StructExtendedBlock");
        if (fieldName == QLatin1String("blockList")) return QLatin1String("StructBaseBlock");
        if (fieldName == QLatin1String("optionalCategory")) return QLatin1String("StructCategory");
        if (fieldName == QLatin1String("configMap")) return QLatin1String("string");
        return QString();
    }
    
    QString fieldContainerType(const QString& fieldName) const override {
        if (fieldName == QLatin1String("name")) return QLatin1String("none");
        if (fieldName == QLatin1String("status")) return QLatin1String("none");
        if (fieldName == QLatin1String("baseBlock")) return QLatin1String("none");
        if (fieldName == QLatin1String("extendedBlock")) return QLatin1String("none");
        if (fieldName == QLatin1String("blockList")) return QLatin1String("array");
        if (fieldName == QLatin1String("optionalCategory")) return QLatin1String("optional");
        if (fieldName == QLatin1String("configMap")) return QLatin1String("map");
        return QLatin1String("none");
    }

    // 字段访问器
    QString getName() const { return name_; }
    void setName(const QString& value) { name_ = value; }
    StructStatus getStatus() const { return status_; }
    void setStatus(const StructStatus& value) { status_ = value; }
    StructBaseBlockBlock getBaseBlock() const { return baseBlock_; }
    void setBaseBlock(const StructBaseBlockBlock& value) { baseBlock_ = value; }
    StructExtendedBlockBlock getExtendedBlock() const { return extendedBlock_; }
    void setExtendedBlock(const StructExtendedBlockBlock& value) { extendedBlock_ = value; }
    QVector<StructBaseBlockBlock> getBlockList() const { return blockList_; }
    void setBlockList(const QVector<StructBaseBlockBlock>& value) { blockList_ = value; }
    std::optional<StructCategory> getOptionalCategory() const { return optionalCategory_; }
    void setOptionalCategory(const std::optional<StructCategory>& value) { optionalCategory_ = value; }
    QMap<QString, QString> getConfigMap() const { return configMap_; }
    void setConfigMap(const QMap<QString, QString>& value) { configMap_ = value; }
private:
    QString name_ = "综合测试";
    StructStatus status_ = /* complex expression */;
    StructBaseBlockBlock baseBlock_;
    StructExtendedBlockBlock extendedBlock_;
    QVector<StructBaseBlockBlock> blockList_;
    std::optional<StructCategory> optionalCategory_;
    QMap<QString, QString> configMap_;
};
Q_DECLARE_METATYPE(ComprehensiveStructModel)


} // namespace examples
} // namespace structs
