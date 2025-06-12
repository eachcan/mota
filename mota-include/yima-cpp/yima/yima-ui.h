#pragma once

// 此文件由 Mota 代码生成器自动生成
// 生成时间: 2025-06-11 23:24:40// 源文件: .\mota-include\yima-ui.mota
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

using namespace ymf;

namespace yima {
// Int注解
class MODEL_EXPORT IntAnnotation : public IAnnotation {
public:
    IntAnnotation() = default;
    
    // 实现IAnnotation接口
    QString name() const override {
        return "Int";
    }
    
    QVariant argument(const QString& argumentName) const override {        if (argumentName == QLatin1String("min")) return QVariant::fromValue(min_);        if (argumentName == QLatin1String("max")) return QVariant::fromValue(max_);        if (argumentName == QLatin1String("step")) return QVariant::fromValue(step_);        if (argumentName == QLatin1String("desc")) return QVariant::fromValue(desc_);        return QVariant();
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
private:int32_tmin_;int32_tmax_;int32_tstep_;QStringdesc_;};
Q_DECLARE_METATYPE(IntAnnotation)// Float注解
class MODEL_EXPORT FloatAnnotation : public IAnnotation {
public:
    FloatAnnotation() = default;
    
    // 实现IAnnotation接口
    QString name() const override {
        return "Float";
    }
    
    QVariant argument(const QString& argumentName) const override {        if (argumentName == QLatin1String("min")) return QVariant::fromValue(min_);        if (argumentName == QLatin1String("max")) return QVariant::fromValue(max_);        if (argumentName == QLatin1String("step")) return QVariant::fromValue(step_);        if (argumentName == QLatin1String("desc")) return QVariant::fromValue(desc_);        return QVariant();
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
private:doublemin_;doublemax_;doublestep_;QStringdesc_;};
Q_DECLARE_METATYPE(FloatAnnotation)// Text注解
class MODEL_EXPORT TextAnnotation : public IAnnotation {
public:
    TextAnnotation() = default;
    
    // 实现IAnnotation接口
    QString name() const override {
        return "Text";
    }
    
    QVariant argument(const QString& argumentName) const override {        if (argumentName == QLatin1String("max_length")) return QVariant::fromValue(max_length_);        if (argumentName == QLatin1String("desc")) return QVariant::fromValue(desc_);        if (argumentName == QLatin1String("pattern")) return QVariant::fromValue(pattern_);        return QVariant();
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
private:int32_tmax_length_;QStringdesc_;QStringpattern_;};
Q_DECLARE_METATYPE(TextAnnotation)// Switcher注解
class MODEL_EXPORT SwitcherAnnotation : public IAnnotation {
public:
    SwitcherAnnotation() = default;
    
    // 实现IAnnotation接口
    QString name() const override {
        return "Switcher";
    }
    
    QVariant argument(const QString& argumentName) const override {        if (argumentName == QLatin1String("desc")) return QVariant::fromValue(desc_);        return QVariant();
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
private:QStringdesc_;};
Q_DECLARE_METATYPE(SwitcherAnnotation)// Select注解
class MODEL_EXPORT SelectAnnotation : public IAnnotation {
public:
    SelectAnnotation() = default;
    
    // 实现IAnnotation接口
    QString name() const override {
        return "Select";
    }
    
    QVariant argument(const QString& argumentName) const override {        if (argumentName == QLatin1String("desc")) return QVariant::fromValue(desc_);        if (argumentName == QLatin1String("enumClass")) return QVariant::fromValue(enumClass_);        if (argumentName == QLatin1String("field")) return QVariant::fromValue(field_);        return QVariant();
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
    QString getEnumclass() const {
        return enumClass_;
    }
    
    void setEnumclass(const QString& value) {
        enumClass_ = value;
    } 
    // field字段的访问器
    QString getField() const {
        return field_;
    }
    
    void setField(const QString& value) {
        field_ = value;
    } 
private:QStringdesc_;QStringenumClass_;QStringfield_;};
Q_DECLARE_METATYPE(SelectAnnotation)// EnumValue注解
class MODEL_EXPORT EnumValueAnnotation : public IAnnotation {
public:
    EnumValueAnnotation() = default;
    
    // 实现IAnnotation接口
    QString name() const override {
        return "EnumValue";
    }
    
    QVariant argument(const QString& argumentName) const override {        if (argumentName == QLatin1String("title")) return QVariant::fromValue(title_);        if (argumentName == QLatin1String("desc")) return QVariant::fromValue(desc_);        if (argumentName == QLatin1String("value")) return QVariant::fromValue(value_);        return QVariant();
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
private:QStringtitle_;QStringdesc_;QStringvalue_;};
Q_DECLARE_METATYPE(EnumValueAnnotation)// FolderDialog注解
class MODEL_EXPORT FolderDialogAnnotation : public IAnnotation {
public:
    FolderDialogAnnotation() = default;
    
    // 实现IAnnotation接口
    QString name() const override {
        return "FolderDialog";
    }
    
    QVariant argument(const QString& argumentName) const override {        if (argumentName == QLatin1String("buttonText")) return QVariant::fromValue(buttonText_);        return QVariant();
    }
    
    QStringList argumentNames() const override {
        return QStringList{QLatin1String("buttonText")};
    }
    
    // 特定于FolderDialog的访问器
    // buttonText字段的访问器
    QString getButtontext() const {
        return buttonText_;
    }
    
    void setButtontext(const QString& value) {
        buttonText_ = value;
    } 
private:QStringbuttonText_;};
Q_DECLARE_METATYPE(FolderDialogAnnotation)// FileDialog注解
class MODEL_EXPORT FileDialogAnnotation : public IAnnotation {
public:
    FileDialogAnnotation() = default;
    
    // 实现IAnnotation接口
    QString name() const override {
        return "FileDialog";
    }
    
    QVariant argument(const QString& argumentName) const override {        if (argumentName == QLatin1String("filter")) return QVariant::fromValue(filter_);        if (argumentName == QLatin1String("buttonText")) return QVariant::fromValue(buttonText_);        return QVariant();
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
    QString getButtontext() const {
        return buttonText_;
    }
    
    void setButtontext(const QString& value) {
        buttonText_ = value;
    } 
private:QStringfilter_;QStringbuttonText_;};
Q_DECLARE_METATYPE(FileDialogAnnotation)// ColorPicker注解
class MODEL_EXPORT ColorPickerAnnotation : public IAnnotation {
public:
    ColorPickerAnnotation() = default;
    
    // 实现IAnnotation接口
    QString name() const override {
        return "ColorPicker";
    }
    
    QVariant argument(const QString& argumentName) const override {        if (argumentName == QLatin1String("default_value")) return QVariant::fromValue(default_value_);        if (argumentName == QLatin1String("buttonText")) return QVariant::fromValue(buttonText_);        return QVariant();
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
    QString getButtontext() const {
        return buttonText_;
    }
    
    void setButtontext(const QString& value) {
        buttonText_ = value;
    } 
private:QStringdefault_value_;QStringbuttonText_;};
Q_DECLARE_METATYPE(ColorPickerAnnotation)// Date注解
class MODEL_EXPORT DateAnnotation : public IAnnotation {
public:
    DateAnnotation() = default;
    
    // 实现IAnnotation接口
    QString name() const override {
        return "Date";
    }
    
    QVariant argument(const QString& argumentName) const override {        if (argumentName == QLatin1String("format")) return QVariant::fromValue(format_);        if (argumentName == QLatin1String("buttonText")) return QVariant::fromValue(buttonText_);        return QVariant();
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
    QString getButtontext() const {
        return buttonText_;
    }
    
    void setButtontext(const QString& value) {
        buttonText_ = value;
    } 
private:QStringformat_;QStringbuttonText_;};
Q_DECLARE_METATYPE(DateAnnotation)// Time注解
class MODEL_EXPORT TimeAnnotation : public IAnnotation {
public:
    TimeAnnotation() = default;
    
    // 实现IAnnotation接口
    QString name() const override {
        return "Time";
    }
    
    QVariant argument(const QString& argumentName) const override {        if (argumentName == QLatin1String("format")) return QVariant::fromValue(format_);        if (argumentName == QLatin1String("buttonText")) return QVariant::fromValue(buttonText_);        return QVariant();
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
    QString getButtontext() const {
        return buttonText_;
    }
    
    void setButtontext(const QString& value) {
        buttonText_ = value;
    } 
private:QStringformat_;QStringbuttonText_;};
Q_DECLARE_METATYPE(TimeAnnotation)// DrawRectangle注解
class MODEL_EXPORT DrawRectangleAnnotation : public IAnnotation {
public:
    DrawRectangleAnnotation() = default;
    
    // 实现IAnnotation接口
    QString name() const override {
        return "DrawRectangle";
    }
    
    QVariant argument(const QString& argumentName) const override {        if (argumentName == QLatin1String("buttonText")) return QVariant::fromValue(buttonText_);        return QVariant();
    }
    
    QStringList argumentNames() const override {
        return QStringList{QLatin1String("buttonText")};
    }
    
    // 特定于DrawRectangle的访问器
    // buttonText字段的访问器
    QString getButtontext() const {
        return buttonText_;
    }
    
    void setButtontext(const QString& value) {
        buttonText_ = value;
    } 
private:QStringbuttonText_;};
Q_DECLARE_METATYPE(DrawRectangleAnnotation)// DrawCircle注解
class MODEL_EXPORT DrawCircleAnnotation : public IAnnotation {
public:
    DrawCircleAnnotation() = default;
    
    // 实现IAnnotation接口
    QString name() const override {
        return "DrawCircle";
    }
    
    QVariant argument(const QString& argumentName) const override {        if (argumentName == QLatin1String("buttonText")) return QVariant::fromValue(buttonText_);        return QVariant();
    }
    
    QStringList argumentNames() const override {
        return QStringList{QLatin1String("buttonText")};
    }
    
    // 特定于DrawCircle的访问器
    // buttonText字段的访问器
    QString getButtontext() const {
        return buttonText_;
    }
    
    void setButtontext(const QString& value) {
        buttonText_ = value;
    } 
private:QStringbuttonText_;};
Q_DECLARE_METATYPE(DrawCircleAnnotation)// DrawPolygon注解
class MODEL_EXPORT DrawPolygonAnnotation : public IAnnotation {
public:
    DrawPolygonAnnotation() = default;
    
    // 实现IAnnotation接口
    QString name() const override {
        return "DrawPolygon";
    }
    
    QVariant argument(const QString& argumentName) const override {        if (argumentName == QLatin1String("buttonText")) return QVariant::fromValue(buttonText_);        return QVariant();
    }
    
    QStringList argumentNames() const override {
        return QStringList{QLatin1String("buttonText")};
    }
    
    // 特定于DrawPolygon的访问器
    // buttonText字段的访问器
    QString getButtontext() const {
        return buttonText_;
    }
    
    void setButtontext(const QString& value) {
        buttonText_ = value;
    } 
private:QStringbuttonText_;};
Q_DECLARE_METATYPE(DrawPolygonAnnotation)// DrawLine注解
class MODEL_EXPORT DrawLineAnnotation : public IAnnotation {
public:
    DrawLineAnnotation() = default;
    
    // 实现IAnnotation接口
    QString name() const override {
        return "DrawLine";
    }
    
    QVariant argument(const QString& argumentName) const override {        if (argumentName == QLatin1String("buttonText")) return QVariant::fromValue(buttonText_);        return QVariant();
    }
    
    QStringList argumentNames() const override {
        return QStringList{QLatin1String("buttonText")};
    }
    
    // 特定于DrawLine的访问器
    // buttonText字段的访问器
    QString getButtontext() const {
        return buttonText_;
    }
    
    void setButtontext(const QString& value) {
        buttonText_ = value;
    } 
private:QStringbuttonText_;};
Q_DECLARE_METATYPE(DrawLineAnnotation)// DrawPoint注解
class MODEL_EXPORT DrawPointAnnotation : public IAnnotation {
public:
    DrawPointAnnotation() = default;
    
    // 实现IAnnotation接口
    QString name() const override {
        return "DrawPoint";
    }
    
    QVariant argument(const QString& argumentName) const override {        if (argumentName == QLatin1String("buttonText")) return QVariant::fromValue(buttonText_);        return QVariant();
    }
    
    QStringList argumentNames() const override {
        return QStringList{QLatin1String("buttonText")};
    }
    
    // 特定于DrawPoint的访问器
    // buttonText字段的访问器
    QString getButtontext() const {
        return buttonText_;
    }
    
    void setButtontext(const QString& value) {
        buttonText_ = value;
    } 
private:QStringbuttonText_;};
Q_DECLARE_METATYPE(DrawPointAnnotation)// Label注解
class MODEL_EXPORT LabelAnnotation : public IAnnotation {
public:
    LabelAnnotation() = default;
    
    // 实现IAnnotation接口
    QString name() const override {
        return "Label";
    }
    
    QVariant argument(const QString& argumentName) const override {        if (argumentName == QLatin1String("text")) return QVariant::fromValue(text_);        return QVariant();
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
private:QStringtext_;};
Q_DECLARE_METATYPE(LabelAnnotation)// Validate注解
class MODEL_EXPORT ValidateAnnotation : public IAnnotation {
public:
    ValidateAnnotation() = default;
    
    // 实现IAnnotation接口
    QString name() const override {
        return "Validate";
    }
    
    QVariant argument(const QString& argumentName) const override {        if (argumentName == QLatin1String("rule")) return QVariant::fromValue(rule_);        if (argumentName == QLatin1String("message")) return QVariant::fromValue(message_);        return QVariant();
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
private:QStringrule_;QStringmessage_;};
Q_DECLARE_METATYPE(ValidateAnnotation)// Tooltip注解
class MODEL_EXPORT TooltipAnnotation : public IAnnotation {
public:
    TooltipAnnotation() = default;
    
    // 实现IAnnotation接口
    QString name() const override {
        return "Tooltip";
    }
    
    QVariant argument(const QString& argumentName) const override {        if (argumentName == QLatin1String("text")) return QVariant::fromValue(text_);        if (argumentName == QLatin1String("duration")) return QVariant::fromValue(duration_);        return QVariant();
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
private:QStringtext_;int32_tduration_;};
Q_DECLARE_METATYPE(TooltipAnnotation)// ReadOnly注解
class MODEL_EXPORT ReadOnlyAnnotation : public IAnnotation {
public:
    ReadOnlyAnnotation() = default;
    
    // 实现IAnnotation接口
    QString name() const override {
        return "ReadOnly";
    }
    
    QVariant argument(const QString& argumentName) const override {        return QVariant();
    }
    
    QStringList argumentNames() const override {
        return QStringList{};
    }
    
    // 特定于ReadOnly的访问器
private:};
Q_DECLARE_METATYPE(ReadOnlyAnnotation)// Hidden注解
class MODEL_EXPORT HiddenAnnotation : public IAnnotation {
public:
    HiddenAnnotation() = default;
    
    // 实现IAnnotation接口
    QString name() const override {
        return "Hidden";
    }
    
    QVariant argument(const QString& argumentName) const override {        return QVariant();
    }
    
    QStringList argumentNames() const override {
        return QStringList{};
    }
    
    // 特定于Hidden的访问器
private:};
Q_DECLARE_METATYPE(HiddenAnnotation)}
 
