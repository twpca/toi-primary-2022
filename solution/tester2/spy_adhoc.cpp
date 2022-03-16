// O(n^2 m^2) Adhoc solution
// Expect: AC
#include<bits/stdc++.h>
#define REP(x,y,z) for(int x=y;x<=z;x++)
#define MSET(x,y) memset(x,y,sizeof(x))
#define M 2005
using namespace std;
bool e[M][M];
int toid(int m, int x,int y) {
    return x*m + y;
}
struct AdHocSolver {
    using P = pair<int,int>;
    int n, m;
    bool rev;
    AdHocSolver(int _n, int _m){
        n = _n;
        m = _m;
        rev = false;
        if (n > m) {
            swap(n, m);
            rev = true;
        }
    }

    vector<P> repeat_xy_vector(int x, int y, int z) {
        // (1, x) (1, y) (1, x) (1, y)..., (1, z)
        vector<P> res;
        while ((int)res.size() < n-1) {
            res.emplace_back(1, x);
            if ((int)res.size() < n-1) {
                res.emplace_back(1, y);
            }
        }
        res.emplace_back(1, z);
        return res;
    }

    vector<P> get_base_vector() {
        if (n==2) {
            return vector<P> {
                P(1, 2),
                P(1, -3)
            };
        } else if (n%2 == 0) { // n%2==0, n>=4
            if (n == m) {
                return repeat_xy_vector(2, -2, -3);
            } else {
                return repeat_xy_vector(2, -2, -1);
            }
        } else { // n%2==1, n>=3
            if (n == m) {
                return repeat_xy_vector(2, -2, 2);
            } else {
                return repeat_xy_vector(2, -2, 1);
            }
        }
    }

    void add_node(vector<int> &v, int x, int y) {
        if (!rev) {
            v.push_back(toid(m, x, y));
        } else {
            v.push_back(toid(n, y, x));
        }
    }

    vector<int> construct(vector<P>& vs) {
        vector<int> res;
        int x = 0;
        int y = 0;
        int p = 0;
        add_node(res, x, y);
        while ((int)res.size() < n*m) {
            x = ((x + vs[p].first ) % n + n) % n;
            y = ((y + vs[p].second) % m + m) % m;
            p = (p + 1) % (int)vs.size();
            add_node(res, x, y);
        }
        return res;
    }

    vector<int> solve() {
        if (n==4 && m==4) {
            return vector<int> {0, 6, 8, 14, 1, 7, 9, 15,
                2, 4, 10, 12, 11, 5, 3, 13};
        }
        vector<P> base = get_base_vector();
        return construct(base);
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
        AdHocSolver s(n, m);
        auto v = s.solve();
        for (int i: v) {
            printf("%d %d\n", i/m+1, i%m+1);
        }
        printf("%d %d\n", v[0]/m+1, v[0]%m+1);
    }
    return 0;
}
