// https://www.luogu.com.cn/problem/UVA12991
#include <iostream>
#include <algorithm>
#include <cmath>
#include <cstdio>
typedef long long ll;
const int MAXN = 5000;
const ll inf = 9e18;
int n;
ll p[MAXN], q[MAXN];
ll dp[MAXN][2], pre[MAXN][2], ppre[MAXN][2], suf[MAXN][2], ssuf[MAXN][2];

ll cost(int l, int r, bool type);

void solve() {
    std::cin >> n;
    for (int i = 1; i <= n; i++) std::cin >> p[i] >> q[i];
    // 初始化
    dp[0][0] = dp[0][1] = 0;
    for (int i = 1; i <= n; i++) dp[i][0] = dp[i][1] = inf;
    for (int i = 1; i <= n; i++) pre[i][0] = pre[i-1][0] + p[i], pre[i][1] = pre[i-1][1] + q[i];
    for (int i = 1; i <= n; i++) ppre[i][0] = ppre[i-1][0] + pre[i][0], ppre[i][1] = ppre[i-1][1] + pre[i][1];
    // 注意这里要把suf的第n+1项处理好，由于题目是多测试点的，每次跑完一遍都需要重新初始化
    suf[n+1][0] = ssuf[n+1][0] = suf[n+1][1] = ssuf[n+1][1] = 0;
    for (int i = n; i >= 1; i--) suf[i][0] = suf[i+1][0] + p[i], suf[i][1] = suf[i+1][1] + q[i];
    for (int i = n; i >= 1; i--) ssuf[i][0] = ssuf[i+1][0] + suf[i][0], ssuf[i][1] = ssuf[i+1][1] + suf[i][1];
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j <= i - 1; j++) {
            // 注意这里cost 函数的写法：计算的贡献到底是乒乓球的还是游泳池的
            dp[i][0] = std::min(dp[i][0], dp[j][1] + cost(j + 1, i, 1)); 
            dp[i][1] = std::min(dp[i][1], dp[j][0] + cost(j + 1, i, 0)); 
        }
    }
    return;
}

int main() {
    int T; std::cin >> T;
    for (int i = 1; i <= T; i++) {
        solve();
        printf("Case #%d: %lld\n", i, std::min(dp[n][0], dp[n][1]));
    }
    return 0;
}

ll cost(int l, int r, bool type) {
    // 注意理解ppre跟ssuf的定义：二阶前缀和和它的方向
    int mid = (l + r) >> 1;
    ll lcost, rcost;
    if (l == 1 && r == n) return inf; // 不能全为乒乓球或游泳池
    if (l == 1) return ppre[r][type];
    if (r == n) return ssuf[l][type];
    lcost = ssuf[l][type] - ssuf[mid + 1][type] - (mid - l + 1) * suf[mid + 1][type];
    rcost = ppre[r][type] - ppre[mid][type] - (r - mid) * pre[mid][type];
    return lcost + rcost;
}
