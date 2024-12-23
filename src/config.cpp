#include "config.h"
#include <stdexcept>

namespace mota {

Config Config::loadFromFile(const std::string& path) {
    Config config;
    try {
        YAML::Node root = YAML::LoadFile(path);
        if (!root["models"]) {
            throw std::runtime_error("Missing 'models' section in config file");
        }

        for (const auto& model : root["models"]) {
            ModelConfig modelConfig;
            if (!model["mota"] || !model["model"]) {
                throw std::runtime_error("Each model must have 'mota' and 'model' fields");
            }
            modelConfig.mota = model["mota"].as<std::string>();
            modelConfig.model = model["model"].as<std::string>();
            config.models.push_back(modelConfig);
        }
    } catch (const YAML::Exception& e) {
        throw std::runtime_error("Failed to parse config file: " + std::string(e.what()));
    }
    return config;
}

} // namespace mota
