#pragma once

// @completed

#include "framework_global.h"
#include <QString>
#include <QVariant>
#include <QMap>
#include <QCborValue>
#include <memory>
#include "IStorageEngine.h"
#include "ValidationResult.h"

#include "model_declares.h"

namespace ymf {

    class ApplicationContext;  // 前向声明

#if defined(FRAMEWORK_LIBRARY)
#  define MODEL_EXPORT Q_DECL_EXPORT
#else
#  define MODEL_EXPORT Q_DECL_IMPORT
#endif

    class MODEL_EXPORT IModel {
    public:

        IModel();
        virtual ~IModel() = default;
        
        // 序列化/反序列化接口
        virtual QCborValue toCbor() const = 0;
        virtual void fromCbor(const QCborValue& cbor) = 0;
        
        // 存储接口
        bool save();    // 根据模型配置自动保存
        bool load();    // 根据模型配置自动加载
        bool saveToFile(const QString& filepath, const QString& format);
        bool loadFromFile(const QString& filepath, const QString& format);
        
        // 模型是否可写
        bool writable() const;
        void writable(bool writable);
        
        // 获取模型作用域
        Scope scope() const;
        void scope(Scope scope);
        
        // 获取/设置限定符
        QString qualifier() const;
        void qualifier(const QString& qualifier);
        
        // 获取/设置 ApplicationContext
        void setContext(ApplicationContext* context);
        ApplicationContext* context() const;
        
        // 获取所有字段
        virtual QStringList fields() const = 0;
        
        // 获取字段类型
        virtual QString fieldType(const QString& fieldName) const = 0;

        // 获取模型注解
        virtual QList<std::shared_ptr<void>> modelAnnotations() const = 0;

        // 获取模型的 StorageAnnotation 注解
        std::shared_ptr<StorageAnnotation> modelStorageAnnotation() const;

        // 获取模型的 ScopeAnnotation 注解
        std::shared_ptr<ScopeAnnotation> modelScopeAnnotation() const;

        // 获取模型的 WindowAnnotation 注解
        std::shared_ptr<WindowAnnotation> modelWindowAnnotation() const;

        // 获取字段注解
        virtual QList<std::shared_ptr<void>> fieldAnnotations(const QString& fieldName) const = 0;

        // 获取具体的注解
        template <typename T>
        std::shared_ptr<T> fieldAnnotation(const QString& fieldName) const;

        // 获取模型的注释
        virtual QString description() const = 0;

        // 获取字段的注释
        virtual QString fieldDescription(const QString& fieldName) const = 0;
        
        // 获取字段值
        virtual QVariant value(const QString& fieldName) const = 0;
        
        // 设置字段值
        virtual void value(const QString& fieldName, const QVariant& value) = 0;
        
        // 验证模型
        ValidationResult validate() const;

        // 获取验证错误
        QList<ValidationError> validationErrors() const;
        
    protected:
        // 获取产品目录
        virtual QString productDir() const;

        // 获取模型名
        virtual QString modelName() const = 0;
        
        // 获取配置目录
        QString configDir() const;

        // 获取应用安装目录
        QString appDir() const;

    private:
        friend class ApplicationContext;

        // 解析存储路径
        QString resolvePath() const;

        std::shared_ptr<IStorageEngine> storageEngine(const QString& format);

        Scope m_scope = Scope::Global;
        bool m_writable = false;
        QString m_qualifier;
        ApplicationContext* m_context = nullptr;
        mutable ValidationResult m_lastValidationResult;    // 缓存的验证结果
    };

    // BaseBlock 保持独立
    class MODEL_EXPORT BaseBlock {
    public:
        virtual ~BaseBlock() = default;
        virtual QCborValue toCbor() const = 0;
        virtual void fromCbor(const QCborValue& cbor) = 0;

        // 获取块名称
        virtual QString name() const = 0;

        // 获取所有的字段
        virtual QStringList fields() const = 0;

        // 获取字段类型
        virtual QString fieldType(const QString& fieldName) const = 0;

        // 获取字段注解
        virtual QList<std::shared_ptr<void>> fieldAnnotation(const QString& fieldName) const = 0;

        // 获取块的注释
        virtual QString description() const = 0;

        // 获取字段的注释
        virtual QString fieldDescription(const QString& fieldName) const = 0;

        // 获取字段值
        virtual QVariant value(const QString& fieldName) const = 0;

        // 设置字段值
        virtual void value(const QString& fieldName, const QVariant& value) = 0;
    };

    // 注解接口
    class MODEL_EXPORT IAnnotation {
    public:
        virtual ~IAnnotation() = default;

        // 获取注解名称
        virtual QString name() const = 0;

        // 获取注解的参数
        virtual QList<std::shared_ptr<void>> arguments() const = 0;

        // 获取注解的参数
        template <typename T>
        std::shared_ptr<T> argument(const QString& name) const;

        // 获取注解的参数名称
        QStringList argumentNames() const;

        // 获取注解的参数值
        template <typename T>
        T argumentValue(const QString& name) const;
    };

} // namespace ymf
