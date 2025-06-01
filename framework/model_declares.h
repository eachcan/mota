#pragma once

#include <QString>
#include <QVariant>
#include <QList>

namespace ymf {
    enum class Scope {
        Global,     // 全局配置
        Product,    // 产品配置
    };
    // 字段注解
    enum class FormType { // 用于字段，表示 UI 渲染类型
        DrawRectangle,  // 矩形绘制
        DrawCircle,     // 圆形绘制
        DrawEllipse,    // 椭圆绘制
        DrawLine,       // 线段绘制
        DrawHLine,      // 水平线绘制
        DrawVLine,      // 垂直线绘制
        DrawPolygon,    // 多边形绘制
        Int,            // 整数输入
        Float,         // 浮点数输入
        IntRange,       // 整数范围输入
        FloatRange,    // 浮点数范围输入
        Text,           // 文本输入
        Switcher,       // 布尔开关
        Select,          // 预定义选项选择
        FileSelect,      // 文件选择
        FolderSelect,    // 文件夹选择
    };


    struct Option { // 用于选择类型字段
        QVariant value;      // 选项值
        QString text;       // 显示文本
        QString help;       // 帮助文本
        bool enabled;       // 是否启用
    };

    struct EnumValueAnnotation { // 用于 enum 类型字段
        QString title;
        QString description;
        QString value; // 保存为字符串时的值
    };

    struct FormAnnotation { // 用于字段，表示 UI 渲染类型
        QString label;
        QString description;
        bool visible = true;
        bool editable = true;
        bool required = false;
    };

    // 用于 Rectangle 类型字段，仅修饰 Rectangle 的字段类型
    struct RectangleAnnotation : FormAnnotation {
        FormType formType = FormType::DrawRectangle;
    };

    // 用于 Circle 类型字段，仅修饰 Circle 的字段类型
    struct CircleAnnotation : FormAnnotation {
        FormType formType = FormType::DrawCircle;
    };

    // 用于 Ellipse 类型字段，仅修饰 Ellipse 的字段类型
    struct EllipseAnnotation : FormAnnotation {
        FormType formType = FormType::DrawEllipse;
    };

    // 用于 Polygon 类型字段，仅修饰 Polygon 的字段类型
    struct PolygonAnnotation : FormAnnotation {
        FormType formType = FormType::DrawPolygon;
    };

    // 用于 Line 类型字段，仅修饰 Line 的字段类型
    struct LineAnnotation : FormAnnotation {
        FormType formType = FormType::DrawLine;
    };

    // 用于 int8 / int16 / int32 / int64 类型字段
    struct HLineAnnotation : FormAnnotation {
        FormType formType = FormType::DrawHLine;
        QString maxValueField;
        QString minValueField;
        long maxValue = INT_MAX; // int 最大值
        long minValue = 0;
    };

    // 用于 int8 / int16 / int32 / int64 类型字段
    struct VLineAnnotation : FormAnnotation {
        FormType formType = FormType::DrawVLine;
        QString maxValueField;
        QString minValueField;
        long maxValue = INT_MAX; // int 最大值
        long minValue = 0;
    };

    // 用于 IntRange 类型字段
    struct IntRangeAnnotation : FormAnnotation {
        FormType formType = FormType::IntRange;
        QString maxValueField;
        QString minValueField;
        long maxValue = INT_MAX;
        long minValue = 0;
    };

    // 用于 FloatRange 类型字段
    struct FloatRangeAnnotation : FormAnnotation {
        FormType formType = FormType::FloatRange;
        QString maxValueField;
        QString minValueField;
        double maxValue = INT_MAX;
        double minValue = 0;
    };

    enum class NumberMode {
        Input,
        Preview,
        Slider,
        PreviewSlider
    };

    // 用于 int 或 long 类型字段
    struct IntAnnotation : FormAnnotation {
        FormType formType = FormType::Int;
        QString maxValueField;
        QString minValueField;
        int maxValue = INT_MAX;
        int minValue = 0;
        int step = 1;
        NumberMode mode = NumberMode::Input; // 支持 input / preview / slider / preview_slider
    };

    // 用于 double 或 float 类型字段
    struct FloatAnnotation : FormAnnotation {
        FormType formType = FormType::Float;
        QString maxValueField;
        QString minValueField;
        double maxValue = INT_MAX;
        double minValue = 0;
        double step = 1.0; // 步长
        int8_t precision = 2; // 小数位数
        NumberMode mode = NumberMode::Input; // 支持 input / preview / slider / preview_slider
    };

    // 用于 string 类型字段
    struct TextAnnotation : FormAnnotation {
        FormType formType = FormType::Text;
        int maxLength = 256;
        QString placeholder;
        QString regex; // 正则表达式
    };

    enum class SwitcherMode {
        Checkbox,
        Button,
        Switch
    };

    // 用于 bool 类型字段
    struct SwitcherAnnotation : FormAnnotation {
        FormType formType = FormType::Switcher;
        SwitcherMode mode = SwitcherMode::Checkbox;
    };

    // 用于 string 类型字段，显示为下拉框
    struct SelectAnnotation : FormAnnotation {
        FormType formType = FormType::Select;
        QString enumClass;
        QString field; // 选项字段引用，指向到 repeated Option
    };

    // 用于 enum 类型的字段，显示为下拉框
    struct EnumAnnotation : FormAnnotation {
        FormType formType = FormType::Select;
    };

    // 用于文件选择
    struct FileSelectAnnotation : FormAnnotation {
        FormType formType = FormType::FileSelect;
        QString dirPath;
        QString filter;
    };

    // 用于文件夹选择
    struct FolderSelectAnnotation : FormAnnotation {
        FormType formType = FormType::FolderSelect;
        QString dirPath;
    };

    struct Rectangle {
        int row1;
        int col1;
        int row2;
        int col2;
        int angle;
    };

    struct Circle {
        int row;
        int col;
        int radius;
    };

    struct Ellipse {
        int row;
        int col;
        int radius1;
        int radius2;
        int angle;
    };

    struct Line {
        int row1;
        int col1;
        int row2;
        int col2;
    };

    struct HLine {
        int row;
        int col1;
        int col2;
    };

    struct VLine {
        int col;
        int row1;
        int row2;
    };

    struct IntRange {
        long minValue;
        long maxValue;
    };

    struct FloatRange {
        double minValue;
        double maxValue;
    };

    struct Polygon {
        QList<QPointF> points;
    };

} // namespace ymf
