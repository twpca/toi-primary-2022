// O(2^n)
// Expect: pass n <= 20
#include<bits/stdc++.h>
#define REP(x,y,z) for(int x=y;x<=z;x++)
#define MSET(x,y) memset(x,y,sizeof(x))
#define M 10005
#define INF 2'000'000'000
using namespace std;
int n,in[M],dis[30][30];
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
int dfs(int cur, int lc, int rc) {
    if (cur > n) {
        return 0;
    }

    return min(
        dis[lc][in[cur]] + dfs(cur+1, in[cur], rc),
        dis[rc][in[cur]] + dfs(cur+1, lc, in[cur]));
}
void work() {
    string tmp;
    cin >> tmp;
    REP(i,1,n) in[i] = tmp[i-1] - 'A';
    printf("%d\n", dfs(1, 'F'-'A', 'J'-'A'));
}
int main()
{
    init();
    while (~scanf("%d", &n)) {
        work();
    }
    return 0;
}
