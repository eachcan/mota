#include "BaseModel.h"
#include <memory>

namespace mota {

std::shared_ptr<IStorageEngine> BaseModel::getStorageEngine(const std::string& format) {
    return StorageEngineManager::instance().getEngine(format);
}

bool BaseModel::saveToFile(const std::string& filepath, const std::string& format) {
    auto engine = getStorageEngine(format);
    if (!engine) {
        return false;
    }
    
    // 将当前对象序列化为 QCborValue
    QCborValue data = toCbor();
    
    // 使用存储引擎保存
    return engine->save(filepath, data);
}

bool BaseModel::loadFromFile(const std::string& filepath, const std::string& format) {
    auto engine = getStorageEngine(format);
    if (!engine) {
        return false;
    }
    
    // 使用存储引擎加载
    QCborValue data = engine->load(filepath);
    if (data.isNull()) {
        return false;
    }
    
    // 将数据反序列化到当前对象
    fromCbor(data);
    return true;
}

} 