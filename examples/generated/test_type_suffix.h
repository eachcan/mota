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
// 生成时间: 2025-06-09 17:37:03
// 源文件: document.mota

using namespace ymf;




namespace examples {

namespace type_suffix {




// User块
class MODEL_EXPORT UserBlock :  {
public:
    UserBlock() = default;
    


    
    // 实现IBlock接口
    QCborValue toCbor() const override {
        QCborMap map;



























        return map;
    }
    
    void fromCbor(const QCborValue& cbor) override {
        QCborMap map = cbor.toMap();



























    }
    
    QString name() const override {
        return "User";
    }
    
    QStringList fields() const override {
        return QStringList{"name""age""email"};
    }
    
    QString fieldType(const QString& fieldName) const override {


        if (fieldName == "name") {
            return "string";
        }

        if (fieldName == "age") {
            return "int32";
        }

        if (fieldName == "email") {
            return "string";
        }

        return QString();

    }
    
    QList<QSharedPointer<IAnnotation>> annotations() const override {

        return QList<QSharedPointer<IAnnotation>>();

    }
    
    QList<QSharedPointer<void>> fieldAnnotation(const QString& fieldName) const override {


        if (fieldName == "name") {
            QList<QSharedPointer<void>> result;

            return result;
        }
<%endforeach%>

        return QList<QSharedPointer<void>>();
    }
    
    QString description() const override {
        return "Generated block User";
    }
    
    QString fieldDescription(const QString& fieldName) const override {

        if (fieldName == "name") {
            return "field.description";
        }

        if (fieldName == "age") {
            return "field.description";
        }

        if (fieldName == "email") {
            return "field.description";
        }

        return QString();
    }
    
    QVariant value(const QString& fieldName) const override {

        if (fieldName == "name") {
            return QVariant::fromValue(name_);
        }

        if (fieldName == "age") {
            return QVariant::fromValue(age_);
        }

        if (fieldName == "email") {
            return QVariant::fromValue(email_);
        }

        return QVariant();
    }
    
    void value(const QString& fieldName, const QVariant& value) override {

        if (fieldName == "name") {
            name_ = value.value<QString>();
            return;
        }

        if (fieldName == "age") {
            age_ = value.value<int32_t>();
            return;
        }

        if (fieldName == "email") {
            email_ = value.value<QString>();
            return;
        }

    }
    
    // 特定于User的访问器



    QString getName() const {
        return name_;
    }



    void setName(const QString& value) {
        name_ = value;
    }



    int32_t getAge() const {
        return age_;
    }



    void setAge(const int32_t& value) {
        age_ = value;
    }



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
class MODEL_EXPORT ProfileBlock :  {
public:
    ProfileBlock() = default;
    


    
    // 实现IBlock接口
    QCborValue toCbor() const override {
        QCborMap map;



























        return map;
    }
    
    void fromCbor(const QCborValue& cbor) override {
        QCborMap map = cbor.toMap();



























    }
    
    QString name() const override {
        return "Profile";
    }
    
    QStringList fields() const override {
        return QStringList{"bio""avatar""tags"};
    }
    
    QString fieldType(const QString& fieldName) const override {


        if (fieldName == "bio") {
            return "string";
        }

        if (fieldName == "avatar") {
            return "string";
        }

        if (fieldName == "tags") {
            return "repeated string";
        }

        return QString();

    }
    
    QList<QSharedPointer<IAnnotation>> annotations() const override {

        return QList<QSharedPointer<IAnnotation>>();

    }
    
    QList<QSharedPointer<void>> fieldAnnotation(const QString& fieldName) const override {


        if (fieldName == "bio") {
            QList<QSharedPointer<void>> result;

            return result;
        }
<%endforeach%>

        return QList<QSharedPointer<void>>();
    }
    
    QString description() const override {
        return "Generated block Profile";
    }
    
    QString fieldDescription(const QString& fieldName) const override {

        if (fieldName == "bio") {
            return "field.description";
        }

        if (fieldName == "avatar") {
            return "field.description";
        }

        if (fieldName == "tags") {
            return "field.description";
        }

        return QString();
    }
    
    QVariant value(const QString& fieldName) const override {

        if (fieldName == "bio") {
            return QVariant::fromValue(bio_);
        }

        if (fieldName == "avatar") {
            return QVariant::fromValue(avatar_);
        }

        if (fieldName == "tags") {
            return QVariant::fromValue(tags_);
        }

        return QVariant();
    }
    
    void value(const QString& fieldName, const QVariant& value) override {

        if (fieldName == "bio") {
            bio_ = value.value<QString>();
            return;
        }

        if (fieldName == "avatar") {
            avatar_ = value.value<QString>();
            return;
        }

        if (fieldName == "tags") {
            tags_ = value.value<repeated string>();
            return;
        }

    }
    
    // 特定于Profile的访问器



    QString getBio() const {
        return bio_;
    }



    void setBio(const QString& value) {
        bio_ = value;
    }



    QString getAvatar() const {
        return avatar_;
    }



    void setAvatar(const QString& value) {
        avatar_ = value;
    }



    repeated string getTags() const {
        return tags_;
    }



    void setTags(const repeated string& value) {
        tags_ = value;
    }



    
private:


    QString bio_;

    QString avatar_;

    repeated string tags_;


}; 


// UserProfile结构体
class MODEL_EXPORT UserProfileModel :  {
public:
    UserProfileModel() = default;
    


    
    // 实现IModel接口
    QCborValue toCbor() const override {
        QCborMap map;











































        return map;
    }
    
    void fromCbor(const QCborValue& cbor) override {
        QCborMap map = cbor.toMap();











































    }
    
    QStringList fields() const override {
        return QStringList{"user""profile""friends""description""isActive"};
    }
    
    QString fieldOriginTypeName(const QString& fieldName) const override {


        if (fieldName == "user") {
            return "User";
        }

        if (fieldName == "profile") {
            return "Profile";
        }

        if (fieldName == "friends") {
            return "repeated User";
        }

        if (fieldName == "description") {
            return "string";
        }

        if (fieldName == "isActive") {
            return "bool";
        }

        return QString();

    }
    
    QList<QSharedPointer<IAnnotation>> annotations() const override {



    }
    
    QList<QSharedPointer<IAnnotation>> fieldAnnotations(const QString& fieldName) const override {


        if (fieldName == "user") {
            QList<QSharedPointer<void>> result;

            return result;
        }
<%endforeach%>

        return QList<QSharedPointer<IAnnotation>>();
    }
    
    QString description() const override {
        return "Generated struct UserProfile";
    }
    
    QString fieldDescription(const QString& fieldName) const override {

        if (fieldName == "user") {
            return "field.description";
        }

        if (fieldName == "profile") {
            return "field.description";
        }

        if (fieldName == "friends") {
            return "field.description";
        }

        if (fieldName == "description") {
            return "field.description";
        }

        if (fieldName == "isActive") {
            return "field.description";
        }

        return QString();
    }
    
    QVariant value(const QString& fieldName) const override {

        if (fieldName == "user") {
            return QVariant::fromValue(user_);
        }

        if (fieldName == "profile") {
            return QVariant::fromValue(profile_);
        }

        if (fieldName == "friends") {
            return QVariant::fromValue(friends_);
        }

        if (fieldName == "description") {
            return QVariant::fromValue(description_);
        }

        if (fieldName == "isActive") {
            return QVariant::fromValue(isActive_);
        }

        return QVariant();
    }
    
    void value(const QString& fieldName, const QVariant& value) override {

        if (fieldName == "user") {
            user_ = value.value<User>();
            return;
        }

        if (fieldName == "profile") {
            profile_ = value.value<Profile>();
            return;
        }

        if (fieldName == "friends") {
            friends_ = value.value<repeated User>();
            return;
        }

        if (fieldName == "description") {
            description_ = value.value<QString>();
            return;
        }

        if (fieldName == "isActive") {
            isActive_ = value.value<bool>();
            return;
        }

    }
    
    // 特定于UserProfile的访问器



    User getUser() const {
        return user_;
    }



    void setUser(const User& value) {
        user_ = value;
    }



    Profile getProfile() const {
        return profile_;
    }



    void setProfile(const Profile& value) {
        profile_ = value;
    }



    repeated User getFriends() const {
        return friends_;
    }



    void setFriends(const repeated User& value) {
        friends_ = value;
    }



    QString getDescription() const {
        return description_;
    }



    void setDescription(const QString& value) {
        description_ = value;
    }



    bool getIsactive() const {
        return isActive_;
    }



    void setIsactive(const bool& value) {
        isActive_ = value;
    }



    
protected:
    QString modelName() const override {
        return "UserProfile";
    }
    
private:


    User user_;

    Profile profile_;

    repeated User friends_;

    QString description_;

    bool isActive_;


}; 


// UserValidator注解
class MODEL_EXPORT UserValidatorAnnotation : public IAnnotation {
public:
    UserValidatorAnnotation() = default;
    


    
    // 实现IAnnotation接口
    QString name() const override {
        return "UserValidator";
    }
    
    QStringList argumentNames() const override {
        return QStringList{"pattern""minLength""maxLength"};
    }
    
    QVariant argumentValue(const QString& argumentName) const override {

        if (fieldName == "pattern") {
            return QVariant::fromValue(pattern_);
        }

        if (fieldName == "minLength") {
            return QVariant::fromValue(minLength_);
        }

        if (fieldName == "maxLength") {
            return QVariant::fromValue(maxLength_);
        }

        return QVariant();
    }
    
    void argumentValue(const QString& argumentName, const QVariant& value) override {

        if (fieldName == "pattern") {
            pattern_ = value.value<QString>();
            return;
        }

        if (fieldName == "minLength") {
            minLength_ = value.value<int32_t>();
            return;
        }

        if (fieldName == "maxLength") {
            maxLength_ = value.value<int32_t>();
            return;
        }

    }
    
    QString description() const override {
        return "Generated annotation UserValidator";
    }
    
    QString argumentDescription(const QString& argumentName) const override {

        if (fieldName == "pattern") {
            return "field.description";
        }

        if (fieldName == "minLength") {
            return "field.description";
        }

        if (fieldName == "maxLength") {
            return "field.description";
        }

        return QString();
    }
    
    // 特定于UserValidator的访问器



    QString getPattern() const {
        return pattern_;
    }



    void setPattern(const QString& value) {
        pattern_ = value;
    }



    int32_t getMinlength() const {
        return minLength_;
    }



    void setMinlength(const int32_t& value) {
        minLength_ = value;
    }



    int32_t getMaxlength() const {
        return maxLength_;
    }



    void setMaxlength(const int32_t& value) {
        maxLength_ = value;
    }



    
private:


    QString pattern_;

    int32_t minLength_;

    int32_t maxLength_;


}; 


// UserRole枚举
enum class UserRole : int32_t {


    Admin = 0

    Moderator = 1

    User = 2

    Guest = 3


};

class MODEL_EXPORT UserRoleHelper {
public:
    static QString toString(UserRole value) {
        switch (value) {


            case UserRole::Admin:
                return "value.string_value";

            case UserRole::Moderator:
                return "value.string_value";

            case UserRole::User:
                return "value.string_value";

            case UserRole::Guest:
                return "value.string_value";


            default:
                return QString();
        }
    }
    
    static UserRole fromString(const QString& str) {


        if (str == "value.string_value") {
            return UserRole::Admin;
        }

        if (str == "value.string_value") {
            return UserRole::Moderator;
        }

        if (str == "value.string_value") {
            return UserRole::User;
        }

        if (str == "value.string_value") {
            return UserRole::Guest;
        }


        return static_cast<UserRole>(0);
    }
    
    static QStringList allStringValues() {
        return QStringList{

            "value.string_value"

            "value.string_value"

            "value.string_value"

            "value.string_value"

        };
    }
    
    static QStringList allDisplayNames() {
        return QStringList{

            "value.display_name"

            "value.display_name"

            "value.display_name"

            "value.display_name"

        };
    }
    
    static QList<QSharedPointer<IAnnotation>> annotations() {



    }
    
    static QList<QSharedPointer<IAnnotation>> valueAnnotations(UserRole value) {
        switch (value) {


            case UserRole::Admin: {

            }
<%endforeach%>

            default:
                return QList<QSharedPointer<IAnnotation>>();
        }
    }
    
    static QList<QSharedPointer<IAnnotation>> valueAnnotationsByName(const QString& valueName) {


        if (valueName == "Admin") {

        }
<%endforeach%>

        return QList<QSharedPointer<IAnnotation>>();
    }
    
    static QString description() {
        return "DESCRIPTION";
    }
    
    static QString valueDescription(UserRole value) {
        switch (value) {

            case UserRole::Admin:
                return "value.description";

            case UserRole::Moderator:
                return "value.description";

            case UserRole::User:
                return "value.description";

            case UserRole::Guest:
                return "value.description";

            default:
                return QString();
        }
    }
    
    static QString valueDescriptionByName(const QString& valueName) {

        if (valueName == "Admin") {
            return "value.description";
        }

        if (valueName == "Moderator") {
            return "value.description";
        }

        if (valueName == "User") {
            return "value.description";
        }

        if (valueName == "Guest") {
            return "value.description";
        }

        return QString();
    }
}; 


// ComplexSystem结构体
class MODEL_EXPORT ComplexSystemModel :  {
public:
    ComplexSystemModel() = default;
    


    
    // 实现IModel接口
    QCborValue toCbor() const override {
        QCborMap map;



































































        return map;
    }
    
    void fromCbor(const QCborValue& cbor) override {
        QCborMap map = cbor.toMap();



































































    }
    
    QStringList fields() const override {
        return QStringList{"mainUser""userProfiles""defaultRole""allowedRoles""systemName""maxUsers""isEnabled""username"};
    }
    
    QString fieldOriginTypeName(const QString& fieldName) const override {


        if (fieldName == "mainUser") {
            return "User";
        }

        if (fieldName == "userProfiles") {
            return "repeated Profile";
        }

        if (fieldName == "defaultRole") {
            return "UserRole";
        }

        if (fieldName == "allowedRoles") {
            return "repeated UserRole";
        }

        if (fieldName == "systemName") {
            return "string";
        }

        if (fieldName == "maxUsers") {
            return "int32";
        }

        if (fieldName == "isEnabled") {
            return "bool";
        }

        if (fieldName == "username") {
            return "string";
        }

        return QString();

    }
    
    QList<QSharedPointer<IAnnotation>> annotations() const override {



    }
    
    QList<QSharedPointer<IAnnotation>> fieldAnnotations(const QString& fieldName) const override {


        if (fieldName == "mainUser") {
            QList<QSharedPointer<void>> result;

            return result;
        }
<%endforeach%>

        return QList<QSharedPointer<IAnnotation>>();
    }
    
    QString description() const override {
        return "Generated struct ComplexSystem";
    }
    
    QString fieldDescription(const QString& fieldName) const override {

        if (fieldName == "mainUser") {
            return "field.description";
        }

        if (fieldName == "userProfiles") {
            return "field.description";
        }

        if (fieldName == "defaultRole") {
            return "field.description";
        }

        if (fieldName == "allowedRoles") {
            return "field.description";
        }

        if (fieldName == "systemName") {
            return "field.description";
        }

        if (fieldName == "maxUsers") {
            return "field.description";
        }

        if (fieldName == "isEnabled") {
            return "field.description";
        }

        if (fieldName == "username") {
            return "field.description";
        }

        return QString();
    }
    
    QVariant value(const QString& fieldName) const override {

        if (fieldName == "mainUser") {
            return QVariant::fromValue(mainUser_);
        }

        if (fieldName == "userProfiles") {
            return QVariant::fromValue(userProfiles_);
        }

        if (fieldName == "defaultRole") {
            return QVariant::fromValue(defaultRole_);
        }

        if (fieldName == "allowedRoles") {
            return QVariant::fromValue(allowedRoles_);
        }

        if (fieldName == "systemName") {
            return QVariant::fromValue(systemName_);
        }

        if (fieldName == "maxUsers") {
            return QVariant::fromValue(maxUsers_);
        }

        if (fieldName == "isEnabled") {
            return QVariant::fromValue(isEnabled_);
        }

        if (fieldName == "username") {
            return QVariant::fromValue(username_);
        }

        return QVariant();
    }
    
    void value(const QString& fieldName, const QVariant& value) override {

        if (fieldName == "mainUser") {
            mainUser_ = value.value<User>();
            return;
        }

        if (fieldName == "userProfiles") {
            userProfiles_ = value.value<repeated Profile>();
            return;
        }

        if (fieldName == "defaultRole") {
            defaultRole_ = value.value<UserRole>();
            return;
        }

        if (fieldName == "allowedRoles") {
            allowedRoles_ = value.value<repeated UserRole>();
            return;
        }

        if (fieldName == "systemName") {
            systemName_ = value.value<QString>();
            return;
        }

        if (fieldName == "maxUsers") {
            maxUsers_ = value.value<int32_t>();
            return;
        }

        if (fieldName == "isEnabled") {
            isEnabled_ = value.value<bool>();
            return;
        }

        if (fieldName == "username") {
            username_ = value.value<QString>();
            return;
        }

    }
    
    // 特定于ComplexSystem的访问器



    User getMainuser() const {
        return mainUser_;
    }



    void setMainuser(const User& value) {
        mainUser_ = value;
    }



    repeated Profile getUserprofiles() const {
        return userProfiles_;
    }



    void setUserprofiles(const repeated Profile& value) {
        userProfiles_ = value;
    }



    UserRole getDefaultrole() const {
        return defaultRole_;
    }



    void setDefaultrole(const UserRole& value) {
        defaultRole_ = value;
    }



    repeated UserRole getAllowedroles() const {
        return allowedRoles_;
    }



    void setAllowedroles(const repeated UserRole& value) {
        allowedRoles_ = value;
    }



    QString getSystemname() const {
        return systemName_;
    }



    void setSystemname(const QString& value) {
        systemName_ = value;
    }



    int32_t getMaxusers() const {
        return maxUsers_;
    }



    void setMaxusers(const int32_t& value) {
        maxUsers_ = value;
    }



    bool getIsenabled() const {
        return isEnabled_;
    }



    void setIsenabled(const bool& value) {
        isEnabled_ = value;
    }



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


    User mainUser_;

    repeated Profile userProfiles_;

    UserRole defaultRole_;

    repeated UserRole allowedRoles_;

    QString systemName_;

    int32_t maxUsers_;

    bool isEnabled_;

    QString username_;


}; 





} // namespace examples

} // namespace type_suffix


 
