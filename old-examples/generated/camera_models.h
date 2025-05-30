#pragma once
#include "base_model.h"
#include <optional>
#include <vector>
#include <map>

namespace myapp::camera {

enum class CameraType {
    Normal = 0,
    HighSpeed = 1,
    HD = 2
};

class BaseTaskBlock : public mota::BaseBlock {
public:
    int32_t taskId{0};
    std::string name;
    int8_t priority{0};

    QCborValue toCbor() const override;
    void fromCbor(const QCborValue& cbor) override;
};

class CameraTaskBlock : public BaseTaskBlock {
public:
    CameraType type{CameraType::Normal};
    int32_t position{0};
    std::optional<int32_t> refPosition;

    QCborValue toCbor() const override;
    void fromCbor(const QCborValue& cbor) override;
};

class DeviceModel : public mota::BaseModel {
public:
    int32_t id{0};
    std::string name;
    bool enabled{true};

    QCborValue toCbor() const override;
    void fromCbor(const QCborValue& cbor) override;
    
    bool save();
    void reset();
};

class CameraModel : public DeviceModel {
public:
    CameraType type{CameraType::Normal};
    int32_t position{0};
    std::optional<int32_t> refPosition;

    QCborValue toCbor() const override;
    void fromCbor(const QCborValue& cbor) override;
    
    bool save();
    void reset();
};

class AdvancedCameraModel : public CameraModel {
public:
    float exposureTime{1.0f};
    int32_t iso{100};
    bool autoFocus{true};

    QCborValue toCbor() const override;
    void fromCbor(const QCborValue& cbor) override;
    
    bool save();
    void reset();
};

class CameraTaskConfigModel : public mota::BaseModel, public CameraTaskBlock {
public:
    int32_t timeout{5000};
    int8_t retryCount{3};
    std::vector<std::string> params;

    QCborValue toCbor() const override;
    void fromCbor(const QCborValue& cbor) override;
    
    bool save();
    void reset();
};

class TaskMapModel : public mota::BaseModel {
public:
    std::map<std::string, CameraTaskConfigModel> tasks;

    QCborValue toCbor() const override;
    void fromCbor(const QCborValue& cbor) override;
    
    bool save();
    void reset();
};

} 