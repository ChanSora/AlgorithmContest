// https://www.luogu.com.cn/problem/P3052
#include <iostream>
#include <cmath>
#include <algorithm>
const int MAXN = 20, inf = 2147483647;
int n, maxw, w[MAXN], dp[MAXN][(1 << 19) - 1];

int main() {
    std::cin >> n >> maxw;
    for (int i = 1; i <= n; i++) {
        std::cin >> w[i];
    }
    for (int i = 1; i <= n; i++) { // 初始化
        for (int j = 0; j < std::pow(2, n); j++) {
            dp[i][j] = inf;
        }
    }
    for (int i = 0; i < n; i++) {
        dp[1][1 << i] = w[i+1];
    }
    // DP过程
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j < std::pow(2, n); j++) {
            if (dp[i][j] == inf) continue; // 排除未处理过的情况
            // std::cout << "doing " << i << " and " << j << '\n';
            for (int k = 0; k < n; k++) {
                if (j & (1 << k)) continue; // 如果已经包含在情况内就排除
                // 两种情况都要加min：加新元素的时候如果有更优的排法就先选更优的
                if (dp[i][j] + w[k+1] <= maxw) dp[i][j | (1 << k)] = std::min(dp[i][j | (1 << k)], dp[i][j] + w[k+1]);
                else dp[i+1][j | (1 << k)] = std::min(dp[i+1][j | (1 << k)], w[k+1]);
            }
        }
    }
    int ans = 0;
    for (int i = 1; i <= n; i++) {
        if (dp[i][(int)std::pow(2, n) - 1] != inf) {
            // std::cout << dp[i][(int)std::pow(2, n) - 1] << '\n';
            ans = i;
            break;
        }
    }
    std::cout << ans << '\n';
    return 0;
}