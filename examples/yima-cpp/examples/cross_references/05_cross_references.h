#pragma once

// 此文件由 Mota 代码生成器自动生成
// Mota 版本: 0.2.0
// 生成时间: 2025-06-14 19:05:02
// 源文件: .\examples\05_cross_references.mota

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
#include "02_enums.h"
#include "03_blocks.h"
#include "04_structs.h"

using namespace ymf;

namespace examples {
namespace cross_references {

enum class CrossEnum {
    FIRST,
    SECOND,
    THIRD
};

class CrossEnumEnumUtil {
    public:
        static QStringList uiComments() {
            return QStringList();
        }

        static QStringList fieldNames() {
            return QStringList{QLatin1String("FIRST"), QLatin1String("SECOND"), QLatin1String("THIRD")};
        }

        static CrossEnum fromString(const QString& str) {
            if (str == QLatin1String("FIRST")) return CrossEnum::FIRST;
            if (str == QLatin1String("SECOND")) return CrossEnum::SECOND;
            if (str == QLatin1String("THIRD")) return CrossEnum::THIRD;
            return CrossEnum::FIRST;

        }

        static QString toString(CrossEnum value) {
            if (value == CrossEnum::FIRST) return QLatin1String("FIRST");
            if (value == CrossEnum::SECOND) return QLatin1String("SECOND");
            if (value == CrossEnum::THIRD) return QLatin1String("THIRD");
            return QLatin1String("FIRST");

        }

        static QStringList fieldUiComments(const QString& fieldName) {
            return QStringList();
        }

        static QVector<QSharedPointer<IAnnotation>> annotations() {
            return QVector<QSharedPointer<IAnnotation>>();
        }

        static QVector<QSharedPointer<IAnnotation>> fieldAnnotations(const QString& fieldName) {
            return QVector<QSharedPointer<IAnnotation>>();
        }
};

// CrossBlock块定义
class MODEL_EXPORT CrossBlockBlock : public IBlock {
public:
    CrossBlockBlock() = default;
    
    // 实现 IBlock 接口
    QCborMap toCbor() const override {
        QCborMap map;
                map.insert(QLatin1String("id"), id_.toCbor());
                map.insert(QLatin1String("name"), name_.toCbor());
                map.insert(QLatin1String("simpleStatus"), simpleStatus_.toCbor());
                map.insert(QLatin1String("valueStatus"), valueStatus_.toCbor());
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
        tmpValue = map.value(QLatin1String("simpleStatus"));
        if (!tmpValue.isNull()) {
            simpleStatus_.fromCbor(tmpValue.toMap());
        }
        tmpValue = map.value(QLatin1String("valueStatus"));
        if (!tmpValue.isNull()) {
            valueStatus_.fromCbor(tmpValue.toMap());
        }
    }
    
    QString name() const override {
        return QLatin1String("CrossBlock");
    }
    
    QStringList fields() const override {
        return QStringList{QLatin1String("id"), QLatin1String("name"), QLatin1String("simpleStatus"), QLatin1String("valueStatus")};
    }
    
    QString fieldType(const QString& fieldName) const override {
        if (fieldName == QLatin1String("id")) return QLatin1String("int32");
        if (fieldName == QLatin1String("name")) return QLatin1String("string");
        if (fieldName == QLatin1String("simpleStatus")) return QLatin1String("examples.enums.SimpleEnum");
        if (fieldName == QLatin1String("valueStatus")) return QLatin1String("examples.enums.ValueEnum");
        return QString();
    }
    
    QString fieldContainerType(const QString& fieldName) const override {
        if (fieldName == QLatin1String("id")) return QLatin1String("none");
        if (fieldName == QLatin1String("name")) return QLatin1String("none");
        if (fieldName == QLatin1String("simpleStatus")) return QLatin1String("none");
        if (fieldName == QLatin1String("valueStatus")) return QLatin1String("none");
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
        if (fieldName == QLatin1String("simpleStatus")) {
            QList<QSharedPointer<IAnnotation>> result;
            return result;
        }
        if (fieldName == QLatin1String("valueStatus")) {
            QList<QSharedPointer<IAnnotation>> result;
            return result;
        }
        return QList<QSharedPointer<IAnnotation>>();
    }
    
    QString description() const override {
        return QLatin1String("CrossBlock");
    }
    
    QString fieldDescription(const QString& fieldName) const override {
        if (fieldName == QLatin1String("id")) return QLatin1String("id");
        if (fieldName == QLatin1String("name")) return QLatin1String("name");
        if (fieldName == QLatin1String("simpleStatus")) return QLatin1String("simpleStatus");
        if (fieldName == QLatin1String("valueStatus")) return QLatin1String("valueStatus");
        return QString();
    }
    
    QVariant value(const QString& fieldName) const override {
        if (fieldName == QLatin1String("id")) return QVariant::fromValue(id_);
        if (fieldName == QLatin1String("name")) return QVariant::fromValue(name_);
        if (fieldName == QLatin1String("simpleStatus")) return QVariant::fromValue(simpleStatus_);
        if (fieldName == QLatin1String("valueStatus")) return QVariant::fromValue(valueStatus_);
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
        if (fieldName == QLatin1String("simpleStatus")) {
            simpleStatus_ = value.value<examples::enums::SimpleEnum>();
            return;
        }
        if (fieldName == QLatin1String("valueStatus")) {
            valueStatus_ = value.value<examples::enums::ValueEnum>();
            return;
        }
    }
    
    // 字段访问器
    int32_t getId() const { return id_; }
    void setId(const int32_t& value) { id_ = value; }
    QString getName() const { return name_; }
    void setName(const QString& value) { name_ = value; }
    examples::enums::SimpleEnum getSimpleStatus() const { return simpleStatus_; }
    void setSimpleStatus(const examples::enums::SimpleEnum& value) { simpleStatus_ = value; }
    examples::enums::ValueEnum getValueStatus() const { return valueStatus_; }
    void setValueStatus(const examples::enums::ValueEnum& value) { valueStatus_ = value; }
private:
    int32_t id_ = 0;
    QString name_ = "";
    examples::enums::SimpleEnum simpleStatus_ = /* complex expression */;
    examples::enums::ValueEnum valueStatus_ = /* complex expression */;
};
Q_DECLARE_METATYPE(CrossBlockBlock)

// InheritedCrossBlock块定义
class MODEL_EXPORT InheritedCrossBlockBlock : public examples::blocks::BaseBlockBlock, public IBlock {
public:
    InheritedCrossBlockBlock() = default;
    
    // 实现 IBlock 接口
    QCborMap toCbor() const override {
        QCborMap map = examples::blocks::BaseBlockBlock::toCbor();
                map.insert(QLatin1String("score"), score_.toCbor());
                map.insert(QLatin1String("category"), category_.toCbor());
                map.insert(QLatin1String("blockStatus"), blockStatus_.toCbor());
        return map;
    }
    
    void fromCbor(const QCborMap& map) override {
        examples::blocks::BaseBlockBlock::fromCbor(map);
        QCborValue tmpValue;
        tmpValue = map.value(QLatin1String("score"));
        if (!tmpValue.isNull()) {
            score_.fromCbor(tmpValue.toMap());
        }
        tmpValue = map.value(QLatin1String("category"));
        if (!tmpValue.isNull()) {
            category_.fromCbor(tmpValue.toMap());
        }
        tmpValue = map.value(QLatin1String("blockStatus"));
        if (!tmpValue.isNull()) {
            blockStatus_.fromCbor(tmpValue.toMap());
        }
    }
    
    QString name() const override {
        return QLatin1String("InheritedCrossBlock");
    }
    
    QStringList fields() const override {
        return QStringList{QLatin1String("score"), QLatin1String("category"), QLatin1String("blockStatus")};
    }
    
    QString fieldType(const QString& fieldName) const override {
        if (fieldName == QLatin1String("score")) return QLatin1String("float64");
        if (fieldName == QLatin1String("category")) return QLatin1String("examples.enums.SimpleEnum");
        if (fieldName == QLatin1String("blockStatus")) return QLatin1String("examples.blocks.BlockStatus");
        return QString();
    }
    
    QString fieldContainerType(const QString& fieldName) const override {
        if (fieldName == QLatin1String("score")) return QLatin1String("none");
        if (fieldName == QLatin1String("category")) return QLatin1String("none");
        if (fieldName == QLatin1String("blockStatus")) return QLatin1String("none");
        return QLatin1String("none");
    }
    
    QList<QSharedPointer<IAnnotation>> annotations() const override {
        QList<QSharedPointer<IAnnotation>> result;
        return result;
    }
    
    QList<QSharedPointer<IAnnotation>> fieldAnnotation(const QString& fieldName) const override {
        if (fieldName == QLatin1String("score")) {
            QList<QSharedPointer<IAnnotation>> result;
            return result;
        }
        if (fieldName == QLatin1String("category")) {
            QList<QSharedPointer<IAnnotation>> result;
            return result;
        }
        if (fieldName == QLatin1String("blockStatus")) {
            QList<QSharedPointer<IAnnotation>> result;
            return result;
        }
        return QList<QSharedPointer<IAnnotation>>();
    }
    
    QString description() const override {
        return QLatin1String("InheritedCrossBlock");
    }
    
    QString fieldDescription(const QString& fieldName) const override {
        if (fieldName == QLatin1String("score")) return QLatin1String("score");
        if (fieldName == QLatin1String("category")) return QLatin1String("category");
        if (fieldName == QLatin1String("blockStatus")) return QLatin1String("blockStatus");
        return QString();
    }
    
    QVariant value(const QString& fieldName) const override {
        if (fieldName == QLatin1String("score")) return QVariant::fromValue(score_);
        if (fieldName == QLatin1String("category")) return QVariant::fromValue(category_);
        if (fieldName == QLatin1String("blockStatus")) return QVariant::fromValue(blockStatus_);
        return QVariant();
    }
    
    void value(const QString& fieldName, const QVariant& value) override {
        if (fieldName == QLatin1String("score")) {
            score_ = value.value<double>();
            return;
        }
        if (fieldName == QLatin1String("category")) {
            category_ = value.value<examples::enums::SimpleEnum>();
            return;
        }
        if (fieldName == QLatin1String("blockStatus")) {
            blockStatus_ = value.value<examples::blocks::BlockStatus>();
            return;
        }
    }
    
    // 字段访问器
    double getScore() const { return score_; }
    void setScore(const double& value) { score_ = value; }
    examples::enums::SimpleEnum getCategory() const { return category_; }
    void setCategory(const examples::enums::SimpleEnum& value) { category_ = value; }
    examples::blocks::BlockStatus getBlockStatus() const { return blockStatus_; }
    void setBlockStatus(const examples::blocks::BlockStatus& value) { blockStatus_ = value; }
private:
    double score_ = 0.000000;
    examples::enums::SimpleEnum category_ = /* complex expression */;
    examples::blocks::BlockStatus blockStatus_ = /* complex expression */;
};
Q_DECLARE_METATYPE(InheritedCrossBlockBlock)

// AdvancedCrossBlock块定义
class MODEL_EXPORT AdvancedCrossBlockBlock : public examples::blocks::ExtendedBlockBlock, public IBlock {
public:
    AdvancedCrossBlockBlock() = default;
    
    // 实现 IBlock 接口
    QCborMap toCbor() const override {
        QCborMap map = examples::blocks::ExtendedBlockBlock::toCbor();
                map.insert(QLatin1String("advancedField"), advancedField_.toCbor());
        QCborArray valueEnumArrayArray;
        for (const auto& item : valueEnumArray_) {
            valueEnumArrayArray.append(item.toCbor());
        }
        map.insert(QLatin1String("valueEnumArray"), valueEnumArrayArray);
                if (optionalAnnotatedBlock_) {
            map.insert(QLatin1String("optionalAnnotatedBlock"), optionalAnnotatedBlock_->toCbor());
        }
        QCborMap enumMapMap;
        for (auto it = enumMap_.cbegin(); it != enumMap_.cend(); ++it) {
            enumMapMap.insert(it.key(), it.value().toCbor());
        }
        map.insert(QLatin1String("enumMap"), enumMapMap);
        return map;
    }
    
    void fromCbor(const QCborMap& map) override {
        examples::blocks::ExtendedBlockBlock::fromCbor(map);
        QCborValue tmpValue;
        tmpValue = map.value(QLatin1String("advancedField"));
        if (!tmpValue.isNull()) {
            advancedField_ = tmpValue.toString();advancedField_.fromCbor(tmpValue.toMap());
        }
        tmpValue = map.value(QLatin1String("valueEnumArray"));
        if (tmpValue.isArray()) {
            QCborArray valueEnumArrayArray = tmpValue.toArray();
            QVector<examples::enums::ValueEnum> valueEnumArrayList;
            for (const auto& item : valueEnumArrayArray) {
                examples::enums::ValueEnum itemValue;
                itemValue.fromCbor(item.toMap());
                valueEnumArrayList.append(itemValue);
            }
            valueEnumArray_ = valueEnumArrayList;
        }
        tmpValue = map.value(QLatin1String("optionalAnnotatedBlock"));
        if (!tmpValue.isNull()) {
            examples::blocks::AnnotatedBlockBlock itemValue;
            itemValue.fromCbor(tmpValue.toMap());
            optionalAnnotatedBlock_ = itemValue;
        }
        tmpValue = map.value(QLatin1String("enumMap"));
        if (tmpValue.isMap()) {
            QCborMap enumMapMap = tmpValue.toMap();
            QMap<QString, examples::enums::SimpleEnum> enumMapResult;
            for (auto it = enumMapMap.cbegin(); it != enumMapMap.cend(); ++it) {
                examples::enums::SimpleEnum itemValue;
                itemValue.fromCbor(it.value().toMap());
                enumMapResult.insert(it.key().toString(), itemValue);
            }
            enumMap_ = enumMapResult;
        }
    }
    
    QString name() const override {
        return QLatin1String("AdvancedCrossBlock");
    }
    
    QStringList fields() const override {
        return QStringList{QLatin1String("advancedField"), QLatin1String("valueEnumArray"), QLatin1String("optionalAnnotatedBlock"), QLatin1String("enumMap")};
    }
    
    QString fieldType(const QString& fieldName) const override {
        if (fieldName == QLatin1String("advancedField")) return QLatin1String("string");
        if (fieldName == QLatin1String("valueEnumArray")) return QLatin1String("examples.enums.ValueEnum");
        if (fieldName == QLatin1String("optionalAnnotatedBlock")) return QLatin1String("examples.blocks.AnnotatedBlock");
        if (fieldName == QLatin1String("enumMap")) return QLatin1String("examples.enums.SimpleEnum");
        return QString();
    }
    
    QString fieldContainerType(const QString& fieldName) const override {
        if (fieldName == QLatin1String("advancedField")) return QLatin1String("none");
        if (fieldName == QLatin1String("valueEnumArray")) return QLatin1String("array");
        if (fieldName == QLatin1String("optionalAnnotatedBlock")) return QLatin1String("optional");
        if (fieldName == QLatin1String("enumMap")) return QLatin1String("map");
        return QLatin1String("none");
    }
    
    QList<QSharedPointer<IAnnotation>> annotations() const override {
        QList<QSharedPointer<IAnnotation>> result;
        return result;
    }
    
    QList<QSharedPointer<IAnnotation>> fieldAnnotation(const QString& fieldName) const override {
        if (fieldName == QLatin1String("advancedField")) {
            QList<QSharedPointer<IAnnotation>> result;
            return result;
        }
        if (fieldName == QLatin1String("valueEnumArray")) {
            QList<QSharedPointer<IAnnotation>> result;
            return result;
        }
        if (fieldName == QLatin1String("optionalAnnotatedBlock")) {
            QList<QSharedPointer<IAnnotation>> result;
            return result;
        }
        if (fieldName == QLatin1String("enumMap")) {
            QList<QSharedPointer<IAnnotation>> result;
            return result;
        }
        return QList<QSharedPointer<IAnnotation>>();
    }
    
    QString description() const override {
        return QLatin1String("AdvancedCrossBlock");
    }
    
    QString fieldDescription(const QString& fieldName) const override {
        if (fieldName == QLatin1String("advancedField")) return QLatin1String("advancedField");
        if (fieldName == QLatin1String("valueEnumArray")) return QLatin1String("valueEnumArray");
        if (fieldName == QLatin1String("optionalAnnotatedBlock")) return QLatin1String("optionalAnnotatedBlock");
        if (fieldName == QLatin1String("enumMap")) return QLatin1String("enumMap");
        return QString();
    }
    
    QVariant value(const QString& fieldName) const override {
        if (fieldName == QLatin1String("advancedField")) return QVariant::fromValue(advancedField_);
        if (fieldName == QLatin1String("valueEnumArray")) return QVariant::fromValue(valueEnumArray_);
        if (fieldName == QLatin1String("optionalAnnotatedBlock")) return QVariant::fromValue(optionalAnnotatedBlock_);
        if (fieldName == QLatin1String("enumMap")) return QVariant::fromValue(enumMap_);
        return QVariant();
    }
    
    void value(const QString& fieldName, const QVariant& value) override {
        if (fieldName == QLatin1String("advancedField")) {
            advancedField_ = value.value<QString>();
            return;
        }
        if (fieldName == QLatin1String("valueEnumArray")) {
            valueEnumArray_ = value.value<QVector<examples::enums::ValueEnum>>();
            return;
        }
        if (fieldName == QLatin1String("optionalAnnotatedBlock")) {
            optionalAnnotatedBlock_ = value.value<std::optional<examples::blocks::AnnotatedBlockBlock>>();
            return;
        }
        if (fieldName == QLatin1String("enumMap")) {
            enumMap_ = value.value<QMap<QString, examples::enums::SimpleEnum>>();
            return;
        }
    }
    
    // 字段访问器
    QString getAdvancedField() const { return advancedField_; }
    void setAdvancedField(const QString& value) { advancedField_ = value; }
    QVector<examples::enums::ValueEnum> getValueEnumArray() const { return valueEnumArray_; }
    void setValueEnumArray(const QVector<examples::enums::ValueEnum>& value) { valueEnumArray_ = value; }
    std::optional<examples::blocks::AnnotatedBlockBlock> getOptionalAnnotatedBlock() const { return optionalAnnotatedBlock_; }
    void setOptionalAnnotatedBlock(const std::optional<examples::blocks::AnnotatedBlockBlock>& value) { optionalAnnotatedBlock_ = value; }
    QMap<QString, examples::enums::SimpleEnum> getEnumMap() const { return enumMap_; }
    void setEnumMap(const QMap<QString, examples::enums::SimpleEnum>& value) { enumMap_ = value; }
private:
    QString advancedField_ = "";
    QVector<examples::enums::ValueEnum> valueEnumArray_;
    std::optional<examples::blocks::AnnotatedBlockBlock> optionalAnnotatedBlock_;
    QMap<QString, examples::enums::SimpleEnum> enumMap_;
};
Q_DECLARE_METATYPE(AdvancedCrossBlockBlock)

    // CrossStruct结构体
    class MODEL_EXPORT CrossStructModel : public IModel {
    public:
        CrossStructModel() = default;
        
        // 实现 IModel 接口
        QCborMap toCbor() const override {
            QCborMap map;
                    map.insert(QLatin1String("name"), name_.toCbor());
                    map.insert(QLatin1String("enumField"), enumField_.toCbor());
                    map.insert(QLatin1String("valueEnumField"), valueEnumField_.toCbor());
                    map.insert(QLatin1String("baseBlock"), baseBlock_.toCbor());
                    map.insert(QLatin1String("extendedBlock"), extendedBlock_.toCbor());
                    map.insert(QLatin1String("annotatedBlock"), annotatedBlock_.toCbor());
                    map.insert(QLatin1String("crossEnum"), crossEnum_.toCbor());
                    map.insert(QLatin1String("crossBlock"), crossBlock_.toCbor());
            return map;
        }
        
        void fromCbor(const QCborMap& map) override {
            QCborValue tmpValue;
            tmpValue = map.value(QLatin1String("name"));
            if (!tmpValue.isNull()) {
                name_ = tmpValue.toString();name_.fromCbor(tmpValue.toMap());
            }
            tmpValue = map.value(QLatin1String("enumField"));
            if (!tmpValue.isNull()) {
                enumField_.fromCbor(tmpValue.toMap());
            }
            tmpValue = map.value(QLatin1String("valueEnumField"));
            if (!tmpValue.isNull()) {
                valueEnumField_.fromCbor(tmpValue.toMap());
            }
            tmpValue = map.value(QLatin1String("baseBlock"));
            if (!tmpValue.isNull()) {
                baseBlock_.fromCbor(tmpValue.toMap());
            }
            tmpValue = map.value(QLatin1String("extendedBlock"));
            if (!tmpValue.isNull()) {
                extendedBlock_.fromCbor(tmpValue.toMap());
            }
            tmpValue = map.value(QLatin1String("annotatedBlock"));
            if (!tmpValue.isNull()) {
                annotatedBlock_.fromCbor(tmpValue.toMap());
            }
            tmpValue = map.value(QLatin1String("crossEnum"));
            if (!tmpValue.isNull()) {
                crossEnum_.fromCbor(tmpValue.toMap());
            }
            tmpValue = map.value(QLatin1String("crossBlock"));
            if (!tmpValue.isNull()) {
                crossBlock_.fromCbor(tmpValue.toMap());
            }
        }
        
        QString name() const override {
            return QLatin1String("CrossStruct");
        }
        
        QStringList fields() const override {
            return QStringList{QLatin1String("name"), QLatin1String("enumField"), QLatin1String("valueEnumField"), QLatin1String("baseBlock"), QLatin1String("extendedBlock"), QLatin1String("annotatedBlock"), QLatin1String("crossEnum"), QLatin1String("crossBlock")};
        }
        
        QString fieldType(const QString& fieldName) const override {
            if (fieldName == QLatin1String("name")) return QLatin1String("string");
            if (fieldName == QLatin1String("enumField")) return QLatin1String("examples.enums.SimpleEnum");
            if (fieldName == QLatin1String("valueEnumField")) return QLatin1String("examples.enums.ValueEnum");
            if (fieldName == QLatin1String("baseBlock")) return QLatin1String("examples.blocks.BaseBlock");
            if (fieldName == QLatin1String("extendedBlock")) return QLatin1String("examples.blocks.ExtendedBlock");
            if (fieldName == QLatin1String("annotatedBlock")) return QLatin1String("examples.blocks.AnnotatedBlock");
            if (fieldName == QLatin1String("crossEnum")) return QLatin1String("CrossEnum");
            if (fieldName == QLatin1String("crossBlock")) return QLatin1String("CrossBlock");
            return QString();
        }
        
        QString fieldContainerType(const QString& fieldName) const override {
            if (fieldName == QLatin1String("name")) return QLatin1String("none");
            if (fieldName == QLatin1String("enumField")) return QLatin1String("none");
            if (fieldName == QLatin1String("valueEnumField")) return QLatin1String("none");
            if (fieldName == QLatin1String("baseBlock")) return QLatin1String("none");
            if (fieldName == QLatin1String("extendedBlock")) return QLatin1String("none");
            if (fieldName == QLatin1String("annotatedBlock")) return QLatin1String("none");
            if (fieldName == QLatin1String("crossEnum")) return QLatin1String("none");
            if (fieldName == QLatin1String("crossBlock")) return QLatin1String("none");
            return QLatin1String("none");
        }
    
        // 字段访问器
        QString getName() const { return name_; }
        void setName(const QString& value) { name_ = value; }
    examples::enums::SimpleEnum getEnumField() const { return enumField_; }
        void setEnumField(const examples::enums::SimpleEnum& value) { enumField_ = value; }
    examples::enums::ValueEnum getValueEnumField() const { return valueEnumField_; }
        void setValueEnumField(const examples::enums::ValueEnum& value) { valueEnumField_ = value; }
    examples::blocks::BaseBlockBlock getBaseBlock() const { return baseBlock_; }
        void setBaseBlock(const examples::blocks::BaseBlockBlock& value) { baseBlock_ = value; }
    examples::blocks::ExtendedBlockBlock getExtendedBlock() const { return extendedBlock_; }
        void setExtendedBlock(const examples::blocks::ExtendedBlockBlock& value) { extendedBlock_ = value; }
    examples::blocks::AnnotatedBlockBlock getAnnotatedBlock() const { return annotatedBlock_; }
        void setAnnotatedBlock(const examples::blocks::AnnotatedBlockBlock& value) { annotatedBlock_ = value; }
    CrossEnum getCrossEnum() const { return crossEnum_; }
        void setCrossEnum(const CrossEnum& value) { crossEnum_ = value; }
    CrossBlockBlock getCrossBlock() const { return crossBlock_; }
        void setCrossBlock(const CrossBlockBlock& value) { crossBlock_ = value; }
    private:
        QString name_ = "";
        examples::enums::SimpleEnum enumField_ = /* complex expression */;
        examples::enums::ValueEnum valueEnumField_ = /* complex expression */;
        examples::blocks::BaseBlockBlock baseBlock_;
        examples::blocks::ExtendedBlockBlock extendedBlock_;
        examples::blocks::AnnotatedBlockBlock annotatedBlock_;
        CrossEnum crossEnum_ = /* complex expression */;
        CrossBlockBlock crossBlock_;
    };
    Q_DECLARE_METATYPE(CrossStructModel)
    
        // InheritedCrossStruct结构体
    class MODEL_EXPORT InheritedCrossStructModel : public examples::structs::StructBaseBlockModel, public IModel {
    public:
        InheritedCrossStructModel() = default;
        
        // 实现 IModel 接口
        QCborMap toCbor() const override {
            QCborMap map = examples::structs::StructBaseBlockModel::toCbor();
                    map.insert(QLatin1String("description"), description_.toCbor());
                    map.insert(QLatin1String("enumField"), enumField_.toCbor());
                    map.insert(QLatin1String("blockField"), blockField_.toCbor());
                    map.insert(QLatin1String("structStatus"), structStatus_.toCbor());
            QCborArray valueEnumArrayArray;
            for (const auto& item : valueEnumArray_) {
                valueEnumArrayArray.append(item.toCbor());
            }
            map.insert(QLatin1String("valueEnumArray"), valueEnumArrayArray);
                    if (optionalBlock_) {
                map.insert(QLatin1String("optionalBlock"), optionalBlock_->toCbor());
            }
            QCborMap categoryMapMap;
            for (auto it = categoryMap_.cbegin(); it != categoryMap_.cend(); ++it) {
                categoryMapMap.insert(it.key(), it.value().toCbor());
            }
            map.insert(QLatin1String("categoryMap"), categoryMapMap);
            return map;
        }
        
        void fromCbor(const QCborMap& map) override {
            examples::structs::StructBaseBlockModel::fromCbor(map);
            QCborValue tmpValue;
            tmpValue = map.value(QLatin1String("description"));
            if (!tmpValue.isNull()) {
                description_ = tmpValue.toString();description_.fromCbor(tmpValue.toMap());
            }
            tmpValue = map.value(QLatin1String("enumField"));
            if (!tmpValue.isNull()) {
                enumField_.fromCbor(tmpValue.toMap());
            }
            tmpValue = map.value(QLatin1String("blockField"));
            if (!tmpValue.isNull()) {
                blockField_.fromCbor(tmpValue.toMap());
            }
            tmpValue = map.value(QLatin1String("structStatus"));
            if (!tmpValue.isNull()) {
                structStatus_.fromCbor(tmpValue.toMap());
            }
            tmpValue = map.value(QLatin1String("valueEnumArray"));
            if (tmpValue.isArray()) {
                QCborArray valueEnumArrayArray = tmpValue.toArray();
                QVector<examples::enums::ValueEnum> valueEnumArrayList;
                for (const auto& item : valueEnumArrayArray) {
                    examples::enums::ValueEnum itemValue;
                    itemValue.fromCbor(item.toMap());
                    valueEnumArrayList.append(itemValue);
                }
                valueEnumArray_ = valueEnumArrayList;
            }
            tmpValue = map.value(QLatin1String("optionalBlock"));
            if (!tmpValue.isNull()) {
                            examples::blocks::ExtendedBlockBlock itemValue;
            itemValue.fromCbor(tmpValue.toMap());
            optionalBlock_ = itemValue;
            }
            tmpValue = map.value(QLatin1String("categoryMap"));
            if (tmpValue.isMap()) {
                QCborMap categoryMapMap = tmpValue.toMap();
                QMap<QString, examples::structs::StructCategory> categoryMapResult;
                for (auto it = categoryMapMap.cbegin(); it != categoryMapMap.cend(); ++it) {
                    examples::structs::StructCategory itemValue;
                    itemValue.fromCbor(it.value().toMap());
                    categoryMapResult.insert(it.key().toString(), itemValue);
                }
                categoryMap_ = categoryMapResult;
            }
        }
        
        QString name() const override {
            return QLatin1String("InheritedCrossStruct");
        }
        
        QStringList fields() const override {
            return QStringList{QLatin1String("description"), QLatin1String("enumField"), QLatin1String("blockField"), QLatin1String("structStatus"), QLatin1String("valueEnumArray"), QLatin1String("optionalBlock"), QLatin1String("categoryMap")};
        }
        
        QString fieldType(const QString& fieldName) const override {
            if (fieldName == QLatin1String("description")) return QLatin1String("string");
            if (fieldName == QLatin1String("enumField")) return QLatin1String("examples.enums.SimpleEnum");
            if (fieldName == QLatin1String("blockField")) return QLatin1String("examples.blocks.BaseBlock");
            if (fieldName == QLatin1String("structStatus")) return QLatin1String("examples.structs.StructStatus");
            if (fieldName == QLatin1String("valueEnumArray")) return QLatin1String("examples.enums.ValueEnum");
            if (fieldName == QLatin1String("optionalBlock")) return QLatin1String("examples.blocks.ExtendedBlock");
            if (fieldName == QLatin1String("categoryMap")) return QLatin1String("examples.structs.StructCategory");
            return QString();
        }
        
        QString fieldContainerType(const QString& fieldName) const override {
            if (fieldName == QLatin1String("description")) return QLatin1String("none");
            if (fieldName == QLatin1String("enumField")) return QLatin1String("none");
            if (fieldName == QLatin1String("blockField")) return QLatin1String("none");
            if (fieldName == QLatin1String("structStatus")) return QLatin1String("none");
            if (fieldName == QLatin1String("valueEnumArray")) return QLatin1String("array");
            if (fieldName == QLatin1String("optionalBlock")) return QLatin1String("optional");
            if (fieldName == QLatin1String("categoryMap")) return QLatin1String("map");
            return QLatin1String("none");
        }
    
        // 字段访问器
        QString getDescription() const { return description_; }
        void setDescription(const QString& value) { description_ = value; }
    examples::enums::SimpleEnum getEnumField() const { return enumField_; }
        void setEnumField(const examples::enums::SimpleEnum& value) { enumField_ = value; }
    examples::blocks::BaseBlockBlock getBlockField() const { return blockField_; }
        void setBlockField(const examples::blocks::BaseBlockBlock& value) { blockField_ = value; }
    examples::structs::StructStatus getStructStatus() const { return structStatus_; }
        void setStructStatus(const examples::structs::StructStatus& value) { structStatus_ = value; }
    QVector<examples::enums::ValueEnum> getValueEnumArray() const { return valueEnumArray_; }
        void setValueEnumArray(const QVector<examples::enums::ValueEnum>& value) { valueEnumArray_ = value; }
    std::optional<examples::blocks::ExtendedBlockBlock> getOptionalBlock() const { return optionalBlock_; }
        void setOptionalBlock(const std::optional<examples::blocks::ExtendedBlockBlock>& value) { optionalBlock_ = value; }
    QMap<QString, examples::structs::StructCategory> getCategoryMap() const { return categoryMap_; }
        void setCategoryMap(const QMap<QString, examples::structs::StructCategory>& value) { categoryMap_ = value; }
    private:
        QString description_ = "";
        examples::enums::SimpleEnum enumField_ = /* complex expression */;
        examples::blocks::BaseBlockBlock blockField_;
        examples::structs::StructStatus structStatus_ = /* complex expression */;
        QVector<examples::enums::ValueEnum> valueEnumArray_ = [
    "/* complex expression */",
    "/* complex expression */"
];
        std::optional<examples::blocks::ExtendedBlockBlock> optionalBlock_;
        QMap<QString, examples::structs::StructCategory> categoryMap_;
    };
    Q_DECLARE_METATYPE(InheritedCrossStructModel)
    
        // UltimateCrossTest结构体
    class MODEL_EXPORT UltimateCrossTestModel : public examples::blocks::AllTypesBlockModel, public IModel {
    public:
        UltimateCrossTestModel() = default;
        
        // 实现 IModel 接口
        QCborMap toCbor() const override {
            QCborMap map = examples::blocks::AllTypesBlockModel::toCbor();
                    map.insert(QLatin1String("simpleEnum"), simpleEnum_.toCbor());
                    map.insert(QLatin1String("valueEnum"), valueEnum_.toCbor());
                    map.insert(QLatin1String("baseBlock"), baseBlock_.toCbor());
                    map.insert(QLatin1String("extendedBlock"), extendedBlock_.toCbor());
                    map.insert(QLatin1String("annotatedBlock"), annotatedBlock_.toCbor());
                    map.insert(QLatin1String("containerBlock"), containerBlock_.toCbor());
                    map.insert(QLatin1String("structBaseBlock"), structBaseBlock_.toCbor());
                    map.insert(QLatin1String("structExtendedBlock"), structExtendedBlock_.toCbor());
                    map.insert(QLatin1String("crossEnum"), crossEnum_.toCbor());
                    map.insert(QLatin1String("crossBlock"), crossBlock_.toCbor());
                    map.insert(QLatin1String("inheritedCrossBlock"), inheritedCrossBlock_.toCbor());
            QCborArray enumArrayArray;
            for (const auto& item : enumArray_) {
                enumArrayArray.append(item.toCbor());
            }
            map.insert(QLatin1String("enumArray"), enumArrayArray);
            QCborArray blockArrayArray;
            for (const auto& item : blockArray_) {
                blockArrayArray.append(item.toCbor());
            }
            map.insert(QLatin1String("blockArray"), blockArrayArray);
            QCborArray statusArrayArray;
            for (const auto& item : statusArray_) {
                statusArrayArray.append(item.toCbor());
            }
            map.insert(QLatin1String("statusArray"), statusArrayArray);
                    if (optionalEnum_) {
                map.insert(QLatin1String("optionalEnum"), optionalEnum_->toCbor());
            }
                    if (optionalBlock_) {
                map.insert(QLatin1String("optionalBlock"), optionalBlock_->toCbor());
            }
                    if (optionalCategory_) {
                map.insert(QLatin1String("optionalCategory"), optionalCategory_->toCbor());
            }
            QCborMap enumMapMap;
            for (auto it = enumMap_.cbegin(); it != enumMap_.cend(); ++it) {
                enumMapMap.insert(it.key(), it.value().toCbor());
            }
            map.insert(QLatin1String("enumMap"), enumMapMap);
            QCborMap blockMapMap;
            for (auto it = blockMap_.cbegin(); it != blockMap_.cend(); ++it) {
                blockMapMap.insert(it.key(), it.value().toCbor());
            }
            map.insert(QLatin1String("blockMap"), blockMapMap);
            QCborMap structBlockMapMap;
            for (auto it = structBlockMap_.cbegin(); it != structBlockMap_.cend(); ++it) {
                structBlockMapMap.insert(it.key(), it.value().toCbor());
            }
            map.insert(QLatin1String("structBlockMap"), structBlockMapMap);
            return map;
        }
        
        void fromCbor(const QCborMap& map) override {
            examples::blocks::AllTypesBlockModel::fromCbor(map);
            QCborValue tmpValue;
            tmpValue = map.value(QLatin1String("simpleEnum"));
            if (!tmpValue.isNull()) {
                simpleEnum_.fromCbor(tmpValue.toMap());
            }
            tmpValue = map.value(QLatin1String("valueEnum"));
            if (!tmpValue.isNull()) {
                valueEnum_.fromCbor(tmpValue.toMap());
            }
            tmpValue = map.value(QLatin1String("baseBlock"));
            if (!tmpValue.isNull()) {
                baseBlock_.fromCbor(tmpValue.toMap());
            }
            tmpValue = map.value(QLatin1String("extendedBlock"));
            if (!tmpValue.isNull()) {
                extendedBlock_.fromCbor(tmpValue.toMap());
            }
            tmpValue = map.value(QLatin1String("annotatedBlock"));
            if (!tmpValue.isNull()) {
                annotatedBlock_.fromCbor(tmpValue.toMap());
            }
            tmpValue = map.value(QLatin1String("containerBlock"));
            if (!tmpValue.isNull()) {
                containerBlock_.fromCbor(tmpValue.toMap());
            }
            tmpValue = map.value(QLatin1String("structBaseBlock"));
            if (!tmpValue.isNull()) {
                structBaseBlock_.fromCbor(tmpValue.toMap());
            }
            tmpValue = map.value(QLatin1String("structExtendedBlock"));
            if (!tmpValue.isNull()) {
                structExtendedBlock_.fromCbor(tmpValue.toMap());
            }
            tmpValue = map.value(QLatin1String("crossEnum"));
            if (!tmpValue.isNull()) {
                crossEnum_.fromCbor(tmpValue.toMap());
            }
            tmpValue = map.value(QLatin1String("crossBlock"));
            if (!tmpValue.isNull()) {
                crossBlock_.fromCbor(tmpValue.toMap());
            }
            tmpValue = map.value(QLatin1String("inheritedCrossBlock"));
            if (!tmpValue.isNull()) {
                inheritedCrossBlock_.fromCbor(tmpValue.toMap());
            }
            tmpValue = map.value(QLatin1String("enumArray"));
            if (tmpValue.isArray()) {
                QCborArray enumArrayArray = tmpValue.toArray();
                QVector<examples::enums::SimpleEnum> enumArrayList;
                for (const auto& item : enumArrayArray) {
                    examples::enums::SimpleEnum itemValue;
                    itemValue.fromCbor(item.toMap());
                    enumArrayList.append(itemValue);
                }
                enumArray_ = enumArrayList;
            }
            tmpValue = map.value(QLatin1String("blockArray"));
            if (tmpValue.isArray()) {
                QCborArray blockArrayArray = tmpValue.toArray();
                QVector<examples::blocks::BaseBlockBlock> blockArrayList;
                for (const auto& item : blockArrayArray) {
                    examples::blocks::BaseBlockBlock itemValue;
                    itemValue.fromCbor(item.toMap());
                    blockArrayList.append(itemValue);
                }
                blockArray_ = blockArrayList;
            }
            tmpValue = map.value(QLatin1String("statusArray"));
            if (tmpValue.isArray()) {
                QCborArray statusArrayArray = tmpValue.toArray();
                QVector<examples::structs::StructStatus> statusArrayList;
                for (const auto& item : statusArrayArray) {
                    examples::structs::StructStatus itemValue;
                    itemValue.fromCbor(item.toMap());
                    statusArrayList.append(itemValue);
                }
                statusArray_ = statusArrayList;
            }
            tmpValue = map.value(QLatin1String("optionalEnum"));
            if (!tmpValue.isNull()) {
                            examples::enums::ValueEnum itemValue;
            itemValue.fromCbor(tmpValue.toMap());
            optionalEnum_ = itemValue;
            }
            tmpValue = map.value(QLatin1String("optionalBlock"));
            if (!tmpValue.isNull()) {
                            examples::blocks::AnnotatedBlockBlock itemValue;
            itemValue.fromCbor(tmpValue.toMap());
            optionalBlock_ = itemValue;
            }
            tmpValue = map.value(QLatin1String("optionalCategory"));
            if (!tmpValue.isNull()) {
                            examples::structs::StructCategory itemValue;
            itemValue.fromCbor(tmpValue.toMap());
            optionalCategory_ = itemValue;
            }
            tmpValue = map.value(QLatin1String("enumMap"));
            if (tmpValue.isMap()) {
                QCborMap enumMapMap = tmpValue.toMap();
                QMap<QString, examples::enums::SimpleEnum> enumMapResult;
                for (auto it = enumMapMap.cbegin(); it != enumMapMap.cend(); ++it) {
                    examples::enums::SimpleEnum itemValue;
                    itemValue.fromCbor(it.value().toMap());
                    enumMapResult.insert(it.key().toString(), itemValue);
                }
                enumMap_ = enumMapResult;
            }
            tmpValue = map.value(QLatin1String("blockMap"));
            if (tmpValue.isMap()) {
                QCborMap blockMapMap = tmpValue.toMap();
                QMap<QString, examples::blocks::BaseBlockBlock> blockMapResult;
                for (auto it = blockMapMap.cbegin(); it != blockMapMap.cend(); ++it) {
                    examples::blocks::BaseBlockBlock itemValue;
                    itemValue.fromCbor(it.value().toMap());
                    blockMapResult.insert(it.key().toString(), itemValue);
                }
                blockMap_ = blockMapResult;
            }
            tmpValue = map.value(QLatin1String("structBlockMap"));
            if (tmpValue.isMap()) {
                QCborMap structBlockMapMap = tmpValue.toMap();
                QMap<QString, examples::structs::StructBaseBlockBlock> structBlockMapResult;
                for (auto it = structBlockMapMap.cbegin(); it != structBlockMapMap.cend(); ++it) {
                    examples::structs::StructBaseBlockBlock itemValue;
                    itemValue.fromCbor(it.value().toMap());
                    structBlockMapResult.insert(it.key().toString(), itemValue);
                }
                structBlockMap_ = structBlockMapResult;
            }
        }
        
        QString name() const override {
            return QLatin1String("UltimateCrossTest");
        }
        
        QStringList fields() const override {
            return QStringList{QLatin1String("simpleEnum"), QLatin1String("valueEnum"), QLatin1String("baseBlock"), QLatin1String("extendedBlock"), QLatin1String("annotatedBlock"), QLatin1String("containerBlock"), QLatin1String("structBaseBlock"), QLatin1String("structExtendedBlock"), QLatin1String("crossEnum"), QLatin1String("crossBlock"), QLatin1String("inheritedCrossBlock"), QLatin1String("enumArray"), QLatin1String("blockArray"), QLatin1String("statusArray"), QLatin1String("optionalEnum"), QLatin1String("optionalBlock"), QLatin1String("optionalCategory"), QLatin1String("enumMap"), QLatin1String("blockMap"), QLatin1String("structBlockMap")};
        }
        
        QString fieldType(const QString& fieldName) const override {
            if (fieldName == QLatin1String("simpleEnum")) return QLatin1String("examples.enums.SimpleEnum");
            if (fieldName == QLatin1String("valueEnum")) return QLatin1String("examples.enums.ValueEnum");
            if (fieldName == QLatin1String("baseBlock")) return QLatin1String("examples.blocks.BaseBlock");
            if (fieldName == QLatin1String("extendedBlock")) return QLatin1String("examples.blocks.ExtendedBlock");
            if (fieldName == QLatin1String("annotatedBlock")) return QLatin1String("examples.blocks.AnnotatedBlock");
            if (fieldName == QLatin1String("containerBlock")) return QLatin1String("examples.blocks.ContainerBlock");
            if (fieldName == QLatin1String("structBaseBlock")) return QLatin1String("examples.structs.StructBaseBlock");
            if (fieldName == QLatin1String("structExtendedBlock")) return QLatin1String("examples.structs.StructExtendedBlock");
            if (fieldName == QLatin1String("crossEnum")) return QLatin1String("CrossEnum");
            if (fieldName == QLatin1String("crossBlock")) return QLatin1String("CrossBlock");
            if (fieldName == QLatin1String("inheritedCrossBlock")) return QLatin1String("InheritedCrossBlock");
            if (fieldName == QLatin1String("enumArray")) return QLatin1String("examples.enums.SimpleEnum");
            if (fieldName == QLatin1String("blockArray")) return QLatin1String("examples.blocks.BaseBlock");
            if (fieldName == QLatin1String("statusArray")) return QLatin1String("examples.structs.StructStatus");
            if (fieldName == QLatin1String("optionalEnum")) return QLatin1String("examples.enums.ValueEnum");
            if (fieldName == QLatin1String("optionalBlock")) return QLatin1String("examples.blocks.AnnotatedBlock");
            if (fieldName == QLatin1String("optionalCategory")) return QLatin1String("examples.structs.StructCategory");
            if (fieldName == QLatin1String("enumMap")) return QLatin1String("examples.enums.SimpleEnum");
            if (fieldName == QLatin1String("blockMap")) return QLatin1String("examples.blocks.BaseBlock");
            if (fieldName == QLatin1String("structBlockMap")) return QLatin1String("examples.structs.StructBaseBlock");
            return QString();
        }
        
        QString fieldContainerType(const QString& fieldName) const override {
            if (fieldName == QLatin1String("simpleEnum")) return QLatin1String("none");
            if (fieldName == QLatin1String("valueEnum")) return QLatin1String("none");
            if (fieldName == QLatin1String("baseBlock")) return QLatin1String("none");
            if (fieldName == QLatin1String("extendedBlock")) return QLatin1String("none");
            if (fieldName == QLatin1String("annotatedBlock")) return QLatin1String("none");
            if (fieldName == QLatin1String("containerBlock")) return QLatin1String("none");
            if (fieldName == QLatin1String("structBaseBlock")) return QLatin1String("none");
            if (fieldName == QLatin1String("structExtendedBlock")) return QLatin1String("none");
            if (fieldName == QLatin1String("crossEnum")) return QLatin1String("none");
            if (fieldName == QLatin1String("crossBlock")) return QLatin1String("none");
            if (fieldName == QLatin1String("inheritedCrossBlock")) return QLatin1String("none");
            if (fieldName == QLatin1String("enumArray")) return QLatin1String("array");
            if (fieldName == QLatin1String("blockArray")) return QLatin1String("array");
            if (fieldName == QLatin1String("statusArray")) return QLatin1String("array");
            if (fieldName == QLatin1String("optionalEnum")) return QLatin1String("optional");
            if (fieldName == QLatin1String("optionalBlock")) return QLatin1String("optional");
            if (fieldName == QLatin1String("optionalCategory")) return QLatin1String("optional");
            if (fieldName == QLatin1String("enumMap")) return QLatin1String("map");
            if (fieldName == QLatin1String("blockMap")) return QLatin1String("map");
            if (fieldName == QLatin1String("structBlockMap")) return QLatin1String("map");
            return QLatin1String("none");
        }
    
        // 字段访问器
        examples::enums::SimpleEnum getSimpleEnum() const { return simpleEnum_; }
        void setSimpleEnum(const examples::enums::SimpleEnum& value) { simpleEnum_ = value; }
    examples::enums::ValueEnum getValueEnum() const { return valueEnum_; }
        void setValueEnum(const examples::enums::ValueEnum& value) { valueEnum_ = value; }
    examples::blocks::BaseBlockBlock getBaseBlock() const { return baseBlock_; }
        void setBaseBlock(const examples::blocks::BaseBlockBlock& value) { baseBlock_ = value; }
    examples::blocks::ExtendedBlockBlock getExtendedBlock() const { return extendedBlock_; }
        void setExtendedBlock(const examples::blocks::ExtendedBlockBlock& value) { extendedBlock_ = value; }
    examples::blocks::AnnotatedBlockBlock getAnnotatedBlock() const { return annotatedBlock_; }
        void setAnnotatedBlock(const examples::blocks::AnnotatedBlockBlock& value) { annotatedBlock_ = value; }
    examples::blocks::ContainerBlockBlock getContainerBlock() const { return containerBlock_; }
        void setContainerBlock(const examples::blocks::ContainerBlockBlock& value) { containerBlock_ = value; }
    examples::structs::StructBaseBlockBlock getStructBaseBlock() const { return structBaseBlock_; }
        void setStructBaseBlock(const examples::structs::StructBaseBlockBlock& value) { structBaseBlock_ = value; }
    examples::structs::StructExtendedBlockBlock getStructExtendedBlock() const { return structExtendedBlock_; }
        void setStructExtendedBlock(const examples::structs::StructExtendedBlockBlock& value) { structExtendedBlock_ = value; }
    CrossEnum getCrossEnum() const { return crossEnum_; }
        void setCrossEnum(const CrossEnum& value) { crossEnum_ = value; }
    CrossBlockBlock getCrossBlock() const { return crossBlock_; }
        void setCrossBlock(const CrossBlockBlock& value) { crossBlock_ = value; }
    InheritedCrossBlockBlock getInheritedCrossBlock() const { return inheritedCrossBlock_; }
        void setInheritedCrossBlock(const InheritedCrossBlockBlock& value) { inheritedCrossBlock_ = value; }
    QVector<examples::enums::SimpleEnum> getEnumArray() const { return enumArray_; }
        void setEnumArray(const QVector<examples::enums::SimpleEnum>& value) { enumArray_ = value; }
    QVector<examples::blocks::BaseBlockBlock> getBlockArray() const { return blockArray_; }
        void setBlockArray(const QVector<examples::blocks::BaseBlockBlock>& value) { blockArray_ = value; }
    QVector<examples::structs::StructStatus> getStatusArray() const { return statusArray_; }
        void setStatusArray(const QVector<examples::structs::StructStatus>& value) { statusArray_ = value; }
    std::optional<examples::enums::ValueEnum> getOptionalEnum() const { return optionalEnum_; }
        void setOptionalEnum(const std::optional<examples::enums::ValueEnum>& value) { optionalEnum_ = value; }
    std::optional<examples::blocks::AnnotatedBlockBlock> getOptionalBlock() const { return optionalBlock_; }
        void setOptionalBlock(const std::optional<examples::blocks::AnnotatedBlockBlock>& value) { optionalBlock_ = value; }
    std::optional<examples::structs::StructCategory> getOptionalCategory() const { return optionalCategory_; }
        void setOptionalCategory(const std::optional<examples::structs::StructCategory>& value) { optionalCategory_ = value; }
    QMap<QString, examples::enums::SimpleEnum> getEnumMap() const { return enumMap_; }
        void setEnumMap(const QMap<QString, examples::enums::SimpleEnum>& value) { enumMap_ = value; }
    QMap<QString, examples::blocks::BaseBlockBlock> getBlockMap() const { return blockMap_; }
        void setBlockMap(const QMap<QString, examples::blocks::BaseBlockBlock>& value) { blockMap_ = value; }
    QMap<QString, examples::structs::StructBaseBlockBlock> getStructBlockMap() const { return structBlockMap_; }
        void setStructBlockMap(const QMap<QString, examples::structs::StructBaseBlockBlock>& value) { structBlockMap_ = value; }
    private:
        examples::enums::SimpleEnum simpleEnum_ = /* complex expression */;
        examples::enums::ValueEnum valueEnum_ = /* complex expression */;
        examples::blocks::BaseBlockBlock baseBlock_;
        examples::blocks::ExtendedBlockBlock extendedBlock_;
        examples::blocks::AnnotatedBlockBlock annotatedBlock_;
        examples::blocks::ContainerBlockBlock containerBlock_;
        examples::structs::StructBaseBlockBlock structBaseBlock_;
        examples::structs::StructExtendedBlockBlock structExtendedBlock_;
        CrossEnum crossEnum_ = /* complex expression */;
        CrossBlockBlock crossBlock_;
        InheritedCrossBlockBlock inheritedCrossBlock_;
        QVector<examples::enums::SimpleEnum> enumArray_ = [
    "/* complex expression */",
    "/* complex expression */"
];
        QVector<examples::blocks::BaseBlockBlock> blockArray_;
        QVector<examples::structs::StructStatus> statusArray_ = [
    "/* complex expression */",
    "/* complex expression */"
];
        std::optional<examples::enums::ValueEnum> optionalEnum_ = /* complex expression */;
        std::optional<examples::blocks::AnnotatedBlockBlock> optionalBlock_;
        std::optional<examples::structs::StructCategory> optionalCategory_;
        QMap<QString, examples::enums::SimpleEnum> enumMap_;
        QMap<QString, examples::blocks::BaseBlockBlock> blockMap_;
        QMap<QString, examples::structs::StructBaseBlockBlock> structBlockMap_;
    };
    Q_DECLARE_METATYPE(UltimateCrossTestModel)
    
    
} // namespace examples
} // namespace cross_references
