// https://www.luogu.com.cn/problem/P2704
#include <iostream>
#include <string>
#include <cmath>
#include <algorithm>
#include <cstdio>
const int MAXN = 110, MAXM = 11, STATUS = 200, inf = 2147483647;
int n, m, cnt, dp[MAXN][STATUS][STATUS], MAP[MAXN], mask[STATUS];

void solve() {
    for (int x = 0; x < (1 << m); x++) {
        if (!((x & (x << 2)) || (x & (x << 1)))) mask[++cnt] = x;
    }
} 

int main() {
    std::cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        std::string s; std::cin >> s;
        int status = 0;
        for (int j = 0; j < s.length(); j++) {
            status |= (s[j] == 'P' ? 0 : (1 << j));
        }
        MAP[i] = status;
    }
    solve();
    for (int i = 1; i <= n; i++) for (int j = 0; j < (1 << m); j++) for (int k = 0; k < (1 << m); k++) dp[i][j][k] = -inf;
    for (int i = 1; i <= cnt; i++) {
        if (!(mask[i] & MAP[1])) dp[1][i][0] = __builtin_popcount(mask[i]);
    }
    for (int line = 2; line <= n; line++) {
        for (int i = 1; i <= cnt; i++) {
            if (mask[i] & MAP[line]) continue;
            for (int j = 1; j <= cnt; j++) {
                if (mask[i] & mask[j] || mask[j] & MAP[line-1]) continue;
                if (line == 2 && dp[line-1][j][0] != -inf) dp[line][i][j] = std::max(dp[line][i][j], dp[line-1][j][0] + __builtin_popcount(mask[i]));
                else {
                    for (int k = 1; k <= cnt; k++) {
                        if (!(mask[j] & mask[k] || mask[i] & mask[k] || mask[k] & MAP[line-2]) && dp[line-1][j][k] != -inf) {
                            dp[line][i][j] = std::max(dp[line][i][j], dp[line-1][j][k] + __builtin_popcount(mask[i]));
                        }
                    }
                }
            }
        }
    }
    int ans = -inf;
    for (int i = 1; i <= cnt; i++) for (int j = 0; j <= cnt; j++) ans = std::max(ans, dp[n][i][j]);
    std::cout << ans << '\n';
    return 0;
}