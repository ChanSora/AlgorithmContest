// https://www.luogu.com.cn/problem/P3959
#include <iostream>
#include <algorithm>
const int MAXN = 12, M = (1 << 12), inf = 0x3f3f3f3f;
int n, m, c[MAXN][MAXN], cost[M][M]; 
long long dp[MAXN][M];
void init() {
    for (int i = 0; i < (1 << n); i++) {
        for (int j = i; j; j = (j - 1) & i) {
            if (j == i) continue;
            for (int t = 0, tmp = inf; t < n; t++, tmp = inf) {
                if (!(((i ^ j) >> t) & 1)) continue;
                for (int l = 0; l < n; l++) if ((j >> l) & 1) tmp = std::min(tmp, c[l][t]);
                if (tmp >= inf) {
                    cost[j][i] = inf;
                    break;
                } else cost[j][i] += tmp;
            }
        }
    }
    return;
}
long long DP(int x) {
    long long res = inf;
    for (int i = 0; i < MAXN; i++) for (int j = 0; j < M; j++) dp[i][j] = inf;
    dp[0][1 << x] = 0;
    for (int i = 1; i < n; i++) {
        for (int j = 0; j < (1 << n); j++) {
            for (int k = j; k; k = (k - 1) & j) {
                if (k == j) continue;
                dp[i][j] = std::min(dp[i][j], dp[i - 1][k] + 1ll * i * cost[k][j]);
            }
            if (j == (1 << n) - 1) res = std::min(res, dp[i][j]);
        }
    }
    return res;
}
int main() {
    std::cin >> n >> m;
    if (n == 1) {
        std::cout << 0 << '\n';
        return 0;
    }
    for (int i = 0; i < n; i++) for (int j = 0; j < n; j++) c[i][j] = inf;
    for (int i = 1, u, v, w; i <= m; i++) {
        std::cin >> u >> v >> w; u--, v--;
        c[u][v] = c[v][u] = std::min(c[u][v], w);
    }
    init();
    long long ans = inf;
    for (int i = 0; i < n; i++) ans = std::min(ans, DP(i));
    std::cout << ans << '\n';
    return 0;
}