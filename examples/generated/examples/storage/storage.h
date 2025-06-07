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


namespace examples::storage {


// ThemeColor块
class MODEL_EXPORT ThemeColorBlock : public IBlock {
public:
    ThemeColorBlock() = default;
    
    
    // 实现IBlock接口
    QCborValue toCbor() const override {
        QCborMap map;
        map.insert(QLatin1String("r"), QCborValue(getR()));
        map.insert(QLatin1String("g"), QCborValue(getG()));
        map.insert(QLatin1String("b"), QCborValue(getB()));
        map.insert(QLatin1String("a"), QCborValue(getA()));
        return map;
    }
    
    void fromCbor(const QCborValue& cbor) override {
        QCborMap map = cbor.toMap();
        setR(static_cast<int32_t>(map.value(QLatin1String("r")).toInteger()));
        setG(static_cast<int32_t>(map.value(QLatin1String("g")).toInteger()));
        setB(static_cast<int32_t>(map.value(QLatin1String("b")).toInteger()));
        setA(static_cast<int32_t>(map.value(QLatin1String("a")).toInteger()));
    }
    
    QString name() const override {
        return "ThemeColor";
    }
    
    QStringList fields() const override {
        return QStringList{QLatin1String("r"), QLatin1String("g"), QLatin1String("b"), QLatin1String("a")};
    }
    
    QString fieldType(const QString& fieldName) const override {
        if (fieldName == QLatin1String("r")) return QLatin1String("int32");
        if (fieldName == QLatin1String("g")) return QLatin1String("int32");
        if (fieldName == QLatin1String("b")) return QLatin1String("int32");
        if (fieldName == QLatin1String("a")) return QLatin1String("int32");
        return QLatin1String("");
    }
    
    QList<QSharedPointer<IAnnotation>> annotations() const override {
        
        return QList<QSharedPointer<IAnnotation>>();
    }
    
    QList<QSharedPointer<void>> fieldAnnotation(const QString& fieldName) const override {
        if (fieldName == QLatin1String("r")) {
            return QList<QSharedPointer<void>>();
        }
        if (fieldName == QLatin1String("g")) {
            return QList<QSharedPointer<void>>();
        }
        if (fieldName == QLatin1String("b")) {
            return QList<QSharedPointer<void>>();
        }
        if (fieldName == QLatin1String("a")) {
            return QList<QSharedPointer<void>>();
        }
        return QList<QSharedPointer<void>>();
    }
    
    QString description() const override {
        return "Generated from block ThemeColor";
    }
    
    QString fieldDescription(const QString& fieldName) const override {
        
        return QString();
    }
    
    QVariant value(const QString& fieldName) const override {
        if (fieldName == QLatin1String("r")) return QVariant::fromValue(r_);
        if (fieldName == QLatin1String("g")) return QVariant::fromValue(g_);
        if (fieldName == QLatin1String("b")) return QVariant::fromValue(b_);
        if (fieldName == QLatin1String("a")) return QVariant::fromValue(a_);
        return QVariant();
    }
    
    void value(const QString& fieldName, const QVariant& value) override {
        if (fieldName == QLatin1String("r")) {
            r_ = value.value<int32_t>();
            return;
        }
        if (fieldName == QLatin1String("g")) {
            g_ = value.value<int32_t>();
            return;
        }
        if (fieldName == QLatin1String("b")) {
            b_ = value.value<int32_t>();
            return;
        }
        if (fieldName == QLatin1String("a")) {
            a_ = value.value<int32_t>();
            return;
        }
    }
    
    // 特定于ThemeColor的访问器
        // r字段的访问器
    int32_t getR() const {
        return r_;
    }
    
    void setR(const int32_t& value) {
        r_ = value;
    } 

        // g字段的访问器
    int32_t getG() const {
        return g_;
    }
    
    void setG(const int32_t& value) {
        g_ = value;
    } 

        // b字段的访问器
    int32_t getB() const {
        return b_;
    }
    
    void setB(const int32_t& value) {
        b_ = value;
    } 

        // a字段的访问器
    int32_t getA() const {
        return a_;
    }
    
    void setA(const int32_t& value) {
        a_ = value;
    } 
    
private:
    int32_t r_;
    int32_t g_;
    int32_t b_;
    int32_t a_;
};


// UserPreferences结构体

class MODEL_EXPORT UserPreferencesModel : public IModel {
public:
    UserPreferencesModel() = default;
    
    
    // 实现IModel接口
    QCborValue toCbor() const override {
        QCborMap map;
        map.insert(QLatin1String("username"), QCborValue(getUsername()));
        map.insert(QLatin1String("darkMode"), QCborValue(getDarkMode()));
        map.insert(QLatin1String("fontSize"), QCborValue(getFontSize()));
        map.insert(QLatin1String("primaryColor"), getPrimaryColor().toCbor());
        return map;
    }
    
    void fromCbor(const QCborValue& cbor) override {
        QCborMap map = cbor.toMap();
        setUsername(map.value(QLatin1String("username")).toString());
        setDarkMode(map.value(QLatin1String("darkMode")).toBool());
        setFontSize(static_cast<int32_t>(map.value(QLatin1String("fontSize")).toInteger()));
        ThemeColorBlock primaryColor;
        primaryColor.fromCbor(map.value(QLatin1String("primaryColor")));
        setPrimaryColor(primaryColor);
    }
    
    QStringList fields() const override {
        return QStringList{QLatin1String("username"), QLatin1String("darkMode"), QLatin1String("fontSize"), QLatin1String("primaryColor")};
    }
    
    QString fieldOriginTypeName(const QString& fieldName) const override {
        if (fieldName == QLatin1String("username")) return QLatin1String("string");
        if (fieldName == QLatin1String("darkMode")) return QLatin1String("bool");
        if (fieldName == QLatin1String("fontSize")) return QLatin1String("int32");
        if (fieldName == QLatin1String("primaryColor")) return QLatin1String("ThemeColor");
        return QLatin1String("");
    }
    
    QList<QSharedPointer<IAnnotation>> annotations() const override {
        
        return QList<QSharedPointer<IAnnotation>>();
    }
    
    QList<QSharedPointer<void>> fieldAnnotations(const QString& fieldName) const override {
        if (fieldName == QLatin1String("username")) {
            return QList<QSharedPointer<void>>();
        }
        if (fieldName == QLatin1String("darkMode")) {
            return QList<QSharedPointer<void>>();
        }
        if (fieldName == QLatin1String("fontSize")) {
            return QList<QSharedPointer<void>>();
        }
        if (fieldName == QLatin1String("primaryColor")) {
            return QList<QSharedPointer<void>>();
        }
        return QList<QSharedPointer<void>>();
    }
    
    QString description() const override {
        return "Generated from struct UserPreferences";
    }
    
    QString fieldDescription(const QString& fieldName) const override {
        
        return QString();
    }
    
    QVariant value(const QString& fieldName) const override {
        if (fieldName == QLatin1String("username")) return QVariant::fromValue(username_);
        if (fieldName == QLatin1String("darkMode")) return QVariant::fromValue(darkMode_);
        if (fieldName == QLatin1String("fontSize")) return QVariant::fromValue(fontSize_);
        if (fieldName == QLatin1String("primaryColor")) return QVariant::fromValue(primaryColor_);
        return QVariant();
    }
    
    void value(const QString& fieldName, const QVariant& value) override {
        if (fieldName == QLatin1String("username")) {
            username_ = value.value<QString>();
            return;
        }
        if (fieldName == QLatin1String("darkMode")) {
            darkMode_ = value.value<bool>();
            return;
        }
        if (fieldName == QLatin1String("fontSize")) {
            fontSize_ = value.value<int32_t>();
            return;
        }
        if (fieldName == QLatin1String("primaryColor")) {
            primaryColor_ = value.value<ThemeColorBlock>();
            return;
        }
    }
    
    // 特定于UserPreferences的访问器
        // username字段的访问器
    QString getUsername() const {
        return username_;
    }
    
    void setUsername(const QString& value) {
        username_ = value;
    } 

        // darkMode字段的访问器
    bool getDarkMode() const {
        return darkMode_;
    }
    
    void setDarkMode(const bool& value) {
        darkMode_ = value;
    } 

        // fontSize字段的访问器
    int32_t getFontSize() const {
        return fontSize_;
    }
    
    void setFontSize(const int32_t& value) {
        fontSize_ = value;
    } 

        // primaryColor字段的访问器
    ThemeColorBlock getPrimaryColor() const {
        return primaryColor_;
    }
    
    void setPrimaryColor(const ThemeColorBlock& value) {
        primaryColor_ = value;
    } 
    
protected:
    QString modelName() const override {
        return "UserPreferences";
    }
    
private:
    QString username_;
    bool darkMode_;
    int32_t fontSize_;
    ThemeColorBlock primaryColor_;
    
    // 变更通知
    void notifyChange();
};


// AppSettings结构体

class MODEL_EXPORT AppSettingsModel : public IModel {
public:
    AppSettingsModel() = default;
    
    
    // 实现IModel接口
    QCborValue toCbor() const override {
        QCborMap map;
        map.insert(QLatin1String("language"), QCborValue(getLanguage()));
        map.insert(QLatin1String("autoUpdate"), QCborValue(getAutoUpdate()));
        QCborArray recentFilesArray;
        for (const auto& item : getRecentFiles()) {
            recentFilesArray.append(QCborValue(item));
        }
        map.insert(QLatin1String("recentFiles"), recentFilesArray);
        return map;
    }
    
    void fromCbor(const QCborValue& cbor) override {
        QCborMap map = cbor.toMap();
        setLanguage(map.value(QLatin1String("language")).toString());
        setAutoUpdate(map.value(QLatin1String("autoUpdate")).toBool());
        QCborArray recentFilesArray = map.value(QLatin1String("recentFiles")).toArray();
        QVector<QString> recentFiles;
        for (const auto& itemValue : recentFilesArray) {
            recentFiles.append(static_cast<QString>(itemValue.toString()));
        }
        setRecentFiles(recentFiles);
    }
    
    QStringList fields() const override {
        return QStringList{QLatin1String("language"), QLatin1String("autoUpdate"), QLatin1String("recentFiles")};
    }
    
    QString fieldOriginTypeName(const QString& fieldName) const override {
        if (fieldName == QLatin1String("language")) return QLatin1String("string");
        if (fieldName == QLatin1String("autoUpdate")) return QLatin1String("bool");
        if (fieldName == QLatin1String("recentFiles")) return QLatin1String("repeated string");
        return QLatin1String("");
    }
    
    QList<QSharedPointer<IAnnotation>> annotations() const override {
        
        return QList<QSharedPointer<IAnnotation>>();
    }
    
    QList<QSharedPointer<void>> fieldAnnotations(const QString& fieldName) const override {
        if (fieldName == QLatin1String("language")) {
            return QList<QSharedPointer<void>>();
        }
        if (fieldName == QLatin1String("autoUpdate")) {
            return QList<QSharedPointer<void>>();
        }
        if (fieldName == QLatin1String("recentFiles")) {
            return QList<QSharedPointer<void>>();
        }
        return QList<QSharedPointer<void>>();
    }
    
    QString description() const override {
        return "Generated from struct AppSettings";
    }
    
    QString fieldDescription(const QString& fieldName) const override {
        
        return QString();
    }
    
    QVariant value(const QString& fieldName) const override {
        if (fieldName == QLatin1String("language")) return QVariant::fromValue(language_);
        if (fieldName == QLatin1String("autoUpdate")) return QVariant::fromValue(autoUpdate_);
        if (fieldName == QLatin1String("recentFiles")) return QVariant::fromValue(recentFiles_);
        return QVariant();
    }
    
    void value(const QString& fieldName, const QVariant& value) override {
        if (fieldName == QLatin1String("language")) {
            language_ = value.value<QString>();
            return;
        }
        if (fieldName == QLatin1String("autoUpdate")) {
            autoUpdate_ = value.value<bool>();
            return;
        }
        if (fieldName == QLatin1String("recentFiles")) {
            recentFiles_ = value.value<QVector<QString>>();
            return;
        }
    }
    
    // 特定于AppSettings的访问器
        // language字段的访问器
    QString getLanguage() const {
        return language_;
    }
    
    void setLanguage(const QString& value) {
        language_ = value;
    } 

        // autoUpdate字段的访问器
    bool getAutoUpdate() const {
        return autoUpdate_;
    }
    
    void setAutoUpdate(const bool& value) {
        autoUpdate_ = value;
    } 

        // recentFiles字段的访问器
    QVector<QString> getRecentFiles() const {
        return recentFiles_;
    }
    
    void setRecentFiles(const QVector<QString>& value) {
        recentFiles_ = value;
    } 
    
protected:
    QString modelName() const override {
        return "AppSettings";
    }
    
private:
    QString language_;
    bool autoUpdate_;
    QVector<QString> recentFiles_;
    
    // 变更通知
    void notifyChange();
};



} // namespace examples::storage

