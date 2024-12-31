#include "config.h"

namespace mota {

void Config::addSearchPath(const std::string& path) {
    std::filesystem::path fsPath(path);
    auto normalizedPath = fsPath.make_preferred().string();
    if (std::find(searchPaths.begin(), searchPaths.end(), normalizedPath) == searchPaths.end()) {
        searchPaths.push_back(normalizedPath);
    }
}

}
