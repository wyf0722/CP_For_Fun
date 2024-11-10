import os
import json
import sys
import argparse

# 获取当前脚本所在的目录
script_dir = os.path.dirname(os.path.realpath(__file__))

# 设置命令行参数
parser = argparse.ArgumentParser(description="Generate VSCode snippets from source files.")
parser.add_argument(
    "-d", "--directory", type=str, default=".",
    help="Relative directory to search for source files (default: current script's directory)"
)
parser.add_argument(
    "-e", "--extensions", type=str, nargs='+', default=["cpp"],
    help="List of file extensions to create snippets from (default: ['cpp'])"
)
parser.add_argument(
    "-o", "--output", type=str, default="cpp.json",
    help="Output file for the generated snippets (default: cpp.json)"
)

args = parser.parse_args()

# 将输入目录转换为相对于脚本目录的绝对路径
search_dir = os.path.abspath(os.path.join(script_dir, args.directory))

snippets = {}

# Walk through the specified directory
for subdir in os.walk(search_dir):
    # Ignore hidden directories and .git
    if subdir[0].startswith('.') or '.git' in subdir[0]:
        continue

    # Process each file in the current directory
    for filename in subdir[2]:
        # Split file name and extension
        name, extension = os.path.splitext(filename)
        extension = extension.lstrip('.')  # Remove dot from extension for comparison
        
        # Skip files without the specified extensions
        if extension not in args.extensions:
            continue

        # Check for duplicate snippets
        if name in snippets:
            print(f'Error: Duplicate snippet {name}', file=sys.stderr)
            sys.exit(1)

        # Read the file and create a snippet
        path = os.path.join(subdir[0], filename)
        with open(path, 'r', encoding='utf-8') as f:
            snippet = {
                "prefix": name,
                "body": [line.rstrip() for line in f.readlines()],
                "description": name
            }
            snippets[name] = snippet

        print(f'Generated snippet for {name}', file=sys.stderr)

# Write snippets to the specified output file
with open(args.output, 'w', encoding='utf-8') as f:
    f.write(json.dumps(snippets, indent=2))

print('Snippets generation completed', file=sys.stderr)
