#include <bits/stdc++.h>

using namespace std;

string to_string(string s) {
    return '"' + s + '"';
}

string to_string(const char* s) {
    return to_string((string)s);
}

string to_string(bool b) {
    return (b ? "true" : "false");
}

template <typename A, typename B>
string to_string(pair<A, B> p) {
    return "(" + to_string(p.first) + ", " + to_string(p.second) + ")";
}

template <typename A>
string to_string(A v) {
    bool first = true;
    string res = "{";
    for (const auto& x : v) {
        if (!first) {
            res += ", ";
        }
        first = false;
        res += to_string(x);
    }
    res += "}";
    return res;
}

void debug_out() {
    cout << endl;
}

template <typename Head, typename... Tail>
void debug_out(Head H, Tail... T) {
    cout << " " << to_string(H);
    debug_out(T...);
}

#define debug(...)                                  \
    cout << __FUNCTION__ << ":" << __LINE__ << "->" \
         << " [" << #__VA_ARGS__ << "] =",          \
        debug_out(__VA_ARGS__)


#define all(x) begin(x), end(x)
#define rep(i, a, b) for (int i = a; i < (b); i++)
#define rrep(i, a, b) for (int i = a; i >= b; i--)
using i64 = long long;
using ll = long long;
using pii = pair<int, int>;
using vi = vector<int>;
using vl = vector<ll>;
using vvl = vector<vector<ll>>;
using vvi = vector<vector<int>>;
using vpii = vector<pair<int, int>>;
const int inf = INT_MAX / 2 - 100;
const i64 infLL = LLONG_MAX / 3;
const long long MOD = 1e9 + 7;
const int dx[4]{1, 0, -1, 0}, dy[4]{0, 1, 0, -1};

template <class T>
void mkuni(vector<T>& v) {
    sort(all(v));
    v.erase(unique(all(v)), v.end());
}

template <class T>
int lwb(vector<T>& a, const T& b) {
    return int(lower_bound(all(a), b) - begin(a));
}

template <class T>
int upb(vector<T>& a, const T& b) {
    return int(upper_bound(all(a), b) - begin(a));
}

constexpr int popcount(int x) {
    return __builtin_popcount(x);
}

constexpr int topbit(int x) {
    return x == 0 ? 0 : 31 - __builtin_clz(x);
}

template <class T, class U>
void safeErase(T& t, const U& u) {
    auto it = t.find(u);
    assert(it != end(t));
    t.erase(it);
}

template <class T>
vector<int> sortidx(const vector<T>& a) {
    int n = a.size();
    vector<int> idx(n);
    iota(idx.begin(), idx.end(), 0);
    sort(idx.begin(), idx.end(), [&](int i, int j) { return a[i] < a[j]; });
    return idx;
}

template <class T, class S = T>
S SUM(const vector<T>& a) {
    return accumulate(a.begin(), a.end(), S(0));
}

template <class T>
T MAX(const vector<T>& a) {
    return *max_element(a.begin(), a.end());
}

template <class T>
T MIN(const vector<T>& a) {
    return *min_element(a.begin(), a.end());
}

template <class T>
bool chmin(T& a, const T& b) {
    return b < a ? a = b, 1 : 0;
}  // set a = min(a,b)
template <class T>
bool chmax(T& a, const T& b) {
    return a < b ? a = b, 1 : 0;
}  // set a = max(a,b)

/*
 *             _       _   _                      __                   __
 *   ___  ___ | |_   _| |_(_) ___  _ __     ___  / _| __      ___   _ / _|
 *  / __|/ _ \| | | | | __| |/ _ \| '_ \   / _ \| |_  \ \ /\ / / | | | |_
 *  \__ \ (_) | | |_| | |_| | (_) | | | | | (_) |  _|  \ V  V /| |_| |  _|
 *  |___/\___/|_|\__,_|\__|_|\___/|_| |_|  \___/|_|     \_/\_/  \__, |_|
 *                                                              |___/
 */

struct DSU {
    std::vector<int> f, siz;
     
    DSU() {}
    DSU(int n) {
        init(n);
    }
     
    void init(int n) {
        f.resize(n);
        std::iota(f.begin(), f.end(), 0);
        siz.assign(n, 1);
    }
     
    int find(int x) {
        while (x != f[x]) {
            x = f[x] = f[f[x]];
        }
        return x;
    }
     
    bool same(int x, int y) {
        return find(x) == find(y);
    }
     
    bool merge(int x, int y) {
        x = find(x);
        y = find(y);
        if (x == y) {
            return false;
        }
        siz[x] += siz[y];
        f[y] = x;
        return true;
    }
     
    int size(int x) {
        return siz[find(x)];
    }
};
const int MX = 1e5 + 10;
struct Primes {
    vector<int> lpf, lpfcnt, primes, remaining;

    Primes(int n) {
        lpf.resize(n+1);
        lpfcnt.resize(n+1);
        remaining.resize(n+1);
        for (int i=2; i<=n; i++) {
            if (!lpf[i]) {
                lpf[i] = i;
                lpfcnt[i] = remaining[i] = 1;
                primes.push_back(i);
            }
            for (int j = 0; i * primes[j] <= n; j++) {
                int val = i * primes[j];
                lpf[val] = primes[j];
                lpfcnt[val] = lpfcnt[primes[j]] + (lpf[i] == primes[j] ? lpfcnt[i] : 0);
                remaining[val] = (lpf[i] == primes[j]) ? remaining[i] : i;
                if (primes[j] == lpf[i]) break;
            }
        }
    }

    bool isprime(long long x) {
        if (x < 2) return false;
        if (x < lpf.size()) return lpf[x] == x;
        for (long long i=2; i*i<=x; i++) {
            if (!(x%i)) return false;
        }
        return true;
    }

    vector<pair<int, int>> factorise(int x) {
        vector<pair<int, int>> factors;
        for (; x > 1; x = remaining[x]) factors.emplace_back(lpf[x], lpfcnt[x]);
        return factors;
    }
} primes(MX);

class Solution {
public:
    bool gcdSort(vector<int>& nums) {
        int n = nums.size();
        DSU dsu(n + MX);
        for (int i = 0; i < n; i++) {
            for (auto [p, _]: primes.factorise(nums[i])) {
                dsu.merge(i, p + n);
            }
        }

        unordered_map<int, vector<int>> mp;
        for (int i = 0; i < n; i++) {
            mp[dsu.find(i)].push_back(i);
        }
        for (auto &[_, v]: mp) {
            vi vals;
            for (int idx: v) vals.push_back(nums[idx]);
            sort(all(vals));
            for (int i = 0; i < vals.size(); i++) nums[v[i]] = vals[i];
        }
        for (int i = 1; i < n; i++) if (nums[i - 1] > nums[i]) return false;
        return true;
    }
};
