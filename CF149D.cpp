// https://www.luogu.com.cn/problem/CF149D
// https://codeforces.com/problemset/problem/149/D
#include <iostream>
#include <cstdio>
#include <string>
#include <stack>
#include <cstring>
const int MAXN = 1000, mod = 1e9 + 7;
struct Data {
    int idx;
    bool type;
} data[MAXN];
int opp[MAXN], a[MAXN][MAXN][3][3], s[MAXN];

int main() {
    std::string str; std::cin >> str;
    int len = str.length();
    for (int i = 0; i < len; i++) data[i + 1].idx = i + 1, data[i + 1].type = (str[i] == '(' ? 0 : 1);
    // for (int i = 1; i <= len; i++) printf("data.idx:%d, type:%d\n", data[i].idx, data[i].type);
    // 完成括号匹配
    std::stack<Data> stk;
    for (int i = 1; i <= len; i++) {
        if (stk.empty()) stk.push(data[i]);
        else if (stk.top().type ^ data[i].type) {
            // std::cout << i << " match!" << '\n';
            opp[stk.top().idx] = i;
            opp[i] = stk.top().idx;
            stk.pop();
            
        } else stk.push(data[i]);
    }
    // std::cout << s << '\n';
    // for (int i = 1; i <= len; i++) std::cout << opp[i] << ' ';
    // std::cout << '\n';
    memset(s, 0, sizeof(int) * (len + 1));
    for (int i = 1; i <= len; i++) s[i] = s[i - 1] + (data[i].type ? -1 : 1); 
    // printf("%d%c", s[i], i == len ? '\n' : ' ');
    // 主算法：从小到大区间DP
    // ai, j, m, n:从i到j，情况为m,n的方案数(0,无染色 1,蓝 2,红)
    for (int i = 1; i <= len; i++)
        for (int j = 1; j <= len; j++)
            for (int k = 0; k < 9; k++)
                a[i][j][k / 3][k % 3] = 0;
    for (int bias = 1; bias < len; bias += 2) {
        for (int i = 1; i + bias <= len; i++) {
            if (data[i].type ^ data[i + bias].type) {
                // printf("%d, %d matched.\n", i, i + bias);
                // 满足左(右)，接下来检查端点有没有可能是括号内部的点;
                // 如果左1右-1，匹配成功则和为0;
                if (s[i + bias] - s[i - 1] != 0) continue;
                else {
                    // 匹配成功，开始计算内部括号的方案数
                    if (bias == 1) {
                        for (int j = 0; j < 9; j++) {
                            if (j / 3 == j % 3) continue;
                            if (j / 3 != 0 && j % 3 != 0) continue;
                            a[i][i + bias][j / 3][j % 3] = 1;
                            // printf("%d, %d, %d %d:%d\n", i, i + bias, j / 3, j % 3, a[i][i + bias][j / 3][j % 3]);
                        }
                        continue;
                    } //特判一下初始情况：只有一对括号
                    if (opp[i] == i + bias) { //最外层是括号
                        // a[i][i + bias][0][0] = 0;
                        for (int m = 0; m < 9; m++) {
                            if (m / 3 == m % 3) continue;
                            if (m / 3 != 0 && m % 3 != 0) continue;
                            for (int n = 0; n < 9; n++) {
                                // 检查相邻括号是否同色
                                bool leftok = ((m / 3) != (n / 3)) || (m / 3 == 0);
                                bool rightok = ((m % 3) != (n % 3)) || (m % 3 == 0);
                                a[i][i + bias][m / 3][m % 3] += (leftok && rightok) ? a[i + 1][i + bias - 1][n / 3][n % 3] : 0;
                                a[i][i + bias][m / 3][m % 3] %= mod;
                            }
                        }
                    } else { // 如果是一个个独立的小块
                        for (int line = i; line < i + bias; line++) {
                            if (data[line].type == 1 && data[line + 1].type == 0) {//  )( 的情况
                                if (s[line] - s[i - 1] != 0) continue;
                                for (int m = 0; m < 9; m++) {
                                    for (int n = 0; n < 9; n++) {
                                        bool ok = (n / 3) != (n % 3) || (n / 3 == 0) || (n % 3 == 0); // 只需中间情况不同色即可
                                        if (ok) a[i][i + bias][m / 3][m % 3] += (long long)(a[i][line][m / 3][n / 3] * a[line + 1][i + bias][n % 3][m % 3]) % mod, 
                                        a[i][i + bias][m / 3][m % 3] %= mod;
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    long long sum = 0;
    for (int i = 0; i < 9; i++) sum += a[1][len][i / 3][i % 3];
    std::cout << sum % mod << '\n';
    return 0;
}