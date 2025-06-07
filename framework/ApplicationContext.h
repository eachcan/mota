#pragma once

#include "framework_global.h"
#include "Factory.h"
#include "IService.h"
#include "IModel.h"

#include <QObject>
#include <QString>
#include <QMap>
#include <QSet>
#include <memory>
#include <typeindex>
#include <type_traits>
#include <QMutex>

namespace ymf {
    // 前向声明
    class IModule;
    class IModelValidator;


    // 驱动信息
    struct DriverInfo {
        std::type_index factoryType;
        QString name;
    };

    // 记录模块注册的资源
    struct ModuleResources {
        QSet<std::type_index> factories;      // 工厂类型
        QMap<std::type_index, QString> drivers; // 工厂驱动
        QSet<std::type_index> modelTypes;         // 模型类型
        QSet<QString> services;               // 服务名称
        QSet<QString> dependencies;           // 依赖的模块

        ModuleResources() = default;
        ModuleResources(const ModuleResources&) = default;
        ModuleResources& operator=(const ModuleResources&) = default;
        ModuleResources(ModuleResources&&) = default;
        ModuleResources& operator=(ModuleResources&&) = default;
    };

    // 模块状态
    enum class ModuleState {
        Ready,          // 已加载且可用
        Pending,    // 等待依赖
        Failed          // 加载失败
    };

    // 待处理模块
    struct ModuleInfo {
        IModule* module;                      // 模块实例
        ModuleState state;                    // 当前状态
        QString error;                        // 错误信息（如果失败）
        QSet<QString> missingDeps;           // 缺失的依赖
    };

    // 模型信息索引
    struct ModelInfoIndex {
        std::type_index type;
        QString qualifier;

        bool operator<(const ModelInfoIndex& other) const {
            return type < other.type || (type == other.type && qualifier < other.qualifier);
        }

        bool operator==(const ModelInfoIndex& other) const {
            return type == other.type && qualifier == other.qualifier;
        }

        ModelInfoIndex(const std::type_index& type, const QString& qualifier) : type(type), qualifier(qualifier) {}

        ModelInfoIndex() = default;
        ModelInfoIndex(const ModelInfoIndex&) = default;
        ModelInfoIndex& operator=(const ModelInfoIndex&) = default;
        ModelInfoIndex(ModelInfoIndex&&) = default;
        ModelInfoIndex& operator=(ModelInfoIndex&&) = default;
    };

    class FRAMEWORK_EXPORT ApplicationContext : public QObject {
        Q_OBJECT
    public:
        static ApplicationContext* instance();

        // Factory 管理
        template<typename T>
        void registerFactoryType();
        
        template<typename T>
        void registerFactoryDriver(T* driver);
        
        template<typename T>
        bool existsFactory() const;
        
        template<typename T>
        T* getFactoryDriver(const QString& driverName);
        
        template<typename T>
        bool existsFactoryDriver(const QString& driverName) const;
        
        template<typename T>
        QStringList getFactoryDriverList() const;

        // Service 管理
        template<typename T>
        void registerService(T* service);
        
        template<typename T>
        bool hasService() const;
        
        template<typename T>
        T* getService();
        
        template<typename T>
        T* getService(const QString& name);

        // Model 管理
        template<typename T>
        void registerModelType();

        template<typename T>
        std::shared_ptr<T> getModel(const QString& qualifier = QString());
        
        template<typename T>
        std::shared_ptr<T> getWriteableModel(const QString& qualifier = QString());
        
        // 同步可写模型到只读模型
        void syncModelData(const ModelInfoIndex& key);

        // 生成模型的 key
        static ModelInfoIndex makeModelKey(const std::type_index& type, const QString& qualifier) {
            return { type, qualifier };
        }

        // Module 管理
        bool tryLoadModule(IModule* module);
        void loadModule(const QString& modulePath);  // 从文件加载模块
        void unloadModule(IModule* module);
        void loadModules(const QString& directory);  // 从目录加载所有模块
        void unloadModules();  // 卸载所有模块
        IModule* getModule(const QString& name) const;
        bool isModuleLoaded(const QString& name) const;
        
        // 获取待处理模块信息
        QStringList getPendingModules() const;
        QSet<QString> getMissingDependencies(const QString& moduleName) const;
        QStringList getFailedModules() const;  // 获取因依赖缺失而无法加载的模块

        // 模型验证
        template<typename T>
        void registerValidator(std::shared_ptr<IModelValidator> validator);
        template<typename T>
        void unregisterValidator(std::shared_ptr<IModelValidator> validator);

        // 获取验证器
        QList<std::shared_ptr<IModelValidator>> getValidators(const std::type_index& type) const;

        // 产品管理
        QString getProductName() const;
        void setProductName(const QString& productName);

        // 调试模式
        bool isDebugMode() const;
        void setDebugMode(bool debugMode);

        void changeLanguage(QString language);
        QString getCurrentLanguage() const;
        
    signals:
        void moduleLoadError(const QString& moduleName, const QString& error);
        void moduleLoaded(const QString& moduleName);
        void moduleUnloaded(const QString& moduleName);

        // 产品管理
        void productNameChanged(const QString& productName);

    protected:
        ApplicationContext();
        ~ApplicationContext();

    private:
        static ApplicationContext* s_instance;

        // 核心模块管理
        QMap<QString, IModule*> m_readyModules;           // 已加载的模块
        QMap<QString, ModuleResources> m_moduleResources;  // 模块资源记录
        QMap<QString, ModuleInfo> m_modules;    // 全部模块列表，包含未完成加载的模块和失败加载的模块
        QMap<QString, bool> m_hasCyclingDependency;            // 已检查的依赖循环

        // 模块加载控制
        QMutex m_moduleLock;
        QString m_currentModuleName;               // 当前正在初始化的模块
        
        // 工厂注册表
        QMap<std::type_index, std::shared_ptr<Factory<void>>> m_factories;
        
        // 服务注册表
        QMap<QString, std::shared_ptr<IService>> m_services;          

        // 模型注册表
        QSet<std::type_index> m_modelTypes;                           // 模型类型
        QMap<ModelInfoIndex, std::shared_ptr<IModel>> m_readOnlyModels;             // 模型注册表
        QMap<ModelInfoIndex, std::shared_ptr<IModel>> m_writeableModels;             // 模型注册表
        
        // Validator 管理
        QMap<std::type_index, QList<std::shared_ptr<IModelValidator>>> m_validators;  // Validator 注册表

        // 产品信息
        QString m_productName;
        
        // 调试模式
        bool m_debugMode;

        // 语言
        QString m_currentLanguage = "zh_CN";
        
        // 模块管理辅助函数
        bool validateModule(IModule* module, QString& error);
        bool checkDependencies(IModule* module, QSet<QString>& missingDeps);
        bool hasDependencyCycle(const QString& name, QSet<QString>& visited);
        void cleanupModule(IModule* module);
        
        // 记录资源注册
        void trackFactoryType(std::type_index type);
        void trackFactoryDriver(std::type_index factoryType, const QString& name);
        void trackService(const QString& name);
        void trackModelType(const std::type_index& type);
        
        // 依赖管理
        void unloadModuleWithDependents(IModule* module);
        
        // 待处理模块管理
        void tryLoadDependentModules(const QString& loadedModule);
    };
}
#include "ApplicationContext.inl"
