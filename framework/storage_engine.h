#pragma once
#include <string>
#include <memory>
#include <map>
#include <QCborValue>

namespace mota {

class IStorageEngine {
public:
    virtual ~IStorageEngine() = default;
    virtual bool save(const std::string& filepath, const QCborValue& data) = 0;
    virtual QCborValue load(const std::string& filepath) = 0;
};

class StorageEngineManager {
public:
    static StorageEngineManager& instance();
    
    std::shared_ptr<IStorageEngine> getEngine(const std::string& format);
    
private:
    StorageEngineManager() = default;
    ~StorageEngineManager() = default;
    StorageEngineManager(const StorageEngineManager&) = delete;
    StorageEngineManager& operator=(const StorageEngineManager&) = delete;
    
    std::map<std::string, std::shared_ptr<IStorageEngine>> engines_;
};

class CborStorageEngine : public IStorageEngine {
public:
    bool save(const std::string& filepath, const QCborValue& data) override;
    QCborValue load(const std::string& filepath) override;
};

class JsonStorageEngine : public IStorageEngine {
public:
    bool save(const std::string& filepath, const QCborValue& data) override;
    QCborValue load(const std::string& filepath) override;
};

class IniStorageEngine : public IStorageEngine {
public:
    bool save(const std::string& filepath, const QCborValue& data) override;
    QCborValue load(const std::string& filepath) override;
};

} 