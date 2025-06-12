#pragma once

// 此文件由 Mota 代码生成器自动生成
// 生成时间: 2025-06-11 23:24:40// 源文件: .\mota-include\yima-blocks.mota
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

using namespace ymf;

namespace yima {
// Point块定义
class MODEL_EXPORT PointBlock : public IBlock {
public:
    PointBlock() = default;
    
    // 实现 IBlock 接口
    virtual QCborMap toCbor() const override {
        QCborMap map;
        map.insert(QLatin1String("x"), QCborValue(getX()));
        map.insert(QLatin1String("y"), QCborValue(getY()));
        return map;
    }
    
    virtual void fromCbor(const QCborMap& map) override {        QCborValue tmp;
        tmp = map.value(QLatin1String("x"));
        if (!tmp.isNull() && !tmp.isUndefined() || !tmp.isInvalid()) {            setX(tmp.toInteger());        }
        tmp = map.value(QLatin1String("y"));
        if (!tmp.isNull() && !tmp.isUndefined() || !tmp.isInvalid()) {            setY(tmp.toInteger());        }
    }
    
    virtual QString name() const override {
        return "Point";
    }
    
    virtual QStringList fields() const override {
        return QStringList{QLatin1String("x"), QLatin1String("y")};
    }
    
    virtual QString fieldType(const QString& fieldName) const override {
        if (fieldName == QLatin1String("x")) return QLatin1String("int16");
        if (fieldName == QLatin1String("y")) return QLatin1String("int16");
        return QLatin1String("");
    }
    
    virtual QList<QSharedPointer<IAnnotation>> annotations() const override {
        QList<QSharedPointer<IAnnotation>> result;
        return result;
    }
    
    virtual QList<QSharedPointer<IAnnotation>> fieldAnnotation(const QString& fieldName) const override {
        if (fieldName == QLatin1String("x")) {
            QList<QSharedPointer<IAnnotation>> result;
            return result;
        }
        if (fieldName == QLatin1String("y")) {
            QList<QSharedPointer<IAnnotation>> result;
            return result;
        }
        return QList<QSharedPointer<IAnnotation>>();
    }
    
    virtual QString description() const override {
        return "Point";
    }
    
    virtual QString fieldDescription(const QString& fieldName) const override {
        if (fieldName == QLatin1String("x")) {
            return "x";
        }
        if (fieldName == QLatin1String("y")) {
            return "y";
        }
        return QString();
    }
    
    virtual QVariant value(const QString& fieldName) const override {
        if (fieldName == QLatin1String("x")) return QVariant::fromValue(x_);
        if (fieldName == QLatin1String("y")) return QVariant::fromValue(y_);
        return QVariant();
    }
    
    virtual void value(const QString& fieldName, const QVariant& value) override {
        if (fieldName == QLatin1String("x")) {
            x_ = value.value<int16_t>();
            return;
        }
        if (fieldName == QLatin1String("y")) {
            y_ = value.value<int16_t>();
            return;
        }
    }
    
    // 特定于Point的访问器
    int16_t getX() const {
        return x_;
    }

    void setX(const int16_t& value) {
        x_ = value;
    }
    int16_t getY() const {
        return y_;
    }

    void setY(const int16_t& value) {
        y_ = value;
    }
    
private:
    int16_t x_;
    int16_t y_;
};
Q_DECLARE_METATYPE(PointBlock)
// Rectangle块定义
class MODEL_EXPORT RectangleBlock : public IBlock {
public:
    RectangleBlock() = default;
    
    // 实现 IBlock 接口
    virtual QCborMap toCbor() const override {
        QCborMap map;
        map.insert(QLatin1String("width"), QCborValue(getWidth()));
        map.insert(QLatin1String("height"), QCborValue(getHeight()));
        map.insert(QLatin1String("x"), QCborValue(getX()));
        map.insert(QLatin1String("y"), QCborValue(getY()));
        return map;
    }
    
    virtual void fromCbor(const QCborMap& map) override {        QCborValue tmp;
        tmp = map.value(QLatin1String("width"));
        if (!tmp.isNull() && !tmp.isUndefined() || !tmp.isInvalid()) {            setWidth(tmp.toInteger());        }
        tmp = map.value(QLatin1String("height"));
        if (!tmp.isNull() && !tmp.isUndefined() || !tmp.isInvalid()) {            setHeight(tmp.toInteger());        }
        tmp = map.value(QLatin1String("x"));
        if (!tmp.isNull() && !tmp.isUndefined() || !tmp.isInvalid()) {            setX(tmp.toInteger());        }
        tmp = map.value(QLatin1String("y"));
        if (!tmp.isNull() && !tmp.isUndefined() || !tmp.isInvalid()) {            setY(tmp.toInteger());        }
    }
    
    virtual QString name() const override {
        return "Rectangle";
    }
    
    virtual QStringList fields() const override {
        return QStringList{QLatin1String("width"), QLatin1String("height"), QLatin1String("x"), QLatin1String("y")};
    }
    
    virtual QString fieldType(const QString& fieldName) const override {
        if (fieldName == QLatin1String("width")) return QLatin1String("int16");
        if (fieldName == QLatin1String("height")) return QLatin1String("int16");
        if (fieldName == QLatin1String("x")) return QLatin1String("int16");
        if (fieldName == QLatin1String("y")) return QLatin1String("int16");
        return QLatin1String("");
    }
    
    virtual QList<QSharedPointer<IAnnotation>> annotations() const override {
        QList<QSharedPointer<IAnnotation>> result;
        return result;
    }
    
    virtual QList<QSharedPointer<IAnnotation>> fieldAnnotation(const QString& fieldName) const override {
        if (fieldName == QLatin1String("width")) {
            QList<QSharedPointer<IAnnotation>> result;
            return result;
        }
        if (fieldName == QLatin1String("height")) {
            QList<QSharedPointer<IAnnotation>> result;
            return result;
        }
        if (fieldName == QLatin1String("x")) {
            QList<QSharedPointer<IAnnotation>> result;
            return result;
        }
        if (fieldName == QLatin1String("y")) {
            QList<QSharedPointer<IAnnotation>> result;
            return result;
        }
        return QList<QSharedPointer<IAnnotation>>();
    }
    
    virtual QString description() const override {
        return "Rectangle";
    }
    
    virtual QString fieldDescription(const QString& fieldName) const override {
        if (fieldName == QLatin1String("width")) {
            return "width";
        }
        if (fieldName == QLatin1String("height")) {
            return "height";
        }
        if (fieldName == QLatin1String("x")) {
            return "x";
        }
        if (fieldName == QLatin1String("y")) {
            return "y";
        }
        return QString();
    }
    
    virtual QVariant value(const QString& fieldName) const override {
        if (fieldName == QLatin1String("width")) return QVariant::fromValue(width_);
        if (fieldName == QLatin1String("height")) return QVariant::fromValue(height_);
        if (fieldName == QLatin1String("x")) return QVariant::fromValue(x_);
        if (fieldName == QLatin1String("y")) return QVariant::fromValue(y_);
        return QVariant();
    }
    
    virtual void value(const QString& fieldName, const QVariant& value) override {
        if (fieldName == QLatin1String("width")) {
            width_ = value.value<int16_t>();
            return;
        }
        if (fieldName == QLatin1String("height")) {
            height_ = value.value<int16_t>();
            return;
        }
        if (fieldName == QLatin1String("x")) {
            x_ = value.value<int16_t>();
            return;
        }
        if (fieldName == QLatin1String("y")) {
            y_ = value.value<int16_t>();
            return;
        }
    }
    
    // 特定于Rectangle的访问器
    int16_t getWidth() const {
        return width_;
    }

    void setWidth(const int16_t& value) {
        width_ = value;
    }
    int16_t getHeight() const {
        return height_;
    }

    void setHeight(const int16_t& value) {
        height_ = value;
    }
    int16_t getX() const {
        return x_;
    }

    void setX(const int16_t& value) {
        x_ = value;
    }
    int16_t getY() const {
        return y_;
    }

    void setY(const int16_t& value) {
        y_ = value;
    }
    
private:
    int16_t width_;
    int16_t height_;
    int16_t x_;
    int16_t y_;
};
Q_DECLARE_METATYPE(RectangleBlock)
// Circle块定义
class MODEL_EXPORT CircleBlock : public IBlock {
public:
    CircleBlock() = default;
    
    // 实现 IBlock 接口
    virtual QCborMap toCbor() const override {
        QCborMap map;
        map.insert(QLatin1String("radius"), QCborValue(getRadius()));
        map.insert(QLatin1String("x"), QCborValue(getX()));
        map.insert(QLatin1String("y"), QCborValue(getY()));
        return map;
    }
    
    virtual void fromCbor(const QCborMap& map) override {        QCborValue tmp;
        tmp = map.value(QLatin1String("radius"));
        if (!tmp.isNull() && !tmp.isUndefined() || !tmp.isInvalid()) {            setRadius(tmp.toInteger());        }
        tmp = map.value(QLatin1String("x"));
        if (!tmp.isNull() && !tmp.isUndefined() || !tmp.isInvalid()) {            setX(tmp.toInteger());        }
        tmp = map.value(QLatin1String("y"));
        if (!tmp.isNull() && !tmp.isUndefined() || !tmp.isInvalid()) {            setY(tmp.toInteger());        }
    }
    
    virtual QString name() const override {
        return "Circle";
    }
    
    virtual QStringList fields() const override {
        return QStringList{QLatin1String("radius"), QLatin1String("x"), QLatin1String("y")};
    }
    
    virtual QString fieldType(const QString& fieldName) const override {
        if (fieldName == QLatin1String("radius")) return QLatin1String("int16");
        if (fieldName == QLatin1String("x")) return QLatin1String("int16");
        if (fieldName == QLatin1String("y")) return QLatin1String("int16");
        return QLatin1String("");
    }
    
    virtual QList<QSharedPointer<IAnnotation>> annotations() const override {
        QList<QSharedPointer<IAnnotation>> result;
        return result;
    }
    
    virtual QList<QSharedPointer<IAnnotation>> fieldAnnotation(const QString& fieldName) const override {
        if (fieldName == QLatin1String("radius")) {
            QList<QSharedPointer<IAnnotation>> result;
            return result;
        }
        if (fieldName == QLatin1String("x")) {
            QList<QSharedPointer<IAnnotation>> result;
            return result;
        }
        if (fieldName == QLatin1String("y")) {
            QList<QSharedPointer<IAnnotation>> result;
            return result;
        }
        return QList<QSharedPointer<IAnnotation>>();
    }
    
    virtual QString description() const override {
        return "Circle";
    }
    
    virtual QString fieldDescription(const QString& fieldName) const override {
        if (fieldName == QLatin1String("radius")) {
            return "radius";
        }
        if (fieldName == QLatin1String("x")) {
            return "x";
        }
        if (fieldName == QLatin1String("y")) {
            return "y";
        }
        return QString();
    }
    
    virtual QVariant value(const QString& fieldName) const override {
        if (fieldName == QLatin1String("radius")) return QVariant::fromValue(radius_);
        if (fieldName == QLatin1String("x")) return QVariant::fromValue(x_);
        if (fieldName == QLatin1String("y")) return QVariant::fromValue(y_);
        return QVariant();
    }
    
    virtual void value(const QString& fieldName, const QVariant& value) override {
        if (fieldName == QLatin1String("radius")) {
            radius_ = value.value<int16_t>();
            return;
        }
        if (fieldName == QLatin1String("x")) {
            x_ = value.value<int16_t>();
            return;
        }
        if (fieldName == QLatin1String("y")) {
            y_ = value.value<int16_t>();
            return;
        }
    }
    
    // 特定于Circle的访问器
    int16_t getRadius() const {
        return radius_;
    }

    void setRadius(const int16_t& value) {
        radius_ = value;
    }
    int16_t getX() const {
        return x_;
    }

    void setX(const int16_t& value) {
        x_ = value;
    }
    int16_t getY() const {
        return y_;
    }

    void setY(const int16_t& value) {
        y_ = value;
    }
    
private:
    int16_t radius_;
    int16_t x_;
    int16_t y_;
};
Q_DECLARE_METATYPE(CircleBlock)
// Ellipse块定义
class MODEL_EXPORT EllipseBlock : public IBlock {
public:
    EllipseBlock() = default;
    
    // 实现 IBlock 接口
    virtual QCborMap toCbor() const override {
        QCborMap map;
            map.insert(QLatin1String("center"), getCenter().toCbor());
        map.insert(QLatin1String("width"), QCborValue(getWidth()));
        map.insert(QLatin1String("height"), QCborValue(getHeight()));
        map.insert(QLatin1String("rotation"), QCborValue(getRotation()));
        return map;
    }
    
    virtual void fromCbor(const QCborMap& map) override {        QCborValue tmp;
        tmp = map.value(QLatin1String("center"));
        if (!tmp.isNull() && !tmp.isUndefined() || !tmp.isInvalid()) {        setCenter(tmp.toMap());        }
        tmp = map.value(QLatin1String("width"));
        if (!tmp.isNull() && !tmp.isUndefined() || !tmp.isInvalid()) {            setWidth(tmp.toInteger());        }
        tmp = map.value(QLatin1String("height"));
        if (!tmp.isNull() && !tmp.isUndefined() || !tmp.isInvalid()) {            setHeight(tmp.toInteger());        }
        tmp = map.value(QLatin1String("rotation"));
        if (!tmp.isNull() && !tmp.isUndefined() || !tmp.isInvalid()) {            setRotation(tmp.toDouble());        }
    }
    
    virtual QString name() const override {
        return "Ellipse";
    }
    
    virtual QStringList fields() const override {
        return QStringList{QLatin1String("center"), QLatin1String("width"), QLatin1String("height"), QLatin1String("rotation")};
    }
    
    virtual QString fieldType(const QString& fieldName) const override {
        if (fieldName == QLatin1String("center")) return QLatin1String("Point");
        if (fieldName == QLatin1String("width")) return QLatin1String("int16");
        if (fieldName == QLatin1String("height")) return QLatin1String("int16");
        if (fieldName == QLatin1String("rotation")) return QLatin1String("float32");
        return QLatin1String("");
    }
    
    virtual QList<QSharedPointer<IAnnotation>> annotations() const override {
        QList<QSharedPointer<IAnnotation>> result;
        return result;
    }
    
    virtual QList<QSharedPointer<IAnnotation>> fieldAnnotation(const QString& fieldName) const override {
        if (fieldName == QLatin1String("center")) {
            QList<QSharedPointer<IAnnotation>> result;
            return result;
        }
        if (fieldName == QLatin1String("width")) {
            QList<QSharedPointer<IAnnotation>> result;
            return result;
        }
        if (fieldName == QLatin1String("height")) {
            QList<QSharedPointer<IAnnotation>> result;
            return result;
        }
        if (fieldName == QLatin1String("rotation")) {
            QList<QSharedPointer<IAnnotation>> result;
            return result;
        }
        return QList<QSharedPointer<IAnnotation>>();
    }
    
    virtual QString description() const override {
        return "Ellipse";
    }
    
    virtual QString fieldDescription(const QString& fieldName) const override {
        if (fieldName == QLatin1String("center")) {
            return "center";
        }
        if (fieldName == QLatin1String("width")) {
            return "width";
        }
        if (fieldName == QLatin1String("height")) {
            return "height";
        }
        if (fieldName == QLatin1String("rotation")) {
            return "rotation";
        }
        return QString();
    }
    
    virtual QVariant value(const QString& fieldName) const override {
        if (fieldName == QLatin1String("center")) return QVariant::fromValue(center_);
        if (fieldName == QLatin1String("width")) return QVariant::fromValue(width_);
        if (fieldName == QLatin1String("height")) return QVariant::fromValue(height_);
        if (fieldName == QLatin1String("rotation")) return QVariant::fromValue(rotation_);
        return QVariant();
    }
    
    virtual void value(const QString& fieldName, const QVariant& value) override {
        if (fieldName == QLatin1String("center")) {
            center_ = value.value<PointBlock>();
            return;
        }
        if (fieldName == QLatin1String("width")) {
            width_ = value.value<int16_t>();
            return;
        }
        if (fieldName == QLatin1String("height")) {
            height_ = value.value<int16_t>();
            return;
        }
        if (fieldName == QLatin1String("rotation")) {
            rotation_ = value.value<float>();
            return;
        }
    }
    
    // 特定于Ellipse的访问器
    PointBlock getCenter() const {
        return center_;
    }

    void setCenter(const PointBlock& value) {
        center_ = value;
    }
    int16_t getWidth() const {
        return width_;
    }

    void setWidth(const int16_t& value) {
        width_ = value;
    }
    int16_t getHeight() const {
        return height_;
    }

    void setHeight(const int16_t& value) {
        height_ = value;
    }
    float getRotation() const {
        return rotation_;
    }

    void setRotation(const float& value) {
        rotation_ = value;
    }
    
private:
    PointBlock center_;
    int16_t width_;
    int16_t height_;
    float rotation_;
};
Q_DECLARE_METATYPE(EllipseBlock)
// Arc块定义
class MODEL_EXPORT ArcBlock : public IBlock {
public:
    ArcBlock() = default;
    
    // 实现 IBlock 接口
    virtual QCborMap toCbor() const override {
        QCborMap map;
            map.insert(QLatin1String("center"), getCenter().toCbor());
        map.insert(QLatin1String("radius"), QCborValue(getRadius()));
        map.insert(QLatin1String("startAngle"), QCborValue(getStartangle()));
        map.insert(QLatin1String("endAngle"), QCborValue(getEndangle()));
        map.insert(QLatin1String("rotation"), QCborValue(getRotation()));
        return map;
    }
    
    virtual void fromCbor(const QCborMap& map) override {        QCborValue tmp;
        tmp = map.value(QLatin1String("center"));
        if (!tmp.isNull() && !tmp.isUndefined() || !tmp.isInvalid()) {        setCenter(tmp.toMap());        }
        tmp = map.value(QLatin1String("radius"));
        if (!tmp.isNull() && !tmp.isUndefined() || !tmp.isInvalid()) {            setRadius(tmp.toInteger());        }
        tmp = map.value(QLatin1String("startAngle"));
        if (!tmp.isNull() && !tmp.isUndefined() || !tmp.isInvalid()) {            setStartangle(tmp.toDouble());        }
        tmp = map.value(QLatin1String("endAngle"));
        if (!tmp.isNull() && !tmp.isUndefined() || !tmp.isInvalid()) {            setEndangle(tmp.toDouble());        }
        tmp = map.value(QLatin1String("rotation"));
        if (!tmp.isNull() && !tmp.isUndefined() || !tmp.isInvalid()) {            setRotation(tmp.toDouble());        }
    }
    
    virtual QString name() const override {
        return "Arc";
    }
    
    virtual QStringList fields() const override {
        return QStringList{QLatin1String("center"), QLatin1String("radius"), QLatin1String("startAngle"), QLatin1String("endAngle"), QLatin1String("rotation")};
    }
    
    virtual QString fieldType(const QString& fieldName) const override {
        if (fieldName == QLatin1String("center")) return QLatin1String("Point");
        if (fieldName == QLatin1String("radius")) return QLatin1String("int16");
        if (fieldName == QLatin1String("startAngle")) return QLatin1String("float32");
        if (fieldName == QLatin1String("endAngle")) return QLatin1String("float32");
        if (fieldName == QLatin1String("rotation")) return QLatin1String("float32");
        return QLatin1String("");
    }
    
    virtual QList<QSharedPointer<IAnnotation>> annotations() const override {
        QList<QSharedPointer<IAnnotation>> result;
        return result;
    }
    
    virtual QList<QSharedPointer<IAnnotation>> fieldAnnotation(const QString& fieldName) const override {
        if (fieldName == QLatin1String("center")) {
            QList<QSharedPointer<IAnnotation>> result;
            return result;
        }
        if (fieldName == QLatin1String("radius")) {
            QList<QSharedPointer<IAnnotation>> result;
            return result;
        }
        if (fieldName == QLatin1String("startAngle")) {
            QList<QSharedPointer<IAnnotation>> result;
            return result;
        }
        if (fieldName == QLatin1String("endAngle")) {
            QList<QSharedPointer<IAnnotation>> result;
            return result;
        }
        if (fieldName == QLatin1String("rotation")) {
            QList<QSharedPointer<IAnnotation>> result;
            return result;
        }
        return QList<QSharedPointer<IAnnotation>>();
    }
    
    virtual QString description() const override {
        return "Arc";
    }
    
    virtual QString fieldDescription(const QString& fieldName) const override {
        if (fieldName == QLatin1String("center")) {
            return "center";
        }
        if (fieldName == QLatin1String("radius")) {
            return "radius";
        }
        if (fieldName == QLatin1String("startAngle")) {
            return "startAngle";
        }
        if (fieldName == QLatin1String("endAngle")) {
            return "endAngle";
        }
        if (fieldName == QLatin1String("rotation")) {
            return "rotation";
        }
        return QString();
    }
    
    virtual QVariant value(const QString& fieldName) const override {
        if (fieldName == QLatin1String("center")) return QVariant::fromValue(center_);
        if (fieldName == QLatin1String("radius")) return QVariant::fromValue(radius_);
        if (fieldName == QLatin1String("startAngle")) return QVariant::fromValue(startAngle_);
        if (fieldName == QLatin1String("endAngle")) return QVariant::fromValue(endAngle_);
        if (fieldName == QLatin1String("rotation")) return QVariant::fromValue(rotation_);
        return QVariant();
    }
    
    virtual void value(const QString& fieldName, const QVariant& value) override {
        if (fieldName == QLatin1String("center")) {
            center_ = value.value<PointBlock>();
            return;
        }
        if (fieldName == QLatin1String("radius")) {
            radius_ = value.value<int16_t>();
            return;
        }
        if (fieldName == QLatin1String("startAngle")) {
            startAngle_ = value.value<float>();
            return;
        }
        if (fieldName == QLatin1String("endAngle")) {
            endAngle_ = value.value<float>();
            return;
        }
        if (fieldName == QLatin1String("rotation")) {
            rotation_ = value.value<float>();
            return;
        }
    }
    
    // 特定于Arc的访问器
    PointBlock getCenter() const {
        return center_;
    }

    void setCenter(const PointBlock& value) {
        center_ = value;
    }
    int16_t getRadius() const {
        return radius_;
    }

    void setRadius(const int16_t& value) {
        radius_ = value;
    }
    float getStartangle() const {
        return startAngle_;
    }

    void setStartangle(const float& value) {
        startAngle_ = value;
    }
    float getEndangle() const {
        return endAngle_;
    }

    void setEndangle(const float& value) {
        endAngle_ = value;
    }
    float getRotation() const {
        return rotation_;
    }

    void setRotation(const float& value) {
        rotation_ = value;
    }
    
private:
    PointBlock center_;
    int16_t radius_;
    float startAngle_;
    float endAngle_;
    float rotation_;
};
Q_DECLARE_METATYPE(ArcBlock)
// Polygon块定义
class MODEL_EXPORT PolygonBlock : public IBlock {
public:
    PolygonBlock() = default;
    
    // 实现 IBlock 接口
    virtual QCborMap toCbor() const override {
        QCborMap map;
        QCborArray __pointsArray;
        for (const auto& item : getPoints()) {
            __pointsArray.append(item.toCbor());
        }
        map.insert(QLatin1String("points"), __pointsArray);
        return map;
    }
    
    virtual void fromCbor(const QCborMap& map) override {        QCborValue tmp;
        QCborArray __pointsArray = map.value(QLatin1String("points")).toArray();
        QVector<PointBlock> points;
        for (const auto& itemValue : __pointsArray) {
            PointBlock item;
            item.fromCbor(itemValue.toMap());
            points.append(item);
        }
        setPoints(points);
    }
    
    virtual QString name() const override {
        return "Polygon";
    }
    
    virtual QStringList fields() const override {
        return QStringList{QLatin1String("points")};
    }
    
    virtual QString fieldType(const QString& fieldName) const override {
        if (fieldName == QLatin1String("points")) return QLatin1String("Point");
        return QLatin1String("");
    }
    
    virtual QList<QSharedPointer<IAnnotation>> annotations() const override {
        QList<QSharedPointer<IAnnotation>> result;
        return result;
    }
    
    virtual QList<QSharedPointer<IAnnotation>> fieldAnnotation(const QString& fieldName) const override {
        if (fieldName == QLatin1String("points")) {
            QList<QSharedPointer<IAnnotation>> result;
            return result;
        }
        return QList<QSharedPointer<IAnnotation>>();
    }
    
    virtual QString description() const override {
        return "Polygon";
    }
    
    virtual QString fieldDescription(const QString& fieldName) const override {
        if (fieldName == QLatin1String("points")) {
            return "points";
        }
        return QString();
    }
    
    virtual QVariant value(const QString& fieldName) const override {
        if (fieldName == QLatin1String("points")) return QVariant::fromValue(points_);
        return QVariant();
    }
    
    virtual void value(const QString& fieldName, const QVariant& value) override {
        if (fieldName == QLatin1String("points")) {
            points_ = value.value<QVector<PointBlock>>();
            return;
        }
    }
    
    // 特定于Polygon的访问器
    QVector<PointBlock> getPoints() const {
        return points_;
    }

    void setPoints(const QVector<PointBlock>& value) {
        points_ = value;
    }
    
private:
    QVector<PointBlock> points_;
};
Q_DECLARE_METATYPE(PolygonBlock)
// Line块定义
class MODEL_EXPORT LineBlock : public IBlock {
public:
    LineBlock() = default;
    
    // 实现 IBlock 接口
    virtual QCborMap toCbor() const override {
        QCborMap map;
            map.insert(QLatin1String("start"), getStart().toCbor());
            map.insert(QLatin1String("end"), getEnd().toCbor());
        return map;
    }
    
    virtual void fromCbor(const QCborMap& map) override {        QCborValue tmp;
        tmp = map.value(QLatin1String("start"));
        if (!tmp.isNull() && !tmp.isUndefined() || !tmp.isInvalid()) {        setStart(tmp.toMap());        }
        tmp = map.value(QLatin1String("end"));
        if (!tmp.isNull() && !tmp.isUndefined() || !tmp.isInvalid()) {        setEnd(tmp.toMap());        }
    }
    
    virtual QString name() const override {
        return "Line";
    }
    
    virtual QStringList fields() const override {
        return QStringList{QLatin1String("start"), QLatin1String("end")};
    }
    
    virtual QString fieldType(const QString& fieldName) const override {
        if (fieldName == QLatin1String("start")) return QLatin1String("Point");
        if (fieldName == QLatin1String("end")) return QLatin1String("Point");
        return QLatin1String("");
    }
    
    virtual QList<QSharedPointer<IAnnotation>> annotations() const override {
        QList<QSharedPointer<IAnnotation>> result;
        return result;
    }
    
    virtual QList<QSharedPointer<IAnnotation>> fieldAnnotation(const QString& fieldName) const override {
        if (fieldName == QLatin1String("start")) {
            QList<QSharedPointer<IAnnotation>> result;
            return result;
        }
        if (fieldName == QLatin1String("end")) {
            QList<QSharedPointer<IAnnotation>> result;
            return result;
        }
        return QList<QSharedPointer<IAnnotation>>();
    }
    
    virtual QString description() const override {
        return "Line";
    }
    
    virtual QString fieldDescription(const QString& fieldName) const override {
        if (fieldName == QLatin1String("start")) {
            return "start";
        }
        if (fieldName == QLatin1String("end")) {
            return "end";
        }
        return QString();
    }
    
    virtual QVariant value(const QString& fieldName) const override {
        if (fieldName == QLatin1String("start")) return QVariant::fromValue(start_);
        if (fieldName == QLatin1String("end")) return QVariant::fromValue(end_);
        return QVariant();
    }
    
    virtual void value(const QString& fieldName, const QVariant& value) override {
        if (fieldName == QLatin1String("start")) {
            start_ = value.value<PointBlock>();
            return;
        }
        if (fieldName == QLatin1String("end")) {
            end_ = value.value<PointBlock>();
            return;
        }
    }
    
    // 特定于Line的访问器
    PointBlock getStart() const {
        return start_;
    }

    void setStart(const PointBlock& value) {
        start_ = value;
    }
    PointBlock getEnd() const {
        return end_;
    }

    void setEnd(const PointBlock& value) {
        end_ = value;
    }
    
private:
    PointBlock start_;
    PointBlock end_;
};
Q_DECLARE_METATYPE(LineBlock)
}
 
