#include "IModel.h"
#include <QDir>

IModel::IModel(Region region)
    : m_region(region)
    , m_writable(false)
{
}

bool IModel::saveToFile(const QString& filepath, const QString& format) {
    auto engine = storageEngine(format);
    if (!engine) return false;
    return engine->save(filepath.toStdString(), toCbor());
}

bool IModel::loadFromFile(const QString& filepath, const QString& format) {
    auto engine = storageEngine(format);
    if (!engine) return false;
    QCborValue cbor;
    if (!engine->load(filepath.toStdString(), cbor)) return false;
    fromCbor(cbor);
    return true;
}

bool IModel::save() {
    // 检查是否可写
    if (!writable()) return false;

    // 获取模型注解
    auto annotation = modelAnnotation();
    
    // 获取保存路径
    QString path = resolvePath();
    if (path.isEmpty()) return false;
    
    // 确保目标目录存在
    QFileInfo fileInfo(path);
    QDir dir = fileInfo.dir();
    if (!dir.exists()) {
        if (!dir.mkpath(".")) return false;
    }
    
    // 获取存储格式，如果注解中未指定则使用默认格式
    QString format = annotation.format;
    if (format.isEmpty()) format = "cbor";
    
    // 检查存储引擎是否可用
    auto engine = storageEngine(format);
    if (!engine) return false;
    
    return saveToFile(path, format);
}

bool IModel::load() {
    // 获取模型注解
    auto annotation = modelAnnotation();
    
    // 获取加载路径
    QString path = resolvePath();
    if (path.isEmpty()) return false;
    
    // 检查文件是否存在
    if (!QFileInfo::exists(path)) return false;
    
    // 获取存储格式，如果注解中未指定则使用默认格式
    QString format = annotation.format;
    if (format.isEmpty()) format = "cbor";
    
    // 检查存储引擎是否可用
    auto engine = storageEngine(format);
    if (!engine) return false;
    
    return loadFromFile(path, format);
}

bool IModel::writable() const {
    return m_writable;
}

void IModel::writable(bool writable) {
    m_writable = writable;
}

IModel::Region IModel::region() const {
    return m_region;
}

void IModel::region(Region region) {
    m_region = region;
}

QString IModel::qualifier() const {
    return m_qualifier;
}

QString IModel::qualifier(const QString& qualifier) {
    auto old = m_qualifier;
    m_qualifier = qualifier;
    return old;
}

QString IModel::resolvePath(const QString& qualifier) const {
    // 获取注解中的文件路径
    QString path = modelAnnotation().file;
    if (path.isEmpty()) {
        // 如果注解中没有指定路径，使用默认路径
        if (m_region == Region::Product) {
            path = "${app_path}/settings/${product_dir}/${name}.cbor";
        } else {
            path = "${app_path}/settings/${name}.cbor";
        }
    }

    // 替换变量
    path.replace("${app_path}", QCoreApplication::applicationDirPath());
    path.replace("${product_dir}", productDir());
    path.replace("${qualifier}", qualifier.isEmpty() ? m_qualifier : qualifier);
    path.replace("${name}", modelName());

    // 如果路径不以盘符开头，添加应用目录前缀
    if (!path.contains(QRegExp("^[A-Za-z]:"))) {
        path = QDir::cleanPath(QCoreApplication::applicationDirPath() + "/" + path);
    }

    return path;
}

QString IModel::productDir() const {
    return QString();
}

std::shared_ptr<IStorageEngine> IModel::storageEngine(const QString& format) {
    // TODO: 实现存储引擎工厂，这里应该根据 format 返回对应的存储引擎
    return nullptr;
}
