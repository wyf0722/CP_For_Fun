/*************************************************************************
    > File Name: B.cpp
    > Author: Wu YiFan
    > Github: https://github.com/wyf0722
    > Mail: wyf0722chosen@gmail.com
    > Created Time: 2025-01-05 18:38
************************************************************************/
#include <bits/stdc++.h>

using namespace std;

template<typename A, typename B> ostream& operator<<(ostream &os, const pair<A, B> &p) { return os << '(' << p.first << ", " << p.second << ')'; }
template<typename T_container, typename T = typename enable_if<!is_same<T_container, string>::value, typename T_container::value_type>::type> ostream& operator<<(ostream &os, const T_container &v) { os << '{'; string sep; for (const T &x : v) os << sep << x, sep = ", "; return os << '}'; }

void dbg_out() { cout << endl; }
template<typename Head, typename... Tail> void dbg_out(Head H, Tail... T) { cout << ' ' << H; dbg_out(T...); }
#define debug(...) cout << '[' << __LINE__ << "] (" << #__VA_ARGS__ << "):", dbg_out(__VA_ARGS__)

using i64 = long long;
const int inf = INT_MAX / 2 - 100;
const i64 infLL = LLONG_MAX / 3;
constexpr int MOD = 998244353; // 998244353 1000000007
int dx[4]{1, 0, -1, 0}, dy[4]{0, 1, 0, -1};
template <class T> using V = vector<T>;
template<typename T> using min_heap=priority_queue<T,vector<T>,greater<T>>;
template<typename T> using max_heap=priority_queue<T>;

constexpr int popcount(int x) { return __builtin_popcount(x); }
constexpr int topbit(int x) { return x == 0 ? 0 : 31 - __builtin_clz(x); }

template <class T> bool chmin(T& a, const T& b) { return b < a ? a = b, 1 : 0; }  // set a = min(a,b)
template <class T> bool chmax(T& a, const T& b) { return a < b ? a = b, 1 : 0; }  // set a = max(a,b)

template<class T, class U> T fstTrue(T lo, T hi, U f) { ++hi; assert(lo <= hi); while (lo < hi) { T mid = lo + (hi - lo) / 2; f(mid) ? hi = mid : lo = mid + 1; } return lo; }
template<class T, class U> T lstTrue(T lo, T hi, U f) { --lo; assert(lo <= hi); while (lo < hi) { T mid = lo + (hi - lo + 1) / 2; f(mid) ? lo = mid : hi = mid - 1; } return lo; }

class TaskManager {
private:
    max_heap<pair<int, int>> h;
    unordered_map<int, int> taskId2userId;
    unordered_map<int, int> taskId2priority;
    unordered_set<int> exist;

public:
    TaskManager(vector<vector<int>>& tasks) {
        for (auto &task : tasks) {
            int userId = task[0], taskId = task[1], priority = task[2];
            exist.insert(taskId);
            taskId2userId[taskId] = userId;
            taskId2priority[taskId] = priority;
            h.emplace(priority, taskId);
        }
    }
    
    void add(int userId, int taskId, int priority) {
        exist.insert(taskId);
        taskId2userId[taskId] = userId;
        taskId2priority[taskId] = priority;
        h.emplace(priority, taskId);
    }
    
    void edit(int taskId, int newPriority) {
        taskId2priority[taskId] = newPriority;
        h.emplace(newPriority, taskId);
    }
    
    void rmv(int taskId) {
        taskId2userId.erase(taskId);
        taskId2priority.erase(taskId);
        exist.erase(taskId);
    }
    
    int execTop() {
        while (!h.empty()) {
            auto [priority, taskId] = h.top();
            h.pop();
            debug(priority, taskId);
            if (exist.find(taskId) == exist.end()) {
                continue;
            }
            if (taskId2priority[taskId] != priority) {
                continue;
            }
            int userId = taskId2userId[taskId];
            rmv(taskId);
            debug(userId);
            return userId;
        }
        return -1;
    }
};

/**
 * Your TaskManager object will be instantiated and called as such:
 * TaskManager* obj = new TaskManager(tasks);
 * obj->add(userId,taskId,priority);
 * obj->edit(taskId,newPriority);
 * obj->rmv(taskId);
 * int param_4 = obj->execTop();
 */