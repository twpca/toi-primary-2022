// O(26n * 26)
// Expect: AC
#include<bits/stdc++.h>
#define REP(x,y,z) for(int x=y;x<=z;x++)
#define MSET(x,y) memset(x,y,sizeof(x))
#define M 10005
#define INF 2'000'000'000
using namespace std;
int n,in[M],dis[30][30];
int dp[M][30][30];
void init() {
    string lines[3] = {"QWERTYUIOP", "ASDFGHJKL", "ZXCVBNM"};
    REP(i0,0,2) REP(i1,i0,2) REP(j,0,(int)lines[i0].length()-1) REP(k,0,(int)lines[i1].length()-1) {
        int cj = lines[i0][j] - 'A';
        int ck = lines[i1][k] - 'A';

        int dy = i1 - i0;
        int dx = abs(j-k);
        if (j>k) {
            dx -= min(j-k, i1-i0);
        }
        dis[cj][ck] = dis[ck][cj] = dx + dy;
    }
}
void work() {
    string tmp;
    cin >> tmp;
    REP(i,1,n) in[i] = tmp[i-1] - 'A';

    REP(i,0,n) REP(j,0,25) REP(k,0,25) dp[i][j][k] = INF;
    dp[0]['F'-'A']['J'-'A'] = 0;
    REP(i,0,n-1) REP(j,0,25) REP(k,0,25) if (dp[i][j][k] != INF) {
        int nxt = in[i+1];
        dp[i+1][nxt][k] = min(dp[i+1][nxt][k], dp[i][j][k] + dis[j][nxt]);
        dp[i+1][j][nxt] = min(dp[i+1][j][nxt], dp[i][j][k] + dis[k][nxt]);
    }

    int ans = INF;
    REP(i,0,25)REP(j,0,25) ans = min(ans, dp[n][i][j]);
    printf("%d\n", ans);
}
int main()
{
    init();
    while (~scanf("%d", &n)) {
        work();
    }
    return 0;
}
