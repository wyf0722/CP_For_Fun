import os
import shutil

def divide_folders_by_numeric_range(src_folder, dest_base_folder, group_size=10):
    # 获取src_folder下的所有子文件夹，并尝试将它们的名字转换为整数
    subfolders = [f for f in os.listdir(src_folder) if os.path.isdir(os.path.join(src_folder, f))]
    
    # 尝试将文件夹名转成整数，并过滤掉无法转换成整数的文件夹
    try:
        subfolder_nums = [(int(f), f) for f in subfolders]
    except ValueError:
        print("存在不能转换为整数的文件夹名称，请确保文件夹名称可以被转换为整数。")
        return
    
    # 根据数字排序
    subfolder_nums.sort(key=lambda x: x[0])

    for f in subfolders:
        group_index = int(f) // 10
        group_start = group_index * 10
        group_end = group_start + 9
        target_folder_name = f"{group_start}-{group_end}"
        target_folder_path = os.path.join(dest_base_folder, target_folder_name)
        print(f, target_folder_name, target_folder_path)
        if not os.path.exists(target_folder_path):
            os.makedirs(target_folder_path)
        shutil.copytree(os.path.join(src_folder, f), os.path.join(target_folder_path, f))
    # # 遍历子文件夹，并按照数值范围以及10的整数倍规则分配到不同的目录中
    # current_group_start = None
    # current_group = []
    # for num, folder_name in subfolder_nums:
    #     if current_group_start is None or num >= current_group_start + len(current_group) * group_size:
    #         # 新建一个组
    #         if current_group:
    #             # 移动当前组
    #             start_index = current_group_start
    #             end_index = start_index + min(group_size, len(current_group)) - 1
    #             target_folder_name = f"{start_index}-{end_index}"
    #             target_folder_path = os.path.join(dest_base_folder, target_folder_name)
    #             if not os.path.exists(target_folder_path):
    #                 os.makedirs(target_folder_path)
    #             for _, fname in current_group:
    #                 shutil.move(os.path.join(src_folder, fname), os.path.join(target_folder_path, fname))
            
    #         # 更新current_group_start到下一个10的整数倍
    #         current_group_start = (num // group_size) * group_size
    #         current_group = [(num, folder_name)]
    #     else:
    #         current_group.append((num, folder_name))
    
    # # 处理最后一组
    # if current_group:
    #     start_index = current_group_start
    #     end_index = start_index + min(group_size, len(current_group)) - 1
    #     target_folder_name = f"{start_index}-{end_index}"
    #     target_folder_path = os.path.join(dest_base_folder, target_folder_name)
    #     if not os.path.exists(target_folder_path):
    #         os.makedirs(target_folder_path)
    #     for _, fname in current_group:
    #         shutil.move(os.path.join(src_folder, fname), os.path.join(target_folder_path, fname))

# 使用函数
src_folder = '.\\weekly'  # 替换为你的源文件夹路径
dest_base_folder = '.\\weekly_new'  # 替换为你想要存放划分后文件夹的基础目录
divide_folders_by_numeric_range(src_folder, dest_base_folder)