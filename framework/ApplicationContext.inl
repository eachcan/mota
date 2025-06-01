#include "ApplicationContext.h"

// Factory 管理实现
template<typename FactoryType>
bool ymf::ApplicationContext::existsFactory() const {
    return m_factories.contains(std::type_index(typeid(FactoryType)));
}

template<typename FactoryType>
void ymf::ApplicationContext::registerFactoryType() {
    auto type = std::type_index(typeid(FactoryType));
    if (m_factories.contains(type)) return;
    
    auto factory = std::make_shared<Factory<FactoryType>>();
    m_factories[type] = factory;
    trackFactoryType(type);
}

template<typename T>
void ymf::ApplicationContext::registerFactoryDriver(T* driver) {
    if (!driver) return;
    
    auto factoryType = std::type_index(typeid(T));
    if (!m_factories.contains(factoryType)) {
        // 禁止注册未注册的工厂
        return;
    }
    
    auto factory = m_factories[factoryType];
    QString name = driver->getName();
    factory->registerDriver(driver, name);
    trackFactoryDriver(factoryType, name);
}

template<typename FactoryType>
FactoryType* ymf::ApplicationContext::getFactoryDriver(const QString& driverName) {
    auto factoryType = std::type_index(typeid(FactoryType));
    auto it = m_factories.find(factoryType);
    if (it == m_factories.end()) return nullptr;
    
    auto factory = std::dynamic_pointer_cast<Factory<FactoryType>>(it.value());
    if (!factory) return nullptr;
    
    return static_cast<FactoryType*>(factory->getDriver(driverName));
}

template<typename FactoryType>
bool ymf::ApplicationContext::existsFactoryDriver(const QString& driverName) const {
    auto factoryType = std::type_index(typeid(FactoryType));
    auto it = m_factories.find(factoryType);
    if (it == m_factories.end()) return false;
    
    auto factory = std::dynamic_pointer_cast<Factory<FactoryType>>(it.value());
    if (!factory) return false;
    
    return factory->existsDriver(driverName);
}

template<typename T>
QStringList ymf::ApplicationContext::getFactoryDriverList() const {
    auto factoryType = std::type_index(typeid(T));
    auto it = m_factories.find(factoryType);
    if (it == m_factories.end()) return QStringList();
    
    auto factory = std::dynamic_pointer_cast<Factory<T>>(it.value());
    if (!factory) return QStringList();
    
    return factory->getDriverList();
}

// Service 管理实现
template<typename T>
bool ymf::ApplicationContext::hasService() const {
    return m_services.contains(std::type_index(typeid(T)));
}

template<typename T>
void ymf::ApplicationContext::registerService(T* service) {
    if (!service) return;
    
    auto type = std::type_index(typeid(T));
    if (m_services.contains(type)) return;
    
    m_services[type] = std::shared_ptr<IService>(service);
    service->initialize();
    trackService(service->getName());
}

template<typename T>
T* ymf::ApplicationContext::getService() {
    auto type = std::type_index(typeid(T));
    auto it = m_services.find(type);
    if (it == m_services.end()) return nullptr;
    
    return dynamic_cast<T*>(it.value().get());
}

template<typename T>
T* ymf::ApplicationContext::getService(const QString& name) {
    for (auto it = m_services.begin(); it != m_services.end(); ++it) {
        auto service = it.value();
        if (service->getName() == name) {
            return dynamic_cast<T*>(service.get());
        }
    }
    return nullptr;
}

// Model 管理实现
template <typename T>
inline void ymf::ApplicationContext::registerModelType()
{
    m_modelTypes.insert(typeid(T));
}

template <typename T>
std::shared_ptr<T> ymf::ApplicationContext::getModel(const QString& qualifier) {
    auto key = makeModelKey(typeid(T), qualifier);
    
    // 先查找只读模型
    auto readIt = m_readOnlyModels.find(key);
    if (readIt != m_readOnlyModels.end()) {
        return std::dynamic_pointer_cast<T>(*readIt);
    }
    
    // 创建新的只读模型
    auto model = std::make_shared<T>();
    model->qualifier(qualifier);
    model->writable(false);
    model->setContext(this);
    if (model->load()) {  // 尝试加载已存在的数据
        m_readOnlyModels[key] = model;
    }
    return model;
}

template<typename T>
std::shared_ptr<T> ymf::ApplicationContext::getWriteableModel(const QString& qualifier) {
    auto key = makeModelKey(typeid(T), qualifier);
    
    // 先查找可写模型
    auto writeIt = m_writeableModels.find(key);
    if (writeIt != m_writeableModels.end()) {
        return std::dynamic_pointer_cast<T>(*writeIt);
    }
    
    // 创建新的可写模型
    auto model = std::make_shared<T>();
    model->qualifier(qualifier);
    model->writable(true);
    model->setContext(this);
    if (model->load()) {  // 尝试加载已存在的数据
        m_writeableModels[key] = model;
    }
    return model;
}

// Validator 管理实现
template<typename T>
void ymf::ApplicationContext::registerValidator(std::shared_ptr<IModelValidator> validator) {
    if (!validator) return;
    if (!m_modelTypes.contains(typeid(T))) return;
    if (!m_validators.contains(typeid(T))) {
        m_validators[typeid(T)] = QList<std::shared_ptr<IModelValidator>>();
    }
    if (m_validators[typeid(T)].contains(validator)) return;

    m_validators[typeid(T)].append(validator);
}
