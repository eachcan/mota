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


namespace examples.includes {


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

// WindowSettings块
class MODEL_EXPORT WindowSettingsBlock : public IBlock {
public:
    WindowSettingsBlock() = default;
    
    
    // 实现IBlock接口
    QCborValue toCbor() const override {
        QCborMap map;
        map.insert(QLatin1String("width"), QCborValue(getWidth()));
        map.insert(QLatin1String("height"), QCborValue(getHeight()));
        map.insert(QLatin1String("fullscreen"), QCborValue(getFullscreen()));
        return map;
    }
    
    void fromCbor(const QCborValue& cbor) override {
        QCborMap map = cbor.toMap();
        setWidth(static_cast<int32_t>(map.value(QLatin1String("width")).toInteger()));
        setHeight(static_cast<int32_t>(map.value(QLatin1String("height")).toInteger()));
        setFullscreen(map.value(QLatin1String("fullscreen")).toBool());
    }
    
    QString name() const override {
        return "WindowSettings";
    }
    
    QStringList fields() const override {
        return QStringList{QLatin1String("width"), QLatin1String("height"), QLatin1String("fullscreen")};
    }
    
    QString fieldType(const QString& fieldName) const override {
        if (fieldName == QLatin1String("width")) return QLatin1String("int32");
        if (fieldName == QLatin1String("height")) return QLatin1String("int32");
        if (fieldName == QLatin1String("fullscreen")) return QLatin1String("bool");
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
        if (fieldName == QLatin1String("fullscreen")) {
            return QList<QSharedPointer<void>>();
        }
        return QList<QSharedPointer<void>>();
    }
    
    QString description() const override {
        return "Generated from block WindowSettings";
    }
    
    QString fieldDescription(const QString& fieldName) const override {
        
        return QString();
    }
    
    QVariant value(const QString& fieldName) const override {
        if (fieldName == QLatin1String("width")) return QVariant::fromValue(width_);
        if (fieldName == QLatin1String("height")) return QVariant::fromValue(height_);
        if (fieldName == QLatin1String("fullscreen")) return QVariant::fromValue(fullscreen_);
        return QVariant();
    }
    
    void value(const QString& fieldName, const QVariant& value) override {
        if (fieldName == QLatin1String("width")) {
            width_ = value.value<int32_t>();
            return;
        }
        if (fieldName == QLatin1String("height")) {
            height_ = value.value<int32_t>();
            return;
        }
        if (fieldName == QLatin1String("fullscreen")) {
            fullscreen_ = value.value<bool>();
            return;
        }
    }
    
    // 特定于WindowSettings的访问器
        // width字段的访问器
    int32_t getWidth() const {
        return width_;
    }
    
    void setWidth(const int32_t& value) {
        width_ = value;
    } 

        // height字段的访问器
    int32_t getHeight() const {
        return height_;
    }
    
    void setHeight(const int32_t& value) {
        height_ = value;
    } 

        // fullscreen字段的访问器
    bool getFullscreen() const {
        return fullscreen_;
    }
    
    void setFullscreen(const bool& value) {
        fullscreen_ = value;
    } 
    
private:
    int32_t width_;
    int32_t height_;
    bool fullscreen_;
};


// DebugSettings块
class MODEL_EXPORT DebugSettingsBlock : public IBlock {
public:
    DebugSettingsBlock() = default;
    
    
    // 实现IBlock接口
    QCborValue toCbor() const override {
        QCborMap map;
        map.insert(QLatin1String("enableDebugTools"), QCborValue(getEnableDebugTools()));
        map.insert(QLatin1String("showFPS"), QCborValue(getShowFPS()));
        map.insert(QLatin1String("logLevel"), QCborValue(getLogLevel()));
        return map;
    }
    
    void fromCbor(const QCborValue& cbor) override {
        QCborMap map = cbor.toMap();
        setEnableDebugTools(map.value(QLatin1String("enableDebugTools")).toBool());
        setShowFPS(map.value(QLatin1String("showFPS")).toBool());
        setLogLevel(map.value(QLatin1String("logLevel")).toString());
    }
    
    QString name() const override {
        return "DebugSettings";
    }
    
    QStringList fields() const override {
        return QStringList{QLatin1String("enableDebugTools"), QLatin1String("showFPS"), QLatin1String("logLevel")};
    }
    
    QString fieldType(const QString& fieldName) const override {
        if (fieldName == QLatin1String("enableDebugTools")) return QLatin1String("bool");
        if (fieldName == QLatin1String("showFPS")) return QLatin1String("bool");
        if (fieldName == QLatin1String("logLevel")) return QLatin1String("string");
        return QLatin1String("");
    }
    
    QList<QSharedPointer<IAnnotation>> annotations() const override {
        
        return QList<QSharedPointer<IAnnotation>>();
    }
    
    QList<QSharedPointer<void>> fieldAnnotation(const QString& fieldName) const override {
        if (fieldName == QLatin1String("enableDebugTools")) {
            return QList<QSharedPointer<void>>();
        }
        if (fieldName == QLatin1String("showFPS")) {
            return QList<QSharedPointer<void>>();
        }
        if (fieldName == QLatin1String("logLevel")) {
            return QList<QSharedPointer<void>>();
        }
        return QList<QSharedPointer<void>>();
    }
    
    QString description() const override {
        return "Generated from block DebugSettings";
    }
    
    QString fieldDescription(const QString& fieldName) const override {
        
        return QString();
    }
    
    QVariant value(const QString& fieldName) const override {
        if (fieldName == QLatin1String("enableDebugTools")) return QVariant::fromValue(enableDebugTools_);
        if (fieldName == QLatin1String("showFPS")) return QVariant::fromValue(showFPS_);
        if (fieldName == QLatin1String("logLevel")) return QVariant::fromValue(logLevel_);
        return QVariant();
    }
    
    void value(const QString& fieldName, const QVariant& value) override {
        if (fieldName == QLatin1String("enableDebugTools")) {
            enableDebugTools_ = value.value<bool>();
            return;
        }
        if (fieldName == QLatin1String("showFPS")) {
            showFPS_ = value.value<bool>();
            return;
        }
        if (fieldName == QLatin1String("logLevel")) {
            logLevel_ = value.value<QString>();
            return;
        }
    }
    
    // 特定于DebugSettings的访问器
        // enableDebugTools字段的访问器
    bool getEnableDebugTools() const {
        return enableDebugTools_;
    }
    
    void setEnableDebugTools(const bool& value) {
        enableDebugTools_ = value;
    } 

        // showFPS字段的访问器
    bool getShowFPS() const {
        return showFPS_;
    }
    
    void setShowFPS(const bool& value) {
        showFPS_ = value;
    } 

        // logLevel字段的访问器
    QString getLogLevel() const {
        return logLevel_;
    }
    
    void setLogLevel(const QString& value) {
        logLevel_ = value;
    } 
    
private:
    bool enableDebugTools_;
    bool showFPS_;
    QString logLevel_;
};


// OldAppConfig结构体

class MODEL_EXPORT OldAppConfigModel : public IModel {
public:
    OldAppConfigModel() = default;
    
    
    // 实现IModel接口
    QCborValue toCbor() const override {
        QCborMap map;
        map.insert(QLatin1String("appName"), QCborValue(getAppName()));
        map.insert(QLatin1String("version"), QCborValue(getVersion()));
        return map;
    }
    
    void fromCbor(const QCborValue& cbor) override {
        QCborMap map = cbor.toMap();
        setAppName(map.value(QLatin1String("appName")).toString());
        setVersion(map.value(QLatin1String("version")).toString());
    }
    
    QStringList fields() const override {
        return QStringList{QLatin1String("appName"), QLatin1String("version")};
    }
    
    QString fieldOriginTypeName(const QString& fieldName) const override {
        if (fieldName == QLatin1String("appName")) return QLatin1String("string");
        if (fieldName == QLatin1String("version")) return QLatin1String("string");
        return QLatin1String("");
    }
    
    QList<QSharedPointer<IAnnotation>> annotations() const override {
        
        return QList<QSharedPointer<IAnnotation>>();
    }
    
    QList<QSharedPointer<void>> fieldAnnotations(const QString& fieldName) const override {
        if (fieldName == QLatin1String("appName")) {
            return QList<QSharedPointer<void>>();
        }
        if (fieldName == QLatin1String("version")) {
            return QList<QSharedPointer<void>>();
        }
        return QList<QSharedPointer<void>>();
    }
    
    QString description() const override {
        return "Generated from struct OldAppConfig";
    }
    
    QString fieldDescription(const QString& fieldName) const override {
        
        return QString();
    }
    
    QVariant value(const QString& fieldName) const override {
        if (fieldName == QLatin1String("appName")) return QVariant::fromValue(appName_);
        if (fieldName == QLatin1String("version")) return QVariant::fromValue(version_);
        return QVariant();
    }
    
    void value(const QString& fieldName, const QVariant& value) override {
        if (fieldName == QLatin1String("appName")) {
            appName_ = value.value<QString>();
            return;
        }
        if (fieldName == QLatin1String("version")) {
            version_ = value.value<QString>();
            return;
        }
    }
    
    // 特定于OldAppConfig的访问器
        // appName字段的访问器
    QString getAppName() const {
        return appName_;
    }
    
    void setAppName(const QString& value) {
        appName_ = value;
    } 

        // version字段的访问器
    QString getVersion() const {
        return version_;
    }
    
    void setVersion(const QString& value) {
        version_ = value;
    } 
    
protected:
    QString modelName() const override {
        return "OldAppConfig";
    }
    
private:
    QString appName_;
    QString version_;
    
    // 变更通知
    void notifyChange();
};


// NewAppConfig结构体

class MODEL_EXPORT NewAppConfigModel : public IModel {
public:
    NewAppConfigModel() = default;
    
    
    // 实现IModel接口
    QCborValue toCbor() const override {
        QCborMap map;
        map.insert(QLatin1String("appName"), QCborValue(getAppName()));
        map.insert(QLatin1String("version"), QCborValue(getVersion()));
        return map;
    }
    
    void fromCbor(const QCborValue& cbor) override {
        QCborMap map = cbor.toMap();
        setAppName(map.value(QLatin1String("appName")).toString());
        setVersion(map.value(QLatin1String("version")).toString());
    }
    
    QStringList fields() const override {
        return QStringList{QLatin1String("appName"), QLatin1String("version")};
    }
    
    QString fieldOriginTypeName(const QString& fieldName) const override {
        if (fieldName == QLatin1String("appName")) return QLatin1String("string");
        if (fieldName == QLatin1String("version")) return QLatin1String("string");
        return QLatin1String("");
    }
    
    QList<QSharedPointer<IAnnotation>> annotations() const override {
        
        return QList<QSharedPointer<IAnnotation>>();
    }
    
    QList<QSharedPointer<void>> fieldAnnotations(const QString& fieldName) const override {
        if (fieldName == QLatin1String("appName")) {
            return QList<QSharedPointer<void>>();
        }
        if (fieldName == QLatin1String("version")) {
            return QList<QSharedPointer<void>>();
        }
        return QList<QSharedPointer<void>>();
    }
    
    QString description() const override {
        return "Generated from struct NewAppConfig";
    }
    
    QString fieldDescription(const QString& fieldName) const override {
        
        return QString();
    }
    
    QVariant value(const QString& fieldName) const override {
        if (fieldName == QLatin1String("appName")) return QVariant::fromValue(appName_);
        if (fieldName == QLatin1String("version")) return QVariant::fromValue(version_);
        return QVariant();
    }
    
    void value(const QString& fieldName, const QVariant& value) override {
        if (fieldName == QLatin1String("appName")) {
            appName_ = value.value<QString>();
            return;
        }
        if (fieldName == QLatin1String("version")) {
            version_ = value.value<QString>();
            return;
        }
    }
    
    // 特定于NewAppConfig的访问器
        // appName字段的访问器
    QString getAppName() const {
        return appName_;
    }
    
    void setAppName(const QString& value) {
        appName_ = value;
    } 

        // version字段的访问器
    QString getVersion() const {
        return version_;
    }
    
    void setVersion(const QString& value) {
        version_ = value;
    } 
    
protected:
    QString modelName() const override {
        return "NewAppConfig";
    }
    
private:
    QString appName_;
    QString version_;
    
    // 变更通知
    void notifyChange();
};


// StartupConfig结构体

class MODEL_EXPORT StartupConfigModel : public IModel {
public:
    StartupConfigModel() = default;
    
    
    // 实现IModel接口
    QCborValue toCbor() const override {
        QCborMap map;
        map.insert(QLatin1String("showWelcome"), QCborValue(getShowWelcome()));
        map.insert(QLatin1String("checkForUpdates"), QCborValue(getCheckForUpdates()));
        return map;
    }
    
    void fromCbor(const QCborValue& cbor) override {
        QCborMap map = cbor.toMap();
        setShowWelcome(map.value(QLatin1String("showWelcome")).toBool());
        setCheckForUpdates(map.value(QLatin1String("checkForUpdates")).toBool());
    }
    
    QStringList fields() const override {
        return QStringList{QLatin1String("showWelcome"), QLatin1String("checkForUpdates")};
    }
    
    QString fieldOriginTypeName(const QString& fieldName) const override {
        if (fieldName == QLatin1String("showWelcome")) return QLatin1String("bool");
        if (fieldName == QLatin1String("checkForUpdates")) return QLatin1String("bool");
        return QLatin1String("");
    }
    
    QList<QSharedPointer<IAnnotation>> annotations() const override {
        
        return QList<QSharedPointer<IAnnotation>>();
    }
    
    QList<QSharedPointer<void>> fieldAnnotations(const QString& fieldName) const override {
        if (fieldName == QLatin1String("showWelcome")) {
            return QList<QSharedPointer<void>>();
        }
        if (fieldName == QLatin1String("checkForUpdates")) {
            return QList<QSharedPointer<void>>();
        }
        return QList<QSharedPointer<void>>();
    }
    
    QString description() const override {
        return "Generated from struct StartupConfig";
    }
    
    QString fieldDescription(const QString& fieldName) const override {
        
        return QString();
    }
    
    QVariant value(const QString& fieldName) const override {
        if (fieldName == QLatin1String("showWelcome")) return QVariant::fromValue(showWelcome_);
        if (fieldName == QLatin1String("checkForUpdates")) return QVariant::fromValue(checkForUpdates_);
        return QVariant();
    }
    
    void value(const QString& fieldName, const QVariant& value) override {
        if (fieldName == QLatin1String("showWelcome")) {
            showWelcome_ = value.value<bool>();
            return;
        }
        if (fieldName == QLatin1String("checkForUpdates")) {
            checkForUpdates_ = value.value<bool>();
            return;
        }
    }
    
    // 特定于StartupConfig的访问器
        // showWelcome字段的访问器
    bool getShowWelcome() const {
        return showWelcome_;
    }
    
    void setShowWelcome(const bool& value) {
        showWelcome_ = value;
    } 

        // checkForUpdates字段的访问器
    bool getCheckForUpdates() const {
        return checkForUpdates_;
    }
    
    void setCheckForUpdates(const bool& value) {
        checkForUpdates_ = value;
    } 
    
protected:
    QString modelName() const override {
        return "StartupConfig";
    }
    
private:
    bool showWelcome_;
    bool checkForUpdates_;
    
    // 变更通知
    void notifyChange();
};


// AppConfig结构体

class MODEL_EXPORT AppConfigModel : public IModel {
public:
    AppConfigModel() = default;
    
    
    // 实现IModel接口
    QCborValue toCbor() const override {
        QCborMap map;
        map.insert(QLatin1String("window"), getWindow().toCbor());
        map.insert(QLatin1String("debug"), getDebug().toCbor());
        map.insert(QLatin1String("logLevel"), QCborValue(getLogLevel()));
        map.insert(QLatin1String("cameraConfig"), QCborValue(getCameraConfig()));
        return map;
    }
    
    void fromCbor(const QCborValue& cbor) override {
        QCborMap map = cbor.toMap();
        WindowSettingsBlock window;
        window.fromCbor(map.value(QLatin1String("window")));
        setWindow(window);
        DebugSettingsBlock debug;
        debug.fromCbor(map.value(QLatin1String("debug")));
        setDebug(debug);
        setLogLevel(map.value(QLatin1String("logLevel")).toString());
        setCameraConfig(map.value(QLatin1String("cameraConfig")).toString());
    }
    
    QStringList fields() const override {
        return QStringList{QLatin1String("window"), QLatin1String("debug"), QLatin1String("logLevel"), QLatin1String("cameraConfig")};
    }
    
    QString fieldOriginTypeName(const QString& fieldName) const override {
        if (fieldName == QLatin1String("window")) return QLatin1String("WindowSettings");
        if (fieldName == QLatin1String("debug")) return QLatin1String("DebugSettings");
        if (fieldName == QLatin1String("logLevel")) return QLatin1String("string");
        if (fieldName == QLatin1String("cameraConfig")) return QLatin1String("string");
        return QLatin1String("");
    }
    
    QList<QSharedPointer<IAnnotation>> annotations() const override {
        
        return QList<QSharedPointer<IAnnotation>>();
    }
    
    QList<QSharedPointer<void>> fieldAnnotations(const QString& fieldName) const override {
        if (fieldName == QLatin1String("window")) {
            return QList<QSharedPointer<void>>();
        }
        if (fieldName == QLatin1String("debug")) {
            return QList<QSharedPointer<void>>();
        }
        if (fieldName == QLatin1String("logLevel")) {
            return QList<QSharedPointer<void>>();
        }
        if (fieldName == QLatin1String("cameraConfig")) {
            return QList<QSharedPointer<void>>();
        }
        return QList<QSharedPointer<void>>();
    }
    
    QString description() const override {
        return "Generated from struct AppConfig";
    }
    
    QString fieldDescription(const QString& fieldName) const override {
        
        return QString();
    }
    
    QVariant value(const QString& fieldName) const override {
        if (fieldName == QLatin1String("window")) return QVariant::fromValue(window_);
        if (fieldName == QLatin1String("debug")) return QVariant::fromValue(debug_);
        if (fieldName == QLatin1String("logLevel")) return QVariant::fromValue(logLevel_);
        if (fieldName == QLatin1String("cameraConfig")) return QVariant::fromValue(cameraConfig_);
        return QVariant();
    }
    
    void value(const QString& fieldName, const QVariant& value) override {
        if (fieldName == QLatin1String("window")) {
            window_ = value.value<WindowSettingsBlock>();
            return;
        }
        if (fieldName == QLatin1String("debug")) {
            debug_ = value.value<DebugSettingsBlock>();
            return;
        }
        if (fieldName == QLatin1String("logLevel")) {
            logLevel_ = value.value<QString>();
            return;
        }
        if (fieldName == QLatin1String("cameraConfig")) {
            cameraConfig_ = value.value<QString>();
            return;
        }
    }
    
    // 特定于AppConfig的访问器
        // window字段的访问器
    WindowSettingsBlock getWindow() const {
        return window_;
    }
    
    void setWindow(const WindowSettingsBlock& value) {
        window_ = value;
    } 

        // debug字段的访问器
    DebugSettingsBlock getDebug() const {
        return debug_;
    }
    
    void setDebug(const DebugSettingsBlock& value) {
        debug_ = value;
    } 

        // logLevel字段的访问器
    QString getLogLevel() const {
        return logLevel_;
    }
    
    void setLogLevel(const QString& value) {
        logLevel_ = value;
    } 

        // cameraConfig字段的访问器
    QString getCameraConfig() const {
        return cameraConfig_;
    }
    
    void setCameraConfig(const QString& value) {
        cameraConfig_ = value;
    } 
    
protected:
    QString modelName() const override {
        return "AppConfig";
    }
    
private:
    WindowSettingsBlock window_;
    DebugSettingsBlock debug_;
    QString logLevel_;
    QString cameraConfig_;
    
    // 变更通知
    void notifyChange();
};



} // namespace examples.includes

