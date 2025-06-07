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
// 生成时间: 2025-06-07 23:37:43
// 源文件: unknown.mota

using namespace ymf;


namespace examples::structs {


// Point2D块
class MODEL_EXPORT Point2DBlock : public IBlock {
public:
    Point2DBlock() = default;
    
    
    // 实现IBlock接口
    QCborValue toCbor() const override {
        QCborMap map;
        map.insert(QLatin1String("x"), QCborValue(getX()));
        map.insert(QLatin1String("y"), QCborValue(getY()));
        return map;
    }
    
    void fromCbor(const QCborValue& cbor) override {
        QCborMap map = cbor.toMap();
        setX(static_cast<float>(map.value(QLatin1String("x")).toDouble()));
        setY(static_cast<float>(map.value(QLatin1String("y")).toDouble()));
    }
    
    QString name() const override {
        return "Point2D";
    }
    
    QStringList fields() const override {
        return QStringList{QLatin1String("x"), QLatin1String("y")};
    }
    
    QString fieldType(const QString& fieldName) const override {
        if (fieldName == QLatin1String("x")) return QLatin1String("float32");
        if (fieldName == QLatin1String("y")) return QLatin1String("float32");
        return QLatin1String("");
    }
    
    QList<QSharedPointer<IAnnotation>> annotations() const override {
        
        return QList<QSharedPointer<IAnnotation>>();
    }
    
    QList<QSharedPointer<void>> fieldAnnotation(const QString& fieldName) const override {
        if (fieldName == QLatin1String("x")) {
            return QList<QSharedPointer<void>>();
        }
        if (fieldName == QLatin1String("y")) {
            return QList<QSharedPointer<void>>();
        }
        return QList<QSharedPointer<void>>();
    }
    
    QString description() const override {
        return "Generated from block Point2D";
    }
    
    QString fieldDescription(const QString& fieldName) const override {
        
        return QString();
    }
    
    QVariant value(const QString& fieldName) const override {
        if (fieldName == QLatin1String("x")) return QVariant::fromValue(x_);
        if (fieldName == QLatin1String("y")) return QVariant::fromValue(y_);
        return QVariant();
    }
    
    void value(const QString& fieldName, const QVariant& value) override {
        if (fieldName == QLatin1String("x")) {
            x_ = value.value<float>();
            return;
        }
        if (fieldName == QLatin1String("y")) {
            y_ = value.value<float>();
            return;
        }
    }
    
    // 特定于Point2D的访问器
        // x字段的访问器
    float getX() const {
        return x_;
    }
    
    void setX(const float& value) {
        x_ = value;
    } 

        // y字段的访问器
    float getY() const {
        return y_;
    }
    
    void setY(const float& value) {
        y_ = value;
    } 
    
private:
    float x_;
    float y_;
};


// Rectangle块
class MODEL_EXPORT RectangleBlock : public IBlock {
public:
    RectangleBlock() = default;
    
    
    // 实现IBlock接口
    QCborValue toCbor() const override {
        QCborMap map;
        map.insert(QLatin1String("topLeftX"), QCborValue(getTopLeftX()));
        map.insert(QLatin1String("topLeftY"), QCborValue(getTopLeftY()));
        map.insert(QLatin1String("bottomRightX"), QCborValue(getBottomRightX()));
        map.insert(QLatin1String("bottomRightY"), QCborValue(getBottomRightY()));
        map.insert(QLatin1String("label"), getLabel().toCbor());
        return map;
    }
    
    void fromCbor(const QCborValue& cbor) override {
        QCborMap map = cbor.toMap();
        setTopLeftX(static_cast<float>(map.value(QLatin1String("topLeftX")).toDouble()));
        setTopLeftY(static_cast<float>(map.value(QLatin1String("topLeftY")).toDouble()));
        setBottomRightX(static_cast<float>(map.value(QLatin1String("bottomRightX")).toDouble()));
        setBottomRightY(static_cast<float>(map.value(QLatin1String("bottomRightY")).toDouble()));
        Optional stringBlock label;
        label.fromCbor(map.value(QLatin1String("label")));
        setLabel(label);
    }
    
    QString name() const override {
        return "Rectangle";
    }
    
    QStringList fields() const override {
        return QStringList{QLatin1String("topLeftX"), QLatin1String("topLeftY"), QLatin1String("bottomRightX"), QLatin1String("bottomRightY"), QLatin1String("label")};
    }
    
    QString fieldType(const QString& fieldName) const override {
        if (fieldName == QLatin1String("topLeftX")) return QLatin1String("float32");
        if (fieldName == QLatin1String("topLeftY")) return QLatin1String("float32");
        if (fieldName == QLatin1String("bottomRightX")) return QLatin1String("float32");
        if (fieldName == QLatin1String("bottomRightY")) return QLatin1String("float32");
        if (fieldName == QLatin1String("label")) return QLatin1String("optional string");
        return QLatin1String("");
    }
    
    QList<QSharedPointer<IAnnotation>> annotations() const override {
        
        return QList<QSharedPointer<IAnnotation>>();
    }
    
    QList<QSharedPointer<void>> fieldAnnotation(const QString& fieldName) const override {
        if (fieldName == QLatin1String("topLeftX")) {
            return QList<QSharedPointer<void>>();
        }
        if (fieldName == QLatin1String("topLeftY")) {
            return QList<QSharedPointer<void>>();
        }
        if (fieldName == QLatin1String("bottomRightX")) {
            return QList<QSharedPointer<void>>();
        }
        if (fieldName == QLatin1String("bottomRightY")) {
            return QList<QSharedPointer<void>>();
        }
        if (fieldName == QLatin1String("label")) {
            return QList<QSharedPointer<void>>();
        }
        return QList<QSharedPointer<void>>();
    }
    
    QString description() const override {
        return "Generated from block Rectangle";
    }
    
    QString fieldDescription(const QString& fieldName) const override {
        
        return QString();
    }
    
    QVariant value(const QString& fieldName) const override {
        if (fieldName == QLatin1String("topLeftX")) return QVariant::fromValue(topLeftX_);
        if (fieldName == QLatin1String("topLeftY")) return QVariant::fromValue(topLeftY_);
        if (fieldName == QLatin1String("bottomRightX")) return QVariant::fromValue(bottomRightX_);
        if (fieldName == QLatin1String("bottomRightY")) return QVariant::fromValue(bottomRightY_);
        if (fieldName == QLatin1String("label")) return QVariant::fromValue(label_);
        return QVariant();
    }
    
    void value(const QString& fieldName, const QVariant& value) override {
        if (fieldName == QLatin1String("topLeftX")) {
            topLeftX_ = value.value<float>();
            return;
        }
        if (fieldName == QLatin1String("topLeftY")) {
            topLeftY_ = value.value<float>();
            return;
        }
        if (fieldName == QLatin1String("bottomRightX")) {
            bottomRightX_ = value.value<float>();
            return;
        }
        if (fieldName == QLatin1String("bottomRightY")) {
            bottomRightY_ = value.value<float>();
            return;
        }
        if (fieldName == QLatin1String("label")) {
            label_ = value.value<Optional stringBlock>();
            return;
        }
    }
    
    // 特定于Rectangle的访问器
        // topLeftX字段的访问器
    float getTopLeftX() const {
        return topLeftX_;
    }
    
    void setTopLeftX(const float& value) {
        topLeftX_ = value;
    } 

        // topLeftY字段的访问器
    float getTopLeftY() const {
        return topLeftY_;
    }
    
    void setTopLeftY(const float& value) {
        topLeftY_ = value;
    } 

        // bottomRightX字段的访问器
    float getBottomRightX() const {
        return bottomRightX_;
    }
    
    void setBottomRightX(const float& value) {
        bottomRightX_ = value;
    } 

        // bottomRightY字段的访问器
    float getBottomRightY() const {
        return bottomRightY_;
    }
    
    void setBottomRightY(const float& value) {
        bottomRightY_ = value;
    } 

        // label字段的访问器
    Optional stringBlock getLabel() const {
        return label_;
    }
    
    void setLabel(const Optional stringBlock& value) {
        label_ = value;
    } 
    
private:
    float topLeftX_;
    float topLeftY_;
    float bottomRightX_;
    float bottomRightY_;
    Optional stringBlock label_;
};


// Style块
class MODEL_EXPORT StyleBlock : public IBlock {
public:
    StyleBlock() = default;
    
    
    // 实现IBlock接口
    QCborValue toCbor() const override {
        QCborMap map;
        map.insert(QLatin1String("fillColor"), QCborValue(getFillColor()));
        map.insert(QLatin1String("strokeColor"), QCborValue(getStrokeColor()));
        map.insert(QLatin1String("strokeWidth"), QCborValue(getStrokeWidth()));
        return map;
    }
    
    void fromCbor(const QCborValue& cbor) override {
        QCborMap map = cbor.toMap();
        setFillColor(map.value(QLatin1String("fillColor")).toString());
        setStrokeColor(map.value(QLatin1String("strokeColor")).toString());
        setStrokeWidth(static_cast<float>(map.value(QLatin1String("strokeWidth")).toDouble()));
    }
    
    QString name() const override {
        return "Style";
    }
    
    QStringList fields() const override {
        return QStringList{QLatin1String("fillColor"), QLatin1String("strokeColor"), QLatin1String("strokeWidth")};
    }
    
    QString fieldType(const QString& fieldName) const override {
        if (fieldName == QLatin1String("fillColor")) return QLatin1String("string");
        if (fieldName == QLatin1String("strokeColor")) return QLatin1String("string");
        if (fieldName == QLatin1String("strokeWidth")) return QLatin1String("float32");
        return QLatin1String("");
    }
    
    QList<QSharedPointer<IAnnotation>> annotations() const override {
        
        return QList<QSharedPointer<IAnnotation>>();
    }
    
    QList<QSharedPointer<void>> fieldAnnotation(const QString& fieldName) const override {
        if (fieldName == QLatin1String("fillColor")) {
            return QList<QSharedPointer<void>>();
        }
        if (fieldName == QLatin1String("strokeColor")) {
            return QList<QSharedPointer<void>>();
        }
        if (fieldName == QLatin1String("strokeWidth")) {
            return QList<QSharedPointer<void>>();
        }
        return QList<QSharedPointer<void>>();
    }
    
    QString description() const override {
        return "Generated from block Style";
    }
    
    QString fieldDescription(const QString& fieldName) const override {
        
        return QString();
    }
    
    QVariant value(const QString& fieldName) const override {
        if (fieldName == QLatin1String("fillColor")) return QVariant::fromValue(fillColor_);
        if (fieldName == QLatin1String("strokeColor")) return QVariant::fromValue(strokeColor_);
        if (fieldName == QLatin1String("strokeWidth")) return QVariant::fromValue(strokeWidth_);
        return QVariant();
    }
    
    void value(const QString& fieldName, const QVariant& value) override {
        if (fieldName == QLatin1String("fillColor")) {
            fillColor_ = value.value<QString>();
            return;
        }
        if (fieldName == QLatin1String("strokeColor")) {
            strokeColor_ = value.value<QString>();
            return;
        }
        if (fieldName == QLatin1String("strokeWidth")) {
            strokeWidth_ = value.value<float>();
            return;
        }
    }
    
    // 特定于Style的访问器
        // fillColor字段的访问器
    QString getFillColor() const {
        return fillColor_;
    }
    
    void setFillColor(const QString& value) {
        fillColor_ = value;
    } 

        // strokeColor字段的访问器
    QString getStrokeColor() const {
        return strokeColor_;
    }
    
    void setStrokeColor(const QString& value) {
        strokeColor_ = value;
    } 

        // strokeWidth字段的访问器
    float getStrokeWidth() const {
        return strokeWidth_;
    }
    
    void setStrokeWidth(const float& value) {
        strokeWidth_ = value;
    } 
    
private:
    QString fillColor_;
    QString strokeColor_;
    float strokeWidth_;
};


// ShapeConfig结构体

class MODEL_EXPORT ShapeConfigModel : public IModel {
public:
    ShapeConfigModel() = default;
    
    
    // 实现IModel接口
    QCborValue toCbor() const override {
        QCborMap map;
        map.insert(QLatin1String("name"), QCborValue(getName()));
        map.insert(QLatin1String("rectangle"), getRectangle().toCbor());
        map.insert(QLatin1String("style"), getStyle().toCbor());
        return map;
    }
    
    void fromCbor(const QCborValue& cbor) override {
        QCborMap map = cbor.toMap();
        setName(map.value(QLatin1String("name")).toString());
        RectangleBlock rectangle;
        rectangle.fromCbor(map.value(QLatin1String("rectangle")));
        setRectangle(rectangle);
        StyleBlock style;
        style.fromCbor(map.value(QLatin1String("style")));
        setStyle(style);
    }
    
    QStringList fields() const override {
        return QStringList{QLatin1String("name"), QLatin1String("rectangle"), QLatin1String("style")};
    }
    
    QString fieldOriginTypeName(const QString& fieldName) const override {
        if (fieldName == QLatin1String("name")) return QLatin1String("string");
        if (fieldName == QLatin1String("rectangle")) return QLatin1String("Rectangle");
        if (fieldName == QLatin1String("style")) return QLatin1String("Style");
        return QLatin1String("");
    }
    
    QList<QSharedPointer<IAnnotation>> annotations() const override {
        
        return QList<QSharedPointer<IAnnotation>>();
    }
    
    QList<QSharedPointer<void>> fieldAnnotations(const QString& fieldName) const override {
        if (fieldName == QLatin1String("name")) {
            return QList<QSharedPointer<void>>();
        }
        if (fieldName == QLatin1String("rectangle")) {
            return QList<QSharedPointer<void>>();
        }
        if (fieldName == QLatin1String("style")) {
            return QList<QSharedPointer<void>>();
        }
        return QList<QSharedPointer<void>>();
    }
    
    QString description() const override {
        return "Generated from struct ShapeConfig";
    }
    
    QString fieldDescription(const QString& fieldName) const override {
        
        return QString();
    }
    
    QVariant value(const QString& fieldName) const override {
        if (fieldName == QLatin1String("name")) return QVariant::fromValue(name_);
        if (fieldName == QLatin1String("rectangle")) return QVariant::fromValue(rectangle_);
        if (fieldName == QLatin1String("style")) return QVariant::fromValue(style_);
        return QVariant();
    }
    
    void value(const QString& fieldName, const QVariant& value) override {
        if (fieldName == QLatin1String("name")) {
            name_ = value.value<QString>();
            return;
        }
        if (fieldName == QLatin1String("rectangle")) {
            rectangle_ = value.value<RectangleBlock>();
            return;
        }
        if (fieldName == QLatin1String("style")) {
            style_ = value.value<StyleBlock>();
            return;
        }
    }
    
    // 特定于ShapeConfig的访问器
        // name字段的访问器
    QString getName() const {
        return name_;
    }
    
    void setName(const QString& value) {
        name_ = value;
    } 

        // rectangle字段的访问器
    RectangleBlock getRectangle() const {
        return rectangle_;
    }
    
    void setRectangle(const RectangleBlock& value) {
        rectangle_ = value;
    } 

        // style字段的访问器
    StyleBlock getStyle() const {
        return style_;
    }
    
    void setStyle(const StyleBlock& value) {
        style_ = value;
    } 
    
protected:
    QString modelName() const override {
        return "ShapeConfig";
    }
    
private:
    QString name_;
    RectangleBlock rectangle_;
    StyleBlock style_;
    
    // 变更通知
    void notifyChange();
};


// PolygonConfig结构体

class MODEL_EXPORT PolygonConfigModel : public IModel {
public:
    PolygonConfigModel() = default;
    
    
    // 实现IModel接口
    QCborValue toCbor() const override {
        QCborMap map;
        map.insert(QLatin1String("name"), QCborValue(getName()));
        map.insert(QLatin1String("verticesJson"), QCborValue(getVerticesJson()));
        map.insert(QLatin1String("style"), getStyle().toCbor());
        return map;
    }
    
    void fromCbor(const QCborValue& cbor) override {
        QCborMap map = cbor.toMap();
        setName(map.value(QLatin1String("name")).toString());
        setVerticesJson(map.value(QLatin1String("verticesJson")).toString());
        StyleBlock style;
        style.fromCbor(map.value(QLatin1String("style")));
        setStyle(style);
    }
    
    QStringList fields() const override {
        return QStringList{QLatin1String("name"), QLatin1String("verticesJson"), QLatin1String("style")};
    }
    
    QString fieldOriginTypeName(const QString& fieldName) const override {
        if (fieldName == QLatin1String("name")) return QLatin1String("string");
        if (fieldName == QLatin1String("verticesJson")) return QLatin1String("string");
        if (fieldName == QLatin1String("style")) return QLatin1String("Style");
        return QLatin1String("");
    }
    
    QList<QSharedPointer<IAnnotation>> annotations() const override {
        
        return QList<QSharedPointer<IAnnotation>>();
    }
    
    QList<QSharedPointer<void>> fieldAnnotations(const QString& fieldName) const override {
        if (fieldName == QLatin1String("name")) {
            return QList<QSharedPointer<void>>();
        }
        if (fieldName == QLatin1String("verticesJson")) {
            return QList<QSharedPointer<void>>();
        }
        if (fieldName == QLatin1String("style")) {
            return QList<QSharedPointer<void>>();
        }
        return QList<QSharedPointer<void>>();
    }
    
    QString description() const override {
        return "Generated from struct PolygonConfig";
    }
    
    QString fieldDescription(const QString& fieldName) const override {
        
        return QString();
    }
    
    QVariant value(const QString& fieldName) const override {
        if (fieldName == QLatin1String("name")) return QVariant::fromValue(name_);
        if (fieldName == QLatin1String("verticesJson")) return QVariant::fromValue(verticesJson_);
        if (fieldName == QLatin1String("style")) return QVariant::fromValue(style_);
        return QVariant();
    }
    
    void value(const QString& fieldName, const QVariant& value) override {
        if (fieldName == QLatin1String("name")) {
            name_ = value.value<QString>();
            return;
        }
        if (fieldName == QLatin1String("verticesJson")) {
            verticesJson_ = value.value<QString>();
            return;
        }
        if (fieldName == QLatin1String("style")) {
            style_ = value.value<StyleBlock>();
            return;
        }
    }
    
    // 特定于PolygonConfig的访问器
        // name字段的访问器
    QString getName() const {
        return name_;
    }
    
    void setName(const QString& value) {
        name_ = value;
    } 

        // verticesJson字段的访问器
    QString getVerticesJson() const {
        return verticesJson_;
    }
    
    void setVerticesJson(const QString& value) {
        verticesJson_ = value;
    } 

        // style字段的访问器
    StyleBlock getStyle() const {
        return style_;
    }
    
    void setStyle(const StyleBlock& value) {
        style_ = value;
    } 
    
protected:
    QString modelName() const override {
        return "PolygonConfig";
    }
    
private:
    QString name_;
    QString verticesJson_;
    StyleBlock style_;
    
    // 变更通知
    void notifyChange();
};



} // namespace examples::structs

