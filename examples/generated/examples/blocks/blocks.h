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
// 生成时间: 2025-06-08 00:40:40
// 源文件: unknown.mota

using namespace ymf;


namespace examples::blocks {


// CameraConfig块
class MODEL_EXPORT CameraConfigBlock : public IBlock {
public:
    CameraConfigBlock() = default;
    
    
    // 实现IBlock接口
    QCborValue toCbor() const override {
        QCborMap map;
        map.insert(QLatin1String("x"), QCborValue(getX()));
        map.insert(QLatin1String("y"), QCborValue(getY()));
        map.insert(QLatin1String("type"), QCborValue(getType()));
        map.insert(QLatin1String("exposure"), QCborValue(getExposure()));
        map.insert(QLatin1String("triggerEnabled"), QCborValue(getTriggerEnabled()));
        return map;
    }
    
    void fromCbor(const QCborValue& cbor) override {
        QCborMap map = cbor.toMap();
        setX(static_cast<int32_t>(map.value(QLatin1String("x")).toInteger()));
        setY(static_cast<int32_t>(map.value(QLatin1String("y")).toInteger()));
        setType(map.value(QLatin1String("type")).toString());
        setExposure(static_cast<double>(map.value(QLatin1String("exposure")).toDouble()));
        setTriggerEnabled(map.value(QLatin1String("triggerEnabled")).toBool());
    }
    
    QString name() const override {
        return "CameraConfig";
    }
    
    QStringList fields() const override {
        return QStringList{QLatin1String("x"), QLatin1String("y"), QLatin1String("type"), QLatin1String("exposure"), QLatin1String("triggerEnabled")};
    }
    
    QString fieldType(const QString& fieldName) const override {
        if (fieldName == QLatin1String("x")) return QLatin1String("int32");
        if (fieldName == QLatin1String("y")) return QLatin1String("int32");
        if (fieldName == QLatin1String("type")) return QLatin1String("string");
        if (fieldName == QLatin1String("exposure")) return QLatin1String("float64");
        if (fieldName == QLatin1String("triggerEnabled")) return QLatin1String("bool");
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
        if (fieldName == QLatin1String("type")) {
            return QList<QSharedPointer<void>>();
        }
        if (fieldName == QLatin1String("exposure")) {
            return QList<QSharedPointer<void>>();
        }
        if (fieldName == QLatin1String("triggerEnabled")) {
            return QList<QSharedPointer<void>>();
        }
        return QList<QSharedPointer<void>>();
    }
    
    QString description() const override {
        return "Generated from block CameraConfig";
    }
    
    QString fieldDescription(const QString& fieldName) const override {
        
        return QString();
    }
    
    QVariant value(const QString& fieldName) const override {
        if (fieldName == QLatin1String("x")) return QVariant::fromValue(x_);
        if (fieldName == QLatin1String("y")) return QVariant::fromValue(y_);
        if (fieldName == QLatin1String("type")) return QVariant::fromValue(type_);
        if (fieldName == QLatin1String("exposure")) return QVariant::fromValue(exposure_);
        if (fieldName == QLatin1String("triggerEnabled")) return QVariant::fromValue(triggerEnabled_);
        return QVariant();
    }
    
    void value(const QString& fieldName, const QVariant& value) override {
        if (fieldName == QLatin1String("x")) {
            x_ = value.value<int32_t>();
            return;
        }
        if (fieldName == QLatin1String("y")) {
            y_ = value.value<int32_t>();
            return;
        }
        if (fieldName == QLatin1String("type")) {
            type_ = value.value<QString>();
            return;
        }
        if (fieldName == QLatin1String("exposure")) {
            exposure_ = value.value<double>();
            return;
        }
        if (fieldName == QLatin1String("triggerEnabled")) {
            triggerEnabled_ = value.value<bool>();
            return;
        }
    }
    
    // 特定于CameraConfig的访问器
        // x字段的访问器
    int32_t getX() const {
        return x_;
    }
    
    void setX(const int32_t& value) {
        x_ = value;
    } 

        // y字段的访问器
    int32_t getY() const {
        return y_;
    }
    
    void setY(const int32_t& value) {
        y_ = value;
    } 

        // type字段的访问器
    QString getType() const {
        return type_;
    }
    
    void setType(const QString& value) {
        type_ = value;
    } 

        // exposure字段的访问器
    double getExposure() const {
        return exposure_;
    }
    
    void setExposure(const double& value) {
        exposure_ = value;
    } 

        // triggerEnabled字段的访问器
    bool getTriggerEnabled() const {
        return triggerEnabled_;
    }
    
    void setTriggerEnabled(const bool& value) {
        triggerEnabled_ = value;
    } 
    
private:
    int32_t x_;
    int32_t y_;
    QString type_;
    double exposure_;
    bool triggerEnabled_;
};


// SystemInfo块
class MODEL_EXPORT SystemInfoBlock : public IBlock {
public:
    SystemInfoBlock() = default;
    
    
    // 实现IBlock接口
    QCborValue toCbor() const override {
        QCborMap map;
        map.insert(QLatin1String("name"), QCborValue(getName()));
        map.insert(QLatin1String("version"), QCborValue(getVersion()));
        return map;
    }
    
    void fromCbor(const QCborValue& cbor) override {
        QCborMap map = cbor.toMap();
        setName(map.value(QLatin1String("name")).toString());
        setVersion(map.value(QLatin1String("version")).toString());
    }
    
    QString name() const override {
        return "SystemInfo";
    }
    
    QStringList fields() const override {
        return QStringList{QLatin1String("name"), QLatin1String("version")};
    }
    
    QString fieldType(const QString& fieldName) const override {
        if (fieldName == QLatin1String("name")) return QLatin1String("string");
        if (fieldName == QLatin1String("version")) return QLatin1String("string");
        return QLatin1String("");
    }
    
    QList<QSharedPointer<IAnnotation>> annotations() const override {
        
        return QList<QSharedPointer<IAnnotation>>();
    }
    
    QList<QSharedPointer<void>> fieldAnnotation(const QString& fieldName) const override {
        if (fieldName == QLatin1String("name")) {
            return QList<QSharedPointer<void>>();
        }
        if (fieldName == QLatin1String("version")) {
            return QList<QSharedPointer<void>>();
        }
        return QList<QSharedPointer<void>>();
    }
    
    QString description() const override {
        return "Generated from block SystemInfo";
    }
    
    QString fieldDescription(const QString& fieldName) const override {
        
        return QString();
    }
    
    QVariant value(const QString& fieldName) const override {
        if (fieldName == QLatin1String("name")) return QVariant::fromValue(name_);
        if (fieldName == QLatin1String("version")) return QVariant::fromValue(version_);
        return QVariant();
    }
    
    void value(const QString& fieldName, const QVariant& value) override {
        if (fieldName == QLatin1String("name")) {
            name_ = value.value<QString>();
            return;
        }
        if (fieldName == QLatin1String("version")) {
            version_ = value.value<QString>();
            return;
        }
    }
    
    // 特定于SystemInfo的访问器
        // name字段的访问器
    QString getName() const {
        return name_;
    }
    
    void setName(const QString& value) {
        name_ = value;
    } 

        // version字段的访问器
    QString getVersion() const {
        return version_;
    }
    
    void setVersion(const QString& value) {
        version_ = value;
    } 
    
private:
    QString name_;
    QString version_;
};


// VisionSystem结构体

class MODEL_EXPORT VisionSystemModel : public IModel {
public:
    VisionSystemModel() = default;
    
    
    // 实现IModel接口
    QCborValue toCbor() const override {
        QCborMap map;
        QCborArray camerasArray;
        for (const auto& item : getCameras()) {
            camerasArray.append(item.toCbor());
        }
        map.insert(QLatin1String("cameras"), camerasArray);
        map.insert(QLatin1String("info"), getInfo().toCbor());
        return map;
    }
    
    void fromCbor(const QCborValue& cbor) override {
        QCborMap map = cbor.toMap();
        QCborArray camerasArray = map.value(QLatin1String("cameras")).toArray();
        QVector<CameraConfigBlock> cameras;
        for (const auto& itemValue : camerasArray) {
            CameraConfigBlock item;
            item.fromCbor(itemValue);
            cameras.append(item);
        }
        setCameras(cameras);
        SystemInfoBlock info;
        info.fromCbor(map.value(QLatin1String("info")));
        setInfo(info);
    }
    
    QStringList fields() const override {
        return QStringList{QLatin1String("cameras"), QLatin1String("info")};
    }
    
    QString fieldOriginTypeName(const QString& fieldName) const override {
        if (fieldName == QLatin1String("cameras")) return QLatin1String("repeated CameraConfig");
        if (fieldName == QLatin1String("info")) return QLatin1String("SystemInfo");
        return QLatin1String("");
    }
    
    QList<QSharedPointer<IAnnotation>> annotations() const override {
        
        return QList<QSharedPointer<IAnnotation>>();
    }
    
    QList<QSharedPointer<void>> fieldAnnotations(const QString& fieldName) const override {
        if (fieldName == QLatin1String("cameras")) {
            return QList<QSharedPointer<void>>();
        }
        if (fieldName == QLatin1String("info")) {
            return QList<QSharedPointer<void>>();
        }
        return QList<QSharedPointer<void>>();
    }
    
    QString description() const override {
        return "Generated from struct VisionSystem";
    }
    
    QString fieldDescription(const QString& fieldName) const override {
        
        return QString();
    }
    
    QVariant value(const QString& fieldName) const override {
        if (fieldName == QLatin1String("cameras")) return QVariant::fromValue(cameras_);
        if (fieldName == QLatin1String("info")) return QVariant::fromValue(info_);
        return QVariant();
    }
    
    void value(const QString& fieldName, const QVariant& value) override {
        if (fieldName == QLatin1String("cameras")) {
            cameras_ = value.value<QVector<CameraConfigBlock>>();
            return;
        }
        if (fieldName == QLatin1String("info")) {
            info_ = value.value<SystemInfoBlock>();
            return;
        }
    }
    
    // 特定于VisionSystem的访问器
        // cameras字段的访问器
    QVector<CameraConfigBlock> getCameras() const {
        return cameras_;
    }
    
    void setCameras(const QVector<CameraConfigBlock>& value) {
        cameras_ = value;
    } 

        // info字段的访问器
    SystemInfoBlock getInfo() const {
        return info_;
    }
    
    void setInfo(const SystemInfoBlock& value) {
        info_ = value;
    } 
    
protected:
    QString modelName() const override {
        return "VisionSystem";
    }
    
private:
    QVector<CameraConfigBlock> cameras_;
    SystemInfoBlock info_;
    
    // 变更通知
    void notifyChange();
};



} // namespace examples::blocks

