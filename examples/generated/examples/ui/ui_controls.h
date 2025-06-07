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


namespace examples::ui {


// Gender枚举
enum class Gender {
    MALE = 0,
    FEMALE = 1,
    OTHER = 2
};

// Gender辅助函数
namespace GenderHelper {
    // 将枚举值转换为字符串
    inline QString toString(Gender value) {
        switch (value) {
            case Gender::MALE:
                return QLatin1String("MALE");
            case Gender::FEMALE:
                return QLatin1String("FEMALE");
            case Gender::OTHER:
                return QLatin1String("OTHER");
            default:
                return QString();
        }
    }
    
    // 将字符串转换为枚举值
    inline Gender fromString(const QString& str) {
        if (str == QLatin1String("MALE")) {
            return Gender::MALE;
        } else if (str == QLatin1String("FEMALE")) {
            return Gender::FEMALE;
        } else if (str == QLatin1String("OTHER")) {
            return Gender::OTHER;
        }
        return Gender::MALE;
    }
    
    // 获取所有枚举值的字符串表示
    inline QStringList allValues() {
        return QStringList() << QLatin1String("MALE") << QLatin1String("FEMALE") << QLatin1String("OTHER");
    }
    
    // 获取所有枚举值的UI显示名称
    inline QStringList allDisplayNames() {
        return QStringList() << QLatin1String("男") << QLatin1String("女") << QLatin1String("其他");
    }
    
    // 获取整个枚举的注解
    inline QList<QSharedPointer<IAnnotation>> annotations() {
                QList<QSharedPointer<IAnnotation>> result;
                return result;
    }
    
    // 获取特定枚举值的注解
    inline QList<QSharedPointer<IAnnotation>> valueAnnotations(Gender value) {
        switch (value) {
            case Gender::MALE: {
                QList<QSharedPointer<IAnnotation>> result;
                // TODO: 创建 yima.EnumValue 注解实例
                return result;
            }
            case Gender::FEMALE: {
                QList<QSharedPointer<IAnnotation>> result;
                // TODO: 创建 yima.EnumValue 注解实例
                return result;
            }
            case Gender::OTHER: {
                QList<QSharedPointer<IAnnotation>> result;
                // TODO: 创建 yima.EnumValue 注解实例
                return result;
            }
            default:
                return QList<QSharedPointer<IAnnotation>>();
        }
    }
    
    // 获取特定枚举值的注解（通过字符串）
    inline QList<QSharedPointer<IAnnotation>> valueAnnotations(const QString& valueName) {
        if (valueName == "MALE") {
                QList<QSharedPointer<IAnnotation>> result;
                // TODO: 创建 yima.EnumValue 注解实例
                return result;
        } else if (valueName == "FEMALE") {
                QList<QSharedPointer<IAnnotation>> result;
                // TODO: 创建 yima.EnumValue 注解实例
                return result;
        } else if (valueName == "OTHER") {
                QList<QSharedPointer<IAnnotation>> result;
                // TODO: 创建 yima.EnumValue 注解实例
                return result;
        }
        return QList<QSharedPointer<IAnnotation>>();
    }
}


// Country枚举
enum class Country {
    CHINA = 0,
    USA = 1,
    JAPAN = 2,
    EUROPE = 3
};

// Country辅助函数
namespace CountryHelper {
    // 将枚举值转换为字符串
    inline QString toString(Country value) {
        switch (value) {
            case Country::CHINA:
                return QLatin1String("CHINA");
            case Country::USA:
                return QLatin1String("USA");
            case Country::JAPAN:
                return QLatin1String("JAPAN");
            case Country::EUROPE:
                return QLatin1String("EUROPE");
            default:
                return QString();
        }
    }
    
    // 将字符串转换为枚举值
    inline Country fromString(const QString& str) {
        if (str == QLatin1String("CHINA")) {
            return Country::CHINA;
        } else if (str == QLatin1String("USA")) {
            return Country::USA;
        } else if (str == QLatin1String("JAPAN")) {
            return Country::JAPAN;
        } else if (str == QLatin1String("EUROPE")) {
            return Country::EUROPE;
        }
        return Country::CHINA;
    }
    
    // 获取所有枚举值的字符串表示
    inline QStringList allValues() {
        return QStringList() << QLatin1String("CHINA") << QLatin1String("USA") << QLatin1String("JAPAN") << QLatin1String("EUROPE");
    }
    
    // 获取所有枚举值的UI显示名称
    inline QStringList allDisplayNames() {
        return QStringList() << QLatin1String("中国") << QLatin1String("美国") << QLatin1String("日本") << QLatin1String("欧洲");
    }
    
    // 获取整个枚举的注解
    inline QList<QSharedPointer<IAnnotation>> annotations() {
                QList<QSharedPointer<IAnnotation>> result;
                return result;
    }
    
    // 获取特定枚举值的注解
    inline QList<QSharedPointer<IAnnotation>> valueAnnotations(Country value) {
        switch (value) {
            case Country::CHINA: {
                QList<QSharedPointer<IAnnotation>> result;
                // TODO: 创建 yima.EnumValue 注解实例
                return result;
            }
            case Country::USA: {
                QList<QSharedPointer<IAnnotation>> result;
                // TODO: 创建 yima.EnumValue 注解实例
                return result;
            }
            case Country::JAPAN: {
                QList<QSharedPointer<IAnnotation>> result;
                // TODO: 创建 yima.EnumValue 注解实例
                return result;
            }
            case Country::EUROPE: {
                QList<QSharedPointer<IAnnotation>> result;
                // TODO: 创建 yima.EnumValue 注解实例
                return result;
            }
            default:
                return QList<QSharedPointer<IAnnotation>>();
        }
    }
    
    // 获取特定枚举值的注解（通过字符串）
    inline QList<QSharedPointer<IAnnotation>> valueAnnotations(const QString& valueName) {
        if (valueName == "CHINA") {
                QList<QSharedPointer<IAnnotation>> result;
                // TODO: 创建 yima.EnumValue 注解实例
                return result;
        } else if (valueName == "USA") {
                QList<QSharedPointer<IAnnotation>> result;
                // TODO: 创建 yima.EnumValue 注解实例
                return result;
        } else if (valueName == "JAPAN") {
                QList<QSharedPointer<IAnnotation>> result;
                // TODO: 创建 yima.EnumValue 注解实例
                return result;
        } else if (valueName == "EUROPE") {
                QList<QSharedPointer<IAnnotation>> result;
                // TODO: 创建 yima.EnumValue 注解实例
                return result;
        }
        return QList<QSharedPointer<IAnnotation>>();
    }
}


// RegistrationForm结构体

class MODEL_EXPORT RegistrationFormModel : public IModel {
public:
    RegistrationFormModel() = default;
    
    
    // 实现IModel接口
    QCborValue toCbor() const override {
        QCborMap map;
        map.insert(QLatin1String("username"), QCborValue(getUsername()));
        map.insert(QLatin1String("password"), QCborValue(getPassword()));
        map.insert(QLatin1String("age"), QCborValue(getAge()));
        map.insert(QLatin1String("volume"), QCborValue(getVolume()));
        map.insert(QLatin1String("country"), QCborValue(static_cast<int>(getCountry())));
        map.insert(QLatin1String("subscribe"), QCborValue(getSubscribe()));
        map.insert(QLatin1String("gender"), QCborValue(static_cast<int>(getGender())));
        map.insert(QLatin1String("birthDate"), QCborValue(getBirthDate()));
        map.insert(QLatin1String("reminderTime"), QCborValue(getReminderTime()));
        map.insert(QLatin1String("themeColor"), QCborValue(getThemeColor()));
        map.insert(QLatin1String("avatar"), QCborValue(getAvatar()));
        map.insert(QLatin1String("notificationsEnabled"), QCborValue(getNotificationsEnabled()));
        return map;
    }
    
    void fromCbor(const QCborValue& cbor) override {
        QCborMap map = cbor.toMap();
        setUsername(map.value(QLatin1String("username")).toString());
        setPassword(map.value(QLatin1String("password")).toString());
        setAge(static_cast<int32_t>(map.value(QLatin1String("age")).toInteger()));
        setVolume(static_cast<int32_t>(map.value(QLatin1String("volume")).toInteger()));
        setCountry(static_cast<Country>(map.value(QLatin1String("country")).toInteger()));
        setSubscribe(map.value(QLatin1String("subscribe")).toBool());
        setGender(static_cast<Gender>(map.value(QLatin1String("gender")).toInteger()));
        setBirthDate(map.value(QLatin1String("birthDate")).toString());
        setReminderTime(map.value(QLatin1String("reminderTime")).toString());
        setThemeColor(map.value(QLatin1String("themeColor")).toString());
        setAvatar(map.value(QLatin1String("avatar")).toString());
        setNotificationsEnabled(map.value(QLatin1String("notificationsEnabled")).toBool());
    }
    
    QStringList fields() const override {
        return QStringList{QLatin1String("username"), QLatin1String("password"), QLatin1String("age"), QLatin1String("volume"), QLatin1String("country"), QLatin1String("subscribe"), QLatin1String("gender"), QLatin1String("birthDate"), QLatin1String("reminderTime"), QLatin1String("themeColor"), QLatin1String("avatar"), QLatin1String("notificationsEnabled")};
    }
    
    QString fieldOriginTypeName(const QString& fieldName) const override {
        if (fieldName == QLatin1String("username")) return QLatin1String("string");
        if (fieldName == QLatin1String("password")) return QLatin1String("string");
        if (fieldName == QLatin1String("age")) return QLatin1String("int32");
        if (fieldName == QLatin1String("volume")) return QLatin1String("int32");
        if (fieldName == QLatin1String("country")) return QLatin1String("Country");
        if (fieldName == QLatin1String("subscribe")) return QLatin1String("bool");
        if (fieldName == QLatin1String("gender")) return QLatin1String("Gender");
        if (fieldName == QLatin1String("birthDate")) return QLatin1String("string");
        if (fieldName == QLatin1String("reminderTime")) return QLatin1String("string");
        if (fieldName == QLatin1String("themeColor")) return QLatin1String("string");
        if (fieldName == QLatin1String("avatar")) return QLatin1String("string");
        if (fieldName == QLatin1String("notificationsEnabled")) return QLatin1String("bool");
        return QLatin1String("");
    }
    
    QList<QSharedPointer<IAnnotation>> annotations() const override {
        
        return QList<QSharedPointer<IAnnotation>>();
    }
    
    QList<QSharedPointer<void>> fieldAnnotations(const QString& fieldName) const override {
        if (fieldName == QLatin1String("username")) {
            return QList<QSharedPointer<void>>();
        }
        if (fieldName == QLatin1String("password")) {
            return QList<QSharedPointer<void>>();
        }
        if (fieldName == QLatin1String("age")) {
            return QList<QSharedPointer<void>>();
        }
        if (fieldName == QLatin1String("volume")) {
            return QList<QSharedPointer<void>>();
        }
        if (fieldName == QLatin1String("country")) {
            return QList<QSharedPointer<void>>();
        }
        if (fieldName == QLatin1String("subscribe")) {
            return QList<QSharedPointer<void>>();
        }
        if (fieldName == QLatin1String("gender")) {
            return QList<QSharedPointer<void>>();
        }
        if (fieldName == QLatin1String("birthDate")) {
            return QList<QSharedPointer<void>>();
        }
        if (fieldName == QLatin1String("reminderTime")) {
            return QList<QSharedPointer<void>>();
        }
        if (fieldName == QLatin1String("themeColor")) {
            return QList<QSharedPointer<void>>();
        }
        if (fieldName == QLatin1String("avatar")) {
            return QList<QSharedPointer<void>>();
        }
        if (fieldName == QLatin1String("notificationsEnabled")) {
            return QList<QSharedPointer<void>>();
        }
        return QList<QSharedPointer<void>>();
    }
    
    QString description() const override {
        return "Generated from struct RegistrationForm";
    }
    
    QString fieldDescription(const QString& fieldName) const override {
        
        return QString();
    }
    
    QVariant value(const QString& fieldName) const override {
        if (fieldName == QLatin1String("username")) return QVariant::fromValue(username_);
        if (fieldName == QLatin1String("password")) return QVariant::fromValue(password_);
        if (fieldName == QLatin1String("age")) return QVariant::fromValue(age_);
        if (fieldName == QLatin1String("volume")) return QVariant::fromValue(volume_);
        if (fieldName == QLatin1String("country")) return QVariant::fromValue(country_);
        if (fieldName == QLatin1String("subscribe")) return QVariant::fromValue(subscribe_);
        if (fieldName == QLatin1String("gender")) return QVariant::fromValue(gender_);
        if (fieldName == QLatin1String("birthDate")) return QVariant::fromValue(birthDate_);
        if (fieldName == QLatin1String("reminderTime")) return QVariant::fromValue(reminderTime_);
        if (fieldName == QLatin1String("themeColor")) return QVariant::fromValue(themeColor_);
        if (fieldName == QLatin1String("avatar")) return QVariant::fromValue(avatar_);
        if (fieldName == QLatin1String("notificationsEnabled")) return QVariant::fromValue(notificationsEnabled_);
        return QVariant();
    }
    
    void value(const QString& fieldName, const QVariant& value) override {
        if (fieldName == QLatin1String("username")) {
            username_ = value.value<QString>();
            return;
        }
        if (fieldName == QLatin1String("password")) {
            password_ = value.value<QString>();
            return;
        }
        if (fieldName == QLatin1String("age")) {
            age_ = value.value<int32_t>();
            return;
        }
        if (fieldName == QLatin1String("volume")) {
            volume_ = value.value<int32_t>();
            return;
        }
        if (fieldName == QLatin1String("country")) {
            country_ = value.value<Country>();
            return;
        }
        if (fieldName == QLatin1String("subscribe")) {
            subscribe_ = value.value<bool>();
            return;
        }
        if (fieldName == QLatin1String("gender")) {
            gender_ = value.value<Gender>();
            return;
        }
        if (fieldName == QLatin1String("birthDate")) {
            birthDate_ = value.value<QString>();
            return;
        }
        if (fieldName == QLatin1String("reminderTime")) {
            reminderTime_ = value.value<QString>();
            return;
        }
        if (fieldName == QLatin1String("themeColor")) {
            themeColor_ = value.value<QString>();
            return;
        }
        if (fieldName == QLatin1String("avatar")) {
            avatar_ = value.value<QString>();
            return;
        }
        if (fieldName == QLatin1String("notificationsEnabled")) {
            notificationsEnabled_ = value.value<bool>();
            return;
        }
    }
    
    // 特定于RegistrationForm的访问器
        // username字段的访问器
    QString getUsername() const {
        return username_;
    }
    
    void setUsername(const QString& value) {
        username_ = value;
    } 

        // password字段的访问器
    QString getPassword() const {
        return password_;
    }
    
    void setPassword(const QString& value) {
        password_ = value;
    } 

        // age字段的访问器
    int32_t getAge() const {
        return age_;
    }
    
    void setAge(const int32_t& value) {
        age_ = value;
    } 

        // volume字段的访问器
    int32_t getVolume() const {
        return volume_;
    }
    
    void setVolume(const int32_t& value) {
        volume_ = value;
    } 

        // country字段的访问器
    Country getCountry() const {
        return country_;
    }
    
    void setCountry(const Country& value) {
        country_ = value;
    } 

        // subscribe字段的访问器
    bool getSubscribe() const {
        return subscribe_;
    }
    
    void setSubscribe(const bool& value) {
        subscribe_ = value;
    } 

        // gender字段的访问器
    Gender getGender() const {
        return gender_;
    }
    
    void setGender(const Gender& value) {
        gender_ = value;
    } 

        // birthDate字段的访问器
    QString getBirthDate() const {
        return birthDate_;
    }
    
    void setBirthDate(const QString& value) {
        birthDate_ = value;
    } 

        // reminderTime字段的访问器
    QString getReminderTime() const {
        return reminderTime_;
    }
    
    void setReminderTime(const QString& value) {
        reminderTime_ = value;
    } 

        // themeColor字段的访问器
    QString getThemeColor() const {
        return themeColor_;
    }
    
    void setThemeColor(const QString& value) {
        themeColor_ = value;
    } 

        // avatar字段的访问器
    QString getAvatar() const {
        return avatar_;
    }
    
    void setAvatar(const QString& value) {
        avatar_ = value;
    } 

        // notificationsEnabled字段的访问器
    bool getNotificationsEnabled() const {
        return notificationsEnabled_;
    }
    
    void setNotificationsEnabled(const bool& value) {
        notificationsEnabled_ = value;
    } 
    
protected:
    QString modelName() const override {
        return "RegistrationForm";
    }
    
private:
    QString username_;
    QString password_;
    int32_t age_;
    int32_t volume_;
    Country country_;
    bool subscribe_;
    Gender gender_;
    QString birthDate_;
    QString reminderTime_;
    QString themeColor_;
    QString avatar_;
    bool notificationsEnabled_;
    
    // 变更通知
    void notifyChange();
};



} // namespace examples::ui

