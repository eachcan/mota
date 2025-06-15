#pragma once

// 此文件由 Mota 代码生成器自动生成
// Mota 版本: 0.2.0
// 生成时间: 2025-06-15 21:07:05
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

class MODEL_EXPORT StructAnnotationAnnotation : public IAnnotation {
public:
    StructAnnotationAnnotation() = default;
    
    // 实现IAnnotation接口
    QString name() const override {
        return QLatin1String("StructAnnotation");
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
Q_DECLARE_METATYPE(StructAnnotationAnnotation)

class MODEL_EXPORT StructValueAnnotationAnnotation : public IAnnotation {
public:
    StructValueAnnotationAnnotation() = default;
    
    // 实现IAnnotation接口
    QString name() const override {
        return QLatin1String("StructValueAnnotation");
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
Q_DECLARE_METATYPE(StructValueAnnotationAnnotation)

class MODEL_EXPORT StructConfigAnnotationAnnotation : public StructAnnotationAnnotation {
public:
    StructConfigAnnotationAnnotation() = default;
    
    // 实现IAnnotation接口
    QString name() const override {
        return QLatin1String("StructConfigAnnotation");
    }
    
    virtual QVariant argumentValue(const QString& argumentName) const override {
        if (argumentName == QLatin1String("required")) {
            return QVariant::fromValue(required_);
        }
        if (argumentName == QLatin1String("priority")) {
            return QVariant::fromValue(priority_);
        }
        return StructAnnotationAnnotation::argumentValue(argumentName);
    }
    
    virtual QStringList fieldNames() const override {
        QStringList names = QStringList{QLatin1String("required"), QLatin1String("priority")};
        names.append(StructAnnotationAnnotation::fieldNames());
        return names;
    }

    virtual QStringList uiComments() const override {
        return QStringList{};
    }
    
    virtual QStringList fieldUiComments(const QString& fieldName) const override {
        if (fieldName == QLatin1String("required")) {
            return QStringList{};
        }
        if (fieldName == QLatin1String("priority")) {
            return QStringList{};
        }
        return StructAnnotationAnnotation::fieldUiComments(fieldName);
    }

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
    bool required_ = false;
    int32_t priority_ = 1;
};
Q_DECLARE_METATYPE(StructConfigAnnotationAnnotation)

enum class StructStatus {
        DRAFT,
        PUBLISHED,
        ARCHIVED
};
Q_DECLARE_METATYPE(StructStatus)

class StructStatusEnumUtil {
    public:
        static QStringList uiComments() {
            return QStringList();
        }

        static QStringList fieldNames() {
            return QStringList{QLatin1String("DRAFT"), QLatin1String("PUBLISHED"), QLatin1String("ARCHIVED")};
        }

        static StructStatus fromString(const QString& str) {
            if (str == QLatin1String("DRAFT")) return StructStatus::DRAFT;
            if (str == QLatin1String("PUBLISHED")) return StructStatus::PUBLISHED;
            if (str == QLatin1String("ARCHIVED")) return StructStatus::ARCHIVED;
            return StructStatus::DRAFT;

        }

        static QString toString(StructStatus value) {
            if (value == StructStatus::DRAFT) return QLatin1String("DRAFT");
            if (value == StructStatus::PUBLISHED) return QLatin1String("PUBLISHED");
            if (value == StructStatus::ARCHIVED) return QLatin1String("ARCHIVED");
            return QLatin1String("DRAFT");

        }

        static QStringList fieldUiComments(const QString& fieldName) {
            return QStringList();
        }

        static QVector<QSharedPointer<IAnnotation>> annotations() {
            return QVector<QSharedPointer<IAnnotation>>();
        }

        static QVector<QSharedPointer<IAnnotation>> fieldAnnotations(const StructStatus& fieldName) {
            return {};
        }
};

enum class StructCategory {
        BASIC,
        ADVANCED,
        PREMIUM
};
Q_DECLARE_METATYPE(StructCategory)

class StructCategoryEnumUtil {
    public:
        static QStringList uiComments() {
            return QStringList();
        }

        static QStringList fieldNames() {
            return QStringList{QLatin1String("BASIC"), QLatin1String("ADVANCED"), QLatin1String("PREMIUM")};
        }

        static StructCategory fromString(const QString& str) {
            if (str == QLatin1String("BASIC")) return StructCategory::BASIC;
            if (str == QLatin1String("ADVANCED")) return StructCategory::ADVANCED;
            if (str == QLatin1String("PREMIUM")) return StructCategory::PREMIUM;
            return StructCategory::BASIC;

        }

        static QString toString(StructCategory value) {
            if (value == StructCategory::BASIC) return QLatin1String("BASIC");
            if (value == StructCategory::ADVANCED) return QLatin1String("ADVANCED");
            if (value == StructCategory::PREMIUM) return QLatin1String("PREMIUM");
            return QLatin1String("BASIC");

        }

        static QStringList fieldUiComments(const QString& fieldName) {
            return QStringList();
        }

        static QVector<QSharedPointer<IAnnotation>> annotations() {
            return QVector<QSharedPointer<IAnnotation>>();
        }

        static QVector<QSharedPointer<IAnnotation>> fieldAnnotations(const StructCategory& fieldName) {
            return {};
        }
};

// StructBaseBlock块定义
class MODEL_EXPORT StructBaseBlockBlock :  public IBlock {
public:
    StructBaseBlockBlock() = default;
    
    // 实现 IBlock 接口
    QCborMap toCbor() const override {

    }
    
    void fromCbor(const QCborMap& map) override {
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
            return QVector<QSharedPointer<IAnnotation>>();
    }
    
    QList<QSharedPointer<IAnnotation>> fieldAnnotation(const QString& fieldName) const override {
        return {};
    }
    
    QString description() const override {
        return QLatin1String("StructBaseBlock");
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
Q_DECLARE_METATYPE(StructBaseBlockBlock)

// StructExtendedBlock块定义
class MODEL_EXPORT StructExtendedBlockBlock : public StructBaseBlockBlock {
public:
    StructExtendedBlockBlock() = default;
    
    // 实现 IBlock 接口
    QCborMap toCbor() const override {

    }
    
    void fromCbor(const QCborMap& map) override {
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
        return StructBaseBlockBlock::fieldContainerType(fieldName);
    }
    
    QList<QSharedPointer<IAnnotation>> annotations() const override {
            return QVector<QSharedPointer<IAnnotation>>();
    }
    
    QList<QSharedPointer<IAnnotation>> fieldAnnotation(const QString& fieldName) const override {
        return {};
    }
    
    QString description() const override {
        return QLatin1String("StructExtendedBlock");
    }
    
    QString fieldDescription(const QString& fieldName) const override {
        if (fieldName == QLatin1String("enabled")) return QLatin1String("");
        if (fieldName == QLatin1String("status")) return QLatin1String("");
        return StructBaseBlockBlock::fieldDescription(fieldName);
    }
    
    QVariant value(const QString& fieldName) const override {
        if (fieldName == QLatin1String("enabled")) {
            return QVariant::fromValue(enabled_);
        }
        if (fieldName == QLatin1String("status")) {
            return QVariant::fromValue(status_);
        }
        return StructBaseBlockBlock::value(fieldName);
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
        StructBaseBlockBlock::value(fieldName, value);
    }
    
    // 字段访问器
    bool getEnabled() const {
        return enabled_;
    }
    void setEnabled(const bool& value) {
        enabled_ = value;
    }
    StructStatus getStatus() const {
        return status_;
    }
    void setStatus(const StructStatus& value) {
        status_ = value;
    }
private:
    bool enabled_ = true;
    StructStatus status_ = DRAFT;
};
Q_DECLARE_METATYPE(StructExtendedBlockBlock)

    // BasicStruct结构体
    class MODEL_EXPORT BasicStructModel : public IModel {
    public:
        BasicStructModel() = default;
        
        // 实现 IModel 接口
        QCborMap toCbor() const override {
            return map;
        }
        
        void fromCbor(const QCborMap& map) override {
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
        // InheritedStruct结构体
    class MODEL_EXPORT InheritedStructModel : public StructBaseBlockModel, public IModel {
    public:
        InheritedStructModel() = default;
        
        // 实现 IModel 接口
        QCborMap toCbor() const override {
            return map;
        }
        
        void fromCbor(const QCborMap& map) override {
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
        // AnnotatedStruct结构体
    class MODEL_EXPORT AnnotatedStructModel : public IModel {
    public:
        AnnotatedStructModel() = default;
        
        // 实现 IModel 接口
        QCborMap toCbor() const override {
            return map;
        }
        
        void fromCbor(const QCborMap& map) override {
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
        // AllTypesStruct结构体
    class MODEL_EXPORT AllTypesStructModel : public IModel {
    public:
        AllTypesStructModel() = default;
        
        // 实现 IModel 接口
        QCborMap toCbor() const override {
            return map;
        }
        
        void fromCbor(const QCborMap& map) override {
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
        // ContainerStruct结构体
    class MODEL_EXPORT ContainerStructModel : public IModel {
    public:
        ContainerStructModel() = default;
        
        // 实现 IModel 接口
        QCborMap toCbor() const override {
            return map;
        }
        
        void fromCbor(const QCborMap& map) override {
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
        // ComprehensiveStruct结构体
    class MODEL_EXPORT ComprehensiveStructModel : public IModel {
    public:
        ComprehensiveStructModel() = default;
        
        // 实现 IModel 接口
        QCborMap toCbor() const override {
            return map;
        }
        
        void fromCbor(const QCborMap& map) override {
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
    
} // namespace examples
} // namespace structs
