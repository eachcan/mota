#pragma once

// 此文件由 Mota 代码生成器自动生成
// Mota 版本: 0.2.0
// 生成时间: 2025-06-15 19:04:33
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

        static QVector<QSharedPointer<IAnnotation>> fieldAnnotations(const CrossEnum& fieldName) {
            return {};
        }
};

// CrossBlock块定义
class MODEL_EXPORT CrossBlockBlock :  public IBlock {
public:
    CrossBlockBlock() = default;
    
    // 实现 IBlock 接口
    QCborMap toCbor() const override {

    }
    
    void fromCbor(const QCborMap& map) override {
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
// InheritedCrossBlock块定义
class MODEL_EXPORT InheritedCrossBlockBlock : public examples::blocks::BaseBlockBlock {
public:
    InheritedCrossBlockBlock() = default;
    
    // 实现 IBlock 接口
    QCborMap toCbor() const override {

    }
    
    void fromCbor(const QCborMap& map) override {
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
        return examples::blocks::BaseBlockBlock::fieldContainerType(fieldName);
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
// AdvancedCrossBlock块定义
class MODEL_EXPORT AdvancedCrossBlockBlock : public examples::blocks::ExtendedBlockBlock {
public:
    AdvancedCrossBlockBlock() = default;
    
    // 实现 IBlock 接口
    QCborMap toCbor() const override {

    }
    
    void fromCbor(const QCborMap& map) override {
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
        return examples::blocks::ExtendedBlockBlock::fieldContainerType(fieldName);
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
    // CrossStruct结构体
    class MODEL_EXPORT CrossStructModel : public IModel {
    public:
        CrossStructModel() = default;
        
        // 实现 IModel 接口
        QCborMap toCbor() const override {
            return map;
        }
        
        void fromCbor(const QCborMap& map) override {
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
        // InheritedCrossStruct结构体
    class MODEL_EXPORT InheritedCrossStructModel : public examples::structs::StructBaseBlockModel, public IModel {
    public:
        InheritedCrossStructModel() = default;
        
        // 实现 IModel 接口
        QCborMap toCbor() const override {
            return map;
        }
        
        void fromCbor(const QCborMap& map) override {
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
        // UltimateCrossTest结构体
    class MODEL_EXPORT UltimateCrossTestModel : public examples::blocks::AllTypesBlockModel, public IModel {
    public:
        UltimateCrossTestModel() = default;
        
        // 实现 IModel 接口
        QCborMap toCbor() const override {
            return map;
        }
        
        void fromCbor(const QCborMap& map) override {
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
    
} // namespace examples
} // namespace cross_references
