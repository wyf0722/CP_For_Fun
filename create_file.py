import os
import sys

def create_file(path, file_name):
    try:
        # 组合路径和文件名
        file_path = os.path.join(path, file_name)
        
        # 获取文件扩展名
        _, file_ext = os.path.splitext(file_name)
        
        # 计算模板文件夹的路径（与脚本在同一目录）
        script_dir = os.path.dirname(os.path.abspath(__file__))

        # 根据文件扩展名选择模板文件
        if file_ext == '.py':
            template_file = 'template.py'
        elif file_ext == '.cpp':
            template_file = 'template.cpp'
        else:
            template_file = None
        print(script_dir)
        print(template_file)
        # 检查路径是否存在
        if not os.path.exists(path):
            # 如果路径不存在则创建路径
            os.makedirs(path)

        # 创建并打开新文件
        with open(file_path, 'w') as file:
            # 如果存在模板文件，则读取并写入模板内容
            if template_file and os.path.exists(os.path.join(script_dir, template_file)):
                with open(os.path.join(script_dir, template_file), 'r') as template:
                    file.write(template.read())
            else:
                print('cant open')
                file.write("")  # 没有模板或找不到模板，写入空内容

        print(f"File '{file_name}' created successfully at '{path}'.")
    except Exception as e:
        print(f"An error occurred: {e}")

if __name__ == "__main__":
    if len(sys.argv) != 3:
        print(f"Usage: {sys.argv[0]} <path> <file_name>")
        sys.exit(1)

    path = sys.argv[1]
    file_name = sys.argv[2]
    create_file(path, file_name)