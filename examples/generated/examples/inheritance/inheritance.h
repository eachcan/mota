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
// 生成时间: 2025-06-07 22:55:13
// 源文件: unknown.mota

using namespace ymf;


namespace examples.inheritance {


// Storage注解
class MODEL_EXPORT StorageAnnotation : public IAnnotation {
public:
    StorageAnnotation() = default;
    
    
    // 实现IAnnotation接口
    QString name() const override {
        return "Storage";
    }
    
    QVariant argument(const QString& argumentName) const override {
        if (argumentName == QLatin1String("path")) return QVariant::fromValue(path_);
        if (argumentName == QLatin1String("format")) return QVariant::fromValue(format_);
        return QVariant();
    }
    
    QStringList argumentNames() const override {
        return QStringList{QLatin1String("path"), QLatin1String("format")};
    }
    
    // 特定于Storage的访问器
        // path字段的访问器
    QString getPath() const {
        return path_;
    }
    
    void setPath(const QString& value) {
        path_ = value;
    } 

        // format字段的访问器
    QString getFormat() const {
        return format_;
    }
    
    void setFormat(const QString& value) {
        format_ = value;
    } 
    
private:
    QString path_;
    QString format_;
}; 

// Window注解
class MODEL_EXPORT WindowAnnotation : public IAnnotation {
public:
    WindowAnnotation() = default;
    
    
    // 实现IAnnotation接口
    QString name() const override {
        return "Window";
    }
    
    QVariant argument(const QString& argumentName) const override {
        if (argumentName == QLatin1String("title")) return QVariant::fromValue(title_);
        if (argumentName == QLatin1String("desc")) return QVariant::fromValue(desc_);
        return QVariant();
    }
    
    QStringList argumentNames() const override {
        return QStringList{QLatin1String("title"), QLatin1String("desc")};
    }
    
    // 特定于Window的访问器
        // title字段的访问器
    QString getTitle() const {
        return title_;
    }
    
    void setTitle(const QString& value) {
        title_ = value;
    } 

        // desc字段的访问器
    QString getDesc() const {
        return desc_;
    }
    
    void setDesc(const QString& value) {
        desc_ = value;
    } 
    
private:
    QString title_;
    QString desc_;
}; 

// Scope注解
class MODEL_EXPORT ScopeAnnotation : public IAnnotation {
public:
    ScopeAnnotation() = default;
    
    
    // 实现IAnnotation接口
    QString name() const override {
        return "Scope";
    }
    
    QVariant argument(const QString& argumentName) const override {
        if (argumentName == QLatin1String("value")) return QVariant::fromValue(value_);
        return QVariant();
    }
    
    QStringList argumentNames() const override {
        return QStringList{QLatin1String("value")};
    }
    
    // 特定于Scope的访问器
        // value字段的访问器
    QString getValue() const {
        return value_;
    }
    
    void setValue(const QString& value) {
        value_ = value;
    } 
    
private:
    QString value_;
}; 

// IniGroup注解
class MODEL_EXPORT IniGroupAnnotation : public IAnnotation {
public:
    IniGroupAnnotation() = default;
    
    
    // 实现IAnnotation接口
    QString name() const override {
        return "IniGroup";
    }
    
    QVariant argument(const QString& argumentName) const override {
        if (argumentName == QLatin1String("value")) return QVariant::fromValue(value_);
        return QVariant();
    }
    
    QStringList argumentNames() const override {
        return QStringList{QLatin1String("value")};
    }
    
    // 特定于IniGroup的访问器
        // value字段的访问器
    QString getValue() const {
        return value_;
    }
    
    void setValue(const QString& value) {
        value_ = value;
    } 
    
private:
    QString value_;
}; 

// Int注解
class MODEL_EXPORT IntAnnotation : public IAnnotation {
public:
    IntAnnotation() = default;
    
    
    // 实现IAnnotation接口
    QString name() const override {
        return "Int";
    }
    
    QVariant argument(const QString& argumentName) const override {
        if (argumentName == QLatin1String("min")) return QVariant::fromValue(min_);
        if (argumentName == QLatin1String("max")) return QVariant::fromValue(max_);
        if (argumentName == QLatin1String("step")) return QVariant::fromValue(step_);
        if (argumentName == QLatin1String("desc")) return QVariant::fromValue(desc_);
        return QVariant();
    }
    
    QStringList argumentNames() const override {
        return QStringList{QLatin1String("min"), QLatin1String("max"), QLatin1String("step"), QLatin1String("desc")};
    }
    
    // 特定于Int的访问器
        // min字段的访问器
    int32_t getMin() const {
        return min_;
    }
    
    void setMin(const int32_t& value) {
        min_ = value;
    } 

        // max字段的访问器
    int32_t getMax() const {
        return max_;
    }
    
    void setMax(const int32_t& value) {
        max_ = value;
    } 

        // step字段的访问器
    int32_t getStep() const {
        return step_;
    }
    
    void setStep(const int32_t& value) {
        step_ = value;
    } 

        // desc字段的访问器
    QString getDesc() const {
        return desc_;
    }
    
    void setDesc(const QString& value) {
        desc_ = value;
    } 
    
private:
    int32_t min_;
    int32_t max_;
    int32_t step_;
    QString desc_;
}; 

// Float注解
class MODEL_EXPORT FloatAnnotation : public IAnnotation {
public:
    FloatAnnotation() = default;
    
    
    // 实现IAnnotation接口
    QString name() const override {
        return "Float";
    }
    
    QVariant argument(const QString& argumentName) const override {
        if (argumentName == QLatin1String("min")) return QVariant::fromValue(min_);
        if (argumentName == QLatin1String("max")) return QVariant::fromValue(max_);
        if (argumentName == QLatin1String("step")) return QVariant::fromValue(step_);
        if (argumentName == QLatin1String("desc")) return QVariant::fromValue(desc_);
        return QVariant();
    }
    
    QStringList argumentNames() const override {
        return QStringList{QLatin1String("min"), QLatin1String("max"), QLatin1String("step"), QLatin1String("desc")};
    }
    
    // 特定于Float的访问器
        // min字段的访问器
    double getMin() const {
        return min_;
    }
    
    void setMin(const double& value) {
        min_ = value;
    } 

        // max字段的访问器
    double getMax() const {
        return max_;
    }
    
    void setMax(const double& value) {
        max_ = value;
    } 

        // step字段的访问器
    double getStep() const {
        return step_;
    }
    
    void setStep(const double& value) {
        step_ = value;
    } 

        // desc字段的访问器
    QString getDesc() const {
        return desc_;
    }
    
    void setDesc(const QString& value) {
        desc_ = value;
    } 
    
private:
    double min_;
    double max_;
    double step_;
    QString desc_;
}; 

// Text注解
class MODEL_EXPORT TextAnnotation : public IAnnotation {
public:
    TextAnnotation() = default;
    
    
    // 实现IAnnotation接口
    QString name() const override {
        return "Text";
    }
    
    QVariant argument(const QString& argumentName) const override {
        if (argumentName == QLatin1String("max_length")) return QVariant::fromValue(max_length_);
        if (argumentName == QLatin1String("desc")) return QVariant::fromValue(desc_);
        if (argumentName == QLatin1String("pattern")) return QVariant::fromValue(pattern_);
        return QVariant();
    }
    
    QStringList argumentNames() const override {
        return QStringList{QLatin1String("max_length"), QLatin1String("desc"), QLatin1String("pattern")};
    }
    
    // 特定于Text的访问器
        // max_length字段的访问器
    int32_t getMaxLength() const {
        return max_length_;
    }
    
    void setMaxLength(const int32_t& value) {
        max_length_ = value;
    } 

        // desc字段的访问器
    QString getDesc() const {
        return desc_;
    }
    
    void setDesc(const QString& value) {
        desc_ = value;
    } 

        // pattern字段的访问器
    QString getPattern() const {
        return pattern_;
    }
    
    void setPattern(const QString& value) {
        pattern_ = value;
    } 
    
private:
    int32_t max_length_;
    QString desc_;
    QString pattern_;
}; 

// Switcher注解
class MODEL_EXPORT SwitcherAnnotation : public IAnnotation {
public:
    SwitcherAnnotation() = default;
    
    
    // 实现IAnnotation接口
    QString name() const override {
        return "Switcher";
    }
    
    QVariant argument(const QString& argumentName) const override {
        if (argumentName == QLatin1String("desc")) return QVariant::fromValue(desc_);
        return QVariant();
    }
    
    QStringList argumentNames() const override {
        return QStringList{QLatin1String("desc")};
    }
    
    // 特定于Switcher的访问器
        // desc字段的访问器
    QString getDesc() const {
        return desc_;
    }
    
    void setDesc(const QString& value) {
        desc_ = value;
    } 
    
private:
    QString desc_;
}; 

// Select注解
class MODEL_EXPORT SelectAnnotation : public IAnnotation {
public:
    SelectAnnotation() = default;
    
    
    // 实现IAnnotation接口
    QString name() const override {
        return "Select";
    }
    
    QVariant argument(const QString& argumentName) const override {
        if (argumentName == QLatin1String("desc")) return QVariant::fromValue(desc_);
        if (argumentName == QLatin1String("enumClass")) return QVariant::fromValue(enumClass_);
        if (argumentName == QLatin1String("field")) return QVariant::fromValue(field_);
        return QVariant();
    }
    
    QStringList argumentNames() const override {
        return QStringList{QLatin1String("desc"), QLatin1String("enumClass"), QLatin1String("field")};
    }
    
    // 特定于Select的访问器
        // desc字段的访问器
    QString getDesc() const {
        return desc_;
    }
    
    void setDesc(const QString& value) {
        desc_ = value;
    } 

        // enumClass字段的访问器
    QString getEnumClass() const {
        return enumClass_;
    }
    
    void setEnumClass(const QString& value) {
        enumClass_ = value;
    } 

        // field字段的访问器
    QString getField() const {
        return field_;
    }
    
    void setField(const QString& value) {
        field_ = value;
    } 
    
private:
    QString desc_;
    QString enumClass_;
    QString field_;
}; 

// EnumValue注解
class MODEL_EXPORT EnumValueAnnotation : public IAnnotation {
public:
    EnumValueAnnotation() = default;
    
    
    // 实现IAnnotation接口
    QString name() const override {
        return "EnumValue";
    }
    
    QVariant argument(const QString& argumentName) const override {
        if (argumentName == QLatin1String("title")) return QVariant::fromValue(title_);
        if (argumentName == QLatin1String("desc")) return QVariant::fromValue(desc_);
        if (argumentName == QLatin1String("value")) return QVariant::fromValue(value_);
        return QVariant();
    }
    
    QStringList argumentNames() const override {
        return QStringList{QLatin1String("title"), QLatin1String("desc"), QLatin1String("value")};
    }
    
    // 特定于EnumValue的访问器
        // title字段的访问器
    QString getTitle() const {
        return title_;
    }
    
    void setTitle(const QString& value) {
        title_ = value;
    } 

        // desc字段的访问器
    QString getDesc() const {
        return desc_;
    }
    
    void setDesc(const QString& value) {
        desc_ = value;
    } 

        // value字段的访问器
    QString getValue() const {
        return value_;
    }
    
    void setValue(const QString& value) {
        value_ = value;
    } 
    
private:
    QString title_;
    QString desc_;
    QString value_;
}; 

// FolderDialog注解
class MODEL_EXPORT FolderDialogAnnotation : public IAnnotation {
public:
    FolderDialogAnnotation() = default;
    
    
    // 实现IAnnotation接口
    QString name() const override {
        return "FolderDialog";
    }
    
    QVariant argument(const QString& argumentName) const override {
        if (argumentName == QLatin1String("buttonText")) return QVariant::fromValue(buttonText_);
        return QVariant();
    }
    
    QStringList argumentNames() const override {
        return QStringList{QLatin1String("buttonText")};
    }
    
    // 特定于FolderDialog的访问器
        // buttonText字段的访问器
    QString getButtonText() const {
        return buttonText_;
    }
    
    void setButtonText(const QString& value) {
        buttonText_ = value;
    } 
    
private:
    QString buttonText_;
}; 

// FileDialog注解
class MODEL_EXPORT FileDialogAnnotation : public IAnnotation {
public:
    FileDialogAnnotation() = default;
    
    
    // 实现IAnnotation接口
    QString name() const override {
        return "FileDialog";
    }
    
    QVariant argument(const QString& argumentName) const override {
        if (argumentName == QLatin1String("filter")) return QVariant::fromValue(filter_);
        if (argumentName == QLatin1String("buttonText")) return QVariant::fromValue(buttonText_);
        return QVariant();
    }
    
    QStringList argumentNames() const override {
        return QStringList{QLatin1String("filter"), QLatin1String("buttonText")};
    }
    
    // 特定于FileDialog的访问器
        // filter字段的访问器
    QString getFilter() const {
        return filter_;
    }
    
    void setFilter(const QString& value) {
        filter_ = value;
    } 

        // buttonText字段的访问器
    QString getButtonText() const {
        return buttonText_;
    }
    
    void setButtonText(const QString& value) {
        buttonText_ = value;
    } 
    
private:
    QString filter_;
    QString buttonText_;
}; 

// ColorPicker注解
class MODEL_EXPORT ColorPickerAnnotation : public IAnnotation {
public:
    ColorPickerAnnotation() = default;
    
    
    // 实现IAnnotation接口
    QString name() const override {
        return "ColorPicker";
    }
    
    QVariant argument(const QString& argumentName) const override {
        if (argumentName == QLatin1String("default_value")) return QVariant::fromValue(default_value_);
        if (argumentName == QLatin1String("buttonText")) return QVariant::fromValue(buttonText_);
        return QVariant();
    }
    
    QStringList argumentNames() const override {
        return QStringList{QLatin1String("default_value"), QLatin1String("buttonText")};
    }
    
    // 特定于ColorPicker的访问器
        // default_value字段的访问器
    QString getDefaultValue() const {
        return default_value_;
    }
    
    void setDefaultValue(const QString& value) {
        default_value_ = value;
    } 

        // buttonText字段的访问器
    QString getButtonText() const {
        return buttonText_;
    }
    
    void setButtonText(const QString& value) {
        buttonText_ = value;
    } 
    
private:
    QString default_value_;
    QString buttonText_;
}; 

// Date注解
class MODEL_EXPORT DateAnnotation : public IAnnotation {
public:
    DateAnnotation() = default;
    
    
    // 实现IAnnotation接口
    QString name() const override {
        return "Date";
    }
    
    QVariant argument(const QString& argumentName) const override {
        if (argumentName == QLatin1String("format")) return QVariant::fromValue(format_);
        if (argumentName == QLatin1String("buttonText")) return QVariant::fromValue(buttonText_);
        return QVariant();
    }
    
    QStringList argumentNames() const override {
        return QStringList{QLatin1String("format"), QLatin1String("buttonText")};
    }
    
    // 特定于Date的访问器
        // format字段的访问器
    QString getFormat() const {
        return format_;
    }
    
    void setFormat(const QString& value) {
        format_ = value;
    } 

        // buttonText字段的访问器
    QString getButtonText() const {
        return buttonText_;
    }
    
    void setButtonText(const QString& value) {
        buttonText_ = value;
    } 
    
private:
    QString format_;
    QString buttonText_;
}; 

// Time注解
class MODEL_EXPORT TimeAnnotation : public IAnnotation {
public:
    TimeAnnotation() = default;
    
    
    // 实现IAnnotation接口
    QString name() const override {
        return "Time";
    }
    
    QVariant argument(const QString& argumentName) const override {
        if (argumentName == QLatin1String("format")) return QVariant::fromValue(format_);
        if (argumentName == QLatin1String("buttonText")) return QVariant::fromValue(buttonText_);
        return QVariant();
    }
    
    QStringList argumentNames() const override {
        return QStringList{QLatin1String("format"), QLatin1String("buttonText")};
    }
    
    // 特定于Time的访问器
        // format字段的访问器
    QString getFormat() const {
        return format_;
    }
    
    void setFormat(const QString& value) {
        format_ = value;
    } 

        // buttonText字段的访问器
    QString getButtonText() const {
        return buttonText_;
    }
    
    void setButtonText(const QString& value) {
        buttonText_ = value;
    } 
    
private:
    QString format_;
    QString buttonText_;
}; 

// DrawRectangle注解
class MODEL_EXPORT DrawRectangleAnnotation : public IAnnotation {
public:
    DrawRectangleAnnotation() = default;
    
    
    // 实现IAnnotation接口
    QString name() const override {
        return "DrawRectangle";
    }
    
    QVariant argument(const QString& argumentName) const override {
        if (argumentName == QLatin1String("buttonText")) return QVariant::fromValue(buttonText_);
        return QVariant();
    }
    
    QStringList argumentNames() const override {
        return QStringList{QLatin1String("buttonText")};
    }
    
    // 特定于DrawRectangle的访问器
        // buttonText字段的访问器
    QString getButtonText() const {
        return buttonText_;
    }
    
    void setButtonText(const QString& value) {
        buttonText_ = value;
    } 
    
private:
    QString buttonText_;
}; 

// DrawCircle注解
class MODEL_EXPORT DrawCircleAnnotation : public IAnnotation {
public:
    DrawCircleAnnotation() = default;
    
    
    // 实现IAnnotation接口
    QString name() const override {
        return "DrawCircle";
    }
    
    QVariant argument(const QString& argumentName) const override {
        if (argumentName == QLatin1String("buttonText")) return QVariant::fromValue(buttonText_);
        return QVariant();
    }
    
    QStringList argumentNames() const override {
        return QStringList{QLatin1String("buttonText")};
    }
    
    // 特定于DrawCircle的访问器
        // buttonText字段的访问器
    QString getButtonText() const {
        return buttonText_;
    }
    
    void setButtonText(const QString& value) {
        buttonText_ = value;
    } 
    
private:
    QString buttonText_;
}; 

// DrawPolygon注解
class MODEL_EXPORT DrawPolygonAnnotation : public IAnnotation {
public:
    DrawPolygonAnnotation() = default;
    
    
    // 实现IAnnotation接口
    QString name() const override {
        return "DrawPolygon";
    }
    
    QVariant argument(const QString& argumentName) const override {
        if (argumentName == QLatin1String("buttonText")) return QVariant::fromValue(buttonText_);
        return QVariant();
    }
    
    QStringList argumentNames() const override {
        return QStringList{QLatin1String("buttonText")};
    }
    
    // 特定于DrawPolygon的访问器
        // buttonText字段的访问器
    QString getButtonText() const {
        return buttonText_;
    }
    
    void setButtonText(const QString& value) {
        buttonText_ = value;
    } 
    
private:
    QString buttonText_;
}; 

// DrawLine注解
class MODEL_EXPORT DrawLineAnnotation : public IAnnotation {
public:
    DrawLineAnnotation() = default;
    
    
    // 实现IAnnotation接口
    QString name() const override {
        return "DrawLine";
    }
    
    QVariant argument(const QString& argumentName) const override {
        if (argumentName == QLatin1String("buttonText")) return QVariant::fromValue(buttonText_);
        return QVariant();
    }
    
    QStringList argumentNames() const override {
        return QStringList{QLatin1String("buttonText")};
    }
    
    // 特定于DrawLine的访问器
        // buttonText字段的访问器
    QString getButtonText() const {
        return buttonText_;
    }
    
    void setButtonText(const QString& value) {
        buttonText_ = value;
    } 
    
private:
    QString buttonText_;
}; 

// DrawPoint注解
class MODEL_EXPORT DrawPointAnnotation : public IAnnotation {
public:
    DrawPointAnnotation() = default;
    
    
    // 实现IAnnotation接口
    QString name() const override {
        return "DrawPoint";
    }
    
    QVariant argument(const QString& argumentName) const override {
        if (argumentName == QLatin1String("buttonText")) return QVariant::fromValue(buttonText_);
        return QVariant();
    }
    
    QStringList argumentNames() const override {
        return QStringList{QLatin1String("buttonText")};
    }
    
    // 特定于DrawPoint的访问器
        // buttonText字段的访问器
    QString getButtonText() const {
        return buttonText_;
    }
    
    void setButtonText(const QString& value) {
        buttonText_ = value;
    } 
    
private:
    QString buttonText_;
}; 

// Label注解
class MODEL_EXPORT LabelAnnotation : public IAnnotation {
public:
    LabelAnnotation() = default;
    
    
    // 实现IAnnotation接口
    QString name() const override {
        return "Label";
    }
    
    QVariant argument(const QString& argumentName) const override {
        if (argumentName == QLatin1String("text")) return QVariant::fromValue(text_);
        return QVariant();
    }
    
    QStringList argumentNames() const override {
        return QStringList{QLatin1String("text")};
    }
    
    // 特定于Label的访问器
        // text字段的访问器
    QString getText() const {
        return text_;
    }
    
    void setText(const QString& value) {
        text_ = value;
    } 
    
private:
    QString text_;
}; 

// Validate注解
class MODEL_EXPORT ValidateAnnotation : public IAnnotation {
public:
    ValidateAnnotation() = default;
    
    
    // 实现IAnnotation接口
    QString name() const override {
        return "Validate";
    }
    
    QVariant argument(const QString& argumentName) const override {
        if (argumentName == QLatin1String("rule")) return QVariant::fromValue(rule_);
        if (argumentName == QLatin1String("message")) return QVariant::fromValue(message_);
        return QVariant();
    }
    
    QStringList argumentNames() const override {
        return QStringList{QLatin1String("rule"), QLatin1String("message")};
    }
    
    // 特定于Validate的访问器
        // rule字段的访问器
    QString getRule() const {
        return rule_;
    }
    
    void setRule(const QString& value) {
        rule_ = value;
    } 

        // message字段的访问器
    QString getMessage() const {
        return message_;
    }
    
    void setMessage(const QString& value) {
        message_ = value;
    } 
    
private:
    QString rule_;
    QString message_;
}; 

// Tooltip注解
class MODEL_EXPORT TooltipAnnotation : public IAnnotation {
public:
    TooltipAnnotation() = default;
    
    
    // 实现IAnnotation接口
    QString name() const override {
        return "Tooltip";
    }
    
    QVariant argument(const QString& argumentName) const override {
        if (argumentName == QLatin1String("text")) return QVariant::fromValue(text_);
        if (argumentName == QLatin1String("duration")) return QVariant::fromValue(duration_);
        return QVariant();
    }
    
    QStringList argumentNames() const override {
        return QStringList{QLatin1String("text"), QLatin1String("duration")};
    }
    
    // 特定于Tooltip的访问器
        // text字段的访问器
    QString getText() const {
        return text_;
    }
    
    void setText(const QString& value) {
        text_ = value;
    } 

        // duration字段的访问器
    int32_t getDuration() const {
        return duration_;
    }
    
    void setDuration(const int32_t& value) {
        duration_ = value;
    } 
    
private:
    QString text_;
    int32_t duration_;
}; 

// ReadOnly注解
class MODEL_EXPORT ReadOnlyAnnotation : public IAnnotation {
public:
    ReadOnlyAnnotation() = default;
    
    
    // 实现IAnnotation接口
    QString name() const override {
        return "ReadOnly";
    }
    
    QVariant argument(const QString& argumentName) const override {
        return QVariant();
    }
    
    QStringList argumentNames() const override {
        return QStringList{};
    }
    
    // 特定于ReadOnly的访问器
    
    
private:
    
}; 

// Hidden注解
class MODEL_EXPORT HiddenAnnotation : public IAnnotation {
public:
    HiddenAnnotation() = default;
    
    
    // 实现IAnnotation接口
    QString name() const override {
        return "Hidden";
    }
    
    QVariant argument(const QString& argumentName) const override {
        return QVariant();
    }
    
    QStringList argumentNames() const override {
        return QStringList{};
    }
    
    // 特定于Hidden的访问器
    
    
private:
    
}; 

// BaseShape块
class MODEL_EXPORT BaseShapeBlock : public IBlock {
public:
    BaseShapeBlock() = default;
    
    
    // 实现IBlock接口
    QCborValue toCbor() const override {
        QCborMap map;
        map.insert(QLatin1String("name"), QCborValue(getName()));
        map.insert(QLatin1String("fillColor"), QCborValue(getFillColor()));
        map.insert(QLatin1String("strokeColor"), QCborValue(getStrokeColor()));
        map.insert(QLatin1String("strokeWidth"), QCborValue(getStrokeWidth()));
        return map;
    }
    
    void fromCbor(const QCborValue& cbor) override {
        QCborMap map = cbor.toMap();
        setName(map.value(QLatin1String("name")).toString());
        setFillColor(map.value(QLatin1String("fillColor")).toString());
        setStrokeColor(map.value(QLatin1String("strokeColor")).toString());
        setStrokeWidth(static_cast<float>(map.value(QLatin1String("strokeWidth")).toDouble()));
    }
    
    QString name() const override {
        return "BaseShape";
    }
    
    QStringList fields() const override {
        return QStringList{QLatin1String("name"), QLatin1String("fillColor"), QLatin1String("strokeColor"), QLatin1String("strokeWidth")};
    }
    
    QString fieldType(const QString& fieldName) const override {
        if (fieldName == QLatin1String("name")) return QLatin1String("string");
        if (fieldName == QLatin1String("fillColor")) return QLatin1String("string");
        if (fieldName == QLatin1String("strokeColor")) return QLatin1String("string");
        if (fieldName == QLatin1String("strokeWidth")) return QLatin1String("float32");
        return QLatin1String("");
    }
    
    QList<QSharedPointer<IAnnotation>> annotations() const override {
        
        return QList<QSharedPointer<IAnnotation>>();
    }
    
    QList<QSharedPointer<void>> fieldAnnotation(const QString& fieldName) const override {
        if (fieldName == QLatin1String("name")) {
            return QList<QSharedPointer<void>>();
        }
        if (fieldName == QLatin1String("fillColor")) {
            return QList<QSharedPointer<void>>();
        }
        if (fieldName == QLatin1String("strokeColor")) {
            return QList<QSharedPointer<void>>();
        }
        if (fieldName == QLatin1String("strokeWidth")) {
            return QList<QSharedPointer<void>>();
        }
        return QList<QSharedPointer<void>>();
    }
    
    QString description() const override {
        return "Generated from block BaseShape";
    }
    
    QString fieldDescription(const QString& fieldName) const override {
        
        return QString();
    }
    
    QVariant value(const QString& fieldName) const override {
        if (fieldName == QLatin1String("name")) return QVariant::fromValue(name_);
        if (fieldName == QLatin1String("fillColor")) return QVariant::fromValue(fillColor_);
        if (fieldName == QLatin1String("strokeColor")) return QVariant::fromValue(strokeColor_);
        if (fieldName == QLatin1String("strokeWidth")) return QVariant::fromValue(strokeWidth_);
        return QVariant();
    }
    
    void value(const QString& fieldName, const QVariant& value) override {
        if (fieldName == QLatin1String("name")) {
            name_ = value.value<QString>();
            return;
        }
        if (fieldName == QLatin1String("fillColor")) {
            fillColor_ = value.value<QString>();
            return;
        }
        if (fieldName == QLatin1String("strokeColor")) {
            strokeColor_ = value.value<QString>();
            return;
        }
        if (fieldName == QLatin1String("strokeWidth")) {
            strokeWidth_ = value.value<float>();
            return;
        }
    }
    
    // 特定于BaseShape的访问器
        // name字段的访问器
    QString getName() const {
        return name_;
    }
    
    void setName(const QString& value) {
        name_ = value;
    } 

        // fillColor字段的访问器
    QString getFillColor() const {
        return fillColor_;
    }
    
    void setFillColor(const QString& value) {
        fillColor_ = value;
    } 

        // strokeColor字段的访问器
    QString getStrokeColor() const {
        return strokeColor_;
    }
    
    void setStrokeColor(const QString& value) {
        strokeColor_ = value;
    } 

        // strokeWidth字段的访问器
    float getStrokeWidth() const {
        return strokeWidth_;
    }
    
    void setStrokeWidth(const float& value) {
        strokeWidth_ = value;
    } 
    
private:
    QString name_;
    QString fillColor_;
    QString strokeColor_;
    float strokeWidth_;
};


// RectangleShape块
class MODEL_EXPORT RectangleShapeBlock : public BaseShapeBlock, public IBlock {
public:
    RectangleShapeBlock() = default;
    
    
    // 实现IBlock接口
    QCborValue toCbor() const override {
        QCborMap map;
        map.insert(QLatin1String("width"), QCborValue(getWidth()));
        map.insert(QLatin1String("height"), QCborValue(getHeight()));
        map.insert(QLatin1String("area"), QCborValue(getArea()));
        return map;
    }
    
    void fromCbor(const QCborValue& cbor) override {
        QCborMap map = cbor.toMap();
        setWidth(static_cast<float>(map.value(QLatin1String("width")).toDouble()));
        setHeight(static_cast<float>(map.value(QLatin1String("height")).toDouble()));
        setArea(static_cast<float>(map.value(QLatin1String("area")).toDouble()));
    }
    
    QString name() const override {
        return "RectangleShape";
    }
    
    QStringList fields() const override {
        return QStringList{QLatin1String("width"), QLatin1String("height"), QLatin1String("area")};
    }
    
    QString fieldType(const QString& fieldName) const override {
        if (fieldName == QLatin1String("width")) return QLatin1String("float32");
        if (fieldName == QLatin1String("height")) return QLatin1String("float32");
        if (fieldName == QLatin1String("area")) return QLatin1String("float32");
        return QLatin1String("");
    }
    
    QList<QSharedPointer<IAnnotation>> annotations() const override {
        
        return QList<QSharedPointer<IAnnotation>>();
    }
    
    QList<QSharedPointer<void>> fieldAnnotation(const QString& fieldName) const override {
        if (fieldName == QLatin1String("width")) {
            return QList<QSharedPointer<void>>();
        }
        if (fieldName == QLatin1String("height")) {
            return QList<QSharedPointer<void>>();
        }
        if (fieldName == QLatin1String("area")) {
            return QList<QSharedPointer<void>>();
        }
        return QList<QSharedPointer<void>>();
    }
    
    QString description() const override {
        return "Generated from block RectangleShape";
    }
    
    QString fieldDescription(const QString& fieldName) const override {
        
        return QString();
    }
    
    QVariant value(const QString& fieldName) const override {
        if (fieldName == QLatin1String("width")) return QVariant::fromValue(width_);
        if (fieldName == QLatin1String("height")) return QVariant::fromValue(height_);
        if (fieldName == QLatin1String("area")) return QVariant::fromValue(area_);
        return QVariant();
    }
    
    void value(const QString& fieldName, const QVariant& value) override {
        if (fieldName == QLatin1String("width")) {
            width_ = value.value<float>();
            return;
        }
        if (fieldName == QLatin1String("height")) {
            height_ = value.value<float>();
            return;
        }
        if (fieldName == QLatin1String("area")) {
            area_ = value.value<float>();
            return;
        }
    }
    
    // 特定于RectangleShape的访问器
        // width字段的访问器
    float getWidth() const {
        return width_;
    }
    
    void setWidth(const float& value) {
        width_ = value;
    } 

        // height字段的访问器
    float getHeight() const {
        return height_;
    }
    
    void setHeight(const float& value) {
        height_ = value;
    } 

        // area字段的访问器
    float getArea() const {
        return area_;
    }
    
    void setArea(const float& value) {
        area_ = value;
    } 
    
private:
    float width_;
    float height_;
    float area_;
};


// CircleShape块
class MODEL_EXPORT CircleShapeBlock : public BaseShapeBlock, public IBlock {
public:
    CircleShapeBlock() = default;
    
    
    // 实现IBlock接口
    QCborValue toCbor() const override {
        QCborMap map;
        map.insert(QLatin1String("radius"), QCborValue(getRadius()));
        map.insert(QLatin1String("area"), QCborValue(getArea()));
        return map;
    }
    
    void fromCbor(const QCborValue& cbor) override {
        QCborMap map = cbor.toMap();
        setRadius(static_cast<float>(map.value(QLatin1String("radius")).toDouble()));
        setArea(static_cast<float>(map.value(QLatin1String("area")).toDouble()));
    }
    
    QString name() const override {
        return "CircleShape";
    }
    
    QStringList fields() const override {
        return QStringList{QLatin1String("radius"), QLatin1String("area")};
    }
    
    QString fieldType(const QString& fieldName) const override {
        if (fieldName == QLatin1String("radius")) return QLatin1String("float32");
        if (fieldName == QLatin1String("area")) return QLatin1String("float32");
        return QLatin1String("");
    }
    
    QList<QSharedPointer<IAnnotation>> annotations() const override {
        
        return QList<QSharedPointer<IAnnotation>>();
    }
    
    QList<QSharedPointer<void>> fieldAnnotation(const QString& fieldName) const override {
        if (fieldName == QLatin1String("radius")) {
            return QList<QSharedPointer<void>>();
        }
        if (fieldName == QLatin1String("area")) {
            return QList<QSharedPointer<void>>();
        }
        return QList<QSharedPointer<void>>();
    }
    
    QString description() const override {
        return "Generated from block CircleShape";
    }
    
    QString fieldDescription(const QString& fieldName) const override {
        
        return QString();
    }
    
    QVariant value(const QString& fieldName) const override {
        if (fieldName == QLatin1String("radius")) return QVariant::fromValue(radius_);
        if (fieldName == QLatin1String("area")) return QVariant::fromValue(area_);
        return QVariant();
    }
    
    void value(const QString& fieldName, const QVariant& value) override {
        if (fieldName == QLatin1String("radius")) {
            radius_ = value.value<float>();
            return;
        }
        if (fieldName == QLatin1String("area")) {
            area_ = value.value<float>();
            return;
        }
    }
    
    // 特定于CircleShape的访问器
        // radius字段的访问器
    float getRadius() const {
        return radius_;
    }
    
    void setRadius(const float& value) {
        radius_ = value;
    } 

        // area字段的访问器
    float getArea() const {
        return area_;
    }
    
    void setArea(const float& value) {
        area_ = value;
    } 
    
private:
    float radius_;
    float area_;
};


// LineShape块
class MODEL_EXPORT LineShapeBlock : public IBlock {
public:
    LineShapeBlock() = default;
    
    
    // 实现IBlock接口
    QCborValue toCbor() const override {
        QCborMap map;
        map.insert(QLatin1String("startX"), QCborValue(getStartX()));
        map.insert(QLatin1String("startY"), QCborValue(getStartY()));
        map.insert(QLatin1String("endX"), QCborValue(getEndX()));
        map.insert(QLatin1String("endY"), QCborValue(getEndY()));
        map.insert(QLatin1String("lineColor"), QCborValue(getLineColor()));
        map.insert(QLatin1String("lineWidth"), QCborValue(getLineWidth()));
        return map;
    }
    
    void fromCbor(const QCborValue& cbor) override {
        QCborMap map = cbor.toMap();
        setStartX(static_cast<float>(map.value(QLatin1String("startX")).toDouble()));
        setStartY(static_cast<float>(map.value(QLatin1String("startY")).toDouble()));
        setEndX(static_cast<float>(map.value(QLatin1String("endX")).toDouble()));
        setEndY(static_cast<float>(map.value(QLatin1String("endY")).toDouble()));
        setLineColor(map.value(QLatin1String("lineColor")).toString());
        setLineWidth(static_cast<float>(map.value(QLatin1String("lineWidth")).toDouble()));
    }
    
    QString name() const override {
        return "LineShape";
    }
    
    QStringList fields() const override {
        return QStringList{QLatin1String("startX"), QLatin1String("startY"), QLatin1String("endX"), QLatin1String("endY"), QLatin1String("lineColor"), QLatin1String("lineWidth")};
    }
    
    QString fieldType(const QString& fieldName) const override {
        if (fieldName == QLatin1String("startX")) return QLatin1String("float32");
        if (fieldName == QLatin1String("startY")) return QLatin1String("float32");
        if (fieldName == QLatin1String("endX")) return QLatin1String("float32");
        if (fieldName == QLatin1String("endY")) return QLatin1String("float32");
        if (fieldName == QLatin1String("lineColor")) return QLatin1String("string");
        if (fieldName == QLatin1String("lineWidth")) return QLatin1String("float32");
        return QLatin1String("");
    }
    
    QList<QSharedPointer<IAnnotation>> annotations() const override {
        
        return QList<QSharedPointer<IAnnotation>>();
    }
    
    QList<QSharedPointer<void>> fieldAnnotation(const QString& fieldName) const override {
        if (fieldName == QLatin1String("startX")) {
            return QList<QSharedPointer<void>>();
        }
        if (fieldName == QLatin1String("startY")) {
            return QList<QSharedPointer<void>>();
        }
        if (fieldName == QLatin1String("endX")) {
            return QList<QSharedPointer<void>>();
        }
        if (fieldName == QLatin1String("endY")) {
            return QList<QSharedPointer<void>>();
        }
        if (fieldName == QLatin1String("lineColor")) {
            return QList<QSharedPointer<void>>();
        }
        if (fieldName == QLatin1String("lineWidth")) {
            return QList<QSharedPointer<void>>();
        }
        return QList<QSharedPointer<void>>();
    }
    
    QString description() const override {
        return "Generated from block LineShape";
    }
    
    QString fieldDescription(const QString& fieldName) const override {
        
        return QString();
    }
    
    QVariant value(const QString& fieldName) const override {
        if (fieldName == QLatin1String("startX")) return QVariant::fromValue(startX_);
        if (fieldName == QLatin1String("startY")) return QVariant::fromValue(startY_);
        if (fieldName == QLatin1String("endX")) return QVariant::fromValue(endX_);
        if (fieldName == QLatin1String("endY")) return QVariant::fromValue(endY_);
        if (fieldName == QLatin1String("lineColor")) return QVariant::fromValue(lineColor_);
        if (fieldName == QLatin1String("lineWidth")) return QVariant::fromValue(lineWidth_);
        return QVariant();
    }
    
    void value(const QString& fieldName, const QVariant& value) override {
        if (fieldName == QLatin1String("startX")) {
            startX_ = value.value<float>();
            return;
        }
        if (fieldName == QLatin1String("startY")) {
            startY_ = value.value<float>();
            return;
        }
        if (fieldName == QLatin1String("endX")) {
            endX_ = value.value<float>();
            return;
        }
        if (fieldName == QLatin1String("endY")) {
            endY_ = value.value<float>();
            return;
        }
        if (fieldName == QLatin1String("lineColor")) {
            lineColor_ = value.value<QString>();
            return;
        }
        if (fieldName == QLatin1String("lineWidth")) {
            lineWidth_ = value.value<float>();
            return;
        }
    }
    
    // 特定于LineShape的访问器
        // startX字段的访问器
    float getStartX() const {
        return startX_;
    }
    
    void setStartX(const float& value) {
        startX_ = value;
    } 

        // startY字段的访问器
    float getStartY() const {
        return startY_;
    }
    
    void setStartY(const float& value) {
        startY_ = value;
    } 

        // endX字段的访问器
    float getEndX() const {
        return endX_;
    }
    
    void setEndX(const float& value) {
        endX_ = value;
    } 

        // endY字段的访问器
    float getEndY() const {
        return endY_;
    }
    
    void setEndY(const float& value) {
        endY_ = value;
    } 

        // lineColor字段的访问器
    QString getLineColor() const {
        return lineColor_;
    }
    
    void setLineColor(const QString& value) {
        lineColor_ = value;
    } 

        // lineWidth字段的访问器
    float getLineWidth() const {
        return lineWidth_;
    }
    
    void setLineWidth(const float& value) {
        lineWidth_ = value;
    } 
    
private:
    float startX_;
    float startY_;
    float endX_;
    float endY_;
    QString lineColor_;
    float lineWidth_;
};


// TextShape块
class MODEL_EXPORT TextShapeBlock : public BaseShapeBlock, public IBlock {
public:
    TextShapeBlock() = default;
    
    
    // 实现IBlock接口
    QCborValue toCbor() const override {
        QCborMap map;
        map.insert(QLatin1String("text"), QCborValue(getText()));
        map.insert(QLatin1String("fontFamily"), QCborValue(getFontFamily()));
        map.insert(QLatin1String("fontSize"), QCborValue(getFontSize()));
        return map;
    }
    
    void fromCbor(const QCborValue& cbor) override {
        QCborMap map = cbor.toMap();
        setText(map.value(QLatin1String("text")).toString());
        setFontFamily(map.value(QLatin1String("fontFamily")).toString());
        setFontSize(static_cast<int32_t>(map.value(QLatin1String("fontSize")).toInteger()));
    }
    
    QString name() const override {
        return "TextShape";
    }
    
    QStringList fields() const override {
        return QStringList{QLatin1String("text"), QLatin1String("fontFamily"), QLatin1String("fontSize")};
    }
    
    QString fieldType(const QString& fieldName) const override {
        if (fieldName == QLatin1String("text")) return QLatin1String("string");
        if (fieldName == QLatin1String("fontFamily")) return QLatin1String("string");
        if (fieldName == QLatin1String("fontSize")) return QLatin1String("int32");
        return QLatin1String("");
    }
    
    QList<QSharedPointer<IAnnotation>> annotations() const override {
        
        return QList<QSharedPointer<IAnnotation>>();
    }
    
    QList<QSharedPointer<void>> fieldAnnotation(const QString& fieldName) const override {
        if (fieldName == QLatin1String("text")) {
            return QList<QSharedPointer<void>>();
        }
        if (fieldName == QLatin1String("fontFamily")) {
            return QList<QSharedPointer<void>>();
        }
        if (fieldName == QLatin1String("fontSize")) {
            return QList<QSharedPointer<void>>();
        }
        return QList<QSharedPointer<void>>();
    }
    
    QString description() const override {
        return "Generated from block TextShape";
    }
    
    QString fieldDescription(const QString& fieldName) const override {
        
        return QString();
    }
    
    QVariant value(const QString& fieldName) const override {
        if (fieldName == QLatin1String("text")) return QVariant::fromValue(text_);
        if (fieldName == QLatin1String("fontFamily")) return QVariant::fromValue(fontFamily_);
        if (fieldName == QLatin1String("fontSize")) return QVariant::fromValue(fontSize_);
        return QVariant();
    }
    
    void value(const QString& fieldName, const QVariant& value) override {
        if (fieldName == QLatin1String("text")) {
            text_ = value.value<QString>();
            return;
        }
        if (fieldName == QLatin1String("fontFamily")) {
            fontFamily_ = value.value<QString>();
            return;
        }
        if (fieldName == QLatin1String("fontSize")) {
            fontSize_ = value.value<int32_t>();
            return;
        }
    }
    
    // 特定于TextShape的访问器
        // text字段的访问器
    QString getText() const {
        return text_;
    }
    
    void setText(const QString& value) {
        text_ = value;
    } 

        // fontFamily字段的访问器
    QString getFontFamily() const {
        return fontFamily_;
    }
    
    void setFontFamily(const QString& value) {
        fontFamily_ = value;
    } 

        // fontSize字段的访问器
    int32_t getFontSize() const {
        return fontSize_;
    }
    
    void setFontSize(const int32_t& value) {
        fontSize_ = value;
    } 
    
private:
    QString text_;
    QString fontFamily_;
    int32_t fontSize_;
};


// DrawingConfig结构体

class MODEL_EXPORT DrawingConfigModel : public IModel {
public:
    DrawingConfigModel() = default;
    
    
    // 实现IModel接口
    QCborValue toCbor() const override {
        QCborMap map;
        map.insert(QLatin1String("rectangle"), getRectangle().toCbor());
        map.insert(QLatin1String("circle"), getCircle().toCbor());
        map.insert(QLatin1String("line"), getLine().toCbor());
        map.insert(QLatin1String("text"), getText().toCbor());
        return map;
    }
    
    void fromCbor(const QCborValue& cbor) override {
        QCborMap map = cbor.toMap();
        RectangleShapeBlock rectangle;
        rectangle.fromCbor(map.value(QLatin1String("rectangle")));
        setRectangle(rectangle);
        CircleShapeBlock circle;
        circle.fromCbor(map.value(QLatin1String("circle")));
        setCircle(circle);
        LineShapeBlock line;
        line.fromCbor(map.value(QLatin1String("line")));
        setLine(line);
        TextShapeBlock text;
        text.fromCbor(map.value(QLatin1String("text")));
        setText(text);
    }
    
    QStringList fields() const override {
        return QStringList{QLatin1String("rectangle"), QLatin1String("circle"), QLatin1String("line"), QLatin1String("text")};
    }
    
    QString fieldOriginTypeName(const QString& fieldName) const override {
        if (fieldName == QLatin1String("rectangle")) return QLatin1String("RectangleShape");
        if (fieldName == QLatin1String("circle")) return QLatin1String("CircleShape");
        if (fieldName == QLatin1String("line")) return QLatin1String("LineShape");
        if (fieldName == QLatin1String("text")) return QLatin1String("TextShape");
        return QLatin1String("");
    }
    
    QList<QSharedPointer<IAnnotation>> annotations() const override {
        
        return QList<QSharedPointer<IAnnotation>>();
    }
    
    QList<QSharedPointer<void>> fieldAnnotations(const QString& fieldName) const override {
        if (fieldName == QLatin1String("rectangle")) {
            return QList<QSharedPointer<void>>();
        }
        if (fieldName == QLatin1String("circle")) {
            return QList<QSharedPointer<void>>();
        }
        if (fieldName == QLatin1String("line")) {
            return QList<QSharedPointer<void>>();
        }
        if (fieldName == QLatin1String("text")) {
            return QList<QSharedPointer<void>>();
        }
        return QList<QSharedPointer<void>>();
    }
    
    QString description() const override {
        return "Generated from struct DrawingConfig";
    }
    
    QString fieldDescription(const QString& fieldName) const override {
        
        return QString();
    }
    
    QVariant value(const QString& fieldName) const override {
        if (fieldName == QLatin1String("rectangle")) return QVariant::fromValue(rectangle_);
        if (fieldName == QLatin1String("circle")) return QVariant::fromValue(circle_);
        if (fieldName == QLatin1String("line")) return QVariant::fromValue(line_);
        if (fieldName == QLatin1String("text")) return QVariant::fromValue(text_);
        return QVariant();
    }
    
    void value(const QString& fieldName, const QVariant& value) override {
        if (fieldName == QLatin1String("rectangle")) {
            rectangle_ = value.value<RectangleShapeBlock>();
            return;
        }
        if (fieldName == QLatin1String("circle")) {
            circle_ = value.value<CircleShapeBlock>();
            return;
        }
        if (fieldName == QLatin1String("line")) {
            line_ = value.value<LineShapeBlock>();
            return;
        }
        if (fieldName == QLatin1String("text")) {
            text_ = value.value<TextShapeBlock>();
            return;
        }
    }
    
    // 特定于DrawingConfig的访问器
        // rectangle字段的访问器
    RectangleShapeBlock getRectangle() const {
        return rectangle_;
    }
    
    void setRectangle(const RectangleShapeBlock& value) {
        rectangle_ = value;
    } 

        // circle字段的访问器
    CircleShapeBlock getCircle() const {
        return circle_;
    }
    
    void setCircle(const CircleShapeBlock& value) {
        circle_ = value;
    } 

        // line字段的访问器
    LineShapeBlock getLine() const {
        return line_;
    }
    
    void setLine(const LineShapeBlock& value) {
        line_ = value;
    } 

        // text字段的访问器
    TextShapeBlock getText() const {
        return text_;
    }
    
    void setText(const TextShapeBlock& value) {
        text_ = value;
    } 
    
protected:
    QString modelName() const override {
        return "DrawingConfig";
    }
    
private:
    RectangleShapeBlock rectangle_;
    CircleShapeBlock circle_;
    LineShapeBlock line_;
    TextShapeBlock text_;
    
    // 变更通知
    void notifyChange();
};



} // namespace examples.inheritance

