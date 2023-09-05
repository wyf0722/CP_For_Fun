#include "..\leetcode.h"

// ! 数组存储
struct trie {
    int nex[100000][26], cnt;
    bool exist[100000];  // 该结点结尾的字符串是否存在

    void insert(char* s, int l) {  // 插入字符串
        int p = 0;
        for (int i = 0; i < l; i++) {
            int c = s[i] - 'a';
            if (!nex[p][c])
                nex[p][c] = ++cnt;  // 如果没有，就添加结点
            p = nex[p][c];
        }
        exist[p] = 1;
    }

    bool find(char* s, int l) {  // 查找字符串
        int p = 0;
        for (int i = 0; i < l; i++) {
            int c = s[i] - 'a';
            if (!nex[p][c])
                return 0;
            p = nex[p][c];
        }
        return exist[p];
    }
};

// ! 指针实现 
struct Trie {
    struct Node {
        Node* son[26];

        Node() {
            memset(son, 0, sizeof(son));
        }
    };

    Node* root;

    Trie() { root = new Node(); }

    void add(string& s) {
        auto cur = root;
        for (auto i : s) {
            i -= 'a';
            if (!cur->son[i]) {
                cur->son[i] = new Node();
            }
            cur = cur->son[i];
        }
    }

    bool query(string& s) {
        auto cur = root;
        bool flag = true;
        for (auto i : s) {
            i -= 'a';
            if (!cur->son[i]) {
                flag = false;
                break;
            }
            cur = cur->son[i];
        }
        return flag;
    }
};

int main() {
    Trie tr;
    int t;
    cout << "input the number of strings:\n";
    cin >> t;
    while (t--) {
        cout << "input the string:\t";
        string str;
        cin >> str;
        tr.add(str);
    }
    string input;
    cout << "input the string you want to input:\n";
    cin >> input;
    cout << tr.query(input);
    return 0;
}