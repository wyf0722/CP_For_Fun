// 随机模数
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

int rnd(int x, int y) {
    return uniform_int_distribution<int>(x, y)(rng);
}

int SINGLE_MOD = 998244353 + rnd(0, 1e9), SINGLE_BASE = 233 + rnd(0, 1e3);

// 单模数
struct StringHash {
    vector<long long> P, H;
    int MOD, BASE;

    StringHash() {}

    StringHash(string &s, int m = SINGLE_MOD, int b = SINGLE_BASE) {
        MOD = m;
        BASE = b;
        int n = s.size();
        P.resize(n + 1);
        P[0] = 1;
        for (int i = 1; i <= n; i++) P[i] = P[i - 1] * BASE % MOD;
        H.resize(n + 1);
        H[0] = 0;
        for (int i = 1; i <= n; i++) H[i] = (H[i - 1] * BASE + (s[i - 1] ^ 7)) % MOD;
    }

    // s[l, r]下标从1开始
    long long query(int l, int r) {
        return (H[r] - H[l - 1] * P[r - l + 1] % MOD + MOD) % MOD;
    }
};

// 双模数
int MOD1 = 998244353 + rnd(0, 1e9), BASE1 = 233 + rnd(0, 1e3);
int MOD2 = 998244353 + rnd(0, 1e9), BASE2 = 233 + rnd(0, 1e3);
struct DoubleHash {
    StringHash hash1, hash2;

    DoubleHash(string &s) {
        hash1 = StringHash(s, MOD1, BASE1);
        hash2 = StringHash(s, MOD2, BASE2);
    }

    pair<long long, long long> query(int l, int r) {
        return make_pair(hash1.query(l, r), hash2.query(l, r));
    }
};
