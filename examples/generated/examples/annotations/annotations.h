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


namespace examples::annotations {


// AppConfig结构体

class MODEL_EXPORT AppConfigModel : public IModel {
public:
    AppConfigModel() = default;
    
    
    // 实现IModel接口
    QCborValue toCbor() const override {
        QCborMap map;
        map.insert(QLatin1String("appName"), QCborValue(getAppName()));
        map.insert(QLatin1String("maxConnections"), QCborValue(getMaxConnections()));
        map.insert(QLatin1String("enableLogging"), QCborValue(getEnableLogging()));
        map.insert(QLatin1String("logLevel"), QCborValue(getLogLevel()));
        return map;
    }
    
    void fromCbor(const QCborValue& cbor) override {
        QCborMap map = cbor.toMap();
        setAppName(map.value(QLatin1String("appName")).toString());
        setMaxConnections(static_cast<int32_t>(map.value(QLatin1String("maxConnections")).toInteger()));
        setEnableLogging(map.value(QLatin1String("enableLogging")).toBool());
        setLogLevel(map.value(QLatin1String("logLevel")).toString());
    }
    
    QStringList fields() const override {
        return QStringList{QLatin1String("appName"), QLatin1String("maxConnections"), QLatin1String("enableLogging"), QLatin1String("logLevel")};
    }
    
    QString fieldOriginTypeName(const QString& fieldName) const override {
        if (fieldName == QLatin1String("appName")) return QLatin1String("string");
        if (fieldName == QLatin1String("maxConnections")) return QLatin1String("int32");
        if (fieldName == QLatin1String("enableLogging")) return QLatin1String("bool");
        if (fieldName == QLatin1String("logLevel")) return QLatin1String("string");
        return QLatin1String("");
    }
    
    QList<QSharedPointer<IAnnotation>> annotations() const override {
        
        return QList<QSharedPointer<IAnnotation>>();
    }
    
    QList<QSharedPointer<void>> fieldAnnotations(const QString& fieldName) const override {
        if (fieldName == QLatin1String("appName")) {
            return QList<QSharedPointer<void>>();
        }
        if (fieldName == QLatin1String("maxConnections")) {
            return QList<QSharedPointer<void>>();
        }
        if (fieldName == QLatin1String("enableLogging")) {
            return QList<QSharedPointer<void>>();
        }
        if (fieldName == QLatin1String("logLevel")) {
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
        if (fieldName == QLatin1String("appName")) return QVariant::fromValue(appName_);
        if (fieldName == QLatin1String("maxConnections")) return QVariant::fromValue(maxConnections_);
        if (fieldName == QLatin1String("enableLogging")) return QVariant::fromValue(enableLogging_);
        if (fieldName == QLatin1String("logLevel")) return QVariant::fromValue(logLevel_);
        return QVariant();
    }
    
    void value(const QString& fieldName, const QVariant& value) override {
        if (fieldName == QLatin1String("appName")) {
            appName_ = value.value<QString>();
            return;
        }
        if (fieldName == QLatin1String("maxConnections")) {
            maxConnections_ = value.value<int32_t>();
            return;
        }
        if (fieldName == QLatin1String("enableLogging")) {
            enableLogging_ = value.value<bool>();
            return;
        }
        if (fieldName == QLatin1String("logLevel")) {
            logLevel_ = value.value<QString>();
            return;
        }
    }
    
    // 特定于AppConfig的访问器
        // appName字段的访问器
    QString getAppName() const {
        return appName_;
    }
    
    void setAppName(const QString& value) {
        appName_ = value;
    } 

        // maxConnections字段的访问器
    int32_t getMaxConnections() const {
        return maxConnections_;
    }
    
    void setMaxConnections(const int32_t& value) {
        maxConnections_ = value;
    } 

        // enableLogging字段的访问器
    bool getEnableLogging() const {
        return enableLogging_;
    }
    
    void setEnableLogging(const bool& value) {
        enableLogging_ = value;
    } 

        // logLevel字段的访问器
    QString getLogLevel() const {
        return logLevel_;
    }
    
    void setLogLevel(const QString& value) {
        logLevel_ = value;
    } 
    
protected:
    QString modelName() const override {
        return "AppConfig";
    }
    
private:
    QString appName_;
    int32_t maxConnections_;
    bool enableLogging_;
    QString logLevel_;
    
    // 变更通知
    void notifyChange();
};


// DisplayConfig结构体

class MODEL_EXPORT DisplayConfigModel : public IModel {
public:
    DisplayConfigModel() = default;
    
    
    // 实现IModel接口
    QCborValue toCbor() const override {
        QCborMap map;
        map.insert(QLatin1String("uiScale"), QCborValue(getUiScale()));
        map.insert(QLatin1String("theme"), QCborValue(getTheme()));
        return map;
    }
    
    void fromCbor(const QCborValue& cbor) override {
        QCborMap map = cbor.toMap();
        setUiScale(static_cast<int32_t>(map.value(QLatin1String("uiScale")).toInteger()));
        setTheme(map.value(QLatin1String("theme")).toString());
    }
    
    QStringList fields() const override {
        return QStringList{QLatin1String("uiScale"), QLatin1String("theme")};
    }
    
    QString fieldOriginTypeName(const QString& fieldName) const override {
        if (fieldName == QLatin1String("uiScale")) return QLatin1String("int32");
        if (fieldName == QLatin1String("theme")) return QLatin1String("string");
        return QLatin1String("");
    }
    
    QList<QSharedPointer<IAnnotation>> annotations() const override {
        
        return QList<QSharedPointer<IAnnotation>>();
    }
    
    QList<QSharedPointer<void>> fieldAnnotations(const QString& fieldName) const override {
        if (fieldName == QLatin1String("uiScale")) {
            return QList<QSharedPointer<void>>();
        }
        if (fieldName == QLatin1String("theme")) {
            return QList<QSharedPointer<void>>();
        }
        return QList<QSharedPointer<void>>();
    }
    
    QString description() const override {
        return "Generated from struct DisplayConfig";
    }
    
    QString fieldDescription(const QString& fieldName) const override {
        
        return QString();
    }
    
    QVariant value(const QString& fieldName) const override {
        if (fieldName == QLatin1String("uiScale")) return QVariant::fromValue(uiScale_);
        if (fieldName == QLatin1String("theme")) return QVariant::fromValue(theme_);
        return QVariant();
    }
    
    void value(const QString& fieldName, const QVariant& value) override {
        if (fieldName == QLatin1String("uiScale")) {
            uiScale_ = value.value<int32_t>();
            return;
        }
        if (fieldName == QLatin1String("theme")) {
            theme_ = value.value<QString>();
            return;
        }
    }
    
    // 特定于DisplayConfig的访问器
        // uiScale字段的访问器
    int32_t getUiScale() const {
        return uiScale_;
    }
    
    void setUiScale(const int32_t& value) {
        uiScale_ = value;
    } 

        // theme字段的访问器
    QString getTheme() const {
        return theme_;
    }
    
    void setTheme(const QString& value) {
        theme_ = value;
    } 
    
protected:
    QString modelName() const override {
        return "DisplayConfig";
    }
    
private:
    int32_t uiScale_;
    QString theme_;
    
    // 变更通知
    void notifyChange();
};


// NetworkConfig结构体

class MODEL_EXPORT NetworkConfigModel : public IModel {
public:
    NetworkConfigModel() = default;
    
    
    // 实现IModel接口
    QCborValue toCbor() const override {
        QCborMap map;
        map.insert(QLatin1String("apiEndpoint"), QCborValue(getApiEndpoint()));
        map.insert(QLatin1String("requestTimeout"), QCborValue(getRequestTimeout()));
        return map;
    }
    
    void fromCbor(const QCborValue& cbor) override {
        QCborMap map = cbor.toMap();
        setApiEndpoint(map.value(QLatin1String("apiEndpoint")).toString());
        setRequestTimeout(static_cast<int32_t>(map.value(QLatin1String("requestTimeout")).toInteger()));
    }
    
    QStringList fields() const override {
        return QStringList{QLatin1String("apiEndpoint"), QLatin1String("requestTimeout")};
    }
    
    QString fieldOriginTypeName(const QString& fieldName) const override {
        if (fieldName == QLatin1String("apiEndpoint")) return QLatin1String("string");
        if (fieldName == QLatin1String("requestTimeout")) return QLatin1String("int32");
        return QLatin1String("");
    }
    
    QList<QSharedPointer<IAnnotation>> annotations() const override {
        
        return QList<QSharedPointer<IAnnotation>>();
    }
    
    QList<QSharedPointer<void>> fieldAnnotations(const QString& fieldName) const override {
        if (fieldName == QLatin1String("apiEndpoint")) {
            return QList<QSharedPointer<void>>();
        }
        if (fieldName == QLatin1String("requestTimeout")) {
            return QList<QSharedPointer<void>>();
        }
        return QList<QSharedPointer<void>>();
    }
    
    QString description() const override {
        return "Generated from struct NetworkConfig";
    }
    
    QString fieldDescription(const QString& fieldName) const override {
        
        return QString();
    }
    
    QVariant value(const QString& fieldName) const override {
        if (fieldName == QLatin1String("apiEndpoint")) return QVariant::fromValue(apiEndpoint_);
        if (fieldName == QLatin1String("requestTimeout")) return QVariant::fromValue(requestTimeout_);
        return QVariant();
    }
    
    void value(const QString& fieldName, const QVariant& value) override {
        if (fieldName == QLatin1String("apiEndpoint")) {
            apiEndpoint_ = value.value<QString>();
            return;
        }
        if (fieldName == QLatin1String("requestTimeout")) {
            requestTimeout_ = value.value<int32_t>();
            return;
        }
    }
    
    // 特定于NetworkConfig的访问器
        // apiEndpoint字段的访问器
    QString getApiEndpoint() const {
        return apiEndpoint_;
    }
    
    void setApiEndpoint(const QString& value) {
        apiEndpoint_ = value;
    } 

        // requestTimeout字段的访问器
    int32_t getRequestTimeout() const {
        return requestTimeout_;
    }
    
    void setRequestTimeout(const int32_t& value) {
        requestTimeout_ = value;
    } 
    
protected:
    QString modelName() const override {
        return "NetworkConfig";
    }
    
private:
    QString apiEndpoint_;
    int32_t requestTimeout_;
    
    // 变更通知
    void notifyChange();
};



} // namespace examples::annotations

