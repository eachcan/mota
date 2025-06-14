
#pragma once

#include <QString>
#include <QVariant>
#include <QStringList>

namespace ymf {

#if defined(FRAMEWORK_LIBRARY)
#  define MODEL_EXPORT __declspec(dllexport)
#else
#  define MODEL_EXPORT __declspec(dllimport)
#endif

    // 注解接口
    class MODEL_EXPORT IAnnotation {
    public:
        virtual ~IAnnotation() = default;

        // 获取注解名称
        virtual QString name() const = 0;

        // 获取注解的参数
        virtual QVariant argumentValue(const QString& name) const = 0;

        // 获取注解的参数名称
        virtual QStringList fieldNames() const = 0;

        // 获取注解的UI注释
        virtual QStringList uiComments() const = 0;

        // 获取字段的UI注释
        virtual QStringList fieldUiComments(const QString& fieldName) const = 0;
    };

} // namespace ymf