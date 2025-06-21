/*************************************************************************
    > File Name: C.cpp
    > Author: Wu YiFan
    > Github: https://github.com/wyf0722
    > Mail: wyf0722chosen@gmail.com
    > Created Time: 2025-06-22 00:38
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

// https://github.com/Joshc88/CPTemplates/blob/main/Math/primes.h
const int MX = 1e5 + 10;
struct Primes {
    vector<int> lpf, lpfcnt, primes, remaining;

    Primes(int n) {
        lpf.resize(n + 1);
        lpfcnt.resize(n + 1);
        remaining.resize(n + 1);
        for (int i = 2; i <= n; i++) {
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
                if (primes[j] == lpf[i])
                    break;
            }
        }
    }

    bool isprime(long long x) {
        if (x < 2)
            return false;
        if (x < lpf.size())
            return lpf[x] == x;
        for (long long i = 2; i * i <= x; i++) {
            if (!(x % i))
                return false;
        }
        return true;
    }

    vector<pair<int, int>> factorise(int x) {
        vector<pair<int, int>> factors;
        for (; x > 1; x = remaining[x])
            factors.emplace_back(lpf[x], lpfcnt[x]);
        return factors;
    }
} primes(MX);

template <typename T, class Compare = std::less<T>> class RangeMinQuery : private Compare {
    static const int BUCKET_SIZE = 32;
    static const int BUCKET_SIZE_LOG = 5;
    static_assert(BUCKET_SIZE == (1 << BUCKET_SIZE_LOG), "BUCKET_SIZE should be a power of 2");
    static const int CACHE_LINE_ALIGNMENT = 64;
    int n = 0;
    std::vector<T> data;
    std::vector<T> pref_data;
    std::vector<T> suff_data;
    std::vector<T> sparse_table;
    std::vector<uint32_t> range_mask;

private:
    int num_buckets() const {
        return n >> BUCKET_SIZE_LOG;
    }
    int num_levels() const {
        return num_buckets() ? 32 - __builtin_clz(num_buckets()) : 0;
    }
    int sparse_table_size() const {
        return num_buckets() * num_levels();
    }
private:
    const T& min(const T& a, const T& b) const {
        return Compare::operator()(a, b) ? a : b;
    }
    void setmin(T& a, const T& b) const {
        if (Compare::operator()(b, a)) a = b;
    }

    template <typename Vec> static int get_size(const Vec& v) { using std::size; return int(size(v)); }

public:
    RangeMinQuery() {}
    template <typename Vec> explicit RangeMinQuery(const Vec& data_, const Compare& comp_ = Compare())
        : Compare(comp_)
        , n(get_size(data_))
        , data(n)
        , pref_data(n)
        , suff_data(n)
        , sparse_table(sparse_table_size())
        , range_mask(n)
    {
        for (int i = 0; i < n; i++) data[i] = data_[i];
        for (int i = 0; i < n; i++) {
            if (i & (BUCKET_SIZE-1)) {
                uint32_t m = range_mask[i-1];
                while (m && !Compare::operator()(data[(i | (BUCKET_SIZE-1)) - __builtin_clz(m)], data[i])) {
                    m -= uint32_t(1) << (BUCKET_SIZE - 1 - __builtin_clz(m));
                }
                m |= uint32_t(1) << (i & (BUCKET_SIZE - 1));
                range_mask[i] = m;
            } else {
                range_mask[i] = 1;
            }
        }
        for (int i = 0; i < n; i++) {
            pref_data[i] = data[i];
            if (i & (BUCKET_SIZE-1)) {
                setmin(pref_data[i], pref_data[i-1]);
            }
        }
        for (int i = n-1; i >= 0; i--) {
            suff_data[i] = data[i];
            if (i+1 < n && ((i+1) & (BUCKET_SIZE-1))) {
                setmin(suff_data[i], suff_data[i+1]);
            }
        }
        for (int i = 0; i < num_buckets(); i++) {
            sparse_table[i] = data[i * BUCKET_SIZE];
            for (int v = 1; v < BUCKET_SIZE; v++) {
                setmin(sparse_table[i], data[i * BUCKET_SIZE + v]);
            }
        }
        for (int l = 0; l+1 < num_levels(); l++) {
            for (int i = 0; i + (1 << (l+1)) <= num_buckets(); i++) {
                sparse_table[(l+1) * num_buckets() + i] = min(sparse_table[l * num_buckets() + i], sparse_table[l * num_buckets() + i + (1 << l)]);
            }
        }
    }

    T query(int l, int r) const {
        assert(l <= r);
        int bucket_l = (l >> BUCKET_SIZE_LOG);
        int bucket_r = (r >> BUCKET_SIZE_LOG);
        if (bucket_l == bucket_r) {
            uint32_t msk = range_mask[r] & ~((uint32_t(1) << (l & (BUCKET_SIZE-1))) - 1);
            int ind = (l & ~(BUCKET_SIZE-1)) + __builtin_ctz(msk);
            return data[ind];
        } else {
            T ans = min(suff_data[l], pref_data[r]);
            bucket_l++;
            if (bucket_l < bucket_r) {
                int level = (32 - __builtin_clz(bucket_r - bucket_l)) - 1;
                setmin(ans, sparse_table[level * num_buckets() + bucket_l]);
                setmin(ans, sparse_table[level * num_buckets() + bucket_r - (1 << level)]);
            }
            return ans;
        }
    }
};

template <typename T> using RangeMaxQuery = RangeMinQuery<T, std::greater<T>>;

class Solution {
public:
    int primeSubarray(vector<int>& nums, int k) {
        int n = nums.size();
        vector<int> mx_v(nums), mn_v(nums), pre(n);
        int pre_pos = -1;
        for (int i = 0; i < n; i++) {
            pre[i] = pre_pos;
            if (!primes.isprime(nums[i])) {
                mx_v[i] = -inf;
                mn_v[i] = inf;
            } else {
                pre_pos = i;
            }
        }
        RangeMaxQuery<int> mxq(mx_v);
        RangeMinQuery<int> mnq(mn_v);
        int ans = 0;
        for (int i = 0; i < n; i++) {
            int R = -1;
            if (primes.isprime(nums[i])) {
                // 前一个质数
                if (pre[i] != -1) {
                    R = pre[i];
                }
            } else {
                // 前两个质数
                if (pre[i] != -1 && pre[pre[i]] != -1) {
                    R = pre[pre[i]];
                }
            }
            if (R == -1) continue;
            if (mxq.query(R, i) - mnq.query(R, i) > k) continue;
            int lo = -1, hi = R;
            while (lo + 1 < hi) {
                int mid = (lo + hi) / 2;
                if (mxq.query(mid, i) - mnq.query(mid, i) <= k) {
                    hi = mid;
                } else {
                    lo = mid;
                }
            }
            // [hi, R] 符合
            ans += R - hi + 1;
        }
        return ans;
    }
};