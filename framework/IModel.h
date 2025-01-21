#pragma once

#include "framework_global.h"
#include <QString>
#include <QVariant>
#include <QMap>
#include <QCborValue>
#include <QCoreApplication>
#include <memory>
#include "StorageEngine.h"

class MODULE_EXPORT IModel {
public:
    enum class Region {
        Global,     // 全局配置
        Product     // 产品相关配置
    };

    enum class UIType {
        DrawRectangle,  // 矩形绘制
        DrawCircle,     // 圆形绘制
        DrawHLine,      // 水平线绘制
        DrawVLine,      // 垂直线绘制
        Range,          // 范围输入
        Number,         // 数值输入
        Text,           // 文本输入
        Switcher,       // 布尔开关
        Select          // 预定义选项选择
    };

    struct Option {
        QString value;      // 选项值
        QString text;       // 显示文本
        QString help;       // 帮助文本
        bool enabled;       // 是否启用
    };

    // 结构体注解
    struct ModelAnnotation {
        QString file;       // 目标文件路径
        QString level;      // 作用域级别
        QString format;     // 数据格式
    };

    // 字段注解
    struct FieldAnnotation {
        UIType uiType;                 // UI 渲染类型
        bool visible;                  // 是否可见
        QVariant minValue;            // 最小值（数值类型）
        QVariant maxValue;            // 最大值（数值类型）
        QString minField;             // 最小值引用字段（范围类型）
        QString maxField;             // 最大值引用字段（范围类型）
        int maxLength;                // 最大长度（文本类型）
        QList<Option> options;        // 选项列表（选择类型）
        QString optionsField;         // 选项字段引用（选择类型）
        QString description;          // 字段描述
        bool isSystem;                // 是否系统字段
    };

    IModel(Region region = Region::Global);
    virtual ~IModel() = default;
    
    // 序列化/反序列化接口
    virtual QCborValue toCbor() const = 0;
    virtual void fromCbor(const QCborValue& cbor) = 0;
    
    // 存储接口
    bool saveToFile(const QString& filepath, const QString& format);
    bool loadFromFile(const QString& filepath, const QString& format);
    
    // 模型是否可写
    bool writable() const;
    void writable(bool writable);
    
    // 获取模型作用域
    Region region() const;
    void region(Region region);
    
    // 获取/设置限定符
    QString qualifier() const;
    QString qualifier(const QString& qualifier);
    
    // 获取所有字段
    virtual QStringList fields() const = 0;
    
    // 获取字段类型
    virtual QString fieldType(const QString& fieldName) const = 0;
    
    // 获取字段注解
    virtual FieldAnnotation fieldAnnotation(const QString& fieldName) const = 0;

    // 获取模型注解
    virtual ModelAnnotation modelAnnotation() const = 0;
    
    // 获取字段值
    virtual QVariant value(const QString& fieldName) const = 0;
    
    // 设置字段值
    virtual void value(const QString& fieldName, const QVariant& value) = 0;
    
    // 获取实际存储路径
    QString resolvePath(const QString& qualifier = QString()) const;
    
protected:
    // 获取产品目录
    virtual QString productDir() const;

    // 获取模型名
    virtual QString modelName() const = 0;
    
private:
    std::shared_ptr<IStorageEngine> storageEngine(const QString& format);

    Region m_region;                                    // 模型作用域
    bool m_writable;                                   // 是否可写
    QString m_qualifier;                               // 限定符
};

// BaseBlock 保持独立
class BaseBlock {
public:
    virtual ~BaseBlock() = default;
    virtual QCborValue toCbor() const = 0;
    virtual void fromCbor(const QCborValue& cbor) = 0;
};
