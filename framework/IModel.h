#pragma once

// @completed

#include <QString>
#include <QVariant>
#include <QMap>
#include <QCborValue>
#include <QStringList>
#include <memory>
#include "IStorageEngine.h"
#include "ValidationResult.h"

#include "IAnnotation.h"
#include "IBlock.h"

#include "model_declares.h"

namespace ymf {

    class ApplicationContext;  // 前向声明

    #if defined(FRAMEWORK_LIBRARY)
    #  define MODEL_EXPORT __declspec(dllexport)
    #else
    #  define MODEL_EXPORT __declspec(dllimport)
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
        
        // 获取/设置限定符
        QString qualifier() const;
        void qualifier(const QString& qualifier);
        
        // 获取/设置 ApplicationContext
        void setContext(ApplicationContext* context);
        ApplicationContext* context() const;
        
        // 获取所有字段
        virtual QStringList fields() const = 0;
        
        // 获取字段类型
        virtual QString fieldOriginTypeName(const QString& fieldName) const = 0;

        // 获取模型注解
        virtual QList<QSharedPointer<IAnnotation>> modelAnnotations() const = 0;

        // 获取字段注解
        virtual QList<QSharedPointer<void>> fieldAnnotations(const QString& fieldName) const = 0;

        // 获取具体的注解
        QSharedPointer<IAnnotation> fieldAnnotation(const QString& fieldName) const;

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
        
        // 获取产品目录
        QString productDir() const;

        void productDir(const QString& dir);
        
    protected:

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

        QSharedPointer<IStorageEngine> storageEngine(const QString& format);

        Scope _scope = Scope::Global;
        bool _writable = false;
        QString _qualifier;
        QString _productDir;
        ApplicationContext* _context = nullptr;
        mutable ValidationResult _lastValidationResult;    // 缓存的验证结果
    };
} // namespace ymf
