import os
import json
from pathlib import Path

def read_template_files(directory):
    templates = {}
    for root, _, files in os.walk(directory):
        category = os.path.basename(root)
        if category not in templates:
            templates[category] = {}
            
        for file in files:
            if file.endswith(('.cpp', '.hpp', '.py')):
                with open(os.path.join(root, file), 'r', encoding='utf-8') as f:
                    templates[category][file] = f.read()
    
    return templates

def main():
    base_dir = Path(__file__).parent.parent
    docs_dir = base_dir / 'docs'
    
    # 确保docs目录存在
    docs_dir.mkdir(exist_ok=True)
    
    # 生成C++模板JSON
    cpp_templates = read_template_files(base_dir / 'Copypasta_Cpp')
    with open(docs_dir / 'templates_cpp.json', 'w', encoding='utf-8') as f:
        json.dump(cpp_templates, f, ensure_ascii=False, indent=2)
    
    # 生成Python模板JSON
    python_templates = read_template_files(base_dir / 'Copypasta_Python')
    with open(docs_dir / 'templates_python.json', 'w', encoding='utf-8') as f:
        json.dump(python_templates, f, ensure_ascii=False, indent=2)

if __name__ == '__main__':
    main()