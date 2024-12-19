#pragma once

#include "ast.h"
#include <string>

class Generator {
public:
    Generator() = default;
    void generateCode(const std::shared_ptr<ASTNode>& rootNode);

private:
    void generateStructCode(const std::shared_ptr<StructNode>& node);
    void generateBlockCode(const std::shared_ptr<BlockNode>& node);
};