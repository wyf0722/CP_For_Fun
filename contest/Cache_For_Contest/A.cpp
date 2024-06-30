class Solution {
public:
    int maxHeightOfTriangle(int red, int blue) {
        int ans = 0;
        auto get = [&](int x, int y) -> int {
            int cur = 1;
            int f = 0;
            int r = 0;
            while (1) {
                if (f == 0) {
                    if (x >= cur) {
                        x -= cur;
                        cur++;
                        r++;
                    } else {
                        break;
                    }
                } else {
                    if (y >= cur) {
                        y -= cur;
                        cur++;
                        r++;
                    } else {
                        break;
                    }
                }
                f ^= 1;
            }
            return r;
        };
        return max(get(red, blue), get(blue, red));
    }
};