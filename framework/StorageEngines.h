#pragma once

#include "IStorageEngine.h"
#include <QtCore/QFile>
#include <QtCore/QJsonDocument>
#include <QtCore/QJsonObject>
#include <QtCore/QJsonArray>
#include <QtCore/QSettings>
#include <QtCore/QCborMap>
#include <QtCore/QCborValue>
#include <QtCore/QCborArray>

namespace ymf {

    // CBOR 存储引擎
    class FRAMEWORK_EXPORT CborStorageEngine : public IStorageEngine {
    public:
        bool save(const QString& filepath, const QCborValue& data) override {
            QFile file(filepath);
            if (!file.open(QIODevice::WriteOnly)) return false;
            file.write(data.toCbor());
            return true;
        }

        bool load(const QString& filepath, QCborValue& data) override {
            QFile file(filepath);
            if (!file.open(QIODevice::ReadOnly)) return false;
            data = QCborValue::fromCbor(file.readAll());
            return !data.isInvalid();
        }

        QString format() const override { return "cbor"; }
    };

    // JSON 存储引擎
    class FRAMEWORK_EXPORT JsonStorageEngine : public IStorageEngine {
    public:
        bool save(const QString& filepath, const QCborValue& data) override {
            QFile file(filepath);
            if (!file.open(QIODevice::WriteOnly)) return false;

            QJsonDocument doc;
            if (data.isMap()) {
            doc = QJsonDocument(data.toJsonValue().toObject());
            } else if (data.isArray()) {
                doc = QJsonDocument(data.toJsonValue().toArray());
            }
            file.write(doc.toJson(QJsonDocument::Compact));
            return true;
        }

        bool load(const QString& filepath, QCborValue& data) override {
            QFile file(filepath);
            if (!file.open(QIODevice::ReadOnly)) return false;
            
            QJsonDocument doc = QJsonDocument::fromJson(file.readAll());
            if (doc.isNull()) return false;
            data = QCborValue::fromJsonValue(doc.object());
            return true;
        }

        QString format() const override { return "json"; }
    };

    // INI 存储引擎
    class FRAMEWORK_EXPORT IniStorageEngine : public IStorageEngine {
    public:
        bool save(const QString& filepath, const QCborValue& data) override {
            QSettings settings(filepath, QSettings::IniFormat);
            writeToSettings(settings, "", data);
            settings.sync();
            return settings.status() == QSettings::NoError;
        }

        bool load(const QString& filepath, QCborValue& data) override {
            QSettings settings(filepath, QSettings::IniFormat);
            if (settings.status() != QSettings::NoError) return false;
            data = readFromSettings(settings, "");
            return true;
        }

        QString format() const override { return "ini"; }

    private:
        void writeToSettings(QSettings& settings, const QString& prefix, const QCborValue& value) {
            switch (value.type()) {
                case QCborValue::Map: {
                    QCborMap map = value.toMap();
                    for (auto it = map.begin(); it != map.end(); ++it) {
                        QString key = it.key().toString();
                        QString fullKey = prefix.isEmpty() ? key : prefix + "/" + key;
                        writeToSettings(settings, fullKey, it.value());
                    }
                    break;
                }
                default:
                    settings.setValue(prefix, value.toVariant());
                    break;
            }
        }

        QCborValue readFromSettings(QSettings& settings, const QString& prefix) {
            QCborMap result;
            QStringList childGroups = settings.childGroups();
            QStringList childKeys = settings.childKeys();

            if (childGroups.isEmpty() && childKeys.size() == 1) {
                return QCborValue::fromVariant(settings.value(prefix));
            }

            for (const QString& key : childGroups) {
                QString fullKey = prefix.isEmpty() ? key : prefix + "/" + key;
                settings.beginGroup(key);
                result.insert(key, readFromSettings(settings, fullKey));
                settings.endGroup();
            }

            for (const QString& key : childKeys) {
                result.insert(key, QCborValue::fromVariant(settings.value(key)));
            }

            return result;
        }
    };

    // Windows Registry 存储引擎
    class FRAMEWORK_EXPORT RegistryStorageEngine : public IStorageEngine {
    public:
        bool save(const QString& filepath, const QCborValue& data) override {
            QSettings settings(filepath, QSettings::NativeFormat);
            writeToRegistry(settings, "", data);
            settings.sync();
            return settings.status() == QSettings::NoError;
        }

        bool load(const QString& filepath, QCborValue& data) override {
            QSettings settings(filepath, QSettings::NativeFormat);
            if (settings.status() != QSettings::NoError) return false;
            data = readFromRegistry(settings, "");
            return true;
        }

        QString format() const override { return "registry"; }

    private:
        void writeToRegistry(QSettings& settings, const QString& prefix, const QCborValue& value) {
            switch (value.type()) {
                case QCborValue::Map: {
                    QCborMap map = value.toMap();
                    for (auto it = map.begin(); it != map.end(); ++it) {
                        QString key = it.key().toString();
                        QString fullKey = prefix.isEmpty() ? key : prefix + "\\" + key;
                        writeToRegistry(settings, fullKey, it.value());
                    }
                    break;
                }
                default:
                    settings.setValue(prefix, value.toVariant());
                    break;
            }
        }

        QCborValue readFromRegistry(QSettings& settings, const QString& prefix) {
            QCborMap result;
            QStringList childGroups = settings.childGroups();
            QStringList childKeys = settings.childKeys();

            if (childGroups.isEmpty() && childKeys.size() == 1) {
                return QCborValue::fromVariant(settings.value(prefix));
            }

            for (const QString& key : childGroups) {
                QString fullKey = prefix.isEmpty() ? key : prefix + "\\" + key;
                settings.beginGroup(key);
                result.insert(key, readFromRegistry(settings, fullKey));
                settings.endGroup();
            }

            for (const QString& key : childKeys) {
                result.insert(key, QCborValue::fromVariant(settings.value(key)));
            }

            return result;
        }
    };

} // namespace ymf
