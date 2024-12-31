#include "storage_engine.h"
#include <QFile>
#include <QJsonDocument>
#include <QSettings>

namespace mota {

StorageEngineManager& StorageEngineManager::instance() {
    static StorageEngineManager instance;
    return instance;
}

std::shared_ptr<IStorageEngine> StorageEngineManager::getEngine(const std::string& format) {
    // 如果引擎已存在，直接返回
    auto it = engines_.find(format);
    if (it != engines_.end()) {
        return it->second;
    }
    
    // 创建新的引擎实例
    std::shared_ptr<IStorageEngine> engine;
    if (format == "cbor") {
        engine = std::make_shared<CborStorageEngine>();
    } else if (format == "json") {
        engine = std::make_shared<JsonStorageEngine>();
    } else if (format == "ini") {
        engine = std::make_shared<IniStorageEngine>();
    }
    
    // 存储并返回新创建的引擎
    if (engine) {
        engines_[format] = engine;
    }
    return engine;
}

// CborStorageEngine implementation
bool CborStorageEngine::save(const std::string& filepath, const QCborValue& data) {
    QFile file(QString::fromStdString(filepath));
    if (!file.open(QIODevice::WriteOnly))
        return false;
        
    QCborValue::write(data, &file);
    return true;
}

QCborValue CborStorageEngine::load(const std::string& filepath) {
    QFile file(QString::fromStdString(filepath));
    if (!file.open(QIODevice::ReadOnly))
        return QCborValue();
        
    return QCborValue::fromCbor(file.readAll());
}

// JsonStorageEngine和IniStorageEngine的实现类似...

} 