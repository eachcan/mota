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


namespace examples::includes {


// WindowSettings块
class MODEL_EXPORT WindowSettingsBlock : public IBlock {
public:
    WindowSettingsBlock() = default;
    
    
    // 实现IBlock接口
    QCborValue toCbor() const override {
        QCborMap map;
        map.insert(QLatin1String("width"), QCborValue(getWidth()));
        map.insert(QLatin1String("height"), QCborValue(getHeight()));
        map.insert(QLatin1String("fullscreen"), QCborValue(getFullscreen()));
        return map;
    }
    
    void fromCbor(const QCborValue& cbor) override {
        QCborMap map = cbor.toMap();
        setWidth(static_cast<int32_t>(map.value(QLatin1String("width")).toInteger()));
        setHeight(static_cast<int32_t>(map.value(QLatin1String("height")).toInteger()));
        setFullscreen(map.value(QLatin1String("fullscreen")).toBool());
    }
    
    QString name() const override {
        return "WindowSettings";
    }
    
    QStringList fields() const override {
        return QStringList{QLatin1String("width"), QLatin1String("height"), QLatin1String("fullscreen")};
    }
    
    QString fieldType(const QString& fieldName) const override {
        if (fieldName == QLatin1String("width")) return QLatin1String("int32");
        if (fieldName == QLatin1String("height")) return QLatin1String("int32");
        if (fieldName == QLatin1String("fullscreen")) return QLatin1String("bool");
        return QLatin1String("");
    }
    
    QList<QSharedPointer<IAnnotation>> annotations() const override {
        
        return QList<QSharedPointer<IAnnotation>>();
    }
    
    QList<QSharedPointer<void>> fieldAnnotation(const QString& fieldName) const override {
        if (fieldName == QLatin1String("width")) {
            return QList<QSharedPointer<void>>();
        }
        if (fieldName == QLatin1String("height")) {
            return QList<QSharedPointer<void>>();
        }
        if (fieldName == QLatin1String("fullscreen")) {
            return QList<QSharedPointer<void>>();
        }
        return QList<QSharedPointer<void>>();
    }
    
    QString description() const override {
        return "Generated from block WindowSettings";
    }
    
    QString fieldDescription(const QString& fieldName) const override {
        
        return QString();
    }
    
    QVariant value(const QString& fieldName) const override {
        if (fieldName == QLatin1String("width")) return QVariant::fromValue(width_);
        if (fieldName == QLatin1String("height")) return QVariant::fromValue(height_);
        if (fieldName == QLatin1String("fullscreen")) return QVariant::fromValue(fullscreen_);
        return QVariant();
    }
    
    void value(const QString& fieldName, const QVariant& value) override {
        if (fieldName == QLatin1String("width")) {
            width_ = value.value<int32_t>();
            return;
        }
        if (fieldName == QLatin1String("height")) {
            height_ = value.value<int32_t>();
            return;
        }
        if (fieldName == QLatin1String("fullscreen")) {
            fullscreen_ = value.value<bool>();
            return;
        }
    }
    
    // 特定于WindowSettings的访问器
        // width字段的访问器
    int32_t getWidth() const {
        return width_;
    }
    
    void setWidth(const int32_t& value) {
        width_ = value;
    } 

        // height字段的访问器
    int32_t getHeight() const {
        return height_;
    }
    
    void setHeight(const int32_t& value) {
        height_ = value;
    } 

        // fullscreen字段的访问器
    bool getFullscreen() const {
        return fullscreen_;
    }
    
    void setFullscreen(const bool& value) {
        fullscreen_ = value;
    } 
    
private:
    int32_t width_;
    int32_t height_;
    bool fullscreen_;
};


// DebugSettings块
class MODEL_EXPORT DebugSettingsBlock : public IBlock {
public:
    DebugSettingsBlock() = default;
    
    
    // 实现IBlock接口
    QCborValue toCbor() const override {
        QCborMap map;
        map.insert(QLatin1String("enableDebugTools"), QCborValue(getEnableDebugTools()));
        map.insert(QLatin1String("showFPS"), QCborValue(getShowFPS()));
        map.insert(QLatin1String("logLevel"), QCborValue(getLogLevel()));
        return map;
    }
    
    void fromCbor(const QCborValue& cbor) override {
        QCborMap map = cbor.toMap();
        setEnableDebugTools(map.value(QLatin1String("enableDebugTools")).toBool());
        setShowFPS(map.value(QLatin1String("showFPS")).toBool());
        setLogLevel(map.value(QLatin1String("logLevel")).toString());
    }
    
    QString name() const override {
        return "DebugSettings";
    }
    
    QStringList fields() const override {
        return QStringList{QLatin1String("enableDebugTools"), QLatin1String("showFPS"), QLatin1String("logLevel")};
    }
    
    QString fieldType(const QString& fieldName) const override {
        if (fieldName == QLatin1String("enableDebugTools")) return QLatin1String("bool");
        if (fieldName == QLatin1String("showFPS")) return QLatin1String("bool");
        if (fieldName == QLatin1String("logLevel")) return QLatin1String("string");
        return QLatin1String("");
    }
    
    QList<QSharedPointer<IAnnotation>> annotations() const override {
        
        return QList<QSharedPointer<IAnnotation>>();
    }
    
    QList<QSharedPointer<void>> fieldAnnotation(const QString& fieldName) const override {
        if (fieldName == QLatin1String("enableDebugTools")) {
            return QList<QSharedPointer<void>>();
        }
        if (fieldName == QLatin1String("showFPS")) {
            return QList<QSharedPointer<void>>();
        }
        if (fieldName == QLatin1String("logLevel")) {
            return QList<QSharedPointer<void>>();
        }
        return QList<QSharedPointer<void>>();
    }
    
    QString description() const override {
        return "Generated from block DebugSettings";
    }
    
    QString fieldDescription(const QString& fieldName) const override {
        
        return QString();
    }
    
    QVariant value(const QString& fieldName) const override {
        if (fieldName == QLatin1String("enableDebugTools")) return QVariant::fromValue(enableDebugTools_);
        if (fieldName == QLatin1String("showFPS")) return QVariant::fromValue(showFPS_);
        if (fieldName == QLatin1String("logLevel")) return QVariant::fromValue(logLevel_);
        return QVariant();
    }
    
    void value(const QString& fieldName, const QVariant& value) override {
        if (fieldName == QLatin1String("enableDebugTools")) {
            enableDebugTools_ = value.value<bool>();
            return;
        }
        if (fieldName == QLatin1String("showFPS")) {
            showFPS_ = value.value<bool>();
            return;
        }
        if (fieldName == QLatin1String("logLevel")) {
            logLevel_ = value.value<QString>();
            return;
        }
    }
    
    // 特定于DebugSettings的访问器
        // enableDebugTools字段的访问器
    bool getEnableDebugTools() const {
        return enableDebugTools_;
    }
    
    void setEnableDebugTools(const bool& value) {
        enableDebugTools_ = value;
    } 

        // showFPS字段的访问器
    bool getShowFPS() const {
        return showFPS_;
    }
    
    void setShowFPS(const bool& value) {
        showFPS_ = value;
    } 

        // logLevel字段的访问器
    QString getLogLevel() const {
        return logLevel_;
    }
    
    void setLogLevel(const QString& value) {
        logLevel_ = value;
    } 
    
private:
    bool enableDebugTools_;
    bool showFPS_;
    QString logLevel_;
};


// OldAppConfig结构体

class MODEL_EXPORT OldAppConfigModel : public IModel {
public:
    OldAppConfigModel() = default;
    
    
    // 实现IModel接口
    QCborValue toCbor() const override {
        QCborMap map;
        map.insert(QLatin1String("appName"), QCborValue(getAppName()));
        map.insert(QLatin1String("version"), QCborValue(getVersion()));
        return map;
    }
    
    void fromCbor(const QCborValue& cbor) override {
        QCborMap map = cbor.toMap();
        setAppName(map.value(QLatin1String("appName")).toString());
        setVersion(map.value(QLatin1String("version")).toString());
    }
    
    QStringList fields() const override {
        return QStringList{QLatin1String("appName"), QLatin1String("version")};
    }
    
    QString fieldOriginTypeName(const QString& fieldName) const override {
        if (fieldName == QLatin1String("appName")) return QLatin1String("string");
        if (fieldName == QLatin1String("version")) return QLatin1String("string");
        return QLatin1String("");
    }
    
    QList<QSharedPointer<IAnnotation>> annotations() const override {
        
        return QList<QSharedPointer<IAnnotation>>();
    }
    
    QList<QSharedPointer<void>> fieldAnnotations(const QString& fieldName) const override {
        if (fieldName == QLatin1String("appName")) {
            return QList<QSharedPointer<void>>();
        }
        if (fieldName == QLatin1String("version")) {
            return QList<QSharedPointer<void>>();
        }
        return QList<QSharedPointer<void>>();
    }
    
    QString description() const override {
        return "Generated from struct OldAppConfig";
    }
    
    QString fieldDescription(const QString& fieldName) const override {
        
        return QString();
    }
    
    QVariant value(const QString& fieldName) const override {
        if (fieldName == QLatin1String("appName")) return QVariant::fromValue(appName_);
        if (fieldName == QLatin1String("version")) return QVariant::fromValue(version_);
        return QVariant();
    }
    
    void value(const QString& fieldName, const QVariant& value) override {
        if (fieldName == QLatin1String("appName")) {
            appName_ = value.value<QString>();
            return;
        }
        if (fieldName == QLatin1String("version")) {
            version_ = value.value<QString>();
            return;
        }
    }
    
    // 特定于OldAppConfig的访问器
        // appName字段的访问器
    QString getAppName() const {
        return appName_;
    }
    
    void setAppName(const QString& value) {
        appName_ = value;
    } 

        // version字段的访问器
    QString getVersion() const {
        return version_;
    }
    
    void setVersion(const QString& value) {
        version_ = value;
    } 
    
protected:
    QString modelName() const override {
        return "OldAppConfig";
    }
    
private:
    QString appName_;
    QString version_;
    
    // 变更通知
    void notifyChange();
};


// NewAppConfig结构体

class MODEL_EXPORT NewAppConfigModel : public IModel {
public:
    NewAppConfigModel() = default;
    
    
    // 实现IModel接口
    QCborValue toCbor() const override {
        QCborMap map;
        map.insert(QLatin1String("appName"), QCborValue(getAppName()));
        map.insert(QLatin1String("version"), QCborValue(getVersion()));
        return map;
    }
    
    void fromCbor(const QCborValue& cbor) override {
        QCborMap map = cbor.toMap();
        setAppName(map.value(QLatin1String("appName")).toString());
        setVersion(map.value(QLatin1String("version")).toString());
    }
    
    QStringList fields() const override {
        return QStringList{QLatin1String("appName"), QLatin1String("version")};
    }
    
    QString fieldOriginTypeName(const QString& fieldName) const override {
        if (fieldName == QLatin1String("appName")) return QLatin1String("string");
        if (fieldName == QLatin1String("version")) return QLatin1String("string");
        return QLatin1String("");
    }
    
    QList<QSharedPointer<IAnnotation>> annotations() const override {
        
        return QList<QSharedPointer<IAnnotation>>();
    }
    
    QList<QSharedPointer<void>> fieldAnnotations(const QString& fieldName) const override {
        if (fieldName == QLatin1String("appName")) {
            return QList<QSharedPointer<void>>();
        }
        if (fieldName == QLatin1String("version")) {
            return QList<QSharedPointer<void>>();
        }
        return QList<QSharedPointer<void>>();
    }
    
    QString description() const override {
        return "Generated from struct NewAppConfig";
    }
    
    QString fieldDescription(const QString& fieldName) const override {
        
        return QString();
    }
    
    QVariant value(const QString& fieldName) const override {
        if (fieldName == QLatin1String("appName")) return QVariant::fromValue(appName_);
        if (fieldName == QLatin1String("version")) return QVariant::fromValue(version_);
        return QVariant();
    }
    
    void value(const QString& fieldName, const QVariant& value) override {
        if (fieldName == QLatin1String("appName")) {
            appName_ = value.value<QString>();
            return;
        }
        if (fieldName == QLatin1String("version")) {
            version_ = value.value<QString>();
            return;
        }
    }
    
    // 特定于NewAppConfig的访问器
        // appName字段的访问器
    QString getAppName() const {
        return appName_;
    }
    
    void setAppName(const QString& value) {
        appName_ = value;
    } 

        // version字段的访问器
    QString getVersion() const {
        return version_;
    }
    
    void setVersion(const QString& value) {
        version_ = value;
    } 
    
protected:
    QString modelName() const override {
        return "NewAppConfig";
    }
    
private:
    QString appName_;
    QString version_;
    
    // 变更通知
    void notifyChange();
};


// StartupConfig结构体

class MODEL_EXPORT StartupConfigModel : public IModel {
public:
    StartupConfigModel() = default;
    
    
    // 实现IModel接口
    QCborValue toCbor() const override {
        QCborMap map;
        map.insert(QLatin1String("showWelcome"), QCborValue(getShowWelcome()));
        map.insert(QLatin1String("checkForUpdates"), QCborValue(getCheckForUpdates()));
        return map;
    }
    
    void fromCbor(const QCborValue& cbor) override {
        QCborMap map = cbor.toMap();
        setShowWelcome(map.value(QLatin1String("showWelcome")).toBool());
        setCheckForUpdates(map.value(QLatin1String("checkForUpdates")).toBool());
    }
    
    QStringList fields() const override {
        return QStringList{QLatin1String("showWelcome"), QLatin1String("checkForUpdates")};
    }
    
    QString fieldOriginTypeName(const QString& fieldName) const override {
        if (fieldName == QLatin1String("showWelcome")) return QLatin1String("bool");
        if (fieldName == QLatin1String("checkForUpdates")) return QLatin1String("bool");
        return QLatin1String("");
    }
    
    QList<QSharedPointer<IAnnotation>> annotations() const override {
        
        return QList<QSharedPointer<IAnnotation>>();
    }
    
    QList<QSharedPointer<void>> fieldAnnotations(const QString& fieldName) const override {
        if (fieldName == QLatin1String("showWelcome")) {
            return QList<QSharedPointer<void>>();
        }
        if (fieldName == QLatin1String("checkForUpdates")) {
            return QList<QSharedPointer<void>>();
        }
        return QList<QSharedPointer<void>>();
    }
    
    QString description() const override {
        return "Generated from struct StartupConfig";
    }
    
    QString fieldDescription(const QString& fieldName) const override {
        
        return QString();
    }
    
    QVariant value(const QString& fieldName) const override {
        if (fieldName == QLatin1String("showWelcome")) return QVariant::fromValue(showWelcome_);
        if (fieldName == QLatin1String("checkForUpdates")) return QVariant::fromValue(checkForUpdates_);
        return QVariant();
    }
    
    void value(const QString& fieldName, const QVariant& value) override {
        if (fieldName == QLatin1String("showWelcome")) {
            showWelcome_ = value.value<bool>();
            return;
        }
        if (fieldName == QLatin1String("checkForUpdates")) {
            checkForUpdates_ = value.value<bool>();
            return;
        }
    }
    
    // 特定于StartupConfig的访问器
        // showWelcome字段的访问器
    bool getShowWelcome() const {
        return showWelcome_;
    }
    
    void setShowWelcome(const bool& value) {
        showWelcome_ = value;
    } 

        // checkForUpdates字段的访问器
    bool getCheckForUpdates() const {
        return checkForUpdates_;
    }
    
    void setCheckForUpdates(const bool& value) {
        checkForUpdates_ = value;
    } 
    
protected:
    QString modelName() const override {
        return "StartupConfig";
    }
    
private:
    bool showWelcome_;
    bool checkForUpdates_;
    
    // 变更通知
    void notifyChange();
};


// AppConfig结构体

class MODEL_EXPORT AppConfigModel : public IModel {
public:
    AppConfigModel() = default;
    
    
    // 实现IModel接口
    QCborValue toCbor() const override {
        QCborMap map;
        map.insert(QLatin1String("window"), getWindow().toCbor());
        map.insert(QLatin1String("debug"), getDebug().toCbor());
        map.insert(QLatin1String("logLevel"), QCborValue(getLogLevel()));
        map.insert(QLatin1String("cameraConfig"), QCborValue(getCameraConfig()));
        return map;
    }
    
    void fromCbor(const QCborValue& cbor) override {
        QCborMap map = cbor.toMap();
        WindowSettingsBlock window;
        window.fromCbor(map.value(QLatin1String("window")));
        setWindow(window);
        DebugSettingsBlock debug;
        debug.fromCbor(map.value(QLatin1String("debug")));
        setDebug(debug);
        setLogLevel(map.value(QLatin1String("logLevel")).toString());
        setCameraConfig(map.value(QLatin1String("cameraConfig")).toString());
    }
    
    QStringList fields() const override {
        return QStringList{QLatin1String("window"), QLatin1String("debug"), QLatin1String("logLevel"), QLatin1String("cameraConfig")};
    }
    
    QString fieldOriginTypeName(const QString& fieldName) const override {
        if (fieldName == QLatin1String("window")) return QLatin1String("WindowSettings");
        if (fieldName == QLatin1String("debug")) return QLatin1String("DebugSettings");
        if (fieldName == QLatin1String("logLevel")) return QLatin1String("string");
        if (fieldName == QLatin1String("cameraConfig")) return QLatin1String("string");
        return QLatin1String("");
    }
    
    QList<QSharedPointer<IAnnotation>> annotations() const override {
        
        return QList<QSharedPointer<IAnnotation>>();
    }
    
    QList<QSharedPointer<void>> fieldAnnotations(const QString& fieldName) const override {
        if (fieldName == QLatin1String("window")) {
            return QList<QSharedPointer<void>>();
        }
        if (fieldName == QLatin1String("debug")) {
            return QList<QSharedPointer<void>>();
        }
        if (fieldName == QLatin1String("logLevel")) {
            return QList<QSharedPointer<void>>();
        }
        if (fieldName == QLatin1String("cameraConfig")) {
            return QList<QSharedPointer<void>>();
        }
        return QList<QSharedPointer<void>>();
    }
    
    QString description() const override {
        return "Generated from struct AppConfig";
    }
    
    QString fieldDescription(const QString& fieldName) const override {
        
        return QString();
    }
    
    QVariant value(const QString& fieldName) const override {
        if (fieldName == QLatin1String("window")) return QVariant::fromValue(window_);
        if (fieldName == QLatin1String("debug")) return QVariant::fromValue(debug_);
        if (fieldName == QLatin1String("logLevel")) return QVariant::fromValue(logLevel_);
        if (fieldName == QLatin1String("cameraConfig")) return QVariant::fromValue(cameraConfig_);
        return QVariant();
    }
    
    void value(const QString& fieldName, const QVariant& value) override {
        if (fieldName == QLatin1String("window")) {
            window_ = value.value<WindowSettingsBlock>();
            return;
        }
        if (fieldName == QLatin1String("debug")) {
            debug_ = value.value<DebugSettingsBlock>();
            return;
        }
        if (fieldName == QLatin1String("logLevel")) {
            logLevel_ = value.value<QString>();
            return;
        }
        if (fieldName == QLatin1String("cameraConfig")) {
            cameraConfig_ = value.value<QString>();
            return;
        }
    }
    
    // 特定于AppConfig的访问器
        // window字段的访问器
    WindowSettingsBlock getWindow() const {
        return window_;
    }
    
    void setWindow(const WindowSettingsBlock& value) {
        window_ = value;
    } 

        // debug字段的访问器
    DebugSettingsBlock getDebug() const {
        return debug_;
    }
    
    void setDebug(const DebugSettingsBlock& value) {
        debug_ = value;
    } 

        // logLevel字段的访问器
    QString getLogLevel() const {
        return logLevel_;
    }
    
    void setLogLevel(const QString& value) {
        logLevel_ = value;
    } 

        // cameraConfig字段的访问器
    QString getCameraConfig() const {
        return cameraConfig_;
    }
    
    void setCameraConfig(const QString& value) {
        cameraConfig_ = value;
    } 
    
protected:
    QString modelName() const override {
        return "AppConfig";
    }
    
private:
    WindowSettingsBlock window_;
    DebugSettingsBlock debug_;
    QString logLevel_;
    QString cameraConfig_;
    
    // 变更通知
    void notifyChange();
};



} // namespace examples::includes

