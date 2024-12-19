#pragma once
#include <string>
#include <vector>
#include <memory>
#include <iostream>

// 定义 Mota 语法树的节点

class ASTNode {
public:
    virtual ~ASTNode() = default;
    virtual void print() const = 0;
};

class NamespaceNode : public ASTNode {
public:
    explicit NamespaceNode(const std::string& name) : name(name) {}
    void print() const override {
        std::cout << "Namespace: " << name << std::endl;
    }

private:
    std::string name;
};

class StructNode : public ASTNode {
public:
    explicit StructNode(const std::string& name) : name(name) {}
    void print() const override {
        std::cout << "Struct: " << name << std::endl;
    }

private:
    std::string name;
};

class BlockNode : public ASTNode {
public:
    explicit BlockNode(const std::string& name) : name(name) {}
    void print() const override {
        std::cout << "Block: " << name << std::endl;
    }

private:
    std::string name;
};
