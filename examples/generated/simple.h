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
// 生成时间: 2025-06-09 17:26:44
// 源文件: document.mota

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
    
    QStringList argumentNames() const override {
        return QStringList{"min""max""desc"};
    }
    
    QVariant argumentValue(const QString& argumentName) const override {

        if (argumentName == "min") {
            return QVariant::fromValue(min_);
        }

        if (argumentName == "max") {
            return QVariant::fromValue(max_);
        }

        if (argumentName == "desc") {
            return QVariant::fromValue(desc_);
        }

        return QVariant();
    }
    
    void argumentValue(const QString& argumentName, const QVariant& value) override {

        if (argumentName == "min") {
            min_ = value.value<int32_t>();
            return;
        }

        if (argumentName == "max") {
            max_ = value.value<int32_t>();
            return;
        }

        if (argumentName == "desc") {
            desc_ = value.value<QString>();
            return;
        }

    }
    
    QString description() const override {
        return "Generated annotation Range";
    }
    
    QString argumentDescription(const QString& argumentName) const override {

        if (argumentName == "min") {
            return "field.description";
        }

        if (argumentName == "max") {
            return "field.description";
        }

        if (argumentName == "desc") {
            return "field.description";
        }

        return QString();
    }
    
    // 特定于Range的访问器



    int32_t getMin() const {
        return min_;
    }


    void setMin(const int32_t& value) {
        min_ = value;
    }



    int32_t getMax() const {
        return max_;
    }


    void setMax(const int32_t& value) {
        max_ = value;
    }



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
enum class Priority : int32_t {


    Low = 0

    Medium = 1

    High = 2


};

class MODEL_EXPORT PriorityHelper {
public:
    static QString toString(Priority value) {
        switch (value) {


            case Priority::Low:
                return "value.string_value";

            case Priority::Medium:
                return "value.string_value";

            case Priority::High:
                return "value.string_value";


            default:
                return QString();
        }
    }
    
    static Priority fromString(const QString& str) {


        if (str == "value.string_value") {
            return Priority::Low;
        }

        if (str == "value.string_value") {
            return Priority::Medium;
        }

        if (str == "value.string_value") {
            return Priority::High;
        }


        return static_cast<Priority>(0);
    }
    
    static QStringList allStringValues() {
        return QStringList{

            "value.string_value"

            "value.string_value"

            "value.string_value"

        };
    }
    
    static QStringList allDisplayNames() {
        return QStringList{

            "value.display_name"

            "value.display_name"

            "value.display_name"

        };
    }
    
    static QList<QSharedPointer<IAnnotation>> annotations() {



    }
    
    static QList<QSharedPointer<IAnnotation>> valueAnnotations(Priority value) {
        switch (value) {


            case Priority::Low: {

            }
<%endforeach%>

            default:
                return QList<QSharedPointer<IAnnotation>>();
        }
    }
    
    static QList<QSharedPointer<IAnnotation>> valueAnnotationsByName(const QString& valueName) {


        if (valueName == "Low") {

        }
<%endforeach%>

        return QList<QSharedPointer<IAnnotation>>();
    }
    
    static QString description() {
        return "Generated enum Priority";
    }
    
    static QString valueDescription(Priority value) {
        switch (value) {

            case Priority::Low:
                return "value.description";

            case Priority::Medium:
                return "value.description";

            case Priority::High:
                return "value.description";

            default:
                return QString();
        }
    }
    
    static QString valueDescriptionByName(const QString& valueName) {

        if (valueName == "Low") {
            return "value.description";
        }

        if (valueName == "Medium") {
            return "value.description";
        }

        if (valueName == "High") {
            return "value.description";
        }

        return QString();
    }
}; 


// Config块
class MODEL_EXPORT ConfigBlock :  {
public:
    ConfigBlock() = default;
    


    
    // 实现IBlock接口
    QCborValue toCbor() const override {
        QCborMap map;


<%if (field_type_template(field.type) == "INT")%>
        map["name"] = QCborValue(name_);
<%endif%>
<%if (field_type_template(field.type) == "FLOAT")%>
        map["name"] = QCborValue(name_);
<%endif%>
<%if (field_type_template(field.type) == "STRING")%>
        map["name"] = QCborValue(name_);
<%endif%>
<%if (field_type_template(field.type) == "BOOL")%>
        map["name"] = QCborValue(name_);
<%endif%>
<%if (field_type_template(field.type) == "BYTES")%>
        map["name"] = QCborValue(name_);
<%endif%>
<%if (field_type_template(field.type) == "ARRAY")%>
        QCborArray nameArray;
        for (const auto& item : name_) {
            nameArray.append(item.toCbor());
        }
        map["name"] = nameArray;
<%endif%>
<%if (field_type_template(field.type) == "COMPLEX")%>
        map["name"] = name_.toCbor();
<%endif%>

<%if (field_type_template(field.type) == "INT")%>
        map["enabled"] = QCborValue(enabled_);
<%endif%>
<%if (field_type_template(field.type) == "FLOAT")%>
        map["enabled"] = QCborValue(enabled_);
<%endif%>
<%if (field_type_template(field.type) == "STRING")%>
        map["enabled"] = QCborValue(enabled_);
<%endif%>
<%if (field_type_template(field.type) == "BOOL")%>
        map["enabled"] = QCborValue(enabled_);
<%endif%>
<%if (field_type_template(field.type) == "BYTES")%>
        map["enabled"] = QCborValue(enabled_);
<%endif%>
<%if (field_type_template(field.type) == "ARRAY")%>
        QCborArray enabledArray;
        for (const auto& item : enabled_) {
            enabledArray.append(item.toCbor());
        }
        map["enabled"] = enabledArray;
<%endif%>
<%if (field_type_template(field.type) == "COMPLEX")%>
        map["enabled"] = enabled_.toCbor();
<%endif%>

<%if (field_type_template(field.type) == "INT")%>
        map["priority"] = QCborValue(priority_);
<%endif%>
<%if (field_type_template(field.type) == "FLOAT")%>
        map["priority"] = QCborValue(priority_);
<%endif%>
<%if (field_type_template(field.type) == "STRING")%>
        map["priority"] = QCborValue(priority_);
<%endif%>
<%if (field_type_template(field.type) == "BOOL")%>
        map["priority"] = QCborValue(priority_);
<%endif%>
<%if (field_type_template(field.type) == "BYTES")%>
        map["priority"] = QCborValue(priority_);
<%endif%>
<%if (field_type_template(field.type) == "ARRAY")%>
        QCborArray priorityArray;
        for (const auto& item : priority_) {
            priorityArray.append(item.toCbor());
        }
        map["priority"] = priorityArray;
<%endif%>
<%if (field_type_template(field.type) == "COMPLEX")%>
        map["priority"] = priority_.toCbor();
<%endif%>


        return map;
    }
    
    void fromCbor(const QCborValue& cbor) override {
        QCborMap map = cbor.toMap();


<%if (field_type_template(field.type) == "INT")%>
        if (map.contains("name")) {
            name_ = map["name"].toInteger();
        }
<%endif%>
<%if (field_type_template(field.type) == "FLOAT")%>
        if (map.contains("name")) {
            name_ = map["name"].toDouble();
        }
<%endif%>
<%if (field_type_template(field.type) == "STRING")%>
        if (map.contains("name")) {
            name_ = map["name"].toString();
        }
<%endif%>
<%if (field_type_template(field.type) == "BOOL")%>
        if (map.contains("name")) {
            name_ = map["name"].toBool();
        }
<%endif%>
<%if (field_type_template(field.type) == "BYTES")%>
        if (map.contains("name")) {
            name_ = map["name"].toByteArray();
        }
<%endif%>
<%if (field_type_template(field.type) == "ARRAY")%>
        if (map.contains("name")) {
            QCborArray nameArray = map["name"].toArray();
            name_.clear();
            for (const auto& item : nameArray) {
                QString element;
                element.fromCbor(item);
                name_.append(element);
            }
        }
<%endif%>
<%if (field_type_template(field.type) == "COMPLEX")%>
        if (map.contains("name")) {
            name_.fromCbor(map["name"]);
        }
<%endif%>

<%if (field_type_template(field.type) == "INT")%>
        if (map.contains("enabled")) {
            enabled_ = map["enabled"].toInteger();
        }
<%endif%>
<%if (field_type_template(field.type) == "FLOAT")%>
        if (map.contains("enabled")) {
            enabled_ = map["enabled"].toDouble();
        }
<%endif%>
<%if (field_type_template(field.type) == "STRING")%>
        if (map.contains("enabled")) {
            enabled_ = map["enabled"].toString();
        }
<%endif%>
<%if (field_type_template(field.type) == "BOOL")%>
        if (map.contains("enabled")) {
            enabled_ = map["enabled"].toBool();
        }
<%endif%>
<%if (field_type_template(field.type) == "BYTES")%>
        if (map.contains("enabled")) {
            enabled_ = map["enabled"].toByteArray();
        }
<%endif%>
<%if (field_type_template(field.type) == "ARRAY")%>
        if (map.contains("enabled")) {
            QCborArray enabledArray = map["enabled"].toArray();
            enabled_.clear();
            for (const auto& item : enabledArray) {
                bool element;
                element.fromCbor(item);
                enabled_.append(element);
            }
        }
<%endif%>
<%if (field_type_template(field.type) == "COMPLEX")%>
        if (map.contains("enabled")) {
            enabled_.fromCbor(map["enabled"]);
        }
<%endif%>

<%if (field_type_template(field.type) == "INT")%>
        if (map.contains("priority")) {
            priority_ = map["priority"].toInteger();
        }
<%endif%>
<%if (field_type_template(field.type) == "FLOAT")%>
        if (map.contains("priority")) {
            priority_ = map["priority"].toDouble();
        }
<%endif%>
<%if (field_type_template(field.type) == "STRING")%>
        if (map.contains("priority")) {
            priority_ = map["priority"].toString();
        }
<%endif%>
<%if (field_type_template(field.type) == "BOOL")%>
        if (map.contains("priority")) {
            priority_ = map["priority"].toBool();
        }
<%endif%>
<%if (field_type_template(field.type) == "BYTES")%>
        if (map.contains("priority")) {
            priority_ = map["priority"].toByteArray();
        }
<%endif%>
<%if (field_type_template(field.type) == "ARRAY")%>
        if (map.contains("priority")) {
            QCborArray priorityArray = map["priority"].toArray();
            priority_.clear();
            for (const auto& item : priorityArray) {
                Priority element;
                element.fromCbor(item);
                priority_.append(element);
            }
        }
<%endif%>
<%if (field_type_template(field.type) == "COMPLEX")%>
        if (map.contains("priority")) {
            priority_.fromCbor(map["priority"]);
        }
<%endif%>


    }
    
    QString name() const override {
        return "Config";
    }
    
    QStringList fields() const override {
        return QStringList{"name""enabled""priority"};
    }
    
    QString fieldType(const QString& fieldName) const override {


        if (fieldName == "name") {
            return "string";
        }

        if (fieldName == "enabled") {
            return "bool";
        }

        if (fieldName == "priority") {
            return "Priority";
        }

        return QString();

    }
    
    QList<QSharedPointer<IAnnotation>> annotations() const override {



    }
    
    QList<QSharedPointer<void>> fieldAnnotation(const QString& fieldName) const override {


        if (fieldName == "name") {
            QList<QSharedPointer<void>> result;

            return result;
        }
<%endforeach%>

        return QList<QSharedPointer<void>>();
    }
    
    QString description() const override {
        return "Generated block Config";
    }
    
    QString fieldDescription(const QString& fieldName) const override {

        if (argumentName == "name") {
            return "field.description";
        }

        if (argumentName == "enabled") {
            return "field.description";
        }

        if (argumentName == "priority") {
            return "field.description";
        }

        return QString();
    }
    
    QVariant value(const QString& fieldName) const override {

        if (argumentName == "name") {
            return QVariant::fromValue(name_);
        }

        if (argumentName == "enabled") {
            return QVariant::fromValue(enabled_);
        }

        if (argumentName == "priority") {
            return QVariant::fromValue(priority_);
        }

        return QVariant();
    }
    
    void value(const QString& fieldName, const QVariant& value) override {

        if (argumentName == "name") {
            name_ = value.value<QString>();
            return;
        }

        if (argumentName == "enabled") {
            enabled_ = value.value<bool>();
            return;
        }

        if (argumentName == "priority") {
            priority_ = value.value<Priority>();
            return;
        }

    }
    
    // 特定于Config的访问器



    QString getName() const {
        return name_;
    }


    void setName(const QString& value) {
        name_ = value;
    }



    bool getEnabled() const {
        return enabled_;
    }


    void setEnabled(const bool& value) {
        enabled_ = value;
    }



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
class MODEL_EXPORT TaskModel :  {
public:
    TaskModel() = default;
    


    
    // 实现IModel接口
    QCborValue toCbor() const override {
        QCborMap map;


<%if (field_type_template(field.type) == "INT")%>
        map["title"] = QCborValue(title_);
<%endif%>
<%if (field_type_template(field.type) == "FLOAT")%>
        map["title"] = QCborValue(title_);
<%endif%>
<%if (field_type_template(field.type) == "STRING")%>
        map["title"] = QCborValue(title_);
<%endif%>
<%if (field_type_template(field.type) == "BOOL")%>
        map["title"] = QCborValue(title_);
<%endif%>
<%if (field_type_template(field.type) == "BYTES")%>
        map["title"] = QCborValue(title_);
<%endif%>
<%if (field_type_template(field.type) == "ARRAY")%>
        QCborArray titleArray;
        for (const auto& item : title_) {
            titleArray.append(item.toCbor());
        }
        map["title"] = titleArray;
<%endif%>
<%if (field_type_template(field.type) == "COMPLEX")%>
        map["title"] = title_.toCbor();
<%endif%>

<%if (field_type_template(field.type) == "INT")%>
        map["description"] = QCborValue(description_);
<%endif%>
<%if (field_type_template(field.type) == "FLOAT")%>
        map["description"] = QCborValue(description_);
<%endif%>
<%if (field_type_template(field.type) == "STRING")%>
        map["description"] = QCborValue(description_);
<%endif%>
<%if (field_type_template(field.type) == "BOOL")%>
        map["description"] = QCborValue(description_);
<%endif%>
<%if (field_type_template(field.type) == "BYTES")%>
        map["description"] = QCborValue(description_);
<%endif%>
<%if (field_type_template(field.type) == "ARRAY")%>
        QCborArray descriptionArray;
        for (const auto& item : description_) {
            descriptionArray.append(item.toCbor());
        }
        map["description"] = descriptionArray;
<%endif%>
<%if (field_type_template(field.type) == "COMPLEX")%>
        map["description"] = description_.toCbor();
<%endif%>

<%if (field_type_template(field.type) == "INT")%>
        map["completed"] = QCborValue(completed_);
<%endif%>
<%if (field_type_template(field.type) == "FLOAT")%>
        map["completed"] = QCborValue(completed_);
<%endif%>
<%if (field_type_template(field.type) == "STRING")%>
        map["completed"] = QCborValue(completed_);
<%endif%>
<%if (field_type_template(field.type) == "BOOL")%>
        map["completed"] = QCborValue(completed_);
<%endif%>
<%if (field_type_template(field.type) == "BYTES")%>
        map["completed"] = QCborValue(completed_);
<%endif%>
<%if (field_type_template(field.type) == "ARRAY")%>
        QCborArray completedArray;
        for (const auto& item : completed_) {
            completedArray.append(item.toCbor());
        }
        map["completed"] = completedArray;
<%endif%>
<%if (field_type_template(field.type) == "COMPLEX")%>
        map["completed"] = completed_.toCbor();
<%endif%>

<%if (field_type_template(field.type) == "INT")%>
        map["tags"] = QCborValue(tags_);
<%endif%>
<%if (field_type_template(field.type) == "FLOAT")%>
        map["tags"] = QCborValue(tags_);
<%endif%>
<%if (field_type_template(field.type) == "STRING")%>
        map["tags"] = QCborValue(tags_);
<%endif%>
<%if (field_type_template(field.type) == "BOOL")%>
        map["tags"] = QCborValue(tags_);
<%endif%>
<%if (field_type_template(field.type) == "BYTES")%>
        map["tags"] = QCborValue(tags_);
<%endif%>
<%if (field_type_template(field.type) == "ARRAY")%>
        QCborArray tagsArray;
        for (const auto& item : tags_) {
            tagsArray.append(item.toCbor());
        }
        map["tags"] = tagsArray;
<%endif%>
<%if (field_type_template(field.type) == "COMPLEX")%>
        map["tags"] = tags_.toCbor();
<%endif%>

<%if (field_type_template(field.type) == "INT")%>
        map["config"] = QCborValue(config_);
<%endif%>
<%if (field_type_template(field.type) == "FLOAT")%>
        map["config"] = QCborValue(config_);
<%endif%>
<%if (field_type_template(field.type) == "STRING")%>
        map["config"] = QCborValue(config_);
<%endif%>
<%if (field_type_template(field.type) == "BOOL")%>
        map["config"] = QCborValue(config_);
<%endif%>
<%if (field_type_template(field.type) == "BYTES")%>
        map["config"] = QCborValue(config_);
<%endif%>
<%if (field_type_template(field.type) == "ARRAY")%>
        QCborArray configArray;
        for (const auto& item : config_) {
            configArray.append(item.toCbor());
        }
        map["config"] = configArray;
<%endif%>
<%if (field_type_template(field.type) == "COMPLEX")%>
        map["config"] = config_.toCbor();
<%endif%>


        return map;
    }
    
    void fromCbor(const QCborValue& cbor) override {
        QCborMap map = cbor.toMap();


<%if (field_type_template(field.type) == "INT")%>
        if (map.contains("title")) {
            title_ = map["title"].toInteger();
        }
<%endif%>
<%if (field_type_template(field.type) == "FLOAT")%>
        if (map.contains("title")) {
            title_ = map["title"].toDouble();
        }
<%endif%>
<%if (field_type_template(field.type) == "STRING")%>
        if (map.contains("title")) {
            title_ = map["title"].toString();
        }
<%endif%>
<%if (field_type_template(field.type) == "BOOL")%>
        if (map.contains("title")) {
            title_ = map["title"].toBool();
        }
<%endif%>
<%if (field_type_template(field.type) == "BYTES")%>
        if (map.contains("title")) {
            title_ = map["title"].toByteArray();
        }
<%endif%>
<%if (field_type_template(field.type) == "ARRAY")%>
        if (map.contains("title")) {
            QCborArray titleArray = map["title"].toArray();
            title_.clear();
            for (const auto& item : titleArray) {
                QString element;
                element.fromCbor(item);
                title_.append(element);
            }
        }
<%endif%>
<%if (field_type_template(field.type) == "COMPLEX")%>
        if (map.contains("title")) {
            title_.fromCbor(map["title"]);
        }
<%endif%>

<%if (field_type_template(field.type) == "INT")%>
        if (map.contains("description")) {
            description_ = map["description"].toInteger();
        }
<%endif%>
<%if (field_type_template(field.type) == "FLOAT")%>
        if (map.contains("description")) {
            description_ = map["description"].toDouble();
        }
<%endif%>
<%if (field_type_template(field.type) == "STRING")%>
        if (map.contains("description")) {
            description_ = map["description"].toString();
        }
<%endif%>
<%if (field_type_template(field.type) == "BOOL")%>
        if (map.contains("description")) {
            description_ = map["description"].toBool();
        }
<%endif%>
<%if (field_type_template(field.type) == "BYTES")%>
        if (map.contains("description")) {
            description_ = map["description"].toByteArray();
        }
<%endif%>
<%if (field_type_template(field.type) == "ARRAY")%>
        if (map.contains("description")) {
            QCborArray descriptionArray = map["description"].toArray();
            description_.clear();
            for (const auto& item : descriptionArray) {
                QString element;
                element.fromCbor(item);
                description_.append(element);
            }
        }
<%endif%>
<%if (field_type_template(field.type) == "COMPLEX")%>
        if (map.contains("description")) {
            description_.fromCbor(map["description"]);
        }
<%endif%>

<%if (field_type_template(field.type) == "INT")%>
        if (map.contains("completed")) {
            completed_ = map["completed"].toInteger();
        }
<%endif%>
<%if (field_type_template(field.type) == "FLOAT")%>
        if (map.contains("completed")) {
            completed_ = map["completed"].toDouble();
        }
<%endif%>
<%if (field_type_template(field.type) == "STRING")%>
        if (map.contains("completed")) {
            completed_ = map["completed"].toString();
        }
<%endif%>
<%if (field_type_template(field.type) == "BOOL")%>
        if (map.contains("completed")) {
            completed_ = map["completed"].toBool();
        }
<%endif%>
<%if (field_type_template(field.type) == "BYTES")%>
        if (map.contains("completed")) {
            completed_ = map["completed"].toByteArray();
        }
<%endif%>
<%if (field_type_template(field.type) == "ARRAY")%>
        if (map.contains("completed")) {
            QCborArray completedArray = map["completed"].toArray();
            completed_.clear();
            for (const auto& item : completedArray) {
                bool element;
                element.fromCbor(item);
                completed_.append(element);
            }
        }
<%endif%>
<%if (field_type_template(field.type) == "COMPLEX")%>
        if (map.contains("completed")) {
            completed_.fromCbor(map["completed"]);
        }
<%endif%>

<%if (field_type_template(field.type) == "INT")%>
        if (map.contains("tags")) {
            tags_ = map["tags"].toInteger();
        }
<%endif%>
<%if (field_type_template(field.type) == "FLOAT")%>
        if (map.contains("tags")) {
            tags_ = map["tags"].toDouble();
        }
<%endif%>
<%if (field_type_template(field.type) == "STRING")%>
        if (map.contains("tags")) {
            tags_ = map["tags"].toString();
        }
<%endif%>
<%if (field_type_template(field.type) == "BOOL")%>
        if (map.contains("tags")) {
            tags_ = map["tags"].toBool();
        }
<%endif%>
<%if (field_type_template(field.type) == "BYTES")%>
        if (map.contains("tags")) {
            tags_ = map["tags"].toByteArray();
        }
<%endif%>
<%if (field_type_template(field.type) == "ARRAY")%>
        if (map.contains("tags")) {
            QCborArray tagsArray = map["tags"].toArray();
            tags_.clear();
            for (const auto& item : tagsArray) {
                QVector<QString> element;
                element.fromCbor(item);
                tags_.append(element);
            }
        }
<%endif%>
<%if (field_type_template(field.type) == "COMPLEX")%>
        if (map.contains("tags")) {
            tags_.fromCbor(map["tags"]);
        }
<%endif%>

<%if (field_type_template(field.type) == "INT")%>
        if (map.contains("config")) {
            config_ = map["config"].toInteger();
        }
<%endif%>
<%if (field_type_template(field.type) == "FLOAT")%>
        if (map.contains("config")) {
            config_ = map["config"].toDouble();
        }
<%endif%>
<%if (field_type_template(field.type) == "STRING")%>
        if (map.contains("config")) {
            config_ = map["config"].toString();
        }
<%endif%>
<%if (field_type_template(field.type) == "BOOL")%>
        if (map.contains("config")) {
            config_ = map["config"].toBool();
        }
<%endif%>
<%if (field_type_template(field.type) == "BYTES")%>
        if (map.contains("config")) {
            config_ = map["config"].toByteArray();
        }
<%endif%>
<%if (field_type_template(field.type) == "ARRAY")%>
        if (map.contains("config")) {
            QCborArray configArray = map["config"].toArray();
            config_.clear();
            for (const auto& item : configArray) {
                Config element;
                element.fromCbor(item);
                config_.append(element);
            }
        }
<%endif%>
<%if (field_type_template(field.type) == "COMPLEX")%>
        if (map.contains("config")) {
            config_.fromCbor(map["config"]);
        }
<%endif%>


    }
    
    QStringList fields() const override {
        return QStringList{"title""description""completed""tags""config"};
    }
    
    QString fieldOriginTypeName(const QString& fieldName) const override {


        if (fieldName == "title") {
            return "string";
        }

        if (fieldName == "description") {
            return "string";
        }

        if (fieldName == "completed") {
            return "bool";
        }

        if (fieldName == "tags") {
            return "repeated string";
        }

        if (fieldName == "config") {
            return "Config";
        }

        return QString();

    }
    
    QList<QSharedPointer<IAnnotation>> annotations() const override {



    }
    
    QList<QSharedPointer<IAnnotation>> fieldAnnotations(const QString& fieldName) const override {


        if (fieldName == "title") {
            QList<QSharedPointer<void>> result;

            return result;
        }
<%endforeach%>

        return QList<QSharedPointer<IAnnotation>>();
    }
    
    QString description() const override {
        return "Generated struct Task";
    }
    
    QString fieldDescription(const QString& fieldName) const override {

        if (argumentName == "title") {
            return "field.description";
        }

        if (argumentName == "description") {
            return "field.description";
        }

        if (argumentName == "completed") {
            return "field.description";
        }

        if (argumentName == "tags") {
            return "field.description";
        }

        if (argumentName == "config") {
            return "field.description";
        }

        return QString();
    }
    
    QVariant value(const QString& fieldName) const override {

        if (argumentName == "title") {
            return QVariant::fromValue(title_);
        }

        if (argumentName == "description") {
            return QVariant::fromValue(description_);
        }

        if (argumentName == "completed") {
            return QVariant::fromValue(completed_);
        }

        if (argumentName == "tags") {
            return QVariant::fromValue(tags_);
        }

        if (argumentName == "config") {
            return QVariant::fromValue(config_);
        }

        return QVariant();
    }
    
    void value(const QString& fieldName, const QVariant& value) override {

        if (argumentName == "title") {
            title_ = value.value<QString>();
            return;
        }

        if (argumentName == "description") {
            description_ = value.value<QString>();
            return;
        }

        if (argumentName == "completed") {
            completed_ = value.value<bool>();
            return;
        }

        if (argumentName == "tags") {
            tags_ = value.value<QVector<QString>>();
            return;
        }

        if (argumentName == "config") {
            config_ = value.value<Config>();
            return;
        }

    }
    
    // 特定于Task的访问器



    QString getTitle() const {
        return title_;
    }


    void setTitle(const QString& value) {
        title_ = value;
    }



    QString getDescription() const {
        return description_;
    }


    void setDescription(const QString& value) {
        description_ = value;
    }



    bool getCompleted() const {
        return completed_;
    }


    void setCompleted(const bool& value) {
        completed_ = value;
    }



    QVector<QString> getTags() const {
        return tags_;
    }


    void setTags(const QVector<QString>& value) {
        tags_ = value;
    }



    Config getConfig() const {
        return config_;
    }


    void setConfig(const Config& value) {
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

    Config config_;


}; 





} // namespace examples


 
