// O(2^(nm)) DP
// Expect: subtask 1
#include<bits/stdc++.h>
#define REP(x,y,z) for(int x=y;x<=z;x++)
#define MSET(x,y) memset(x,y,sizeof(x))
#define M 2005
using namespace std;
bool e[M][M];
int toid(int m, int x,int y) {
    return x*m + y;
}
struct DPSolver {
    int n, m;
    DPSolver(int _n, int _m) :n(_n), m(_m) {}
    int B(int x) { return 1<<x; }

    vector<int> check(int st) {
        int msk = B(n*m) - 1;
        vector<vector<bool>> dp(
            B(n*m),
            vector<bool> (n*m)
        );
        vector<vector<int>> fr1(
            B(n*m),
            vector<int> (n*m)
        );
        vector<vector<int>> fr2(
            B(n*m),
            vector<int> (n*m)
        );
        dp[B(st)][st] = true;

        REP(i,0,msk-1) REP(j,0,n*m-1) if (dp[i][j]) {
            REP(k,0,n*m-1) if (e[j][k] && (B(k) & i) == 0) {
                int i2 = i | B(k);
                int j2 = k;
                dp[i2][j2] = true;
                fr1[i2][j2] = k;
                fr2[i2][j2] = j;
            }
        }

        vector<int> res;
        REP(ed,0,n*m-1) if (dp[msk][ed] && e[ed][st]) {
            int i = msk;
            int j = ed;
            while (i != B(st)) {
                res.push_back(fr1[i][j]);
                int tmp = fr2[i][j];
                i = i ^ B(fr1[i][j]);
                j = tmp;
            }
            res.push_back(st);
            break;
        }
        reverse(res.begin(), res.end());
        return res;
    }

    vector<int> solve() {
        REP(i,0,n*m-1) {
            vector<int> v = check(i);
            if (v.size()) {
                return v;
            }
        }
        return vector<int>();
    }
};
bool init(int n, int m) {
    MSET(e, false);
    vector<int> deg(n*m+1, 0);

    REP(i1,0,n-1) REP(j1,0,m-1) REP(i2,0,n-1) REP(j2,0,m-1) {
        if (i1==i2 || j1==j2) continue;
        if (i1-j1 == i2-j2) continue;
        if (i1+j1 == i2+j2) continue;

        int x = toid(m, i1, j1);
        int y = toid(m, i2, j2);
        e[x][y] = true;
        deg[x]++;
    }

    // check if deg[i] + deg[j] >= nm
    REP(i,0,n*m-1) REP(j,i+1,n*m-1) {
        if (e[i][j]) continue;
        if (deg[i] + deg[j] < n*m) return false;
    }
    return true;
}
bool noans(int x,int y) {
    if (x > y) swap(x, y);
    if (x==2 && y<=4) return true;
    if (x==3 && y==3) return true;
    return false;
}
int main()
{
    srand(114514);
    int n, m;
    while (~scanf("%d %d", &n, &m)) {
        if (noans(n, m)) {
            puts("-1");
            continue;
        }

        init(n, m);
        DPSolver s(n, m);
        auto v = s.solve();
        for (int i: v) {
            printf("%d %d\n", i/m+1, i%m+1);
        }
        printf("%d %d\n", v[0]/m+1, v[0]%m+1);
    }
    return 0;
}
