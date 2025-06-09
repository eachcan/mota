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
// 生成时间: 2025-06-08 21:04:04
// 源文件: annotations.mota

using namespace ymf;


namespace examples::annotations {


// DateTimePicker注解
class MODEL_EXPORT DateTimePickerAnnotation : public IAnnotation {
public:
    DateTimePickerAnnotation() = default;
    
    
    // 实现IAnnotation接口
    QString name() const override {
        return "DateTimePicker";
    }
    
    QVariant argument(const QString& argumentName) const override {
        if (argumentName == QLatin1String("format")) return QVariant::fromValue(format_);
        if (argumentName == QLatin1String("placeholder")) return QVariant::fromValue(placeholder_);
        if (argumentName == QLatin1String("value")) return QVariant::fromValue(value_);
        if (argumentName == QLatin1String("type")) return QVariant::fromValue(type_);
        if (argumentName == QLatin1String("from")) return QVariant::fromValue(from_);
        if (argumentName == QLatin1String("to")) return QVariant::fromValue(to_);
        return QVariant();
    }
    
    QStringList argumentNames() const override {
        return QStringList{QLatin1String("format"), QLatin1String("placeholder"), QLatin1String("value"), QLatin1String("type"), QLatin1String("from"), QLatin1String("to")};
    }
    
    // 特定于DateTimePicker的访问器
        // format字段的访问器
    QString getFormat() const {
        return format_;
    }
    
    void setFormat(const QString& value) {
        format_ = value;
    } 

        // placeholder字段的访问器
    QString getPlaceholder() const {
        return placeholder_;
    }
    
    void setPlaceholder(const QString& value) {
        placeholder_ = value;
    } 

        // value字段的访问器
    QString getValue() const {
        return value_;
    }
    
    void setValue(const QString& value) {
        value_ = value;
    } 

        // type字段的访问器
    QString getType() const {
        return type_;
    }
    
    void setType(const QString& value) {
        type_ = value;
    } 

        // from字段的访问器
    QString getFrom() const {
        return from_;
    }
    
    void setFrom(const QString& value) {
        from_ = value;
    } 

        // to字段的访问器
    QString getTo() const {
        return to_;
    }
    
    void setTo(const QString& value) {
        to_ = value;
    } 
    
private:
    QString format_ = "yyyy-MM-dd HH:mm:ss";
    QString placeholder_ = "请选择日期时间";
    QString value_;
    QString type_ = "datetime";
    QString from_;
    QString to_;
}; 

// ModeOption注解
class MODEL_EXPORT ModeOptionAnnotation : public IAnnotation {
public:
    ModeOptionAnnotation() = default;
    
    
    // 实现IAnnotation接口
    QString name() const override {
        return "ModeOption";
    }
    
    QVariant argument(const QString& argumentName) const override {
        if (argumentName == QLatin1String("text")) return QVariant::fromValue(text_);
        if (argumentName == QLatin1String("value")) return QVariant::fromValue(value_);
        return QVariant();
    }
    
    QStringList argumentNames() const override {
        return QStringList{QLatin1String("text"), QLatin1String("value")};
    }
    
    // 特定于ModeOption的访问器
        // text字段的访问器
    QString getText() const {
        return text_;
    }
    
    void setText(const QString& value) {
        text_ = value;
    } 

        // value字段的访问器
    QString getValue() const {
        return value_;
    }
    
    void setValue(const QString& value) {
        value_ = value;
    } 
    
private:
    QString text_ = "正常模式";
    QString value_ = "normal";
}; 

// ModeSelector注解
class MODEL_EXPORT ModeSelectorAnnotation : public IAnnotation {
public:
    ModeSelectorAnnotation() = default;
    
    
    // 实现IAnnotation接口
    QString name() const override {
        return "ModeSelector";
    }
    
    QVariant argument(const QString& argumentName) const override {
        if (argumentName == QLatin1String("default")) return QVariant::fromValue(default_);
        if (argumentName == QLatin1String("value")) return QVariant::fromValue(value_);
        return QVariant();
    }
    
    QStringList argumentNames() const override {
        return QStringList{QLatin1String("default"), QLatin1String("value")};
    }
    
    // 特定于ModeSelector的访问器
        // default字段的访问器
    QSharedPointer<ModeOptionAnnotation> getDefault() const {
        return default_;
    }
    
    void setDefault(const QSharedPointer<ModeOptionAnnotation>& value) {
        default_ = value;
    } 

        // value字段的访问器
    QVector<QSharedPointer<ModeOptionAnnotation>> getValue() const {
        return value_;
    }
    
    void setValue(const QVector<QSharedPointer<ModeOptionAnnotation>>& value) {
        value_ = value;
    } 
    
private:
    QSharedPointer<ModeOptionAnnotation> default_;
    QVector<QSharedPointer<ModeOptionAnnotation>> value_;
}; 

// RunMode结构体

class MODEL_EXPORT RunModeModel : public IModel {
public:
    RunModeModel() = default;
    
    
    // 实现IModel接口
    QCborValue toCbor() const override {
        QCborMap map;
        map.insert(QLatin1String("name"), QCborValue(getName()));
        return map;
    }
    
    void fromCbor(const QCborValue& cbor) override {
        QCborMap map = cbor.toMap();
        setName(map.value(QLatin1String("name")).toString());
    }
    
    QStringList fields() const override {
        return QStringList{QLatin1String("name")};
    }
    
    QString fieldOriginTypeName(const QString& fieldName) const override {
        if (fieldName == QLatin1String("name")) return QLatin1String("string");
        return QLatin1String("");
    }
    
    QList<QSharedPointer<IAnnotation>> annotations() const override {
        
        return QList<QSharedPointer<IAnnotation>>();
    }
    
    QList<QSharedPointer<void>> fieldAnnotations(const QString& fieldName) const override {
        if (fieldName == QLatin1String("name")) {
            QList<QSharedPointer<void>> result;
            auto ModeSelectorInstance = QSharedPointer<ModeSelectorAnnotation>::create();
            ModeSelectorInstance->setDefault(QSharedPointer<ModeOptionAnnotation>::create());
            ModeSelectorInstance->setValue({QSharedPointer<ModeOptionAnnotation>::create(), QSharedPointer<ModeOptionAnnotation>::create(), QSharedPointer<ModeOptionAnnotation>::create(), QSharedPointer<ModeOptionAnnotation>::create()});
            result.append(qSharedPointerCast<void>(ModeSelectorInstance));

            return result;
        }
        return QList<QSharedPointer<void>>();
    }
    
    QString description() const override {
        return "Generated from struct RunMode";
    }
    
    QString fieldDescription(const QString& fieldName) const override {
        
        return QString();
    }
    
    QVariant value(const QString& fieldName) const override {
        if (fieldName == QLatin1String("name")) return QVariant::fromValue(name_);
        return QVariant();
    }
    
    void value(const QString& fieldName, const QVariant& value) override {
        if (fieldName == QLatin1String("name")) {
            name_ = value.value<QString>();
            return;
        }
    }
    
    // 特定于RunMode的访问器
        // name字段的访问器
    QString getName() const {
        return name_;
    }
    
    void setName(const QString& value) {
        name_ = value;
    } 
    
protected:
    QString modelName() const override {
        return "RunMode";
    }
    
private:
    QString name_;
};



} // namespace examples::annotations

