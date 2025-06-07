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
// 生成时间: 2025-06-07 22:55:14
// 源文件: unknown.mota

using namespace ymf;


namespace examples.validation {


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

// ValidatedForm结构体

class MODEL_EXPORT ValidatedFormModel : public IModel {
public:
    ValidatedFormModel() = default;
    
    
    // 实现IModel接口
    QCborValue toCbor() const override {
        QCborMap map;
        map.insert(QLatin1String("username"), QCborValue(getUsername()));
        map.insert(QLatin1String("password"), QCborValue(getPassword()));
        map.insert(QLatin1String("phone"), QCborValue(getPhone()));
        map.insert(QLatin1String("email"), QCborValue(getEmail()));
        map.insert(QLatin1String("age"), QCborValue(getAge()));
        map.insert(QLatin1String("website"), QCborValue(getWebsite()));
        map.insert(QLatin1String("confirmPassword"), QCborValue(getConfirmPassword()));
        return map;
    }
    
    void fromCbor(const QCborValue& cbor) override {
        QCborMap map = cbor.toMap();
        setUsername(map.value(QLatin1String("username")).toString());
        setPassword(map.value(QLatin1String("password")).toString());
        setPhone(map.value(QLatin1String("phone")).toString());
        setEmail(map.value(QLatin1String("email")).toString());
        setAge(static_cast<int32_t>(map.value(QLatin1String("age")).toInteger()));
        setWebsite(map.value(QLatin1String("website")).toString());
        setConfirmPassword(map.value(QLatin1String("confirmPassword")).toString());
    }
    
    QStringList fields() const override {
        return QStringList{QLatin1String("username"), QLatin1String("password"), QLatin1String("phone"), QLatin1String("email"), QLatin1String("age"), QLatin1String("website"), QLatin1String("confirmPassword")};
    }
    
    QString fieldOriginTypeName(const QString& fieldName) const override {
        if (fieldName == QLatin1String("username")) return QLatin1String("string");
        if (fieldName == QLatin1String("password")) return QLatin1String("string");
        if (fieldName == QLatin1String("phone")) return QLatin1String("string");
        if (fieldName == QLatin1String("email")) return QLatin1String("string");
        if (fieldName == QLatin1String("age")) return QLatin1String("int32");
        if (fieldName == QLatin1String("website")) return QLatin1String("string");
        if (fieldName == QLatin1String("confirmPassword")) return QLatin1String("string");
        return QLatin1String("");
    }
    
    QList<QSharedPointer<IAnnotation>> annotations() const override {
        
        return QList<QSharedPointer<IAnnotation>>();
    }
    
    QList<QSharedPointer<void>> fieldAnnotations(const QString& fieldName) const override {
        if (fieldName == QLatin1String("username")) {
            return QList<QSharedPointer<void>>();
        }
        if (fieldName == QLatin1String("password")) {
            return QList<QSharedPointer<void>>();
        }
        if (fieldName == QLatin1String("phone")) {
            return QList<QSharedPointer<void>>();
        }
        if (fieldName == QLatin1String("email")) {
            return QList<QSharedPointer<void>>();
        }
        if (fieldName == QLatin1String("age")) {
            return QList<QSharedPointer<void>>();
        }
        if (fieldName == QLatin1String("website")) {
            return QList<QSharedPointer<void>>();
        }
        if (fieldName == QLatin1String("confirmPassword")) {
            return QList<QSharedPointer<void>>();
        }
        return QList<QSharedPointer<void>>();
    }
    
    QString description() const override {
        return "Generated from struct ValidatedForm";
    }
    
    QString fieldDescription(const QString& fieldName) const override {
        
        return QString();
    }
    
    QVariant value(const QString& fieldName) const override {
        if (fieldName == QLatin1String("username")) return QVariant::fromValue(username_);
        if (fieldName == QLatin1String("password")) return QVariant::fromValue(password_);
        if (fieldName == QLatin1String("phone")) return QVariant::fromValue(phone_);
        if (fieldName == QLatin1String("email")) return QVariant::fromValue(email_);
        if (fieldName == QLatin1String("age")) return QVariant::fromValue(age_);
        if (fieldName == QLatin1String("website")) return QVariant::fromValue(website_);
        if (fieldName == QLatin1String("confirmPassword")) return QVariant::fromValue(confirmPassword_);
        return QVariant();
    }
    
    void value(const QString& fieldName, const QVariant& value) override {
        if (fieldName == QLatin1String("username")) {
            username_ = value.value<QString>();
            return;
        }
        if (fieldName == QLatin1String("password")) {
            password_ = value.value<QString>();
            return;
        }
        if (fieldName == QLatin1String("phone")) {
            phone_ = value.value<QString>();
            return;
        }
        if (fieldName == QLatin1String("email")) {
            email_ = value.value<QString>();
            return;
        }
        if (fieldName == QLatin1String("age")) {
            age_ = value.value<int32_t>();
            return;
        }
        if (fieldName == QLatin1String("website")) {
            website_ = value.value<QString>();
            return;
        }
        if (fieldName == QLatin1String("confirmPassword")) {
            confirmPassword_ = value.value<QString>();
            return;
        }
    }
    
    // 特定于ValidatedForm的访问器
        // username字段的访问器
    QString getUsername() const {
        return username_;
    }
    
    void setUsername(const QString& value) {
        username_ = value;
    } 

        // password字段的访问器
    QString getPassword() const {
        return password_;
    }
    
    void setPassword(const QString& value) {
        password_ = value;
    } 

        // phone字段的访问器
    QString getPhone() const {
        return phone_;
    }
    
    void setPhone(const QString& value) {
        phone_ = value;
    } 

        // email字段的访问器
    QString getEmail() const {
        return email_;
    }
    
    void setEmail(const QString& value) {
        email_ = value;
    } 

        // age字段的访问器
    int32_t getAge() const {
        return age_;
    }
    
    void setAge(const int32_t& value) {
        age_ = value;
    } 

        // website字段的访问器
    QString getWebsite() const {
        return website_;
    }
    
    void setWebsite(const QString& value) {
        website_ = value;
    } 

        // confirmPassword字段的访问器
    QString getConfirmPassword() const {
        return confirmPassword_;
    }
    
    void setConfirmPassword(const QString& value) {
        confirmPassword_ = value;
    } 
    
protected:
    QString modelName() const override {
        return "ValidatedForm";
    }
    
private:
    QString username_;
    QString password_;
    QString phone_;
    QString email_;
    int32_t age_;
    QString website_;
    QString confirmPassword_;
    
    // 变更通知
    void notifyChange();
};


// ConditionalValidation结构体

class MODEL_EXPORT ConditionalValidationModel : public IModel {
public:
    ConditionalValidationModel() = default;
    
    
    // 实现IModel接口
    QCborValue toCbor() const override {
        QCborMap map;
        map.insert(QLatin1String("needsShipping"), QCborValue(getNeedsShipping()));
        map.insert(QLatin1String("country"), QCborValue(getCountry()));
        map.insert(QLatin1String("shippingAddress"), getShippingAddress().toCbor());
        map.insert(QLatin1String("zipCode"), getZipCode().toCbor());
        return map;
    }
    
    void fromCbor(const QCborValue& cbor) override {
        QCborMap map = cbor.toMap();
        setNeedsShipping(map.value(QLatin1String("needsShipping")).toBool());
        setCountry(map.value(QLatin1String("country")).toString());
        Optional stringBlock shippingAddress;
        shippingAddress.fromCbor(map.value(QLatin1String("shippingAddress")));
        setShippingAddress(shippingAddress);
        Optional stringBlock zipCode;
        zipCode.fromCbor(map.value(QLatin1String("zipCode")));
        setZipCode(zipCode);
    }
    
    QStringList fields() const override {
        return QStringList{QLatin1String("needsShipping"), QLatin1String("country"), QLatin1String("shippingAddress"), QLatin1String("zipCode")};
    }
    
    QString fieldOriginTypeName(const QString& fieldName) const override {
        if (fieldName == QLatin1String("needsShipping")) return QLatin1String("bool");
        if (fieldName == QLatin1String("country")) return QLatin1String("string");
        if (fieldName == QLatin1String("shippingAddress")) return QLatin1String("optional string");
        if (fieldName == QLatin1String("zipCode")) return QLatin1String("optional string");
        return QLatin1String("");
    }
    
    QList<QSharedPointer<IAnnotation>> annotations() const override {
        
        return QList<QSharedPointer<IAnnotation>>();
    }
    
    QList<QSharedPointer<void>> fieldAnnotations(const QString& fieldName) const override {
        if (fieldName == QLatin1String("needsShipping")) {
            return QList<QSharedPointer<void>>();
        }
        if (fieldName == QLatin1String("country")) {
            return QList<QSharedPointer<void>>();
        }
        if (fieldName == QLatin1String("shippingAddress")) {
            return QList<QSharedPointer<void>>();
        }
        if (fieldName == QLatin1String("zipCode")) {
            return QList<QSharedPointer<void>>();
        }
        return QList<QSharedPointer<void>>();
    }
    
    QString description() const override {
        return "Generated from struct ConditionalValidation";
    }
    
    QString fieldDescription(const QString& fieldName) const override {
        
        return QString();
    }
    
    QVariant value(const QString& fieldName) const override {
        if (fieldName == QLatin1String("needsShipping")) return QVariant::fromValue(needsShipping_);
        if (fieldName == QLatin1String("country")) return QVariant::fromValue(country_);
        if (fieldName == QLatin1String("shippingAddress")) return QVariant::fromValue(shippingAddress_);
        if (fieldName == QLatin1String("zipCode")) return QVariant::fromValue(zipCode_);
        return QVariant();
    }
    
    void value(const QString& fieldName, const QVariant& value) override {
        if (fieldName == QLatin1String("needsShipping")) {
            needsShipping_ = value.value<bool>();
            return;
        }
        if (fieldName == QLatin1String("country")) {
            country_ = value.value<QString>();
            return;
        }
        if (fieldName == QLatin1String("shippingAddress")) {
            shippingAddress_ = value.value<Optional stringBlock>();
            return;
        }
        if (fieldName == QLatin1String("zipCode")) {
            zipCode_ = value.value<Optional stringBlock>();
            return;
        }
    }
    
    // 特定于ConditionalValidation的访问器
        // needsShipping字段的访问器
    bool getNeedsShipping() const {
        return needsShipping_;
    }
    
    void setNeedsShipping(const bool& value) {
        needsShipping_ = value;
    } 

        // country字段的访问器
    QString getCountry() const {
        return country_;
    }
    
    void setCountry(const QString& value) {
        country_ = value;
    } 

        // shippingAddress字段的访问器
    Optional stringBlock getShippingAddress() const {
        return shippingAddress_;
    }
    
    void setShippingAddress(const Optional stringBlock& value) {
        shippingAddress_ = value;
    } 

        // zipCode字段的访问器
    Optional stringBlock getZipCode() const {
        return zipCode_;
    }
    
    void setZipCode(const Optional stringBlock& value) {
        zipCode_ = value;
    } 
    
protected:
    QString modelName() const override {
        return "ConditionalValidation";
    }
    
private:
    bool needsShipping_;
    QString country_;
    Optional stringBlock shippingAddress_;
    Optional stringBlock zipCode_;
    
    // 变更通知
    void notifyChange();
};


// AdvancedValidation结构体

class MODEL_EXPORT AdvancedValidationModel : public IModel {
public:
    AdvancedValidationModel() = default;
    
    
    // 实现IModel接口
    QCborValue toCbor() const override {
        QCborMap map;
        map.insert(QLatin1String("creditCardNumber"), QCborValue(getCreditCardNumber()));
        map.insert(QLatin1String("expiryDate"), QCborValue(getExpiryDate()));
        map.insert(QLatin1String("cvv"), QCborValue(getCvv()));
        map.insert(QLatin1String("cardholderName"), QCborValue(getCardholderName()));
        return map;
    }
    
    void fromCbor(const QCborValue& cbor) override {
        QCborMap map = cbor.toMap();
        setCreditCardNumber(map.value(QLatin1String("creditCardNumber")).toString());
        setExpiryDate(map.value(QLatin1String("expiryDate")).toString());
        setCvv(map.value(QLatin1String("cvv")).toString());
        setCardholderName(map.value(QLatin1String("cardholderName")).toString());
    }
    
    QStringList fields() const override {
        return QStringList{QLatin1String("creditCardNumber"), QLatin1String("expiryDate"), QLatin1String("cvv"), QLatin1String("cardholderName")};
    }
    
    QString fieldOriginTypeName(const QString& fieldName) const override {
        if (fieldName == QLatin1String("creditCardNumber")) return QLatin1String("string");
        if (fieldName == QLatin1String("expiryDate")) return QLatin1String("string");
        if (fieldName == QLatin1String("cvv")) return QLatin1String("string");
        if (fieldName == QLatin1String("cardholderName")) return QLatin1String("string");
        return QLatin1String("");
    }
    
    QList<QSharedPointer<IAnnotation>> annotations() const override {
        
        return QList<QSharedPointer<IAnnotation>>();
    }
    
    QList<QSharedPointer<void>> fieldAnnotations(const QString& fieldName) const override {
        if (fieldName == QLatin1String("creditCardNumber")) {
            return QList<QSharedPointer<void>>();
        }
        if (fieldName == QLatin1String("expiryDate")) {
            return QList<QSharedPointer<void>>();
        }
        if (fieldName == QLatin1String("cvv")) {
            return QList<QSharedPointer<void>>();
        }
        if (fieldName == QLatin1String("cardholderName")) {
            return QList<QSharedPointer<void>>();
        }
        return QList<QSharedPointer<void>>();
    }
    
    QString description() const override {
        return "Generated from struct AdvancedValidation";
    }
    
    QString fieldDescription(const QString& fieldName) const override {
        
        return QString();
    }
    
    QVariant value(const QString& fieldName) const override {
        if (fieldName == QLatin1String("creditCardNumber")) return QVariant::fromValue(creditCardNumber_);
        if (fieldName == QLatin1String("expiryDate")) return QVariant::fromValue(expiryDate_);
        if (fieldName == QLatin1String("cvv")) return QVariant::fromValue(cvv_);
        if (fieldName == QLatin1String("cardholderName")) return QVariant::fromValue(cardholderName_);
        return QVariant();
    }
    
    void value(const QString& fieldName, const QVariant& value) override {
        if (fieldName == QLatin1String("creditCardNumber")) {
            creditCardNumber_ = value.value<QString>();
            return;
        }
        if (fieldName == QLatin1String("expiryDate")) {
            expiryDate_ = value.value<QString>();
            return;
        }
        if (fieldName == QLatin1String("cvv")) {
            cvv_ = value.value<QString>();
            return;
        }
        if (fieldName == QLatin1String("cardholderName")) {
            cardholderName_ = value.value<QString>();
            return;
        }
    }
    
    // 特定于AdvancedValidation的访问器
        // creditCardNumber字段的访问器
    QString getCreditCardNumber() const {
        return creditCardNumber_;
    }
    
    void setCreditCardNumber(const QString& value) {
        creditCardNumber_ = value;
    } 

        // expiryDate字段的访问器
    QString getExpiryDate() const {
        return expiryDate_;
    }
    
    void setExpiryDate(const QString& value) {
        expiryDate_ = value;
    } 

        // cvv字段的访问器
    QString getCvv() const {
        return cvv_;
    }
    
    void setCvv(const QString& value) {
        cvv_ = value;
    } 

        // cardholderName字段的访问器
    QString getCardholderName() const {
        return cardholderName_;
    }
    
    void setCardholderName(const QString& value) {
        cardholderName_ = value;
    } 
    
protected:
    QString modelName() const override {
        return "AdvancedValidation";
    }
    
private:
    QString creditCardNumber_;
    QString expiryDate_;
    QString cvv_;
    QString cardholderName_;
    
    // 变更通知
    void notifyChange();
};



} // namespace examples.validation

