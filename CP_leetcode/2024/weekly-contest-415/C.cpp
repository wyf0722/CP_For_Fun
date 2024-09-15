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
/**
 * @link https://github.com/nealwu/competitive-programming/blob/master/strings/trie.cc
*/
template <char MIN_CHAR = 'a', int ALPHABET = 26>
struct array_trie {
    struct trie_node {
        array<int, ALPHABET> child;
        int words_here = 0, starting_with = 0;

        trie_node() { memset(&child[0], -1, ALPHABET * sizeof(int)); }
    };

    static const int ROOT = 0;

    vector<trie_node> nodes = {trie_node()};

    array_trie(int total_length = -1) {
        if (total_length >= 0)
            nodes.reserve(total_length + 1);
    }

    int get_or_create_child(int node, int c) {
        if (nodes[node].child[c] < 0) {
            nodes[node].child[c] = int(nodes.size());
            nodes.emplace_back();
        }

        return nodes[node].child[c];
    }

    int build(const string& word, int delta) {
        int node = ROOT;

        for (char ch : word) {
            nodes[node].starting_with += delta;
            node = get_or_create_child(node, ch - MIN_CHAR);
        }

        nodes[node].starting_with += delta;
        return node;
    }

    int add(const string& word) {
        int node = build(word, +1);
        nodes[node].words_here++;
        return node;
    }

    int erase(const string& word) {
        int node = build(word, -1);
        nodes[node].words_here--;
        return node;
    }

    int find(const string& str) const {
        int node = ROOT;

        for (char ch : str) {
            node = nodes[node].child[ch - MIN_CHAR];

            if (node < 0)
                break;
        }

        return node;
    }

    // Given a string, how many words in the trie are prefixes of the string?
    int count_prefixes(const string& str, bool include_full) const {
        int node = ROOT, count = 0;

        for (char ch : str) {
            count += nodes[node].words_here;
            node = nodes[node].child[ch - MIN_CHAR];

            if (node < 0)
                break;
        }

        if (include_full && node >= 0)
            count += nodes[node].words_here;

        return count;
    }

    // Given a string, how many words in the trie start with the given string?
    int count_starting_with(const string& str, bool include_full) const {
        int node = find(str);

        if (node < 0)
            return 0;

        return nodes[node].starting_with -
               (include_full ? 0 : nodes[node].words_here);
    }
};

class Solution {
public:
    int minValidStrings(vector<string>& words, string target) {
        int n = target.size();
        vector<int> dp(n + 1, inf);
        dp[n] = 0;
        array_trie trie;
        for (auto &word : words) {
            trie.add(word);
        }
        for (int i = n - 1; i >= 0; i--) {
            int cur = 0;
            for (int j = i; j < n; j++) {
                if (trie.nodes[cur].child[target[j] - 'a'] == -1) {
                    break;
                } else {
                    cur = trie.nodes[cur].child[target[j] - 'a'];
                    chmin(dp[i], dp[j + 1] + 1);
                }
            }
        }
        return dp[0] == inf ? -1 : dp[0];
    }
};

