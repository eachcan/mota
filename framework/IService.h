#pragma once

// @completed

#include "framework_global.h"
#include <QString>

namespace ymf {

    class MODULE_EXPORT IService {
    public:
        virtual ~IService() = default;
        
        // 获取服务名称
        virtual QString getName() const = 0;
        
        // 服务初始化
        virtual void initialize() = 0;
        
        // 服务清理
        virtual void cleanup() = 0;
    };

} // namespace ymf
