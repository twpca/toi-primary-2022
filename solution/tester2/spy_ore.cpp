// O(n^2 m^2): construct path for sufficiently large testdata using Ore's theorem
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
struct BruteSolver {
    const int MAGIC = 10000;
    int n, m, cnt;
    bool find_ans;
    vector<int> ord, ans;
    vector<bool> vis;

    BruteSolver(int _n, int _m) :n(_n), m(_m) {
        find_ans = false;
        vis = vector<bool> (n*m+1, false);

        n = _n;
        m = _m;
        cnt = 0;
        ord.clear();
        REP(i,0,n*m-1) ord.push_back(i);
    }

    void dfs(int id) {
        cnt++;
        if (id >= n*m) {
            if (e[ans[n*m-1]][ans[0]]) {
                find_ans = true;
            }
            return;
        }

        int c0 = cnt;
        REP(i,0,n*m-1) {
            if (vis[ord[i]]) continue;
            if (id >= 1 && !e[ans[id-1]][ord[i]]) continue;
            ans.push_back(ord[i]);
            vis[ord[i]] = true;
            dfs(id + 1);
            if (find_ans) break;

            vis[ord[i]] = false;
            ans.pop_back();
            if (cnt - c0 > MAGIC) break;
        }
    }

    vector<int> solve() {
        while (!find_ans) {
            ans.clear();
            random_shuffle(ord.begin(), ord.end());
            fill(vis.begin(), vis.end(), false);
            dfs(0);
        }
        return ans;
    }
};
struct OreSolver {
    int n, m;
    OreSolver(int _n, int _m) :n(_n), m(_m) {}
    vector<int> solve() {
        vector<int> res;
        REP(i,0,n*m-1) res.push_back(i);

        auto mod_id = [this](int x) {
            x = x % (this->n * this->m);
            if (x < 0) x += n * this->m;
            return x;
        };
        auto get_res = [mod_id, &res](int x) {
            return res[mod_id(x)];
        };
        auto cyclic_reverse = [mod_id, &res](int l,int r) {
            REP(i,l,r) {
                int j = r - (i-l);
                if (i>=j) break;
                swap(res[mod_id(i)], res[mod_id(j)]);
            }
        };

        REP(_, 1, 2) REP(i, 0, n*m-1) {
            int cur = get_res(i);
            int nxt = get_res(i+1);
            if (!e[cur][nxt]) {
                REP(j, 2, n*m-2) {
                    int cur2 = get_res(i+j);
                    int nxt2 = get_res(i+j+1);
                    if (e[cur][cur2] && e[nxt][nxt2]) {
                        cyclic_reverse(i+1, i+j);
                        break;
                    }
                }
            }
        }
        return res;
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

        bool ore_valid = init(n, m);
        vector<int> v;
        if (ore_valid) {
            OreSolver s(n, m);
            v = s.solve();
        } else {
            BruteSolver s(n, m);
            v = s.solve();
        }

        for (int i: v) {
            printf("%d %d\n", i/m+1, i%m+1);
        }
        printf("%d %d\n", v[0]/m+1, v[0]%m+1);
    }
    return 0;
}
