#pragma once
#include <string>
#include <memory>
#include "StorageEngine.h"

namespace mota {

class BaseModel {
public:
    virtual ~BaseModel() = default;
    virtual QCborValue toCbor() const = 0;
    virtual void fromCbor(const QCborValue& cbor) = 0;
    
protected:
    bool saveToFile(const std::string& filepath, const std::string& format);
    bool loadFromFile(const std::string& filepath, const std::string& format);
    
private:
    std::shared_ptr<IStorageEngine> getStorageEngine(const std::string& format);
};

class BaseBlock {
public:
    virtual ~BaseBlock() = default;
    virtual QCborValue toCbor() const = 0;
    virtual void fromCbor(const QCborValue& cbor) = 0;
};

} 