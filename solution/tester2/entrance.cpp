// O(n * r^2)
// Expect: AC
#include<bits/stdc++.h>
#define REP(x,y,z) for(int x=y;x<=z;x++)
#define MSET(x,y) memset(x,y,sizeof(x))
#define M
using namespace std;
using LL = long long;
using P = pair<int,int>;
struct Hashp {
    size_t operator () (const P &a) const {
        return hash<LL>()(10'000'000LL*a.first + a.second);
    }
};
int n,r;
int main()
{
    while (~scanf("%d %d", &n, &r)) {
        LL r2 = (LL)r*r;
        unordered_map<P,int,Hashp> vis;

        REP(_, 1, n) {
            int x, y;
            scanf("%d %d", &x, &y);
            REP(i,x-r,x+r) REP(j,y-r,y+r) {
                LL d = (LL)(x-i)*(x-i) + (LL)(y-j)*(y-j);
                if (d <= r2) {
                    vis[P(i,j)]++;
                }
            }
        }

        int ans = 0;
        for (auto i: vis) {
            if (i.second % 2) {
                ans++;
            }
        }
        printf("%d\n", ans);
    }
    return 0;
}
