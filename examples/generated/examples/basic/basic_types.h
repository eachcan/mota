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


namespace examples.basic {


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

// BasicTypes结构体

class MODEL_EXPORT BasicTypesModel : public IModel {
public:
    BasicTypesModel() = default;
    
    
    // 实现IModel接口
    QCborValue toCbor() const override {
        QCborMap map;
        map.insert(QLatin1String("int8Value"), QCborValue(getInt8Value()));
        map.insert(QLatin1String("int16Value"), QCborValue(getInt16Value()));
        map.insert(QLatin1String("int32Value"), QCborValue(getInt32Value()));
        map.insert(QLatin1String("int64Value"), QCborValue(getInt64Value()));
        map.insert(QLatin1String("float32Value"), QCborValue(getFloat32Value()));
        map.insert(QLatin1String("float64Value"), QCborValue(getFloat64Value()));
        map.insert(QLatin1String("boolValue"), QCborValue(getBoolValue()));
        map.insert(QLatin1String("stringValue"), QCborValue(getStringValue()));
        return map;
    }
    
    void fromCbor(const QCborValue& cbor) override {
        QCborMap map = cbor.toMap();
        setInt8Value(static_cast<int8_t>(map.value(QLatin1String("int8Value")).toInteger()));
        setInt16Value(static_cast<int16_t>(map.value(QLatin1String("int16Value")).toInteger()));
        setInt32Value(static_cast<int32_t>(map.value(QLatin1String("int32Value")).toInteger()));
        setInt64Value(static_cast<int64_t>(map.value(QLatin1String("int64Value")).toInteger()));
        setFloat32Value(static_cast<float>(map.value(QLatin1String("float32Value")).toDouble()));
        setFloat64Value(static_cast<double>(map.value(QLatin1String("float64Value")).toDouble()));
        setBoolValue(map.value(QLatin1String("boolValue")).toBool());
        setStringValue(map.value(QLatin1String("stringValue")).toString());
    }
    
    QStringList fields() const override {
        return QStringList{QLatin1String("int8Value"), QLatin1String("int16Value"), QLatin1String("int32Value"), QLatin1String("int64Value"), QLatin1String("float32Value"), QLatin1String("float64Value"), QLatin1String("boolValue"), QLatin1String("stringValue")};
    }
    
    QString fieldOriginTypeName(const QString& fieldName) const override {
        if (fieldName == QLatin1String("int8Value")) return QLatin1String("int8");
        if (fieldName == QLatin1String("int16Value")) return QLatin1String("int16");
        if (fieldName == QLatin1String("int32Value")) return QLatin1String("int32");
        if (fieldName == QLatin1String("int64Value")) return QLatin1String("int64");
        if (fieldName == QLatin1String("float32Value")) return QLatin1String("float32");
        if (fieldName == QLatin1String("float64Value")) return QLatin1String("float64");
        if (fieldName == QLatin1String("boolValue")) return QLatin1String("bool");
        if (fieldName == QLatin1String("stringValue")) return QLatin1String("string");
        return QLatin1String("");
    }
    
    QList<QSharedPointer<IAnnotation>> annotations() const override {
        
        return QList<QSharedPointer<IAnnotation>>();
    }
    
    QList<QSharedPointer<void>> fieldAnnotations(const QString& fieldName) const override {
        if (fieldName == QLatin1String("int8Value")) {
            return QList<QSharedPointer<void>>();
        }
        if (fieldName == QLatin1String("int16Value")) {
            return QList<QSharedPointer<void>>();
        }
        if (fieldName == QLatin1String("int32Value")) {
            return QList<QSharedPointer<void>>();
        }
        if (fieldName == QLatin1String("int64Value")) {
            return QList<QSharedPointer<void>>();
        }
        if (fieldName == QLatin1String("float32Value")) {
            return QList<QSharedPointer<void>>();
        }
        if (fieldName == QLatin1String("float64Value")) {
            return QList<QSharedPointer<void>>();
        }
        if (fieldName == QLatin1String("boolValue")) {
            return QList<QSharedPointer<void>>();
        }
        if (fieldName == QLatin1String("stringValue")) {
            return QList<QSharedPointer<void>>();
        }
        return QList<QSharedPointer<void>>();
    }
    
    QString description() const override {
        return "Generated from struct BasicTypes";
    }
    
    QString fieldDescription(const QString& fieldName) const override {
        
        return QString();
    }
    
    QVariant value(const QString& fieldName) const override {
        if (fieldName == QLatin1String("int8Value")) return QVariant::fromValue(int8Value_);
        if (fieldName == QLatin1String("int16Value")) return QVariant::fromValue(int16Value_);
        if (fieldName == QLatin1String("int32Value")) return QVariant::fromValue(int32Value_);
        if (fieldName == QLatin1String("int64Value")) return QVariant::fromValue(int64Value_);
        if (fieldName == QLatin1String("float32Value")) return QVariant::fromValue(float32Value_);
        if (fieldName == QLatin1String("float64Value")) return QVariant::fromValue(float64Value_);
        if (fieldName == QLatin1String("boolValue")) return QVariant::fromValue(boolValue_);
        if (fieldName == QLatin1String("stringValue")) return QVariant::fromValue(stringValue_);
        return QVariant();
    }
    
    void value(const QString& fieldName, const QVariant& value) override {
        if (fieldName == QLatin1String("int8Value")) {
            int8Value_ = value.value<int8_t>();
            return;
        }
        if (fieldName == QLatin1String("int16Value")) {
            int16Value_ = value.value<int16_t>();
            return;
        }
        if (fieldName == QLatin1String("int32Value")) {
            int32Value_ = value.value<int32_t>();
            return;
        }
        if (fieldName == QLatin1String("int64Value")) {
            int64Value_ = value.value<int64_t>();
            return;
        }
        if (fieldName == QLatin1String("float32Value")) {
            float32Value_ = value.value<float>();
            return;
        }
        if (fieldName == QLatin1String("float64Value")) {
            float64Value_ = value.value<double>();
            return;
        }
        if (fieldName == QLatin1String("boolValue")) {
            boolValue_ = value.value<bool>();
            return;
        }
        if (fieldName == QLatin1String("stringValue")) {
            stringValue_ = value.value<QString>();
            return;
        }
    }
    
    // 特定于BasicTypes的访问器
        // int8Value字段的访问器
    int8_t getInt8Value() const {
        return int8Value_;
    }
    
    void setInt8Value(const int8_t& value) {
        int8Value_ = value;
    } 

        // int16Value字段的访问器
    int16_t getInt16Value() const {
        return int16Value_;
    }
    
    void setInt16Value(const int16_t& value) {
        int16Value_ = value;
    } 

        // int32Value字段的访问器
    int32_t getInt32Value() const {
        return int32Value_;
    }
    
    void setInt32Value(const int32_t& value) {
        int32Value_ = value;
    } 

        // int64Value字段的访问器
    int64_t getInt64Value() const {
        return int64Value_;
    }
    
    void setInt64Value(const int64_t& value) {
        int64Value_ = value;
    } 

        // float32Value字段的访问器
    float getFloat32Value() const {
        return float32Value_;
    }
    
    void setFloat32Value(const float& value) {
        float32Value_ = value;
    } 

        // float64Value字段的访问器
    double getFloat64Value() const {
        return float64Value_;
    }
    
    void setFloat64Value(const double& value) {
        float64Value_ = value;
    } 

        // boolValue字段的访问器
    bool getBoolValue() const {
        return boolValue_;
    }
    
    void setBoolValue(const bool& value) {
        boolValue_ = value;
    } 

        // stringValue字段的访问器
    QString getStringValue() const {
        return stringValue_;
    }
    
    void setStringValue(const QString& value) {
        stringValue_ = value;
    } 
    
protected:
    QString modelName() const override {
        return "BasicTypes";
    }
    
private:
    int8_t int8Value_;
    int16_t int16Value_;
    int32_t int32Value_;
    int64_t int64Value_;
    float float32Value_;
    double float64Value_;
    bool boolValue_;
    QString stringValue_;
    
    // 变更通知
    void notifyChange();
};


// ContainerTypes结构体

class MODEL_EXPORT ContainerTypesModel : public IModel {
public:
    ContainerTypesModel() = default;
    
    
    // 实现IModel接口
    QCborValue toCbor() const override {
        QCborMap map;
        QCborArray numbersArray;
        for (const auto& item : getNumbers()) {
            numbersArray.append(QCborValue(item));
        }
        map.insert(QLatin1String("numbers"), numbersArray);
        QCborArray namesArray;
        for (const auto& item : getNames()) {
            namesArray.append(QCborValue(item));
        }
        map.insert(QLatin1String("names"), namesArray);
        map.insert(QLatin1String("middleName"), getMiddleName().toCbor());
        map.insert(QLatin1String("age"), getAge().toCbor());
        return map;
    }
    
    void fromCbor(const QCborValue& cbor) override {
        QCborMap map = cbor.toMap();
        QCborArray numbersArray = map.value(QLatin1String("numbers")).toArray();
        QVector<int32_t> numbers;
        for (const auto& itemValue : numbersArray) {
            numbers.append(static_cast<int32_t>(itemValue.toInteger()));
        }
        setNumbers(numbers);
        QCborArray namesArray = map.value(QLatin1String("names")).toArray();
        QVector<QString> names;
        for (const auto& itemValue : namesArray) {
            names.append(static_cast<QString>(itemValue.toString()));
        }
        setNames(names);
        Optional stringBlock middleName;
        middleName.fromCbor(map.value(QLatin1String("middleName")));
        setMiddleName(middleName);
        Optional int32Block age;
        age.fromCbor(map.value(QLatin1String("age")));
        setAge(age);
    }
    
    QStringList fields() const override {
        return QStringList{QLatin1String("numbers"), QLatin1String("names"), QLatin1String("middleName"), QLatin1String("age")};
    }
    
    QString fieldOriginTypeName(const QString& fieldName) const override {
        if (fieldName == QLatin1String("numbers")) return QLatin1String("repeated int32");
        if (fieldName == QLatin1String("names")) return QLatin1String("repeated string");
        if (fieldName == QLatin1String("middleName")) return QLatin1String("optional string");
        if (fieldName == QLatin1String("age")) return QLatin1String("optional int32");
        return QLatin1String("");
    }
    
    QList<QSharedPointer<IAnnotation>> annotations() const override {
        
        return QList<QSharedPointer<IAnnotation>>();
    }
    
    QList<QSharedPointer<void>> fieldAnnotations(const QString& fieldName) const override {
        if (fieldName == QLatin1String("numbers")) {
            return QList<QSharedPointer<void>>();
        }
        if (fieldName == QLatin1String("names")) {
            return QList<QSharedPointer<void>>();
        }
        if (fieldName == QLatin1String("middleName")) {
            return QList<QSharedPointer<void>>();
        }
        if (fieldName == QLatin1String("age")) {
            return QList<QSharedPointer<void>>();
        }
        return QList<QSharedPointer<void>>();
    }
    
    QString description() const override {
        return "Generated from struct ContainerTypes";
    }
    
    QString fieldDescription(const QString& fieldName) const override {
        
        return QString();
    }
    
    QVariant value(const QString& fieldName) const override {
        if (fieldName == QLatin1String("numbers")) return QVariant::fromValue(numbers_);
        if (fieldName == QLatin1String("names")) return QVariant::fromValue(names_);
        if (fieldName == QLatin1String("middleName")) return QVariant::fromValue(middleName_);
        if (fieldName == QLatin1String("age")) return QVariant::fromValue(age_);
        return QVariant();
    }
    
    void value(const QString& fieldName, const QVariant& value) override {
        if (fieldName == QLatin1String("numbers")) {
            numbers_ = value.value<QVector<int32_t>>();
            return;
        }
        if (fieldName == QLatin1String("names")) {
            names_ = value.value<QVector<QString>>();
            return;
        }
        if (fieldName == QLatin1String("middleName")) {
            middleName_ = value.value<Optional stringBlock>();
            return;
        }
        if (fieldName == QLatin1String("age")) {
            age_ = value.value<Optional int32Block>();
            return;
        }
    }
    
    // 特定于ContainerTypes的访问器
        // numbers字段的访问器
    QVector<int32_t> getNumbers() const {
        return numbers_;
    }
    
    void setNumbers(const QVector<int32_t>& value) {
        numbers_ = value;
    } 

        // names字段的访问器
    QVector<QString> getNames() const {
        return names_;
    }
    
    void setNames(const QVector<QString>& value) {
        names_ = value;
    } 

        // middleName字段的访问器
    Optional stringBlock getMiddleName() const {
        return middleName_;
    }
    
    void setMiddleName(const Optional stringBlock& value) {
        middleName_ = value;
    } 

        // age字段的访问器
    Optional int32Block getAge() const {
        return age_;
    }
    
    void setAge(const Optional int32Block& value) {
        age_ = value;
    } 
    
protected:
    QString modelName() const override {
        return "ContainerTypes";
    }
    
private:
    QVector<int32_t> numbers_;
    QVector<QString> names_;
    Optional stringBlock middleName_;
    Optional int32Block age_;
    
    // 变更通知
    void notifyChange();
};


// StudentScores结构体

class MODEL_EXPORT StudentScoresModel : public IModel {
public:
    StudentScoresModel() = default;
    
    
    // 实现IModel接口
    QCborValue toCbor() const override {
        QCborMap map;
        map.insert(QLatin1String("studentName"), QCborValue(getStudentName()));
        map.insert(QLatin1String("studentId"), QCborValue(getStudentId()));
        map.insert(QLatin1String("mathScore"), QCborValue(getMathScore()));
        map.insert(QLatin1String("englishScore"), QCborValue(getEnglishScore()));
        map.insert(QLatin1String("scienceScore"), QCborValue(getScienceScore()));
        return map;
    }
    
    void fromCbor(const QCborValue& cbor) override {
        QCborMap map = cbor.toMap();
        setStudentName(map.value(QLatin1String("studentName")).toString());
        setStudentId(static_cast<int32_t>(map.value(QLatin1String("studentId")).toInteger()));
        setMathScore(static_cast<int32_t>(map.value(QLatin1String("mathScore")).toInteger()));
        setEnglishScore(static_cast<int32_t>(map.value(QLatin1String("englishScore")).toInteger()));
        setScienceScore(static_cast<int32_t>(map.value(QLatin1String("scienceScore")).toInteger()));
    }
    
    QStringList fields() const override {
        return QStringList{QLatin1String("studentName"), QLatin1String("studentId"), QLatin1String("mathScore"), QLatin1String("englishScore"), QLatin1String("scienceScore")};
    }
    
    QString fieldOriginTypeName(const QString& fieldName) const override {
        if (fieldName == QLatin1String("studentName")) return QLatin1String("string");
        if (fieldName == QLatin1String("studentId")) return QLatin1String("int32");
        if (fieldName == QLatin1String("mathScore")) return QLatin1String("int32");
        if (fieldName == QLatin1String("englishScore")) return QLatin1String("int32");
        if (fieldName == QLatin1String("scienceScore")) return QLatin1String("int32");
        return QLatin1String("");
    }
    
    QList<QSharedPointer<IAnnotation>> annotations() const override {
        
        return QList<QSharedPointer<IAnnotation>>();
    }
    
    QList<QSharedPointer<void>> fieldAnnotations(const QString& fieldName) const override {
        if (fieldName == QLatin1String("studentName")) {
            return QList<QSharedPointer<void>>();
        }
        if (fieldName == QLatin1String("studentId")) {
            return QList<QSharedPointer<void>>();
        }
        if (fieldName == QLatin1String("mathScore")) {
            return QList<QSharedPointer<void>>();
        }
        if (fieldName == QLatin1String("englishScore")) {
            return QList<QSharedPointer<void>>();
        }
        if (fieldName == QLatin1String("scienceScore")) {
            return QList<QSharedPointer<void>>();
        }
        return QList<QSharedPointer<void>>();
    }
    
    QString description() const override {
        return "Generated from struct StudentScores";
    }
    
    QString fieldDescription(const QString& fieldName) const override {
        
        return QString();
    }
    
    QVariant value(const QString& fieldName) const override {
        if (fieldName == QLatin1String("studentName")) return QVariant::fromValue(studentName_);
        if (fieldName == QLatin1String("studentId")) return QVariant::fromValue(studentId_);
        if (fieldName == QLatin1String("mathScore")) return QVariant::fromValue(mathScore_);
        if (fieldName == QLatin1String("englishScore")) return QVariant::fromValue(englishScore_);
        if (fieldName == QLatin1String("scienceScore")) return QVariant::fromValue(scienceScore_);
        return QVariant();
    }
    
    void value(const QString& fieldName, const QVariant& value) override {
        if (fieldName == QLatin1String("studentName")) {
            studentName_ = value.value<QString>();
            return;
        }
        if (fieldName == QLatin1String("studentId")) {
            studentId_ = value.value<int32_t>();
            return;
        }
        if (fieldName == QLatin1String("mathScore")) {
            mathScore_ = value.value<int32_t>();
            return;
        }
        if (fieldName == QLatin1String("englishScore")) {
            englishScore_ = value.value<int32_t>();
            return;
        }
        if (fieldName == QLatin1String("scienceScore")) {
            scienceScore_ = value.value<int32_t>();
            return;
        }
    }
    
    // 特定于StudentScores的访问器
        // studentName字段的访问器
    QString getStudentName() const {
        return studentName_;
    }
    
    void setStudentName(const QString& value) {
        studentName_ = value;
    } 

        // studentId字段的访问器
    int32_t getStudentId() const {
        return studentId_;
    }
    
    void setStudentId(const int32_t& value) {
        studentId_ = value;
    } 

        // mathScore字段的访问器
    int32_t getMathScore() const {
        return mathScore_;
    }
    
    void setMathScore(const int32_t& value) {
        mathScore_ = value;
    } 

        // englishScore字段的访问器
    int32_t getEnglishScore() const {
        return englishScore_;
    }
    
    void setEnglishScore(const int32_t& value) {
        englishScore_ = value;
    } 

        // scienceScore字段的访问器
    int32_t getScienceScore() const {
        return scienceScore_;
    }
    
    void setScienceScore(const int32_t& value) {
        scienceScore_ = value;
    } 
    
protected:
    QString modelName() const override {
        return "StudentScores";
    }
    
private:
    QString studentName_;
    int32_t studentId_;
    int32_t mathScore_;
    int32_t englishScore_;
    int32_t scienceScore_;
    
    // 变更通知
    void notifyChange();
};



} // namespace examples.basic

