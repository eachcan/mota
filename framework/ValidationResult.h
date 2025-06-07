#pragma once

// @completed

#include <QString>
#include <QList>

namespace ymf {

    // 验证错误
    class ValidationError {
    public:
        // 构造函数直接移动字符串
        ValidationError(QString field, QString message)
            : m_field(std::move(field))
            , m_message(std::move(message)) {}

        // 返回常量引用
        const QString& field() const { return m_field; }
        const QString& message() const { return m_message; }

    private:
        QString m_field;
        QString m_message;
    };

    // 验证结果
    class ValidationResult {
    public:
        // 创建成功结果
        static ValidationResult success() {
            return ValidationResult();
        }

        // 创建错误结果
        static ValidationResult error(QString field, QString message) {
            ValidationResult result;
            result.addError(std::move(field), std::move(message));
            return result;
        }

        // 添加错误
        void addError(QString field, QString message) {
            m_errors.emplace_back(std::move(field), std::move(message));
        }

        // 添加其他验证结果的错误
        void addErrors(const ValidationResult& other) {
            for (const auto& error : other.m_errors) {
                m_errors.emplace_back(QString(error.field()), QString(error.message()));
            }
        }

        // 判断是否有效
        bool isValid() const {
            return m_errors.isEmpty();
        }

        // 获取所有错误
        const QList<ValidationError>& errors() const {
            return m_errors;
        }

        // 获取第一个错误消息
        const QString& firstErrorMessage() const {
            static const QString empty;
            return m_errors.isEmpty() ? empty : m_errors.first().message();
        }

        // 获取指定字段的错误消息
        QString fieldError(const QString& field) const {
            for (const auto& error : m_errors) {
                if (error.field() == field) {
                    return error.message();
                }
            }
            return QString();
        }

    private:
        QList<ValidationError> m_errors;
    };

} // namespace ymf
