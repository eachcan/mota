#include "generator.h"
#include <iostream>
#include <sstream>

namespace mota {
namespace generator {

std::string Generator::generateAnnotationDecl(const ast::AnnotationDecl& annotation) {
    TemplateVars vars;
    
    // 基本信息
    vars["ANNOTATION_NAME"] = annotation.name;
    vars["TYPE_NAME"] = annotation.name;
    vars["TYPE_KIND"] = "annotation";
    vars["TYPE"] = "annotation";
    
    // 继承信息
    if (!annotation.baseName.empty()) {
        vars["HAS_BASE_CLASS"] = "true";
        vars["BASE_NAME"] = annotation.baseName;
        vars["BASE_CLASS"] = annotation.baseName;
    } else {
        vars["HAS_BASE_CLASS"] = "false";
        vars["BASE_NAME"] = "";
        vars["BASE_CLASS"] = "";
    }
    
    // 字段信息
    vars["HAS_FIELDS"] = annotation.fields.empty() ? "false" : "true";
    vars["FIELDS"] = nlohmann::json::parse(buildFieldsData(annotation.fields));
    
    // 添加描述信息
    vars["DESCRIPTION"] = "Generated annotation " + annotation.name;
    
    // 使用模板引擎渲染
    return templateEngine_->renderTemplate("annotation_decl", vars);
}

std::string Generator::generateStructDecl(const ast::Struct& struct_) {
    TemplateVars vars;
    
    // 基本信息
    vars["STRUCT_NAME"] = struct_.name;
    vars["TYPE_NAME"] = struct_.name;
    vars["TYPE_KIND"] = "struct";
    vars["TYPE"] = "struct";
    
    // 继承信息
    if (!struct_.baseName.empty()) {
        vars["HAS_BASE_CLASS"] = "true";
        vars["BASE_NAME"] = struct_.baseName;
        vars["BASE_CLASS"] = struct_.baseName;
    } else {
        vars["HAS_BASE_CLASS"] = "false";
        vars["BASE_NAME"] = "";
        vars["BASE_CLASS"] = "";
    }
    
    // 字段信息
    vars["HAS_FIELDS"] = struct_.fields.empty() ? "false" : "true";
    vars["FIELDS"] = nlohmann::json::parse(buildFieldsData(struct_.fields));
    
    // 注解信息
    vars["HAS_ANNOTATIONS"] = struct_.annotations.empty() ? "false" : "true";
    
    // 添加描述信息
    vars["DESCRIPTION"] = "Generated struct " + struct_.name;
    
    // 使用模板引擎渲染
    return templateEngine_->renderTemplate("struct_decl", vars);
}

std::string Generator::generateBlockDecl(const ast::Block& block) {
    TemplateVars vars;
    
    // 基本信息
    vars["BLOCK_NAME"] = block.name;
    vars["TYPE_NAME"] = block.name;
    vars["TYPE_KIND"] = "block";
    vars["TYPE"] = "block";
    
    // 继承信息
    if (!block.baseName.empty()) {
        vars["HAS_BASE_CLASS"] = "true";
        vars["BASE_NAME"] = block.baseName;
        vars["BASE_CLASS"] = block.baseName;
    } else {
        vars["HAS_BASE_CLASS"] = "false";
        vars["BASE_NAME"] = "";
        vars["BASE_CLASS"] = "";
    }
    
    // 字段信息
    vars["HAS_FIELDS"] = block.fields.empty() ? "false" : "true";
    vars["FIELDS"] = nlohmann::json::parse(buildFieldsData(block.fields));
    
    // 注解信息
    vars["HAS_ANNOTATIONS"] = block.annotations.empty() ? "false" : "true";
    
    // 添加描述信息
    vars["DESCRIPTION"] = "Generated block " + block.name;
    
    // 使用模板引擎渲染
    return templateEngine_->renderTemplate("block_decl", vars);
}

std::string Generator::generateEnumDecl(const ast::Enum& enum_) {
    std::cout << "Generator: generateEnumDecl starting for enum '" << enum_.name << "'" << std::endl;
    
    TemplateVars vars;
    
    try {
        // 基本信息
        vars["ENUM_NAME"] = enum_.name;
        vars["TYPE_NAME"] = enum_.name;
        vars["TYPE_KIND"] = "enum";
        
        std::cout << "Generator: Set basic enum info" << std::endl;
        
        // 枚举值信息
        vars["HAS_VALUES"] = enum_.values.empty() ? "false" : "true";
        
        std::cout << "Generator: Building enum values, count: " << enum_.values.size() << std::endl;
        
        // 构建枚举值数据
        nlohmann::json valuesArray = nlohmann::json::array();
        for (size_t i = 0; i < enum_.values.size(); ++i) {
            const auto& value = enum_.values[i];
            nlohmann::json valueObj = {
                {"name", value->name},
                {"index", i},
                {"is_first", i == 0},
                {"is_last", i == enum_.values.size() - 1}
            };
            
            // 如果有值，添加值信息
            if (value->value) {
                valueObj["has_value"] = true;
                // 这里需要处理表达式值，暂时用占位符
                valueObj["value"] = "0";
            } else {
                valueObj["has_value"] = false;
                valueObj["value"] = "";
            }
            
            valuesArray.push_back(valueObj);
        }
        vars["ENUM_VALUES"] = valuesArray;
        
        std::cout << "Generator: Built enum values array" << std::endl;
        
        // 注解信息
        vars["HAS_ANNOTATIONS"] = enum_.annotations.empty() ? "false" : "true";
        
        std::cout << "Generator: Calling template engine for enum_decl..." << std::endl;
        
        // 使用模板引擎渲染
        std::string result = templateEngine_->renderTemplate("enum_decl", vars);
        
        std::cout << "Generator: Template engine returned result for enum" << std::endl;
        return result;
        
    } catch (const std::exception& e) {
        std::cerr << "Generator: Exception in generateEnumDecl: " << e.what() << std::endl;
        return "";
    } catch (...) {
        std::cerr << "Generator: Unknown exception in generateEnumDecl" << std::endl;
        return "";
    }
}

std::string Generator::buildFieldsData(const std::vector<std::unique_ptr<ast::Field>>& fields) {
    // 构建JSON数组
    nlohmann::json fieldsArray = nlohmann::json::array();
    
    for (size_t i = 0; i < fields.size(); ++i) {
        const auto& field = fields[i];
        
        // 预计算所有需要的字段相关值
        std::string fieldName = field->name;
        std::string fieldType = field->type->toString();
        std::string fieldTypeMapped = mapType(fieldType);
        std::string fieldNamePascal = toPascalCase(fieldName);
        std::string fieldNameCamel = toCamelCase(fieldName);
        std::string privateFieldName = fieldName + "_";
        

        
        // 构建字段的JSON对象，包含所有可能需要的变量
        nlohmann::json fieldObj = {
            {"name", fieldName},
            {"type", fieldType},
            {"type_mapped", fieldTypeMapped},
            {"origin_type_name", fieldType},
            {"description", "Generated field for " + fieldName},
            {"is_repeated", isRepeatedType(*field->type)},
            {"is_optional", isOptionalType(*field->type)},
            {"is_map", isMapType(*field->type)},
            {"is_builtin", isBuiltinType(fieldType)},
            {"is_custom_type", !isBuiltinType(fieldType)},
            {"index", i},
            {"is_first", i == 0},
            {"is_last", i == fields.size() - 1},
            // 所有可能的变量名形式
            {"FIELD_NAME", fieldName},
            {"FIELD_TYPE", fieldType},
            {"FIELD_TYPE_MAPPED", fieldTypeMapped},
            {"field_name", fieldName},
            {"field_type", fieldType},
            {"field_type_mapped", fieldTypeMapped},
            {"field_name_pascal", fieldNamePascal},
            {"field_name_camel", fieldNameCamel},
            {"FIELD_NAME_PASCAL", fieldNamePascal},
            {"FIELD_NAME_CAMEL", fieldNameCamel},
            {"private_field_name", privateFieldName},
            {"PRIVATE_FIELD_NAME", privateFieldName},
            // getter/setter 方法名
            {"getter_name", "get" + fieldNamePascal},
            {"setter_name", "set" + fieldNamePascal},
            {"GETTER_NAME", "get" + fieldNamePascal},
            {"SETTER_NAME", "set" + fieldNamePascal},
            // 注解相关
            {"HAS_ANNOTATIONS", false},
            {"ANNOTATIONS", nlohmann::json::array()}
        };
        
        fieldsArray.push_back(fieldObj);
    }
    
    return fieldsArray.dump();
}

TemplateVars Generator::buildAnnotationVars(const std::unique_ptr<ast::Annotation>& annotation) {
    TemplateVars vars;
    // 暂时返回空变量，待AST结构确定后实现
    return vars;
}

TemplateVars Generator::buildStructVars(const std::unique_ptr<ast::Struct>& struct_) {
    TemplateVars vars;
    // 暂时返回空变量，待AST结构确定后实现
    return vars;
}

TemplateVars Generator::buildBlockVars(const std::unique_ptr<ast::Block>& block) {
    TemplateVars vars;
    // 暂时返回空变量，待AST结构确定后实现
    return vars;
}

TemplateVars Generator::buildEnumVars(const std::unique_ptr<ast::Enum>& enum_) {
    TemplateVars vars;
    // 暂时返回空变量，待AST结构确定后实现
    return vars;
}

} // namespace generator
} // namespace mota 