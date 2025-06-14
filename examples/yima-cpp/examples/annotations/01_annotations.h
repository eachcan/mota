#pragma once

// 此文件由 Mota 代码生成器自动生成
// Mota 版本: 0.2.0
// 生成时间: 2025-06-15 19:04:27
// 源文件: .\examples\01_annotations.mota

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
namespace annotations {

// === 基础注解 ===
// 这是注解的UI注释
class MODEL_EXPORT BaseAnnotationAnnotation : public IAnnotation {
public:
    BaseAnnotationAnnotation() = default;
    
    // 实现IAnnotation接口
    QString name() const override {
        return QLatin1String("BaseAnnotation");
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
Q_DECLARE_METATYPE(BaseAnnotationAnnotation)

class MODEL_EXPORT ArrayBaseAnnotation : public IAnnotation {
public:
    ArrayBaseAnnotation() = default;
    
    // 实现IAnnotation接口
    QString name() const override {
        return QLatin1String("ArrayBase");
    }
    
    virtual QVariant argumentValue(const QString& argumentName) const override {
        if (argumentName == QLatin1String("baseArray")) {
            QVariantList list;
            for (const auto& item : baseArray_) {
                list.append(QVariant::fromValue(item));
            }
            return list;
        }
        if (argumentName == QLatin1String("intArray")) {
            QVariantList list;
            for (const auto& item : intArray_) {
                list.append(QVariant::fromValue(item));
            }
            return list;
        }
        return QVariant();
    }
    
    virtual QStringList fieldNames() const override {
        QStringList names = QStringList{QLatin1String("baseArray"), QLatin1String("intArray")};
        return names;
    }

    virtual QStringList uiComments() const override {
        return QStringList{};
    }
    
    virtual QStringList fieldUiComments(const QString& fieldName) const override {
        if (fieldName == QLatin1String("baseArray")) {
            return QStringList{};
        }
        if (fieldName == QLatin1String("intArray")) {
            return QStringList{};
        }
        return QStringList();
    }

    QVector<QSharedPointer<BaseAnnotationAnnotation>> getBaseArray() const {
        return baseArray_;
    }
    void setBaseArray(const QVector<QSharedPointer<BaseAnnotationAnnotation>>& value) {
        baseArray_ = value;
    }
    QVector<int32_t> getIntArray() const {
        return intArray_; 
    }
    void setIntArray(const QVector<int32_t>& value) {
        intArray_ = value;
    }
private:
    QVector<QSharedPointer<BaseAnnotationAnnotation>> baseArray_;
    QVector<int32_t> intArray_;
};
Q_DECLARE_METATYPE(ArrayBaseAnnotation)

// 这是注解的UI注释
// 这是第二行 UI 注释
class MODEL_EXPORT ValueAnnotationAnnotation : public IAnnotation {
public:
    ValueAnnotationAnnotation() = default;
    
    // 实现IAnnotation接口
    QString name() const override {
        return QLatin1String("ValueAnnotation");
    }
    
    virtual QVariant argumentValue(const QString& argumentName) const override {
        if (argumentName == QLatin1String("min")) {
            return QVariant::fromValue(min_);
        }
        if (argumentName == QLatin1String("max")) {
            return QVariant::fromValue(max_);
        }
        return QVariant();
    }
    
    virtual QStringList fieldNames() const override {
        QStringList names = QStringList{QLatin1String("min"), QLatin1String("max")};
        return names;
    }

    virtual QStringList uiComments() const override {
        return QStringList{};
    }
    
    virtual QStringList fieldUiComments(const QString& fieldName) const override {
        if (fieldName == QLatin1String("min")) {
            return QStringList{};
        }
        if (fieldName == QLatin1String("max")) {
            return QStringList{};
        }
        return QStringList();
    }

    // 最小值
// 请你注意，最小值不能小于0
    int32_t getMin() const {
        return min_;
    }
    void setMin(const int32_t& value) {
        min_ = value;
    }
    int32_t getMax() const {
        return max_;
    }
    void setMax(const int32_t& value) {
        max_ = value;
    }
private:
    int32_t min_ = 0;
    int32_t max_ = 100;
};
Q_DECLARE_METATYPE(ValueAnnotationAnnotation)

class MODEL_EXPORT IniStorageAnnotation : public yima::StorageAnnotation {
public:
    IniStorageAnnotation() = default;
    
    // 实现IAnnotation接口
    QString name() const override {
        return QLatin1String("IniStorage");
    }
    
    virtual QVariant argumentValue(const QString& argumentName) const override {
        if (argumentName == QLatin1String("ini_path")) {
            return QVariant::fromValue(ini_path_);
        }
        return yima::StorageAnnotation::argumentValue(argumentName);
    }
    
    virtual QStringList fieldNames() const override {
        QStringList names = QStringList{QLatin1String("ini_path")};
        names.append(yima::StorageAnnotation::fieldNames());
        return names;
    }

    virtual QStringList uiComments() const override {
        return QStringList{};
    }
    
    virtual QStringList fieldUiComments(const QString& fieldName) const override {
        if (fieldName == QLatin1String("ini_path")) {
            return QStringList{};
        }
        return yima::StorageAnnotation::fieldUiComments(fieldName);
    }

    QString getIniPath() const {
        return ini_path_;
    }
    void setIniPath(const QString& value) {
        ini_path_ = value;
    }
private:
    QString ini_path_ = "";
};
Q_DECLARE_METATYPE(IniStorageAnnotation)

// === 注解继承 ===
class MODEL_EXPORT ExtendedAnnotationAnnotation : public BaseAnnotationAnnotation {
public:
    ExtendedAnnotationAnnotation() = default;
    
    // 实现IAnnotation接口
    QString name() const override {
        return QLatin1String("ExtendedAnnotation");
    }
    
    virtual QVariant argumentValue(const QString& argumentName) const override {
        if (argumentName == QLatin1String("required")) {
            return QVariant::fromValue(required_);
        }
        if (argumentName == QLatin1String("range")) {
            return QVariant::fromValue(range_);
        }
        return BaseAnnotationAnnotation::argumentValue(argumentName);
    }
    
    virtual QStringList fieldNames() const override {
        QStringList names = QStringList{QLatin1String("required"), QLatin1String("range")};
        names.append(BaseAnnotationAnnotation::fieldNames());
        return names;
    }

    virtual QStringList uiComments() const override {
        return QStringList{};
    }
    
    virtual QStringList fieldUiComments(const QString& fieldName) const override {
        if (fieldName == QLatin1String("required")) {
            return QStringList{};
        }
        if (fieldName == QLatin1String("range")) {
            return QStringList{};
        }
        return BaseAnnotationAnnotation::fieldUiComments(fieldName);
    }

    // 是否必填
    bool getRequired() const {
        return required_;
    }
    void setRequired(const bool& value) {
        required_ = value;
    }
    // 注解作为字段类型
    QSharedPointer<ValueAnnotationAnnotation> getRange() const {
        return range_;
    }
    void setRange(const QSharedPointer<ValueAnnotationAnnotation>& value) {
        range_ = value;
    }
private:
    bool required_ = false;
    QSharedPointer<ValueAnnotationAnnotation> range_;
};
Q_DECLARE_METATYPE(ExtendedAnnotationAnnotation)

// === 全字段类型测试 ===
class MODEL_EXPORT AllTypesAnnotationAnnotation : public IAnnotation {
public:
    AllTypesAnnotationAnnotation() = default;
    
    // 实现IAnnotation接口
    QString name() const override {
        return QLatin1String("AllTypesAnnotation");
    }
    
    virtual QVariant argumentValue(const QString& argumentName) const override {
        if (argumentName == QLatin1String("int8Field")) {
            return QVariant::fromValue(int8Field_);
        }
        if (argumentName == QLatin1String("int16Field")) {
            return QVariant::fromValue(int16Field_);
        }
        if (argumentName == QLatin1String("int32Field")) {
            return QVariant::fromValue(int32Field_);
        }
        if (argumentName == QLatin1String("int64Field")) {
            return QVariant::fromValue(int64Field_);
        }
        if (argumentName == QLatin1String("uint8Field")) {
            return QVariant::fromValue(uint8Field_);
        }
        if (argumentName == QLatin1String("uint16Field")) {
            return QVariant::fromValue(uint16Field_);
        }
        if (argumentName == QLatin1String("uint32Field")) {
            return QVariant::fromValue(uint32Field_);
        }
        if (argumentName == QLatin1String("uint64Field")) {
            return QVariant::fromValue(uint64Field_);
        }
        if (argumentName == QLatin1String("float32Field")) {
            return QVariant::fromValue(float32Field_);
        }
        if (argumentName == QLatin1String("float64Field")) {
            return QVariant::fromValue(float64Field_);
        }
        if (argumentName == QLatin1String("boolField")) {
            return QVariant::fromValue(boolField_);
        }
        if (argumentName == QLatin1String("stringField")) {
            return QVariant::fromValue(stringField_);
        }
        if (argumentName == QLatin1String("bytesField")) {
            return QVariant::fromValue(bytesField_);
        }
        if (argumentName == QLatin1String("baseRef")) {
            return QVariant::fromValue(baseRef_);
        }
        if (argumentName == QLatin1String("valueRef")) {
            return QVariant::fromValue(valueRef_);
        }
        return QVariant();
    }
    
    virtual QStringList fieldNames() const override {
        QStringList names = QStringList{QLatin1String("int8Field"), QLatin1String("int16Field"), QLatin1String("int32Field"), QLatin1String("int64Field"), QLatin1String("uint8Field"), QLatin1String("uint16Field"), QLatin1String("uint32Field"), QLatin1String("uint64Field"), QLatin1String("float32Field"), QLatin1String("float64Field"), QLatin1String("boolField"), QLatin1String("stringField"), QLatin1String("bytesField"), QLatin1String("baseRef"), QLatin1String("valueRef")};
        return names;
    }

    virtual QStringList uiComments() const override {
        return QStringList{};
    }
    
    virtual QStringList fieldUiComments(const QString& fieldName) const override {
        if (fieldName == QLatin1String("int8Field")) {
            return QStringList{};
        }
        if (fieldName == QLatin1String("int16Field")) {
            return QStringList{};
        }
        if (fieldName == QLatin1String("int32Field")) {
            return QStringList{};
        }
        if (fieldName == QLatin1String("int64Field")) {
            return QStringList{};
        }
        if (fieldName == QLatin1String("uint8Field")) {
            return QStringList{};
        }
        if (fieldName == QLatin1String("uint16Field")) {
            return QStringList{};
        }
        if (fieldName == QLatin1String("uint32Field")) {
            return QStringList{};
        }
        if (fieldName == QLatin1String("uint64Field")) {
            return QStringList{};
        }
        if (fieldName == QLatin1String("float32Field")) {
            return QStringList{};
        }
        if (fieldName == QLatin1String("float64Field")) {
            return QStringList{};
        }
        if (fieldName == QLatin1String("boolField")) {
            return QStringList{};
        }
        if (fieldName == QLatin1String("stringField")) {
            return QStringList{};
        }
        if (fieldName == QLatin1String("bytesField")) {
            return QStringList{};
        }
        if (fieldName == QLatin1String("baseRef")) {
            return QStringList{};
        }
        if (fieldName == QLatin1String("valueRef")) {
            return QStringList{};
        }
        return QStringList();
    }

    // 所有基础类型
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
    // 注解类型
    QSharedPointer<BaseAnnotationAnnotation> getBaseRef() const {
        return baseRef_;
    }
    void setBaseRef(const QSharedPointer<BaseAnnotationAnnotation>& value) {
        baseRef_ = value;
    }
    QSharedPointer<ValueAnnotationAnnotation> getValueRef() const {
        return valueRef_;
    }
    void setValueRef(const QSharedPointer<ValueAnnotationAnnotation>& value) {
        valueRef_ = value;
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
    QSharedPointer<BaseAnnotationAnnotation> baseRef_;
    QSharedPointer<ValueAnnotationAnnotation> valueRef_;
};
Q_DECLARE_METATYPE(AllTypesAnnotationAnnotation)

// === 容器类型测试 ===
class MODEL_EXPORT ContainerAnnotationAnnotation : public IAnnotation {
public:
    ContainerAnnotationAnnotation() = default;
    
    // 实现IAnnotation接口
    QString name() const override {
        return QLatin1String("ContainerAnnotation");
    }
    
    virtual QVariant argumentValue(const QString& argumentName) const override {
        if (argumentName == QLatin1String("intArray")) {
            QVariantList list;
            for (const auto& item : intArray_) {
                list.append(QVariant::fromValue(item));
            }
            return list;
        }
        if (argumentName == QLatin1String("stringArray")) {
            QVariantList list;
            for (const auto& item : stringArray_) {
                list.append(QVariant::fromValue(item));
            }
            return list;
        }
        if (argumentName == QLatin1String("annotationArray")) {
            QVariantList list;
            for (const auto& item : annotationArray_) {
                list.append(QVariant::fromValue(item));
            }
            return list;
        }
        if (argumentName == QLatin1String("optionalInt")) {
            return QVariant::fromValue(optionalInt_);
        }
        if (argumentName == QLatin1String("optionalString")) {
            return QVariant::fromValue(optionalString_);
        }
        if (argumentName == QLatin1String("optionalAnnotation")) {
            return QVariant::fromValue(optionalAnnotation_);
        }
        if (argumentName == QLatin1String("intMap")) {
            return QVariant::fromValue(intMap_);
        }
        if (argumentName == QLatin1String("stringMap")) {
            return QVariant::fromValue(stringMap_);
        }
        if (argumentName == QLatin1String("annotationMap")) {
            return QVariant::fromValue(annotationMap_);
        }
        return QVariant();
    }
    
    virtual QStringList fieldNames() const override {
        QStringList names = QStringList{QLatin1String("intArray"), QLatin1String("stringArray"), QLatin1String("annotationArray"), QLatin1String("optionalInt"), QLatin1String("optionalString"), QLatin1String("optionalAnnotation"), QLatin1String("intMap"), QLatin1String("stringMap"), QLatin1String("annotationMap")};
        return names;
    }

    virtual QStringList uiComments() const override {
        return QStringList{};
    }
    
    virtual QStringList fieldUiComments(const QString& fieldName) const override {
        if (fieldName == QLatin1String("intArray")) {
            return QStringList{};
        }
        if (fieldName == QLatin1String("stringArray")) {
            return QStringList{};
        }
        if (fieldName == QLatin1String("annotationArray")) {
            return QStringList{};
        }
        if (fieldName == QLatin1String("optionalInt")) {
            return QStringList{};
        }
        if (fieldName == QLatin1String("optionalString")) {
            return QStringList{};
        }
        if (fieldName == QLatin1String("optionalAnnotation")) {
            return QStringList{};
        }
        if (fieldName == QLatin1String("intMap")) {
            return QStringList{};
        }
        if (fieldName == QLatin1String("stringMap")) {
            return QStringList{};
        }
        if (fieldName == QLatin1String("annotationMap")) {
            return QStringList{};
        }
        return QStringList();
    }

    // repeated容器
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
    QVector<QSharedPointer<BaseAnnotationAnnotation>> getAnnotationArray() const {
        return annotationArray_;
    }
    void setAnnotationArray(const QVector<QSharedPointer<BaseAnnotationAnnotation>>& value) {
        annotationArray_ = value;
    }
    // optional容器
    std::optional<int32_t> getOptionalInt() const {
        return optionalInt_;
    }
    void setOptionalInt(const std::optional<int32_t>& value) {
        optionalInt_ = value;
    }
    std::optional<QString> getOptionalString() const {
        return optionalString_;
    }
    void setOptionalString(const std::optional<QString>& value) {
        optionalString_ = value;
    }
    std::optional<QSharedPointer<BaseAnnotationAnnotation>> getOptionalAnnotation() const {
        return optionalAnnotation_;
    }
    void setOptionalAnnotation(const std::optional<QSharedPointer<BaseAnnotationAnnotation>>& value) {
        optionalAnnotation_ = value;
    }
    // map容器
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
    QMap<QString, QSharedPointer<BaseAnnotationAnnotation>> getAnnotationMap() const {
        return annotationMap_;
    }
    void setAnnotationMap(const QMap<QString, QSharedPointer<BaseAnnotationAnnotation>>& value) {
        annotationMap_ = value;
    }
private:
    QVector<int32_t> intArray_;
    QVector<QString> stringArray_;
    QVector<QSharedPointer<BaseAnnotationAnnotation>> annotationArray_;
    std::optional<int32_t> optionalInt_;
    std::optional<QString> optionalString_;
    std::optional<QSharedPointer<BaseAnnotationAnnotation>> optionalAnnotation_;
    QMap<QString, int32_t> intMap_;
    QMap<QString, QString> stringMap_;
    QMap<QString, QSharedPointer<BaseAnnotationAnnotation>> annotationMap_;
};
Q_DECLARE_METATYPE(ContainerAnnotationAnnotation)

// === 特殊注解 ===
class MODEL_EXPORT ValueOnlyAnnotation : public IAnnotation {
public:
    ValueOnlyAnnotation() = default;
    
    // 实现IAnnotation接口
    QString name() const override {
        return QLatin1String("ValueOnly");
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

    // 字段名为value，使用时可省略参数名
    QString getValue() const {
        return value_;
    }
    void setValue(const QString& value) {
        value_ = value;
    }
private:
    QString value_;
};
Q_DECLARE_METATYPE(ValueOnlyAnnotation)

// 这是一个没有参数的注解
class MODEL_EXPORT NoParamsAnnotation : public IAnnotation {
public:
    NoParamsAnnotation() = default;
    
    // 实现IAnnotation接口
    QString name() const override {
        return QLatin1String("NoParams");
    }
    
    virtual QVariant argumentValue(const QString& argumentName) const override {
        return QVariant();
    }
    
    virtual QStringList fieldNames() const override {
        QStringList names = QStringList{};
        return names;
    }

    virtual QStringList uiComments() const override {
        return QStringList{};
    }
    
    virtual QStringList fieldUiComments(const QString& fieldName) const override {
        return QStringList();
    }

private:
};
Q_DECLARE_METATYPE(NoParamsAnnotation)


} // namespace examples
} // namespace annotations
