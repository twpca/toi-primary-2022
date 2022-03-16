// O(n0 * n2) DP
// DP using 32bit int
// Expect: [AC, WA, WA]
#include<algorithm>
#include<vector>
#include<cstdio>
#include<cstring>
#define REP(x,y,z) for(int x=y;x<=z;x++)
#define MSET(x,y) std::memset(x,y,sizeof(x))
#define M 1005
using namespace std;
int n, n0, n2, dp[M][M][11], pw[2*M];
inline int m11(int x) { return (x % 11 + 11) % 11; }
void print(vector<char> &v) {
    for (char c: v) {
        printf("%c", c);
    }
    puts("");
}
int main()
{
    pw[0] = 1;
    REP(i,1,2*M-1) pw[i] = m11(pw[i-1] * 10);

    scanf("%d %d", &n0, &n2);
    n = n0 + n2;

    MSET(dp, -1);
    dp[0][0][0] = 1;
    for (int p=n; p>=1; p--) {
        int used = n - p + 1;
        REP(i, 0, min(n0, used)) {
            int j = used - i;
            if (j < 0 || j > n2) {
                continue;
            }

            REP(k,0,10) {
                dp[i][j][k] = 0;
                // 0
                if (i > 0 && dp[i-1][j][k] != -1) {
                    dp[i][j][k] += dp[i-1][j][k];
                }
                // 2
                int mod = m11(2 * pw[n-p]);
                int pre = m11(k - mod);
                if (j > 0 && dp[i][j-1][pre] != -1) {
                    dp[i][j][k] += dp[i][j-1][pre];
                }
            }
        }
    }

    if (dp[n0][n2][0] < 2) {
        puts("-1");
        return 0;
    }

    // 2nd biggest
    vector<char> ans;
    int i = n0;
    int j = n2;
    int k = 0;
    int cnt = 2;
    while (i > 0 || j > 0) {
        int mod = m11(2 * pw[i+j-1]);
        int pre = m11(k - mod);
        if (j > 0 && dp[i][j-1][pre] >= cnt) {
            ans.push_back('2');
            j--;
            k = pre;
        } else {
            ans.push_back('0');
            if (j > 0) cnt -= dp[i][j-1][pre];
            i--;
        }
    }
    print(ans);

    // 2nd smallest
    ans.clear();
    i = n0;
    j = n2;
    k = 0;
    cnt = 2;
    while (i > 0 || j > 0) {
        int mod = m11(2 * pw[i+j-1]);
        int pre = m11(k - mod);
        if (i > 0 && dp[i-1][j][k] >= cnt) {
            ans.push_back('0');
            i--;
        } else {
            ans.push_back('2');
            if (i > 0) cnt -= dp[i-1][j][k];
            j--;
            k = pre;
        }
    }
    print(ans);
    return 0;
}
