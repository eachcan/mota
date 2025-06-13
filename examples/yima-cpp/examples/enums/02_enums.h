#pragma once

// 此文件由 Mota 代码生成器自动生成
// Mota 版本: 0.2.0
// 生成时间: 2025-06-13 22:21:12
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

    // SimpleEnum枚举
enum class SimpleEnum {
    VALUE1,
    VALUE2,
    VALUE3
};

    // ValueEnum枚举
enum class ValueEnum {
    LOW = 1,
    MEDIUM = 2,
    HIGH = 3
};

[MISSING_MISC:block]    // EnumStruct结构体
    class MODEL_EXPORT EnumStructModel : public IModel {
    public:
        EnumStructModel() = default;
        
        // 实现 IModel 接口
        QCborMap toCbor() const override {
            QCborMap map;
                    map.insert(QLatin1String("simpleField"), simpleField_.toCbor());
                    map.insert(QLatin1String("valueField"), valueField_.toCbor());
            QCborArray simpleArrayArray;
            for (const auto& item : simpleArray_) {
                simpleArrayArray.append(item.toCbor());
            }
            map.insert(QLatin1String("simpleArray"), simpleArrayArray);
            QCborArray valueArrayArray;
            for (const auto& item : valueArray_) {
                valueArrayArray.append(item.toCbor());
            }
            map.insert(QLatin1String("valueArray"), valueArrayArray);
                    if (optionalSimple_) {
                map.insert(QLatin1String("optionalSimple"), optionalSimple_->toCbor());
            }
                    if (optionalValue_) {
                map.insert(QLatin1String("optionalValue"), optionalValue_->toCbor());
            }
            QCborMap simpleMapMap;
            for (auto it = simpleMap_.cbegin(); it != simpleMap_.cend(); ++it) {
                simpleMapMap.insert(it.key(), it.value().toCbor());
            }
            map.insert(QLatin1String("simpleMap"), simpleMapMap);
            QCborMap valueMapMap;
            for (auto it = valueMap_.cbegin(); it != valueMap_.cend(); ++it) {
                valueMapMap.insert(it.key(), it.value().toCbor());
            }
            map.insert(QLatin1String("valueMap"), valueMapMap);
                    map.insert(QLatin1String("blockField"), blockField_.toCbor());
            QCborArray blockArrayArray;
            for (const auto& item : blockArray_) {
                blockArrayArray.append(item.toCbor());
            }
            map.insert(QLatin1String("blockArray"), blockArrayArray);
                    if (optionalBlock_) {
                map.insert(QLatin1String("optionalBlock"), optionalBlock_->toCbor());
            }
            return map;
        }
        
        void fromCbor(const QCborMap& map) override {
            QCborValue tmpValue;
            tmpValue = map.value(QLatin1String("simpleField"));
            if (!tmpValue.isNull()) {
                simpleField_.fromCbor(tmpValue.toMap());
            }
            tmpValue = map.value(QLatin1String("valueField"));
            if (!tmpValue.isNull()) {
                valueField_.fromCbor(tmpValue.toMap());
            }
            tmpValue = map.value(QLatin1String("simpleArray"));
            if (tmpValue.isArray()) {
                QCborArray simpleArrayArray = tmpValue.toArray();
                QVector<SimpleEnum> simpleArrayList;
                for (const auto& item : simpleArrayArray) {
                    SimpleEnum itemValue;
                    itemValue.fromCbor(item.toMap());
                    simpleArrayList.append(itemValue);
                }
                simpleArray_ = simpleArrayList;
            }
            tmpValue = map.value(QLatin1String("valueArray"));
            if (tmpValue.isArray()) {
                QCborArray valueArrayArray = tmpValue.toArray();
                QVector<ValueEnum> valueArrayList;
                for (const auto& item : valueArrayArray) {
                    ValueEnum itemValue;
                    itemValue.fromCbor(item.toMap());
                    valueArrayList.append(itemValue);
                }
                valueArray_ = valueArrayList;
            }
            tmpValue = map.value(QLatin1String("optionalSimple"));
            if (!tmpValue.isNull()) {
                SimpleEnum itemValue;
                itemValue.fromCbor(tmpValue.toMap());
                optionalSimple_ = itemValue;
            }
            tmpValue = map.value(QLatin1String("optionalValue"));
            if (!tmpValue.isNull()) {
                ValueEnum itemValue;
                itemValue.fromCbor(tmpValue.toMap());
                optionalValue_ = itemValue;
            }
            tmpValue = map.value(QLatin1String("simpleMap"));
            if (tmpValue.isMap()) {
                QCborMap simpleMapMap = tmpValue.toMap();
                QMap<QString, SimpleEnum> simpleMapResult;
                for (auto it = simpleMapMap.cbegin(); it != simpleMapMap.cend(); ++it) {
                    SimpleEnum itemValue;
                    itemValue.fromCbor(it.value().toMap());
                    simpleMapResult.insert(it.key().toString(), itemValue);
                }
                simpleMap_ = simpleMapResult;
            }
            tmpValue = map.value(QLatin1String("valueMap"));
            if (tmpValue.isMap()) {
                QCborMap valueMapMap = tmpValue.toMap();
                QMap<QString, ValueEnum> valueMapResult;
                for (auto it = valueMapMap.cbegin(); it != valueMapMap.cend(); ++it) {
                    ValueEnum itemValue;
                    itemValue.fromCbor(it.value().toMap());
                    valueMapResult.insert(it.key().toString(), itemValue);
                }
                valueMap_ = valueMapResult;
            }
            tmpValue = map.value(QLatin1String("blockField"));
            if (!tmpValue.isNull()) {
                blockField_.fromCbor(tmpValue.toMap());
            }
            tmpValue = map.value(QLatin1String("blockArray"));
            if (tmpValue.isArray()) {
                QCborArray blockArrayArray = tmpValue.toArray();
                QVector<EnumBlockBlock> blockArrayList;
                for (const auto& item : blockArrayArray) {
                    EnumBlockBlock itemValue;
                    itemValue.fromCbor(item.toMap());
                    blockArrayList.append(itemValue);
                }
                blockArray_ = blockArrayList;
            }
            tmpValue = map.value(QLatin1String("optionalBlock"));
            if (!tmpValue.isNull()) {
                EnumBlockBlock itemValue;
                itemValue.fromCbor(tmpValue.toMap());
                optionalBlock_ = itemValue;
            }
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
        SimpleEnum simpleField_;
        ValueEnum valueField_;
        QVector<SimpleEnum> simpleArray_;
        QVector<ValueEnum> valueArray_;
        std::optional<SimpleEnum> optionalSimple_;
        std::optional<ValueEnum> optionalValue_;
        QMap<QString, SimpleEnum> simpleMap_;
        QMap<QString, ValueEnum> valueMap_;
        EnumBlockBlock blockField_;
        QVector<EnumBlockBlock> blockArray_;
        std::optional<EnumBlockBlock> optionalBlock_;
    };
    Q_DECLARE_METATYPE(EnumStructModel)
    
    
} // namespace examples
} // namespace enums
