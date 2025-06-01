#pragma once

// @completed

#include <QString>
#include <QVariant>
#include <QVariantMap>
#include <memory>
#include "ValidationResult.h"

namespace ymf {

    class IModel;

    // 模型验证器基类
    class IModelValidator {
    public:
        virtual ~IModelValidator() = default;

        // 验证模型，由派生类实现
        virtual ValidationResult validate(const IModel* model) = 0;

    protected:
        // 辅助方法：检查数值范围
        template<typename T>
        void validateRange(const QString& field, const T& value, const T& min, const T& max, ValidationResult& result) {
            if (value < min || value > max) {
                result.addError(field, 
                    QString("Value must be between %1 and %2").arg(min).arg(max));
            }
        }

        // 辅助方法：检查是否在选项列表中
        void validateOptions(const QString& field, const QString& value, const QStringList& options, ValidationResult& result) {
            if (!options.contains(value)) {
                result.addError(field, "Invalid option selected");
            }
        }

        // 辅助方法：检查字符串长度
        void validateLength(const QString& field, const QString& value, int minLength, int maxLength, ValidationResult& result) {
            if (value.length() < minLength || value.length() > maxLength) {
                result.addError(field,
                    QString("Length must be between %1 and %2").arg(minLength).arg(maxLength));
            }
        }

        // 辅助方法：检查必填字段
        void validateRequired(const QString& field, const QVariant& value, ValidationResult& result) {
            if (value.isNull() || !value.isValid() || 
                (value.typeId() == QMetaType::QString && value.toString().isEmpty())) {
                result.addError(field, "This field is required");
            }
        }

        // 辅助方法：检查正则表达式
        void validateRegex(const QString& field, const QString& value, const QRegularExpression& regex, ValidationResult& result) {
            if (!regex.match(value).hasMatch()) {
                result.addError(field, "Invalid format");
            }
        }

        // 辅助方法：检查数值是否大于指定值
        template<typename T>
        void validateGreaterThan(const QString& field, const T& value, const T& min, ValidationResult& result) {
            if (value <= min) {
                result.addError(field, 
                    QString("Value must be greater than %1").arg(min));
            }
        }

        // 辅助方法：检查数值是否小于指定值
        template<typename T>
        void validateLessThan(const QString& field, const T& value, const T& max, ValidationResult& result) {
            if (value >= max) {
                result.addError(field, 
                    QString("Value must be less than %1").arg(max));
            }
        }
    };

} // namespace ymf
