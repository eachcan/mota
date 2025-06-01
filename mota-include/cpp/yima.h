#pragma once

#include "IModel.h"
#include <QString>
#include <QStringList>
#include <QVariant>

using namespace ymf;

class IAnnotation;
class IBlock;

class StorageAnnotation : public IAnnotation {
public:
    // 获取注解名称
    QString name() const override {
        return "storage";
    }

    // 获取注解的参数
    QVariant argument(const QString& name) const override {
        if (name == "path") return getPath();
        if (name == "format") return getFormat();
        return QVariant();
    }

    // 获取注解的参数名称
    QStringList argumentNames() const override {
        return QStringList() << "path" << "format";
    }

    QString getPath() const {
        return m_path;
    }

    void setPath(QString value) {
        m_path = value;
    }

    QString getFormat() const {
        return m_format;
    }

    void setFormat(QString value) {
        m_format = value;
    }

private:
    QString m_path;
    QString m_format;
};

class WindowAnnotation : public IAnnotation {
public:
    // 获取注解名称
    QString name() const override {
        return "window";
    }

    // 获取注解的参数
    QVariant argument(const QString& name) const override {
        if (name == "title") return getTitle();
        if (name == "desc") return getDesc();
        return QVariant();
    }

    // 获取注解的参数名称
    QStringList argumentNames() const override {
        return QStringList() << "title" << "desc";
    }

    QString getTitle() const {
        return m_title;
    }

    void setTitle(QString value) {
        m_title = value;
    }

    QString getDesc() const {
        return m_desc;
    }

    void setDesc(QString value) {
        m_desc = value;
    }

private:
    QString m_title;
    QString m_desc;
};

class ScopeAnnotation : public IAnnotation {
public:
    // 获取注解名称
    QString name() const override {
        return "scope";
    }

    // 获取注解的参数
    QVariant argument(const QString& name) const override {
        if (name == "value") return getValue();
        return QVariant();
    }

    // 获取注解的参数名称
    QStringList argumentNames() const override {
        return QStringList() << "value";
    }

    QString getValue() const {
        return m_value;
    }

    void setValue(QString value) {
        m_value = value;
    }

private:
    QString m_value;
};

