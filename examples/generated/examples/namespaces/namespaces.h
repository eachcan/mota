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


namespace examples::namespaces {


// BasicConfig块
class MODEL_EXPORT BasicConfigBlock : public IBlock {
public:
    BasicConfigBlock() = default;
    
    
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
        setVersion(static_cast<int32_t>(map.value(QLatin1String("version")).toInteger()));
    }
    
    QString name() const override {
        return "BasicConfig";
    }
    
    QStringList fields() const override {
        return QStringList{QLatin1String("name"), QLatin1String("version")};
    }
    
    QString fieldType(const QString& fieldName) const override {
        if (fieldName == QLatin1String("name")) return QLatin1String("string");
        if (fieldName == QLatin1String("version")) return QLatin1String("int32");
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
        return "Generated from block BasicConfig";
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
            version_ = value.value<int32_t>();
            return;
        }
    }
    
    // 特定于BasicConfig的访问器
        // name字段的访问器
    QString getName() const {
        return name_;
    }
    
    void setName(const QString& value) {
        name_ = value;
    } 

        // version字段的访问器
    int32_t getVersion() const {
        return version_;
    }
    
    void setVersion(const int32_t& value) {
        version_ = value;
    } 
    
private:
    QString name_;
    int32_t version_;
};


// AdvancedSettings块
class MODEL_EXPORT AdvancedSettingsBlock : public IBlock {
public:
    AdvancedSettingsBlock() = default;
    
    
    // 实现IBlock接口
    QCborValue toCbor() const override {
        QCborMap map;
        map.insert(QLatin1String("enableAdvancedFeatures"), QCborValue(getEnableAdvancedFeatures()));
        map.insert(QLatin1String("precision"), QCborValue(getPrecision()));
        return map;
    }
    
    void fromCbor(const QCborValue& cbor) override {
        QCborMap map = cbor.toMap();
        setEnableAdvancedFeatures(map.value(QLatin1String("enableAdvancedFeatures")).toBool());
        setPrecision(static_cast<double>(map.value(QLatin1String("precision")).toDouble()));
    }
    
    QString name() const override {
        return "AdvancedSettings";
    }
    
    QStringList fields() const override {
        return QStringList{QLatin1String("enableAdvancedFeatures"), QLatin1String("precision")};
    }
    
    QString fieldType(const QString& fieldName) const override {
        if (fieldName == QLatin1String("enableAdvancedFeatures")) return QLatin1String("bool");
        if (fieldName == QLatin1String("precision")) return QLatin1String("float64");
        return QLatin1String("");
    }
    
    QList<QSharedPointer<IAnnotation>> annotations() const override {
        
        return QList<QSharedPointer<IAnnotation>>();
    }
    
    QList<QSharedPointer<void>> fieldAnnotation(const QString& fieldName) const override {
        if (fieldName == QLatin1String("enableAdvancedFeatures")) {
            return QList<QSharedPointer<void>>();
        }
        if (fieldName == QLatin1String("precision")) {
            return QList<QSharedPointer<void>>();
        }
        return QList<QSharedPointer<void>>();
    }
    
    QString description() const override {
        return "Generated from block AdvancedSettings";
    }
    
    QString fieldDescription(const QString& fieldName) const override {
        
        return QString();
    }
    
    QVariant value(const QString& fieldName) const override {
        if (fieldName == QLatin1String("enableAdvancedFeatures")) return QVariant::fromValue(enableAdvancedFeatures_);
        if (fieldName == QLatin1String("precision")) return QVariant::fromValue(precision_);
        return QVariant();
    }
    
    void value(const QString& fieldName, const QVariant& value) override {
        if (fieldName == QLatin1String("enableAdvancedFeatures")) {
            enableAdvancedFeatures_ = value.value<bool>();
            return;
        }
        if (fieldName == QLatin1String("precision")) {
            precision_ = value.value<double>();
            return;
        }
    }
    
    // 特定于AdvancedSettings的访问器
        // enableAdvancedFeatures字段的访问器
    bool getEnableAdvancedFeatures() const {
        return enableAdvancedFeatures_;
    }
    
    void setEnableAdvancedFeatures(const bool& value) {
        enableAdvancedFeatures_ = value;
    } 

        // precision字段的访问器
    double getPrecision() const {
        return precision_;
    }
    
    void setPrecision(const double& value) {
        precision_ = value;
    } 
    
private:
    bool enableAdvancedFeatures_;
    double precision_;
};


// AdvancedConfig结构体

class MODEL_EXPORT AdvancedConfigModel : public IModel {
public:
    AdvancedConfigModel() = default;
    
    
    // 实现IModel接口
    QCborValue toCbor() const override {
        QCborMap map;
        map.insert(QLatin1String("basicConfig"), getBasicConfig().toCbor());
        map.insert(QLatin1String("settings"), getSettings().toCbor());
        map.insert(QLatin1String("configName"), QCborValue(getConfigName()));
        return map;
    }
    
    void fromCbor(const QCborValue& cbor) override {
        QCborMap map = cbor.toMap();
        BasicConfigBlock basicConfig;
        basicConfig.fromCbor(map.value(QLatin1String("basicConfig")));
        setBasicConfig(basicConfig);
        AdvancedSettingsBlock settings;
        settings.fromCbor(map.value(QLatin1String("settings")));
        setSettings(settings);
        setConfigName(map.value(QLatin1String("configName")).toString());
    }
    
    QStringList fields() const override {
        return QStringList{QLatin1String("basicConfig"), QLatin1String("settings"), QLatin1String("configName")};
    }
    
    QString fieldOriginTypeName(const QString& fieldName) const override {
        if (fieldName == QLatin1String("basicConfig")) return QLatin1String("BasicConfig");
        if (fieldName == QLatin1String("settings")) return QLatin1String("AdvancedSettings");
        if (fieldName == QLatin1String("configName")) return QLatin1String("string");
        return QLatin1String("");
    }
    
    QList<QSharedPointer<IAnnotation>> annotations() const override {
        
        return QList<QSharedPointer<IAnnotation>>();
    }
    
    QList<QSharedPointer<void>> fieldAnnotations(const QString& fieldName) const override {
        if (fieldName == QLatin1String("basicConfig")) {
            return QList<QSharedPointer<void>>();
        }
        if (fieldName == QLatin1String("settings")) {
            return QList<QSharedPointer<void>>();
        }
        if (fieldName == QLatin1String("configName")) {
            return QList<QSharedPointer<void>>();
        }
        return QList<QSharedPointer<void>>();
    }
    
    QString description() const override {
        return "Generated from struct AdvancedConfig";
    }
    
    QString fieldDescription(const QString& fieldName) const override {
        
        return QString();
    }
    
    QVariant value(const QString& fieldName) const override {
        if (fieldName == QLatin1String("basicConfig")) return QVariant::fromValue(basicConfig_);
        if (fieldName == QLatin1String("settings")) return QVariant::fromValue(settings_);
        if (fieldName == QLatin1String("configName")) return QVariant::fromValue(configName_);
        return QVariant();
    }
    
    void value(const QString& fieldName, const QVariant& value) override {
        if (fieldName == QLatin1String("basicConfig")) {
            basicConfig_ = value.value<BasicConfigBlock>();
            return;
        }
        if (fieldName == QLatin1String("settings")) {
            settings_ = value.value<AdvancedSettingsBlock>();
            return;
        }
        if (fieldName == QLatin1String("configName")) {
            configName_ = value.value<QString>();
            return;
        }
    }
    
    // 特定于AdvancedConfig的访问器
        // basicConfig字段的访问器
    BasicConfigBlock getBasicConfig() const {
        return basicConfig_;
    }
    
    void setBasicConfig(const BasicConfigBlock& value) {
        basicConfig_ = value;
    } 

        // settings字段的访问器
    AdvancedSettingsBlock getSettings() const {
        return settings_;
    }
    
    void setSettings(const AdvancedSettingsBlock& value) {
        settings_ = value;
    } 

        // configName字段的访问器
    QString getConfigName() const {
        return configName_;
    }
    
    void setConfigName(const QString& value) {
        configName_ = value;
    } 
    
protected:
    QString modelName() const override {
        return "AdvancedConfig";
    }
    
private:
    BasicConfigBlock basicConfig_;
    AdvancedSettingsBlock settings_;
    QString configName_;
    
    // 变更通知
    void notifyChange();
};


// SystemConfig结构体

class MODEL_EXPORT SystemConfigModel : public IModel {
public:
    SystemConfigModel() = default;
    
    
    // 实现IModel接口
    QCborValue toCbor() const override {
        QCborMap map;
        map.insert(QLatin1String("basic"), getBasic().toCbor());
        map.insert(QLatin1String("advanced"), getAdvanced().toCbor());
        map.insert(QLatin1String("systemId"), QCborValue(getSystemId()));
        return map;
    }
    
    void fromCbor(const QCborValue& cbor) override {
        QCborMap map = cbor.toMap();
        BasicConfigBlock basic;
        basic.fromCbor(map.value(QLatin1String("basic")));
        setBasic(basic);
        AdvancedSettingsBlock advanced;
        advanced.fromCbor(map.value(QLatin1String("advanced")));
        setAdvanced(advanced);
        setSystemId(map.value(QLatin1String("systemId")).toString());
    }
    
    QStringList fields() const override {
        return QStringList{QLatin1String("basic"), QLatin1String("advanced"), QLatin1String("systemId")};
    }
    
    QString fieldOriginTypeName(const QString& fieldName) const override {
        if (fieldName == QLatin1String("basic")) return QLatin1String("BasicConfig");
        if (fieldName == QLatin1String("advanced")) return QLatin1String("AdvancedSettings");
        if (fieldName == QLatin1String("systemId")) return QLatin1String("string");
        return QLatin1String("");
    }
    
    QList<QSharedPointer<IAnnotation>> annotations() const override {
        
        return QList<QSharedPointer<IAnnotation>>();
    }
    
    QList<QSharedPointer<void>> fieldAnnotations(const QString& fieldName) const override {
        if (fieldName == QLatin1String("basic")) {
            return QList<QSharedPointer<void>>();
        }
        if (fieldName == QLatin1String("advanced")) {
            return QList<QSharedPointer<void>>();
        }
        if (fieldName == QLatin1String("systemId")) {
            return QList<QSharedPointer<void>>();
        }
        return QList<QSharedPointer<void>>();
    }
    
    QString description() const override {
        return "Generated from struct SystemConfig";
    }
    
    QString fieldDescription(const QString& fieldName) const override {
        
        return QString();
    }
    
    QVariant value(const QString& fieldName) const override {
        if (fieldName == QLatin1String("basic")) return QVariant::fromValue(basic_);
        if (fieldName == QLatin1String("advanced")) return QVariant::fromValue(advanced_);
        if (fieldName == QLatin1String("systemId")) return QVariant::fromValue(systemId_);
        return QVariant();
    }
    
    void value(const QString& fieldName, const QVariant& value) override {
        if (fieldName == QLatin1String("basic")) {
            basic_ = value.value<BasicConfigBlock>();
            return;
        }
        if (fieldName == QLatin1String("advanced")) {
            advanced_ = value.value<AdvancedSettingsBlock>();
            return;
        }
        if (fieldName == QLatin1String("systemId")) {
            systemId_ = value.value<QString>();
            return;
        }
    }
    
    // 特定于SystemConfig的访问器
        // basic字段的访问器
    BasicConfigBlock getBasic() const {
        return basic_;
    }
    
    void setBasic(const BasicConfigBlock& value) {
        basic_ = value;
    } 

        // advanced字段的访问器
    AdvancedSettingsBlock getAdvanced() const {
        return advanced_;
    }
    
    void setAdvanced(const AdvancedSettingsBlock& value) {
        advanced_ = value;
    } 

        // systemId字段的访问器
    QString getSystemId() const {
        return systemId_;
    }
    
    void setSystemId(const QString& value) {
        systemId_ = value;
    } 
    
protected:
    QString modelName() const override {
        return "SystemConfig";
    }
    
private:
    BasicConfigBlock basic_;
    AdvancedSettingsBlock advanced_;
    QString systemId_;
    
    // 变更通知
    void notifyChange();
};



} // namespace examples::namespaces

