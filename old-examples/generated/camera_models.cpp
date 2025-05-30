#include "generated/camera_models.h"
#include <QCborMap>
#include <QCborArray>

namespace myapp::camera {

// BaseTaskBlock 实现
QCborValue BaseTaskBlock::toCbor() const {
    QCborMap map;
    map.insert("taskId", taskId);
    map.insert("name", QString::fromStdString(name));
    map.insert("priority", priority);
    return map;
}

void BaseTaskBlock::fromCbor(const QCborValue& cbor) {
    auto map = cbor.toMap();
    taskId = map["taskId"].toInteger();
    name = map["name"].toString().toStdString();
    priority = map["priority"].toInteger();
}

// CameraTaskBlock 实现 - 继承自 BaseTaskBlock
QCborValue CameraTaskBlock::toCbor() const {
    // 先获取父类的序列化结果
    QCborMap map = BaseTaskBlock::toCbor().toMap();
    // 添加子类的字段
    map.insert("type", static_cast<int>(type));
    map.insert("position", position);
    if(refPosition) {
        map.insert("refPosition", *refPosition);
    }
    return map;
}

void CameraTaskBlock::fromCbor(const QCborValue& cbor) {
    // 先调用父类的反序列化
    BaseTaskBlock::fromCbor(cbor);
    
    auto map = cbor.toMap();
    type = static_cast<CameraType>(map["type"].toInteger());
    position = map["position"].toInteger();
    if(map.contains("refPosition")) {
        refPosition = map["refPosition"].toInteger();
    } else {
        refPosition = std::nullopt;
    }
}

// DeviceModel 实现
QCborValue DeviceModel::toCbor() const {
    QCborMap map;
    map.insert("id", id);
    map.insert("name", QString::fromStdString(name));
    map.insert("enabled", enabled);
    return map;
}

void DeviceModel::fromCbor(const QCborValue& cbor) {
    auto map = cbor.toMap();
    id = map["id"].toInteger();
    name = map["name"].toString().toStdString();
    enabled = map["enabled"].toBool();
}

bool DeviceModel::save() {
    return saveToFile("${app_path}/device-base.cbor", "cbor");
}

void DeviceModel::reset() {
    loadFromFile("${app_path}/device-base.cbor", "cbor");
}

// CameraModel 实现 - 继承自 DeviceModel
QCborValue CameraModel::toCbor() const {
    // 获取父类序列化结果
    QCborMap map = DeviceModel::toCbor().toMap();
    // 添加子类字段
    map.insert("type", static_cast<int>(type));
    map.insert("position", position);
    if(refPosition) {
        map.insert("refPosition", *refPosition);
    }
    return map;
}

void CameraModel::fromCbor(const QCborValue& cbor) {
    DeviceModel::fromCbor(cbor);
    
    auto map = cbor.toMap();
    type = static_cast<CameraType>(map["type"].toInteger());
    position = map["position"].toInteger();
    if(map.contains("refPosition")) {
        refPosition = map["refPosition"].toInteger();
    } else {
        refPosition = std::nullopt;
    }
}

bool CameraModel::save() {
    return saveToFile("${app_path}/${qualifier}-camera.cbor", "cbor");
}

void CameraModel::reset() {
    loadFromFile("${app_path}/${qualifier}-camera.cbor", "cbor");
}

// CameraTaskConfigModel 实现 - 继承自 BaseModel 和 CameraTaskBlock
QCborValue CameraTaskConfigModel::toCbor() const {
    // 获取 CameraTaskBlock 的序列化结果
    QCborMap map = CameraTaskBlock::toCbor().toMap();
    
    // 添加自身的字段
    map.insert("timeout", timeout);
    map.insert("retryCount", retryCount);
    
    // 序列化 repeated 字段
    QCborArray paramsArray;
    for(const auto& param : params) {
        paramsArray.append(QString::fromStdString(param));
    }
    map.insert("params", paramsArray);
    
    return map;
}

void CameraTaskConfigModel::fromCbor(const QCborValue& cbor) {
    // 先调用 CameraTaskBlock 的反序列化
    CameraTaskBlock::fromCbor(cbor);
    
    auto map = cbor.toMap();
    timeout = map["timeout"].toInteger();
    retryCount = map["retryCount"].toInteger();
    
    // 反序列化 repeated 字段
    params.clear();
    auto paramsArray = map["params"].toArray();
    for(const auto& param : paramsArray) {
        params.push_back(param.toString().toStdString());
    }
}

bool CameraTaskConfigModel::save() {
    return saveToFile("${app_path}/${qualifier}-camera-task.cbor", "cbor");
}

void CameraTaskConfigModel::reset() {
    loadFromFile("${app_path}/${qualifier}-camera-task.cbor", "cbor");
}

// TaskMapModel 实现 - 包含 map 类型字段
QCborValue TaskMapModel::toCbor() const {
    QCborMap map;
    
    // 序列化 map 字段
    QCborMap tasksMap;
    for(const auto& [key, value] : tasks) {
        tasksMap.insert(QString::fromStdString(key), value.toCbor());
    }
    map.insert("tasks", tasksMap);
    
    return map;
}

void TaskMapModel::fromCbor(const QCborValue& cbor) {
    auto map = cbor.toMap();
    
    // 反序列化 map 字段
    tasks.clear();
    auto tasksMap = map["tasks"].toMap();
    for(auto it = tasksMap.begin(); it != tasksMap.end(); ++it) {
        CameraTaskConfigModel config;
        config.fromCbor(it.value());
        tasks[it.key().toString().toStdString()] = config;
    }
}

bool TaskMapModel::save() {
    return saveToFile("${app_path}/${qualifier}-task-map.cbor", "cbor");
}

void TaskMapModel::reset() {
    loadFromFile("${app_path}/${qualifier}-task-map.cbor", "cbor");
}

} 