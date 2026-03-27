// https://www.luogu.com.cn/problem/P2150
#include <iostream>
#include <algorithm>
#include <cstring>
const int maxn = 505, STATUS = (1 << 8);
int n, mod;
long long dp[STATUS][STATUS], f1[STATUS][STATUS], f2[STATUS][STATUS];
int p[10] = {0,2,3,5,7,11,13,17,19,0};
struct node {
    int val, S, big;
    void init() {
        int tmp = val; big = -1;
        for (int i = 1; i <= 8; i++) {
            if (tmp % p[i] == 0) {
                S |= (1 << (i - 1));
                while(tmp % p[i] == 0) tmp /= p[i];
            }
        }
        if (tmp != 1) big = tmp;
    }
} a[maxn];
inline bool cmp(node a, node b) {
    return a.big < b.big;
} 
int main() {
    std::ios::sync_with_stdio(false);
    std::cin >> n >> mod;
    for (int i = 1; i < n; i++) {
        a[i].val = i + 1; a[i].init();
    }
    std::sort(a + 1, a + n + 1, cmp); // 按大质因子大小排序
    dp[0][0] = 1;
    for (int i = 1; i < n; i++) {
        if (i == 1 || a[i].big != a[i - 1].big || a[i].big == -1) { 
            // 同一个大质因子内的数，不能同时出现在两边，因此需要
            memcpy(f1, dp, sizeof(f1)); // f1:新数被加到G
            memcpy(f2, dp, sizeof(f2)); // f2:新数被加到W
        }
        for (int j = STATUS - 1; j >= 0; j--) {
            for (int k = STATUS - 1; k >= 0; k--) {
                if (j & k) continue;
                if ((k & a[i].S) == 0) f1[j | a[i].S][k] += f1[j][k], f1[j | a[i].S][k] %= mod;
                if ((j & a[i].S) == 0) f2[j][k | a[i].S] += f2[j][k], f2[j][k | a[i].S] %= mod;
            }
        }
        if (i == n - 1 || a[i].big != a[i + 1].big || a[i].big == -1) {
            for (int j = STATUS - 1; j >= 0; j--) {
                for (int k = STATUS - 1; k >= 0; k--) {
                    if (j & k) continue;
                    dp[j][k] = f1[j][k] + f2[j][k] + mod - dp[j][k];
                    dp[j][k] %= mod;
                }
            }
        }
    }
    long long ans = 0;
    for (int i = 0; i < STATUS; i++) {
        for (int j = 0; j < STATUS; j++) {
            if (i & j) continue;
            if (dp[i][j] == 0) continue;
            ans += dp[i][j];
            ans %= mod;
        }
    }
    std::cout << ans << '\n';
    return 0;
}