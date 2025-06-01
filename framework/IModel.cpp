#include "IModel.h"
#include "ApplicationContext.h"
#include "IModelValidator.h"
#include "StorageEngineFactory.h"
#include <QCoreApplication>
#include <QDir>
#include <QFileInfo>
#include <typeinfo>
#include <typeindex>

namespace ymf {
    IModel::IModel() 
        : m_scope(Scope::Global)
        , m_writable(false)
    {
    }

    bool IModel::save() {
        if (!writable()) return false;
        
        // 先保存数据
        bool success = saveToFile(resolvePath(), "cbor"); // 默认使用 cbor 格式
        
        // 如果保存成功且有 context，同步到只读模型
        if (success && m_context) {
            ModelInfoIndex key = m_context->makeModelKey(typeid(*this), m_qualifier);
            m_context->syncModelData(key);
        }
        
        return success;
    }

    bool IModel::load() {
        return loadFromFile(resolvePath(), "cbor"); // 默认使用 cbor 格式
    }

    bool IModel::saveToFile(const QString& filepath, const QString& format) {
        auto engine = storageEngine(format);
        if (!engine) return false;
        return engine->save(filepath, toCbor());
    }

    bool IModel::loadFromFile(const QString& filepath, const QString& format) {
        auto engine = storageEngine(format);
        if (!engine) return false;
        
        QCborValue data;
        if (!engine->load(filepath, data)) return false;
        
        fromCbor(data);
        return true;
    }

    QString IModel::resolvePath() const {
        // 获取存储注解
        QString format = "cbor"; // 默认格式
        QString path = ""; // 默认路径为空
        
        // 尝试从注解中获取存储路径和格式
        auto storageAnnotation = modelStorageAnnotation();
        if (storageAnnotation) {
            path = storageAnnotation->path;
            format = storageAnnotation->format;
        }
        
        QString result = path;
        
        // 如果路径为空，使用默认路径
        if (result.isEmpty()) {
            // 基本路径：{config}
            result = configDir();
            
            // 如果是产品配置，添加产品目录
            if (m_scope == Scope::Product) {
                result = QString("%1/%2").arg(result, productDir());
            }
            
            // 添加模型名
            result = QString("%1/%2").arg(result, modelName());
            
            // 如果有限定符，添加到文件名中
            if (!m_qualifier.isEmpty()) {
                result = QString("%1-%2").arg(result, m_qualifier);
            }
            
            // 添加扩展名
            result = QString("%1.%2").arg(result, format);
        }
        
        // 替换变量
        result.replace("${app}", appDir());
        result.replace("${config}", configDir());
        result.replace("${product}", productDir());
        result.replace("${model}", modelName());
        result.replace("${qualifier}", m_qualifier.isEmpty() ? "default" : m_qualifier);
        
        // 确保目录存在
        QFileInfo fileInfo(result);
        QDir dir = fileInfo.dir();
        if (!dir.exists()) {
            dir.mkpath(".");
        }
        
        return result;
    }

    QString IModel::configDir() const {
        return QString("%1/config").arg(appDir());
    }

    QString IModel::appDir() const {
        return QCoreApplication::applicationDirPath();
    }

    QString IModel::productDir() const {
        return m_context->getProductName();
    }

    bool IModel::writable() const {
        return m_writable;
    }

    void IModel::writable(bool writable) {
        m_writable = writable;
    }

    Scope IModel::scope() const {
        return m_scope;
    }

    void IModel::scope(Scope scope) {
        m_scope = scope;
    }

    QString IModel::qualifier() const {
        return m_qualifier;
    }

    void IModel::qualifier(const QString& qualifier) {
        m_qualifier = qualifier;
    }

    void IModel::setContext(ApplicationContext* context) {
        m_context = context;
    }

    ApplicationContext* IModel::context() const {
        return m_context;
    }

    std::shared_ptr<StorageAnnotation> IModel::modelStorageAnnotation() const
    {
        auto annotations = modelAnnotations();
        for (const auto& annotation : annotations) {
            auto result = AnnotationTypeHelper::as<StorageAnnotation>(annotation);
            if (result) {
                return result;
            }
        }
        return nullptr;
    }

    std::shared_ptr<ScopeAnnotation> IModel::modelScopeAnnotation() const
    {
        auto annotations = modelAnnotations();
        for (const auto& annotation : annotations) {
            auto result = AnnotationTypeHelper::as<ScopeAnnotation>(annotation);
            if (result) {
                return result;
            }
        }
        return nullptr;
    }

    std::shared_ptr<WindowAnnotation> IModel::modelWindowAnnotation() const
    {
        auto annotations = modelAnnotations();
        for (const auto& annotation : annotations) {
            auto result = AnnotationTypeHelper::as<WindowAnnotation>(annotation);
            if (result) {
                return result;
            }
        }
        return nullptr;
    }

    std::shared_ptr<IStorageEngine> IModel::storageEngine(const QString& format) {
        return StorageEngineFactory::instance()->getEngine(format);
    }

    ValidationResult IModel::validate() const {
        auto validators = m_context ? m_context->getValidators(typeid(*this)) : QList<std::shared_ptr<IModelValidator>>();
        
        m_lastValidationResult = ValidationResult::success();
        
        for (auto& validator : validators) {
            auto result = validator->validate(this);
            if (!result.isValid()) {
                m_lastValidationResult.addErrors(result);
            }
        }
        
        return m_lastValidationResult;
    }

    QList<ValidationError> IModel::validationErrors() const {
        return m_lastValidationResult.errors();
    }

} // namespace ymf
