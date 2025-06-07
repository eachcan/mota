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

// 此文件由 Mota 代码生成器自动生成
// 生成时间: 2025-06-07 21:58:59
// 源文件: unknown.mota

using namespace ymf;


namespace yima {


// Point块
class MODEL_EXPORT PointBlock : public IBlock {
public:
    PointBlock() = default;
    
    
    // 实现IBlock接口
    QCborValue toCbor() const override {
        QCborMap map;
        map.insert(QLatin1String("x"), QCborValue(getX()));
        map.insert(QLatin1String("y"), QCborValue(getY()));
        return map;
    }
    
    void fromCbor(const QCborValue& cbor) override {
        QCborMap map = cbor.toMap();
        setX(static_cast<int16_t>(map.value(QLatin1String("x")).toInteger()));
        setY(static_cast<int16_t>(map.value(QLatin1String("y")).toInteger()));
    }
    
    QString name() const override {
        return "Point";
    }
    
    QStringList fields() const override {
        return QStringList{QLatin1String("x"), QLatin1String("y")};
    }
    
    QString fieldType(const QString& fieldName) const override {
        if (fieldName == QLatin1String("x")) return QLatin1String("int16");
        if (fieldName == QLatin1String("y")) return QLatin1String("int16");
        return QLatin1String("");
    }
    
    QList<QSharedPointer<void>> fieldAnnotation(const QString& fieldName) const override {
        
        return QList<QSharedPointer<void>>();
    }
    
    QString description() const override {
        return "Generated from block Point";
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
            x_ = value.value<int16_t>();
            return;
        }
        if (fieldName == QLatin1String("y")) {
            y_ = value.value<int16_t>();
            return;
        }
    }
    
    // 特定于Point的访问器
        // x字段的访问器
    int16_t getX() const {
        return x_;
    }
    
    void setX(const int16_t& value) {
        x_ = value;
    } 

        // y字段的访问器
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


// Rectangle块
class MODEL_EXPORT RectangleBlock : public IBlock {
public:
    RectangleBlock() = default;
    
    
    // 实现IBlock接口
    QCborValue toCbor() const override {
        QCborMap map;
        map.insert(QLatin1String("width"), QCborValue(getWidth()));
        map.insert(QLatin1String("height"), QCborValue(getHeight()));
        map.insert(QLatin1String("x"), QCborValue(getX()));
        map.insert(QLatin1String("y"), QCborValue(getY()));
        return map;
    }
    
    void fromCbor(const QCborValue& cbor) override {
        QCborMap map = cbor.toMap();
        setWidth(static_cast<int16_t>(map.value(QLatin1String("width")).toInteger()));
        setHeight(static_cast<int16_t>(map.value(QLatin1String("height")).toInteger()));
        setX(static_cast<int16_t>(map.value(QLatin1String("x")).toInteger()));
        setY(static_cast<int16_t>(map.value(QLatin1String("y")).toInteger()));
    }
    
    QString name() const override {
        return "Rectangle";
    }
    
    QStringList fields() const override {
        return QStringList{QLatin1String("width"), QLatin1String("height"), QLatin1String("x"), QLatin1String("y")};
    }
    
    QString fieldType(const QString& fieldName) const override {
        if (fieldName == QLatin1String("width")) return QLatin1String("int16");
        if (fieldName == QLatin1String("height")) return QLatin1String("int16");
        if (fieldName == QLatin1String("x")) return QLatin1String("int16");
        if (fieldName == QLatin1String("y")) return QLatin1String("int16");
        return QLatin1String("");
    }
    
    QList<QSharedPointer<void>> fieldAnnotation(const QString& fieldName) const override {
        
        return QList<QSharedPointer<void>>();
    }
    
    QString description() const override {
        return "Generated from block Rectangle";
    }
    
    QString fieldDescription(const QString& fieldName) const override {
        
        return QString();
    }
    
    QVariant value(const QString& fieldName) const override {
        if (fieldName == QLatin1String("width")) return QVariant::fromValue(width_);
        if (fieldName == QLatin1String("height")) return QVariant::fromValue(height_);
        if (fieldName == QLatin1String("x")) return QVariant::fromValue(x_);
        if (fieldName == QLatin1String("y")) return QVariant::fromValue(y_);
        return QVariant();
    }
    
    void value(const QString& fieldName, const QVariant& value) override {
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
        // width字段的访问器
    int16_t getWidth() const {
        return width_;
    }
    
    void setWidth(const int16_t& value) {
        width_ = value;
    } 

        // height字段的访问器
    int16_t getHeight() const {
        return height_;
    }
    
    void setHeight(const int16_t& value) {
        height_ = value;
    } 

        // x字段的访问器
    int16_t getX() const {
        return x_;
    }
    
    void setX(const int16_t& value) {
        x_ = value;
    } 

        // y字段的访问器
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


// Circle块
class MODEL_EXPORT CircleBlock : public IBlock {
public:
    CircleBlock() = default;
    
    
    // 实现IBlock接口
    QCborValue toCbor() const override {
        QCborMap map;
        map.insert(QLatin1String("radius"), QCborValue(getRadius()));
        map.insert(QLatin1String("x"), QCborValue(getX()));
        map.insert(QLatin1String("y"), QCborValue(getY()));
        return map;
    }
    
    void fromCbor(const QCborValue& cbor) override {
        QCborMap map = cbor.toMap();
        setRadius(static_cast<int16_t>(map.value(QLatin1String("radius")).toInteger()));
        setX(static_cast<int16_t>(map.value(QLatin1String("x")).toInteger()));
        setY(static_cast<int16_t>(map.value(QLatin1String("y")).toInteger()));
    }
    
    QString name() const override {
        return "Circle";
    }
    
    QStringList fields() const override {
        return QStringList{QLatin1String("radius"), QLatin1String("x"), QLatin1String("y")};
    }
    
    QString fieldType(const QString& fieldName) const override {
        if (fieldName == QLatin1String("radius")) return QLatin1String("int16");
        if (fieldName == QLatin1String("x")) return QLatin1String("int16");
        if (fieldName == QLatin1String("y")) return QLatin1String("int16");
        return QLatin1String("");
    }
    
    QList<QSharedPointer<void>> fieldAnnotation(const QString& fieldName) const override {
        
        return QList<QSharedPointer<void>>();
    }
    
    QString description() const override {
        return "Generated from block Circle";
    }
    
    QString fieldDescription(const QString& fieldName) const override {
        
        return QString();
    }
    
    QVariant value(const QString& fieldName) const override {
        if (fieldName == QLatin1String("radius")) return QVariant::fromValue(radius_);
        if (fieldName == QLatin1String("x")) return QVariant::fromValue(x_);
        if (fieldName == QLatin1String("y")) return QVariant::fromValue(y_);
        return QVariant();
    }
    
    void value(const QString& fieldName, const QVariant& value) override {
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
        // radius字段的访问器
    int16_t getRadius() const {
        return radius_;
    }
    
    void setRadius(const int16_t& value) {
        radius_ = value;
    } 

        // x字段的访问器
    int16_t getX() const {
        return x_;
    }
    
    void setX(const int16_t& value) {
        x_ = value;
    } 

        // y字段的访问器
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


// Ellipse块
class MODEL_EXPORT EllipseBlock : public IBlock {
public:
    EllipseBlock() = default;
    
    
    // 实现IBlock接口
    QCborValue toCbor() const override {
        QCborMap map;
        map.insert(QLatin1String("center"), getCenter().toCbor());
        map.insert(QLatin1String("width"), QCborValue(getWidth()));
        map.insert(QLatin1String("height"), QCborValue(getHeight()));
        map.insert(QLatin1String("rotation"), QCborValue(getRotation()));
        return map;
    }
    
    void fromCbor(const QCborValue& cbor) override {
        QCborMap map = cbor.toMap();
        PointBlock center;
        center.fromCbor(map.value(QLatin1String("center")));
        setCenter(center);
        setWidth(static_cast<int16_t>(map.value(QLatin1String("width")).toInteger()));
        setHeight(static_cast<int16_t>(map.value(QLatin1String("height")).toInteger()));
        setRotation(static_cast<float>(map.value(QLatin1String("rotation")).toDouble()));
    }
    
    QString name() const override {
        return "Ellipse";
    }
    
    QStringList fields() const override {
        return QStringList{QLatin1String("center"), QLatin1String("width"), QLatin1String("height"), QLatin1String("rotation")};
    }
    
    QString fieldType(const QString& fieldName) const override {
        if (fieldName == QLatin1String("center")) return QLatin1String("Point");
        if (fieldName == QLatin1String("width")) return QLatin1String("int16");
        if (fieldName == QLatin1String("height")) return QLatin1String("int16");
        if (fieldName == QLatin1String("rotation")) return QLatin1String("float32");
        return QLatin1String("");
    }
    
    QList<QSharedPointer<void>> fieldAnnotation(const QString& fieldName) const override {
        
        return QList<QSharedPointer<void>>();
    }
    
    QString description() const override {
        return "Generated from block Ellipse";
    }
    
    QString fieldDescription(const QString& fieldName) const override {
        
        return QString();
    }
    
    QVariant value(const QString& fieldName) const override {
        if (fieldName == QLatin1String("center")) return QVariant::fromValue(center_);
        if (fieldName == QLatin1String("width")) return QVariant::fromValue(width_);
        if (fieldName == QLatin1String("height")) return QVariant::fromValue(height_);
        if (fieldName == QLatin1String("rotation")) return QVariant::fromValue(rotation_);
        return QVariant();
    }
    
    void value(const QString& fieldName, const QVariant& value) override {
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
        // center字段的访问器
    PointBlock getCenter() const {
        return center_;
    }
    
    void setCenter(const PointBlock& value) {
        center_ = value;
    } 

        // width字段的访问器
    int16_t getWidth() const {
        return width_;
    }
    
    void setWidth(const int16_t& value) {
        width_ = value;
    } 

        // height字段的访问器
    int16_t getHeight() const {
        return height_;
    }
    
    void setHeight(const int16_t& value) {
        height_ = value;
    } 

        // rotation字段的访问器
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


// Arc块
class MODEL_EXPORT ArcBlock : public IBlock {
public:
    ArcBlock() = default;
    
    
    // 实现IBlock接口
    QCborValue toCbor() const override {
        QCborMap map;
        map.insert(QLatin1String("center"), getCenter().toCbor());
        map.insert(QLatin1String("radius"), QCborValue(getRadius()));
        map.insert(QLatin1String("startAngle"), QCborValue(getStartAngle()));
        map.insert(QLatin1String("endAngle"), QCborValue(getEndAngle()));
        map.insert(QLatin1String("rotation"), QCborValue(getRotation()));
        return map;
    }
    
    void fromCbor(const QCborValue& cbor) override {
        QCborMap map = cbor.toMap();
        PointBlock center;
        center.fromCbor(map.value(QLatin1String("center")));
        setCenter(center);
        setRadius(static_cast<int16_t>(map.value(QLatin1String("radius")).toInteger()));
        setStartAngle(static_cast<float>(map.value(QLatin1String("startAngle")).toDouble()));
        setEndAngle(static_cast<float>(map.value(QLatin1String("endAngle")).toDouble()));
        setRotation(static_cast<float>(map.value(QLatin1String("rotation")).toDouble()));
    }
    
    QString name() const override {
        return "Arc";
    }
    
    QStringList fields() const override {
        return QStringList{QLatin1String("center"), QLatin1String("radius"), QLatin1String("startAngle"), QLatin1String("endAngle"), QLatin1String("rotation")};
    }
    
    QString fieldType(const QString& fieldName) const override {
        if (fieldName == QLatin1String("center")) return QLatin1String("Point");
        if (fieldName == QLatin1String("radius")) return QLatin1String("int16");
        if (fieldName == QLatin1String("startAngle")) return QLatin1String("float32");
        if (fieldName == QLatin1String("endAngle")) return QLatin1String("float32");
        if (fieldName == QLatin1String("rotation")) return QLatin1String("float32");
        return QLatin1String("");
    }
    
    QList<QSharedPointer<void>> fieldAnnotation(const QString& fieldName) const override {
        
        return QList<QSharedPointer<void>>();
    }
    
    QString description() const override {
        return "Generated from block Arc";
    }
    
    QString fieldDescription(const QString& fieldName) const override {
        
        return QString();
    }
    
    QVariant value(const QString& fieldName) const override {
        if (fieldName == QLatin1String("center")) return QVariant::fromValue(center_);
        if (fieldName == QLatin1String("radius")) return QVariant::fromValue(radius_);
        if (fieldName == QLatin1String("startAngle")) return QVariant::fromValue(startAngle_);
        if (fieldName == QLatin1String("endAngle")) return QVariant::fromValue(endAngle_);
        if (fieldName == QLatin1String("rotation")) return QVariant::fromValue(rotation_);
        return QVariant();
    }
    
    void value(const QString& fieldName, const QVariant& value) override {
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
        // center字段的访问器
    PointBlock getCenter() const {
        return center_;
    }
    
    void setCenter(const PointBlock& value) {
        center_ = value;
    } 

        // radius字段的访问器
    int16_t getRadius() const {
        return radius_;
    }
    
    void setRadius(const int16_t& value) {
        radius_ = value;
    } 

        // startAngle字段的访问器
    float getStartAngle() const {
        return startAngle_;
    }
    
    void setStartAngle(const float& value) {
        startAngle_ = value;
    } 

        // endAngle字段的访问器
    float getEndAngle() const {
        return endAngle_;
    }
    
    void setEndAngle(const float& value) {
        endAngle_ = value;
    } 

        // rotation字段的访问器
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


// Polygon块
class MODEL_EXPORT PolygonBlock : public IBlock {
public:
    PolygonBlock() = default;
    
    
    // 实现IBlock接口
    QCborValue toCbor() const override {
        QCborMap map;
        QCborArray pointsArray;
        for (const auto& item : getPoints()) {
            pointsArray.append(item.toCbor());
        }
        map.insert(QLatin1String("points"), pointsArray);
        return map;
    }
    
    void fromCbor(const QCborValue& cbor) override {
        QCborMap map = cbor.toMap();
        QCborArray pointsArray = map.value(QLatin1String("points")).toArray();
        QVector<PointBlock> points;
        for (const auto& itemValue : pointsArray) {
            PointBlock item;
            item.fromCbor(itemValue);
            points.append(item);
        }
        setPoints(points);
    }
    
    QString name() const override {
        return "Polygon";
    }
    
    QStringList fields() const override {
        return QStringList{QLatin1String("points")};
    }
    
    QString fieldType(const QString& fieldName) const override {
        if (fieldName == QLatin1String("points")) return QLatin1String("repeated Point");
        return QLatin1String("");
    }
    
    QList<QSharedPointer<void>> fieldAnnotation(const QString& fieldName) const override {
        
        return QList<QSharedPointer<void>>();
    }
    
    QString description() const override {
        return "Generated from block Polygon";
    }
    
    QString fieldDescription(const QString& fieldName) const override {
        
        return QString();
    }
    
    QVariant value(const QString& fieldName) const override {
        if (fieldName == QLatin1String("points")) return QVariant::fromValue(points_);
        return QVariant();
    }
    
    void value(const QString& fieldName, const QVariant& value) override {
        if (fieldName == QLatin1String("points")) {
            points_ = value.value<QVector<PointBlock>>();
            return;
        }
    }
    
    // 特定于Polygon的访问器
        // points字段的访问器
    QVector<PointBlock> getPoints() const {
        return points_;
    }
    
    void setPoints(const QVector<PointBlock>& value) {
        points_ = value;
    } 
    
private:
    QVector<PointBlock> points_;
};


// Line块
class MODEL_EXPORT LineBlock : public IBlock {
public:
    LineBlock() = default;
    
    
    // 实现IBlock接口
    QCborValue toCbor() const override {
        QCborMap map;
        map.insert(QLatin1String("start"), getStart().toCbor());
        map.insert(QLatin1String("end"), getEnd().toCbor());
        return map;
    }
    
    void fromCbor(const QCborValue& cbor) override {
        QCborMap map = cbor.toMap();
        PointBlock start;
        start.fromCbor(map.value(QLatin1String("start")));
        setStart(start);
        PointBlock end;
        end.fromCbor(map.value(QLatin1String("end")));
        setEnd(end);
    }
    
    QString name() const override {
        return "Line";
    }
    
    QStringList fields() const override {
        return QStringList{QLatin1String("start"), QLatin1String("end")};
    }
    
    QString fieldType(const QString& fieldName) const override {
        if (fieldName == QLatin1String("start")) return QLatin1String("Point");
        if (fieldName == QLatin1String("end")) return QLatin1String("Point");
        return QLatin1String("");
    }
    
    QList<QSharedPointer<void>> fieldAnnotation(const QString& fieldName) const override {
        
        return QList<QSharedPointer<void>>();
    }
    
    QString description() const override {
        return "Generated from block Line";
    }
    
    QString fieldDescription(const QString& fieldName) const override {
        
        return QString();
    }
    
    QVariant value(const QString& fieldName) const override {
        if (fieldName == QLatin1String("start")) return QVariant::fromValue(start_);
        if (fieldName == QLatin1String("end")) return QVariant::fromValue(end_);
        return QVariant();
    }
    
    void value(const QString& fieldName, const QVariant& value) override {
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
        // start字段的访问器
    PointBlock getStart() const {
        return start_;
    }
    
    void setStart(const PointBlock& value) {
        start_ = value;
    } 

        // end字段的访问器
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



} // namespace yima

