// https://www.luogu.com.cn/problem/P4342
// 区间DP
#include <algorithm>
#include <iostream>
#include <cstring>
const int MAXN = 200, inf = 2147483647;
int a[MAXN][MAXN], b[MAXN][MAXN], s[MAXN], edge[MAXN];

int get_val(int *vals, int len, bool type, bool mode) {
    int val;
    if (mode == false) {
        val = -inf;
        for (int i = 0; i < len; i++) {
            for (int j = i; j < len; j++) {
                if ((i + j) % 2 == 0) continue;
                val = std::max(val, type ? vals[i] * vals[j] : vals[i] + vals[j]);
            }
        }
    } else {
        val = inf;
        for (int i = 0; i < len; i++) {
            for (int j = i; j < len; j++) {
                if ((i + j) % 2 == 0) continue;
                val = std::min(val, type ? vals[i] * vals[j] : vals[i] + vals[j]);
            }
        }
    }
    return val;
}
int main() {
    int n; std::cin >> n;
    for (int i = 1; i <= 2*n; i++) for (int j = 1; j <= 2*n; j++) a[i][j] = -inf, b[i][j] = inf;

    for (int i = 1; i <= n; i++) {
        char type; std::cin >> type >> s[i];
        if (type == 't') edge[i - 1] = 0;
        else edge[i - 1] = 1; 
    }
    for (int i = 0; i < 2*n; i++) a[i + 1][i + 1] = s[i % n + 1], b[i + 1][i + 1] = s[i % n + 1]; 
    memcpy(edge + n, edge, sizeof(int) * n);
    // for (int i = 1; i <= 2*n; i++) a[i][i] = 0;
    for (int bias = 1; bias <= n - 1; bias++) {
        for (int i = 1; i <= 2 * n - bias; i++) {
            for (int j = i; j <= i + bias - 1; j++) {
                // std::cout << a[i][j] << ' ' << a[j + 1][i + bias] << '\n';
                // std::cout << b[i][j] << ' ' << b[j + 1][i + bias] << '\n';
                int vals[4], max_val, min_val;
                vals[0] = a[i][j], vals[1] = a[j + 1][i + bias], vals[2] = b[i][j], vals[3] = b[j + 1][i + bias];
                // int val = edge[j] ? a[i][j] * a[j + 1][i + bias] : a[i][j] + a[j + 1][i + bias];
                max_val = get_val(vals, 4, edge[j], 0);
                min_val = get_val(vals, 4, edge[j], 1);
                // std::cout << i << ' ' << j << ' ' << i + bias << ' ' << val << '\n';
                a[i][i + bias] = std::max(a[i][i + bias], max_val);
                b[i][i + bias] = std::min(b[i][i + bias], min_val);
                // printf("max_val in a[%d][%d] and a[%d][%d]: %d and %d type:%c\n", i, j, j + 1, i + bias, a[i][j], a[j + 1][i + bias], edge[j] ? '*' : '+');
                // printf("min_val in b[%d][%d] and b[%d][%d]: %d and %d type:%c\n", i, j, j + 1, i + bias, b[i][j], b[j + 1][i + bias], edge[j] ? '*' : '+');
                // printf("get a/b[%d][%d]min_val:%d; max_val:%d\n", i, i + bias, min_val, max_val);
            }
        }
    }
    int out = -inf;
    for (int i = 1; i <= n; i++) out = std::max(out, a[i][i + n - 1]);
    std::cout << out << '\n';
    int outedge[n + 1]; int cnt = 0;
    for (int i = 1; i <= n; i++) {
        if (a[i][i + n - 1] == out) outedge[cnt++] = i;
    }
    std::sort(outedge, outedge + cnt);
    for (int i = 0; i < cnt; i++) std::cout << outedge[i] << ' ';
    std::cout << '\n';
    return 0;
}