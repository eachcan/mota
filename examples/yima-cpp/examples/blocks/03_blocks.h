#pragma once

// 此文件由 Mota 代码生成器自动生成
// 生成时间: 2025-06-13 16:50:58
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
Q_DECLARE_METATYPE(BlockAnnotationAnnotation)


// BlockValueAnnotation注解
class MODEL_EXPORT BlockValueAnnotationAnnotation : public IAnnotation {
public:
    BlockValueAnnotationAnnotation() = default;
    
    // 实现IAnnotation接口
    QString name() const override {
        return QLatin1String("BlockValueAnnotation");
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
Q_DECLARE_METATYPE(BlockValueAnnotationAnnotation)


// BlockStatus枚举
enum class BlockStatus {
    ACTIVE = 1,
    INACTIVE = 2,
    PENDING = 3
};


// BlockType枚举
enum class BlockType {
    PRIMARY,
    SECONDARY,
    AUXILIARY
};


// BaseBlock块定义
class MODEL_EXPORT BaseBlockBlock : public IBlock {
public:
    BaseBlockBlock() = default;
    
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
            name_ = tmpValue.toString();
        }
    }
    
    QString name() const override {
        return QLatin1String("BaseBlock");
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
        return QLatin1String("BaseBlock");
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
Q_DECLARE_METATYPE(BaseBlockBlock)


// ExtendedBlock块定义
class MODEL_EXPORT ExtendedBlockBlock : public BaseBlockBlock, public IBlock {
public:
    ExtendedBlockBlock() = default;
    
    // 实现 IBlock 接口
    QCborMap toCbor() const override {
        QCborMap map = BaseBlockBlock::toCbor();
        map.insert(QLatin1String("active"), active_.toCbor());
        map.insert(QLatin1String("status"), status_.toCbor());
        map.insert(QLatin1String("type"), type_.toCbor());
        return map;
    }
    
    void fromCbor(const QCborMap& map) override {
        BaseBlockBlock::fromCbor(map);
        QCborValue tmpValue;
        tmpValue = map.value(QLatin1String("active"));
        if (!tmpValue.isNull()) {
            active_ = tmpValue.toBool();
        }
        tmpValue = map.value(QLatin1String("status"));
        if (!tmpValue.isNull()) {
            status_.fromCbor(tmpValue.toMap());
        }
        tmpValue = map.value(QLatin1String("type"));
        if (!tmpValue.isNull()) {
            type_.fromCbor(tmpValue.toMap());
        }
    }
    
    QString name() const override {
        return QLatin1String("ExtendedBlock");
    }
    
    QStringList fields() const override {
        return QStringList{QLatin1String("active"), QLatin1String("status"), QLatin1String("type")};
    }
    
    QString fieldType(const QString& fieldName) const override {
        if (fieldName == QLatin1String("active")) return QLatin1String("bool");
        if (fieldName == QLatin1String("status")) return QLatin1String("BlockStatus");
        if (fieldName == QLatin1String("type")) return QLatin1String("BlockType");
        return QString();
    }
    
    QString fieldContainerType(const QString& fieldName) const override {
        if (fieldName == QLatin1String("active")) return QLatin1String("none");
        if (fieldName == QLatin1String("status")) return QLatin1String("none");
        if (fieldName == QLatin1String("type")) return QLatin1String("none");
        return QLatin1String("none");
    }
    
    QList<QSharedPointer<IAnnotation>> annotations() const override {
        QList<QSharedPointer<IAnnotation>> result;
        return result;
    }
    
    QList<QSharedPointer<IAnnotation>> fieldAnnotation(const QString& fieldName) const override {
        if (fieldName == QLatin1String("active")) {
            QList<QSharedPointer<IAnnotation>> result;
            return result;
        }
        if (fieldName == QLatin1String("status")) {
            QList<QSharedPointer<IAnnotation>> result;
            return result;
        }
        if (fieldName == QLatin1String("type")) {
            QList<QSharedPointer<IAnnotation>> result;
            return result;
        }
        return QList<QSharedPointer<IAnnotation>>();
    }
    
    QString description() const override {
        return QLatin1String("ExtendedBlock");
    }
    
    QString fieldDescription(const QString& fieldName) const override {
        if (fieldName == QLatin1String("active")) return QLatin1String("active");
        if (fieldName == QLatin1String("status")) return QLatin1String("status");
        if (fieldName == QLatin1String("type")) return QLatin1String("type");
        return QString();
    }
    
    QVariant value(const QString& fieldName) const override {
        if (fieldName == QLatin1String("active")) return QVariant::fromValue(active_);
        if (fieldName == QLatin1String("status")) return QVariant::fromValue(status_);
        if (fieldName == QLatin1String("type")) return QVariant::fromValue(type_);
        return QVariant();
    }
    
    void value(const QString& fieldName, const QVariant& value) override {
        if (fieldName == QLatin1String("active")) {
            active_ = value.value<bool>();
            return;
        }
        if (fieldName == QLatin1String("status")) {
            status_ = value.value<BlockStatus>();
            return;
        }
        if (fieldName == QLatin1String("type")) {
            type_ = value.value<BlockType>();
            return;
        }
    }
    
    // 字段访问器
    bool getActive() const { return active_; }
    void setActive(const bool& value) { active_ = value; }
    BlockStatus getStatus() const { return status_; }
    void setStatus(const BlockStatus& value) { status_ = value; }
    BlockType getType() const { return type_; }
    void setType(const BlockType& value) { type_ = value; }
private:
    bool active_ = true;
    BlockStatus status_ = /* complex expression */;
    BlockType type_ = /* complex expression */;
};
Q_DECLARE_METATYPE(ExtendedBlockBlock)


// AnnotatedBlock块定义
class MODEL_EXPORT AnnotatedBlockBlock : public IBlock {
public:
    AnnotatedBlockBlock() = default;
    
    // 实现 IBlock 接口
    QCborMap toCbor() const override {
        QCborMap map;
        map.insert(QLatin1String("data"), data_.toCbor());
        map.insert(QLatin1String("config"), config_.toCbor());
        return map;
    }
    
    void fromCbor(const QCborMap& map) override {
        QCborValue tmpValue;
        tmpValue = map.value(QLatin1String("data"));
        if (!tmpValue.isNull()) {
            data_ = tmpValue.toString();
        }
        tmpValue = map.value(QLatin1String("config"));
        if (!tmpValue.isNull()) {
            config_ = tmpValue.toString();
        }
    }
    
    QString name() const override {
        return QLatin1String("AnnotatedBlock");
    }
    
    QStringList fields() const override {
        return QStringList{QLatin1String("data"), QLatin1String("config")};
    }
    
    QString fieldType(const QString& fieldName) const override {
        if (fieldName == QLatin1String("data")) return QLatin1String("string");
        if (fieldName == QLatin1String("config")) return QLatin1String("string");
        return QString();
    }
    
    QString fieldContainerType(const QString& fieldName) const override {
        if (fieldName == QLatin1String("data")) return QLatin1String("none");
        if (fieldName == QLatin1String("config")) return QLatin1String("none");
        return QLatin1String("none");
    }
    
    QList<QSharedPointer<IAnnotation>> annotations() const override {
        QList<QSharedPointer<IAnnotation>> result;
        result.append(QSharedPointer<IAnnotation>(new BlockValueAnnotationAnnotation()));
        result.append(QSharedPointer<IAnnotation>(new BlockAnnotationAnnotation()));
        return result;
    }
    
    QList<QSharedPointer<IAnnotation>> fieldAnnotation(const QString& fieldName) const override {
        if (fieldName == QLatin1String("data")) {
            QList<QSharedPointer<IAnnotation>> result;
            result.append(QSharedPointer<IAnnotation>(new BlockValueAnnotationAnnotation()));
            return result;
        }
        if (fieldName == QLatin1String("config")) {
            QList<QSharedPointer<IAnnotation>> result;
            result.append(QSharedPointer<IAnnotation>(new BlockAnnotationAnnotation()));
            return result;
        }
        return QList<QSharedPointer<IAnnotation>>();
    }
    
    QString description() const override {
        return QLatin1String("AnnotatedBlock");
    }
    
    QString fieldDescription(const QString& fieldName) const override {
        if (fieldName == QLatin1String("data")) return QLatin1String("data");
        if (fieldName == QLatin1String("config")) return QLatin1String("config");
        return QString();
    }
    
    QVariant value(const QString& fieldName) const override {
        if (fieldName == QLatin1String("data")) return QVariant::fromValue(data_);
        if (fieldName == QLatin1String("config")) return QVariant::fromValue(config_);
        return QVariant();
    }
    
    void value(const QString& fieldName, const QVariant& value) override {
        if (fieldName == QLatin1String("data")) {
            data_ = value.value<QString>();
            return;
        }
        if (fieldName == QLatin1String("config")) {
            config_ = value.value<QString>();
            return;
        }
    }
    
    // 字段访问器
    QString getData() const { return data_; }
    void setData(const QString& value) { data_ = value; }
    QString getConfig() const { return config_; }
    void setConfig(const QString& value) { config_ = value; }
private:
    QString data_ = "";
    QString config_ = "";
};
Q_DECLARE_METATYPE(AnnotatedBlockBlock)


// AllTypesBlock块定义
class MODEL_EXPORT AllTypesBlockBlock : public IBlock {
public:
    AllTypesBlockBlock() = default;
    
    // 实现 IBlock 接口
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
        map.insert(QLatin1String("type"), type_.toCbor());
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
            boolField_ = tmpValue.toBool();
        }
        tmpValue = map.value(QLatin1String("stringField"));
        if (!tmpValue.isNull()) {
            stringField_ = tmpValue.toString();
        }
        tmpValue = map.value(QLatin1String("bytesField"));
        if (!tmpValue.isNull()) {
            bytesField_ = tmpValue.toByteArray();
        }
        tmpValue = map.value(QLatin1String("status"));
        if (!tmpValue.isNull()) {
            status_.fromCbor(tmpValue.toMap());
        }
        tmpValue = map.value(QLatin1String("type"));
        if (!tmpValue.isNull()) {
            type_.fromCbor(tmpValue.toMap());
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
        return QLatin1String("AllTypesBlock");
    }
    
    QStringList fields() const override {
        return QStringList{QLatin1String("int8Field"), QLatin1String("int16Field"), QLatin1String("int32Field"), QLatin1String("int64Field"), QLatin1String("uint8Field"), QLatin1String("uint16Field"), QLatin1String("uint32Field"), QLatin1String("uint64Field"), QLatin1String("float32Field"), QLatin1String("float64Field"), QLatin1String("boolField"), QLatin1String("stringField"), QLatin1String("bytesField"), QLatin1String("status"), QLatin1String("type"), QLatin1String("baseBlock"), QLatin1String("extendedBlock")};
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
        if (fieldName == QLatin1String("status")) return QLatin1String("BlockStatus");
        if (fieldName == QLatin1String("type")) return QLatin1String("BlockType");
        if (fieldName == QLatin1String("baseBlock")) return QLatin1String("BaseBlock");
        if (fieldName == QLatin1String("extendedBlock")) return QLatin1String("ExtendedBlock");
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
        if (fieldName == QLatin1String("type")) return QLatin1String("none");
        if (fieldName == QLatin1String("baseBlock")) return QLatin1String("none");
        if (fieldName == QLatin1String("extendedBlock")) return QLatin1String("none");
        return QLatin1String("none");
    }
    
    QList<QSharedPointer<IAnnotation>> annotations() const override {
        QList<QSharedPointer<IAnnotation>> result;
        return result;
    }
    
    QList<QSharedPointer<IAnnotation>> fieldAnnotation(const QString& fieldName) const override {
        if (fieldName == QLatin1String("int8Field")) {
            QList<QSharedPointer<IAnnotation>> result;
            return result;
        }
        if (fieldName == QLatin1String("int16Field")) {
            QList<QSharedPointer<IAnnotation>> result;
            return result;
        }
        if (fieldName == QLatin1String("int32Field")) {
            QList<QSharedPointer<IAnnotation>> result;
            return result;
        }
        if (fieldName == QLatin1String("int64Field")) {
            QList<QSharedPointer<IAnnotation>> result;
            return result;
        }
        if (fieldName == QLatin1String("uint8Field")) {
            QList<QSharedPointer<IAnnotation>> result;
            return result;
        }
        if (fieldName == QLatin1String("uint16Field")) {
            QList<QSharedPointer<IAnnotation>> result;
            return result;
        }
        if (fieldName == QLatin1String("uint32Field")) {
            QList<QSharedPointer<IAnnotation>> result;
            return result;
        }
        if (fieldName == QLatin1String("uint64Field")) {
            QList<QSharedPointer<IAnnotation>> result;
            return result;
        }
        if (fieldName == QLatin1String("float32Field")) {
            QList<QSharedPointer<IAnnotation>> result;
            return result;
        }
        if (fieldName == QLatin1String("float64Field")) {
            QList<QSharedPointer<IAnnotation>> result;
            return result;
        }
        if (fieldName == QLatin1String("boolField")) {
            QList<QSharedPointer<IAnnotation>> result;
            return result;
        }
        if (fieldName == QLatin1String("stringField")) {
            QList<QSharedPointer<IAnnotation>> result;
            return result;
        }
        if (fieldName == QLatin1String("bytesField")) {
            QList<QSharedPointer<IAnnotation>> result;
            return result;
        }
        if (fieldName == QLatin1String("status")) {
            QList<QSharedPointer<IAnnotation>> result;
            return result;
        }
        if (fieldName == QLatin1String("type")) {
            QList<QSharedPointer<IAnnotation>> result;
            return result;
        }
        if (fieldName == QLatin1String("baseBlock")) {
            QList<QSharedPointer<IAnnotation>> result;
            return result;
        }
        if (fieldName == QLatin1String("extendedBlock")) {
            QList<QSharedPointer<IAnnotation>> result;
            return result;
        }
        return QList<QSharedPointer<IAnnotation>>();
    }
    
    QString description() const override {
        return QLatin1String("AllTypesBlock");
    }
    
    QString fieldDescription(const QString& fieldName) const override {
        if (fieldName == QLatin1String("int8Field")) return QLatin1String("int8Field");
        if (fieldName == QLatin1String("int16Field")) return QLatin1String("int16Field");
        if (fieldName == QLatin1String("int32Field")) return QLatin1String("int32Field");
        if (fieldName == QLatin1String("int64Field")) return QLatin1String("int64Field");
        if (fieldName == QLatin1String("uint8Field")) return QLatin1String("uint8Field");
        if (fieldName == QLatin1String("uint16Field")) return QLatin1String("uint16Field");
        if (fieldName == QLatin1String("uint32Field")) return QLatin1String("uint32Field");
        if (fieldName == QLatin1String("uint64Field")) return QLatin1String("uint64Field");
        if (fieldName == QLatin1String("float32Field")) return QLatin1String("float32Field");
        if (fieldName == QLatin1String("float64Field")) return QLatin1String("float64Field");
        if (fieldName == QLatin1String("boolField")) return QLatin1String("boolField");
        if (fieldName == QLatin1String("stringField")) return QLatin1String("stringField");
        if (fieldName == QLatin1String("bytesField")) return QLatin1String("bytesField");
        if (fieldName == QLatin1String("status")) return QLatin1String("status");
        if (fieldName == QLatin1String("type")) return QLatin1String("type");
        if (fieldName == QLatin1String("baseBlock")) return QLatin1String("baseBlock");
        if (fieldName == QLatin1String("extendedBlock")) return QLatin1String("extendedBlock");
        return QString();
    }
    
    QVariant value(const QString& fieldName) const override {
        if (fieldName == QLatin1String("int8Field")) return QVariant::fromValue(int8Field_);
        if (fieldName == QLatin1String("int16Field")) return QVariant::fromValue(int16Field_);
        if (fieldName == QLatin1String("int32Field")) return QVariant::fromValue(int32Field_);
        if (fieldName == QLatin1String("int64Field")) return QVariant::fromValue(int64Field_);
        if (fieldName == QLatin1String("uint8Field")) return QVariant::fromValue(uint8Field_);
        if (fieldName == QLatin1String("uint16Field")) return QVariant::fromValue(uint16Field_);
        if (fieldName == QLatin1String("uint32Field")) return QVariant::fromValue(uint32Field_);
        if (fieldName == QLatin1String("uint64Field")) return QVariant::fromValue(uint64Field_);
        if (fieldName == QLatin1String("float32Field")) return QVariant::fromValue(float32Field_);
        if (fieldName == QLatin1String("float64Field")) return QVariant::fromValue(float64Field_);
        if (fieldName == QLatin1String("boolField")) return QVariant::fromValue(boolField_);
        if (fieldName == QLatin1String("stringField")) return QVariant::fromValue(stringField_);
        if (fieldName == QLatin1String("bytesField")) return QVariant::fromValue(bytesField_);
        if (fieldName == QLatin1String("status")) return QVariant::fromValue(status_);
        if (fieldName == QLatin1String("type")) return QVariant::fromValue(type_);
        if (fieldName == QLatin1String("baseBlock")) return QVariant::fromValue(baseBlock_);
        if (fieldName == QLatin1String("extendedBlock")) return QVariant::fromValue(extendedBlock_);
        return QVariant();
    }
    
    void value(const QString& fieldName, const QVariant& value) override {
        if (fieldName == QLatin1String("int8Field")) {
            int8Field_ = value.value<int8_t>();
            return;
        }
        if (fieldName == QLatin1String("int16Field")) {
            int16Field_ = value.value<int16_t>();
            return;
        }
        if (fieldName == QLatin1String("int32Field")) {
            int32Field_ = value.value<int32_t>();
            return;
        }
        if (fieldName == QLatin1String("int64Field")) {
            int64Field_ = value.value<int64_t>();
            return;
        }
        if (fieldName == QLatin1String("uint8Field")) {
            uint8Field_ = value.value<uint8_t>();
            return;
        }
        if (fieldName == QLatin1String("uint16Field")) {
            uint16Field_ = value.value<uint16_t>();
            return;
        }
        if (fieldName == QLatin1String("uint32Field")) {
            uint32Field_ = value.value<uint32_t>();
            return;
        }
        if (fieldName == QLatin1String("uint64Field")) {
            uint64Field_ = value.value<uint64_t>();
            return;
        }
        if (fieldName == QLatin1String("float32Field")) {
            float32Field_ = value.value<float>();
            return;
        }
        if (fieldName == QLatin1String("float64Field")) {
            float64Field_ = value.value<double>();
            return;
        }
        if (fieldName == QLatin1String("boolField")) {
            boolField_ = value.value<bool>();
            return;
        }
        if (fieldName == QLatin1String("stringField")) {
            stringField_ = value.value<QString>();
            return;
        }
        if (fieldName == QLatin1String("bytesField")) {
            bytesField_ = value.value<QByteArray>();
            return;
        }
        if (fieldName == QLatin1String("status")) {
            status_ = value.value<BlockStatus>();
            return;
        }
        if (fieldName == QLatin1String("type")) {
            type_ = value.value<BlockType>();
            return;
        }
        if (fieldName == QLatin1String("baseBlock")) {
            baseBlock_ = value.value<BaseBlockBlock>();
            return;
        }
        if (fieldName == QLatin1String("extendedBlock")) {
            extendedBlock_ = value.value<ExtendedBlockBlock>();
            return;
        }
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
    BlockStatus getStatus() const { return status_; }
    void setStatus(const BlockStatus& value) { status_ = value; }
    BlockType getType() const { return type_; }
    void setType(const BlockType& value) { type_ = value; }
    BaseBlockBlock getBaseBlock() const { return baseBlock_; }
    void setBaseBlock(const BaseBlockBlock& value) { baseBlock_ = value; }
    ExtendedBlockBlock getExtendedBlock() const { return extendedBlock_; }
    void setExtendedBlock(const ExtendedBlockBlock& value) { extendedBlock_ = value; }
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
    BlockStatus status_ = /* complex expression */;
    BlockType type_ = /* complex expression */;
    BaseBlockBlock baseBlock_;
    ExtendedBlockBlock extendedBlock_;
};
Q_DECLARE_METATYPE(AllTypesBlockBlock)


// ContainerBlock块定义
class MODEL_EXPORT ContainerBlockBlock : public IBlock {
public:
    ContainerBlockBlock() = default;
    
    // 实现 IBlock 接口
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
                stringArrayList.append(item.toString());
            }
            stringArray_ = stringArrayList;
        }
        tmpValue = map.value(QLatin1String("statusArray"));
        if (tmpValue.isArray()) {
            QCborArray statusArrayArray = tmpValue.toArray();
            QVector<BlockStatus> statusArrayList;
            for (const auto& item : statusArrayArray) {
                BlockStatus itemValue;
                itemValue.fromCbor(item.toMap());
                statusArrayList.append(itemValue);
            }
            statusArray_ = statusArrayList;
        }
        tmpValue = map.value(QLatin1String("blockArray"));
        if (tmpValue.isArray()) {
            QCborArray blockArrayArray = tmpValue.toArray();
            QVector<BaseBlockBlock> blockArrayList;
            for (const auto& item : blockArrayArray) {
                BaseBlockBlock itemValue;
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
            optionalString_ = tmpValue.toString();
        }
        tmpValue = map.value(QLatin1String("optionalStatus"));
        if (!tmpValue.isNull()) {
            BlockStatus itemValue;
            itemValue.fromCbor(tmpValue.toMap());
            optionalStatus_ = itemValue;
        }
        tmpValue = map.value(QLatin1String("optionalBlock"));
        if (!tmpValue.isNull()) {
            BaseBlockBlock itemValue;
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
                stringMapResult.insert(it.key().toString(), it.value().toString());
            }
            stringMap_ = stringMapResult;
        }
        tmpValue = map.value(QLatin1String("statusMap"));
        if (tmpValue.isMap()) {
            QCborMap statusMapMap = tmpValue.toMap();
            QMap<QString, BlockStatus> statusMapResult;
            for (auto it = statusMapMap.cbegin(); it != statusMapMap.cend(); ++it) {
                BlockStatus itemValue;
                itemValue.fromCbor(it.value().toMap());
                statusMapResult.insert(it.key().toString(), itemValue);
            }
            statusMap_ = statusMapResult;
        }
        tmpValue = map.value(QLatin1String("blockMap"));
        if (tmpValue.isMap()) {
            QCborMap blockMapMap = tmpValue.toMap();
            QMap<QString, BaseBlockBlock> blockMapResult;
            for (auto it = blockMapMap.cbegin(); it != blockMapMap.cend(); ++it) {
                BaseBlockBlock itemValue;
                itemValue.fromCbor(it.value().toMap());
                blockMapResult.insert(it.key().toString(), itemValue);
            }
            blockMap_ = blockMapResult;
        }
    }
    
    QString name() const override {
        return QLatin1String("ContainerBlock");
    }
    
    QStringList fields() const override {
        return QStringList{QLatin1String("intArray"), QLatin1String("stringArray"), QLatin1String("statusArray"), QLatin1String("blockArray"), QLatin1String("optionalInt"), QLatin1String("optionalString"), QLatin1String("optionalStatus"), QLatin1String("optionalBlock"), QLatin1String("intMap"), QLatin1String("stringMap"), QLatin1String("statusMap"), QLatin1String("blockMap")};
    }
    
    QString fieldType(const QString& fieldName) const override {
        if (fieldName == QLatin1String("intArray")) return QLatin1String("int32");
        if (fieldName == QLatin1String("stringArray")) return QLatin1String("string");
        if (fieldName == QLatin1String("statusArray")) return QLatin1String("BlockStatus");
        if (fieldName == QLatin1String("blockArray")) return QLatin1String("BaseBlock");
        if (fieldName == QLatin1String("optionalInt")) return QLatin1String("int32");
        if (fieldName == QLatin1String("optionalString")) return QLatin1String("string");
        if (fieldName == QLatin1String("optionalStatus")) return QLatin1String("BlockStatus");
        if (fieldName == QLatin1String("optionalBlock")) return QLatin1String("BaseBlock");
        if (fieldName == QLatin1String("intMap")) return QLatin1String("int32");
        if (fieldName == QLatin1String("stringMap")) return QLatin1String("string");
        if (fieldName == QLatin1String("statusMap")) return QLatin1String("BlockStatus");
        if (fieldName == QLatin1String("blockMap")) return QLatin1String("BaseBlock");
        return QString();
    }
    
    QString fieldContainerType(const QString& fieldName) const override {
        if (fieldName == QLatin1String("intArray")) return QLatin1String("array");
        if (fieldName == QLatin1String("stringArray")) return QLatin1String("array");
        if (fieldName == QLatin1String("statusArray")) return QLatin1String("array");
        if (fieldName == QLatin1String("blockArray")) return QLatin1String("array");
        if (fieldName == QLatin1String("optionalInt")) return QLatin1String("optional");
        if (fieldName == QLatin1String("optionalString")) return QLatin1String("optional");
        if (fieldName == QLatin1String("optionalStatus")) return QLatin1String("optional");
        if (fieldName == QLatin1String("optionalBlock")) return QLatin1String("optional");
        if (fieldName == QLatin1String("intMap")) return QLatin1String("map");
        if (fieldName == QLatin1String("stringMap")) return QLatin1String("map");
        if (fieldName == QLatin1String("statusMap")) return QLatin1String("map");
        if (fieldName == QLatin1String("blockMap")) return QLatin1String("map");
        return QLatin1String("none");
    }
    
    QList<QSharedPointer<IAnnotation>> annotations() const override {
        QList<QSharedPointer<IAnnotation>> result;
        return result;
    }
    
    QList<QSharedPointer<IAnnotation>> fieldAnnotation(const QString& fieldName) const override {
        if (fieldName == QLatin1String("intArray")) {
            QList<QSharedPointer<IAnnotation>> result;
            result.append(QSharedPointer<IAnnotation>(new BlockAnnotationAnnotation()));
            return result;
        }
        if (fieldName == QLatin1String("stringArray")) {
            QList<QSharedPointer<IAnnotation>> result;
            result.append(QSharedPointer<IAnnotation>(new BlockValueAnnotationAnnotation()));
            return result;
        }
        if (fieldName == QLatin1String("statusArray")) {
            QList<QSharedPointer<IAnnotation>> result;
            return result;
        }
        if (fieldName == QLatin1String("blockArray")) {
            QList<QSharedPointer<IAnnotation>> result;
            return result;
        }
        if (fieldName == QLatin1String("optionalInt")) {
            QList<QSharedPointer<IAnnotation>> result;
            result.append(QSharedPointer<IAnnotation>(new BlockValueAnnotationAnnotation()));
            return result;
        }
        if (fieldName == QLatin1String("optionalString")) {
            QList<QSharedPointer<IAnnotation>> result;
            return result;
        }
        if (fieldName == QLatin1String("optionalStatus")) {
            QList<QSharedPointer<IAnnotation>> result;
            result.append(QSharedPointer<IAnnotation>(new BlockAnnotationAnnotation()));
            return result;
        }
        if (fieldName == QLatin1String("optionalBlock")) {
            QList<QSharedPointer<IAnnotation>> result;
            return result;
        }
        if (fieldName == QLatin1String("intMap")) {
            QList<QSharedPointer<IAnnotation>> result;
            result.append(QSharedPointer<IAnnotation>(new BlockAnnotationAnnotation()));
            return result;
        }
        if (fieldName == QLatin1String("stringMap")) {
            QList<QSharedPointer<IAnnotation>> result;
            return result;
        }
        if (fieldName == QLatin1String("statusMap")) {
            QList<QSharedPointer<IAnnotation>> result;
            result.append(QSharedPointer<IAnnotation>(new BlockValueAnnotationAnnotation()));
            return result;
        }
        if (fieldName == QLatin1String("blockMap")) {
            QList<QSharedPointer<IAnnotation>> result;
            return result;
        }
        return QList<QSharedPointer<IAnnotation>>();
    }
    
    QString description() const override {
        return QLatin1String("ContainerBlock");
    }
    
    QString fieldDescription(const QString& fieldName) const override {
        if (fieldName == QLatin1String("intArray")) return QLatin1String("intArray");
        if (fieldName == QLatin1String("stringArray")) return QLatin1String("stringArray");
        if (fieldName == QLatin1String("statusArray")) return QLatin1String("statusArray");
        if (fieldName == QLatin1String("blockArray")) return QLatin1String("blockArray");
        if (fieldName == QLatin1String("optionalInt")) return QLatin1String("optionalInt");
        if (fieldName == QLatin1String("optionalString")) return QLatin1String("optionalString");
        if (fieldName == QLatin1String("optionalStatus")) return QLatin1String("optionalStatus");
        if (fieldName == QLatin1String("optionalBlock")) return QLatin1String("optionalBlock");
        if (fieldName == QLatin1String("intMap")) return QLatin1String("intMap");
        if (fieldName == QLatin1String("stringMap")) return QLatin1String("stringMap");
        if (fieldName == QLatin1String("statusMap")) return QLatin1String("statusMap");
        if (fieldName == QLatin1String("blockMap")) return QLatin1String("blockMap");
        return QString();
    }
    
    QVariant value(const QString& fieldName) const override {
        if (fieldName == QLatin1String("intArray")) return QVariant::fromValue(intArray_);
        if (fieldName == QLatin1String("stringArray")) return QVariant::fromValue(stringArray_);
        if (fieldName == QLatin1String("statusArray")) return QVariant::fromValue(statusArray_);
        if (fieldName == QLatin1String("blockArray")) return QVariant::fromValue(blockArray_);
        if (fieldName == QLatin1String("optionalInt")) return QVariant::fromValue(optionalInt_);
        if (fieldName == QLatin1String("optionalString")) return QVariant::fromValue(optionalString_);
        if (fieldName == QLatin1String("optionalStatus")) return QVariant::fromValue(optionalStatus_);
        if (fieldName == QLatin1String("optionalBlock")) return QVariant::fromValue(optionalBlock_);
        if (fieldName == QLatin1String("intMap")) return QVariant::fromValue(intMap_);
        if (fieldName == QLatin1String("stringMap")) return QVariant::fromValue(stringMap_);
        if (fieldName == QLatin1String("statusMap")) return QVariant::fromValue(statusMap_);
        if (fieldName == QLatin1String("blockMap")) return QVariant::fromValue(blockMap_);
        return QVariant();
    }
    
    void value(const QString& fieldName, const QVariant& value) override {
        if (fieldName == QLatin1String("intArray")) {
            intArray_ = value.value<QVector<int32_t>>();
            return;
        }
        if (fieldName == QLatin1String("stringArray")) {
            stringArray_ = value.value<QVector<QString>>();
            return;
        }
        if (fieldName == QLatin1String("statusArray")) {
            statusArray_ = value.value<QVector<BlockStatus>>();
            return;
        }
        if (fieldName == QLatin1String("blockArray")) {
            blockArray_ = value.value<QVector<BaseBlockBlock>>();
            return;
        }
        if (fieldName == QLatin1String("optionalInt")) {
            optionalInt_ = value.value<std::optional<int32_t>>();
            return;
        }
        if (fieldName == QLatin1String("optionalString")) {
            optionalString_ = value.value<std::optional<QString>>();
            return;
        }
        if (fieldName == QLatin1String("optionalStatus")) {
            optionalStatus_ = value.value<std::optional<BlockStatus>>();
            return;
        }
        if (fieldName == QLatin1String("optionalBlock")) {
            optionalBlock_ = value.value<std::optional<BaseBlockBlock>>();
            return;
        }
        if (fieldName == QLatin1String("intMap")) {
            intMap_ = value.value<QMap<QString, int32_t>>();
            return;
        }
        if (fieldName == QLatin1String("stringMap")) {
            stringMap_ = value.value<QMap<QString, QString>>();
            return;
        }
        if (fieldName == QLatin1String("statusMap")) {
            statusMap_ = value.value<QMap<QString, BlockStatus>>();
            return;
        }
        if (fieldName == QLatin1String("blockMap")) {
            blockMap_ = value.value<QMap<QString, BaseBlockBlock>>();
            return;
        }
    }
    
    // 字段访问器
    QVector<int32_t> getIntArray() const { return intArray_; }
    void setIntArray(const QVector<int32_t>& value) { intArray_ = value; }
    QVector<QString> getStringArray() const { return stringArray_; }
    void setStringArray(const QVector<QString>& value) { stringArray_ = value; }
    QVector<BlockStatus> getStatusArray() const { return statusArray_; }
    void setStatusArray(const QVector<BlockStatus>& value) { statusArray_ = value; }
    QVector<BaseBlockBlock> getBlockArray() const { return blockArray_; }
    void setBlockArray(const QVector<BaseBlockBlock>& value) { blockArray_ = value; }
    std::optional<int32_t> getOptionalInt() const { return optionalInt_; }
    void setOptionalInt(const std::optional<int32_t>& value) { optionalInt_ = value; }
    std::optional<QString> getOptionalString() const { return optionalString_; }
    void setOptionalString(const std::optional<QString>& value) { optionalString_ = value; }
    std::optional<BlockStatus> getOptionalStatus() const { return optionalStatus_; }
    void setOptionalStatus(const std::optional<BlockStatus>& value) { optionalStatus_ = value; }
    std::optional<BaseBlockBlock> getOptionalBlock() const { return optionalBlock_; }
    void setOptionalBlock(const std::optional<BaseBlockBlock>& value) { optionalBlock_ = value; }
    QMap<QString, int32_t> getIntMap() const { return intMap_; }
    void setIntMap(const QMap<QString, int32_t>& value) { intMap_ = value; }
    QMap<QString, QString> getStringMap() const { return stringMap_; }
    void setStringMap(const QMap<QString, QString>& value) { stringMap_ = value; }
    QMap<QString, BlockStatus> getStatusMap() const { return statusMap_; }
    void setStatusMap(const QMap<QString, BlockStatus>& value) { statusMap_ = value; }
    QMap<QString, BaseBlockBlock> getBlockMap() const { return blockMap_; }
    void setBlockMap(const QMap<QString, BaseBlockBlock>& value) { blockMap_ = value; }
private:
    QVector<int32_t> intArray_ = [
    "1",
    "2",
    "3"
];
    QVector<QString> stringArray_;
    QVector<BlockStatus> statusArray_ = [
    "/* complex expression */",
    "/* complex expression */"
];
    QVector<BaseBlockBlock> blockArray_;
    std::optional<int32_t> optionalInt_ = 42;
    std::optional<QString> optionalString_;
    std::optional<BlockStatus> optionalStatus_;
    std::optional<BaseBlockBlock> optionalBlock_;
    QMap<QString, int32_t> intMap_;
    QMap<QString, QString> stringMap_;
    QMap<QString, BlockStatus> statusMap_;
    QMap<QString, BaseBlockBlock> blockMap_;
};
Q_DECLARE_METATYPE(ContainerBlockBlock)


} // namespace examples
} // namespace blocks
