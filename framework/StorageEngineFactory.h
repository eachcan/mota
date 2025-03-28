#pragma once

#include "framework_global.h"
#include "IStorageEngine.h"
#include <memory>
#include <QtCore/QString>
#include <QtCore/QMap>

namespace ymf {
        
    class FRAMEWORK_EXPORT StorageEngineFactory {
    public:
        static StorageEngineFactory* instance();

        // 获取指定格式的存储引擎实例
        std::shared_ptr<IStorageEngine> getEngine(const QString& format);

        // 注册存储引擎
        void registerEngine(const QString& format, std::shared_ptr<IStorageEngine> engine);

        // 检查是否支持指定格式
        bool supportsFormat(const QString& format) const;

    private:
        StorageEngineFactory() = default;
        ~StorageEngineFactory() = default;
        StorageEngineFactory(const StorageEngineFactory&) = delete;
        StorageEngineFactory& operator=(const StorageEngineFactory&) = delete;

        QMap<QString, std::shared_ptr<IStorageEngine>> m_engines;
        static StorageEngineFactory* s_instance;
    };

} // namespace ymf
