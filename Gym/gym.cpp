#include <bits/stdc++.h>

using namespace std;

template<typename A, typename B> ostream& operator<<(ostream &os, const pair<A, B> &p) { return os << '(' << p.first << ", " << p.second << ')'; }
template<typename T_container, typename T = typename enable_if<!is_same<T_container, string>::value, typename T_container::value_type>::type> ostream& operator<<(ostream &os, const T_container &v) { os << '{'; string sep; for (const T &x : v) os << sep << x, sep = ", "; return os << '}'; }
 
void dbg_out() { cout << endl; }
template<typename Head, typename... Tail> void dbg_out(Head H, Tail... T) { cout << ' ' << H; dbg_out(T...); }
#define debug(...) cout << '[' << __FILE__ << ':' << __LINE__ << "] (" << #__VA_ARGS__ << "):", dbg_out(__VA_ARGS__)

#define all(x) begin(x), end(x)
#define rall(x) begin(x), end(x)
// loops
#define FOR(i, a, b) for (int i = (a); i < (b); ++i)
#define F0R(i, a) FOR(i, 0, a)
#define ROF(i, a, b) for (int i = (b)-1; i >= (a); --i)
#define R0F(i, a) ROF(i, 0, a)
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
int MOD = 1e9 + 7;
int dx[4]{1, 0, -1, 0}, dy[4]{0, 1, 0, -1};
template<typename T> using min_heap=priority_queue<T,vector<T>,greater<T>>;
template<typename T> using max_heap=priority_queue<T>;

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

template<class T, class U>
T fstTrue(T lo, T hi, U f) {
	++hi;
	assert(lo <= hi);  // assuming f is increasing
	while (lo < hi) {  // find first index such that f is true
		T mid = lo + (hi - lo) / 2;
		f(mid) ? hi = mid : lo = mid + 1;
	}
	return lo;
}

template<class T, class U>
T lstTrue(T lo, T hi, U f) {
	--lo;
	assert(lo <= hi);  // assuming f is decreasing
	while (lo < hi) {  // find first index such that f is true
		T mid = lo + (hi - lo + 1) / 2;
		f(mid) ? lo = mid : hi = mid - 1;
	}
	return lo;
}

inline void add_mod(int& x, int y) { x += y; if (x >= MOD) x -= MOD; }
inline void sub_mod(int& x, int y) { x += MOD - y; if (x >= MOD) x -= MOD; }

template <class T>
bool chmin(T& a, const T& b) {
    return b < a ? a = b, 1 : 0;
}  // set a = min(a,b)
template <class T>
bool chmax(T& a, const T& b) {
    return a < b ? a = b, 1 : 0;
}  // set a = max(a,b)

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
const int offset = 505;
class Solution {
public:
    int paintWalls(vector<int>& cost, vector<int>& time) {
        int n = cost.size();
		tensor<int, 2> mem({n, 1500}, -1);
		auto dp = [&](auto &&self, int i, int delta) -> int {
			if (i == n) {
				return delta >= 0 ? 0 : inf;
			}
			if (delta >= n - i) {
				return 0;
			}
			int &r = mem[{i, delta + offset}];
			if (r != -1) return r;
			r = min(self(self, i + 1, delta + time[i]) + cost[i], self(self, i + 1, delta - 1));
			return r;
		};
		return dp(dp, 0, 0);
    }
};