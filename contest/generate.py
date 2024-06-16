import os
import sys


def create_files(file_names):
    """在Temporary目录下创建文件"""
    script_dir = os.path.dirname(os.path.abspath(__file__))
    script_dir = os.path.join(script_dir, 'Cache_For_Contest')
    
    # 遍历文件名列表，创建每个文件
    for file_name in file_names:
        file_path = os.path.join(script_dir, file_name)
        with open(file_path, "w") as f:  # 'w'模式会创建文件，如果文件已存在则覆盖
            f.write("")  # 写入空内容，创建空文件
        print(f"文件 {file_name} 已创建于 {file_path}")


if __name__ == "__main__":
    # sys.argv[1:]会获取命令行参数中脚本名之后的所有参数
    file_names = sys.argv[1:]

    if not file_names:
        print("请提供要创建的文件名。")
    else:
        create_files(file_names)
