#include "StorageEngineFactory.h"
#include "StorageEngines.h"

namespace ymf {

    StorageEngineFactory* StorageEngineFactory::s_instance = nullptr;

    StorageEngineFactory* StorageEngineFactory::instance() {
        if (!s_instance) {
            s_instance = new StorageEngineFactory();
            
            // 注册内置的存储引擎
            s_instance->registerEngine("cbor", std::make_shared<CborStorageEngine>());
            s_instance->registerEngine("json", std::make_shared<JsonStorageEngine>());
            s_instance->registerEngine("ini", std::make_shared<IniStorageEngine>());
            s_instance->registerEngine("winreg", std::make_shared<RegistryStorageEngine>());
        }
        return s_instance;
    }

    std::shared_ptr<IStorageEngine> StorageEngineFactory::getEngine(const QString& format) {
        if (format.isEmpty() || !supportsFormat(format)) {
            return m_engines.value("cbor");
        }
        
        return m_engines.value(format);
    }

    void StorageEngineFactory::registerEngine(const QString& format, std::shared_ptr<IStorageEngine> engine) {
        if (engine && !format.isEmpty()) {
            m_engines[format] = engine;
        }
    }

    bool StorageEngineFactory::supportsFormat(const QString& format) const {
        return m_engines.contains(format);
    }

} // namespace ymf
