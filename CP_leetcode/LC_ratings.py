# 获取 https://raw.githubusercontent.com/zerotrac/leetcode_problem_rating/main/data.json 数据
import requests
import json
import os


def fetch_leetcode_ratings():
    url = "https://raw.githubusercontent.com/zerotrac/leetcode_problem_rating/main/data.json"

    # 添加请求头，模拟浏览器行为
    headers = {
        "User-Agent":
        "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/91.0.4472.124 Safari/537.36"
    }

    try:
        # 发送GET请求获取数据
        response = requests.get(url, headers=headers)
        response.raise_for_status()  # 如果请求失败则抛出异常

        # 解析JSON数据
        data = response.json()

        # 获取脚本所在目录
        script_dir = os.path.dirname(os.path.abspath(__file__))
        output_file = os.path.join(script_dir, "leetcode_ratings.json")

        # 将数据保存到本地文件
        with open(output_file, "w", encoding="utf-8") as f:
            json.dump(data, f, ensure_ascii=False, indent=4)

        print(f"成功获取数据并保存到 {output_file}，共 {len(data)} 条题目记录")
        return data

    except requests.exceptions.RequestException as e:
        print(f"请求失败: {e}")
    except json.JSONDecodeError:
        print("JSON解析失败，返回的数据格式不正确")
    except Exception as e:
        print(f"发生错误: {e}")

    return None


if __name__ == "__main__":
    print("开始获取LeetCode题目评分数据...")
    data = fetch_leetcode_ratings()

    if data:
        # 展示前5条数据作为示例
        print(data[:5])
