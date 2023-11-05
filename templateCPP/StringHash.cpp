typedef unsigned long long ULL;
const int P = 131;
const int N = 100010;
class StringHash {
public:
    ULL p[N], h[N];
    int n;

    StringHash(string s) {
        n = s.size();
        p[0] = 1;
        h[0] = 0;
        for (int i = 1; i <= n; i++) {
            h[i] = h[i - 1] * P + s[i - 1];
            p[i] = p[i - 1] * P;
        }
    }
    
    // hash s[l, r]
    ULL get(int l, int r) { return h[r] - h[l - 1] * p[r - l + 1]; }

    bool substr(int l1, int r1, int l2, int r2) {
        return get(l1, r1) == get(l2, r2);
    }
};