#pragma once

// 此文件由 Mota 代码生成器自动生成
// Mota 版本: 0.2.0
// 生成时间: 2025-06-15 21:43:44
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

#include "framework/IBlock.h"
#include "framework/IModel.h"
#include "framework/IAnnotation.h"
#include "yima.h"

using namespace ymf;

namespace examples {
namespace blocks {

class MODEL_EXPORT BlockAnnotationAnnotation : public IAnnotation {
public:
    BlockAnnotationAnnotation() = default;
    
    // 实现IAnnotation接口
    QString name() const override {
        return QLatin1String("BlockAnnotation");
    }
    
    virtual QVariant argumentValue(const QString& argumentName) const override {
        if (argumentName == QLatin1String("description")) {
            return QVariant::fromValue(description_);
        }
        return QVariant();
    }
    
    virtual QStringList fieldNames() const override {
        QStringList names = QStringList{QLatin1String("description")};
        return names;
    }

    virtual QStringList uiComments() const override {
        return QStringList{};
    }
    
    virtual QStringList fieldUiComments(const QString& fieldName) const override {
        if (fieldName == QLatin1String("description")) {
            return QStringList{};
        }
        return QStringList();
    }

    QString getDescription() const {
        return description_;
    }
    void setDescription(const QString& value) {
        description_ = value;
    }
private:
    QString description_ = "";
};
Q_DECLARE_METATYPE(BlockAnnotationAnnotation)

class MODEL_EXPORT BlockValueAnnotationAnnotation : public IAnnotation {
public:
    BlockValueAnnotationAnnotation() = default;
    
    // 实现IAnnotation接口
    QString name() const override {
        return QLatin1String("BlockValueAnnotation");
    }
    
    virtual QVariant argumentValue(const QString& argumentName) const override {
        if (argumentName == QLatin1String("value")) {
            return QVariant::fromValue(value_);
        }
        return QVariant();
    }
    
    virtual QStringList fieldNames() const override {
        QStringList names = QStringList{QLatin1String("value")};
        return names;
    }

    virtual QStringList uiComments() const override {
        return QStringList{};
    }
    
    virtual QStringList fieldUiComments(const QString& fieldName) const override {
        if (fieldName == QLatin1String("value")) {
            return QStringList{};
        }
        return QStringList();
    }

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

enum class BlockStatus {
        ACTIVE,
        INACTIVE,
        PENDING
};
Q_DECLARE_METATYPE(BlockStatus)

class BlockStatusEnumUtil {
    public:
        static QStringList uiComments() {
            return QStringList();
        }

        static QStringList fieldNames() {
            return QStringList{QLatin1String("ACTIVE"), QLatin1String("INACTIVE"), QLatin1String("PENDING")};
        }

        static BlockStatus fromString(const QString& str) {
            if (str == QLatin1String("ACTIVE")) return BlockStatus::ACTIVE;
            if (str == QLatin1String("INACTIVE")) return BlockStatus::INACTIVE;
            if (str == QLatin1String("PENDING")) return BlockStatus::PENDING;
            return BlockStatus::ACTIVE;

        }

        static QString toString(BlockStatus value) {
            if (value == BlockStatus::ACTIVE) return QLatin1String("ACTIVE");
            if (value == BlockStatus::INACTIVE) return QLatin1String("INACTIVE");
            if (value == BlockStatus::PENDING) return QLatin1String("PENDING");
            return QLatin1String("ACTIVE");

        }

        static QStringList fieldUiComments(const QString& fieldName) {
            return QStringList();
        }

        static QVector<QSharedPointer<IAnnotation>> annotations() {
            return QVector<QSharedPointer<IAnnotation>>();
        }

        static QVector<QSharedPointer<IAnnotation>> fieldAnnotations(const BlockStatus& fieldName) {
            return {};
        }
};

enum class BlockType {
        PRIMARY,
        SECONDARY,
        AUXILIARY
};
Q_DECLARE_METATYPE(BlockType)

class BlockTypeEnumUtil {
    public:
        static QStringList uiComments() {
            return QStringList();
        }

        static QStringList fieldNames() {
            return QStringList{QLatin1String("PRIMARY"), QLatin1String("SECONDARY"), QLatin1String("AUXILIARY")};
        }

        static BlockType fromString(const QString& str) {
            if (str == QLatin1String("PRIMARY")) return BlockType::PRIMARY;
            if (str == QLatin1String("SECONDARY")) return BlockType::SECONDARY;
            if (str == QLatin1String("AUXILIARY")) return BlockType::AUXILIARY;
            return BlockType::PRIMARY;

        }

        static QString toString(BlockType value) {
            if (value == BlockType::PRIMARY) return QLatin1String("PRIMARY");
            if (value == BlockType::SECONDARY) return QLatin1String("SECONDARY");
            if (value == BlockType::AUXILIARY) return QLatin1String("AUXILIARY");
            return QLatin1String("PRIMARY");

        }

        static QStringList fieldUiComments(const QString& fieldName) {
            return QStringList();
        }

        static QVector<QSharedPointer<IAnnotation>> annotations() {
            return QVector<QSharedPointer<IAnnotation>>();
        }

        static QVector<QSharedPointer<IAnnotation>> fieldAnnotations(const BlockType& fieldName) {
            return {};
        }
};

// BaseBlock块定义
class MODEL_EXPORT BaseBlockBlock :  public IBlock {
public:
    BaseBlockBlock() = default;
    
    // 实现 IBlock 接口
    QCborMap toCbor() const override {

    }
    
    void fromCbor(const QCborMap& map) override {
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
            return QVector<QSharedPointer<IAnnotation>>();
    }
    
    QList<QSharedPointer<IAnnotation>> fieldAnnotation(const QString& fieldName) const override {
        return {};
    }
    
    QString description() const override {
        return QLatin1String("");
    }
    
    QString fieldDescription(const QString& fieldName) const override {
        if (fieldName == QLatin1String("id")) return QLatin1String("");
        if (fieldName == QLatin1String("name")) return QLatin1String("");
        return QString();
    }
    
    QVariant value(const QString& fieldName) const override {
        if (fieldName == QLatin1String("id")) {
            return QVariant::fromValue(id_);
        }
        if (fieldName == QLatin1String("name")) {
            return QVariant::fromValue(name_);
        }
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
    int32_t getId() const {
        return id_;
    }
    void setId(const int32_t& value) {
        id_ = value;
    }
    QString getName() const {
        return name_;
    }
    void setName(const QString& value) {
        name_ = value;
    }
private:
    int32_t id_ = 0;
    QString name_ = "";
};
Q_DECLARE_METATYPE(BaseBlockBlock)

// ExtendedBlock块定义
class MODEL_EXPORT ExtendedBlockBlock : public BaseBlockBlock {
public:
    ExtendedBlockBlock() = default;
    
    // 实现 IBlock 接口
    QCborMap toCbor() const override {

    }
    
    void fromCbor(const QCborMap& map) override {
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
        return BaseBlockBlock::fieldContainerType(fieldName);
    }
    
    QList<QSharedPointer<IAnnotation>> annotations() const override {
            return QVector<QSharedPointer<IAnnotation>>();
    }
    
    QList<QSharedPointer<IAnnotation>> fieldAnnotation(const QString& fieldName) const override {
        return BaseBlockBlock::fieldAnnotation(fieldName);
    }
    
    QString description() const override {
        return QLatin1String("");
    }
    
    QString fieldDescription(const QString& fieldName) const override {
        if (fieldName == QLatin1String("active")) return QLatin1String("");
        if (fieldName == QLatin1String("status")) return QLatin1String("");
        if (fieldName == QLatin1String("type")) return QLatin1String("");
        return BaseBlockBlock::fieldDescription(fieldName);
    }
    
    QVariant value(const QString& fieldName) const override {
        if (fieldName == QLatin1String("active")) {
            return QVariant::fromValue(active_);
        }
        if (fieldName == QLatin1String("status")) {
            return QVariant::fromValue(status_);
        }
        if (fieldName == QLatin1String("type")) {
            return QVariant::fromValue(type_);
        }
        return BaseBlockBlock::value(fieldName);
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
        BaseBlockBlock::value(fieldName, value);
    }
    
    // 字段访问器
    bool getActive() const {
        return active_;
    }
    void setActive(const bool& value) {
        active_ = value;
    }
    BlockStatus getStatus() const {
        return status_;
    }
    void setStatus(const BlockStatus& value) {
        status_ = value;
    }
    BlockType getType() const {
        return type_;
    }
    void setType(const BlockType& value) {
        type_ = value;
    }
private:
    bool active_ = true;
    BlockStatus status_ = BlockStatus::ACTIVE;
    BlockType type_ = BlockType::PRIMARY;
};
Q_DECLARE_METATYPE(ExtendedBlockBlock)

// AnnotatedBlock块定义
class MODEL_EXPORT AnnotatedBlockBlock :  public IBlock {
public:
    AnnotatedBlockBlock() = default;
    
    // 实现 IBlock 接口
    QCborMap toCbor() const override {

    }
    
    void fromCbor(const QCborMap& map) override {
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
            return QVector<QSharedPointer<IAnnotation>>{
    [&]() {
        // annotation, set all arguments
        auto __instance = QSharedPointer<BlockValueAnnotationAnnotation>::create();
        __instance->setValue("test_block");
        return __instance;
    }(),
    [&]() {
        // annotation, set all arguments
        auto __instance = QSharedPointer<BlockAnnotationAnnotation>::create();
        __instance->setDescription("带注解的块");
        return __instance;
    }(),
            };
    }
    
    QList<QSharedPointer<IAnnotation>> fieldAnnotation(const QString& fieldName) const override {
        if (fieldName == "data")
            return QVector<QSharedPointer<IAnnotation>>{
                [&]() {
        // annotation, set all arguments
        auto __instance = QSharedPointer<BlockValueAnnotationAnnotation>::create();
        __instance->setValue("data_field");
        return __instance;
    }()
            };
        if (fieldName == "config")
            return QVector<QSharedPointer<IAnnotation>>{
                [&]() {
        // annotation, set all arguments
        auto __instance = QSharedPointer<BlockAnnotationAnnotation>::create();
        __instance->setDescription("配置字段");
        return __instance;
    }()
            };
        return {};
    }
    
    QString description() const override {
        return QLatin1String("");
    }
    
    QString fieldDescription(const QString& fieldName) const override {
        if (fieldName == QLatin1String("data")) return QLatin1String("");
        if (fieldName == QLatin1String("config")) return QLatin1String("");
        return QString();
    }
    
    QVariant value(const QString& fieldName) const override {
        if (fieldName == QLatin1String("data")) {
            return QVariant::fromValue(data_);
        }
        if (fieldName == QLatin1String("config")) {
            return QVariant::fromValue(config_);
        }
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
    QString getData() const {
        return data_;
    }
    void setData(const QString& value) {
        data_ = value;
    }
    QString getConfig() const {
        return config_;
    }
    void setConfig(const QString& value) {
        config_ = value;
    }
private:
    QString data_ = "";
    QString config_ = "";
};
Q_DECLARE_METATYPE(AnnotatedBlockBlock)

// AllTypesBlock块定义
class MODEL_EXPORT AllTypesBlockBlock :  public IBlock {
public:
    AllTypesBlockBlock() = default;
    
    // 实现 IBlock 接口
    QCborMap toCbor() const override {

    }
    
    void fromCbor(const QCborMap& map) override {
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
            return QVector<QSharedPointer<IAnnotation>>();
    }
    
    QList<QSharedPointer<IAnnotation>> fieldAnnotation(const QString& fieldName) const override {
        return {};
    }
    
    QString description() const override {
        return QLatin1String("");
    }
    
    QString fieldDescription(const QString& fieldName) const override {
        if (fieldName == QLatin1String("int8Field")) return QLatin1String("");
        if (fieldName == QLatin1String("int16Field")) return QLatin1String("");
        if (fieldName == QLatin1String("int32Field")) return QLatin1String("");
        if (fieldName == QLatin1String("int64Field")) return QLatin1String("");
        if (fieldName == QLatin1String("uint8Field")) return QLatin1String("");
        if (fieldName == QLatin1String("uint16Field")) return QLatin1String("");
        if (fieldName == QLatin1String("uint32Field")) return QLatin1String("");
        if (fieldName == QLatin1String("uint64Field")) return QLatin1String("");
        if (fieldName == QLatin1String("float32Field")) return QLatin1String("");
        if (fieldName == QLatin1String("float64Field")) return QLatin1String("");
        if (fieldName == QLatin1String("boolField")) return QLatin1String("");
        if (fieldName == QLatin1String("stringField")) return QLatin1String("");
        if (fieldName == QLatin1String("bytesField")) return QLatin1String("");
        if (fieldName == QLatin1String("status")) return QLatin1String("");
        if (fieldName == QLatin1String("type")) return QLatin1String("");
        if (fieldName == QLatin1String("baseBlock")) return QLatin1String("");
        if (fieldName == QLatin1String("extendedBlock")) return QLatin1String("");
        return QString();
    }
    
    QVariant value(const QString& fieldName) const override {
        if (fieldName == QLatin1String("int8Field")) {
            return QVariant::fromValue(int8Field_);
        }
        if (fieldName == QLatin1String("int16Field")) {
            return QVariant::fromValue(int16Field_);
        }
        if (fieldName == QLatin1String("int32Field")) {
            return QVariant::fromValue(int32Field_);
        }
        if (fieldName == QLatin1String("int64Field")) {
            return QVariant::fromValue(int64Field_);
        }
        if (fieldName == QLatin1String("uint8Field")) {
            return QVariant::fromValue(uint8Field_);
        }
        if (fieldName == QLatin1String("uint16Field")) {
            return QVariant::fromValue(uint16Field_);
        }
        if (fieldName == QLatin1String("uint32Field")) {
            return QVariant::fromValue(uint32Field_);
        }
        if (fieldName == QLatin1String("uint64Field")) {
            return QVariant::fromValue(uint64Field_);
        }
        if (fieldName == QLatin1String("float32Field")) {
            return QVariant::fromValue(float32Field_);
        }
        if (fieldName == QLatin1String("float64Field")) {
            return QVariant::fromValue(float64Field_);
        }
        if (fieldName == QLatin1String("boolField")) {
            return QVariant::fromValue(boolField_);
        }
        if (fieldName == QLatin1String("stringField")) {
            return QVariant::fromValue(stringField_);
        }
        if (fieldName == QLatin1String("bytesField")) {
            return QVariant::fromValue(bytesField_);
        }
        if (fieldName == QLatin1String("status")) {
            return QVariant::fromValue(status_);
        }
        if (fieldName == QLatin1String("type")) {
            return QVariant::fromValue(type_);
        }
        if (fieldName == QLatin1String("baseBlock")) {
            return QVariant::fromValue(baseBlock_);
        }
        if (fieldName == QLatin1String("extendedBlock")) {
            return QVariant::fromValue(extendedBlock_);
        }
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
    int8_t getInt8Field() const {
        return int8Field_;
    }
    void setInt8Field(const int8_t& value) {
        int8Field_ = value;
    }
    int16_t getInt16Field() const {
        return int16Field_;
    }
    void setInt16Field(const int16_t& value) {
        int16Field_ = value;
    }
    int32_t getInt32Field() const {
        return int32Field_;
    }
    void setInt32Field(const int32_t& value) {
        int32Field_ = value;
    }
    int64_t getInt64Field() const {
        return int64Field_;
    }
    void setInt64Field(const int64_t& value) {
        int64Field_ = value;
    }
    uint8_t getUint8Field() const {
        return uint8Field_;
    }
    void setUint8Field(const uint8_t& value) {
        uint8Field_ = value;
    }
    uint16_t getUint16Field() const {
        return uint16Field_;
    }
    void setUint16Field(const uint16_t& value) {
        uint16Field_ = value;
    }
    uint32_t getUint32Field() const {
        return uint32Field_;
    }
    void setUint32Field(const uint32_t& value) {
        uint32Field_ = value;
    }
    uint64_t getUint64Field() const {
        return uint64Field_;
    }
    void setUint64Field(const uint64_t& value) {
        uint64Field_ = value;
    }
    float getFloat32Field() const {
        return float32Field_;
    }
    void setFloat32Field(const float& value) {
        float32Field_ = value;
    }
    double getFloat64Field() const {
        return float64Field_;
    }
    void setFloat64Field(const double& value) {
        float64Field_ = value;
    }
    bool getBoolField() const {
        return boolField_;
    }
    void setBoolField(const bool& value) {
        boolField_ = value;
    }
    QString getStringField() const {
        return stringField_;
    }
    void setStringField(const QString& value) {
        stringField_ = value;
    }
    QByteArray getBytesField() const {
        return bytesField_;
    }
    void setBytesField(const QByteArray& value) {
        bytesField_ = value;
    }
    BlockStatus getStatus() const {
        return status_;
    }
    void setStatus(const BlockStatus& value) {
        status_ = value;
    }
    BlockType getType() const {
        return type_;
    }
    void setType(const BlockType& value) {
        type_ = value;
    }
    QSharedPointer<BaseBlockBlock> getBaseBlock() const {
        return baseBlock_;
    }
    void setBaseBlock(const QSharedPointer<BaseBlockBlock>& value) {
        baseBlock_ = value;
    }
    QSharedPointer<ExtendedBlockBlock> getExtendedBlock() const {
        return extendedBlock_;
    }
    void setExtendedBlock(const QSharedPointer<ExtendedBlockBlock>& value) {
        extendedBlock_ = value;
    }
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
    BlockStatus status_ = BlockStatus::PENDING;
    BlockType type_ = BlockType::SECONDARY;
    QSharedPointer<BaseBlockBlock> baseBlock_;
    QSharedPointer<ExtendedBlockBlock> extendedBlock_;
};
Q_DECLARE_METATYPE(AllTypesBlockBlock)

// ContainerBlock块定义
class MODEL_EXPORT ContainerBlockBlock :  public IBlock {
public:
    ContainerBlockBlock() = default;
    
    // 实现 IBlock 接口
    QCborMap toCbor() const override {

    }
    
    void fromCbor(const QCborMap& map) override {
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
            return QVector<QSharedPointer<IAnnotation>>();
    }
    
    QList<QSharedPointer<IAnnotation>> fieldAnnotation(const QString& fieldName) const override {
        if (fieldName == "intArray")
            return QVector<QSharedPointer<IAnnotation>>{
                [&]() {
        // annotation, set all arguments
        auto __instance = QSharedPointer<BlockAnnotationAnnotation>::create();
        __instance->setDescription("整数数组");
        return __instance;
    }()
            };
        if (fieldName == "stringArray")
            return QVector<QSharedPointer<IAnnotation>>{
                [&]() {
        // annotation, set all arguments
        auto __instance = QSharedPointer<BlockValueAnnotationAnnotation>::create();
        __instance->setValue("string_array");
        return __instance;
    }()
            };
        if (fieldName == "optionalInt")
            return QVector<QSharedPointer<IAnnotation>>{
                [&]() {
        // annotation, set all arguments
        auto __instance = QSharedPointer<BlockValueAnnotationAnnotation>::create();
        __instance->setValue("optional_int");
        return __instance;
    }()
            };
        if (fieldName == "optionalStatus")
            return QVector<QSharedPointer<IAnnotation>>{
                [&]() {
        // annotation, set all arguments
        auto __instance = QSharedPointer<BlockAnnotationAnnotation>::create();
        __instance->setDescription("可选状态");
        return __instance;
    }()
            };
        if (fieldName == "intMap")
            return QVector<QSharedPointer<IAnnotation>>{
                [&]() {
        // annotation, set all arguments
        auto __instance = QSharedPointer<BlockAnnotationAnnotation>::create();
        __instance->setDescription("整数映射");
        return __instance;
    }()
            };
        if (fieldName == "statusMap")
            return QVector<QSharedPointer<IAnnotation>>{
                [&]() {
        // annotation, set all arguments
        auto __instance = QSharedPointer<BlockValueAnnotationAnnotation>::create();
        __instance->setValue("status_map");
        return __instance;
    }()
            };
        return {};
    }
    
    QString description() const override {
        return QLatin1String("");
    }
    
    QString fieldDescription(const QString& fieldName) const override {
        if (fieldName == QLatin1String("intArray")) return QLatin1String("");
        if (fieldName == QLatin1String("stringArray")) return QLatin1String("");
        if (fieldName == QLatin1String("statusArray")) return QLatin1String("");
        if (fieldName == QLatin1String("blockArray")) return QLatin1String("");
        if (fieldName == QLatin1String("optionalInt")) return QLatin1String("");
        if (fieldName == QLatin1String("optionalString")) return QLatin1String("");
        if (fieldName == QLatin1String("optionalStatus")) return QLatin1String("");
        if (fieldName == QLatin1String("optionalBlock")) return QLatin1String("");
        if (fieldName == QLatin1String("intMap")) return QLatin1String("");
        if (fieldName == QLatin1String("stringMap")) return QLatin1String("");
        if (fieldName == QLatin1String("statusMap")) return QLatin1String("");
        if (fieldName == QLatin1String("blockMap")) return QLatin1String("");
        return QString();
    }
    
    QVariant value(const QString& fieldName) const override {
        if (fieldName == QLatin1String("intArray")) {
            return QVariant::fromValue(intArray_);
        }
        if (fieldName == QLatin1String("stringArray")) {
            return QVariant::fromValue(stringArray_);
        }
        if (fieldName == QLatin1String("statusArray")) {
            return QVariant::fromValue(statusArray_);
        }
        if (fieldName == QLatin1String("blockArray")) {
            return QVariant::fromValue(blockArray_);
        }
        if (fieldName == QLatin1String("optionalInt")) {
            return QVariant::fromValue(optionalInt_);
        }
        if (fieldName == QLatin1String("optionalString")) {
            return QVariant::fromValue(optionalString_);
        }
        if (fieldName == QLatin1String("optionalStatus")) {
            return QVariant::fromValue(optionalStatus_);
        }
        if (fieldName == QLatin1String("optionalBlock")) {
            return QVariant::fromValue(optionalBlock_);
        }
        if (fieldName == QLatin1String("intMap")) {
            return QVariant::fromValue(intMap_);
        }
        if (fieldName == QLatin1String("stringMap")) {
            return QVariant::fromValue(stringMap_);
        }
        if (fieldName == QLatin1String("statusMap")) {
            return QVariant::fromValue(statusMap_);
        }
        if (fieldName == QLatin1String("blockMap")) {
            return QVariant::fromValue(blockMap_);
        }
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
            optionalInt_ = value.value<int32_t>();
            return;
        }
        if (fieldName == QLatin1String("optionalString")) {
            optionalString_ = value.value<QString>();
            return;
        }
        if (fieldName == QLatin1String("optionalStatus")) {
            optionalStatus_ = value.value<BlockStatus>();
            return;
        }
        if (fieldName == QLatin1String("optionalBlock")) {
            optionalBlock_ = value.value<BaseBlockBlock>();
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
    QVector<int32_t> getIntArray() const {
        return intArray_; 
    }
    void setIntArray(const QVector<int32_t>& value) {
        intArray_ = value;
    }
    QVector<QString> getStringArray() const {
        return stringArray_; 
    }
    void setStringArray(const QVector<QString>& value) {
        stringArray_ = value;
    }
    QVector<BlockStatus> getStatusArray() const {
        return statusArray_; 
    }
    void setStatusArray(const QVector<BlockStatus>& value) {
        statusArray_ = value;
    }
    QVector<QSharedPointer<BaseBlockBlock>> getBlockArray() const {
        return blockArray_;
    }
    void setBlockArray(const QVector<QSharedPointer<BaseBlockBlock>>& value) {
        blockArray_ = value;
    }
    int32_t getOptionalInt() const {
        return optionalInt_;
    }
    void setOptionalInt(const int32_t& value) {
        optionalInt_ = value;
    }
    QString getOptionalString() const {
        return optionalString_;
    }
    void setOptionalString(const QString& value) {
        optionalString_ = value;
    }
    BlockStatus getOptionalStatus() const {
        return optionalStatus_;
    }
    void setOptionalStatus(const BlockStatus& value) {
        optionalStatus_ = value;
    }
    QSharedPointer<BaseBlockBlock> getOptionalBlock() const {
        return optionalBlock_;
    }
    void setOptionalBlock(const QSharedPointer<BaseBlockBlock>& value) {
        optionalBlock_ = value;
    }
    QMap<QString, int32_t> getIntMap() const {
        return intMap_;
    }
    void setIntMap(const QMap<QString, int32_t>& value) {
        intMap_ = value;
    }
    QMap<QString, QString> getStringMap() const {
        return stringMap_;
    }
    void setStringMap(const QMap<QString, QString>& value) {
        stringMap_ = value;
    }
    QMap<QString, BlockStatus> getStatusMap() const {
        return statusMap_;
    }
    void setStatusMap(const QMap<QString, BlockStatus>& value) {
        statusMap_ = value;
    }
    QMap<QString, QSharedPointer<BaseBlockBlock>> getBlockMap() const {
        return blockMap_;
    }
    void setBlockMap(const QMap<QString, QSharedPointer<BaseBlockBlock>>& value) {
        blockMap_ = value;
    }
private:
    QVector<int32_t> intArray_ = { 1, 2, 3 };
    QVector<QString> stringArray_;
    QVector<BlockStatus> statusArray_ = { BlockStatus::ACTIVE, BlockStatus::PENDING };
    QVector<QSharedPointer<BaseBlockBlock>> blockArray_;
    int32_t optionalInt_ = 42;
    QString optionalString_;
    BlockStatus optionalStatus_;
    QSharedPointer<BaseBlockBlock> optionalBlock_;
    QMap<QString, int32_t> intMap_;
    QMap<QString, QString> stringMap_;
    QMap<QString, BlockStatus> statusMap_;
    QMap<QString, QSharedPointer<BaseBlockBlock>> blockMap_;
};
Q_DECLARE_METATYPE(ContainerBlockBlock)


} // namespace examples
} // namespace blocks
