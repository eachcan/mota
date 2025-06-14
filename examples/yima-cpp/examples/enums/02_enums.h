#pragma once

// 此文件由 Mota 代码生成器自动生成
// Mota 版本: 0.2.0
// 生成时间: 2025-06-15 01:57:09
// 源文件: .\examples\02_enums.mota

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
#include "01_annotations.h"

using namespace ymf;

namespace examples {
namespace enums {

// === 枚举定义 ===
enum class SimpleEnum {
        VALUE1,
        VALUE2,
        VALUE3
};

class SimpleEnumEnumUtil {
    public:
        static QStringList uiComments() {
            return QStringList{QLatin1String("=== 枚举定义 ===")};
        }

        static QStringList fieldNames() {
            return QStringList{QLatin1String("VALUE1"), QLatin1String("VALUE2"), QLatin1String("VALUE3")};
        }

        static SimpleEnum fromString(const QString& str) {
            if (str == QLatin1String("VALUE1")) return SimpleEnum::VALUE1;
            if (str == QLatin1String("VALUE2")) return SimpleEnum::VALUE2;
            if (str == QLatin1String("VALUE3")) return SimpleEnum::VALUE3;
            return SimpleEnum::VALUE1;

        }

        static QString toString(SimpleEnum value) {
            if (value == SimpleEnum::VALUE1) return QLatin1String("VALUE1");
            if (value == SimpleEnum::VALUE2) return QLatin1String("VALUE2");
            if (value == SimpleEnum::VALUE3) return QLatin1String("VALUE3");
            return QLatin1String("VALUE1");

        }

        static QStringList fieldUiComments(const QString& fieldName) {
            return QStringList();
        }

        static QVector<QSharedPointer<IAnnotation>> annotations() {
            return QVector<QSharedPointer<IAnnotation>>{
    [&]() {
        // annotation, set all arguments
        auto __instance = QSharedPointer<examples::annotations::ValueOnlyAnnotation>::create();
        __instance->setValue("simple_enum");
        return __instance;
    }(),
            };
        }

        static QVector<QSharedPointer<IAnnotation>> fieldAnnotations(const SimpleEnum& fieldName) {
            if (fieldName == SimpleEnum::VALUE1)
                 return QVector<QSharedPointer<IAnnotation>>{
                    [&]() {
        // annotation, set all arguments
        auto __instance = QSharedPointer<examples::annotations::BaseAnnotationAnnotation>::create();
        __instance->setDescription("第一个值");
        return __instance;
    }()
                };
            if (fieldName == SimpleEnum::VALUE2)
                 return QVector<QSharedPointer<IAnnotation>>{
                    [&]() {
        // annotation, set all arguments
        auto __instance = QSharedPointer<examples::annotations::BaseAnnotationAnnotation>::create();
        __instance->setDescription("第二个值");
        return __instance;
    }()
                };
            if (fieldName == SimpleEnum::VALUE3)
                 return QVector<QSharedPointer<IAnnotation>>{
                    [&]() {
        // annotation, set all arguments
        auto __instance = QSharedPointer<examples::annotations::BaseAnnotationAnnotation>::create();
        __instance->setDescription("第三个值");
        return __instance;
    }()
                };
            return {};
        }
};

enum class ArrayAnnotation {
        VALUE1,
        VALUE2
};

class ArrayAnnotationEnumUtil {
    public:
        static QStringList uiComments() {
            return QStringList();
        }

        static QStringList fieldNames() {
            return QStringList{QLatin1String("VALUE1"), QLatin1String("VALUE2")};
        }

        static ArrayAnnotation fromString(const QString& str) {
            if (str == QLatin1String("VALUE1")) return ArrayAnnotation::VALUE1;
            if (str == QLatin1String("VALUE2")) return ArrayAnnotation::VALUE2;
            return ArrayAnnotation::VALUE1;

        }

        static QString toString(ArrayAnnotation value) {
            if (value == ArrayAnnotation::VALUE1) return QLatin1String("VALUE1");
            if (value == ArrayAnnotation::VALUE2) return QLatin1String("VALUE2");
            return QLatin1String("VALUE1");

        }

        static QStringList fieldUiComments(const QString& fieldName) {
            return QStringList();
        }

        static QVector<QSharedPointer<IAnnotation>> annotations() {
            return QVector<QSharedPointer<IAnnotation>>();
        }

        static QVector<QSharedPointer<IAnnotation>> fieldAnnotations(const ArrayAnnotation& fieldName) {
            if (fieldName == ArrayAnnotation::VALUE1)
                 return QVector<QSharedPointer<IAnnotation>>{
                    [&]() {
        // annotation, set all arguments
        auto __instance = QSharedPointer<examples::annotations::ArrayBaseAnnotation>::create();
        QVector<QSharedPointer<examples::annotations::BaseAnnotationAnnotation>> __baseArrayArray;
        __baseArrayArray.append(    // array_item, construct a new instance line misc annotation
    [&]() {
        // array_item, set all arguments
        auto __instance = QSharedPointer<examples::annotations::BaseAnnotationAnnotation>::create();
        __instance->setDescription("第一个值");
        return __instance;
    }()
);
        __baseArrayArray.append(    // array_item, construct a new instance line misc annotation
    [&]() {
        // array_item, set all arguments
        auto __instance = QSharedPointer<examples::annotations::BaseAnnotationAnnotation>::create();
        __instance->setDescription("第二个值");
        return __instance;
    }()
);
        __instance->setBaseArray(__baseArrayArray);

        QVector<int32_t> __intArrayArray;
        __intArrayArray.append(1);   
        __intArrayArray.append(2);   
        __intArrayArray.append(3);   
        __instance->setIntArray(__intArrayArray);

        return __instance;
    }()
                };
            if (fieldName == ArrayAnnotation::VALUE2)
                 return QVector<QSharedPointer<IAnnotation>>{
                    [&]() {
        // annotation, set all arguments
        auto __instance = QSharedPointer<examples::annotations::ArrayBaseAnnotation>::create();
        QVector<QSharedPointer<examples::annotations::BaseAnnotationAnnotation>> __baseArrayArray;
        __baseArrayArray.append(    // array_item, construct a new instance line misc annotation
    [&]() {
        // array_item, set all arguments
        auto __instance = QSharedPointer<examples::annotations::BaseAnnotationAnnotation>::create();
        __instance->setDescription("第三个值");
        return __instance;
    }()
);
        __baseArrayArray.append(    // array_item, construct a new instance line misc annotation
    [&]() {
        // array_item, set all arguments
        auto __instance = QSharedPointer<examples::annotations::BaseAnnotationAnnotation>::create();
        __instance->setDescription("第四个值");
        return __instance;
    }()
);
        __instance->setBaseArray(__baseArrayArray);

        QVector<int32_t> __intArrayArray;
        __intArrayArray.append(4);   
        __intArrayArray.append(5);   
        __intArrayArray.append(6);   
        __instance->setIntArray(__intArrayArray);

        return __instance;
    }()
                };
            return {};
        }
};

enum class ValueEnum {
        LOW,
        MEDIUM,
        HIGH
};

class ValueEnumEnumUtil {
    public:
        static QStringList uiComments() {
            return QStringList();
        }

        static QStringList fieldNames() {
            return QStringList{QLatin1String("LOW"), QLatin1String("MEDIUM"), QLatin1String("HIGH")};
        }

        static ValueEnum fromString(const QString& str) {
            if (str == QLatin1String("LOW")) return ValueEnum::LOW;
            if (str == QLatin1String("MEDIUM")) return ValueEnum::MEDIUM;
            if (str == QLatin1String("HIGH")) return ValueEnum::HIGH;
            return ValueEnum::LOW;

        }

        static QString toString(ValueEnum value) {
            if (value == ValueEnum::LOW) return QLatin1String("LOW");
            if (value == ValueEnum::MEDIUM) return QLatin1String("MEDIUM");
            if (value == ValueEnum::HIGH) return QLatin1String("HIGH");
            return QLatin1String("LOW");

        }

        static QStringList fieldUiComments(const QString& fieldName) {
            return QStringList();
        }

        static QVector<QSharedPointer<IAnnotation>> annotations() {
            return QVector<QSharedPointer<IAnnotation>>{
    [&]() {
        // annotation, set all arguments
        auto __instance = QSharedPointer<examples::annotations::ExtendedAnnotationAnnotation>::create();
        __instance->setRequired(true);
        __instance->setRange(    // argument.value, construct a new instance line misc annotation
    [&]() {
        // argument.value, set all arguments
        auto __instance = QSharedPointer<examples::annotations::ValueAnnotationAnnotation>::create();
        __instance->setMin(1);
        __instance->setMax(10);
        return __instance;
    }()
);
        return __instance;
    }(),
            };
        }

        static QVector<QSharedPointer<IAnnotation>> fieldAnnotations(const ValueEnum& fieldName) {
            if (fieldName == ValueEnum::LOW)
                 return QVector<QSharedPointer<IAnnotation>>{
                    [&]() {
        // annotation, set all arguments
        auto __instance = QSharedPointer<examples::annotations::BaseAnnotationAnnotation>::create();
        __instance->setDescription("低优先级");
        return __instance;
    }()
                };
            if (fieldName == ValueEnum::MEDIUM)
                 return QVector<QSharedPointer<IAnnotation>>{
                    [&]() {
        // annotation, set all arguments
        auto __instance = QSharedPointer<examples::annotations::BaseAnnotationAnnotation>::create();
        __instance->setDescription("中优先级");
        return __instance;
    }()
                };
            if (fieldName == ValueEnum::HIGH)
                 return QVector<QSharedPointer<IAnnotation>>{
                    [&]() {
        // annotation, set all arguments
        auto __instance = QSharedPointer<examples::annotations::BaseAnnotationAnnotation>::create();
        __instance->setDescription("高优先级");
        return __instance;
    }()
                };
            return {};
        }
};

// EnumBlock块定义
class MODEL_EXPORT EnumBlockBlock : public IBlock {
public:
    EnumBlockBlock() = default;
    
    // 实现 IBlock 接口
    QCborMap toCbor() const override {

    }
    
    void fromCbor(const QCborMap& map) override {
    }
    
    QString name() const override {
        return QLatin1String("EnumBlock");
    }
    
    QStringList fields() const override {
        return QStringList{QLatin1String("simpleField"), QLatin1String("valueField"), QLatin1String("simpleArray"), QLatin1String("valueArray"), QLatin1String("optionalSimple"), QLatin1String("optionalValue"), QLatin1String("simpleMap"), QLatin1String("valueMap")};
    }
    
    QString fieldType(const QString& fieldName) const override {
        if (fieldName == QLatin1String("simpleField")) return QLatin1String("SimpleEnum");
        if (fieldName == QLatin1String("valueField")) return QLatin1String("ValueEnum");
        if (fieldName == QLatin1String("simpleArray")) return QLatin1String("SimpleEnum");
        if (fieldName == QLatin1String("valueArray")) return QLatin1String("ValueEnum");
        if (fieldName == QLatin1String("optionalSimple")) return QLatin1String("SimpleEnum");
        if (fieldName == QLatin1String("optionalValue")) return QLatin1String("ValueEnum");
        if (fieldName == QLatin1String("simpleMap")) return QLatin1String("SimpleEnum");
        if (fieldName == QLatin1String("valueMap")) return QLatin1String("ValueEnum");
        return QString();
    }
    
    QString fieldContainerType(const QString& fieldName) const override {
        if (fieldName == QLatin1String("simpleField")) return QLatin1String("none");
        if (fieldName == QLatin1String("valueField")) return QLatin1String("none");
        if (fieldName == QLatin1String("simpleArray")) return QLatin1String("array");
        if (fieldName == QLatin1String("valueArray")) return QLatin1String("array");
        if (fieldName == QLatin1String("optionalSimple")) return QLatin1String("optional");
        if (fieldName == QLatin1String("optionalValue")) return QLatin1String("optional");
        if (fieldName == QLatin1String("simpleMap")) return QLatin1String("map");
        if (fieldName == QLatin1String("valueMap")) return QLatin1String("map");
        return QLatin1String("none");
    }
    
    QList<QSharedPointer<IAnnotation>> annotations() const override {
        QList<QSharedPointer<IAnnotation>> result;
        return result;
    }
    
    QList<QSharedPointer<IAnnotation>> fieldAnnotation(const QString& fieldName) const override {
        if (fieldName == QLatin1String("simpleField")) {
            QList<QSharedPointer<IAnnotation>> result;
            return result;
        }
        if (fieldName == QLatin1String("valueField")) {
            QList<QSharedPointer<IAnnotation>> result;
            return result;
        }
        if (fieldName == QLatin1String("simpleArray")) {
            QList<QSharedPointer<IAnnotation>> result;
            return result;
        }
        if (fieldName == QLatin1String("valueArray")) {
            QList<QSharedPointer<IAnnotation>> result;
            return result;
        }
        if (fieldName == QLatin1String("optionalSimple")) {
            QList<QSharedPointer<IAnnotation>> result;
            return result;
        }
        if (fieldName == QLatin1String("optionalValue")) {
            QList<QSharedPointer<IAnnotation>> result;
            return result;
        }
        if (fieldName == QLatin1String("simpleMap")) {
            QList<QSharedPointer<IAnnotation>> result;
            return result;
        }
        if (fieldName == QLatin1String("valueMap")) {
            QList<QSharedPointer<IAnnotation>> result;
            return result;
        }
        return QList<QSharedPointer<IAnnotation>>();
    }
    
    QString description() const override {
        return QLatin1String("EnumBlock");
    }
    
    QString fieldDescription(const QString& fieldName) const override {
        if (fieldName == QLatin1String("simpleField")) return QLatin1String("simpleField");
        if (fieldName == QLatin1String("valueField")) return QLatin1String("valueField");
        if (fieldName == QLatin1String("simpleArray")) return QLatin1String("simpleArray");
        if (fieldName == QLatin1String("valueArray")) return QLatin1String("valueArray");
        if (fieldName == QLatin1String("optionalSimple")) return QLatin1String("optionalSimple");
        if (fieldName == QLatin1String("optionalValue")) return QLatin1String("optionalValue");
        if (fieldName == QLatin1String("simpleMap")) return QLatin1String("simpleMap");
        if (fieldName == QLatin1String("valueMap")) return QLatin1String("valueMap");
        return QString();
    }
    
    QVariant value(const QString& fieldName) const override {
        if (fieldName == QLatin1String("simpleField")) return QVariant::fromValue(simpleField_);
        if (fieldName == QLatin1String("valueField")) return QVariant::fromValue(valueField_);
        if (fieldName == QLatin1String("simpleArray")) return QVariant::fromValue(simpleArray_);
        if (fieldName == QLatin1String("valueArray")) return QVariant::fromValue(valueArray_);
        if (fieldName == QLatin1String("optionalSimple")) return QVariant::fromValue(optionalSimple_);
        if (fieldName == QLatin1String("optionalValue")) return QVariant::fromValue(optionalValue_);
        if (fieldName == QLatin1String("simpleMap")) return QVariant::fromValue(simpleMap_);
        if (fieldName == QLatin1String("valueMap")) return QVariant::fromValue(valueMap_);
        return QVariant();
    }
    
    void value(const QString& fieldName, const QVariant& value) override {
        if (fieldName == QLatin1String("simpleField")) {
            simpleField_ = value.value<SimpleEnum>();
            return;
        }
        if (fieldName == QLatin1String("valueField")) {
            valueField_ = value.value<ValueEnum>();
            return;
        }
        if (fieldName == QLatin1String("simpleArray")) {
            simpleArray_ = value.value<QVector<SimpleEnum>>();
            return;
        }
        if (fieldName == QLatin1String("valueArray")) {
            valueArray_ = value.value<QVector<ValueEnum>>();
            return;
        }
        if (fieldName == QLatin1String("optionalSimple")) {
            optionalSimple_ = value.value<std::optional<SimpleEnum>>();
            return;
        }
        if (fieldName == QLatin1String("optionalValue")) {
            optionalValue_ = value.value<std::optional<ValueEnum>>();
            return;
        }
        if (fieldName == QLatin1String("simpleMap")) {
            simpleMap_ = value.value<QMap<QString, SimpleEnum>>();
            return;
        }
        if (fieldName == QLatin1String("valueMap")) {
            valueMap_ = value.value<QMap<QString, ValueEnum>>();
            return;
        }
    }
    
    // 字段访问器
    SimpleEnum getSimpleField() const { return simpleField_; }
    void setSimpleField(const SimpleEnum& value) { simpleField_ = value; }
    ValueEnum getValueField() const { return valueField_; }
    void setValueField(const ValueEnum& value) { valueField_ = value; }
    QVector<SimpleEnum> getSimpleArray() const { return simpleArray_; }
    void setSimpleArray(const QVector<SimpleEnum>& value) { simpleArray_ = value; }
    QVector<ValueEnum> getValueArray() const { return valueArray_; }
    void setValueArray(const QVector<ValueEnum>& value) { valueArray_ = value; }
    std::optional<SimpleEnum> getOptionalSimple() const { return optionalSimple_; }
    void setOptionalSimple(const std::optional<SimpleEnum>& value) { optionalSimple_ = value; }
    std::optional<ValueEnum> getOptionalValue() const { return optionalValue_; }
    void setOptionalValue(const std::optional<ValueEnum>& value) { optionalValue_ = value; }
    QMap<QString, SimpleEnum> getSimpleMap() const { return simpleMap_; }
    void setSimpleMap(const QMap<QString, SimpleEnum>& value) { simpleMap_ = value; }
    QMap<QString, ValueEnum> getValueMap() const { return valueMap_; }
    void setValueMap(const QMap<QString, ValueEnum>& value) { valueMap_ = value; }
private:
    // EnumStruct结构体
    class MODEL_EXPORT EnumStructModel : public IModel {
    public:
        EnumStructModel() = default;
        
        // 实现 IModel 接口
        QCborMap toCbor() const override {
            return map;
        }
        
        void fromCbor(const QCborMap& map) override {
        }
        
        QString name() const override {
            return QLatin1String("EnumStruct");
        }
        
        QStringList fields() const override {
            return QStringList{QLatin1String("simpleField"), QLatin1String("valueField"), QLatin1String("simpleArray"), QLatin1String("valueArray"), QLatin1String("optionalSimple"), QLatin1String("optionalValue"), QLatin1String("simpleMap"), QLatin1String("valueMap"), QLatin1String("blockField"), QLatin1String("blockArray"), QLatin1String("optionalBlock")};
        }
        
        QString fieldType(const QString& fieldName) const override {
            if (fieldName == QLatin1String("simpleField")) return QLatin1String("SimpleEnum");
            if (fieldName == QLatin1String("valueField")) return QLatin1String("ValueEnum");
            if (fieldName == QLatin1String("simpleArray")) return QLatin1String("SimpleEnum");
            if (fieldName == QLatin1String("valueArray")) return QLatin1String("ValueEnum");
            if (fieldName == QLatin1String("optionalSimple")) return QLatin1String("SimpleEnum");
            if (fieldName == QLatin1String("optionalValue")) return QLatin1String("ValueEnum");
            if (fieldName == QLatin1String("simpleMap")) return QLatin1String("SimpleEnum");
            if (fieldName == QLatin1String("valueMap")) return QLatin1String("ValueEnum");
            if (fieldName == QLatin1String("blockField")) return QLatin1String("EnumBlock");
            if (fieldName == QLatin1String("blockArray")) return QLatin1String("EnumBlock");
            if (fieldName == QLatin1String("optionalBlock")) return QLatin1String("EnumBlock");
            return QString();
        }
        
        QString fieldContainerType(const QString& fieldName) const override {
            if (fieldName == QLatin1String("simpleField")) return QLatin1String("none");
            if (fieldName == QLatin1String("valueField")) return QLatin1String("none");
            if (fieldName == QLatin1String("simpleArray")) return QLatin1String("array");
            if (fieldName == QLatin1String("valueArray")) return QLatin1String("array");
            if (fieldName == QLatin1String("optionalSimple")) return QLatin1String("optional");
            if (fieldName == QLatin1String("optionalValue")) return QLatin1String("optional");
            if (fieldName == QLatin1String("simpleMap")) return QLatin1String("map");
            if (fieldName == QLatin1String("valueMap")) return QLatin1String("map");
            if (fieldName == QLatin1String("blockField")) return QLatin1String("none");
            if (fieldName == QLatin1String("blockArray")) return QLatin1String("array");
            if (fieldName == QLatin1String("optionalBlock")) return QLatin1String("optional");
            return QLatin1String("none");
        }
    
        // 字段访问器
        SimpleEnum getSimpleField() const { return simpleField_; }
        void setSimpleField(const SimpleEnum& value) { simpleField_ = value; }
    ValueEnum getValueField() const { return valueField_; }
        void setValueField(const ValueEnum& value) { valueField_ = value; }
    QVector<SimpleEnum> getSimpleArray() const { return simpleArray_; }
        void setSimpleArray(const QVector<SimpleEnum>& value) { simpleArray_ = value; }
    QVector<ValueEnum> getValueArray() const { return valueArray_; }
        void setValueArray(const QVector<ValueEnum>& value) { valueArray_ = value; }
    std::optional<SimpleEnum> getOptionalSimple() const { return optionalSimple_; }
        void setOptionalSimple(const std::optional<SimpleEnum>& value) { optionalSimple_ = value; }
    std::optional<ValueEnum> getOptionalValue() const { return optionalValue_; }
        void setOptionalValue(const std::optional<ValueEnum>& value) { optionalValue_ = value; }
    QMap<QString, SimpleEnum> getSimpleMap() const { return simpleMap_; }
        void setSimpleMap(const QMap<QString, SimpleEnum>& value) { simpleMap_ = value; }
    QMap<QString, ValueEnum> getValueMap() const { return valueMap_; }
        void setValueMap(const QMap<QString, ValueEnum>& value) { valueMap_ = value; }
    EnumBlockBlock getBlockField() const { return blockField_; }
        void setBlockField(const EnumBlockBlock& value) { blockField_ = value; }
    QVector<EnumBlockBlock> getBlockArray() const { return blockArray_; }
        void setBlockArray(const QVector<EnumBlockBlock>& value) { blockArray_ = value; }
    std::optional<EnumBlockBlock> getOptionalBlock() const { return optionalBlock_; }
        void setOptionalBlock(const std::optional<EnumBlockBlock>& value) { optionalBlock_ = value; }
    private:
    
} // namespace examples
} // namespace enums
