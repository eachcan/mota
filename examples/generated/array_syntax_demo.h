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
// 生成时间: 2025-06-09 17:26:44
// 源文件: document.mota

using namespace ymf;




namespace examples {

namespace array_syntax {




// Option注解
class MODEL_EXPORT OptionAnnotation : public IAnnotation {
public:
    OptionAnnotation() = default;
    


    
    // 实现IAnnotation接口
    QString name() const override {
        return "Option";
    }
    
    QStringList argumentNames() const override {
        return QStringList{"text""value""enabled"};
    }
    
    QVariant argumentValue(const QString& argumentName) const override {

        if (argumentName == "text") {
            return QVariant::fromValue(text_);
        }

        if (argumentName == "value") {
            return QVariant::fromValue(value_);
        }

        if (argumentName == "enabled") {
            return QVariant::fromValue(enabled_);
        }

        return QVariant();
    }
    
    void argumentValue(const QString& argumentName, const QVariant& value) override {

        if (argumentName == "text") {
            text_ = value.value<QString>();
            return;
        }

        if (argumentName == "value") {
            value_ = value.value<QString>();
            return;
        }

        if (argumentName == "enabled") {
            enabled_ = value.value<bool>();
            return;
        }

    }
    
    QString description() const override {
        return "Generated annotation Option";
    }
    
    QString argumentDescription(const QString& argumentName) const override {

        if (argumentName == "text") {
            return "field.description";
        }

        if (argumentName == "value") {
            return "field.description";
        }

        if (argumentName == "enabled") {
            return "field.description";
        }

        return QString();
    }
    
    // 特定于Option的访问器



    QString getText() const {
        return text_;
    }


    void setText(const QString& value) {
        text_ = value;
    }



    QString getValue() const {
        return value_;
    }


    void setValue(const QString& value) {
        value_ = value;
    }



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
    
    QStringList argumentNames() const override {
        return QStringList{"min""max""allowedValues"};
    }
    
    QVariant argumentValue(const QString& argumentName) const override {

        if (argumentName == "min") {
            return QVariant::fromValue(min_);
        }

        if (argumentName == "max") {
            return QVariant::fromValue(max_);
        }

        if (argumentName == "allowedValues") {
            return QVariant::fromValue(allowedValues_);
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

        if (argumentName == "allowedValues") {
            allowedValues_ = value.value<QVector<QString>>();
            return;
        }

    }
    
    QString description() const override {
        return "Generated annotation Validator";
    }
    
    QString argumentDescription(const QString& argumentName) const override {

        if (argumentName == "min") {
            return "field.description";
        }

        if (argumentName == "max") {
            return "field.description";
        }

        if (argumentName == "allowedValues") {
            return "field.description";
        }

        return QString();
    }
    
    // 特定于Validator的访问器



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



    QVector<QString> getAllowedvalues() const {
        return allowedValues_;
    }


    void setAllowedvalues(const QVector<QString>& value) {
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
    
    QStringList argumentNames() const override {
        return QStringList{"type""options""validator"};
    }
    
    QVariant argumentValue(const QString& argumentName) const override {

        if (argumentName == "type") {
            return QVariant::fromValue(type_);
        }

        if (argumentName == "options") {
            return QVariant::fromValue(options_);
        }

        if (argumentName == "validator") {
            return QVariant::fromValue(validator_);
        }

        return QVariant();
    }
    
    void argumentValue(const QString& argumentName, const QVariant& value) override {

        if (argumentName == "type") {
            type_ = value.value<QString>();
            return;
        }

        if (argumentName == "options") {
            options_ = value.value<QVector<Option>>();
            return;
        }

        if (argumentName == "validator") {
            validator_ = value.value<Validator>();
            return;
        }

    }
    
    QString description() const override {
        return "Generated annotation UIConfig";
    }
    
    QString argumentDescription(const QString& argumentName) const override {

        if (argumentName == "type") {
            return "field.description";
        }

        if (argumentName == "options") {
            return "field.description";
        }

        if (argumentName == "validator") {
            return "field.description";
        }

        return QString();
    }
    
    // 特定于UIConfig的访问器



    QString getType() const {
        return type_;
    }


    void setType(const QString& value) {
        type_ = value;
    }



    QVector<Option> getOptions() const {
        return options_;
    }


    void setOptions(const QVector<Option>& value) {
        options_ = value;
    }



    Validator getValidator() const {
        return validator_;
    }


    void setValidator(const Validator& value) {
        validator_ = value;
    }



    
private:


    QString type_;

    QVector<Option> options_;

    Validator validator_;


}; 


// BaseAnnotation注解
class MODEL_EXPORT BaseAnnotationAnnotation : public IAnnotation {
public:
    BaseAnnotationAnnotation() = default;
    


    
    // 实现IAnnotation接口
    QString name() const override {
        return "BaseAnnotation";
    }
    
    QStringList argumentNames() const override {
        return QStringList{"description"};
    }
    
    QVariant argumentValue(const QString& argumentName) const override {

        if (argumentName == "description") {
            return QVariant::fromValue(description_);
        }

        return QVariant();
    }
    
    void argumentValue(const QString& argumentName, const QVariant& value) override {

        if (argumentName == "description") {
            description_ = value.value<QString>();
            return;
        }

    }
    
    QString description() const override {
        return "Generated annotation BaseAnnotation";
    }
    
    QString argumentDescription(const QString& argumentName) const override {

        if (argumentName == "description") {
            return "field.description";
        }

        return QString();
    }
    
    // 特定于BaseAnnotation的访问器



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
    
    QStringList argumentNames() const override {
        return QStringList{"priority"};
    }
    
    QVariant argumentValue(const QString& argumentName) const override {

        if (argumentName == "priority") {
            return QVariant::fromValue(priority_);
        }

        return QVariant();
    }
    
    void argumentValue(const QString& argumentName, const QVariant& value) override {

        if (argumentName == "priority") {
            priority_ = value.value<int32_t>();
            return;
        }

    }
    
    QString description() const override {
        return "Generated annotation ExtendedAnnotation";
    }
    
    QString argumentDescription(const QString& argumentName) const override {

        if (argumentName == "priority") {
            return "field.description";
        }

        return QString();
    }
    
    // 特定于ExtendedAnnotation的访问器



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
class MODEL_EXPORT ConfigurationModel :  {
public:
    ConfigurationModel() = default;
    


    
    // 实现IModel接口
    QCborValue toCbor() const override {
        QCborMap map;


<%if (field_type_template(field.type) == "INT")%>
        map["numbers"] = QCborValue(numbers_);
<%endif%>
<%if (field_type_template(field.type) == "FLOAT")%>
        map["numbers"] = QCborValue(numbers_);
<%endif%>
<%if (field_type_template(field.type) == "STRING")%>
        map["numbers"] = QCborValue(numbers_);
<%endif%>
<%if (field_type_template(field.type) == "BOOL")%>
        map["numbers"] = QCborValue(numbers_);
<%endif%>
<%if (field_type_template(field.type) == "BYTES")%>
        map["numbers"] = QCborValue(numbers_);
<%endif%>
<%if (field_type_template(field.type) == "ARRAY")%>
        QCborArray numbersArray;
        for (const auto& item : numbers_) {
            numbersArray.append(item.toCbor());
        }
        map["numbers"] = numbersArray;
<%endif%>
<%if (field_type_template(field.type) == "COMPLEX")%>
        map["numbers"] = numbers_.toCbor();
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

<%if (field_type_template(field.type) == "INT")%>
        map["matrix"] = QCborValue(matrix_);
<%endif%>
<%if (field_type_template(field.type) == "FLOAT")%>
        map["matrix"] = QCborValue(matrix_);
<%endif%>
<%if (field_type_template(field.type) == "STRING")%>
        map["matrix"] = QCborValue(matrix_);
<%endif%>
<%if (field_type_template(field.type) == "BOOL")%>
        map["matrix"] = QCborValue(matrix_);
<%endif%>
<%if (field_type_template(field.type) == "BYTES")%>
        map["matrix"] = QCborValue(matrix_);
<%endif%>
<%if (field_type_template(field.type) == "ARRAY")%>
        QCborArray matrixArray;
        for (const auto& item : matrix_) {
            matrixArray.append(item.toCbor());
        }
        map["matrix"] = matrixArray;
<%endif%>
<%if (field_type_template(field.type) == "COMPLEX")%>
        map["matrix"] = matrix_.toCbor();
<%endif%>

<%if (field_type_template(field.type) == "INT")%>
        map["demo"] = QCborValue(demo_);
<%endif%>
<%if (field_type_template(field.type) == "FLOAT")%>
        map["demo"] = QCborValue(demo_);
<%endif%>
<%if (field_type_template(field.type) == "STRING")%>
        map["demo"] = QCborValue(demo_);
<%endif%>
<%if (field_type_template(field.type) == "BOOL")%>
        map["demo"] = QCborValue(demo_);
<%endif%>
<%if (field_type_template(field.type) == "BYTES")%>
        map["demo"] = QCborValue(demo_);
<%endif%>
<%if (field_type_template(field.type) == "ARRAY")%>
        QCborArray demoArray;
        for (const auto& item : demo_) {
            demoArray.append(item.toCbor());
        }
        map["demo"] = demoArray;
<%endif%>
<%if (field_type_template(field.type) == "COMPLEX")%>
        map["demo"] = demo_.toCbor();
<%endif%>


        return map;
    }
    
    void fromCbor(const QCborValue& cbor) override {
        QCborMap map = cbor.toMap();


<%if (field_type_template(field.type) == "INT")%>
        if (map.contains("numbers")) {
            numbers_ = map["numbers"].toInteger();
        }
<%endif%>
<%if (field_type_template(field.type) == "FLOAT")%>
        if (map.contains("numbers")) {
            numbers_ = map["numbers"].toDouble();
        }
<%endif%>
<%if (field_type_template(field.type) == "STRING")%>
        if (map.contains("numbers")) {
            numbers_ = map["numbers"].toString();
        }
<%endif%>
<%if (field_type_template(field.type) == "BOOL")%>
        if (map.contains("numbers")) {
            numbers_ = map["numbers"].toBool();
        }
<%endif%>
<%if (field_type_template(field.type) == "BYTES")%>
        if (map.contains("numbers")) {
            numbers_ = map["numbers"].toByteArray();
        }
<%endif%>
<%if (field_type_template(field.type) == "ARRAY")%>
        if (map.contains("numbers")) {
            QCborArray numbersArray = map["numbers"].toArray();
            numbers_.clear();
            for (const auto& item : numbersArray) {
                QVector<int32_t> element;
                element.fromCbor(item);
                numbers_.append(element);
            }
        }
<%endif%>
<%if (field_type_template(field.type) == "COMPLEX")%>
        if (map.contains("numbers")) {
            numbers_.fromCbor(map["numbers"]);
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
                QString element;
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

<%if (field_type_template(field.type) == "INT")%>
        if (map.contains("matrix")) {
            matrix_ = map["matrix"].toInteger();
        }
<%endif%>
<%if (field_type_template(field.type) == "FLOAT")%>
        if (map.contains("matrix")) {
            matrix_ = map["matrix"].toDouble();
        }
<%endif%>
<%if (field_type_template(field.type) == "STRING")%>
        if (map.contains("matrix")) {
            matrix_ = map["matrix"].toString();
        }
<%endif%>
<%if (field_type_template(field.type) == "BOOL")%>
        if (map.contains("matrix")) {
            matrix_ = map["matrix"].toBool();
        }
<%endif%>
<%if (field_type_template(field.type) == "BYTES")%>
        if (map.contains("matrix")) {
            matrix_ = map["matrix"].toByteArray();
        }
<%endif%>
<%if (field_type_template(field.type) == "ARRAY")%>
        if (map.contains("matrix")) {
            QCborArray matrixArray = map["matrix"].toArray();
            matrix_.clear();
            for (const auto& item : matrixArray) {
                QVector<repeated int32> element;
                element.fromCbor(item);
                matrix_.append(element);
            }
        }
<%endif%>
<%if (field_type_template(field.type) == "COMPLEX")%>
        if (map.contains("matrix")) {
            matrix_.fromCbor(map["matrix"]);
        }
<%endif%>

<%if (field_type_template(field.type) == "INT")%>
        if (map.contains("demo")) {
            demo_ = map["demo"].toInteger();
        }
<%endif%>
<%if (field_type_template(field.type) == "FLOAT")%>
        if (map.contains("demo")) {
            demo_ = map["demo"].toDouble();
        }
<%endif%>
<%if (field_type_template(field.type) == "STRING")%>
        if (map.contains("demo")) {
            demo_ = map["demo"].toString();
        }
<%endif%>
<%if (field_type_template(field.type) == "BOOL")%>
        if (map.contains("demo")) {
            demo_ = map["demo"].toBool();
        }
<%endif%>
<%if (field_type_template(field.type) == "BYTES")%>
        if (map.contains("demo")) {
            demo_ = map["demo"].toByteArray();
        }
<%endif%>
<%if (field_type_template(field.type) == "ARRAY")%>
        if (map.contains("demo")) {
            QCborArray demoArray = map["demo"].toArray();
            demo_.clear();
            for (const auto& item : demoArray) {
                QString element;
                element.fromCbor(item);
                demo_.append(element);
            }
        }
<%endif%>
<%if (field_type_template(field.type) == "COMPLEX")%>
        if (map.contains("demo")) {
            demo_.fromCbor(map["demo"]);
        }
<%endif%>


    }
    
    QStringList fields() const override {
        return QStringList{"numbers""tags""priority""matrix""demo"};
    }
    
    QString fieldOriginTypeName(const QString& fieldName) const override {


        if (fieldName == "numbers") {
            return "repeated int32";
        }

        if (fieldName == "tags") {
            return "repeated string";
        }

        if (fieldName == "priority") {
            return "string";
        }

        if (fieldName == "matrix") {
            return "repeated repeated int32";
        }

        if (fieldName == "demo") {
            return "string";
        }

        return QString();

    }
    
    QList<QSharedPointer<IAnnotation>> annotations() const override {



    }
    
    QList<QSharedPointer<IAnnotation>> fieldAnnotations(const QString& fieldName) const override {


        if (fieldName == "numbers") {
            QList<QSharedPointer<void>> result;

            return result;
        }
<%endforeach%>

        return QList<QSharedPointer<IAnnotation>>();
    }
    
    QString description() const override {
        return "Generated struct Configuration";
    }
    
    QString fieldDescription(const QString& fieldName) const override {

        if (argumentName == "numbers") {
            return "field.description";
        }

        if (argumentName == "tags") {
            return "field.description";
        }

        if (argumentName == "priority") {
            return "field.description";
        }

        if (argumentName == "matrix") {
            return "field.description";
        }

        if (argumentName == "demo") {
            return "field.description";
        }

        return QString();
    }
    
    QVariant value(const QString& fieldName) const override {

        if (argumentName == "numbers") {
            return QVariant::fromValue(numbers_);
        }

        if (argumentName == "tags") {
            return QVariant::fromValue(tags_);
        }

        if (argumentName == "priority") {
            return QVariant::fromValue(priority_);
        }

        if (argumentName == "matrix") {
            return QVariant::fromValue(matrix_);
        }

        if (argumentName == "demo") {
            return QVariant::fromValue(demo_);
        }

        return QVariant();
    }
    
    void value(const QString& fieldName, const QVariant& value) override {

        if (argumentName == "numbers") {
            numbers_ = value.value<QVector<int32_t>>();
            return;
        }

        if (argumentName == "tags") {
            tags_ = value.value<QVector<QString>>();
            return;
        }

        if (argumentName == "priority") {
            priority_ = value.value<QString>();
            return;
        }

        if (argumentName == "matrix") {
            matrix_ = value.value<QVector<repeated int32>>();
            return;
        }

        if (argumentName == "demo") {
            demo_ = value.value<QString>();
            return;
        }

    }
    
    // 特定于Configuration的访问器



    QVector<int32_t> getNumbers() const {
        return numbers_;
    }


    void setNumbers(const QVector<int32_t>& value) {
        numbers_ = value;
    }



    QVector<QString> getTags() const {
        return tags_;
    }


    void setTags(const QVector<QString>& value) {
        tags_ = value;
    }



    QString getPriority() const {
        return priority_;
    }


    void setPriority(const QString& value) {
        priority_ = value;
    }



    QVector<repeated int32> getMatrix() const {
        return matrix_;
    }


    void setMatrix(const QVector<repeated int32>& value) {
        matrix_ = value;
    }



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

    QVector<repeated int32> matrix_;

    QString demo_;


}; 


// Status枚举
enum class Status : int32_t {


    PENDING = 0

    RUNNING = 1

    COMPLETED = 2


};

class MODEL_EXPORT StatusHelper {
public:
    static QString toString(Status value) {
        switch (value) {


            case Status::PENDING:
                return "value.string_value";

            case Status::RUNNING:
                return "value.string_value";

            case Status::COMPLETED:
                return "value.string_value";


            default:
                return QString();
        }
    }
    
    static Status fromString(const QString& str) {


        if (str == "value.string_value") {
            return Status::PENDING;
        }

        if (str == "value.string_value") {
            return Status::RUNNING;
        }

        if (str == "value.string_value") {
            return Status::COMPLETED;
        }


        return static_cast<Status>(0);
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
    
    static QList<QSharedPointer<IAnnotation>> valueAnnotations(Status value) {
        switch (value) {


            case Status::PENDING: {

            }
<%endforeach%>

            default:
                return QList<QSharedPointer<IAnnotation>>();
        }
    }
    
    static QList<QSharedPointer<IAnnotation>> valueAnnotationsByName(const QString& valueName) {


        if (valueName == "PENDING") {

        }
<%endforeach%>

        return QList<QSharedPointer<IAnnotation>>();
    }
    
    static QString description() {
        return "Generated enum Status";
    }
    
    static QString valueDescription(Status value) {
        switch (value) {

            case Status::PENDING:
                return "value.description";

            case Status::RUNNING:
                return "value.description";

            case Status::COMPLETED:
                return "value.description";

            default:
                return QString();
        }
    }
    
    static QString valueDescriptionByName(const QString& valueName) {

        if (valueName == "PENDING") {
            return "value.description";
        }

        if (valueName == "RUNNING") {
            return "value.description";
        }

        if (valueName == "COMPLETED") {
            return "value.description";
        }

        return QString();
    }
}; 


// TaskConfig块
class MODEL_EXPORT TaskConfigBlock :  {
public:
    TaskConfigBlock() = default;
    


    
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
        map["status"] = QCborValue(status_);
<%endif%>
<%if (field_type_template(field.type) == "FLOAT")%>
        map["status"] = QCborValue(status_);
<%endif%>
<%if (field_type_template(field.type) == "STRING")%>
        map["status"] = QCborValue(status_);
<%endif%>
<%if (field_type_template(field.type) == "BOOL")%>
        map["status"] = QCborValue(status_);
<%endif%>
<%if (field_type_template(field.type) == "BYTES")%>
        map["status"] = QCborValue(status_);
<%endif%>
<%if (field_type_template(field.type) == "ARRAY")%>
        QCborArray statusArray;
        for (const auto& item : status_) {
            statusArray.append(item.toCbor());
        }
        map["status"] = statusArray;
<%endif%>
<%if (field_type_template(field.type) == "COMPLEX")%>
        map["status"] = status_.toCbor();
<%endif%>

<%if (field_type_template(field.type) == "INT")%>
        map["dependencies"] = QCborValue(dependencies_);
<%endif%>
<%if (field_type_template(field.type) == "FLOAT")%>
        map["dependencies"] = QCborValue(dependencies_);
<%endif%>
<%if (field_type_template(field.type) == "STRING")%>
        map["dependencies"] = QCborValue(dependencies_);
<%endif%>
<%if (field_type_template(field.type) == "BOOL")%>
        map["dependencies"] = QCborValue(dependencies_);
<%endif%>
<%if (field_type_template(field.type) == "BYTES")%>
        map["dependencies"] = QCborValue(dependencies_);
<%endif%>
<%if (field_type_template(field.type) == "ARRAY")%>
        QCborArray dependenciesArray;
        for (const auto& item : dependencies_) {
            dependenciesArray.append(item.toCbor());
        }
        map["dependencies"] = dependenciesArray;
<%endif%>
<%if (field_type_template(field.type) == "COMPLEX")%>
        map["dependencies"] = dependencies_.toCbor();
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
        if (map.contains("status")) {
            status_ = map["status"].toInteger();
        }
<%endif%>
<%if (field_type_template(field.type) == "FLOAT")%>
        if (map.contains("status")) {
            status_ = map["status"].toDouble();
        }
<%endif%>
<%if (field_type_template(field.type) == "STRING")%>
        if (map.contains("status")) {
            status_ = map["status"].toString();
        }
<%endif%>
<%if (field_type_template(field.type) == "BOOL")%>
        if (map.contains("status")) {
            status_ = map["status"].toBool();
        }
<%endif%>
<%if (field_type_template(field.type) == "BYTES")%>
        if (map.contains("status")) {
            status_ = map["status"].toByteArray();
        }
<%endif%>
<%if (field_type_template(field.type) == "ARRAY")%>
        if (map.contains("status")) {
            QCborArray statusArray = map["status"].toArray();
            status_.clear();
            for (const auto& item : statusArray) {
                Status element;
                element.fromCbor(item);
                status_.append(element);
            }
        }
<%endif%>
<%if (field_type_template(field.type) == "COMPLEX")%>
        if (map.contains("status")) {
            status_.fromCbor(map["status"]);
        }
<%endif%>

<%if (field_type_template(field.type) == "INT")%>
        if (map.contains("dependencies")) {
            dependencies_ = map["dependencies"].toInteger();
        }
<%endif%>
<%if (field_type_template(field.type) == "FLOAT")%>
        if (map.contains("dependencies")) {
            dependencies_ = map["dependencies"].toDouble();
        }
<%endif%>
<%if (field_type_template(field.type) == "STRING")%>
        if (map.contains("dependencies")) {
            dependencies_ = map["dependencies"].toString();
        }
<%endif%>
<%if (field_type_template(field.type) == "BOOL")%>
        if (map.contains("dependencies")) {
            dependencies_ = map["dependencies"].toBool();
        }
<%endif%>
<%if (field_type_template(field.type) == "BYTES")%>
        if (map.contains("dependencies")) {
            dependencies_ = map["dependencies"].toByteArray();
        }
<%endif%>
<%if (field_type_template(field.type) == "ARRAY")%>
        if (map.contains("dependencies")) {
            QCborArray dependenciesArray = map["dependencies"].toArray();
            dependencies_.clear();
            for (const auto& item : dependenciesArray) {
                QVector<QString> element;
                element.fromCbor(item);
                dependencies_.append(element);
            }
        }
<%endif%>
<%if (field_type_template(field.type) == "COMPLEX")%>
        if (map.contains("dependencies")) {
            dependencies_.fromCbor(map["dependencies"]);
        }
<%endif%>


    }
    
    QString name() const override {
        return "TaskConfig";
    }
    
    QStringList fields() const override {
        return QStringList{"name""status""dependencies"};
    }
    
    QString fieldType(const QString& fieldName) const override {


        if (fieldName == "name") {
            return "string";
        }

        if (fieldName == "status") {
            return "Status";
        }

        if (fieldName == "dependencies") {
            return "repeated string";
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
        return "Generated block TaskConfig";
    }
    
    QString fieldDescription(const QString& fieldName) const override {

        if (argumentName == "name") {
            return "field.description";
        }

        if (argumentName == "status") {
            return "field.description";
        }

        if (argumentName == "dependencies") {
            return "field.description";
        }

        return QString();
    }
    
    QVariant value(const QString& fieldName) const override {

        if (argumentName == "name") {
            return QVariant::fromValue(name_);
        }

        if (argumentName == "status") {
            return QVariant::fromValue(status_);
        }

        if (argumentName == "dependencies") {
            return QVariant::fromValue(dependencies_);
        }

        return QVariant();
    }
    
    void value(const QString& fieldName, const QVariant& value) override {

        if (argumentName == "name") {
            name_ = value.value<QString>();
            return;
        }

        if (argumentName == "status") {
            status_ = value.value<Status>();
            return;
        }

        if (argumentName == "dependencies") {
            dependencies_ = value.value<QVector<QString>>();
            return;
        }

    }
    
    // 特定于TaskConfig的访问器



    QString getName() const {
        return name_;
    }


    void setName(const QString& value) {
        name_ = value;
    }



    Status getStatus() const {
        return status_;
    }


    void setStatus(const Status& value) {
        status_ = value;
    }



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
class MODEL_EXPORT ProjectModel :  {
public:
    ProjectModel() = default;
    


    
    // 实现IModel接口
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
        map["tasks"] = QCborValue(tasks_);
<%endif%>
<%if (field_type_template(field.type) == "FLOAT")%>
        map["tasks"] = QCborValue(tasks_);
<%endif%>
<%if (field_type_template(field.type) == "STRING")%>
        map["tasks"] = QCborValue(tasks_);
<%endif%>
<%if (field_type_template(field.type) == "BOOL")%>
        map["tasks"] = QCborValue(tasks_);
<%endif%>
<%if (field_type_template(field.type) == "BYTES")%>
        map["tasks"] = QCborValue(tasks_);
<%endif%>
<%if (field_type_template(field.type) == "ARRAY")%>
        QCborArray tasksArray;
        for (const auto& item : tasks_) {
            tasksArray.append(item.toCbor());
        }
        map["tasks"] = tasksArray;
<%endif%>
<%if (field_type_template(field.type) == "COMPLEX")%>
        map["tasks"] = tasks_.toCbor();
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
        if (map.contains("tasks")) {
            tasks_ = map["tasks"].toInteger();
        }
<%endif%>
<%if (field_type_template(field.type) == "FLOAT")%>
        if (map.contains("tasks")) {
            tasks_ = map["tasks"].toDouble();
        }
<%endif%>
<%if (field_type_template(field.type) == "STRING")%>
        if (map.contains("tasks")) {
            tasks_ = map["tasks"].toString();
        }
<%endif%>
<%if (field_type_template(field.type) == "BOOL")%>
        if (map.contains("tasks")) {
            tasks_ = map["tasks"].toBool();
        }
<%endif%>
<%if (field_type_template(field.type) == "BYTES")%>
        if (map.contains("tasks")) {
            tasks_ = map["tasks"].toByteArray();
        }
<%endif%>
<%if (field_type_template(field.type) == "ARRAY")%>
        if (map.contains("tasks")) {
            QCborArray tasksArray = map["tasks"].toArray();
            tasks_.clear();
            for (const auto& item : tasksArray) {
                QVector<TaskConfig> element;
                element.fromCbor(item);
                tasks_.append(element);
            }
        }
<%endif%>
<%if (field_type_template(field.type) == "COMPLEX")%>
        if (map.contains("tasks")) {
            tasks_.fromCbor(map["tasks"]);
        }
<%endif%>


    }
    
    QStringList fields() const override {
        return QStringList{"name""tasks"};
    }
    
    QString fieldOriginTypeName(const QString& fieldName) const override {


        if (fieldName == "name") {
            return "string";
        }

        if (fieldName == "tasks") {
            return "repeated TaskConfig";
        }

        return QString();

    }
    
    QList<QSharedPointer<IAnnotation>> annotations() const override {



    }
    
    QList<QSharedPointer<IAnnotation>> fieldAnnotations(const QString& fieldName) const override {


        if (fieldName == "name") {
            QList<QSharedPointer<void>> result;

            return result;
        }
<%endforeach%>

        return QList<QSharedPointer<IAnnotation>>();
    }
    
    QString description() const override {
        return "Generated struct Project";
    }
    
    QString fieldDescription(const QString& fieldName) const override {

        if (argumentName == "name") {
            return "field.description";
        }

        if (argumentName == "tasks") {
            return "field.description";
        }

        return QString();
    }
    
    QVariant value(const QString& fieldName) const override {

        if (argumentName == "name") {
            return QVariant::fromValue(name_);
        }

        if (argumentName == "tasks") {
            return QVariant::fromValue(tasks_);
        }

        return QVariant();
    }
    
    void value(const QString& fieldName, const QVariant& value) override {

        if (argumentName == "name") {
            name_ = value.value<QString>();
            return;
        }

        if (argumentName == "tasks") {
            tasks_ = value.value<QVector<TaskConfig>>();
            return;
        }

    }
    
    // 特定于Project的访问器



    QString getName() const {
        return name_;
    }


    void setName(const QString& value) {
        name_ = value;
    }



    QVector<TaskConfig> getTasks() const {
        return tasks_;
    }


    void setTasks(const QVector<TaskConfig>& value) {
        tasks_ = value;
    }



    
protected:
    QString modelName() const override {
        return "Project";
    }
    
private:


    QString name_;

    QVector<TaskConfig> tasks_;


}; 





} // namespace examples

} // namespace array_syntax


 
