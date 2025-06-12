#pragma once

// 此文件由 Mota 代码生成器自动生成
// 生成时间: 2025-06-11 23:24:41// 源文件: .\mota-include\yima.mota
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

using namespace ymf;

namespace yima {
// Storage注解
class MODEL_EXPORT StorageAnnotation : public IAnnotation {
public:
    StorageAnnotation() = default;
    
    // 实现IAnnotation接口
    QString name() const override {
        return "Storage";
    }
    
    QVariant argument(const QString& argumentName) const override {        if (argumentName == QLatin1String("path")) return QVariant::fromValue(path_);        if (argumentName == QLatin1String("format")) return QVariant::fromValue(format_);        return QVariant();
    }
    
    QStringList argumentNames() const override {
        return QStringList{QLatin1String("path"), QLatin1String("format")};
    }
    
    // 特定于Storage的访问器
    // path字段的访问器
    QString getPath() const {
        return path_;
    }
    
    void setPath(const QString& value) {
        path_ = value;
    } 
    // format字段的访问器
    QString getFormat() const {
        return format_;
    }
    
    void setFormat(const QString& value) {
        format_ = value;
    } 
private:QStringpath_;QStringformat_;};
Q_DECLARE_METATYPE(StorageAnnotation)// Window注解
class MODEL_EXPORT WindowAnnotation : public IAnnotation {
public:
    WindowAnnotation() = default;
    
    // 实现IAnnotation接口
    QString name() const override {
        return "Window";
    }
    
    QVariant argument(const QString& argumentName) const override {        if (argumentName == QLatin1String("title")) return QVariant::fromValue(title_);        if (argumentName == QLatin1String("desc")) return QVariant::fromValue(desc_);        return QVariant();
    }
    
    QStringList argumentNames() const override {
        return QStringList{QLatin1String("title"), QLatin1String("desc")};
    }
    
    // 特定于Window的访问器
    // title字段的访问器
    QString getTitle() const {
        return title_;
    }
    
    void setTitle(const QString& value) {
        title_ = value;
    } 
    // desc字段的访问器
    QString getDesc() const {
        return desc_;
    }
    
    void setDesc(const QString& value) {
        desc_ = value;
    } 
private:QStringtitle_;QStringdesc_;};
Q_DECLARE_METATYPE(WindowAnnotation)// Scope注解
class MODEL_EXPORT ScopeAnnotation : public IAnnotation {
public:
    ScopeAnnotation() = default;
    
    // 实现IAnnotation接口
    QString name() const override {
        return "Scope";
    }
    
    QVariant argument(const QString& argumentName) const override {        if (argumentName == QLatin1String("value")) return QVariant::fromValue(value_);        return QVariant();
    }
    
    QStringList argumentNames() const override {
        return QStringList{QLatin1String("value")};
    }
    
    // 特定于Scope的访问器
    // value字段的访问器
    QString getValue() const {
        return value_;
    }
    
    void setValue(const QString& value) {
        value_ = value;
    } 
private:QStringvalue_;};
Q_DECLARE_METATYPE(ScopeAnnotation)// IniGroup注解
class MODEL_EXPORT IniGroupAnnotation : public IAnnotation {
public:
    IniGroupAnnotation() = default;
    
    // 实现IAnnotation接口
    QString name() const override {
        return "IniGroup";
    }
    
    QVariant argument(const QString& argumentName) const override {        if (argumentName == QLatin1String("value")) return QVariant::fromValue(value_);        return QVariant();
    }
    
    QStringList argumentNames() const override {
        return QStringList{QLatin1String("value")};
    }
    
    // 特定于IniGroup的访问器
    // value字段的访问器
    QString getValue() const {
        return value_;
    }
    
    void setValue(const QString& value) {
        value_ = value;
    } 
private:QStringvalue_;};
Q_DECLARE_METATYPE(IniGroupAnnotation)}
 
