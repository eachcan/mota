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


#include "yima.h"


// 此文件由 Mota 代码生成器自动生成
// 生成时间: 2025-06-07 23:54:58
// 源文件: unknown.mota

using namespace ymf;


namespace examples {


// Range注解
class MODEL_EXPORT RangeAnnotation : public IAnnotation {
public:
    RangeAnnotation() = default;
    
    
    // 实现IAnnotation接口
    QString name() const override {
        return "Range";
    }
    
    QVariant argument(const QString& argumentName) const override {
        if (argumentName == QLatin1String("min")) return QVariant::fromValue(min_);
        if (argumentName == QLatin1String("max")) return QVariant::fromValue(max_);
        if (argumentName == QLatin1String("desc")) return QVariant::fromValue(desc_);
        return QVariant();
    }
    
    QStringList argumentNames() const override {
        return QStringList{QLatin1String("min"), QLatin1String("max"), QLatin1String("desc")};
    }
    
    // 特定于Range的访问器
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
    QString desc_;
}; 

// Priority枚举
enum class Priority {
    Low = 0,
    Medium = 1,
    High = 2
};

// Priority辅助函数
namespace PriorityHelper {
    // 将枚举值转换为字符串
    inline QString toString(Priority value) {
        switch (value) {
            case Priority::Low:
                return QLatin1String("Low");
            case Priority::Medium:
                return QLatin1String("Medium");
            case Priority::High:
                return QLatin1String("High");
            default:
                return QString();
        }
    }
    
    // 将字符串转换为枚举值
    inline Priority fromString(const QString& str) {
        if (str == QLatin1String("Low")) {
            return Priority::Low;
        } else if (str == QLatin1String("Medium")) {
            return Priority::Medium;
        } else if (str == QLatin1String("High")) {
            return Priority::High;
        }
        return Priority::Low;
    }
    
    // 获取所有枚举值的字符串表示
    inline QStringList allValues() {
        return QStringList() << QLatin1String("Low") << QLatin1String("Medium") << QLatin1String("High");
    }
    
    // 获取所有枚举值的UI显示名称
    inline QStringList allDisplayNames() {
        return QStringList() << QLatin1String("Low") << QLatin1String("Medium") << QLatin1String("High");
    }
    
    // 获取整个枚举的注解
    inline QList<QSharedPointer<IAnnotation>> annotations() {
        QList<QSharedPointer<IAnnotation>> result;
        return result;
        return QList<QSharedPointer<IAnnotation>>();
    }
    
    // 获取特定枚举值的注解
    inline QList<QSharedPointer<IAnnotation>> valueAnnotations(Priority value) {
        switch (value) {
            case Priority::Low: {
                QList<QSharedPointer<IAnnotation>> result;
                return result;
            }
            case Priority::Medium: {
                QList<QSharedPointer<IAnnotation>> result;
                return result;
            }
            case Priority::High: {
                QList<QSharedPointer<IAnnotation>> result;
                return result;
            }
            default:
                return QList<QSharedPointer<IAnnotation>>();
        }
    }
    
    // 获取特定枚举值的注解（通过字符串）
    inline QList<QSharedPointer<IAnnotation>> valueAnnotations(const QString& valueName) {
        if (valueName == "Low") {
            QList<QSharedPointer<IAnnotation>> result;
            return result;
        } else if (valueName == "Medium") {
            QList<QSharedPointer<IAnnotation>> result;
            return result;
        } else if (valueName == "High") {
            QList<QSharedPointer<IAnnotation>> result;
            return result;
        }
        return QList<QSharedPointer<IAnnotation>>();
    }
}


// Config块
class MODEL_EXPORT ConfigBlock : public IBlock {
public:
    ConfigBlock() = default;
    
    
    // 实现IBlock接口
    QCborValue toCbor() const override {
        QCborMap map;
        map.insert(QLatin1String("name"), QCborValue(getName()));
        map.insert(QLatin1String("enabled"), QCborValue(getEnabled()));
        map.insert(QLatin1String("priority"), QCborValue(static_cast<int>(getPriority())));
        return map;
    }
    
    void fromCbor(const QCborValue& cbor) override {
        QCborMap map = cbor.toMap();
        setName(map.value(QLatin1String("name")).toString());
        setEnabled(map.value(QLatin1String("enabled")).toBool());
        setPriority(static_cast<Priority>(map.value(QLatin1String("priority")).toInteger()));
    }
    
    QString name() const override {
        return "Config";
    }
    
    QStringList fields() const override {
        return QStringList{QLatin1String("name"), QLatin1String("enabled"), QLatin1String("priority")};
    }
    
    QString fieldType(const QString& fieldName) const override {
        if (fieldName == QLatin1String("name")) return QLatin1String("string");
        if (fieldName == QLatin1String("enabled")) return QLatin1String("bool");
        if (fieldName == QLatin1String("priority")) return QLatin1String("Priority");
        return QLatin1String("");
    }
    
    QList<QSharedPointer<IAnnotation>> annotations() const override {
        
        return QList<QSharedPointer<IAnnotation>>();
    }
    
    QList<QSharedPointer<void>> fieldAnnotation(const QString& fieldName) const override {
        if (fieldName == QLatin1String("name")) {
            return QList<QSharedPointer<void>>();
        }
        if (fieldName == QLatin1String("enabled")) {
            return QList<QSharedPointer<void>>();
        }
        if (fieldName == QLatin1String("priority")) {
            return QList<QSharedPointer<void>>();
        }
        return QList<QSharedPointer<void>>();
    }
    
    QString description() const override {
        return "Generated from block Config";
    }
    
    QString fieldDescription(const QString& fieldName) const override {
        
        return QString();
    }
    
    QVariant value(const QString& fieldName) const override {
        if (fieldName == QLatin1String("name")) return QVariant::fromValue(name_);
        if (fieldName == QLatin1String("enabled")) return QVariant::fromValue(enabled_);
        if (fieldName == QLatin1String("priority")) return QVariant::fromValue(priority_);
        return QVariant();
    }
    
    void value(const QString& fieldName, const QVariant& value) override {
        if (fieldName == QLatin1String("name")) {
            name_ = value.value<QString>();
            return;
        }
        if (fieldName == QLatin1String("enabled")) {
            enabled_ = value.value<bool>();
            return;
        }
        if (fieldName == QLatin1String("priority")) {
            priority_ = value.value<Priority>();
            return;
        }
    }
    
    // 特定于Config的访问器
        // name字段的访问器
    QString getName() const {
        return name_;
    }
    
    void setName(const QString& value) {
        name_ = value;
    } 

        // enabled字段的访问器
    bool getEnabled() const {
        return enabled_;
    }
    
    void setEnabled(const bool& value) {
        enabled_ = value;
    } 

        // priority字段的访问器
    Priority getPriority() const {
        return priority_;
    }
    
    void setPriority(const Priority& value) {
        priority_ = value;
    } 
    
private:
    QString name_;
    bool enabled_;
    Priority priority_;
};


// Task结构体

class MODEL_EXPORT TaskModel : public IModel {
public:
    TaskModel() = default;
    
    
    // 实现IModel接口
    QCborValue toCbor() const override {
        QCborMap map;
        map.insert(QLatin1String("title"), QCborValue(getTitle()));
        map.insert(QLatin1String("description"), QCborValue(getDescription()));
        map.insert(QLatin1String("completed"), QCborValue(getCompleted()));
        QCborArray tagsArray;
        for (const auto& item : getTags()) {
            tagsArray.append(QCborValue(item));
        }
        map.insert(QLatin1String("tags"), tagsArray);
        map.insert(QLatin1String("config"), getConfig().toCbor());
        return map;
    }
    
    void fromCbor(const QCborValue& cbor) override {
        QCborMap map = cbor.toMap();
        setTitle(map.value(QLatin1String("title")).toString());
        setDescription(map.value(QLatin1String("description")).toString());
        setCompleted(map.value(QLatin1String("completed")).toBool());
        QCborArray tagsArray = map.value(QLatin1String("tags")).toArray();
        QVector<QString> tags;
        for (const auto& itemValue : tagsArray) {
            tags.append(static_cast<QString>(itemValue.toString()));
        }
        setTags(tags);
        ConfigBlock config;
        config.fromCbor(map.value(QLatin1String("config")));
        setConfig(config);
    }
    
    QStringList fields() const override {
        return QStringList{QLatin1String("title"), QLatin1String("description"), QLatin1String("completed"), QLatin1String("tags"), QLatin1String("config")};
    }
    
    QString fieldOriginTypeName(const QString& fieldName) const override {
        if (fieldName == QLatin1String("title")) return QLatin1String("string");
        if (fieldName == QLatin1String("description")) return QLatin1String("string");
        if (fieldName == QLatin1String("completed")) return QLatin1String("bool");
        if (fieldName == QLatin1String("tags")) return QLatin1String("repeated string");
        if (fieldName == QLatin1String("config")) return QLatin1String("Config");
        return QLatin1String("");
    }
    
    QList<QSharedPointer<IAnnotation>> annotations() const override {
        
        return QList<QSharedPointer<IAnnotation>>();
    }
    
    QList<QSharedPointer<void>> fieldAnnotations(const QString& fieldName) const override {
        if (fieldName == QLatin1String("title")) {
            return QList<QSharedPointer<void>>();
        }
        if (fieldName == QLatin1String("description")) {
            return QList<QSharedPointer<void>>();
        }
        if (fieldName == QLatin1String("completed")) {
            return QList<QSharedPointer<void>>();
        }
        if (fieldName == QLatin1String("tags")) {
            return QList<QSharedPointer<void>>();
        }
        if (fieldName == QLatin1String("config")) {
            return QList<QSharedPointer<void>>();
        }
        return QList<QSharedPointer<void>>();
    }
    
    QString description() const override {
        return "Generated from struct Task";
    }
    
    QString fieldDescription(const QString& fieldName) const override {
        
        return QString();
    }
    
    QVariant value(const QString& fieldName) const override {
        if (fieldName == QLatin1String("title")) return QVariant::fromValue(title_);
        if (fieldName == QLatin1String("description")) return QVariant::fromValue(description_);
        if (fieldName == QLatin1String("completed")) return QVariant::fromValue(completed_);
        if (fieldName == QLatin1String("tags")) return QVariant::fromValue(tags_);
        if (fieldName == QLatin1String("config")) return QVariant::fromValue(config_);
        return QVariant();
    }
    
    void value(const QString& fieldName, const QVariant& value) override {
        if (fieldName == QLatin1String("title")) {
            title_ = value.value<QString>();
            return;
        }
        if (fieldName == QLatin1String("description")) {
            description_ = value.value<QString>();
            return;
        }
        if (fieldName == QLatin1String("completed")) {
            completed_ = value.value<bool>();
            return;
        }
        if (fieldName == QLatin1String("tags")) {
            tags_ = value.value<QVector<QString>>();
            return;
        }
        if (fieldName == QLatin1String("config")) {
            config_ = value.value<ConfigBlock>();
            return;
        }
    }
    
    // 特定于Task的访问器
        // title字段的访问器
    QString getTitle() const {
        return title_;
    }
    
    void setTitle(const QString& value) {
        title_ = value;
    } 

        // description字段的访问器
    QString getDescription() const {
        return description_;
    }
    
    void setDescription(const QString& value) {
        description_ = value;
    } 

        // completed字段的访问器
    bool getCompleted() const {
        return completed_;
    }
    
    void setCompleted(const bool& value) {
        completed_ = value;
    } 

        // tags字段的访问器
    QVector<QString> getTags() const {
        return tags_;
    }
    
    void setTags(const QVector<QString>& value) {
        tags_ = value;
    } 

        // config字段的访问器
    ConfigBlock getConfig() const {
        return config_;
    }
    
    void setConfig(const ConfigBlock& value) {
        config_ = value;
    } 
    
protected:
    QString modelName() const override {
        return "Task";
    }
    
private:
    QString title_;
    QString description_;
    bool completed_;
    QVector<QString> tags_;
    ConfigBlock config_;
    
    // 变更通知
    void notifyChange();
};



} // namespace examples

