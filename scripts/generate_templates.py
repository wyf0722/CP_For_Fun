import os
import json
from pathlib import Path

def read_template_files(directory):
    templates = {}
    base_path = Path(directory)
    
    for root, _, files in os.walk(directory):
        # 计算相对路径作为分类
        rel_path = os.path.relpath(root, directory)
        if rel_path == '.':
            category = 'root'
        else:
            category = rel_path.replace('\\', '/')
            
        if category not in templates:
            templates[category] = {}
            
        for file in files:
            if file.endswith(('.cpp', '.hpp', '.py')):
                with open(os.path.join(root, file), 'r', encoding='utf-8') as f:
                    templates[category][file] = f.read()
    
    return templates

def main():
    base_dir = Path(__file__).parent.parent
    pages_dir = base_dir / '.github' / 'pages'
    pages_dir.mkdir(exist_ok=True, parents=True)
    
    # 生成C++和Python模板JSON
    for lang, dir_name in [('cpp', 'Copypasta_Cpp'), ('python', 'Copypasta_Python')]:
        templates = read_template_files(base_dir / dir_name)
        with open(pages_dir / f'templates_{lang}.json', 'w', encoding='utf-8') as f:
            json.dump(templates, f, ensure_ascii=False, indent=2)
    
    # 复制网页文件到pages目录
    html_file = base_dir / 'docs' / 'index.html'
    css_file = base_dir / 'docs' / 'style.css'
    js_file = base_dir / 'docs' / 'script.js'
    
    if html_file.exists():
        with open(html_file, 'r', encoding='utf-8') as src, open(pages_dir / 'index.html', 'w', encoding='utf-8') as dst:
            dst.write(src.read())
    
    if css_file.exists():
        with open(css_file, 'r', encoding='utf-8') as src, open(pages_dir / 'style.css', 'w', encoding='utf-8') as dst:
            dst.write(src.read())
    
    if js_file.exists():
        with open(js_file, 'r', encoding='utf-8') as src, open(pages_dir / 'script.js', 'w', encoding='utf-8') as dst:
            dst.write(src.read())

if __name__ == '__main__':
    main()