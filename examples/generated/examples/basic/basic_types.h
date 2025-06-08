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
// 生成时间: 2025-06-08 13:49:35
// 源文件: unknown.mota

using namespace ymf;


namespace examples::basic {


// BasicTypes结构体

class MODEL_EXPORT BasicTypesModel : public IModel {
public:
    BasicTypesModel() = default;
    
    
    // 实现IModel接口
    QCborValue toCbor() const override {
        QCborMap map;
        map.insert(QLatin1String("int8Value"), QCborValue(getInt8Value()));
        map.insert(QLatin1String("int16Value"), QCborValue(getInt16Value()));
        map.insert(QLatin1String("int32Value"), QCborValue(getInt32Value()));
        map.insert(QLatin1String("int64Value"), QCborValue(getInt64Value()));
        map.insert(QLatin1String("float32Value"), QCborValue(getFloat32Value()));
        map.insert(QLatin1String("float64Value"), QCborValue(getFloat64Value()));
        map.insert(QLatin1String("boolValue"), QCborValue(getBoolValue()));
        map.insert(QLatin1String("stringValue"), QCborValue(getStringValue()));
        return map;
    }
    
    void fromCbor(const QCborValue& cbor) override {
        QCborMap map = cbor.toMap();
        setInt8Value(static_cast<int8_t>(map.value(QLatin1String("int8Value")).toInteger()));
        setInt16Value(static_cast<int16_t>(map.value(QLatin1String("int16Value")).toInteger()));
        setInt32Value(static_cast<int32_t>(map.value(QLatin1String("int32Value")).toInteger()));
        setInt64Value(static_cast<int64_t>(map.value(QLatin1String("int64Value")).toInteger()));
        setFloat32Value(static_cast<float>(map.value(QLatin1String("float32Value")).toDouble()));
        setFloat64Value(static_cast<double>(map.value(QLatin1String("float64Value")).toDouble()));
        setBoolValue(map.value(QLatin1String("boolValue")).toBool());
        setStringValue(map.value(QLatin1String("stringValue")).toString());
    }
    
    QStringList fields() const override {
        return QStringList{QLatin1String("int8Value"), QLatin1String("int16Value"), QLatin1String("int32Value"), QLatin1String("int64Value"), QLatin1String("float32Value"), QLatin1String("float64Value"), QLatin1String("boolValue"), QLatin1String("stringValue")};
    }
    
    QString fieldOriginTypeName(const QString& fieldName) const override {
        if (fieldName == QLatin1String("int8Value")) return QLatin1String("int8");
        if (fieldName == QLatin1String("int16Value")) return QLatin1String("int16");
        if (fieldName == QLatin1String("int32Value")) return QLatin1String("int32");
        if (fieldName == QLatin1String("int64Value")) return QLatin1String("int64");
        if (fieldName == QLatin1String("float32Value")) return QLatin1String("float32");
        if (fieldName == QLatin1String("float64Value")) return QLatin1String("float64");
        if (fieldName == QLatin1String("boolValue")) return QLatin1String("bool");
        if (fieldName == QLatin1String("stringValue")) return QLatin1String("string");
        return QLatin1String("");
    }
    
    QList<QSharedPointer<IAnnotation>> annotations() const override {
        
        return QList<QSharedPointer<IAnnotation>>();
    }
    
    QList<QSharedPointer<void>> fieldAnnotations(const QString& fieldName) const override {
        if (fieldName == QLatin1String("int8Value")) {
            return QList<QSharedPointer<void>>();
        }
        if (fieldName == QLatin1String("int16Value")) {
            return QList<QSharedPointer<void>>();
        }
        if (fieldName == QLatin1String("int32Value")) {
            return QList<QSharedPointer<void>>();
        }
        if (fieldName == QLatin1String("int64Value")) {
            return QList<QSharedPointer<void>>();
        }
        if (fieldName == QLatin1String("float32Value")) {
            return QList<QSharedPointer<void>>();
        }
        if (fieldName == QLatin1String("float64Value")) {
            return QList<QSharedPointer<void>>();
        }
        if (fieldName == QLatin1String("boolValue")) {
            return QList<QSharedPointer<void>>();
        }
        if (fieldName == QLatin1String("stringValue")) {
            return QList<QSharedPointer<void>>();
        }
        return QList<QSharedPointer<void>>();
    }
    
    QString description() const override {
        return "Generated from struct BasicTypes";
    }
    
    QString fieldDescription(const QString& fieldName) const override {
        
        return QString();
    }
    
    QVariant value(const QString& fieldName) const override {
        if (fieldName == QLatin1String("int8Value")) return QVariant::fromValue(int8Value_);
        if (fieldName == QLatin1String("int16Value")) return QVariant::fromValue(int16Value_);
        if (fieldName == QLatin1String("int32Value")) return QVariant::fromValue(int32Value_);
        if (fieldName == QLatin1String("int64Value")) return QVariant::fromValue(int64Value_);
        if (fieldName == QLatin1String("float32Value")) return QVariant::fromValue(float32Value_);
        if (fieldName == QLatin1String("float64Value")) return QVariant::fromValue(float64Value_);
        if (fieldName == QLatin1String("boolValue")) return QVariant::fromValue(boolValue_);
        if (fieldName == QLatin1String("stringValue")) return QVariant::fromValue(stringValue_);
        return QVariant();
    }
    
    void value(const QString& fieldName, const QVariant& value) override {
        if (fieldName == QLatin1String("int8Value")) {
            int8Value_ = value.value<int8_t>();
            return;
        }
        if (fieldName == QLatin1String("int16Value")) {
            int16Value_ = value.value<int16_t>();
            return;
        }
        if (fieldName == QLatin1String("int32Value")) {
            int32Value_ = value.value<int32_t>();
            return;
        }
        if (fieldName == QLatin1String("int64Value")) {
            int64Value_ = value.value<int64_t>();
            return;
        }
        if (fieldName == QLatin1String("float32Value")) {
            float32Value_ = value.value<float>();
            return;
        }
        if (fieldName == QLatin1String("float64Value")) {
            float64Value_ = value.value<double>();
            return;
        }
        if (fieldName == QLatin1String("boolValue")) {
            boolValue_ = value.value<bool>();
            return;
        }
        if (fieldName == QLatin1String("stringValue")) {
            stringValue_ = value.value<QString>();
            return;
        }
    }
    
    // 特定于BasicTypes的访问器
        // int8Value字段的访问器
    int8_t getInt8Value() const {
        return int8Value_;
    }
    
    void setInt8Value(const int8_t& value) {
        int8Value_ = value;
    } 

        // int16Value字段的访问器
    int16_t getInt16Value() const {
        return int16Value_;
    }
    
    void setInt16Value(const int16_t& value) {
        int16Value_ = value;
    } 

        // int32Value字段的访问器
    int32_t getInt32Value() const {
        return int32Value_;
    }
    
    void setInt32Value(const int32_t& value) {
        int32Value_ = value;
    } 

        // int64Value字段的访问器
    int64_t getInt64Value() const {
        return int64Value_;
    }
    
    void setInt64Value(const int64_t& value) {
        int64Value_ = value;
    } 

        // float32Value字段的访问器
    float getFloat32Value() const {
        return float32Value_;
    }
    
    void setFloat32Value(const float& value) {
        float32Value_ = value;
    } 

        // float64Value字段的访问器
    double getFloat64Value() const {
        return float64Value_;
    }
    
    void setFloat64Value(const double& value) {
        float64Value_ = value;
    } 

        // boolValue字段的访问器
    bool getBoolValue() const {
        return boolValue_;
    }
    
    void setBoolValue(const bool& value) {
        boolValue_ = value;
    } 

        // stringValue字段的访问器
    QString getStringValue() const {
        return stringValue_;
    }
    
    void setStringValue(const QString& value) {
        stringValue_ = value;
    } 
    
protected:
    QString modelName() const override {
        return "BasicTypes";
    }
    
private:
    int8_t int8Value_;
    int16_t int16Value_;
    int32_t int32Value_;
    int64_t int64Value_;
    float float32Value_;
    double float64Value_;
    bool boolValue_;
    QString stringValue_;
    
    // 变更通知
    void notifyChange();
};


// ContainerTypes结构体

class MODEL_EXPORT ContainerTypesModel : public IModel {
public:
    ContainerTypesModel() = default;
    
    
    // 实现IModel接口
    QCborValue toCbor() const override {
        QCborMap map;
        QCborArray numbersArray;
        for (const auto& item : getNumbers()) {
            numbersArray.append(QCborValue(item));
        }
        map.insert(QLatin1String("numbers"), numbersArray);
        QCborArray namesArray;
        for (const auto& item : getNames()) {
            namesArray.append(QCborValue(item));
        }
        map.insert(QLatin1String("names"), namesArray);
        map.insert(QLatin1String("middleName"), getMiddleName().toCbor());
        map.insert(QLatin1String("age"), getAge().toCbor());
        return map;
    }
    
    void fromCbor(const QCborValue& cbor) override {
        QCborMap map = cbor.toMap();
        QCborArray numbersArray = map.value(QLatin1String("numbers")).toArray();
        QVector<int32_t> numbers;
        for (const auto& itemValue : numbersArray) {
            numbers.append(static_cast<int32_t>(itemValue.toInteger()));
        }
        setNumbers(numbers);
        QCborArray namesArray = map.value(QLatin1String("names")).toArray();
        QVector<QString> names;
        for (const auto& itemValue : namesArray) {
            names.append(static_cast<QString>(itemValue.toString()));
        }
        setNames(names);
        Optional stringBlock middleName;
        middleName.fromCbor(map.value(QLatin1String("middleName")));
        setMiddleName(middleName);
        Optional int32Block age;
        age.fromCbor(map.value(QLatin1String("age")));
        setAge(age);
    }
    
    QStringList fields() const override {
        return QStringList{QLatin1String("numbers"), QLatin1String("names"), QLatin1String("middleName"), QLatin1String("age")};
    }
    
    QString fieldOriginTypeName(const QString& fieldName) const override {
        if (fieldName == QLatin1String("numbers")) return QLatin1String("repeated int32");
        if (fieldName == QLatin1String("names")) return QLatin1String("repeated string");
        if (fieldName == QLatin1String("middleName")) return QLatin1String("optional string");
        if (fieldName == QLatin1String("age")) return QLatin1String("optional int32");
        return QLatin1String("");
    }
    
    QList<QSharedPointer<IAnnotation>> annotations() const override {
        
        return QList<QSharedPointer<IAnnotation>>();
    }
    
    QList<QSharedPointer<void>> fieldAnnotations(const QString& fieldName) const override {
        if (fieldName == QLatin1String("numbers")) {
            return QList<QSharedPointer<void>>();
        }
        if (fieldName == QLatin1String("names")) {
            return QList<QSharedPointer<void>>();
        }
        if (fieldName == QLatin1String("middleName")) {
            return QList<QSharedPointer<void>>();
        }
        if (fieldName == QLatin1String("age")) {
            return QList<QSharedPointer<void>>();
        }
        return QList<QSharedPointer<void>>();
    }
    
    QString description() const override {
        return "Generated from struct ContainerTypes";
    }
    
    QString fieldDescription(const QString& fieldName) const override {
        
        return QString();
    }
    
    QVariant value(const QString& fieldName) const override {
        if (fieldName == QLatin1String("numbers")) return QVariant::fromValue(numbers_);
        if (fieldName == QLatin1String("names")) return QVariant::fromValue(names_);
        if (fieldName == QLatin1String("middleName")) return QVariant::fromValue(middleName_);
        if (fieldName == QLatin1String("age")) return QVariant::fromValue(age_);
        return QVariant();
    }
    
    void value(const QString& fieldName, const QVariant& value) override {
        if (fieldName == QLatin1String("numbers")) {
            numbers_ = value.value<QVector<int32_t>>();
            return;
        }
        if (fieldName == QLatin1String("names")) {
            names_ = value.value<QVector<QString>>();
            return;
        }
        if (fieldName == QLatin1String("middleName")) {
            middleName_ = value.value<Optional stringBlock>();
            return;
        }
        if (fieldName == QLatin1String("age")) {
            age_ = value.value<Optional int32Block>();
            return;
        }
    }
    
    // 特定于ContainerTypes的访问器
        // numbers字段的访问器
    QVector<int32_t> getNumbers() const {
        return numbers_;
    }
    
    void setNumbers(const QVector<int32_t>& value) {
        numbers_ = value;
    } 

        // names字段的访问器
    QVector<QString> getNames() const {
        return names_;
    }
    
    void setNames(const QVector<QString>& value) {
        names_ = value;
    } 

        // middleName字段的访问器
    Optional stringBlock getMiddleName() const {
        return middleName_;
    }
    
    void setMiddleName(const Optional stringBlock& value) {
        middleName_ = value;
    } 

        // age字段的访问器
    Optional int32Block getAge() const {
        return age_;
    }
    
    void setAge(const Optional int32Block& value) {
        age_ = value;
    } 
    
protected:
    QString modelName() const override {
        return "ContainerTypes";
    }
    
private:
    QVector<int32_t> numbers_;
    QVector<QString> names_;
    Optional stringBlock middleName_;
    Optional int32Block age_;
    
    // 变更通知
    void notifyChange();
};


// StudentScores结构体

class MODEL_EXPORT StudentScoresModel : public IModel {
public:
    StudentScoresModel() = default;
    
    
    // 实现IModel接口
    QCborValue toCbor() const override {
        QCborMap map;
        map.insert(QLatin1String("studentName"), QCborValue(getStudentName()));
        map.insert(QLatin1String("studentId"), QCborValue(getStudentId()));
        map.insert(QLatin1String("mathScore"), QCborValue(getMathScore()));
        map.insert(QLatin1String("englishScore"), QCborValue(getEnglishScore()));
        map.insert(QLatin1String("scienceScore"), QCborValue(getScienceScore()));
        return map;
    }
    
    void fromCbor(const QCborValue& cbor) override {
        QCborMap map = cbor.toMap();
        setStudentName(map.value(QLatin1String("studentName")).toString());
        setStudentId(static_cast<int32_t>(map.value(QLatin1String("studentId")).toInteger()));
        setMathScore(static_cast<int32_t>(map.value(QLatin1String("mathScore")).toInteger()));
        setEnglishScore(static_cast<int32_t>(map.value(QLatin1String("englishScore")).toInteger()));
        setScienceScore(static_cast<int32_t>(map.value(QLatin1String("scienceScore")).toInteger()));
    }
    
    QStringList fields() const override {
        return QStringList{QLatin1String("studentName"), QLatin1String("studentId"), QLatin1String("mathScore"), QLatin1String("englishScore"), QLatin1String("scienceScore")};
    }
    
    QString fieldOriginTypeName(const QString& fieldName) const override {
        if (fieldName == QLatin1String("studentName")) return QLatin1String("string");
        if (fieldName == QLatin1String("studentId")) return QLatin1String("int32");
        if (fieldName == QLatin1String("mathScore")) return QLatin1String("int32");
        if (fieldName == QLatin1String("englishScore")) return QLatin1String("int32");
        if (fieldName == QLatin1String("scienceScore")) return QLatin1String("int32");
        return QLatin1String("");
    }
    
    QList<QSharedPointer<IAnnotation>> annotations() const override {
        
        return QList<QSharedPointer<IAnnotation>>();
    }
    
    QList<QSharedPointer<void>> fieldAnnotations(const QString& fieldName) const override {
        if (fieldName == QLatin1String("studentName")) {
            return QList<QSharedPointer<void>>();
        }
        if (fieldName == QLatin1String("studentId")) {
            return QList<QSharedPointer<void>>();
        }
        if (fieldName == QLatin1String("mathScore")) {
            return QList<QSharedPointer<void>>();
        }
        if (fieldName == QLatin1String("englishScore")) {
            return QList<QSharedPointer<void>>();
        }
        if (fieldName == QLatin1String("scienceScore")) {
            return QList<QSharedPointer<void>>();
        }
        return QList<QSharedPointer<void>>();
    }
    
    QString description() const override {
        return "Generated from struct StudentScores";
    }
    
    QString fieldDescription(const QString& fieldName) const override {
        
        return QString();
    }
    
    QVariant value(const QString& fieldName) const override {
        if (fieldName == QLatin1String("studentName")) return QVariant::fromValue(studentName_);
        if (fieldName == QLatin1String("studentId")) return QVariant::fromValue(studentId_);
        if (fieldName == QLatin1String("mathScore")) return QVariant::fromValue(mathScore_);
        if (fieldName == QLatin1String("englishScore")) return QVariant::fromValue(englishScore_);
        if (fieldName == QLatin1String("scienceScore")) return QVariant::fromValue(scienceScore_);
        return QVariant();
    }
    
    void value(const QString& fieldName, const QVariant& value) override {
        if (fieldName == QLatin1String("studentName")) {
            studentName_ = value.value<QString>();
            return;
        }
        if (fieldName == QLatin1String("studentId")) {
            studentId_ = value.value<int32_t>();
            return;
        }
        if (fieldName == QLatin1String("mathScore")) {
            mathScore_ = value.value<int32_t>();
            return;
        }
        if (fieldName == QLatin1String("englishScore")) {
            englishScore_ = value.value<int32_t>();
            return;
        }
        if (fieldName == QLatin1String("scienceScore")) {
            scienceScore_ = value.value<int32_t>();
            return;
        }
    }
    
    // 特定于StudentScores的访问器
        // studentName字段的访问器
    QString getStudentName() const {
        return studentName_;
    }
    
    void setStudentName(const QString& value) {
        studentName_ = value;
    } 

        // studentId字段的访问器
    int32_t getStudentId() const {
        return studentId_;
    }
    
    void setStudentId(const int32_t& value) {
        studentId_ = value;
    } 

        // mathScore字段的访问器
    int32_t getMathScore() const {
        return mathScore_;
    }
    
    void setMathScore(const int32_t& value) {
        mathScore_ = value;
    } 

        // englishScore字段的访问器
    int32_t getEnglishScore() const {
        return englishScore_;
    }
    
    void setEnglishScore(const int32_t& value) {
        englishScore_ = value;
    } 

        // scienceScore字段的访问器
    int32_t getScienceScore() const {
        return scienceScore_;
    }
    
    void setScienceScore(const int32_t& value) {
        scienceScore_ = value;
    } 
    
protected:
    QString modelName() const override {
        return "StudentScores";
    }
    
private:
    QString studentName_;
    int32_t studentId_;
    int32_t mathScore_;
    int32_t englishScore_;
    int32_t scienceScore_;
    
    // 变更通知
    void notifyChange();
};



} // namespace examples::basic

