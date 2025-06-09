#pragma once

#include "ast.h"
#include <string>
#include <unordered_map>
#include <vector>
#include <memory>

namespace mota {
namespace generator {

// 模板变量类型
using TemplateVars = std::unordered_map<std::string, std::string>;

// 生成器配置
struct GeneratorConfig {
    std::string version;
    std::string encoding;
    std::unordered_map<std::string, std::string> templates;
    std::unordered_map<std::string, std::string> typeMapping;
    std::unordered_map<std::string, std::string> fieldTypeTemplates;
    std::unordered_map<std::string, std::string> templateVariables;
    std::unordered_map<std::string, std::string> typeInterfaceMapping;
    
    struct {
        std::string getterPrefix;
        std::string setterPrefix;
        bool pascalCase;
    } accessorFormat;
    
    struct {
        std::string style;
        std::unordered_map<std::string, std::string> prefix;
        std::unordered_map<std::string, std::string> suffix;
    } identifierFormat;
    
    struct {
        std::string separator;
        std::string style;
    } namespaceFormat;
    
    struct {
        std::string singleInheritance;
        std::string multipleInheritance;
        std::string interfaceInheritance;
        std::string combinedInheritance;
        std::string inheritanceKeyword;
    } inheritanceFormat;
    
    struct {
        std::string path;
        std::string type;
    } filePath;
    
    struct {
        std::string startTag;
        std::string endTag;
        std::string itemVariable;
        std::string indexVariable;
    } loopSyntax;
    
    // 语法元素配置
    std::unordered_map<std::string, std::string> syntaxElements;
    
    // Include指令配置
    struct {
        std::string pattern;
        std::string sourceExtension;
        std::string targetExtension;
    } includeDirective;
    
    // 代码生成配置
    struct {
        std::string containerTemplate;
        std::string stringLiteralTemplate;
        std::string variantTemplate;
        std::string collectionSeparator;
    } codeGeneration;
};

// 代码生成器
class Generator {
public:
    explicit Generator(const std::string& templateDir);
    
    // 加载配置
    bool loadConfig(const std::string& configPath);
    
    // 解析配置
    bool parseConfig(const std::string& content);
    
    // 建立类型上下文
    void buildTypeContext(const ast::Document& document);
    
    // 生成代码
    std::string generate(const ast::Document& document, const std::string& outputPath = "");
    
    // 生成单个文件
    std::string generateFile(const ast::Document& document, const std::string& sourceFileName = "");
    
private:
    std::string templateDir_;
    GeneratorConfig config_;
    std::unordered_map<std::string, std::string> templateCache_;
    
    // 类型上下文，用于记录定义的类型
    std::unordered_map<std::string, std::string> typeContext_; // name -> type (block, enum, struct, annotation)
    
    // 加载模板
    std::string loadTemplate(const std::string& templateName);
    
    // 渲染模板
    std::string renderTemplate(const std::string& templateContent, const TemplateVars& vars);
    
    // 生成各种类型的代码
    std::string generateStruct(const ast::Struct& structNode);
    std::string generateBlock(const ast::Block& blockNode);
    std::string generateEnum(const ast::Enum& enumNode);
    std::string generateAnnotation(const ast::AnnotationDecl& annotationNode);
    
    // 生成字段访问器
    std::string generateAccessors(const std::vector<std::unique_ptr<ast::Field>>& fields);
    std::string generatePrivateFields(const std::vector<std::unique_ptr<ast::Field>>& fields);
    std::string generateConstructor(const std::vector<std::unique_ptr<ast::Field>>& fields, const std::string& className);
    std::string generateSerializeFields(const std::vector<std::unique_ptr<ast::Field>>& fields);
    std::string generateDeserializeFields(const std::vector<std::unique_ptr<ast::Field>>& fields);
    std::string generateFieldNames(const std::vector<std::unique_ptr<ast::Field>>& fields);
    std::string generateFieldTypeLogic(const std::vector<std::unique_ptr<ast::Field>>& fields);
    std::string generateValueGetterLogic(const std::vector<std::unique_ptr<ast::Field>>& fields);
    std::string generateValueSetterLogic(const std::vector<std::unique_ptr<ast::Field>>& fields);
    
    // 注解专用的属性处理方法
    std::string generatePropertyTypeLogic(const std::vector<std::unique_ptr<ast::Field>>& fields);
    std::string generatePropertyGetterLogic(const std::vector<std::unique_ptr<ast::Field>>& fields);
    std::string generatePropertySetterLogic(const std::vector<std::unique_ptr<ast::Field>>& fields);
    std::string generateArgumentGetterLogic(const std::vector<std::unique_ptr<ast::Field>>& fields);
    
    // 工具函数
    std::string mapType(const std::string& motaType);
    std::string formatTypeName(const std::string& name, const std::string& type);
    std::string toPascalCase(const std::string& str);
    std::string toCamelCase(const std::string& str);
    std::string toSnakeCase(const std::string& str);
    std::string getCurrentTimestamp();
    std::string extractNamespace(const ast::Document& document);
    std::string extractFileName(const std::string& filePath);
    std::string generateDefaultValue(const ast::Expr& expr, const std::string& fieldType);
    
    // 模板处理
    std::string processLoops(const std::string& content, const TemplateVars& vars);
    std::string expandLoop(const std::string& loopContent, const std::string& collectionData, 
                          const std::string& itemName, const std::string& indexName);
    std::string processConditionals(const std::string& content, const TemplateVars& vars);
    std::string processTemplateFunctions(const std::string& content, const TemplateVars& vars);
    std::string applyTemplateFunction(const std::string& value, const std::string& function);
    
    // 新增的模板函数
    std::string formatNamespacePath(const std::string& namespaceStr);
    std::string joinStrings(const std::string& value, const std::string& separator);
    
    // 基于配置的类型处理
    std::string mapTypeFromConfig(const std::string& motaType);
    std::string formatTypeNameFromConfig(const std::string& name, const std::string& type);
    std::string getTypeSuffix(const std::string& type);
    std::string getInterfaceName(const std::string& type);
    std::string getFieldTemplate(const std::string& motaType);
    std::string getTypeKind(const std::string& typeName);
    
    // 统一的模板变量构建
    TemplateVars buildTemplateVars(const std::string& typeName, const std::string& typeKind, 
                                  const std::vector<std::unique_ptr<ast::Field>>& fields,
                                  const std::string& baseName = "");
    TemplateVars buildFieldTemplateVars(const ast::Field& field);
    TemplateVars buildEnumTemplateVars(const ast::Enum& enumNode);
    
    // 枚举代码生成的辅助方法
    std::string generateEnumValuesFromTemplate(const ast::Enum& enumNode);
    std::string generateEnumToStringCasesFromTemplate(const ast::Enum& enumNode, const std::string& className);
    std::string generateStringToEnumLogicFromTemplate(const ast::Enum& enumNode, const std::string& className);
    std::string generateEnumStringValuesFromTemplate(const ast::Enum& enumNode);
    std::string generateEnumDisplayNamesFromTemplate(const ast::Enum& enumNode);
    std::string generateEnumAnnotationLogicFromTemplate(const ast::Enum& enumNode);
    std::string generateEnumValueAnnotationCasesFromTemplate(const ast::Enum& enumNode, const std::string& className);
    std::string generateEnumValueAnnotationByNameLogicFromTemplate(const ast::Enum& enumNode);
    std::string generateAnnotationLogicFromTemplate(const std::vector<std::unique_ptr<ast::Annotation>>& annotations);
    std::string generateAnnotationInstancesLogic(const std::vector<std::unique_ptr<ast::Annotation>>& annotations);
    std::string generateAnnotationArgumentValue(const ast::Expr& expr);
    std::string getEnumValueDisplayName(const ast::EnumValue& enumValue);
    
    // 基于模板的代码生成
    std::string generateFromTemplate(const std::string& templateType, const std::vector<std::unique_ptr<ast::Field>>& fields);
    std::string generatePrivateFieldsFromTemplate(const std::vector<std::unique_ptr<ast::Field>>& fields);
    std::string generateAccessorsFromTemplate(const std::vector<std::unique_ptr<ast::Field>>& fields);
    std::string generateSerializeFieldsFromTemplate(const std::vector<std::unique_ptr<ast::Field>>& fields);
    std::string generateDeserializeFieldsFromTemplate(const std::vector<std::unique_ptr<ast::Field>>& fields);
    std::string generateFieldNamesFromTemplate(const std::vector<std::unique_ptr<ast::Field>>& fields);
    std::string generateFieldTypeLogicFromTemplate(const std::vector<std::unique_ptr<ast::Field>>& fields);
    std::string generateValueGetterLogicFromTemplate(const std::vector<std::unique_ptr<ast::Field>>& fields);
    std::string generateValueSetterLogicFromTemplate(const std::vector<std::unique_ptr<ast::Field>>& fields);
    std::string generateFieldAnnotationLogicFromTemplate(const std::vector<std::unique_ptr<ast::Field>>& fields);
    std::string generateArgumentGetterLogicFromTemplate(const std::vector<std::unique_ptr<ast::Field>>& fields);
    std::string generateArgumentNamesFromTemplate(const std::vector<std::unique_ptr<ast::Field>>& fields);
    
    // 字段类型模板处理
    std::string getFieldTypeSerializeCode(const std::string& templateName, const TemplateVars& fieldVars);
    std::string getFieldTypeDeserializeCode(const std::string& templateName, const TemplateVars& fieldVars);
    std::string extractTemplateSection(const std::string& templateContent, const std::string& sectionName, const TemplateVars& vars);
};

} // namespace generator
} // namespace mota 