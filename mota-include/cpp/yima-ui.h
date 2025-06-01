#pragma once

#include "IAnnotation.h"

using namespace ymf;

// 整数输入框注解
class IntAnnotation : public IAnnotation {
public:
    // 获取注解名称
    QString name() const override {
        return "int";
    }

    // 获取注解的参数
    QVariant argument(const QString& name) const override {
        if (name == "min") return getMin();
        if (name == "max") return getMax();
        if (name == "step") return getStep();
        if (name == "desc") return getDesc();
        return QVariant();
    }

    // 获取注解的参数名称
    QStringList argumentNames() const override {
        return QStringList() << "min" << "max" << "step" << "desc";
    }

    int getMin() const {
        return m_min;
    }

    void setMin(int value) {
        m_min = value;
    }

    int getMax() const {
        return m_max;
    }

    void setMax(int value) {
        m_max = value;
    }

    int getStep() const {
        return m_step;
    }

    void setStep(int value) {
        m_step = value;
    }

    QString getDesc() const {
        return m_desc;
    }

    void setDesc(QString value) {
        m_desc = value;
    }

private:
    int m_min = 0;
    int m_max = 0;
    int m_step = 1;
    QString m_desc;
};

// 浮点数输入框注解
class FloatAnnotation : public IAnnotation {
public:
    // 获取注解名称
    QString name() const override {
        return "float";
    }

    // 获取注解的参数
    QVariant argument(const QString& name) const override {
        if (name == "min") return getMin();
        if (name == "max") return getMax();
        if (name == "step") return getStep();
        if (name == "desc") return getDesc();
        return QVariant();
    }

    // 获取注解的参数名称
    QStringList argumentNames() const override {
        return QStringList() << "min" << "max" << "step" << "desc";
    }

    double getMin() const {
        return m_min;
    }

    void setMin(double value) {
        m_min = value;
    }

    double getMax() const {
        return m_max;
    }

    void setMax(double value) {
        m_max = value;
    }

    double getStep() const {
        return m_step;
    }

    void setStep(double value) {
        m_step = value;
    }

    QString getDesc() const {
        return m_desc;
    }

    void setDesc(QString value) {
        m_desc = value;
    }

private:
    double m_min = 0.0;
    double m_max = 0.0;
    double m_step = 0.1;
    QString m_desc;
};

// 文本输入框注解
class TextAnnotation : public IAnnotation {
public:
    // 获取注解名称
    QString name() const override {
        return "text";
    }

    // 获取注解的参数
    QVariant argument(const QString& name) const override {
        if (name == "max_length") return getMaxLength();
        if (name == "desc") return getDesc();
        if (name == "pattern") return getPattern();
        return QVariant();
    }

    // 获取注解的参数名称
    QStringList argumentNames() const override {
        return QStringList() << "max_length" << "desc" << "pattern";
    }

    int getMaxLength() const {
        return m_maxLength;
    }

    void setMaxLength(int value) {
        m_maxLength = value;
    }

    QString getDesc() const {
        return m_desc;
    }

    void setDesc(QString value) {
        m_desc = value;
    }

    QString getPattern() const {
        return m_pattern;
    }

    void setPattern(QString value) {
        m_pattern = value;
    }

private:
    int m_maxLength = 0;
    QString m_desc;
    QString m_pattern;
};

// 开关控件注解
class SwitcherAnnotation : public IAnnotation {
public:
    // 获取注解名称
    QString name() const override {
        return "switcher";
    }

    // 获取注解的参数
    QVariant argument(const QString& name) const override {
        if (name == "desc") return getDesc();
        return QVariant();
    }

    // 获取注解的参数名称
    QStringList argumentNames() const override {
        return QStringList() << "desc";
    }

    QString getDesc() const {
        return m_desc;
    }

    void setDesc(QString value) {
        m_desc = value;
    }

private:
    QString m_desc;
};

// 选择框注解
class SelectAnnotation : public IAnnotation {
public:
    // 获取注解名称
    QString name() const override {
        return "select";
    }

    // 获取注解的参数
    QVariant argument(const QString& name) const override {
        if (name == "desc") return getDesc();
        if (name == "enumClass") return getEnumClass();
        if (name == "field") return getField();
        return QVariant();
    }

    // 获取注解的参数名称
    QStringList argumentNames() const override {
        return QStringList() << "desc" << "enumClass" << "field";
    }

    QString getDesc() const {
        return m_desc;
    }

    void setDesc(QString value) {
        m_desc = value;
    }

    QString getEnumClass() const {
        return m_enumClass;
    }

    void setEnumClass(QString value) {
        m_enumClass = value;
    }

    QString getField() const {
        return m_field;
    }

    void setField(QString value) {
        m_field = value;
    }

private:
    QString m_desc;
    QString m_enumClass;
    QString m_field;
};

// 枚举值注解
class EnumValueAnnotation : public IAnnotation {
public:
    // 获取注解名称
    QString name() const override {
        return "enumvalue";
    }

    // 获取注解的参数
    QVariant argument(const QString& name) const override {
        if (name == "title") return getTitle();
        if (name == "desc") return getDesc();
        if (name == "value") return getValue();
        return QVariant();
    }

    // 获取注解的参数名称
    QStringList argumentNames() const override {
        return QStringList() << "title" << "desc" << "value";
    }

    QString getTitle() const {
        return m_title;
    }

    void setTitle(QString value) {
        m_title = value;
    }

    QString getDesc() const {
        return m_desc;
    }

    void setDesc(QString value) {
        m_desc = value;
    }

    QString getValue() const {
        return m_value;
    }

    void setValue(QString value) {
        m_value = value;
    }

private:
    QString m_title;
    QString m_desc;
    QString m_value;
};

// 文件夹选择对话框注解
class FolderDialogAnnotation : public IAnnotation {
public:
    // 获取注解名称
    QString name() const override {
        return "folderdialog";
    }

    // 获取注解的参数
    QVariant argument(const QString& name) const override {
        if (name == "desc") return getDesc();
        return QVariant();
    }

    // 获取注解的参数名称
    QStringList argumentNames() const override {
        return QStringList() << "desc";
    }

    QString getDesc() const {
        return m_desc;
    }

    void setDesc(QString value) {
        m_desc = value;
    }

private:
    QString m_desc;
};

// 文件选择对话框注解
class FileDialogAnnotation : public IAnnotation {
public:
    // 获取注解名称
    QString name() const override {
        return "filedialog";
    }

    // 获取注解的参数
    QVariant argument(const QString& name) const override {
        if (name == "desc") return getDesc();
        if (name == "filter") return getFilter();
        return QVariant();
    }

    // 获取注解的参数名称
    QStringList argumentNames() const override {
        return QStringList() << "desc" << "filter";
    }

    QString getDesc() const {
        return m_desc;
    }

    void setDesc(QString value) {
        m_desc = value;
    }

    QString getFilter() const {
        return m_filter;
    }

    void setFilter(QString value) {
        m_filter = value;
    }

private:
    QString m_desc;
    QString m_filter;
};

// 颜色选择器注解
class ColorAnnotation : public IAnnotation {
public:
    // 获取注解名称
    QString name() const override {
        return "color";
    }

    // 获取注解的参数
    QVariant argument(const QString& name) const override {
        if (name == "desc") return getDesc();
        if (name == "default_value") return getDefaultValue();
        return QVariant();
    }

    // 获取注解的参数名称
    QStringList argumentNames() const override {
        return QStringList() << "desc" << "default_value";
    }

    QString getDesc() const {
        return m_desc;
    }

    void setDesc(QString value) {
        m_desc = value;
    }

    QString getDefaultValue() const {
        return m_defaultValue;
    }

    void setDefaultValue(QString value) {
        m_defaultValue = value;
    }

private:
    QString m_desc;
    QString m_defaultValue = "#000000";
};

// 日期选择器注解
class DateAnnotation : public IAnnotation {
public:
    // 获取注解名称
    QString name() const override {
        return "date";
    }

    // 获取注解的参数
    QVariant argument(const QString& name) const override {
        if (name == "desc") return getDesc();
        if (name == "format") return getFormat();
        return QVariant();
    }

    // 获取注解的参数名称
    QStringList argumentNames() const override {
        return QStringList() << "desc" << "format";
    }

    QString getDesc() const {
        return m_desc;
    }

    void setDesc(QString value) {
        m_desc = value;
    }

    QString getFormat() const {
        return m_format;
    }

    void setFormat(QString value) {
        m_format = value;
    }

private:
    QString m_desc;
    QString m_format = "yyyy-MM-dd";
};

// 时间选择器注解
class TimeAnnotation : public IAnnotation {
public:
    // 获取注解名称
    QString name() const override {
        return "time";
    }

    // 获取注解的参数
    QVariant argument(const QString& name) const override {
        if (name == "desc") return getDesc();
        if (name == "format") return getFormat();
        return QVariant();
    }

    // 获取注解的参数名称
    QStringList argumentNames() const override {
        return QStringList() << "desc" << "format";
    }

    QString getDesc() const {
        return m_desc;
    }

    void setDesc(QString value) {
        m_desc = value;
    }

    QString getFormat() const {
        return m_format;
    }

    void setFormat(QString value) {
        m_format = value;
    }

private:
    QString m_desc;
    QString m_format = "HH:mm:ss";
};

// 分组注解
class IniGroupAnnotation : public IAnnotation {
public:
    // 获取注解名称
    QString name() const override {
        return "inigroup";
    }

    // 获取注解的参数
    QVariant argument(const QString& name) const override {
        if (name == "value") return getValue();
        return QVariant();
    }

    // 获取注解的参数名称
    QStringList argumentNames() const override {
        return QStringList() << "value";
    }

    QString getValue() const {
        return m_value;
    }

    void setValue(QString value) {
        m_value = value;
    }

private:
    QString m_value;
};

// 绘制矩形注解
class DrawRectangleAnnotation : public IAnnotation {
public:
    // 获取注解名称
    QString name() const override {
        return "drawrectangle";
    }

    // 获取注解的参数
    QVariant argument(const QString& name) const override {
        if (name == "desc") return getDesc();
        return QVariant();
    }

    // 获取注解的参数名称
    QStringList argumentNames() const override {
        return QStringList() << "desc";
    }

    QString getDesc() const {
        return m_desc;
    }

    void setDesc(QString value) {
        m_desc = value;
    }

private:
    QString m_desc;
};

// 绘制圆形注解
class DrawCircleAnnotation : public IAnnotation {
public:
    // 获取注解名称
    QString name() const override {
        return "drawcircle";
    }

    // 获取注解的参数
    QVariant argument(const QString& name) const override {
        if (name == "desc") return getDesc();
        return QVariant();
    }

    // 获取注解的参数名称
    QStringList argumentNames() const override {
        return QStringList() << "desc";
    }

    QString getDesc() const {
        return m_desc;
    }

    void setDesc(QString value) {
        m_desc = value;
    }

private:
    QString m_desc;
};

// 绘制多边形注解
class DrawPolygonAnnotation : public IAnnotation {
public:
    // 获取注解名称
    QString name() const override {
        return "drawpolygon";
    }

    // 获取注解的参数
    QVariant argument(const QString& name) const override {
        if (name == "desc") return getDesc();
        return QVariant();
    }

    // 获取注解的参数名称
    QStringList argumentNames() const override {
        return QStringList() << "desc";
    }

    QString getDesc() const {
        return m_desc;
    }

    void setDesc(QString value) {
        m_desc = value;
    }

private:
    QString m_desc;
};

// 绘制线段注解
class DrawLineAnnotation : public IAnnotation {
public:
    // 获取注解名称
    QString name() const override {
        return "drawline";
    }

    // 获取注解的参数
    QVariant argument(const QString& name) const override {
        if (name == "desc") return getDesc();
        return QVariant();
    }

    // 获取注解的参数名称
    QStringList argumentNames() const override {
        return QStringList() << "desc";
    }

    QString getDesc() const {
        return m_desc;
    }

    void setDesc(QString value) {
        m_desc = value;
    }

private:
    QString m_desc;
};

// 绘制点注解
class DrawPointAnnotation : public IAnnotation {
public:
    // 获取注解名称
    QString name() const override {
        return "drawpoint";
    }

    // 获取注解的参数
    QVariant argument(const QString& name) const override {
        if (name == "desc") return getDesc();
        return QVariant();
    }

    // 获取注解的参数名称
    QStringList argumentNames() const override {
        return QStringList() << "desc";
    }

    QString getDesc() const {
        return m_desc;
    }

    void setDesc(QString value) {
        m_desc = value;
    }

private:
    QString m_desc;
};

// 标签注解
class LabelAnnotation : public IAnnotation {
public:
    // 获取注解名称
    QString name() const override {
        return "label";
    }

    // 获取注解的参数
    QVariant argument(const QString& name) const override {
        if (name == "text") return getText();
        if (name == "desc") return getDesc();
        return QVariant();
    }

    // 获取注解的参数名称
    QStringList argumentNames() const override {
        return QStringList() << "text" << "desc";
    }

    QString getText() const {
        return m_text;
    }

    void setText(QString value) {
        m_text = value;
    }

    QString getDesc() const {
        return m_desc;
    }

    void setDesc(QString value) {
        m_desc = value;
    }

private:
    QString m_text;
    QString m_desc;
};

// 验证注解
class ValidateAnnotation : public IAnnotation {
public:
    // 获取注解名称
    QString name() const override {
        return "validate";
    }

    // 获取注解的参数
    QVariant argument(const QString& name) const override {
        if (name == "rule") return getRule();
        if (name == "message") return getMessage();
        return QVariant();
    }

    // 获取注解的参数名称
    QStringList argumentNames() const override {
        return QStringList() << "rule" << "message";
    }

    QString getRule() const {
        return m_rule;
    }

    void setRule(QString value) {
        m_rule = value;
    }

    QString getMessage() const {
        return m_message;
    }

    void setMessage(QString value) {
        m_message = value;
    }

private:
    QString m_rule;
    QString m_message;
};

// 提示注解
class TooltipAnnotation : public IAnnotation {
public:
    // 获取注解名称
    QString name() const override {
        return "tooltip";
    }

    // 获取注解的参数
    QVariant argument(const QString& name) const override {
        if (name == "text") return getText();
        if (name == "duration") return getDuration();
        return QVariant();
    }

    // 获取注解的参数名称
    QStringList argumentNames() const override {
        return QStringList() << "text" << "duration";
    }

    QString getText() const {
        return m_text;
    }

    void setText(QString value) {
        m_text = value;
    }

    int getDuration() const {
        return m_duration;
    }

    void setDuration(int value) {
        m_duration = value;
    }

private:
    QString m_text;
    int m_duration = 3000;
};

// 只读注解
class ReadOnlyAnnotation : public IAnnotation {
public:
    // 获取注解名称
    QString name() const override {
        return "readonly";
    }

    // 获取注解的参数
    QVariant argument(const QString& name) const override {
        return QVariant();
    }

    // 获取注解的参数名称
    QStringList argumentNames() const override {
        return QStringList();
    }
};

// 隐藏注解
class HiddenAnnotation : public IAnnotation {
public:
    // 获取注解名称
    QString name() const override {
        return "hidden";
    }

    // 获取注解的参数
    QVariant argument(const QString& name) const override {
        return QVariant();
    }

    // 获取注解的参数名称
    QStringList argumentNames() const override {
        return QStringList();
    }
};
