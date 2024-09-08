import os
import argparse

DIVIEDE_LINE = '########################################################################################\n'

def append_files_to_txt(directory_path, output_file, overwrite=True):
    """
    将指定目录下所有文件的内容追加到一个文本文件中。
    
    :param directory_path: 包含需要合并的文件的目录路径
    :param output_file: 输出文件的路径
    """

    if overwrite:
        # 创建或清空输出文件
        with open(output_file, 'w', encoding='utf-8') as outfile:
            pass  # 只是清空文件
    
    # 遍历指定目录下的所有文件
    for root, dirs, files in os.walk(directory_path):
        for file in files:
            file_path = os.path.join(root, file)
            try:
                # 打开文件并读取内容
                with open(file_path, 'r', encoding='utf-8') as infile:
                    content = infile.read()
                    # 追加到输出文件
                    with open(output_file, 'a', encoding='utf-8') as outfile:
                        outfile.write(f"--- File: {file} ---\n")
                        outfile.write(content)
                        outfile.write('\n')
                        outfile.write(DIVIEDE_LINE)
            except Exception as e:
                print(f"Error reading file {file_path}: {e}")


if __name__ == "__main__":
    parser = argparse.ArgumentParser(description="Append all files in a directory to a single text file.")
    parser.add_argument("directory", help="Path to the directory containing the files.")
    parser.add_argument("output", help="Path to the output text file.")
    parser.add_argument(
        "-n", "--no-overwrite",
        action="store_false",
        dest="overwrite",
        help="Do not overwrite existing output file."
    )

    args = parser.parse_args()

    append_files_to_txt(args.directory, args.output, args.overwrite)