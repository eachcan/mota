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
#include "yima-ui.h"


// 此文件由 Mota 代码生成器自动生成
// 生成时间: 2025-06-09 17:26:44
// 源文件: document.mota

using namespace ymf;




namespace examples {

namespace annotations {




// DateTimePicker注解
class MODEL_EXPORT DateTimePickerAnnotation : public IAnnotation {
public:
    DateTimePickerAnnotation() = default;
    


    
    // 实现IAnnotation接口
    QString name() const override {
        return "DateTimePicker";
    }
    
    QStringList argumentNames() const override {
        return QStringList{"format""placeholder""value""type""from""to"};
    }
    
    QVariant argumentValue(const QString& argumentName) const override {

        if (argumentName == "format") {
            return QVariant::fromValue(format_);
        }

        if (argumentName == "placeholder") {
            return QVariant::fromValue(placeholder_);
        }

        if (argumentName == "value") {
            return QVariant::fromValue(value_);
        }

        if (argumentName == "type") {
            return QVariant::fromValue(type_);
        }

        if (argumentName == "from") {
            return QVariant::fromValue(from_);
        }

        if (argumentName == "to") {
            return QVariant::fromValue(to_);
        }

        return QVariant();
    }
    
    void argumentValue(const QString& argumentName, const QVariant& value) override {

        if (argumentName == "format") {
            format_ = value.value<QString>();
            return;
        }

        if (argumentName == "placeholder") {
            placeholder_ = value.value<QString>();
            return;
        }

        if (argumentName == "value") {
            value_ = value.value<QString>();
            return;
        }

        if (argumentName == "type") {
            type_ = value.value<QString>();
            return;
        }

        if (argumentName == "from") {
            from_ = value.value<QString>();
            return;
        }

        if (argumentName == "to") {
            to_ = value.value<QString>();
            return;
        }

    }
    
    QString description() const override {
        return "Generated annotation DateTimePicker";
    }
    
    QString argumentDescription(const QString& argumentName) const override {

        if (argumentName == "format") {
            return "field.description";
        }

        if (argumentName == "placeholder") {
            return "field.description";
        }

        if (argumentName == "value") {
            return "field.description";
        }

        if (argumentName == "type") {
            return "field.description";
        }

        if (argumentName == "from") {
            return "field.description";
        }

        if (argumentName == "to") {
            return "field.description";
        }

        return QString();
    }
    
    // 特定于DateTimePicker的访问器



    QString getFormat() const {
        return format_;
    }


    void setFormat(const QString& value) {
        format_ = value;
    }



    QString getPlaceholder() const {
        return placeholder_;
    }


    void setPlaceholder(const QString& value) {
        placeholder_ = value;
    }



    QString getValue() const {
        return value_;
    }


    void setValue(const QString& value) {
        value_ = value;
    }



    QString getType() const {
        return type_;
    }


    void setType(const QString& value) {
        type_ = value;
    }



    QString getFrom() const {
        return from_;
    }


    void setFrom(const QString& value) {
        from_ = value;
    }



    QString getTo() const {
        return to_;
    }


    void setTo(const QString& value) {
        to_ = value;
    }



    
private:


    QString format_;

    QString placeholder_;

    QString value_;

    QString type_;

    QString from_;

    QString to_;


}; 


// ModeOption注解
class MODEL_EXPORT ModeOptionAnnotation : public IAnnotation {
public:
    ModeOptionAnnotation() = default;
    


    
    // 实现IAnnotation接口
    QString name() const override {
        return "ModeOption";
    }
    
    QStringList argumentNames() const override {
        return QStringList{"text""value"};
    }
    
    QVariant argumentValue(const QString& argumentName) const override {

        if (argumentName == "text") {
            return QVariant::fromValue(text_);
        }

        if (argumentName == "value") {
            return QVariant::fromValue(value_);
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

    }
    
    QString description() const override {
        return "Generated annotation ModeOption";
    }
    
    QString argumentDescription(const QString& argumentName) const override {

        if (argumentName == "text") {
            return "field.description";
        }

        if (argumentName == "value") {
            return "field.description";
        }

        return QString();
    }
    
    // 特定于ModeOption的访问器



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



    
private:


    QString text_;

    QString value_;


}; 


// ModeSelector注解
class MODEL_EXPORT ModeSelectorAnnotation : public IAnnotation {
public:
    ModeSelectorAnnotation() = default;
    


    
    // 实现IAnnotation接口
    QString name() const override {
        return "ModeSelector";
    }
    
    QStringList argumentNames() const override {
        return QStringList{"default""value"};
    }
    
    QVariant argumentValue(const QString& argumentName) const override {

        if (argumentName == "default") {
            return QVariant::fromValue(default_);
        }

        if (argumentName == "value") {
            return QVariant::fromValue(value_);
        }

        return QVariant();
    }
    
    void argumentValue(const QString& argumentName, const QVariant& value) override {

        if (argumentName == "default") {
            default_ = value.value<ModeOption>();
            return;
        }

        if (argumentName == "value") {
            value_ = value.value<QVector<ModeOption>>();
            return;
        }

    }
    
    QString description() const override {
        return "Generated annotation ModeSelector";
    }
    
    QString argumentDescription(const QString& argumentName) const override {

        if (argumentName == "default") {
            return "field.description";
        }

        if (argumentName == "value") {
            return "field.description";
        }

        return QString();
    }
    
    // 特定于ModeSelector的访问器



    ModeOption getDefault() const {
        return default_;
    }


    void setDefault(const ModeOption& value) {
        default_ = value;
    }



    QVector<ModeOption> getValue() const {
        return value_;
    }


    void setValue(const QVector<ModeOption>& value) {
        value_ = value;
    }



    
private:


    ModeOption default_;

    QVector<ModeOption> value_;


}; 


// RunMode结构体
class MODEL_EXPORT RunModeModel :  {
public:
    RunModeModel() = default;
    


    
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


    }
    
    QStringList fields() const override {
        return QStringList{"name"};
    }
    
    QString fieldOriginTypeName(const QString& fieldName) const override {


        if (fieldName == "name") {
            return "string";
        }

        return QString();

    }
    
    QList<QSharedPointer<IAnnotation>> annotations() const override {


        QList<QSharedPointer<IAnnotation>> annotations;
<%foreach ANNOTATIONS as annotation%>
        auto _annotation_<%=annotation.index%> = QSharedPointer<<%=annotation.class_name%>>::create();
<%foreach annotation.arguments as arg%>
        _annotation_<%=annotation.index%>-><%=arg.setter_name%>(









);
<%endforeach%>
        annotations.append(qSharedPointerCast<IAnnotation>(_annotation_<%=annotation.index%>));
<%endforeach%>
        return annotations;
<%else%>
        return QList<QSharedPointer<IAnnotation>>();


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
        return "Generated struct RunMode";
    }
    
    QString fieldDescription(const QString& fieldName) const override {

        if (argumentName == "name") {
            return "field.description";
        }

        return QString();
    }
    
    QVariant value(const QString& fieldName) const override {

        if (argumentName == "name") {
            return QVariant::fromValue(name_);
        }

        return QVariant();
    }
    
    void value(const QString& fieldName, const QVariant& value) override {

        if (argumentName == "name") {
            name_ = value.value<QString>();
            return;
        }

    }
    
    // 特定于RunMode的访问器



    QString getName() const {
        return name_;
    }


    void setName(const QString& value) {
        name_ = value;
    }



    
protected:
    QString modelName() const override {
        return "RunMode";
    }
    
private:


    QString name_;


}; 





} // namespace examples

} // namespace annotations


 
