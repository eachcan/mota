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


namespace examples.structs {


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

// Point2D块
class MODEL_EXPORT Point2DBlock : public IBlock {
public:
    Point2DBlock() = default;
    
    
    // 实现IBlock接口
    QCborValue toCbor() const override {
        QCborMap map;
        map.insert(QLatin1String("x"), QCborValue(getX()));
        map.insert(QLatin1String("y"), QCborValue(getY()));
        return map;
    }
    
    void fromCbor(const QCborValue& cbor) override {
        QCborMap map = cbor.toMap();
        setX(static_cast<float>(map.value(QLatin1String("x")).toDouble()));
        setY(static_cast<float>(map.value(QLatin1String("y")).toDouble()));
    }
    
    QString name() const override {
        return "Point2D";
    }
    
    QStringList fields() const override {
        return QStringList{QLatin1String("x"), QLatin1String("y")};
    }
    
    QString fieldType(const QString& fieldName) const override {
        if (fieldName == QLatin1String("x")) return QLatin1String("float32");
        if (fieldName == QLatin1String("y")) return QLatin1String("float32");
        return QLatin1String("");
    }
    
    QList<QSharedPointer<IAnnotation>> annotations() const override {
        
        return QList<QSharedPointer<IAnnotation>>();
    }
    
    QList<QSharedPointer<void>> fieldAnnotation(const QString& fieldName) const override {
        if (fieldName == QLatin1String("x")) {
            return QList<QSharedPointer<void>>();
        }
        if (fieldName == QLatin1String("y")) {
            return QList<QSharedPointer<void>>();
        }
        return QList<QSharedPointer<void>>();
    }
    
    QString description() const override {
        return "Generated from block Point2D";
    }
    
    QString fieldDescription(const QString& fieldName) const override {
        
        return QString();
    }
    
    QVariant value(const QString& fieldName) const override {
        if (fieldName == QLatin1String("x")) return QVariant::fromValue(x_);
        if (fieldName == QLatin1String("y")) return QVariant::fromValue(y_);
        return QVariant();
    }
    
    void value(const QString& fieldName, const QVariant& value) override {
        if (fieldName == QLatin1String("x")) {
            x_ = value.value<float>();
            return;
        }
        if (fieldName == QLatin1String("y")) {
            y_ = value.value<float>();
            return;
        }
    }
    
    // 特定于Point2D的访问器
        // x字段的访问器
    float getX() const {
        return x_;
    }
    
    void setX(const float& value) {
        x_ = value;
    } 

        // y字段的访问器
    float getY() const {
        return y_;
    }
    
    void setY(const float& value) {
        y_ = value;
    } 
    
private:
    float x_;
    float y_;
};


// Rectangle块
class MODEL_EXPORT RectangleBlock : public IBlock {
public:
    RectangleBlock() = default;
    
    
    // 实现IBlock接口
    QCborValue toCbor() const override {
        QCborMap map;
        map.insert(QLatin1String("topLeftX"), QCborValue(getTopLeftX()));
        map.insert(QLatin1String("topLeftY"), QCborValue(getTopLeftY()));
        map.insert(QLatin1String("bottomRightX"), QCborValue(getBottomRightX()));
        map.insert(QLatin1String("bottomRightY"), QCborValue(getBottomRightY()));
        map.insert(QLatin1String("label"), getLabel().toCbor());
        return map;
    }
    
    void fromCbor(const QCborValue& cbor) override {
        QCborMap map = cbor.toMap();
        setTopLeftX(static_cast<float>(map.value(QLatin1String("topLeftX")).toDouble()));
        setTopLeftY(static_cast<float>(map.value(QLatin1String("topLeftY")).toDouble()));
        setBottomRightX(static_cast<float>(map.value(QLatin1String("bottomRightX")).toDouble()));
        setBottomRightY(static_cast<float>(map.value(QLatin1String("bottomRightY")).toDouble()));
        Optional stringBlock label;
        label.fromCbor(map.value(QLatin1String("label")));
        setLabel(label);
    }
    
    QString name() const override {
        return "Rectangle";
    }
    
    QStringList fields() const override {
        return QStringList{QLatin1String("topLeftX"), QLatin1String("topLeftY"), QLatin1String("bottomRightX"), QLatin1String("bottomRightY"), QLatin1String("label")};
    }
    
    QString fieldType(const QString& fieldName) const override {
        if (fieldName == QLatin1String("topLeftX")) return QLatin1String("float32");
        if (fieldName == QLatin1String("topLeftY")) return QLatin1String("float32");
        if (fieldName == QLatin1String("bottomRightX")) return QLatin1String("float32");
        if (fieldName == QLatin1String("bottomRightY")) return QLatin1String("float32");
        if (fieldName == QLatin1String("label")) return QLatin1String("optional string");
        return QLatin1String("");
    }
    
    QList<QSharedPointer<IAnnotation>> annotations() const override {
        
        return QList<QSharedPointer<IAnnotation>>();
    }
    
    QList<QSharedPointer<void>> fieldAnnotation(const QString& fieldName) const override {
        if (fieldName == QLatin1String("topLeftX")) {
            return QList<QSharedPointer<void>>();
        }
        if (fieldName == QLatin1String("topLeftY")) {
            return QList<QSharedPointer<void>>();
        }
        if (fieldName == QLatin1String("bottomRightX")) {
            return QList<QSharedPointer<void>>();
        }
        if (fieldName == QLatin1String("bottomRightY")) {
            return QList<QSharedPointer<void>>();
        }
        if (fieldName == QLatin1String("label")) {
            return QList<QSharedPointer<void>>();
        }
        return QList<QSharedPointer<void>>();
    }
    
    QString description() const override {
        return "Generated from block Rectangle";
    }
    
    QString fieldDescription(const QString& fieldName) const override {
        
        return QString();
    }
    
    QVariant value(const QString& fieldName) const override {
        if (fieldName == QLatin1String("topLeftX")) return QVariant::fromValue(topLeftX_);
        if (fieldName == QLatin1String("topLeftY")) return QVariant::fromValue(topLeftY_);
        if (fieldName == QLatin1String("bottomRightX")) return QVariant::fromValue(bottomRightX_);
        if (fieldName == QLatin1String("bottomRightY")) return QVariant::fromValue(bottomRightY_);
        if (fieldName == QLatin1String("label")) return QVariant::fromValue(label_);
        return QVariant();
    }
    
    void value(const QString& fieldName, const QVariant& value) override {
        if (fieldName == QLatin1String("topLeftX")) {
            topLeftX_ = value.value<float>();
            return;
        }
        if (fieldName == QLatin1String("topLeftY")) {
            topLeftY_ = value.value<float>();
            return;
        }
        if (fieldName == QLatin1String("bottomRightX")) {
            bottomRightX_ = value.value<float>();
            return;
        }
        if (fieldName == QLatin1String("bottomRightY")) {
            bottomRightY_ = value.value<float>();
            return;
        }
        if (fieldName == QLatin1String("label")) {
            label_ = value.value<Optional stringBlock>();
            return;
        }
    }
    
    // 特定于Rectangle的访问器
        // topLeftX字段的访问器
    float getTopLeftX() const {
        return topLeftX_;
    }
    
    void setTopLeftX(const float& value) {
        topLeftX_ = value;
    } 

        // topLeftY字段的访问器
    float getTopLeftY() const {
        return topLeftY_;
    }
    
    void setTopLeftY(const float& value) {
        topLeftY_ = value;
    } 

        // bottomRightX字段的访问器
    float getBottomRightX() const {
        return bottomRightX_;
    }
    
    void setBottomRightX(const float& value) {
        bottomRightX_ = value;
    } 

        // bottomRightY字段的访问器
    float getBottomRightY() const {
        return bottomRightY_;
    }
    
    void setBottomRightY(const float& value) {
        bottomRightY_ = value;
    } 

        // label字段的访问器
    Optional stringBlock getLabel() const {
        return label_;
    }
    
    void setLabel(const Optional stringBlock& value) {
        label_ = value;
    } 
    
private:
    float topLeftX_;
    float topLeftY_;
    float bottomRightX_;
    float bottomRightY_;
    Optional stringBlock label_;
};


// Style块
class MODEL_EXPORT StyleBlock : public IBlock {
public:
    StyleBlock() = default;
    
    
    // 实现IBlock接口
    QCborValue toCbor() const override {
        QCborMap map;
        map.insert(QLatin1String("fillColor"), QCborValue(getFillColor()));
        map.insert(QLatin1String("strokeColor"), QCborValue(getStrokeColor()));
        map.insert(QLatin1String("strokeWidth"), QCborValue(getStrokeWidth()));
        return map;
    }
    
    void fromCbor(const QCborValue& cbor) override {
        QCborMap map = cbor.toMap();
        setFillColor(map.value(QLatin1String("fillColor")).toString());
        setStrokeColor(map.value(QLatin1String("strokeColor")).toString());
        setStrokeWidth(static_cast<float>(map.value(QLatin1String("strokeWidth")).toDouble()));
    }
    
    QString name() const override {
        return "Style";
    }
    
    QStringList fields() const override {
        return QStringList{QLatin1String("fillColor"), QLatin1String("strokeColor"), QLatin1String("strokeWidth")};
    }
    
    QString fieldType(const QString& fieldName) const override {
        if (fieldName == QLatin1String("fillColor")) return QLatin1String("string");
        if (fieldName == QLatin1String("strokeColor")) return QLatin1String("string");
        if (fieldName == QLatin1String("strokeWidth")) return QLatin1String("float32");
        return QLatin1String("");
    }
    
    QList<QSharedPointer<IAnnotation>> annotations() const override {
        
        return QList<QSharedPointer<IAnnotation>>();
    }
    
    QList<QSharedPointer<void>> fieldAnnotation(const QString& fieldName) const override {
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
        return "Generated from block Style";
    }
    
    QString fieldDescription(const QString& fieldName) const override {
        
        return QString();
    }
    
    QVariant value(const QString& fieldName) const override {
        if (fieldName == QLatin1String("fillColor")) return QVariant::fromValue(fillColor_);
        if (fieldName == QLatin1String("strokeColor")) return QVariant::fromValue(strokeColor_);
        if (fieldName == QLatin1String("strokeWidth")) return QVariant::fromValue(strokeWidth_);
        return QVariant();
    }
    
    void value(const QString& fieldName, const QVariant& value) override {
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
    
    // 特定于Style的访问器
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
    QString fillColor_;
    QString strokeColor_;
    float strokeWidth_;
};


// ShapeConfig结构体

class MODEL_EXPORT ShapeConfigModel : public IModel {
public:
    ShapeConfigModel() = default;
    
    
    // 实现IModel接口
    QCborValue toCbor() const override {
        QCborMap map;
        map.insert(QLatin1String("name"), QCborValue(getName()));
        map.insert(QLatin1String("rectangle"), getRectangle().toCbor());
        map.insert(QLatin1String("style"), getStyle().toCbor());
        return map;
    }
    
    void fromCbor(const QCborValue& cbor) override {
        QCborMap map = cbor.toMap();
        setName(map.value(QLatin1String("name")).toString());
        RectangleBlock rectangle;
        rectangle.fromCbor(map.value(QLatin1String("rectangle")));
        setRectangle(rectangle);
        StyleBlock style;
        style.fromCbor(map.value(QLatin1String("style")));
        setStyle(style);
    }
    
    QStringList fields() const override {
        return QStringList{QLatin1String("name"), QLatin1String("rectangle"), QLatin1String("style")};
    }
    
    QString fieldOriginTypeName(const QString& fieldName) const override {
        if (fieldName == QLatin1String("name")) return QLatin1String("string");
        if (fieldName == QLatin1String("rectangle")) return QLatin1String("Rectangle");
        if (fieldName == QLatin1String("style")) return QLatin1String("Style");
        return QLatin1String("");
    }
    
    QList<QSharedPointer<IAnnotation>> annotations() const override {
        
        return QList<QSharedPointer<IAnnotation>>();
    }
    
    QList<QSharedPointer<void>> fieldAnnotations(const QString& fieldName) const override {
        if (fieldName == QLatin1String("name")) {
            return QList<QSharedPointer<void>>();
        }
        if (fieldName == QLatin1String("rectangle")) {
            return QList<QSharedPointer<void>>();
        }
        if (fieldName == QLatin1String("style")) {
            return QList<QSharedPointer<void>>();
        }
        return QList<QSharedPointer<void>>();
    }
    
    QString description() const override {
        return "Generated from struct ShapeConfig";
    }
    
    QString fieldDescription(const QString& fieldName) const override {
        
        return QString();
    }
    
    QVariant value(const QString& fieldName) const override {
        if (fieldName == QLatin1String("name")) return QVariant::fromValue(name_);
        if (fieldName == QLatin1String("rectangle")) return QVariant::fromValue(rectangle_);
        if (fieldName == QLatin1String("style")) return QVariant::fromValue(style_);
        return QVariant();
    }
    
    void value(const QString& fieldName, const QVariant& value) override {
        if (fieldName == QLatin1String("name")) {
            name_ = value.value<QString>();
            return;
        }
        if (fieldName == QLatin1String("rectangle")) {
            rectangle_ = value.value<RectangleBlock>();
            return;
        }
        if (fieldName == QLatin1String("style")) {
            style_ = value.value<StyleBlock>();
            return;
        }
    }
    
    // 特定于ShapeConfig的访问器
        // name字段的访问器
    QString getName() const {
        return name_;
    }
    
    void setName(const QString& value) {
        name_ = value;
    } 

        // rectangle字段的访问器
    RectangleBlock getRectangle() const {
        return rectangle_;
    }
    
    void setRectangle(const RectangleBlock& value) {
        rectangle_ = value;
    } 

        // style字段的访问器
    StyleBlock getStyle() const {
        return style_;
    }
    
    void setStyle(const StyleBlock& value) {
        style_ = value;
    } 
    
protected:
    QString modelName() const override {
        return "ShapeConfig";
    }
    
private:
    QString name_;
    RectangleBlock rectangle_;
    StyleBlock style_;
    
    // 变更通知
    void notifyChange();
};


// PolygonConfig结构体

class MODEL_EXPORT PolygonConfigModel : public IModel {
public:
    PolygonConfigModel() = default;
    
    
    // 实现IModel接口
    QCborValue toCbor() const override {
        QCborMap map;
        map.insert(QLatin1String("name"), QCborValue(getName()));
        map.insert(QLatin1String("verticesJson"), QCborValue(getVerticesJson()));
        map.insert(QLatin1String("style"), getStyle().toCbor());
        return map;
    }
    
    void fromCbor(const QCborValue& cbor) override {
        QCborMap map = cbor.toMap();
        setName(map.value(QLatin1String("name")).toString());
        setVerticesJson(map.value(QLatin1String("verticesJson")).toString());
        StyleBlock style;
        style.fromCbor(map.value(QLatin1String("style")));
        setStyle(style);
    }
    
    QStringList fields() const override {
        return QStringList{QLatin1String("name"), QLatin1String("verticesJson"), QLatin1String("style")};
    }
    
    QString fieldOriginTypeName(const QString& fieldName) const override {
        if (fieldName == QLatin1String("name")) return QLatin1String("string");
        if (fieldName == QLatin1String("verticesJson")) return QLatin1String("string");
        if (fieldName == QLatin1String("style")) return QLatin1String("Style");
        return QLatin1String("");
    }
    
    QList<QSharedPointer<IAnnotation>> annotations() const override {
        
        return QList<QSharedPointer<IAnnotation>>();
    }
    
    QList<QSharedPointer<void>> fieldAnnotations(const QString& fieldName) const override {
        if (fieldName == QLatin1String("name")) {
            return QList<QSharedPointer<void>>();
        }
        if (fieldName == QLatin1String("verticesJson")) {
            return QList<QSharedPointer<void>>();
        }
        if (fieldName == QLatin1String("style")) {
            return QList<QSharedPointer<void>>();
        }
        return QList<QSharedPointer<void>>();
    }
    
    QString description() const override {
        return "Generated from struct PolygonConfig";
    }
    
    QString fieldDescription(const QString& fieldName) const override {
        
        return QString();
    }
    
    QVariant value(const QString& fieldName) const override {
        if (fieldName == QLatin1String("name")) return QVariant::fromValue(name_);
        if (fieldName == QLatin1String("verticesJson")) return QVariant::fromValue(verticesJson_);
        if (fieldName == QLatin1String("style")) return QVariant::fromValue(style_);
        return QVariant();
    }
    
    void value(const QString& fieldName, const QVariant& value) override {
        if (fieldName == QLatin1String("name")) {
            name_ = value.value<QString>();
            return;
        }
        if (fieldName == QLatin1String("verticesJson")) {
            verticesJson_ = value.value<QString>();
            return;
        }
        if (fieldName == QLatin1String("style")) {
            style_ = value.value<StyleBlock>();
            return;
        }
    }
    
    // 特定于PolygonConfig的访问器
        // name字段的访问器
    QString getName() const {
        return name_;
    }
    
    void setName(const QString& value) {
        name_ = value;
    } 

        // verticesJson字段的访问器
    QString getVerticesJson() const {
        return verticesJson_;
    }
    
    void setVerticesJson(const QString& value) {
        verticesJson_ = value;
    } 

        // style字段的访问器
    StyleBlock getStyle() const {
        return style_;
    }
    
    void setStyle(const StyleBlock& value) {
        style_ = value;
    } 
    
protected:
    QString modelName() const override {
        return "PolygonConfig";
    }
    
private:
    QString name_;
    QString verticesJson_;
    StyleBlock style_;
    
    // 变更通知
    void notifyChange();
};



} // namespace examples.structs

