#include "./basic.h"

//! 计算next数组
vector<int> getNext(string pattern) {
    int n = pattern.size();
    vector<int> ans(n, 0);
    // 对于模式串的第一位到最后一位
    for (int i = 0; i < n; i++) {
        // j代表考察的前后缀长度
        for (int j = i; j >= 1; j--) {
            // [0,j-1] and [i-j+1,i] 
            if(pattern.substr(0, j) == pattern.substr(i - j + 1, j)) {
                ans[i] = j;
                break;
            }
        }
    }
    return ans;
}

vector<int> prefix_function1(string s) {
  int n = (int)s.length();
  vector<int> pi(n);
  for (int i = 1; i < n; i++)
    for (int j = i; j >= 0; j--)
      if (s.substr(0, j) == s.substr(i - j + 1, j)) {
        pi[i] = j;
        break;
      }
  return pi;
}

vector<int> prefix_function2(string s) {
  int n = (int)s.length();
  vector<int> pi(n);
  for (int i = 1; i < n; i++) {
    int j = pi[i - 1];
    while (j > 0 && s[i] != s[j]) j = pi[j - 1];
    if (s[i] == s[j]) j++;
    pi[i] = j;
  }
  return pi;
}


int main() {
    // target and pattern
    string t = "ABABAABAA CAADB ABABCAADKDABC", p = "ABABC";
    vector<int> next = prefix_function1(p);
    cout << to_string(next) << endl;
    vector<int> nextt = prefix_function2(p);
    cout << to_string(nextt) << endl;

    //! kmp匹配代码，i在t中只前进，不后退
    int i = 0, j = 0;
    while(i < t.size()) {
        if (t[i] == p[j]) {
            i++;
            j++;
        }else if (j == 0) {
            //* 第一个字符就不相等
            i++;
        }else{
            //* 匹配到第j个字符不相等，查询next[j - 1]
            j = next[j - 1];
        }
        //* 到达模式串尾部
        if (j == p.size()) {
            break;
        }
    }
    printf("in target position %d, got pattern", i - j);
    cout << t.substr(i - j, j) << endl;
    printf("used stl func, in target postion %d, got pattern", t.find(p));
    return 0;
}