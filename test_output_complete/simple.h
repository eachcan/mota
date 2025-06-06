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
// 生成时间: 2025-06-06 18:51:34
// 源文件: unknown.mota

using namespace ymf;


namespace example {


// Range注解
class MODEL_EXPORT Range : public IAnnotation {
public:
    Range() = default;
    explicit Range(const int32_t& min, const int32_t& max, const QString& desc) : min_(min), max_(max), desc_(desc) {}
    
    // 实现IAnnotation接口
    QString name() const override {
        return "Range";
    }
    
    QVariant argument(const QString& name) const override {
        if (name == "min") {
            return QVariant::fromValue(min_);
        } else if (name == "max") {
            return QVariant::fromValue(max_);
        } else if (name == "desc") {
            return QVariant::fromValue(desc_);
        }
        return QVariant();
    }
    
    QStringList argumentNames() const override {
        return QStringList()<< "min" << "max" << "desc";
    }
    
    // 特定于Range的访问器
    const int32_t& getMin() const {
        return min_;
    }
    void setMin(const int32_t& value) {
        min_ = value;
    }
    const int32_t& getMax() const {
        return max_;
    }
    void setMax(const int32_t& value) {
        max_ = value;
    }
    const QString& getDesc() const {
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
    Low,
    Medium,
    High
};

// Priority辅助函数
namespace PriorityHelper {
    // 将枚举值转换为字符串
    inline QString toString(Priority value) {
        switch (value) {
            case Priority::Low:
                return "Low";
            case Priority::Medium:
                return "Medium";
            case Priority::High:
                return "High";
            default:
                return QString();
        }
    }
    
    // 将字符串转换为枚举值
    inline Priority fromString(const QString& str) {
        if (str == "Low") {
            return Priority::Low;
        } else if (str == "Medium") {
            return Priority::Medium;
        } else if (str == "High") {
            return Priority::High;
        }
        return Priority::Low;
    }
    
    // 获取所有枚举值的字符串表示
    inline QStringList allValues() {
        return QStringList() << "Low" << "Medium" << "High";
    }
    
    // 获取所有枚举值的UI显示名称
    inline QStringList allDisplayNames() {
        return QStringList() << "Low" << "Medium" << "High";
    }
}


// Config块
class MODEL_EXPORT Config : public IBlock {
public:
    Config() = default;
    explicit Config(const QString& name, const bool& enabled, const Priority& priority) : name_(name), enabled_(enabled), priority_(priority) {}
    
    // 实现IBlock接口
    QCborValue toCbor() const override {
        QCborMap map;
        map["name"] = QCborValue::fromVariant(QVariant::fromValue(name_));
        map["enabled"] = QCborValue::fromVariant(QVariant::fromValue(enabled_));
        map["priority"] = QCborValue::fromVariant(QVariant::fromValue(priority_));
        return map;
    }
    
    void fromCbor(const QCborValue& cbor) override {
        QCborMap map = cbor.toMap();
        if (map.contains("name")) {
            name_ = map["name"].toVariant().value<QString>();
        }
        if (map.contains("enabled")) {
            enabled_ = map["enabled"].toVariant().value<bool>();
        }
        if (map.contains("priority")) {
            priority_ = map["priority"].toVariant().value<Priority>();
        }
    }
    
    QString name() const override {
        return "Config";
    }
    
    QStringList fields() const override {
        return QStringList()<< "name" << "enabled" << "priority";
    }
    
    QString fieldType(const QString& fieldName) const override {
        if (fieldName == "name") {
            return "QString";
        } else if (fieldName == "enabled") {
            return "bool";
        } else if (fieldName == "priority") {
            return "Priority";
        }
        return QString();
    }
    
    QList<QSharedPointer<void>> fieldAnnotation(const QString& fieldName) const override {
        
        return QList<QSharedPointer<void>>();
    }
    
    QString description() const override {
        return "Generated from block Config";
    }
    
    QString fieldDescription(const QString& fieldName) const override {
        
        return QString();
    }
    
    QVariant value(const QString& fieldName) const override {
        if (fieldName == "name") {
            return QVariant::fromValue(name_);
        } else if (fieldName == "enabled") {
            return QVariant::fromValue(enabled_);
        } else if (fieldName == "priority") {
            return QVariant::fromValue(priority_);
        }
        return QVariant();
    }
    
    void value(const QString& fieldName, const QVariant& value) override {
        if (fieldName == "name") {
            name_ = value.value<QString>();
        } else if (fieldName == "enabled") {
            enabled_ = value.value<bool>();
        } else if (fieldName == "priority") {
            priority_ = value.value<Priority>();
        }
        // 注意：复合类型需要单独处理
    }
    
    // 特定于Config的访问器
    const QString& getName() const {
        return name_;
    }
    void setName(const QString& value) {
        name_ = value;
    }
    const bool& getEnabled() const {
        return enabled_;
    }
    void setEnabled(const bool& value) {
        enabled_ = value;
    }
    const Priority& getPriority() const {
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


// Task块
class MODEL_EXPORT Task : public IBlock {
public:
    Task() = default;
    explicit Task(const QString& title, const QString& description, const bool& completed, const QVector<QString>& tags, const Config& config) : title_(title), description_(description), completed_(completed), tags_(tags), config_(config) {}
    
    // 实现IBlock接口
    QCborValue toCbor() const override {
        QCborMap map;
        map["title"] = QCborValue::fromVariant(QVariant::fromValue(title_));
        map["description"] = QCborValue::fromVariant(QVariant::fromValue(description_));
        map["completed"] = QCborValue::fromVariant(QVariant::fromValue(completed_));
        map["tags"] = QCborValue::fromVariant(QVariant::fromValue(tags_));
        map["config"] = QCborValue::fromVariant(QVariant::fromValue(config_));
        return map;
    }
    
    void fromCbor(const QCborValue& cbor) override {
        QCborMap map = cbor.toMap();
        if (map.contains("title")) {
            title_ = map["title"].toVariant().value<QString>();
        }
        if (map.contains("description")) {
            description_ = map["description"].toVariant().value<QString>();
        }
        if (map.contains("completed")) {
            completed_ = map["completed"].toVariant().value<bool>();
        }
        if (map.contains("tags")) {
            tags_ = map["tags"].toVariant().value<QVector<QString>>();
        }
        if (map.contains("config")) {
            config_ = map["config"].toVariant().value<Config>();
        }
    }
    
    QString name() const override {
        return "Task";
    }
    
    QStringList fields() const override {
        return QStringList()<< "title" << "description" << "completed" << "tags" << "config";
    }
    
    QString fieldType(const QString& fieldName) const override {
        if (fieldName == "title") {
            return "QString";
        } else if (fieldName == "description") {
            return "QString";
        } else if (fieldName == "completed") {
            return "bool";
        } else if (fieldName == "tags") {
            return "QVector<QString>";
        } else if (fieldName == "config") {
            return "Config";
        }
        return QString();
    }
    
    QList<QSharedPointer<void>> fieldAnnotation(const QString& fieldName) const override {
        
        return QList<QSharedPointer<void>>();
    }
    
    QString description() const override {
        return "Generated from block Task";
    }
    
    QString fieldDescription(const QString& fieldName) const override {
        
        return QString();
    }
    
    QVariant value(const QString& fieldName) const override {
        if (fieldName == "title") {
            return QVariant::fromValue(title_);
        } else if (fieldName == "description") {
            return QVariant::fromValue(description_);
        } else if (fieldName == "completed") {
            return QVariant::fromValue(completed_);
        } else if (fieldName == "tags") {
            return QVariant::fromValue(tags_);
        } else if (fieldName == "config") {
            return QVariant::fromValue(config_);
        }
        return QVariant();
    }
    
    void value(const QString& fieldName, const QVariant& value) override {
        if (fieldName == "title") {
            title_ = value.value<QString>();
        } else if (fieldName == "description") {
            description_ = value.value<QString>();
        } else if (fieldName == "completed") {
            completed_ = value.value<bool>();
        } else if (fieldName == "tags") {
            tags_ = value.value<QVector<QString>>();
        } else if (fieldName == "config") {
            config_ = value.value<Config>();
        }
        // 注意：复合类型需要单独处理
    }
    
    // 特定于Task的访问器
    const QString& getTitle() const {
        return title_;
    }
    void setTitle(const QString& value) {
        title_ = value;
    }
    const QString& getDescription() const {
        return description_;
    }
    void setDescription(const QString& value) {
        description_ = value;
    }
    const bool& getCompleted() const {
        return completed_;
    }
    void setCompleted(const bool& value) {
        completed_ = value;
    }
    const QVector<QString>& getTags() const {
        return tags_;
    }
    void setTags(const QVector<QString>& value) {
        tags_ = value;
    }
    const Config& getConfig() const {
        return config_;
    }
    void setConfig(const Config& value) {
        config_ = value;
    }
    
private:
    QString title_;
    QString description_;
    bool completed_;
    QVector<QString> tags_;
    Config config_;
};



} // namespace example

