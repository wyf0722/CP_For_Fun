#include <bits/stdc++.h>

using namespace std;

template<typename A, typename B> ostream& operator<<(ostream &os, const pair<A, B> &p) { return os << '(' << p.first << ", " << p.second << ')'; }
template<typename T_container, typename T = typename enable_if<!is_same<T_container, string>::value, typename T_container::value_type>::type> ostream& operator<<(ostream &os, const T_container &v) { os << '{'; string sep; for (const T &x : v) os << sep << x, sep = ", "; return os << '}'; }

void dbg_out() { cout << endl; }
template<typename Head, typename... Tail> void dbg_out(Head H, Tail... T) { cout << ' ' << H; dbg_out(T...); }
#define debug(...) cout << '[' << __LINE__ << "] (" << #__VA_ARGS__ << "):", dbg_out(__VA_ARGS__)

#define all(x) begin(x), end(x)
#define rall(x) begin(x), end(x)
// loops
#define FOR(i, a, b) for (int i = (a); i < (b); ++i)
#define ROF(i, a, b) for (int i = (b)-1; i >= (a); --i)
#define rep(a) F0R(_, a)
#define each(a, x) for (auto &a : x)
using i64 = long long;
using ll = long long;
using pii = pair<int, int>;
using pll = pair<i64, i64>;
using vi = vector<int>;
using vl = vector<ll>;
using vvi = vector<vector<int>>;
using vvl = vector<vector<ll>>;
using vpii = vector<pii>;
using vpll = vector<pll>;
const int inf = INT_MAX / 2 - 100;
const i64 infLL = LLONG_MAX / 3;
constexpr int MOD = 1000000007; // 998244353 1000000007
int dx[4]{1, 0, -1, 0}, dy[4]{0, 1, 0, -1};
template<typename T> using min_heap=priority_queue<T,vector<T>,greater<T>>;
template<typename T> using max_heap=priority_queue<T>;

constexpr int popcount(int x) { return __builtin_popcount(x); }
constexpr int topbit(int x) { return x == 0 ? 0 : 31 - __builtin_clz(x); }

inline void add_mod(int& x, int y) { x += y; if (x >= MOD) x -= MOD; }
inline void sub_mod(int& x, int y) { x += MOD - y; if (x >= MOD) x -= MOD; }

template <class T> bool chmin(T& a, const T& b) { return b < a ? a = b, 1 : 0; }  // set a = min(a,b)
template <class T> bool chmax(T& a, const T& b) { return a < b ? a = b, 1 : 0; }  // set a = max(a,b)

template <class T> void mkuni(vector<T>& v) { sort(all(v)); v.erase(unique(all(v)), v.end()); }
template <class T> int lwb(vector<T>& a, const T& b) { return int(lower_bound(all(a), b) - begin(a)); }
template <class T> int upb(vector<T>& a, const T& b) { return int(upper_bound(all(a), b) - begin(a)); }
template <class T, class U> void safeErase(T& t, const U& u) { auto it = t.find(u); assert(it != end(t)); t.erase(it); }

template<class T, class U> T fstTrue(T lo, T hi, U f) { ++hi; assert(lo <= hi); while (lo < hi) { T mid = lo + (hi - lo) / 2; f(mid) ? hi = mid : lo = mid + 1; } return lo; }
template<class T, class U> T lstTrue(T lo, T hi, U f) { --lo; assert(lo <= hi); while (lo < hi) { T mid = lo + (hi - lo + 1) / 2; f(mid) ? lo = mid : hi = mid - 1; } return lo; }

/***
 * 𝓽𝓱𝓮 𝓼𝓸𝓵𝓾𝓽𝓲𝓸𝓷 𝓸𝓯 𝔀𝔂𝓯0722
 */

template <typename T, int NDIMS>
struct tensor_view {
    static_assert(NDIMS >= 0, "NDIMS must be nonnegative");

   protected:
    std::array<int, NDIMS> shape;
    std::array<int, NDIMS> strides;
    T* data;

    tensor_view(std::array<int, NDIMS> shape_,
                std::array<int, NDIMS> strides_,
                T* data_)
        : shape(shape_), strides(strides_), data(data_) {}

   public:
    tensor_view() : shape{0}, strides{0}, data(nullptr) {}

   protected:
    int flatten_index(std::array<int, NDIMS> idx) const {
        int res = 0;
        for (int i = 0; i < NDIMS; i++) {
            res += idx[i] * strides[i];
        }
        return res;
    }
    int flatten_index_checked(std::array<int, NDIMS> idx) const {
        int res = 0;
        for (int i = 0; i < NDIMS; i++) {
            assert(0 <= idx[i] && idx[i] < shape[i]);
            res += idx[i] * strides[i];
        }
        return res;
    }

   public:
    T& operator[](std::array<int, NDIMS> idx) const {
#ifdef FAN_DEBUG
        return data[flatten_index_checked(idx)];
#else
        return data[flatten_index(idx)];
#endif
    }
    T& at(std::array<int, NDIMS> idx) const {
        return data[flatten_index_checked(idx)];
    }

    template <int D = NDIMS>
    typename std::enable_if<(0 < D), tensor_view<T, NDIMS - 1>>::type
    operator[](int idx) const {
        std::array<int, NDIMS - 1> nshape;
        std::copy(shape.begin() + 1, shape.end(), nshape.begin());
        std::array<int, NDIMS - 1> nstrides;
        std::copy(strides.begin() + 1, strides.end(), nstrides.begin());
        T* ndata = data + (strides[0] * idx);
        return tensor_view<T, NDIMS - 1>(nshape, nstrides, ndata);
    }
    template <int D = NDIMS>
    typename std::enable_if<(0 < D), tensor_view<T, NDIMS - 1>>::type at(
        int idx) const {
        assert(0 <= idx && idx < shape[0]);
        return operator[](idx);
    }

    template <int D = NDIMS>
    typename std::enable_if<(0 == D), T&>::type operator*() const {
        return *data;
    }

    template <typename U, int D>
    friend struct tensor_view;
    template <typename U, int D>
    friend struct tensor;
};

template <typename T, int NDIMS>
struct tensor {
    static_assert(NDIMS >= 0, "NDIMS must be nonnegative");

   protected:
    std::array<int, NDIMS> shape;
    std::array<int, NDIMS> strides;
    int len;
    T* data;

   public:
    tensor() : shape{0}, strides{0}, len(0), data(nullptr) {}

    explicit tensor(std::array<int, NDIMS> shape_, const T& t = T()) {
        shape = shape_;
        len = 1;
        for (int i = NDIMS - 1; i >= 0; i--) {
            strides[i] = len;
            len *= shape[i];
        }
        data = new T[len];
        std::fill(data, data + len, t);
    }

    tensor(const tensor& o)
        : shape(o.shape), strides(o.strides), len(o.len), data(new T[len]) {
        for (int i = 0; i < len; i++) {
            data[i] = o.data[i];
        }
    }

    tensor& operator=(tensor&& o) noexcept {
        using std::swap;
        swap(shape, o.shape);
        swap(strides, o.strides);
        swap(len, o.len);
        swap(data, o.data);
        return *this;
    }
    tensor(tensor&& o) : tensor() { *this = std::move(o); }
    tensor& operator=(const tensor& o) { return *this = tensor(o); }
    ~tensor() { delete[] data; }

    using view_t = tensor_view<T, NDIMS>;
    view_t view() { return tensor_view<T, NDIMS>(shape, strides, data); }
    operator view_t() { return view(); }

    using const_view_t = tensor_view<const T, NDIMS>;
    const_view_t view() const {
        return tensor_view<const T, NDIMS>(shape, strides, data);
    }
    operator const_view_t() const { return view(); }

    T& operator[](std::array<int, NDIMS> idx) { return view()[idx]; }
    T& at(std::array<int, NDIMS> idx) { return view().at(idx); }
    const T& operator[](std::array<int, NDIMS> idx) const {
        return view()[idx];
    }
    const T& at(std::array<int, NDIMS> idx) const { return view().at(idx); }

    template <int D = NDIMS>
    typename std::enable_if<(0 < D), tensor_view<T, NDIMS - 1>>::type
    operator[](int idx) {
        return view()[idx];
    }
    template <int D = NDIMS>
    typename std::enable_if<(0 < D), tensor_view<T, NDIMS - 1>>::type at(
        int idx) {
        return view().at(idx);
    }

    template <int D = NDIMS>
    typename std::enable_if<(0 < D), tensor_view<const T, NDIMS - 1>>::type
    operator[](int idx) const {
        return view()[idx];
    }
    template <int D = NDIMS>
    typename std::enable_if<(0 < D), tensor_view<const T, NDIMS - 1>>::type at(
        int idx) const {
        return view().at(idx);
    }

    template <int D = NDIMS>
    typename std::enable_if<(0 == D), T&>::type operator*() {
        return *view();
    }
    template <int D = NDIMS>
    typename std::enable_if<(0 == D), const T&>::type operator*() const {
        return *view();
    }
};

class Solution {
public:
    int maxValue(vector<int>& nums, int k) {
        int MX = 1 << 7;
        int n = nums.size();
        tensor<bool, 2> suf({n - k + 1, MX}, false);
        tensor<bool, 2> pre({k + 1, MX});
        pre[{0, 0}] = true;
        tensor<bool, 2> f({k + 1, MX}, false);
        f[{0, 0}] = true;

        for (int i = n - 1; i >= k; i--) {
            int val = nums[i];
            for (int j = min(k - 1, n - 1 - i); j >= 0; j--) {
                for (int x = 0; x < MX; x++) {
                    // 不选 f[i][j][x] = f[i + 1][j][x]
                    // 选 f[i][j + 1][x | val] = f[i + 1][j][x]
                    if (f[{j, x}]) {
                        f[{j + 1, x | val}] = true;
                    }
                }
            }
            if (i <= n - k) {
                for (int x = 0; x < MX; x++) {
                    suf[{i, x}] = f[{k, x}];
                }
            }
        }

        int ans = 0;
        for (int i = 0; i < n - k; i++) {
            int val = nums[i];
            for (int j = min(k - 1, i); j >= 0; j--) {
                for (int x = 0; x < MX; x++) {
                    if (pre[{j, x}]) {
                        pre[{j + 1, x | val}] = true;
                    }
                }
            }
            if (i < k - 1) {
                continue;
            }
            for (int x = 0; x < MX; x++) {
                if (pre[{k, x}]) {
                    for (int y = 0; y < MX; y++) {
                        if (suf[{i + 1, y}]) {
                            chmax(ans, x ^ y);
                        }
                    }
                }
            }
        }
        return ans;
    }
};