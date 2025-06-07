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


namespace examples.ui {


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

// Gender枚举
enum class Gender {
    MALE = 0,
    FEMALE = 1,
    OTHER = 2
};

// Gender辅助函数
namespace GenderHelper {
    // 将枚举值转换为字符串
    inline QString toString(Gender value) {
        switch (value) {
            case Gender::MALE:
                return "MALE";
            case Gender::FEMALE:
                return "FEMALE";
            case Gender::OTHER:
                return "OTHER";
            default:
                return QString();
        }
    }
    
    // 将字符串转换为枚举值
    inline Gender fromString(const QString& str) {
        if (str == "MALE") {
            return Gender::MALE;
        } else if (str == "FEMALE") {
            return Gender::FEMALE;
        } else if (str == "OTHER") {
            return Gender::OTHER;
        }
        return Gender::MALE;
    }
    
    // 获取所有枚举值的字符串表示
    inline QStringList allValues() {
        return QStringList() << "MALE" << "FEMALE" << "OTHER";
    }
    
    // 获取所有枚举值的UI显示名称
    inline QStringList allDisplayNames() {
        return QStringList() << "MALE" << "FEMALE" << "OTHER";
    }
    
    // 获取整个枚举的注解
    inline QList<QSharedPointer<IAnnotation>> annotations() {
        
        return QList<QSharedPointer<IAnnotation>>();
    }
    
    // 获取特定枚举值的注解
    inline QList<QSharedPointer<IAnnotation>> valueAnnotations(Gender value) {
        switch (value) {
            case Gender::MALE:
                return QList<QSharedPointer<IAnnotation>>();
            case Gender::FEMALE:
                return QList<QSharedPointer<IAnnotation>>();
            case Gender::OTHER:
                return QList<QSharedPointer<IAnnotation>>();
            default:
                return QList<QSharedPointer<IAnnotation>>();
        }
    }
    
    // 获取特定枚举值的注解（通过字符串）
    inline QList<QSharedPointer<IAnnotation>> valueAnnotations(const QString& valueName) {
        if (valueName == "MALE") {
            return QList<QSharedPointer<IAnnotation>>();
        } else if (valueName == "FEMALE") {
            return QList<QSharedPointer<IAnnotation>>();
        } else if (valueName == "OTHER") {
            return QList<QSharedPointer<IAnnotation>>();
        }
        return QList<QSharedPointer<IAnnotation>>();
    }
}


// Country枚举
enum class Country {
    CHINA = 0,
    USA = 1,
    JAPAN = 2,
    EUROPE = 3
};

// Country辅助函数
namespace CountryHelper {
    // 将枚举值转换为字符串
    inline QString toString(Country value) {
        switch (value) {
            case Country::CHINA:
                return "CHINA";
            case Country::USA:
                return "USA";
            case Country::JAPAN:
                return "JAPAN";
            case Country::EUROPE:
                return "EUROPE";
            default:
                return QString();
        }
    }
    
    // 将字符串转换为枚举值
    inline Country fromString(const QString& str) {
        if (str == "CHINA") {
            return Country::CHINA;
        } else if (str == "USA") {
            return Country::USA;
        } else if (str == "JAPAN") {
            return Country::JAPAN;
        } else if (str == "EUROPE") {
            return Country::EUROPE;
        }
        return Country::CHINA;
    }
    
    // 获取所有枚举值的字符串表示
    inline QStringList allValues() {
        return QStringList() << "CHINA" << "USA" << "JAPAN" << "EUROPE";
    }
    
    // 获取所有枚举值的UI显示名称
    inline QStringList allDisplayNames() {
        return QStringList() << "CHINA" << "USA" << "JAPAN" << "EUROPE";
    }
    
    // 获取整个枚举的注解
    inline QList<QSharedPointer<IAnnotation>> annotations() {
        
        return QList<QSharedPointer<IAnnotation>>();
    }
    
    // 获取特定枚举值的注解
    inline QList<QSharedPointer<IAnnotation>> valueAnnotations(Country value) {
        switch (value) {
            case Country::CHINA:
                return QList<QSharedPointer<IAnnotation>>();
            case Country::USA:
                return QList<QSharedPointer<IAnnotation>>();
            case Country::JAPAN:
                return QList<QSharedPointer<IAnnotation>>();
            case Country::EUROPE:
                return QList<QSharedPointer<IAnnotation>>();
            default:
                return QList<QSharedPointer<IAnnotation>>();
        }
    }
    
    // 获取特定枚举值的注解（通过字符串）
    inline QList<QSharedPointer<IAnnotation>> valueAnnotations(const QString& valueName) {
        if (valueName == "CHINA") {
            return QList<QSharedPointer<IAnnotation>>();
        } else if (valueName == "USA") {
            return QList<QSharedPointer<IAnnotation>>();
        } else if (valueName == "JAPAN") {
            return QList<QSharedPointer<IAnnotation>>();
        } else if (valueName == "EUROPE") {
            return QList<QSharedPointer<IAnnotation>>();
        }
        return QList<QSharedPointer<IAnnotation>>();
    }
}


// RegistrationForm结构体

class MODEL_EXPORT RegistrationFormModel : public IModel {
public:
    RegistrationFormModel() = default;
    
    
    // 实现IModel接口
    QCborValue toCbor() const override {
        QCborMap map;
        map.insert(QLatin1String("username"), QCborValue(getUsername()));
        map.insert(QLatin1String("password"), QCborValue(getPassword()));
        map.insert(QLatin1String("age"), QCborValue(getAge()));
        map.insert(QLatin1String("volume"), QCborValue(getVolume()));
        map.insert(QLatin1String("country"), QCborValue(static_cast<int>(getCountry())));
        map.insert(QLatin1String("subscribe"), QCborValue(getSubscribe()));
        map.insert(QLatin1String("gender"), QCborValue(static_cast<int>(getGender())));
        map.insert(QLatin1String("birthDate"), QCborValue(getBirthDate()));
        map.insert(QLatin1String("reminderTime"), QCborValue(getReminderTime()));
        map.insert(QLatin1String("themeColor"), QCborValue(getThemeColor()));
        map.insert(QLatin1String("avatar"), QCborValue(getAvatar()));
        map.insert(QLatin1String("notificationsEnabled"), QCborValue(getNotificationsEnabled()));
        return map;
    }
    
    void fromCbor(const QCborValue& cbor) override {
        QCborMap map = cbor.toMap();
        setUsername(map.value(QLatin1String("username")).toString());
        setPassword(map.value(QLatin1String("password")).toString());
        setAge(static_cast<int32_t>(map.value(QLatin1String("age")).toInteger()));
        setVolume(static_cast<int32_t>(map.value(QLatin1String("volume")).toInteger()));
        setCountry(static_cast<Country>(map.value(QLatin1String("country")).toInteger()));
        setSubscribe(map.value(QLatin1String("subscribe")).toBool());
        setGender(static_cast<Gender>(map.value(QLatin1String("gender")).toInteger()));
        setBirthDate(map.value(QLatin1String("birthDate")).toString());
        setReminderTime(map.value(QLatin1String("reminderTime")).toString());
        setThemeColor(map.value(QLatin1String("themeColor")).toString());
        setAvatar(map.value(QLatin1String("avatar")).toString());
        setNotificationsEnabled(map.value(QLatin1String("notificationsEnabled")).toBool());
    }
    
    QStringList fields() const override {
        return QStringList{QLatin1String("username"), QLatin1String("password"), QLatin1String("age"), QLatin1String("volume"), QLatin1String("country"), QLatin1String("subscribe"), QLatin1String("gender"), QLatin1String("birthDate"), QLatin1String("reminderTime"), QLatin1String("themeColor"), QLatin1String("avatar"), QLatin1String("notificationsEnabled")};
    }
    
    QString fieldOriginTypeName(const QString& fieldName) const override {
        if (fieldName == QLatin1String("username")) return QLatin1String("string");
        if (fieldName == QLatin1String("password")) return QLatin1String("string");
        if (fieldName == QLatin1String("age")) return QLatin1String("int32");
        if (fieldName == QLatin1String("volume")) return QLatin1String("int32");
        if (fieldName == QLatin1String("country")) return QLatin1String("Country");
        if (fieldName == QLatin1String("subscribe")) return QLatin1String("bool");
        if (fieldName == QLatin1String("gender")) return QLatin1String("Gender");
        if (fieldName == QLatin1String("birthDate")) return QLatin1String("string");
        if (fieldName == QLatin1String("reminderTime")) return QLatin1String("string");
        if (fieldName == QLatin1String("themeColor")) return QLatin1String("string");
        if (fieldName == QLatin1String("avatar")) return QLatin1String("string");
        if (fieldName == QLatin1String("notificationsEnabled")) return QLatin1String("bool");
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
        if (fieldName == QLatin1String("age")) {
            return QList<QSharedPointer<void>>();
        }
        if (fieldName == QLatin1String("volume")) {
            return QList<QSharedPointer<void>>();
        }
        if (fieldName == QLatin1String("country")) {
            return QList<QSharedPointer<void>>();
        }
        if (fieldName == QLatin1String("subscribe")) {
            return QList<QSharedPointer<void>>();
        }
        if (fieldName == QLatin1String("gender")) {
            return QList<QSharedPointer<void>>();
        }
        if (fieldName == QLatin1String("birthDate")) {
            return QList<QSharedPointer<void>>();
        }
        if (fieldName == QLatin1String("reminderTime")) {
            return QList<QSharedPointer<void>>();
        }
        if (fieldName == QLatin1String("themeColor")) {
            return QList<QSharedPointer<void>>();
        }
        if (fieldName == QLatin1String("avatar")) {
            return QList<QSharedPointer<void>>();
        }
        if (fieldName == QLatin1String("notificationsEnabled")) {
            return QList<QSharedPointer<void>>();
        }
        return QList<QSharedPointer<void>>();
    }
    
    QString description() const override {
        return "Generated from struct RegistrationForm";
    }
    
    QString fieldDescription(const QString& fieldName) const override {
        
        return QString();
    }
    
    QVariant value(const QString& fieldName) const override {
        if (fieldName == QLatin1String("username")) return QVariant::fromValue(username_);
        if (fieldName == QLatin1String("password")) return QVariant::fromValue(password_);
        if (fieldName == QLatin1String("age")) return QVariant::fromValue(age_);
        if (fieldName == QLatin1String("volume")) return QVariant::fromValue(volume_);
        if (fieldName == QLatin1String("country")) return QVariant::fromValue(country_);
        if (fieldName == QLatin1String("subscribe")) return QVariant::fromValue(subscribe_);
        if (fieldName == QLatin1String("gender")) return QVariant::fromValue(gender_);
        if (fieldName == QLatin1String("birthDate")) return QVariant::fromValue(birthDate_);
        if (fieldName == QLatin1String("reminderTime")) return QVariant::fromValue(reminderTime_);
        if (fieldName == QLatin1String("themeColor")) return QVariant::fromValue(themeColor_);
        if (fieldName == QLatin1String("avatar")) return QVariant::fromValue(avatar_);
        if (fieldName == QLatin1String("notificationsEnabled")) return QVariant::fromValue(notificationsEnabled_);
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
        if (fieldName == QLatin1String("age")) {
            age_ = value.value<int32_t>();
            return;
        }
        if (fieldName == QLatin1String("volume")) {
            volume_ = value.value<int32_t>();
            return;
        }
        if (fieldName == QLatin1String("country")) {
            country_ = value.value<Country>();
            return;
        }
        if (fieldName == QLatin1String("subscribe")) {
            subscribe_ = value.value<bool>();
            return;
        }
        if (fieldName == QLatin1String("gender")) {
            gender_ = value.value<Gender>();
            return;
        }
        if (fieldName == QLatin1String("birthDate")) {
            birthDate_ = value.value<QString>();
            return;
        }
        if (fieldName == QLatin1String("reminderTime")) {
            reminderTime_ = value.value<QString>();
            return;
        }
        if (fieldName == QLatin1String("themeColor")) {
            themeColor_ = value.value<QString>();
            return;
        }
        if (fieldName == QLatin1String("avatar")) {
            avatar_ = value.value<QString>();
            return;
        }
        if (fieldName == QLatin1String("notificationsEnabled")) {
            notificationsEnabled_ = value.value<bool>();
            return;
        }
    }
    
    // 特定于RegistrationForm的访问器
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

        // age字段的访问器
    int32_t getAge() const {
        return age_;
    }
    
    void setAge(const int32_t& value) {
        age_ = value;
    } 

        // volume字段的访问器
    int32_t getVolume() const {
        return volume_;
    }
    
    void setVolume(const int32_t& value) {
        volume_ = value;
    } 

        // country字段的访问器
    Country getCountry() const {
        return country_;
    }
    
    void setCountry(const Country& value) {
        country_ = value;
    } 

        // subscribe字段的访问器
    bool getSubscribe() const {
        return subscribe_;
    }
    
    void setSubscribe(const bool& value) {
        subscribe_ = value;
    } 

        // gender字段的访问器
    Gender getGender() const {
        return gender_;
    }
    
    void setGender(const Gender& value) {
        gender_ = value;
    } 

        // birthDate字段的访问器
    QString getBirthDate() const {
        return birthDate_;
    }
    
    void setBirthDate(const QString& value) {
        birthDate_ = value;
    } 

        // reminderTime字段的访问器
    QString getReminderTime() const {
        return reminderTime_;
    }
    
    void setReminderTime(const QString& value) {
        reminderTime_ = value;
    } 

        // themeColor字段的访问器
    QString getThemeColor() const {
        return themeColor_;
    }
    
    void setThemeColor(const QString& value) {
        themeColor_ = value;
    } 

        // avatar字段的访问器
    QString getAvatar() const {
        return avatar_;
    }
    
    void setAvatar(const QString& value) {
        avatar_ = value;
    } 

        // notificationsEnabled字段的访问器
    bool getNotificationsEnabled() const {
        return notificationsEnabled_;
    }
    
    void setNotificationsEnabled(const bool& value) {
        notificationsEnabled_ = value;
    } 
    
protected:
    QString modelName() const override {
        return "RegistrationForm";
    }
    
private:
    QString username_;
    QString password_;
    int32_t age_;
    int32_t volume_;
    Country country_;
    bool subscribe_;
    Gender gender_;
    QString birthDate_;
    QString reminderTime_;
    QString themeColor_;
    QString avatar_;
    bool notificationsEnabled_;
    
    // 变更通知
    void notifyChange();
};



} // namespace examples.ui

