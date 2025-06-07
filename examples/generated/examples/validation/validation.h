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


namespace examples::validation {


// ValidatedForm结构体

class MODEL_EXPORT ValidatedFormModel : public IModel {
public:
    ValidatedFormModel() = default;
    
    
    // 实现IModel接口
    QCborValue toCbor() const override {
        QCborMap map;
        map.insert(QLatin1String("username"), QCborValue(getUsername()));
        map.insert(QLatin1String("password"), QCborValue(getPassword()));
        map.insert(QLatin1String("phone"), QCborValue(getPhone()));
        map.insert(QLatin1String("email"), QCborValue(getEmail()));
        map.insert(QLatin1String("age"), QCborValue(getAge()));
        map.insert(QLatin1String("website"), QCborValue(getWebsite()));
        map.insert(QLatin1String("confirmPassword"), QCborValue(getConfirmPassword()));
        return map;
    }
    
    void fromCbor(const QCborValue& cbor) override {
        QCborMap map = cbor.toMap();
        setUsername(map.value(QLatin1String("username")).toString());
        setPassword(map.value(QLatin1String("password")).toString());
        setPhone(map.value(QLatin1String("phone")).toString());
        setEmail(map.value(QLatin1String("email")).toString());
        setAge(static_cast<int32_t>(map.value(QLatin1String("age")).toInteger()));
        setWebsite(map.value(QLatin1String("website")).toString());
        setConfirmPassword(map.value(QLatin1String("confirmPassword")).toString());
    }
    
    QStringList fields() const override {
        return QStringList{QLatin1String("username"), QLatin1String("password"), QLatin1String("phone"), QLatin1String("email"), QLatin1String("age"), QLatin1String("website"), QLatin1String("confirmPassword")};
    }
    
    QString fieldOriginTypeName(const QString& fieldName) const override {
        if (fieldName == QLatin1String("username")) return QLatin1String("string");
        if (fieldName == QLatin1String("password")) return QLatin1String("string");
        if (fieldName == QLatin1String("phone")) return QLatin1String("string");
        if (fieldName == QLatin1String("email")) return QLatin1String("string");
        if (fieldName == QLatin1String("age")) return QLatin1String("int32");
        if (fieldName == QLatin1String("website")) return QLatin1String("string");
        if (fieldName == QLatin1String("confirmPassword")) return QLatin1String("string");
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
        if (fieldName == QLatin1String("phone")) {
            return QList<QSharedPointer<void>>();
        }
        if (fieldName == QLatin1String("email")) {
            return QList<QSharedPointer<void>>();
        }
        if (fieldName == QLatin1String("age")) {
            return QList<QSharedPointer<void>>();
        }
        if (fieldName == QLatin1String("website")) {
            return QList<QSharedPointer<void>>();
        }
        if (fieldName == QLatin1String("confirmPassword")) {
            return QList<QSharedPointer<void>>();
        }
        return QList<QSharedPointer<void>>();
    }
    
    QString description() const override {
        return "Generated from struct ValidatedForm";
    }
    
    QString fieldDescription(const QString& fieldName) const override {
        
        return QString();
    }
    
    QVariant value(const QString& fieldName) const override {
        if (fieldName == QLatin1String("username")) return QVariant::fromValue(username_);
        if (fieldName == QLatin1String("password")) return QVariant::fromValue(password_);
        if (fieldName == QLatin1String("phone")) return QVariant::fromValue(phone_);
        if (fieldName == QLatin1String("email")) return QVariant::fromValue(email_);
        if (fieldName == QLatin1String("age")) return QVariant::fromValue(age_);
        if (fieldName == QLatin1String("website")) return QVariant::fromValue(website_);
        if (fieldName == QLatin1String("confirmPassword")) return QVariant::fromValue(confirmPassword_);
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
        if (fieldName == QLatin1String("phone")) {
            phone_ = value.value<QString>();
            return;
        }
        if (fieldName == QLatin1String("email")) {
            email_ = value.value<QString>();
            return;
        }
        if (fieldName == QLatin1String("age")) {
            age_ = value.value<int32_t>();
            return;
        }
        if (fieldName == QLatin1String("website")) {
            website_ = value.value<QString>();
            return;
        }
        if (fieldName == QLatin1String("confirmPassword")) {
            confirmPassword_ = value.value<QString>();
            return;
        }
    }
    
    // 特定于ValidatedForm的访问器
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

        // phone字段的访问器
    QString getPhone() const {
        return phone_;
    }
    
    void setPhone(const QString& value) {
        phone_ = value;
    } 

        // email字段的访问器
    QString getEmail() const {
        return email_;
    }
    
    void setEmail(const QString& value) {
        email_ = value;
    } 

        // age字段的访问器
    int32_t getAge() const {
        return age_;
    }
    
    void setAge(const int32_t& value) {
        age_ = value;
    } 

        // website字段的访问器
    QString getWebsite() const {
        return website_;
    }
    
    void setWebsite(const QString& value) {
        website_ = value;
    } 

        // confirmPassword字段的访问器
    QString getConfirmPassword() const {
        return confirmPassword_;
    }
    
    void setConfirmPassword(const QString& value) {
        confirmPassword_ = value;
    } 
    
protected:
    QString modelName() const override {
        return "ValidatedForm";
    }
    
private:
    QString username_;
    QString password_;
    QString phone_;
    QString email_;
    int32_t age_;
    QString website_;
    QString confirmPassword_;
    
    // 变更通知
    void notifyChange();
};


// ConditionalValidation结构体

class MODEL_EXPORT ConditionalValidationModel : public IModel {
public:
    ConditionalValidationModel() = default;
    
    
    // 实现IModel接口
    QCborValue toCbor() const override {
        QCborMap map;
        map.insert(QLatin1String("needsShipping"), QCborValue(getNeedsShipping()));
        map.insert(QLatin1String("country"), QCborValue(getCountry()));
        map.insert(QLatin1String("shippingAddress"), getShippingAddress().toCbor());
        map.insert(QLatin1String("zipCode"), getZipCode().toCbor());
        return map;
    }
    
    void fromCbor(const QCborValue& cbor) override {
        QCborMap map = cbor.toMap();
        setNeedsShipping(map.value(QLatin1String("needsShipping")).toBool());
        setCountry(map.value(QLatin1String("country")).toString());
        Optional stringBlock shippingAddress;
        shippingAddress.fromCbor(map.value(QLatin1String("shippingAddress")));
        setShippingAddress(shippingAddress);
        Optional stringBlock zipCode;
        zipCode.fromCbor(map.value(QLatin1String("zipCode")));
        setZipCode(zipCode);
    }
    
    QStringList fields() const override {
        return QStringList{QLatin1String("needsShipping"), QLatin1String("country"), QLatin1String("shippingAddress"), QLatin1String("zipCode")};
    }
    
    QString fieldOriginTypeName(const QString& fieldName) const override {
        if (fieldName == QLatin1String("needsShipping")) return QLatin1String("bool");
        if (fieldName == QLatin1String("country")) return QLatin1String("string");
        if (fieldName == QLatin1String("shippingAddress")) return QLatin1String("optional string");
        if (fieldName == QLatin1String("zipCode")) return QLatin1String("optional string");
        return QLatin1String("");
    }
    
    QList<QSharedPointer<IAnnotation>> annotations() const override {
        
        return QList<QSharedPointer<IAnnotation>>();
    }
    
    QList<QSharedPointer<void>> fieldAnnotations(const QString& fieldName) const override {
        if (fieldName == QLatin1String("needsShipping")) {
            return QList<QSharedPointer<void>>();
        }
        if (fieldName == QLatin1String("country")) {
            return QList<QSharedPointer<void>>();
        }
        if (fieldName == QLatin1String("shippingAddress")) {
            return QList<QSharedPointer<void>>();
        }
        if (fieldName == QLatin1String("zipCode")) {
            return QList<QSharedPointer<void>>();
        }
        return QList<QSharedPointer<void>>();
    }
    
    QString description() const override {
        return "Generated from struct ConditionalValidation";
    }
    
    QString fieldDescription(const QString& fieldName) const override {
        
        return QString();
    }
    
    QVariant value(const QString& fieldName) const override {
        if (fieldName == QLatin1String("needsShipping")) return QVariant::fromValue(needsShipping_);
        if (fieldName == QLatin1String("country")) return QVariant::fromValue(country_);
        if (fieldName == QLatin1String("shippingAddress")) return QVariant::fromValue(shippingAddress_);
        if (fieldName == QLatin1String("zipCode")) return QVariant::fromValue(zipCode_);
        return QVariant();
    }
    
    void value(const QString& fieldName, const QVariant& value) override {
        if (fieldName == QLatin1String("needsShipping")) {
            needsShipping_ = value.value<bool>();
            return;
        }
        if (fieldName == QLatin1String("country")) {
            country_ = value.value<QString>();
            return;
        }
        if (fieldName == QLatin1String("shippingAddress")) {
            shippingAddress_ = value.value<Optional stringBlock>();
            return;
        }
        if (fieldName == QLatin1String("zipCode")) {
            zipCode_ = value.value<Optional stringBlock>();
            return;
        }
    }
    
    // 特定于ConditionalValidation的访问器
        // needsShipping字段的访问器
    bool getNeedsShipping() const {
        return needsShipping_;
    }
    
    void setNeedsShipping(const bool& value) {
        needsShipping_ = value;
    } 

        // country字段的访问器
    QString getCountry() const {
        return country_;
    }
    
    void setCountry(const QString& value) {
        country_ = value;
    } 

        // shippingAddress字段的访问器
    Optional stringBlock getShippingAddress() const {
        return shippingAddress_;
    }
    
    void setShippingAddress(const Optional stringBlock& value) {
        shippingAddress_ = value;
    } 

        // zipCode字段的访问器
    Optional stringBlock getZipCode() const {
        return zipCode_;
    }
    
    void setZipCode(const Optional stringBlock& value) {
        zipCode_ = value;
    } 
    
protected:
    QString modelName() const override {
        return "ConditionalValidation";
    }
    
private:
    bool needsShipping_;
    QString country_;
    Optional stringBlock shippingAddress_;
    Optional stringBlock zipCode_;
    
    // 变更通知
    void notifyChange();
};


// AdvancedValidation结构体

class MODEL_EXPORT AdvancedValidationModel : public IModel {
public:
    AdvancedValidationModel() = default;
    
    
    // 实现IModel接口
    QCborValue toCbor() const override {
        QCborMap map;
        map.insert(QLatin1String("creditCardNumber"), QCborValue(getCreditCardNumber()));
        map.insert(QLatin1String("expiryDate"), QCborValue(getExpiryDate()));
        map.insert(QLatin1String("cvv"), QCborValue(getCvv()));
        map.insert(QLatin1String("cardholderName"), QCborValue(getCardholderName()));
        return map;
    }
    
    void fromCbor(const QCborValue& cbor) override {
        QCborMap map = cbor.toMap();
        setCreditCardNumber(map.value(QLatin1String("creditCardNumber")).toString());
        setExpiryDate(map.value(QLatin1String("expiryDate")).toString());
        setCvv(map.value(QLatin1String("cvv")).toString());
        setCardholderName(map.value(QLatin1String("cardholderName")).toString());
    }
    
    QStringList fields() const override {
        return QStringList{QLatin1String("creditCardNumber"), QLatin1String("expiryDate"), QLatin1String("cvv"), QLatin1String("cardholderName")};
    }
    
    QString fieldOriginTypeName(const QString& fieldName) const override {
        if (fieldName == QLatin1String("creditCardNumber")) return QLatin1String("string");
        if (fieldName == QLatin1String("expiryDate")) return QLatin1String("string");
        if (fieldName == QLatin1String("cvv")) return QLatin1String("string");
        if (fieldName == QLatin1String("cardholderName")) return QLatin1String("string");
        return QLatin1String("");
    }
    
    QList<QSharedPointer<IAnnotation>> annotations() const override {
        
        return QList<QSharedPointer<IAnnotation>>();
    }
    
    QList<QSharedPointer<void>> fieldAnnotations(const QString& fieldName) const override {
        if (fieldName == QLatin1String("creditCardNumber")) {
            return QList<QSharedPointer<void>>();
        }
        if (fieldName == QLatin1String("expiryDate")) {
            return QList<QSharedPointer<void>>();
        }
        if (fieldName == QLatin1String("cvv")) {
            return QList<QSharedPointer<void>>();
        }
        if (fieldName == QLatin1String("cardholderName")) {
            return QList<QSharedPointer<void>>();
        }
        return QList<QSharedPointer<void>>();
    }
    
    QString description() const override {
        return "Generated from struct AdvancedValidation";
    }
    
    QString fieldDescription(const QString& fieldName) const override {
        
        return QString();
    }
    
    QVariant value(const QString& fieldName) const override {
        if (fieldName == QLatin1String("creditCardNumber")) return QVariant::fromValue(creditCardNumber_);
        if (fieldName == QLatin1String("expiryDate")) return QVariant::fromValue(expiryDate_);
        if (fieldName == QLatin1String("cvv")) return QVariant::fromValue(cvv_);
        if (fieldName == QLatin1String("cardholderName")) return QVariant::fromValue(cardholderName_);
        return QVariant();
    }
    
    void value(const QString& fieldName, const QVariant& value) override {
        if (fieldName == QLatin1String("creditCardNumber")) {
            creditCardNumber_ = value.value<QString>();
            return;
        }
        if (fieldName == QLatin1String("expiryDate")) {
            expiryDate_ = value.value<QString>();
            return;
        }
        if (fieldName == QLatin1String("cvv")) {
            cvv_ = value.value<QString>();
            return;
        }
        if (fieldName == QLatin1String("cardholderName")) {
            cardholderName_ = value.value<QString>();
            return;
        }
    }
    
    // 特定于AdvancedValidation的访问器
        // creditCardNumber字段的访问器
    QString getCreditCardNumber() const {
        return creditCardNumber_;
    }
    
    void setCreditCardNumber(const QString& value) {
        creditCardNumber_ = value;
    } 

        // expiryDate字段的访问器
    QString getExpiryDate() const {
        return expiryDate_;
    }
    
    void setExpiryDate(const QString& value) {
        expiryDate_ = value;
    } 

        // cvv字段的访问器
    QString getCvv() const {
        return cvv_;
    }
    
    void setCvv(const QString& value) {
        cvv_ = value;
    } 

        // cardholderName字段的访问器
    QString getCardholderName() const {
        return cardholderName_;
    }
    
    void setCardholderName(const QString& value) {
        cardholderName_ = value;
    } 
    
protected:
    QString modelName() const override {
        return "AdvancedValidation";
    }
    
private:
    QString creditCardNumber_;
    QString expiryDate_;
    QString cvv_;
    QString cardholderName_;
    
    // 变更通知
    void notifyChange();
};



} // namespace examples::validation

