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


namespace examples::enums {


// LogLevel枚举
enum class LogLevel {
    DEBUG = 0,
    INFO = 1,
    WARNING = 2,
    ERROR = 3
};

// LogLevel辅助函数
namespace LogLevelHelper {
    // 将枚举值转换为字符串
    inline QString toString(LogLevel value) {
        switch (value) {
            case LogLevel::DEBUG:
                return QLatin1String("DEBUG");
            case LogLevel::INFO:
                return QLatin1String("INFO");
            case LogLevel::WARNING:
                return QLatin1String("WARNING");
            case LogLevel::ERROR:
                return QLatin1String("ERROR");
            default:
                return QString();
        }
    }
    
    // 将字符串转换为枚举值
    inline LogLevel fromString(const QString& str) {
        if (str == QLatin1String("DEBUG")) {
            return LogLevel::DEBUG;
        } else if (str == QLatin1String("INFO")) {
            return LogLevel::INFO;
        } else if (str == QLatin1String("WARNING")) {
            return LogLevel::WARNING;
        } else if (str == QLatin1String("ERROR")) {
            return LogLevel::ERROR;
        }
        return LogLevel::DEBUG;
    }
    
    // 获取所有枚举值的字符串表示
    inline QStringList allValues() {
        return QStringList() << QLatin1String("DEBUG") << QLatin1String("INFO") << QLatin1String("WARNING") << QLatin1String("ERROR");
    }
    
    // 获取所有枚举值的UI显示名称
    inline QStringList allDisplayNames() {
        return QStringList() << QLatin1String("详细的调试信息") << QLatin1String("一般信息") << QLatin1String("警告信息") << QLatin1String("错误信息");
    }
    
    // 获取整个枚举的注解
    inline QList<QSharedPointer<IAnnotation>> annotations() {
                QList<QSharedPointer<IAnnotation>> result;
                // TODO: 创建 yima.Window 注解实例
                return result;
    }
    
    // 获取特定枚举值的注解
    inline QList<QSharedPointer<IAnnotation>> valueAnnotations(LogLevel value) {
        switch (value) {
            case LogLevel::DEBUG: {
                QList<QSharedPointer<IAnnotation>> result;
                // TODO: 创建 yima.EnumValue 注解实例
                return result;
            }
            case LogLevel::INFO: {
                QList<QSharedPointer<IAnnotation>> result;
                // TODO: 创建 yima.EnumValue 注解实例
                return result;
            }
            case LogLevel::WARNING: {
                QList<QSharedPointer<IAnnotation>> result;
                // TODO: 创建 yima.EnumValue 注解实例
                return result;
            }
            case LogLevel::ERROR: {
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
        if (valueName == "DEBUG") {
                QList<QSharedPointer<IAnnotation>> result;
                // TODO: 创建 yima.EnumValue 注解实例
                return result;
        } else if (valueName == "INFO") {
                QList<QSharedPointer<IAnnotation>> result;
                // TODO: 创建 yima.EnumValue 注解实例
                return result;
        } else if (valueName == "WARNING") {
                QList<QSharedPointer<IAnnotation>> result;
                // TODO: 创建 yima.EnumValue 注解实例
                return result;
        } else if (valueName == "ERROR") {
                QList<QSharedPointer<IAnnotation>> result;
                // TODO: 创建 yima.EnumValue 注解实例
                return result;
        }
        return QList<QSharedPointer<IAnnotation>>();
    }
}


// HttpStatus枚举
enum class HttpStatus {
    OK = 200,
    BAD_REQUEST = 400,
    UNAUTHORIZED = 401,
    NOT_FOUND = 404,
    INTERNAL_SERVER_ERROR = 500
};

// HttpStatus辅助函数
namespace HttpStatusHelper {
    // 将枚举值转换为字符串
    inline QString toString(HttpStatus value) {
        switch (value) {
            case HttpStatus::OK:
                return QLatin1String("OK");
            case HttpStatus::BAD_REQUEST:
                return QLatin1String("BAD_REQUEST");
            case HttpStatus::UNAUTHORIZED:
                return QLatin1String("UNAUTHORIZED");
            case HttpStatus::NOT_FOUND:
                return QLatin1String("NOT_FOUND");
            case HttpStatus::INTERNAL_SERVER_ERROR:
                return QLatin1String("INTERNAL_SERVER_ERROR");
            default:
                return QString();
        }
    }
    
    // 将字符串转换为枚举值
    inline HttpStatus fromString(const QString& str) {
        if (str == QLatin1String("OK")) {
            return HttpStatus::OK;
        } else if (str == QLatin1String("BAD_REQUEST")) {
            return HttpStatus::BAD_REQUEST;
        } else if (str == QLatin1String("UNAUTHORIZED")) {
            return HttpStatus::UNAUTHORIZED;
        } else if (str == QLatin1String("NOT_FOUND")) {
            return HttpStatus::NOT_FOUND;
        } else if (str == QLatin1String("INTERNAL_SERVER_ERROR")) {
            return HttpStatus::INTERNAL_SERVER_ERROR;
        }
        return HttpStatus::OK;
    }
    
    // 获取所有枚举值的字符串表示
    inline QStringList allValues() {
        return QStringList() << QLatin1String("OK") << QLatin1String("BAD_REQUEST") << QLatin1String("UNAUTHORIZED") << QLatin1String("NOT_FOUND") << QLatin1String("INTERNAL_SERVER_ERROR");
    }
    
    // 获取所有枚举值的UI显示名称
    inline QStringList allDisplayNames() {
        return QStringList() << QLatin1String("OK") << QLatin1String("BAD_REQUEST") << QLatin1String("UNAUTHORIZED") << QLatin1String("NOT_FOUND") << QLatin1String("INTERNAL_SERVER_ERROR");
    }
    
    // 获取整个枚举的注解
    inline QList<QSharedPointer<IAnnotation>> annotations() {
                QList<QSharedPointer<IAnnotation>> result;
                // TODO: 创建 yima.Window 注解实例
                return result;
    }
    
    // 获取特定枚举值的注解
    inline QList<QSharedPointer<IAnnotation>> valueAnnotations(HttpStatus value) {
        switch (value) {
            case HttpStatus::OK: {
                QList<QSharedPointer<IAnnotation>> result;
                return result;
            }
            case HttpStatus::BAD_REQUEST: {
                QList<QSharedPointer<IAnnotation>> result;
                return result;
            }
            case HttpStatus::UNAUTHORIZED: {
                QList<QSharedPointer<IAnnotation>> result;
                return result;
            }
            case HttpStatus::NOT_FOUND: {
                QList<QSharedPointer<IAnnotation>> result;
                return result;
            }
            case HttpStatus::INTERNAL_SERVER_ERROR: {
                QList<QSharedPointer<IAnnotation>> result;
                return result;
            }
            default:
                return QList<QSharedPointer<IAnnotation>>();
        }
    }
    
    // 获取特定枚举值的注解（通过字符串）
    inline QList<QSharedPointer<IAnnotation>> valueAnnotations(const QString& valueName) {
        if (valueName == "OK") {
                QList<QSharedPointer<IAnnotation>> result;
                return result;
        } else if (valueName == "BAD_REQUEST") {
                QList<QSharedPointer<IAnnotation>> result;
                return result;
        } else if (valueName == "UNAUTHORIZED") {
                QList<QSharedPointer<IAnnotation>> result;
                return result;
        } else if (valueName == "NOT_FOUND") {
                QList<QSharedPointer<IAnnotation>> result;
                return result;
        } else if (valueName == "INTERNAL_SERVER_ERROR") {
                QList<QSharedPointer<IAnnotation>> result;
                return result;
        }
        return QList<QSharedPointer<IAnnotation>>();
    }
}


// LogEntry结构体

class MODEL_EXPORT LogEntryModel : public IModel {
public:
    LogEntryModel() = default;
    
    
    // 实现IModel接口
    QCborValue toCbor() const override {
        QCborMap map;
        map.insert(QLatin1String("message"), QCborValue(getMessage()));
        map.insert(QLatin1String("level"), QCborValue(static_cast<int>(getLevel())));
        map.insert(QLatin1String("timestamp"), QCborValue(getTimestamp()));
        return map;
    }
    
    void fromCbor(const QCborValue& cbor) override {
        QCborMap map = cbor.toMap();
        setMessage(map.value(QLatin1String("message")).toString());
        setLevel(static_cast<LogLevel>(map.value(QLatin1String("level")).toInteger()));
        setTimestamp(static_cast<int64_t>(map.value(QLatin1String("timestamp")).toInteger()));
    }
    
    QStringList fields() const override {
        return QStringList{QLatin1String("message"), QLatin1String("level"), QLatin1String("timestamp")};
    }
    
    QString fieldOriginTypeName(const QString& fieldName) const override {
        if (fieldName == QLatin1String("message")) return QLatin1String("string");
        if (fieldName == QLatin1String("level")) return QLatin1String("LogLevel");
        if (fieldName == QLatin1String("timestamp")) return QLatin1String("int64");
        return QLatin1String("");
    }
    
    QList<QSharedPointer<IAnnotation>> annotations() const override {
        
        return QList<QSharedPointer<IAnnotation>>();
    }
    
    QList<QSharedPointer<void>> fieldAnnotations(const QString& fieldName) const override {
        if (fieldName == QLatin1String("message")) {
            return QList<QSharedPointer<void>>();
        }
        if (fieldName == QLatin1String("level")) {
            return QList<QSharedPointer<void>>();
        }
        if (fieldName == QLatin1String("timestamp")) {
            return QList<QSharedPointer<void>>();
        }
        return QList<QSharedPointer<void>>();
    }
    
    QString description() const override {
        return "Generated from struct LogEntry";
    }
    
    QString fieldDescription(const QString& fieldName) const override {
        
        return QString();
    }
    
    QVariant value(const QString& fieldName) const override {
        if (fieldName == QLatin1String("message")) return QVariant::fromValue(message_);
        if (fieldName == QLatin1String("level")) return QVariant::fromValue(level_);
        if (fieldName == QLatin1String("timestamp")) return QVariant::fromValue(timestamp_);
        return QVariant();
    }
    
    void value(const QString& fieldName, const QVariant& value) override {
        if (fieldName == QLatin1String("message")) {
            message_ = value.value<QString>();
            return;
        }
        if (fieldName == QLatin1String("level")) {
            level_ = value.value<LogLevel>();
            return;
        }
        if (fieldName == QLatin1String("timestamp")) {
            timestamp_ = value.value<int64_t>();
            return;
        }
    }
    
    // 特定于LogEntry的访问器
        // message字段的访问器
    QString getMessage() const {
        return message_;
    }
    
    void setMessage(const QString& value) {
        message_ = value;
    } 

        // level字段的访问器
    LogLevel getLevel() const {
        return level_;
    }
    
    void setLevel(const LogLevel& value) {
        level_ = value;
    } 

        // timestamp字段的访问器
    int64_t getTimestamp() const {
        return timestamp_;
    }
    
    void setTimestamp(const int64_t& value) {
        timestamp_ = value;
    } 
    
protected:
    QString modelName() const override {
        return "LogEntry";
    }
    
private:
    QString message_;
    LogLevel level_;
    int64_t timestamp_;
    
    // 变更通知
    void notifyChange();
};



} // namespace examples::enums

