// O(n)
// Expect: AC
#include<bits/stdc++.h>
#define REP(x,y,z) for(int x=y;x<=z;x++)
#define MSET(x,y) memset(x,y,sizeof(x))
#define M 100005
using namespace std;
using P = pair<int,int>;
using LL = long long;
int n,k,w[M];
vector<P> e[M];
void init() {
    REP(i,1,n) e[i].clear();
    REP(i,1,n) scanf("%d", &w[i]);
    REP(i,1,n-1) {
        int x, y, z;
        scanf("%d %d %d", &x, &y, &z);
        e[x].push_back(P(y,z));
        e[y].push_back(P(x,z));
    }
}
pair<LL,int> dfs(int cur,int fa,int fd) {
    LL res = 0;
    int up = 0;

    for (auto i: e[cur]) if (i.first != fa) {
        auto tmp = dfs(i.first, cur, i.second);
        res += tmp.first;
        up += tmp.second;
    }
    res += (LL)abs(up + w[cur] - k)*fd;
    up += w[cur] - k;
    return make_pair(res, up);
}
int main()
{
    while (~scanf("%d %d", &n, &k)) {
        init();
        printf("%lld\n", dfs(1,-1,0).first);
    }
    return 0;
}
