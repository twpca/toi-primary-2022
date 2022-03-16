// O(n)
// Greedily move the nearest finger
// Expect: WA
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
void work() {
    string tmp;
    cin >> tmp;
    REP(i,1,n) in[i] = tmp[i-1] - 'A';

    int lc = 'F' - 'A';
    int rc = 'J' - 'A';
    int ans = 0;
    REP(i,1,n) {
        if (dis[lc][in[i]] <= dis[rc][in[i]]) {
            ans += dis[lc][in[i]];
            lc = in[i];
        } else {
            ans += dis[rc][in[i]];
            rc = in[i];
        }
    }
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
