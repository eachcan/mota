#pragma once

#include "IBlock.h"
#include <QString>
#include <QStringList>
#include <QVariant>
#include <QCborValue>
#include <QCborMap>
#include <QCborArray>
#include <QList>
#include <QSharedPointer>
#include <QVector>

using namespace ymf;

namespace yima {

// Point块
class Point : public IBlock {
public:
    Point() = default;
    
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
        return QStringList() << "x" << "y";
    }
    
    QString fieldType(const QString& fieldName) const override {
        if (fieldName == "x" || fieldName == "y") {
            return "int16";
        }
        return QString();
    }
    
    QList<QSharedPointer<void>> fieldAnnotation(const QString& fieldName) const override {
        return QList<QSharedPointer<void>>();
    }
    
    QString description() const override {
        return "二维点坐标";
    }
    
    QString fieldDescription(const QString& fieldName) const override {
        if (fieldName == "x") {
            return "X坐标";
        } else if (fieldName == "y") {
            return "Y坐标";
        }
        return QString();
    }
    
    QVariant value(const QString& fieldName) const override {
        if (fieldName == "x") {
            return QVariant(getX());
        } else if (fieldName == "y") {
            return QVariant(getY());
        }
        return QVariant();
    }
    
    void value(const QString& fieldName, const QVariant& value) override {
        if (fieldName == "x") {
            setX(static_cast<int16_t>(value.toInt()));
        } else if (fieldName == "y") {
            setY(static_cast<int16_t>(value.toInt()));
        }
    }
    
    // 特定于Point的访问器
    int16_t getX() const { return m_x; }
    void setX(int16_t value) { m_x = value; }
    
    int16_t getY() const { return m_y; }
    void setY(int16_t value) { m_y = value; }
    
private:
    int16_t m_x = 0;
    int16_t m_y = 0;
};

// Rectangle块
class Rectangle : public IBlock {
public:
    Rectangle() = default;
    Rectangle(int16_t width, int16_t height, int16_t x, int16_t y) 
        : m_width(width), m_height(height), m_x(x), m_y(y) {}
    
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
        return QStringList() << "width" << "height" << "x" << "y";
    }
    
    QString fieldType(const QString& fieldName) const override {
        if (fieldName == "width" || fieldName == "height" || fieldName == "x" || fieldName == "y") {
            return "int16";
        }
        return QString();
    }
    
    QList<QSharedPointer<void>> fieldAnnotation(const QString& fieldName) const override {
        return QList<QSharedPointer<void>>();
    }
    
    QString description() const override {
        return "矩形";
    }
    
    QString fieldDescription(const QString& fieldName) const override {
        if (fieldName == "width") {
            return "宽度";
        } else if (fieldName == "height") {
            return "高度";
        } else if (fieldName == "x") {
            return "X坐标";
        } else if (fieldName == "y") {
            return "Y坐标";
        }
        return QString();
    }
    
    QVariant value(const QString& fieldName) const override {
        if (fieldName == "width") {
            return QVariant(getWidth());
        } else if (fieldName == "height") {
            return QVariant(getHeight());
        } else if (fieldName == "x") {
            return QVariant(getX());
        } else if (fieldName == "y") {
            return QVariant(getY());
        }
        return QVariant();
    }
    
    void value(const QString& fieldName, const QVariant& value) override {
        if (fieldName == "width") {
            setWidth(static_cast<int16_t>(value.toInt()));
        } else if (fieldName == "height") {
            setHeight(static_cast<int16_t>(value.toInt()));
        } else if (fieldName == "x") {
            setX(static_cast<int16_t>(value.toInt()));
        } else if (fieldName == "y") {
            setY(static_cast<int16_t>(value.toInt()));
        }
    }
    
    // 特定于Rectangle的访问器
    int16_t getWidth() const { return m_width; }
    void setWidth(int16_t value) { m_width = value; }
    
    int16_t getHeight() const { return m_height; }
    void setHeight(int16_t value) { m_height = value; }
    
    int16_t getX() const { return m_x; }
    void setX(int16_t value) { m_x = value; }
    
    int16_t getY() const { return m_y; }
    void setY(int16_t value) { m_y = value; }
    
private:
    int16_t m_width = 0;
    int16_t m_height = 0;
    int16_t m_x = 0;
    int16_t m_y = 0;
};

// Circle块
class Circle : public IBlock {
public:
    Circle() = default;
    Circle(int16_t radius, int16_t x, int16_t y) 
        : m_radius(radius), m_x(x), m_y(y) {}
    
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
        return QStringList() << "radius" << "x" << "y";
    }
    
    QString fieldType(const QString& fieldName) const override {
        if (fieldName == "radius" || fieldName == "x" || fieldName == "y") {
            return "int16";
        }
        return QString();
    }
    
    QList<QSharedPointer<void>> fieldAnnotation(const QString& fieldName) const override {
        return QList<QSharedPointer<void>>();
    }
    
    QString description() const override {
        return "圆形";
    }
    
    QString fieldDescription(const QString& fieldName) const override {
        if (fieldName == "radius") {
            return "半径";
        } else if (fieldName == "x") {
            return "圆心X坐标";
        } else if (fieldName == "y") {
            return "圆心Y坐标";
        }
        return QString();
    }
    
    QVariant value(const QString& fieldName) const override {
        if (fieldName == "radius") {
            return QVariant(getRadius());
        } else if (fieldName == "x") {
            return QVariant(getX());
        } else if (fieldName == "y") {
            return QVariant(getY());
        }
        return QVariant();
    }
    
    void value(const QString& fieldName, const QVariant& value) override {
        if (fieldName == "radius") {
            setRadius(static_cast<int16_t>(value.toInt()));
        } else if (fieldName == "x") {
            setX(static_cast<int16_t>(value.toInt()));
        } else if (fieldName == "y") {
            setY(static_cast<int16_t>(value.toInt()));
        }
    }
    
    // 特定于Circle的访问器
    int16_t getRadius() const { return m_radius; }
    void setRadius(int16_t value) { m_radius = value; }
    
    int16_t getX() const { return m_x; }
    void setX(int16_t value) { m_x = value; }
    
    int16_t getY() const { return m_y; }
    void setY(int16_t value) { m_y = value; }
    
private:
    int16_t m_radius = 0;
    int16_t m_x = 0;
    int16_t m_y = 0;
};

// Ellipse块
class Ellipse : public IBlock {
public:
    Ellipse() = default;
    Ellipse(const Point& center, int16_t width, int16_t height, float rotation) 
        : m_center(center), m_width(width), m_height(height), m_rotation(rotation) {}
    
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
        Point center;
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
        return QStringList() << "center" << "width" << "height" << "rotation";
    }
    
    QString fieldType(const QString& fieldName) const override {
        if (fieldName == "center") {
            return "Point";
        } else if (fieldName == "width" || fieldName == "height") {
            return "int16";
        } else if (fieldName == "rotation") {
            return "float32";
        }
        return QString();
    }
    
    QList<QSharedPointer<void>> fieldAnnotation(const QString& fieldName) const override {
        return QList<QSharedPointer<void>>();
    }
    
    QString description() const override {
        return "椭圆";
    }
    
    QString fieldDescription(const QString& fieldName) const override {
        if (fieldName == "center") {
            return "中心点";
        } else if (fieldName == "width") {
            return "宽度";
        } else if (fieldName == "height") {
            return "高度";
        } else if (fieldName == "rotation") {
            return "旋转角度（弧度）";
        }
        return QString();
    }
    
    QVariant value(const QString& fieldName) const override {
        if (fieldName == "center") {
            return QVariant::fromValue(&m_center);
        } else if (fieldName == "width") {
            return QVariant(getWidth());
        } else if (fieldName == "height") {
            return QVariant(getHeight());
        } else if (fieldName == "rotation") {
            return QVariant(getRotation());
        }
        return QVariant();
    }
    
    void value(const QString& fieldName, const QVariant& value) override {
        if (fieldName == "width") {
            setWidth(static_cast<int16_t>(value.toInt()));
        } else if (fieldName == "height") {
            setHeight(static_cast<int16_t>(value.toInt()));
        } else if (fieldName == "rotation") {
            setRotation(value.toFloat());
        }
        // 注意：center是复合类型，需要单独处理
    }
    
    // 特定于Ellipse的访问器
    Point getCenter() const { return m_center; }
    void setCenter(const Point& value) { m_center = value; }
    
    int16_t getWidth() const { return m_width; }
    void setWidth(int16_t value) { m_width = value; }
    
    int16_t getHeight() const { return m_height; }
    void setHeight(int16_t value) { m_height = value; }
    
    float getRotation() const { return m_rotation; }
    void setRotation(float value) { m_rotation = value; }
    
private:
    Point m_center;
    int16_t m_width = 0;
    int16_t m_height = 0;
    float m_rotation = 0.0f;
};

// Arc块
class Arc : public IBlock {
public:
    Arc() = default;
    Arc(const Point& center, int16_t radius, float startAngle, float endAngle, float rotation) 
        : m_center(center), m_radius(radius), m_startAngle(startAngle), m_endAngle(endAngle), m_rotation(rotation) {}
    
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
        Point center;
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
        return QStringList() << "center" << "radius" << "startAngle" << "endAngle" << "rotation";
    }
    
    QString fieldType(const QString& fieldName) const override {
        if (fieldName == "center") {
            return "Point";
        } else if (fieldName == "radius") {
            return "int16";
        } else if (fieldName == "startAngle" || fieldName == "endAngle" || fieldName == "rotation") {
            return "float32";
        }
        return QString();
    }
    
    QList<QSharedPointer<void>> fieldAnnotation(const QString& fieldName) const override {
        return QList<QSharedPointer<void>>();
    }
    
    QString description() const override {
        return "圆弧";
    }
    
    QString fieldDescription(const QString& fieldName) const override {
        if (fieldName == "center") {
            return "中心点";
        } else if (fieldName == "radius") {
            return "半径";
        } else if (fieldName == "startAngle") {
            return "起始角度（弧度）";
        } else if (fieldName == "endAngle") {
            return "结束角度（弧度）";
        } else if (fieldName == "rotation") {
            return "旋转角度（弧度）";
        }
        return QString();
    }
    
    QVariant value(const QString& fieldName) const override {
        if (fieldName == "center") {
            return QVariant::fromValue(&m_center);
        } else if (fieldName == "radius") {
            return QVariant(getRadius());
        } else if (fieldName == "startAngle") {
            return QVariant(getStartAngle());
        } else if (fieldName == "endAngle") {
            return QVariant(getEndAngle());
        } else if (fieldName == "rotation") {
            return QVariant(getRotation());
        }
        return QVariant();
    }
    
    void value(const QString& fieldName, const QVariant& value) override {
        if (fieldName == "radius") {
            setRadius(static_cast<int16_t>(value.toInt()));
        } else if (fieldName == "startAngle") {
            setStartAngle(value.toFloat());
        } else if (fieldName == "endAngle") {
            setEndAngle(value.toFloat());
        } else if (fieldName == "rotation") {
            setRotation(value.toFloat());
        }
        // 注意：center是复合类型，需要单独处理
    }
    
    // 特定于Arc的访问器
    Point getCenter() const { return m_center; }
    void setCenter(const Point& value) { m_center = value; }
    
    int16_t getRadius() const { return m_radius; }
    void setRadius(int16_t value) { m_radius = value; }
    
    float getStartAngle() const { return m_startAngle; }
    void setStartAngle(float value) { m_startAngle = value; }
    
    float getEndAngle() const { return m_endAngle; }
    void setEndAngle(float value) { m_endAngle = value; }
    
    float getRotation() const { return m_rotation; }
    void setRotation(float value) { m_rotation = value; }
    
private:
    Point m_center;
    int16_t m_radius = 0;
    float m_startAngle = 0.0f;
    float m_endAngle = 0.0f;
    float m_rotation = 0.0f;
};

// Polygon块
class Polygon : public IBlock {
public:
    Polygon() = default;
    Polygon(const QVector<Point>& points) : m_points(points) {}
    
    // 实现IBlock接口
    QCborValue toCbor() const override {
        QCborMap map;
        QCborArray pointsArray;
        for (const auto& point : getPoints()) {
            pointsArray.append(point.toCbor());
        }
        map.insert(QLatin1String("points"), pointsArray);
        return map;
    }
    
    void fromCbor(const QCborValue& cbor) override {
        QCborMap map = cbor.toMap();
        QCborArray pointsArray = map.value(QLatin1String("points")).toArray();
        QVector<Point> points;
        for (const auto& pointValue : pointsArray) {
            Point point;
            point.fromCbor(pointValue);
            points.append(point);
        }
        setPoints(points);
    }
    
    QString name() const override {
        return "Polygon";
    }
    
    QStringList fields() const override {
        return QStringList() << "points";
    }
    
    QString fieldType(const QString& fieldName) const override {
        if (fieldName == "points") {
            return "repeated Point";
        }
        return QString();
    }
    
    QList<QSharedPointer<void>> fieldAnnotation(const QString& fieldName) const override {
        return QList<QSharedPointer<void>>();
    }
    
    QString description() const override {
        return "多边形";
    }
    
    QString fieldDescription(const QString& fieldName) const override {
        if (fieldName == "points") {
            return "顶点列表";
        }
        return QString();
    }
    
    QVariant value(const QString& fieldName) const override {
        if (fieldName == "points") {
            // 注意：这里返回的是指向内部数据的指针，实际使用时可能需要更复杂的处理
            return QVariant::fromValue(&m_points);
        }
        return QVariant();
    }
    
    void value(const QString& fieldName, const QVariant& value) override {
        // 对于复杂类型，可能需要特殊处理
    }
    
    // 特定于Polygon的访问器
    QVector<Point> getPoints() const { return m_points; }
    void setPoints(const QVector<Point>& value) { m_points = value; }
    
    // 添加点
    void addPoint(const Point& point) {
        m_points.append(point);
    }
    
    // 移除点
    void removePoint(int index) {
        if (index >= 0 && index < m_points.size()) {
            m_points.remove(index);
        }
    }
    
    // 获取点数量
    int pointCount() const {
        return m_points.size();
    }
    
private:
    QVector<Point> m_points;
};

// Line块
class Line : public IBlock {
public:
    Line() = default;
    Line(const Point& start, const Point& end) : m_start(start), m_end(end) {}
    
    // 实现IBlock接口
    QCborValue toCbor() const override {
        QCborMap map;
        map.insert(QLatin1String("start"), getStart().toCbor());
        map.insert(QLatin1String("end"), getEnd().toCbor());
        return map;
    }
    
    void fromCbor(const QCborValue& cbor) override {
        QCborMap map = cbor.toMap();
        Point start, end;
        start.fromCbor(map.value(QLatin1String("start")));
        end.fromCbor(map.value(QLatin1String("end")));
        setStart(start);
        setEnd(end);
    }
    
    QString name() const override {
        return "Line";
    }
    
    QStringList fields() const override {
        return QStringList() << "start" << "end";
    }
    
    QString fieldType(const QString& fieldName) const override {
        if (fieldName == "start" || fieldName == "end") {
            return "Point";
        }
        return QString();
    }
    
    QList<QSharedPointer<void>> fieldAnnotation(const QString& fieldName) const override {
        return QList<QSharedPointer<void>>();
    }
    
    QString description() const override {
        return "线段";
    }
    
    QString fieldDescription(const QString& fieldName) const override {
        if (fieldName == "start") {
            return "起点";
        } else if (fieldName == "end") {
            return "终点";
        }
        return QString();
    }
    
    QVariant value(const QString& fieldName) const override {
        if (fieldName == "start") {
            return QVariant::fromValue(&m_start);
        } else if (fieldName == "end") {
            return QVariant::fromValue(&m_end);
        }
        return QVariant();
    }
    
    void value(const QString& fieldName, const QVariant& value) override {
        // 对于复合类型，可能需要特殊处理
    }
    
    // 特定于Line的访问器
    Point getStart() const { return m_start; }
    void setStart(const Point& value) { m_start = value; }
    
    Point getEnd() const { return m_end; }
    void setEnd(const Point& value) { m_end = value; }
    
private:
    Point m_start;
    Point m_end;
};

} // namespace yima
