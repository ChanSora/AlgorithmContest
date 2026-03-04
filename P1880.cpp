// https://www.luogu.com.cn/problem/P1880
// 区间DP
#include <iostream>
#include <cmath>
#include <cstring>
// #include <vector>
const int MAXN = 1000, inf = 2147483647;
int a[MAXN][MAXN], b[MAXN][MAXN], S[MAXN];

int main() {
    int n;
    std::cin >> n;
    // std::vector<std::vector<int>> a(2*n + 1, std::vector<int>(2*n + 1, 0));
    // for (int i = 1; i <= n; i++) std::cin >> a[i][i];
    // for (int i = 1; i <= n; i++) S[i] = S[i-1] + a[i][i];
    // for (int i = 1; i <= n; i++) a[n+i][n+i] = a[i][i];
    for (int i = 1; i <= n; i++) std::cin >> S[i];
    memcpy(S + n + 1, S + 1, sizeof(int) * n);
    for (int i = 1; i <= 2*n; i++) S[i] += S[i - 1];
    // for (int i = 1; i <= 2*n; i++) std::cout << S[i] << ' ';
    for (int i = 1; i <= 2*n + 1; i++) for (int j = 1; j <= 2*n + 1; j++) a[i][j] = 0, b[i][j] = (i == j ? 0 : inf);
    for (int bias = 1; bias <= n - 1; bias++) {
        for (int i = 1; i <= 2 * n - bias; i++) {
            for (int j = i; j <= i + bias - 1; j++) {
                a[i][i + bias] = std::max(a[i][i + bias], (a[i][j] + a[j + 1][i + bias] + S[i + bias] - S[i-1]));
                b[i][i + bias] = std::min(b[i][i + bias], (b[i][j] + b[j + 1][i + bias] + S[i + bias] - S[i-1]));
                // std::cout << i << ' ' << i + bias << '\n';
                // std::cout << b[i][i + bias] << '\n';
            }
        }
    }
    int outmax = 0, outmin = inf;
    for (int i = 1; i <= n; i++) {
        outmax = std::max(outmax, a[i][i + n - 1]);
        outmin = std::min(outmin, b[i][i + n - 1]);
    }
    std::cout << outmin << '\n' << outmax << '\n';
    return 0;
}