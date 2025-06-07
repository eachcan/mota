#pragma once

// @completed

#include "IFactory.h"
#include <QMap>

namespace ymf {

    template<typename DriverType>
    class Factory : public IFactory {
    public:
        Factory() = default;
        virtual ~Factory() = default;

        QString getDriverTypeName() const override {
            return QString(typeid(DriverType).name());
        }

        void registerDriver(void* driver, const QString& name) override {
            if (!driver) return;
            auto typedDriver = static_cast<DriverType*>(driver);
            m_drivers[name] = typedDriver;
        }

        void unregisterDriver(const QString& name) override {
            m_drivers.remove(name);
        }

        void* getDriver(const QString& name) const override {
            return m_drivers.value(name);
        }

        QStringList getDriverList() const override {
            return m_drivers.keys();
        }

        bool hasDriver(const QString& name) const override {
            return m_drivers.contains(name);
        }

    private:
        QMap<QString, DriverType*> m_drivers;
    };

} // namespace ymf
