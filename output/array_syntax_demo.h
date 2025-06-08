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
// 生成时间: 2025-06-08 18:49:33
// 源文件: unknown.mota

using namespace ymf;



// Option注解
class MODEL_EXPORT OptionAnnotation : public IAnnotation {
public:
    OptionAnnotation() = default;
    
    
    // 实现IAnnotation接口
    QString name() const override {
        return "Option";
    }
    
    QVariant argument(const QString& argumentName) const override {
        if (argumentName == QLatin1String("text")) return QVariant::fromValue(text_);
        if (argumentName == QLatin1String("value")) return QVariant::fromValue(value_);
        if (argumentName == QLatin1String("enabled")) return QVariant::fromValue(enabled_);
        return QVariant();
    }
    
    QStringList argumentNames() const override {
        return QStringList{QLatin1String("text"), QLatin1String("value"), QLatin1String("enabled")};
    }
    
    // 特定于Option的访问器
        // text字段的访问器
    QString getText() const {
        return text_;
    }
    
    void setText(const QString& value) {
        text_ = value;
    } 

        // value字段的访问器
    QString getValue() const {
        return value_;
    }
    
    void setValue(const QString& value) {
        value_ = value;
    } 

        // enabled字段的访问器
    bool getEnabled() const {
        return enabled_;
    }
    
    void setEnabled(const bool& value) {
        enabled_ = value;
    } 
    
private:
    QString text_;
    QString value_;
    bool enabled_;
}; 

// Validator注解
class MODEL_EXPORT ValidatorAnnotation : public IAnnotation {
public:
    ValidatorAnnotation() = default;
    
    
    // 实现IAnnotation接口
    QString name() const override {
        return "Validator";
    }
    
    QVariant argument(const QString& argumentName) const override {
        if (argumentName == QLatin1String("min")) return QVariant::fromValue(min_);
        if (argumentName == QLatin1String("max")) return QVariant::fromValue(max_);
        if (argumentName == QLatin1String("allowedValues")) return QVariant::fromValue(allowedValues_);
        return QVariant();
    }
    
    QStringList argumentNames() const override {
        return QStringList{QLatin1String("min"), QLatin1String("max"), QLatin1String("allowedValues")};
    }
    
    // 特定于Validator的访问器
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

        // allowedValues字段的访问器
    QVector<QString> getAllowedValues() const {
        return allowedValues_;
    }
    
    void setAllowedValues(const QVector<QString>& value) {
        allowedValues_ = value;
    } 
    
private:
    int32_t min_;
    int32_t max_;
    QVector<QString> allowedValues_;
}; 

// UIConfig注解
class MODEL_EXPORT UIConfigAnnotation : public IAnnotation {
public:
    UIConfigAnnotation() = default;
    
    
    // 实现IAnnotation接口
    QString name() const override {
        return "UIConfig";
    }
    
    QVariant argument(const QString& argumentName) const override {
        if (argumentName == QLatin1String("type")) return QVariant::fromValue(type_);
        if (argumentName == QLatin1String("options")) return QVariant::fromValue(options_);
        if (argumentName == QLatin1String("validator")) return QVariant::fromValue(validator_);
        return QVariant();
    }
    
    QStringList argumentNames() const override {
        return QStringList{QLatin1String("type"), QLatin1String("options"), QLatin1String("validator")};
    }
    
    // 特定于UIConfig的访问器
        // type字段的访问器
    QString getType() const {
        return type_;
    }
    
    void setType(const QString& value) {
        type_ = value;
    } 

        // options字段的访问器
    QVector<OptionAnnotation> getOptions() const {
        return options_;
    }
    
    void setOptions(const QVector<OptionAnnotation>& value) {
        options_ = value;
    } 

        // validator字段的访问器
    ValidatorAnnotation getValidator() const {
        return validator_;
    }
    
    void setValidator(const ValidatorAnnotation& value) {
        validator_ = value;
    } 
    
private:
    QString type_;
    QVector<OptionAnnotation> options_;
    ValidatorAnnotation validator_;
}; 

// BaseAnnotation注解
class MODEL_EXPORT BaseAnnotationAnnotation : public IAnnotation {
public:
    BaseAnnotationAnnotation() = default;
    
    
    // 实现IAnnotation接口
    QString name() const override {
        return "BaseAnnotation";
    }
    
    QVariant argument(const QString& argumentName) const override {
        if (argumentName == QLatin1String("description")) return QVariant::fromValue(description_);
        return QVariant();
    }
    
    QStringList argumentNames() const override {
        return QStringList{QLatin1String("description")};
    }
    
    // 特定于BaseAnnotation的访问器
        // description字段的访问器
    QString getDescription() const {
        return description_;
    }
    
    void setDescription(const QString& value) {
        description_ = value;
    } 
    
private:
    QString description_;
}; 

// ExtendedAnnotation注解
class MODEL_EXPORT ExtendedAnnotationAnnotation : public IAnnotation {
public:
    ExtendedAnnotationAnnotation() = default;
    
    
    // 实现IAnnotation接口
    QString name() const override {
        return "ExtendedAnnotation";
    }
    
    QVariant argument(const QString& argumentName) const override {
        if (argumentName == QLatin1String("priority")) return QVariant::fromValue(priority_);
        return QVariant();
    }
    
    QStringList argumentNames() const override {
        return QStringList{QLatin1String("priority")};
    }
    
    // 特定于ExtendedAnnotation的访问器
        // priority字段的访问器
    int32_t getPriority() const {
        return priority_;
    }
    
    void setPriority(const int32_t& value) {
        priority_ = value;
    } 
    
private:
    int32_t priority_;
}; 

// Configuration结构体

class MODEL_EXPORT ConfigurationModel : public IModel {
public:
    ConfigurationModel() = default;
    
    
    // 实现IModel接口
    QCborValue toCbor() const override {
        QCborMap map;
        QCborArray numbersArray;
        for (const auto& item : getNumbers()) {
            numbersArray.append(QCborValue(item));
        }
        map.insert(QLatin1String("numbers"), numbersArray);
        QCborArray tagsArray;
        for (const auto& item : getTags()) {
            tagsArray.append(QCborValue(item));
        }
        map.insert(QLatin1String("tags"), tagsArray);
        map.insert(QLatin1String("priority"), QCborValue(getPriority()));
        QCborArray matrixArray;
        for (const auto& item : getMatrix()) {
            matrixArray.append(item.toCbor());
        }
        map.insert(QLatin1String("matrix"), matrixArray);
        map.insert(QLatin1String("demo"), QCborValue(getDemo()));
        return map;
    }
    
    void fromCbor(const QCborValue& cbor) override {
        QCborMap map = cbor.toMap();
        QCborArray numbersArray = map.value(QLatin1String("numbers")).toArray();
        QVector<int32_t> numbers;
        for (const auto& itemValue : numbersArray) {
            numbers.append(static_cast<int32_t>(itemValue.toInteger()));
        }
        setNumbers(numbers);
        QCborArray tagsArray = map.value(QLatin1String("tags")).toArray();
        QVector<QString> tags;
        for (const auto& itemValue : tagsArray) {
            tags.append(static_cast<QString>(itemValue.toString()));
        }
        setTags(tags);
        setPriority(map.value(QLatin1String("priority")).toString());
        QCborArray matrixArray = map.value(QLatin1String("matrix")).toArray();
        QVector<QVector<int32_t>> matrix;
        for (const auto& itemValue : matrixArray) {
            QVector<int32_t> item;
            item.fromCbor(itemValue);
            matrix.append(item);
        }
        setMatrix(matrix);
        setDemo(map.value(QLatin1String("demo")).toString());
    }
    
    QStringList fields() const override {
        return QStringList{QLatin1String("numbers"), QLatin1String("tags"), QLatin1String("priority"), QLatin1String("matrix"), QLatin1String("demo")};
    }
    
    QString fieldOriginTypeName(const QString& fieldName) const override {
        if (fieldName == QLatin1String("numbers")) return QLatin1String("repeated int32");
        if (fieldName == QLatin1String("tags")) return QLatin1String("repeated string");
        if (fieldName == QLatin1String("priority")) return QLatin1String("string");
        if (fieldName == QLatin1String("matrix")) return QLatin1String("repeated repeated int32");
        if (fieldName == QLatin1String("demo")) return QLatin1String("string");
        return QLatin1String("");
    }
    
    QList<QSharedPointer<IAnnotation>> annotations() const override {
        
        return QList<QSharedPointer<IAnnotation>>();
    }
    
    QList<QSharedPointer<void>> fieldAnnotations(const QString& fieldName) const override {
        if (fieldName == QLatin1String("numbers")) {
            return QList<QSharedPointer<void>>();
        }
        if (fieldName == QLatin1String("tags")) {
            return QList<QSharedPointer<void>>();
        }
        if (fieldName == QLatin1String("priority")) {
            return QList<QSharedPointer<void>>();
        }
        if (fieldName == QLatin1String("matrix")) {
            return QList<QSharedPointer<void>>();
        }
        if (fieldName == QLatin1String("demo")) {
            return QList<QSharedPointer<void>>();
        }
        return QList<QSharedPointer<void>>();
    }
    
    QString description() const override {
        return "Generated from struct Configuration";
    }
    
    QString fieldDescription(const QString& fieldName) const override {
        
        return QString();
    }
    
    QVariant value(const QString& fieldName) const override {
        if (fieldName == QLatin1String("numbers")) return QVariant::fromValue(numbers_);
        if (fieldName == QLatin1String("tags")) return QVariant::fromValue(tags_);
        if (fieldName == QLatin1String("priority")) return QVariant::fromValue(priority_);
        if (fieldName == QLatin1String("matrix")) return QVariant::fromValue(matrix_);
        if (fieldName == QLatin1String("demo")) return QVariant::fromValue(demo_);
        return QVariant();
    }
    
    void value(const QString& fieldName, const QVariant& value) override {
        if (fieldName == QLatin1String("numbers")) {
            numbers_ = value.value<QVector<int32_t>>();
            return;
        }
        if (fieldName == QLatin1String("tags")) {
            tags_ = value.value<QVector<QString>>();
            return;
        }
        if (fieldName == QLatin1String("priority")) {
            priority_ = value.value<QString>();
            return;
        }
        if (fieldName == QLatin1String("matrix")) {
            matrix_ = value.value<QVector<QVector<int32_t>>>();
            return;
        }
        if (fieldName == QLatin1String("demo")) {
            demo_ = value.value<QString>();
            return;
        }
    }
    
    // 特定于Configuration的访问器
        // numbers字段的访问器
    QVector<int32_t> getNumbers() const {
        return numbers_;
    }
    
    void setNumbers(const QVector<int32_t>& value) {
        numbers_ = value;
    } 

        // tags字段的访问器
    QVector<QString> getTags() const {
        return tags_;
    }
    
    void setTags(const QVector<QString>& value) {
        tags_ = value;
    } 

        // priority字段的访问器
    QString getPriority() const {
        return priority_;
    }
    
    void setPriority(const QString& value) {
        priority_ = value;
    } 

        // matrix字段的访问器
    QVector<QVector<int32_t>> getMatrix() const {
        return matrix_;
    }
    
    void setMatrix(const QVector<QVector<int32_t>>& value) {
        matrix_ = value;
    } 

        // demo字段的访问器
    QString getDemo() const {
        return demo_;
    }
    
    void setDemo(const QString& value) {
        demo_ = value;
    } 
    
protected:
    QString modelName() const override {
        return "Configuration";
    }
    
private:
    QVector<int32_t> numbers_;
    QVector<QString> tags_;
    QString priority_;
    QVector<QVector<int32_t>> matrix_;
    QString demo_;
    
    // 变更通知
    void notifyChange();
};


// Status枚举
enum class Status {
    PENDING = 0,
    RUNNING = 1,
    COMPLETED = 2
};

// Status辅助函数
namespace StatusHelper {
    // 将枚举值转换为字符串
    inline QString toString(Status value) {
        switch (value) {
            case Status::PENDING:
                return QLatin1String("PENDING");
            case Status::RUNNING:
                return QLatin1String("RUNNING");
            case Status::COMPLETED:
                return QLatin1String("COMPLETED");
            default:
                return QString();
        }
    }
    
    // 将字符串转换为枚举值
    inline Status fromString(const QString& str) {
        if (str == QLatin1String("PENDING")) {
            return Status::PENDING;
        } else if (str == QLatin1String("RUNNING")) {
            return Status::RUNNING;
        } else if (str == QLatin1String("COMPLETED")) {
            return Status::COMPLETED;
        }
        return Status::PENDING;
    }
    
    // 获取所有枚举值的字符串表示
    inline QStringList allValues() {
        return QStringList() << QLatin1String("PENDING") << QLatin1String("RUNNING") << QLatin1String("COMPLETED");
    }
    
    // 获取所有枚举值的UI显示名称
    inline QStringList allDisplayNames() {
        return QStringList() << QLatin1String("PENDING") << QLatin1String("RUNNING") << QLatin1String("COMPLETED");
    }
    
    // 获取整个枚举的注解
    inline QList<QSharedPointer<IAnnotation>> annotations() {
                QList<QSharedPointer<IAnnotation>> result;
                return result;
    }
    
    // 获取特定枚举值的注解
    inline QList<QSharedPointer<IAnnotation>> valueAnnotations(Status value) {
        switch (value) {
            case Status::PENDING: {
                QList<QSharedPointer<IAnnotation>> result;
                // TODO: 创建 Option 注解实例
                return result;
            }
            case Status::RUNNING: {
                QList<QSharedPointer<IAnnotation>> result;
                // TODO: 创建 Option 注解实例
                return result;
            }
            case Status::COMPLETED: {
                QList<QSharedPointer<IAnnotation>> result;
                // TODO: 创建 Option 注解实例
                return result;
            }
            default:
                return QList<QSharedPointer<IAnnotation>>();
        }
    }
    
    // 获取特定枚举值的注解（通过字符串）
    inline QList<QSharedPointer<IAnnotation>> valueAnnotations(const QString& valueName) {
        if (valueName == "PENDING") {
                QList<QSharedPointer<IAnnotation>> result;
                // TODO: 创建 Option 注解实例
                return result;
        } else if (valueName == "RUNNING") {
                QList<QSharedPointer<IAnnotation>> result;
                // TODO: 创建 Option 注解实例
                return result;
        } else if (valueName == "COMPLETED") {
                QList<QSharedPointer<IAnnotation>> result;
                // TODO: 创建 Option 注解实例
                return result;
        }
        return QList<QSharedPointer<IAnnotation>>();
    }
}


// TaskConfig块
class MODEL_EXPORT TaskConfigBlock : public IBlock {
public:
    TaskConfigBlock() = default;
    
    
    // 实现IBlock接口
    QCborValue toCbor() const override {
        QCborMap map;
        map.insert(QLatin1String("name"), QCborValue(getName()));
        map.insert(QLatin1String("status"), QCborValue(static_cast<int>(getStatus())));
        QCborArray dependenciesArray;
        for (const auto& item : getDependencies()) {
            dependenciesArray.append(QCborValue(item));
        }
        map.insert(QLatin1String("dependencies"), dependenciesArray);
        return map;
    }
    
    void fromCbor(const QCborValue& cbor) override {
        QCborMap map = cbor.toMap();
        setName(map.value(QLatin1String("name")).toString());
        setStatus(static_cast<Status>(map.value(QLatin1String("status")).toInteger()));
        QCborArray dependenciesArray = map.value(QLatin1String("dependencies")).toArray();
        QVector<QString> dependencies;
        for (const auto& itemValue : dependenciesArray) {
            dependencies.append(static_cast<QString>(itemValue.toString()));
        }
        setDependencies(dependencies);
    }
    
    QString name() const override {
        return "TaskConfig";
    }
    
    QStringList fields() const override {
        return QStringList{QLatin1String("name"), QLatin1String("status"), QLatin1String("dependencies")};
    }
    
    QString fieldType(const QString& fieldName) const override {
        if (fieldName == QLatin1String("name")) return QLatin1String("string");
        if (fieldName == QLatin1String("status")) return QLatin1String("Status");
        if (fieldName == QLatin1String("dependencies")) return QLatin1String("repeated string");
        return QLatin1String("");
    }
    
    QList<QSharedPointer<IAnnotation>> annotations() const override {
        
        return QList<QSharedPointer<IAnnotation>>();
    }
    
    QList<QSharedPointer<void>> fieldAnnotation(const QString& fieldName) const override {
        if (fieldName == QLatin1String("name")) {
            return QList<QSharedPointer<void>>();
        }
        if (fieldName == QLatin1String("status")) {
            return QList<QSharedPointer<void>>();
        }
        if (fieldName == QLatin1String("dependencies")) {
            return QList<QSharedPointer<void>>();
        }
        return QList<QSharedPointer<void>>();
    }
    
    QString description() const override {
        return "Generated from block TaskConfig";
    }
    
    QString fieldDescription(const QString& fieldName) const override {
        
        return QString();
    }
    
    QVariant value(const QString& fieldName) const override {
        if (fieldName == QLatin1String("name")) return QVariant::fromValue(name_);
        if (fieldName == QLatin1String("status")) return QVariant::fromValue(status_);
        if (fieldName == QLatin1String("dependencies")) return QVariant::fromValue(dependencies_);
        return QVariant();
    }
    
    void value(const QString& fieldName, const QVariant& value) override {
        if (fieldName == QLatin1String("name")) {
            name_ = value.value<QString>();
            return;
        }
        if (fieldName == QLatin1String("status")) {
            status_ = value.value<Status>();
            return;
        }
        if (fieldName == QLatin1String("dependencies")) {
            dependencies_ = value.value<QVector<QString>>();
            return;
        }
    }
    
    // 特定于TaskConfig的访问器
        // name字段的访问器
    QString getName() const {
        return name_;
    }
    
    void setName(const QString& value) {
        name_ = value;
    } 

        // status字段的访问器
    Status getStatus() const {
        return status_;
    }
    
    void setStatus(const Status& value) {
        status_ = value;
    } 

        // dependencies字段的访问器
    QVector<QString> getDependencies() const {
        return dependencies_;
    }
    
    void setDependencies(const QVector<QString>& value) {
        dependencies_ = value;
    } 
    
private:
    QString name_;
    Status status_;
    QVector<QString> dependencies_;
};


// Project结构体

class MODEL_EXPORT ProjectModel : public IModel {
public:
    ProjectModel() = default;
    
    
    // 实现IModel接口
    QCborValue toCbor() const override {
        QCborMap map;
        map.insert(QLatin1String("name"), QCborValue(getName()));
        QCborArray tasksArray;
        for (const auto& item : getTasks()) {
            tasksArray.append(item.toCbor());
        }
        map.insert(QLatin1String("tasks"), tasksArray);
        return map;
    }
    
    void fromCbor(const QCborValue& cbor) override {
        QCborMap map = cbor.toMap();
        setName(map.value(QLatin1String("name")).toString());
        QCborArray tasksArray = map.value(QLatin1String("tasks")).toArray();
        QVector<TaskConfigBlock> tasks;
        for (const auto& itemValue : tasksArray) {
            TaskConfigBlock item;
            item.fromCbor(itemValue);
            tasks.append(item);
        }
        setTasks(tasks);
    }
    
    QStringList fields() const override {
        return QStringList{QLatin1String("name"), QLatin1String("tasks")};
    }
    
    QString fieldOriginTypeName(const QString& fieldName) const override {
        if (fieldName == QLatin1String("name")) return QLatin1String("string");
        if (fieldName == QLatin1String("tasks")) return QLatin1String("repeated TaskConfig");
        return QLatin1String("");
    }
    
    QList<QSharedPointer<IAnnotation>> annotations() const override {
        
        return QList<QSharedPointer<IAnnotation>>();
    }
    
    QList<QSharedPointer<void>> fieldAnnotations(const QString& fieldName) const override {
        if (fieldName == QLatin1String("name")) {
            return QList<QSharedPointer<void>>();
        }
        if (fieldName == QLatin1String("tasks")) {
            return QList<QSharedPointer<void>>();
        }
        return QList<QSharedPointer<void>>();
    }
    
    QString description() const override {
        return "Generated from struct Project";
    }
    
    QString fieldDescription(const QString& fieldName) const override {
        
        return QString();
    }
    
    QVariant value(const QString& fieldName) const override {
        if (fieldName == QLatin1String("name")) return QVariant::fromValue(name_);
        if (fieldName == QLatin1String("tasks")) return QVariant::fromValue(tasks_);
        return QVariant();
    }
    
    void value(const QString& fieldName, const QVariant& value) override {
        if (fieldName == QLatin1String("name")) {
            name_ = value.value<QString>();
            return;
        }
        if (fieldName == QLatin1String("tasks")) {
            tasks_ = value.value<QVector<TaskConfigBlock>>();
            return;
        }
    }
    
    // 特定于Project的访问器
        // name字段的访问器
    QString getName() const {
        return name_;
    }
    
    void setName(const QString& value) {
        name_ = value;
    } 

        // tasks字段的访问器
    QVector<TaskConfigBlock> getTasks() const {
        return tasks_;
    }
    
    void setTasks(const QVector<TaskConfigBlock>& value) {
        tasks_ = value;
    } 
    
protected:
    QString modelName() const override {
        return "Project";
    }
    
private:
    QString name_;
    QVector<TaskConfigBlock> tasks_;
    
    // 变更通知
    void notifyChange();
};



