#pragma once

// @completed

#include "framework_global.h"
#include <QString>
#include <QCborValue>

namespace ymf {

    class FRAMEWORK_EXPORT IStorageEngine {
    public:
        virtual ~IStorageEngine() = default;

        // 保存数据到文件
        virtual bool save(const QString& filepath, const QCborValue& data) = 0;

        // 从文件加载数据
        virtual bool load(const QString& filepath, QCborValue& data) = 0;

        // 获取存储引擎支持的文件格式
        virtual QString format() const = 0;
    };

} // namespace ymf
