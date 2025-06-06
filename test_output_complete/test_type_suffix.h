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

// 此文件由 Mota 代码生成器自动生成
// 生成时间: 2025-06-06 19:48:45
// 源文件: unknown.mota

using namespace ymf;


namespace examples.type_suffix {


// User块
class MODEL_EXPORT UserBlock : public IBlock {
public:
    UserBlock() = default;
    
    
    // 实现IBlock接口
    QCborValue toCbor() const override {
        QCborMap map;
        map.insert(QLatin1String("name"), QCborValue(getName()));
        map.insert(QLatin1String("age"), QCborValue(getAge()));
        map.insert(QLatin1String("email"), QCborValue(getEmail()));
        return map;
    }
    
    void fromCbor(const QCborValue& cbor) override {
        QCborMap map = cbor.toMap();
        setName(map.value(QLatin1String("name")).toString());
        setAge(static_cast<int32_t>(map.value(QLatin1String("age")).toInteger()));
        setEmail(map.value(QLatin1String("email")).toString());
    }
    
    QString name() const override {
        return "User";
    }
    
    QStringList fields() const override {
        return QStringList{QLatin1String("name"), QLatin1String("age"), QLatin1String("email")};
    }
    
    QString fieldType(const QString& fieldName) const override {
        if (fieldName == QLatin1String("name")) return QLatin1String("string");
        if (fieldName == QLatin1String("age")) return QLatin1String("int32");
        if (fieldName == QLatin1String("email")) return QLatin1String("string");
        return QLatin1String("");
    }
    
    QList<QSharedPointer<void>> fieldAnnotation(const QString& fieldName) const override {
        
        return QList<QSharedPointer<void>>();
    }
    
    QString description() const override {
        return "Generated from block User";
    }
    
    QString fieldDescription(const QString& fieldName) const override {
        
        return QString();
    }
    
    QVariant value(const QString& fieldName) const override {
        if (fieldName == QLatin1String("name")) return QVariant::fromValue(name_);
        if (fieldName == QLatin1String("age")) return QVariant::fromValue(age_);
        if (fieldName == QLatin1String("email")) return QVariant::fromValue(email_);
        return QVariant();
    }
    
    void value(const QString& fieldName, const QVariant& value) override {
        if (fieldName == QLatin1String("name")) {
            name_ = value.value<QString>();
            return true;
        }
        if (fieldName == QLatin1String("age")) {
            age_ = value.value<int32_t>();
            return true;
        }
        if (fieldName == QLatin1String("email")) {
            email_ = value.value<QString>();
            return true;
        }
        return false;
    }
    
    // 特定于User的访问器
        // name字段的访问器
    QString getName() const {
        return name_;
    }
    
    void setName(const QString& value) {
        name_ = value;
    } 

        // age字段的访问器
    int32_t getAge() const {
        return age_;
    }
    
    void setAge(const int32_t& value) {
        age_ = value;
    } 

        // email字段的访问器
    QString getEmail() const {
        return email_;
    }
    
    void setEmail(const QString& value) {
        email_ = value;
    } 
    
private:
    QString name_;
    int32_t age_;
    QString email_;
};


// Profile块
class MODEL_EXPORT ProfileBlock : public IBlock {
public:
    ProfileBlock() = default;
    
    
    // 实现IBlock接口
    QCborValue toCbor() const override {
        QCborMap map;
        map.insert(QLatin1String("bio"), QCborValue(getBio()));
        map.insert(QLatin1String("avatar"), QCborValue(getAvatar()));
        QCborArray tagsArray;
for (const auto& item : getTags()) {
    tagsArray.append(QCborValue(item));
}
map.insert(QLatin1String("tags"), tagsArray);
        return map;
    }
    
    void fromCbor(const QCborValue& cbor) override {
        QCborMap map = cbor.toMap();
        setBio(map.value(QLatin1String("bio")).toString());
        setAvatar(map.value(QLatin1String("avatar")).toString());
        QCborArray tagsArray = map.value(QLatin1String("tags")).toArray();
QVector<QString> tags;
for (const auto& itemValue : tagsArray) {
    tags.append(static_cast<QString>(itemValue.toString()));
}
setTags(tags);
    }
    
    QString name() const override {
        return "Profile";
    }
    
    QStringList fields() const override {
        return QStringList{QLatin1String("bio"), QLatin1String("avatar"), QLatin1String("tags")};
    }
    
    QString fieldType(const QString& fieldName) const override {
        if (fieldName == QLatin1String("bio")) return QLatin1String("string");
        if (fieldName == QLatin1String("avatar")) return QLatin1String("string");
        if (fieldName == QLatin1String("tags")) return QLatin1String("repeated string");
        return QLatin1String("");
    }
    
    QList<QSharedPointer<void>> fieldAnnotation(const QString& fieldName) const override {
        
        return QList<QSharedPointer<void>>();
    }
    
    QString description() const override {
        return "Generated from block Profile";
    }
    
    QString fieldDescription(const QString& fieldName) const override {
        
        return QString();
    }
    
    QVariant value(const QString& fieldName) const override {
        if (fieldName == QLatin1String("bio")) return QVariant::fromValue(bio_);
        if (fieldName == QLatin1String("avatar")) return QVariant::fromValue(avatar_);
        if (fieldName == QLatin1String("tags")) return QVariant::fromValue(tags_);
        return QVariant();
    }
    
    void value(const QString& fieldName, const QVariant& value) override {
        if (fieldName == QLatin1String("bio")) {
            bio_ = value.value<QString>();
            return true;
        }
        if (fieldName == QLatin1String("avatar")) {
            avatar_ = value.value<QString>();
            return true;
        }
        if (fieldName == QLatin1String("tags")) {
            tags_ = value.value<QVector<QString>>();
            return true;
        }
        return false;
    }
    
    // 特定于Profile的访问器
        // bio字段的访问器
    QString getBio() const {
        return bio_;
    }
    
    void setBio(const QString& value) {
        bio_ = value;
    } 

        // avatar字段的访问器
    QString getAvatar() const {
        return avatar_;
    }
    
    void setAvatar(const QString& value) {
        avatar_ = value;
    } 

        // tags字段的访问器
    QVector<QString> getTags() const {
        return tags_;
    }
    
    void setTags(const QVector<QString>& value) {
        tags_ = value;
    } 
    
private:
    QString bio_;
    QString avatar_;
    QVector<QString> tags_;
};


// UserProfile结构体

class MODEL_EXPORT UserProfile : public IModel {
public:
    UserProfile() = default;
    
    
    // 实现IModel接口
    QCborValue toCbor() const override {
        QCborMap map;
        map.insert(QLatin1String("user"), getUser().toCbor());
        map.insert(QLatin1String("profile"), getProfile().toCbor());
        QCborArray friendsArray;
for (const auto& item : getFriends()) {
    friendsArray.append(item.toCbor());
}
map.insert(QLatin1String("friends"), friendsArray);
        map.insert(QLatin1String("description"), QCborValue(getDescription()));
        map.insert(QLatin1String("isActive"), QCborValue(getIsActive()));
        return map;
    }
    
    void fromCbor(const QCborValue& cbor) override {
        QCborMap map = cbor.toMap();
        UserBlock user;
user.fromCbor(map.value(QLatin1String("user")));
setUser(user);
        ProfileBlock profile;
profile.fromCbor(map.value(QLatin1String("profile")));
setProfile(profile);
        QCborArray friendsArray = map.value(QLatin1String("friends")).toArray();
QVector<UserBlock> friends;
for (const auto& itemValue : friendsArray) {
    UserBlock item;
    item.fromCbor(itemValue);
    friends.append(item);
}
setFriends(friends);
        setDescription(map.value(QLatin1String("description")).toString());
        setIsActive(map.value(QLatin1String("isActive")).toBool());
    }
    
    QStringList fields() const override {
        return QStringList{QLatin1String("user"), QLatin1String("profile"), QLatin1String("friends"), QLatin1String("description"), QLatin1String("isActive")};
    }
    
    QString fieldOriginTypeName(const QString& fieldName) const override {
        if (fieldName == QLatin1String("user")) return QLatin1String("User");
        if (fieldName == QLatin1String("profile")) return QLatin1String("Profile");
        if (fieldName == QLatin1String("friends")) return QLatin1String("repeated User");
        if (fieldName == QLatin1String("description")) return QLatin1String("string");
        if (fieldName == QLatin1String("isActive")) return QLatin1String("bool");
        return QLatin1String("");
    }
    
    QList<QSharedPointer<void>> fieldAnnotations(const QString& fieldName) const override {
        
        return QList<QSharedPointer<void>>();
    }
    
    QString description() const override {
        return "Generated from struct UserProfile";
    }
    
    QString fieldDescription(const QString& fieldName) const override {
        
        return QString();
    }
    
    QVariant value(const QString& fieldName) const override {
        if (fieldName == QLatin1String("user")) return QVariant::fromValue(user_);
        if (fieldName == QLatin1String("profile")) return QVariant::fromValue(profile_);
        if (fieldName == QLatin1String("friends")) return QVariant::fromValue(friends_);
        if (fieldName == QLatin1String("description")) return QVariant::fromValue(description_);
        if (fieldName == QLatin1String("isActive")) return QVariant::fromValue(isActive_);
        return QVariant();
    }
    
    void value(const QString& fieldName, const QVariant& value) override {
        if (fieldName == QLatin1String("user")) {
            user_ = value.value<UserBlock>();
            return true;
        }
        if (fieldName == QLatin1String("profile")) {
            profile_ = value.value<ProfileBlock>();
            return true;
        }
        if (fieldName == QLatin1String("friends")) {
            friends_ = value.value<QVector<UserBlock>>();
            return true;
        }
        if (fieldName == QLatin1String("description")) {
            description_ = value.value<QString>();
            return true;
        }
        if (fieldName == QLatin1String("isActive")) {
            isActive_ = value.value<bool>();
            return true;
        }
        return false;
    }
    
    // 特定于UserProfile的访问器
        // user字段的访问器
    UserBlock getUser() const {
        return user_;
    }
    
    void setUser(const UserBlock& value) {
        user_ = value;
    } 

        // profile字段的访问器
    ProfileBlock getProfile() const {
        return profile_;
    }
    
    void setProfile(const ProfileBlock& value) {
        profile_ = value;
    } 

        // friends字段的访问器
    QVector<UserBlock> getFriends() const {
        return friends_;
    }
    
    void setFriends(const QVector<UserBlock>& value) {
        friends_ = value;
    } 

        // description字段的访问器
    QString getDescription() const {
        return description_;
    }
    
    void setDescription(const QString& value) {
        description_ = value;
    } 

        // isActive字段的访问器
    bool getIsActive() const {
        return isActive_;
    }
    
    void setIsActive(const bool& value) {
        isActive_ = value;
    } 
    
protected:
    QString modelName() const override {
        return "UserProfile";
    }
    
private:
    UserBlock user_;
    ProfileBlock profile_;
    QVector<UserBlock> friends_;
    QString description_;
    bool isActive_;
    
    // 变更通知
    void notifyChange();
};


// UserValidator注解
class MODEL_EXPORT UserValidatorAnnotation : public IAnnotation {
public:
    UserValidatorAnnotation() = default;
    
    
    // 实现IAnnotation接口
    QString name() const override {
        return "UserValidator";
    }
    
    QVariant argument(const QString& argumentName) const override {
        if (argumentName == QLatin1String("pattern")) return QVariant::fromValue(pattern_);
        if (argumentName == QLatin1String("minLength")) return QVariant::fromValue(minLength_);
        if (argumentName == QLatin1String("maxLength")) return QVariant::fromValue(maxLength_);
        return QVariant();
    }
    
    QStringList argumentNames() const override {
        return QStringList{QLatin1String("pattern"), QLatin1String("minLength"), QLatin1String("maxLength")};
    }
    
    // 特定于UserValidator的访问器
        // pattern字段的访问器
    QString getPattern() const {
        return pattern_;
    }
    
    void setPattern(const QString& value) {
        pattern_ = value;
    } 

        // minLength字段的访问器
    int32_t getMinLength() const {
        return minLength_;
    }
    
    void setMinLength(const int32_t& value) {
        minLength_ = value;
    } 

        // maxLength字段的访问器
    int32_t getMaxLength() const {
        return maxLength_;
    }
    
    void setMaxLength(const int32_t& value) {
        maxLength_ = value;
    } 
    
private:
    QString pattern_;
    int32_t minLength_;
    int32_t maxLength_;
}; 

// UserRole枚举
enum class UserRoleEnum {
    Admin = 0,
    Moderator = 1,
    User = 2,
    Guest = 3
};

// UserRole辅助函数
namespace UserRoleEnumHelper {
    // 将枚举值转换为字符串
    inline QString toString(UserRoleEnum value) {
        switch (value) {
            case UserRoleEnum::Admin:
                return "Admin";
            case UserRoleEnum::Moderator:
                return "Moderator";
            case UserRoleEnum::User:
                return "User";
            case UserRoleEnum::Guest:
                return "Guest";
            default:
                return QString();
        }
    }
    
    // 将字符串转换为枚举值
    inline UserRoleEnum fromString(const QString& str) {
        if (str == "Admin") {
            return UserRoleEnum::Admin;
        } else if (str == "Moderator") {
            return UserRoleEnum::Moderator;
        } else if (str == "User") {
            return UserRoleEnum::User;
        } else if (str == "Guest") {
            return UserRoleEnum::Guest;
        }
        return UserRoleEnum::Admin;
    }
    
    // 获取所有枚举值的字符串表示
    inline QStringList allValues() {
        return QStringList() << "Admin" << "Moderator" << "User" << "Guest";
    }
    
    // 获取所有枚举值的UI显示名称
    inline QStringList allDisplayNames() {
        return QStringList() << "Admin" << "Moderator" << "User" << "Guest";
    }
}


// ComplexSystem结构体

class MODEL_EXPORT ComplexSystem : public IModel {
public:
    ComplexSystem() = default;
    
    
    // 实现IModel接口
    QCborValue toCbor() const override {
        QCborMap map;
        map.insert(QLatin1String("mainUser"), getMainUser().toCbor());
        QCborArray userProfilesArray;
for (const auto& item : getUserProfiles()) {
    userProfilesArray.append(item.toCbor());
}
map.insert(QLatin1String("userProfiles"), userProfilesArray);
        map.insert(QLatin1String("defaultRole"), getDefaultRole().toCbor());
        QCborArray allowedRolesArray;
for (const auto& item : getAllowedRoles()) {
    allowedRolesArray.append(item.toCbor());
}
map.insert(QLatin1String("allowedRoles"), allowedRolesArray);
        map.insert(QLatin1String("systemName"), QCborValue(getSystemName()));
        map.insert(QLatin1String("maxUsers"), QCborValue(getMaxUsers()));
        map.insert(QLatin1String("isEnabled"), QCborValue(getIsEnabled()));
        map.insert(QLatin1String("username"), QCborValue(getUsername()));
        return map;
    }
    
    void fromCbor(const QCborValue& cbor) override {
        QCborMap map = cbor.toMap();
        UserBlock mainUser;
mainUser.fromCbor(map.value(QLatin1String("mainUser")));
setMainUser(mainUser);
        QCborArray userProfilesArray = map.value(QLatin1String("userProfiles")).toArray();
QVector<ProfileBlock> userProfiles;
for (const auto& itemValue : userProfilesArray) {
    ProfileBlock item;
    item.fromCbor(itemValue);
    userProfiles.append(item);
}
setUserProfiles(userProfiles);
        UserRoleEnum defaultRole;
defaultRole.fromCbor(map.value(QLatin1String("defaultRole")));
setDefaultRole(defaultRole);
        QCborArray allowedRolesArray = map.value(QLatin1String("allowedRoles")).toArray();
QVector<UserRoleEnum> allowedRoles;
for (const auto& itemValue : allowedRolesArray) {
    UserRoleEnum item;
    item.fromCbor(itemValue);
    allowedRoles.append(item);
}
setAllowedRoles(allowedRoles);
        setSystemName(map.value(QLatin1String("systemName")).toString());
        setMaxUsers(static_cast<int32_t>(map.value(QLatin1String("maxUsers")).toInteger()));
        setIsEnabled(map.value(QLatin1String("isEnabled")).toBool());
        setUsername(map.value(QLatin1String("username")).toString());
    }
    
    QStringList fields() const override {
        return QStringList{QLatin1String("mainUser"), QLatin1String("userProfiles"), QLatin1String("defaultRole"), QLatin1String("allowedRoles"), QLatin1String("systemName"), QLatin1String("maxUsers"), QLatin1String("isEnabled"), QLatin1String("username")};
    }
    
    QString fieldOriginTypeName(const QString& fieldName) const override {
        if (fieldName == QLatin1String("mainUser")) return QLatin1String("User");
        if (fieldName == QLatin1String("userProfiles")) return QLatin1String("repeated Profile");
        if (fieldName == QLatin1String("defaultRole")) return QLatin1String("UserRole");
        if (fieldName == QLatin1String("allowedRoles")) return QLatin1String("repeated UserRole");
        if (fieldName == QLatin1String("systemName")) return QLatin1String("string");
        if (fieldName == QLatin1String("maxUsers")) return QLatin1String("int32");
        if (fieldName == QLatin1String("isEnabled")) return QLatin1String("bool");
        if (fieldName == QLatin1String("username")) return QLatin1String("string");
        return QLatin1String("");
    }
    
    QList<QSharedPointer<void>> fieldAnnotations(const QString& fieldName) const override {
        
        return QList<QSharedPointer<void>>();
    }
    
    QString description() const override {
        return "Generated from struct ComplexSystem";
    }
    
    QString fieldDescription(const QString& fieldName) const override {
        
        return QString();
    }
    
    QVariant value(const QString& fieldName) const override {
        if (fieldName == QLatin1String("mainUser")) return QVariant::fromValue(mainUser_);
        if (fieldName == QLatin1String("userProfiles")) return QVariant::fromValue(userProfiles_);
        if (fieldName == QLatin1String("defaultRole")) return QVariant::fromValue(defaultRole_);
        if (fieldName == QLatin1String("allowedRoles")) return QVariant::fromValue(allowedRoles_);
        if (fieldName == QLatin1String("systemName")) return QVariant::fromValue(systemName_);
        if (fieldName == QLatin1String("maxUsers")) return QVariant::fromValue(maxUsers_);
        if (fieldName == QLatin1String("isEnabled")) return QVariant::fromValue(isEnabled_);
        if (fieldName == QLatin1String("username")) return QVariant::fromValue(username_);
        return QVariant();
    }
    
    void value(const QString& fieldName, const QVariant& value) override {
        if (fieldName == QLatin1String("mainUser")) {
            mainUser_ = value.value<UserBlock>();
            return true;
        }
        if (fieldName == QLatin1String("userProfiles")) {
            userProfiles_ = value.value<QVector<ProfileBlock>>();
            return true;
        }
        if (fieldName == QLatin1String("defaultRole")) {
            defaultRole_ = value.value<UserRoleEnum>();
            return true;
        }
        if (fieldName == QLatin1String("allowedRoles")) {
            allowedRoles_ = value.value<QVector<UserRoleEnum>>();
            return true;
        }
        if (fieldName == QLatin1String("systemName")) {
            systemName_ = value.value<QString>();
            return true;
        }
        if (fieldName == QLatin1String("maxUsers")) {
            maxUsers_ = value.value<int32_t>();
            return true;
        }
        if (fieldName == QLatin1String("isEnabled")) {
            isEnabled_ = value.value<bool>();
            return true;
        }
        if (fieldName == QLatin1String("username")) {
            username_ = value.value<QString>();
            return true;
        }
        return false;
    }
    
    // 特定于ComplexSystem的访问器
        // mainUser字段的访问器
    UserBlock getMainUser() const {
        return mainUser_;
    }
    
    void setMainUser(const UserBlock& value) {
        mainUser_ = value;
    } 

        // userProfiles字段的访问器
    QVector<ProfileBlock> getUserProfiles() const {
        return userProfiles_;
    }
    
    void setUserProfiles(const QVector<ProfileBlock>& value) {
        userProfiles_ = value;
    } 

        // defaultRole字段的访问器
    UserRoleEnum getDefaultRole() const {
        return defaultRole_;
    }
    
    void setDefaultRole(const UserRoleEnum& value) {
        defaultRole_ = value;
    } 

        // allowedRoles字段的访问器
    QVector<UserRoleEnum> getAllowedRoles() const {
        return allowedRoles_;
    }
    
    void setAllowedRoles(const QVector<UserRoleEnum>& value) {
        allowedRoles_ = value;
    } 

        // systemName字段的访问器
    QString getSystemName() const {
        return systemName_;
    }
    
    void setSystemName(const QString& value) {
        systemName_ = value;
    } 

        // maxUsers字段的访问器
    int32_t getMaxUsers() const {
        return maxUsers_;
    }
    
    void setMaxUsers(const int32_t& value) {
        maxUsers_ = value;
    } 

        // isEnabled字段的访问器
    bool getIsEnabled() const {
        return isEnabled_;
    }
    
    void setIsEnabled(const bool& value) {
        isEnabled_ = value;
    } 

        // username字段的访问器
    QString getUsername() const {
        return username_;
    }
    
    void setUsername(const QString& value) {
        username_ = value;
    } 
    
protected:
    QString modelName() const override {
        return "ComplexSystem";
    }
    
private:
    UserBlock mainUser_;
    QVector<ProfileBlock> userProfiles_;
    UserRoleEnum defaultRole_;
    QVector<UserRoleEnum> allowedRoles_;
    QString systemName_;
    int32_t maxUsers_;
    bool isEnabled_;
    QString username_;
    
    // 变更通知
    void notifyChange();
};



} // namespace examples.type_suffix

