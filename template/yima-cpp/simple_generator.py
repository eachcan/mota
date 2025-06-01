#!/usr/bin/env python
# -*- coding: utf-8 -*-

"""
简单的Mota代码生成器
用于从Mota定义生成C++代码
"""

import os
import re
import json
import datetime
import argparse
from pathlib import Path

# 简单的模板渲染函数
def render_template(template_str, variables):
    """
    简单的模板渲染函数，支持条件语句
    
    Args:
        template_str: 模板字符串
        variables: 变量字典
    
    Returns:
        渲染后的字符串
    """
    # 处理条件语句
    def process_conditionals(template):
        # 处理条件块
        conditional_pattern = r'{{#(\w+)}}(.*?){{/\1}}'
        
        def replace_conditional(match):
            condition_var = match.group(1)
            content = match.group(2)
            
            # 如果条件为真，保留内容，否则返回空字符串
            if variables.get(condition_var):
                return content
            return ''
        
        # 使用正则表达式替换所有条件块
        while re.search(conditional_pattern, template, re.DOTALL):
            template = re.sub(conditional_pattern, replace_conditional, template, flags=re.DOTALL)
        
        return template
    
    # 先处理条件语句
    result = process_conditionals(template_str)
    
    # 然后替换变量
    for key, value in variables.items():
        placeholder = '{{' + key + '}}'
        if isinstance(value, str):
            result = result.replace(placeholder, value)
        elif value is not None:
            result = result.replace(placeholder, str(value))
    
    return result

def pascal_case(name):
    """将字符串转换为Pascal命名风格"""
    return ''.join(word.capitalize() for word in name.split('_'))

def camel_case(name):
    """将字符串转换为Camel命名风格"""
    words = name.split('_')
    return words[0] + ''.join(word.capitalize() for word in words[1:])

def parse_mota_file(file_path, parsed_files=None):
    """
    解析Mota定义文件
    
    Args:
        file_path: Mota文件路径
        parsed_files: 已经解析过的文件列表，用于防止循环包含
    
    Returns:
        包含解析结果的字典
    """
    # 初始化已解析文件列表
    if parsed_files is None:
        parsed_files = set()
    
    # 如果文件已经解析过，跳过
    if file_path in parsed_files:
        return {'blocks': [], 'structs': [], 'enums': []}
    
    # 标记文件为已解析
    parsed_files.add(file_path)
    
    with open(file_path, 'r', encoding='utf-8-sig') as f:
        content = f.read()
    
    # 简单的解析逻辑，实际项目中可能需要更复杂的解析器
    blocks = []
    structs = []
    enums = []
    
    # 先解析include指令
    include_pattern = r'include\s+"([^"]+)"'
    included_results = []
    
    for match in re.finditer(include_pattern, content):
        include_file = match.group(1)
        include_path = os.path.join(os.path.dirname(file_path), include_file)
        
        # 递归解析包含的文件
        if os.path.exists(include_path):
            include_result = parse_mota_file(include_path, parsed_files)
            included_results.append(include_result)
        else:
            print(f"警告：找不到包含文件 {include_path}")
    
    # 解析block
    block_pattern = r'block\s+(\w+)\s*{([^}]*)}'
    for match in re.finditer(block_pattern, content, re.DOTALL):
        block_name = match.group(1)
        block_content = match.group(2)
        
        fields = []
        for line in block_content.strip().split('\n'):
            line = line.strip()
            if not line or line.startswith('//'):
                continue
                
            # 简单解析字段定义
            field_match = re.match(r'(\w+)\s+(\w+);', line)
            if field_match:
                field_type = field_match.group(1)
                field_name = field_match.group(2)
                fields.append({
                    'name': field_name,
                    'type': field_type
                })
        
        blocks.append({
            'name': block_name,
            'fields': fields
        })
    
    # 解析struct (简化版，实际可能需要更复杂的解析)
    struct_pattern = r'struct\s+(\w+)\s*{([^}]*)}'
    for match in re.finditer(struct_pattern, content, re.DOTALL):
        struct_name = match.group(1)
        struct_content = match.group(2)
        
        fields = []
        for line in struct_content.strip().split('\n'):
            line = line.strip()
            if not line or line.startswith('//'):
                continue
                
            # 简单解析字段定义
            field_match = re.match(r'(\w+)\s+(\w+);', line)
            if field_match:
                field_type = field_match.group(1)
                field_name = field_match.group(2)
                fields.append({
                    'name': field_name,
                    'type': field_type
                })
        
        structs.append({
            'name': struct_name,
            'fields': fields
        })
    
    # 解析enum
    enum_pattern = r'enum\s+(\w+)\s*{([^}]*)}'
    for match in re.finditer(enum_pattern, content, re.DOTALL):
        enum_name = match.group(1)
        enum_content = match.group(2)
        
        values = []
        for line in enum_content.strip().split('\n'):
            line = line.strip()
            if not line or line.startswith('//'):
                continue
                
            # 去掉末尾的逗号
            if line.endswith(','):
                line = line[:-1]
                
            # 解析枚举值
            enum_value_match = re.match(r'(\w+)(?:\s*=\s*(\d+))?', line.rstrip(','))
            if enum_value_match:
                enum_value_name = enum_value_match.group(1)
                enum_value_value = enum_value_match.group(2) if enum_value_match.group(2) else None
                values.append({
                    'name': enum_value_name,
                    'value': enum_value_value
                })
        
        enums.append({
            'name': enum_name,
            'values': values
        })
    
    # 合并包含文件的结果
    for included_result in included_results:
        blocks.extend(included_result['blocks'])
        structs.extend(included_result['structs'])
        enums.extend(included_result['enums'])
    
    return {
        'blocks': blocks,
        'structs': structs,
        'enums': enums
    }

def generate_field_serialization(field, config, is_serialize=True):
    """
    生成字段序列化或反序列化代码
    
    Args:
        field: 字段信息
        config: 配置信息
        is_serialize: 是否为序列化（True）或反序列化（False）
    
    Returns:
        生成的代码
    """
    field_name = field['name']
    field_type = field['type']
    
    # 转换字段名为Pascal命名风格
    field_name_pascal = pascal_case(field_name)
    
    # 检查是否为基本类型
    cpp_type = config['type_mapping'].get(field_type)
    
    if cpp_type:
        # 基本类型
        if is_serialize:
            return f'map.insert(QLatin1String("{field_name}"), QCborValue(get{field_name_pascal}()));'
        else:
            if cpp_type in ['int8_t', 'int16_t', 'int32_t', 'int64_t', 'uint8_t', 'uint16_t', 'uint32_t', 'uint64_t']:
                return f'set{field_name_pascal}(static_cast<{cpp_type}>(map.value(QLatin1String("{field_name}")).toInteger()));'
            elif cpp_type in ['float', 'double']:
                return f'set{field_name_pascal}(static_cast<{cpp_type}>(map.value(QLatin1String("{field_name}")).toDouble()));'
            elif cpp_type == 'QString':
                return f'set{field_name_pascal}(map.value(QLatin1String("{field_name}")).toString());'
            elif cpp_type == 'bool':
                return f'set{field_name_pascal}(map.value(QLatin1String("{field_name}")).toBool());'
            elif cpp_type == 'QByteArray':
                return f'set{field_name_pascal}(map.value(QLatin1String("{field_name}")).toByteArray());'
    else:
        # 复合类型
        if is_serialize:
            return f'map.insert(QLatin1String("{field_name}"), get{field_name_pascal}().toCbor());'
        else:
            return f'{field_type} {field_name};\n{field_name}.fromCbor(map.value(QLatin1String("{field_name}")));\nset{field_name_pascal}({field_name});'
    
    return ''

def generate_field_accessor(field, config):
    """
    生成字段访问器代码
    
    Args:
        field: 字段信息
        config: 配置信息
    
    Returns:
        生成的代码
    """
    field_name = field['name']
    field_type = field['type']
    
    # 转换字段名为Pascal命名风格
    field_name_pascal = pascal_case(field_name)
    
    # 获取C++类型
    cpp_type = config['type_mapping'].get(field_type, field_type)
    
    # 生成getter
    getter = f"{cpp_type} get{field_name_pascal}() const {{ return m_{field_name}; }}"
    
    # 生成setter
    setter = f"void set{field_name_pascal}({cpp_type} value) {{ m_{field_name} = value; }}"
    
    return f"{getter}\n{setter}"

def generate_field_value_getter(field, config):
    """
    生成value()方法中获取字段值的代码
    
    Args:
        field: 字段信息
        config: 配置信息
    
    Returns:
        生成的代码
    """
    field_name = field['name']
    field_type = field['type']
    
    # 转换字段名为Pascal命名风格
    field_name_pascal = pascal_case(field_name)
    
    # 检查是否为基本类型
    cpp_type = config['type_mapping'].get(field_type)
    
    if cpp_type:
        # 基本类型
        return f'if (fieldName == "{field_name}") {{\n    return QVariant(get{field_name_pascal}());\n}}'
    else:
        # 复合类型
        return f'if (fieldName == "{field_name}") {{\n    return QVariant::fromValue(&m_{field_name});\n}}'

def generate_field_value_setter(field, config):
    """
    生成value()方法中设置字段值的代码
    
    Args:
        field: 字段信息
        config: 配置信息
    
    Returns:
        生成的代码
    """
    field_name = field['name']
    field_type = field['type']
    
    # 转换字段名为Pascal命名风格
    field_name_pascal = pascal_case(field_name)
    
    # 检查是否为基本类型
    cpp_type = config['type_mapping'].get(field_type)
    
    if cpp_type:
        # 基本类型
        if cpp_type in ['int8_t', 'int16_t', 'int32_t', 'int64_t', 'uint8_t', 'uint16_t', 'uint32_t', 'uint64_t']:
            return f'if (fieldName == "{field_name}") {{\n    set{field_name_pascal}(static_cast<{cpp_type}>(value.toInt()));\n}}'
        elif cpp_type in ['float', 'double']:
            return f'if (fieldName == "{field_name}") {{\n    set{field_name_pascal}(value.toFloat());\n}}'
        elif cpp_type == 'QString':
            return f'if (fieldName == "{field_name}") {{\n    set{field_name_pascal}(value.toString());\n}}'
        elif cpp_type == 'bool':
            return f'if (fieldName == "{field_name}") {{\n    set{field_name_pascal}(value.toBool());\n}}'
        elif cpp_type == 'QByteArray':
            return f'if (fieldName == "{field_name}") {{\n    set{field_name_pascal}(value.toByteArray());\n}}'
    
    # 复合类型不在这里处理，需要特殊处理
    return ''

def generate_field_type_logic(field, config):
    """
    生成fieldType()方法中的代码
    
    Args:
        field: 字段信息
        config: 配置信息
    
    Returns:
        生成的代码
    """
    field_name = field['name']
    field_type = field['type']
    
    return f'if (fieldName == "{field_name}") {{\n    return "{field_type}";\n}}'

def generate_field_description_logic(field, config):
    """
    生成fieldDescription()方法中的代码
    
    Args:
        field: 字段信息
        config: 配置信息
    
    Returns:
        生成的代码
    """
    field_name = field['name']
    
    # 这里简单返回字段名作为描述，实际项目中可能需要更多信息
    return f'if (fieldName == "{field_name}") {{\n    return "{field_name}";\n}}'

def generate_block_code(block, config, templates):
    """
    生成块类的代码
    
    Args:
        block: 块信息
        config: 配置信息
        templates: 模板字典
    
    Returns:
        生成的代码
    """
    block_name = block['name']
    fields = block['fields']
    
    # 生成字段序列化代码
    serialize_fields = []
    for field in fields:
        serialize_fields.append(generate_field_serialization(field, config, True))
    
    # 生成字段反序列化代码
    deserialize_fields = []
    for field in fields:
        deserialize_fields.append(generate_field_serialization(field, config, False))
    
    # 生成字段名列表
    field_names = ' << '.join(f'"{field["name"]}"' for field in fields)
    
    # 生成字段类型逻辑
    field_type_logic = []
    for field in fields:
        field_type_logic.append(generate_field_type_logic(field, config))
    
    # 生成字段描述逻辑
    field_description_logic = []
    for field in fields:
        field_description_logic.append(generate_field_description_logic(field, config))
    
    # 生成value()方法中获取字段值的代码
    value_getter_logic = []
    for field in fields:
        value_getter_logic.append(generate_field_value_getter(field, config))
    
    # 生成value()方法中设置字段值的代码
    value_setter_logic = []
    for field in fields:
        setter_code = generate_field_value_setter(field, config)
        if setter_code:
            value_setter_logic.append(setter_code)
    
    # 生成访问器
    accessors = []
    for field in fields:
        accessors.append(generate_field_accessor(field, config))
    
    # 生成私有字段
    private_fields = []
    for field in fields:
        field_type = config['type_mapping'].get(field['type'], field['type'])
        private_fields.append(f"{field_type} m_{field['name']} = {{}};")
    
    # 生成构造函数
    constructor_params = []
    constructor_inits = []
    
    for field in fields:
        field_type = config['type_mapping'].get(field['type'], field['type'])
        constructor_params.append(f"const {field_type}& {field['name']}")
        constructor_inits.append(f"m_{field['name']}({field['name']})")
    
    constructor = f"{block_name}({', '.join(constructor_params)}) \n        : {', '.join(constructor_inits)} {{}}"
    
    # 渲染模板
    variables = {
        'BLOCK_NAME': block_name,
        'CONSTRUCTOR': constructor,
        'SERIALIZE_FIELDS': '\n        '.join(serialize_fields),
        'DESERIALIZE_FIELDS': '\n        '.join(deserialize_fields),
        'FIELD_NAMES': field_names,
        'FIELD_TYPE_LOGIC': '\n        '.join(field_type_logic),
        'FIELD_ANNOTATION_LOGIC': '',
        'DESCRIPTION': block_name,
        'FIELD_DESCRIPTION_LOGIC': '\n        '.join(field_description_logic),
        'VALUE_GETTER_LOGIC': '\n        '.join(value_getter_logic),
        'VALUE_SETTER_LOGIC': '\n        '.join(value_setter_logic),
        'ACCESSORS': '\n    '.join(accessors),
        'PRIVATE_FIELDS': '\n    '.join(private_fields)
    }
    
    return render_template(templates['block'], variables)

def generate_struct_code(struct, config, templates):
    """
    生成结构体的代码
    
    Args:
        struct: 结构体信息
        config: 配置信息
        templates: 模板字典
    
    Returns:
        生成的代码
    """
    # 结构体生成逻辑与块类似，但有一些不同
    struct_name = struct['name']
    fields = struct['fields']
    
    # 生成字段序列化代码
    serialize_fields = []
    for field in fields:
        serialize_fields.append(generate_field_serialization(field, config, True))
    
    # 生成字段反序列化代码
    deserialize_fields = []
    for field in fields:
        deserialize_fields.append(generate_field_serialization(field, config, False))
    
    # 生成字段名列表
    field_names = ' << '.join(f'"{field["name"]}"' for field in fields)
    
    # 生成字段类型逻辑
    field_type_logic = []
    for field in fields:
        field_type_logic.append(generate_field_type_logic(field, config))
    
    # 生成字段描述逻辑
    field_description_logic = []
    for field in fields:
        field_description_logic.append(generate_field_description_logic(field, config))
    
    # 生成value()方法中获取字段值的代码
    value_getter_logic = []
    for field in fields:
        value_getter_logic.append(generate_field_value_getter(field, config))
    
    # 生成value()方法中设置字段值的代码
    value_setter_logic = []
    for field in fields:
        setter_code = generate_field_value_setter(field, config)
        if setter_code:
            value_setter_logic.append(setter_code)
    
    # 生成访问器
    accessors = []
    for field in fields:
        accessors.append(generate_field_accessor(field, config))
    
    # 生成私有字段
    private_fields = []
    for field in fields:
        field_type = config['type_mapping'].get(field['type'], field['type'])
        private_fields.append(f"{field_type} m_{field['name']} = {{}};")
    
    # 生成构造函数
    constructor_params = []
    constructor_inits = []
    
    for field in fields:
        field_type = config['type_mapping'].get(field['type'], field['type'])
        constructor_params.append(f"const {field_type}& {field['name']}")
        constructor_inits.append(f"m_{field['name']}({field['name']})")
    
    constructor = f"{struct_name}({', '.join(constructor_params)}) \n        : {', '.join(constructor_inits)} {{}}"
    
    # 渲染模板
    variables = {
        'STRUCT_NAME': struct_name,
        'STRUCT_ANNOTATIONS': '',
        'CONSTRUCTOR': constructor,
        'SERIALIZE_FIELDS': '\n        '.join(serialize_fields),
        'DESERIALIZE_FIELDS': '\n        '.join(deserialize_fields),
        'FIELD_NAMES': field_names,
        'FIELD_TYPE_LOGIC': '\n        '.join(field_type_logic),
        'FIELD_ANNOTATION_LOGIC': '',
        'DESCRIPTION': struct_name,
        'FIELD_DESCRIPTION_LOGIC': '\n        '.join(field_description_logic),
        'VALUE_GETTER_LOGIC': '\n        '.join(value_getter_logic),
        'VALUE_SETTER_LOGIC': '\n        '.join(value_setter_logic),
        'ACCESSORS': '\n    '.join(accessors),
        'PRIVATE_FIELDS': '\n    '.join(private_fields)
    }
    
    return render_template(templates['struct'], variables)

def generate_enum_code(enum, config, templates):
    """
    生成枚举的代码
    
    Args:
        enum: 枚举信息
        config: 配置信息
        templates: 模板字典
    
    Returns:
        生成的代码
    """
    enum_name = enum['name']
    values = enum['values']
    
    # 生成枚举值
    enum_values = []
    for i, value in enumerate(values):
        if value['value'] is not None:
            enum_values.append(f"{value['name']} = {value['value']}")
        else:
            # 如果没有指定值，则自动递增
            enum_values.append(value['name'])
    
    # 生成toString方法的case语句
    enum_to_string_cases = []
    for value in values:
        enum_to_string_cases.append(f"case {enum_name}::{value['name']}:\n                return \"{value['name']}\";")
    
    # 生成fromString方法的逻辑
    string_to_enum_logic = []
    for value in values:
        string_to_enum_logic.append(f"if (str == \"{value['name']}\")\n            return {enum_name}::{value['name']};")
    
    # 生成所有枚举值的字符串表示
    enum_string_values = ' << '.join(f'"{value["name"]}"' for value in values)
    
    # 生成所有枚举值的UI显示名称（这里简单使用枚举值名称）
    enum_display_names = ' << '.join(f'"{value["name"]}"' for value in values)
    
    # 默认枚举值（使用第一个值）
    default_enum_value = values[0]['name'] if values else "UNKNOWN"
    
    # 渲染模板
    variables = {
        'ENUM_NAME': enum_name,
        'ENUM_VALUES': ',\n    '.join(enum_values),
        'ENUM_TO_STRING_CASES': '\n            '.join(enum_to_string_cases),
        'STRING_TO_ENUM_LOGIC': '\n        '.join(string_to_enum_logic),
        'ENUM_STRING_VALUES': enum_string_values,
        'ENUM_DISPLAY_NAMES': enum_display_names,
        'DEFAULT_ENUM_VALUE': default_enum_value
    }
    
    return render_template(templates['enum'], variables)

def generate_header_file(parsed_data, source_file, output_file, config, templates):
    """
    生成头文件
    
    Args:
        parsed_data: 解析的Mota数据
        source_file: 源文件路径
        output_file: 输出文件路径
        config: 配置信息
        templates: 模板字典
    
    Returns:
        None
    """
    blocks = parsed_data['blocks']
    structs = parsed_data['structs']
    enums = parsed_data['enums']
    
    # 生成所有块类的代码
    block_codes = []
    for block in blocks:
        block_codes.append(generate_block_code(block, config, templates))
    
    # 生成所有结构体的代码
    struct_codes = []
    for struct in structs:
        struct_codes.append(generate_struct_code(struct, config, templates))
    
    # 生成所有枚举的代码
    enum_codes = []
    for enum in enums:
        enum_codes.append(generate_enum_code(enum, config, templates))
    
    # 合并所有代码
    content = '\n\n'.join(enum_codes + struct_codes + block_codes)
    
    # 获取命名空间设置
    namespace_enabled = config.get('namespace', {}).get('enable', True)
    namespace = config.get('namespace', {}).get('default', 'yima')
    
    # 渲染头文件模板
    variables = {
        'GENERATION_TIME': datetime.datetime.now().strftime('%Y-%m-%d %H:%M:%S'),
        'SOURCE_FILE': os.path.basename(source_file),
        'CONTENT': content,
        'NAMESPACE': namespace,
        'HAS_NAMESPACE': namespace_enabled
    }
    
    header_content = render_template(templates['header'], variables)
    
    # 确保输出目录存在
    os.makedirs(os.path.dirname(output_file), exist_ok=True)
    
    # 写入文件
    with open(output_file, 'w', encoding='utf-8-sig') as f:
        f.write(header_content)
    
    print(f"生成文件: {output_file}")

def load_templates(template_dir):
    """
    加载所有模板文件
    
    Args:
        template_dir: 模板目录
    
    Returns:
        包含所有模板的字典
    """
    templates = {}
    
    # 加载配置文件
    config_path = os.path.join(template_dir, 'generator_config.json')
    with open(config_path, 'r', encoding='utf-8-sig') as f:
        config = json.load(f)
    
    # 加载模板文件
    for key, filename in config['templates'].items():
        template_path = os.path.join(template_dir, filename)
        with open(template_path, 'r', encoding='utf-8-sig') as f:
            templates[key] = f.read()
    
    return templates, config

def main():
    parser = argparse.ArgumentParser(description='从Mota定义生成C++代码')
    parser.add_argument('input', help='输入的Mota定义文件')
    parser.add_argument('--template-dir', default='template/yima-cpp', help='模板目录')
    parser.add_argument('--output-dir', help='输出目录')
    
    args = parser.parse_args()
    
    # 加载模板和配置
    templates, config = load_templates(args.template_dir)
    
    # 解析Mota文件
    parsed_data = parse_mota_file(args.input)
    
    # 确定输出目录
    output_dir = args.output_dir or config['output']['directory']
    
    # 生成输出文件路径
    input_filename = os.path.splitext(os.path.basename(args.input))[0]
    output_file = os.path.join(output_dir, f"{input_filename}{config['output']['extension']}")
    
    # 生成头文件
    generate_header_file(parsed_data, args.input, output_file, config, templates)

if __name__ == '__main__':
    main()
