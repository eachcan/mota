#ifndef CONFIG_H
#define CONFIG_H

#include <string>
#include <vector>
#include <yaml-cpp/yaml.h>

namespace mota {

struct ModelConfig {
    std::string mota;  // mota 文件或目录路径
    std::string model; // 模型文件或目录路径
};

struct Config {
    std::vector<ModelConfig> models;
    
    static Config loadFromFile(const std::string& path);
};

} // namespace mota

#endif // CONFIG_H
