// script to test all solutions and all valid testdatas
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
struct Validator {
    int check_vertices(int n, int m, vector<int> v) {
        // return error index
        // return -1 if no issue
        int px = -1;
        int py = -1;
        int pa = -10000000;
        int pb = -10000000;

        if ((int)v.size() != n*m) return false;

        vector<bool> vis(n*m+1);
        REP(idx, 0, (int)v.size()-1) {
            int i = v[idx];
            if (vis[i]) return idx;
            vis[i] = true;
        }

        v.push_back(v[0]);
        REP(idx, 0, (int)v.size()-1) {
            int i = v[idx];
            int x = i/m;
            int y = i%m;
            if (x>=n || x<0) return idx;
            if (y>=m || y<0) return idx;
            if (x==px || y==py) return idx;
            if (x+y == pa) return idx;
            if (x-y == pb) return idx;
            px = x;
            py = y;
            pa = x+y;
            pb = x-y;
        }
        return -1;
    }

    void validate(const char* algo, int n, int m, vector<int>& v) {
        int err = check_vertices(n, m, v);
        if (err != -1) {
            printf("%s: n=%d m=%d\n", algo, n, m);
            if ((int)v.size() != n*m) {
                printf("v.size() = %d\n", (int)v.size());
            } else {
                printf("erridx = %d\n", err);
            }
            REP(idx, 0, (int)v.size()-1)  {
                int i = v[idx];
                printf("(%d, %d)", i/m, i%m);
                if (idx == err) {
                    puts(" <=");
                } else {
                    puts("");
                }
            }
            exit(0);
        }
    }

    void check_all(int mxa) {
        REP(n,2,mxa) REP(m,2,mxa) {
            if (n*m > 2000) break;
            bool ore_valid = init(n, m);
            /*if (!noans(n, m) && n*m <= 16) {
                auto s = new DPSolver(n, m);
                auto v = s->solve();
                validate("dp", n, m, v);
            }*/
            if (!noans(n, m)) {
                if (m==2)printf("%d %d\n",n,m);
                auto s = new BruteSolver(n, m);
                auto v = s->solve();
                validate("brute", n, m, v);
            }
            /*if (!noans(n,m) && ore_valid) {
                auto s = new OreSolver(n, m);
                auto v = s->solve();
                validate("ore", n, m, v);
            }
            if (!noans(n,m)) {
                auto s = new AdHocSolver(n, m);
                auto v = s->solve();
                validate("adhoc", n, m, v);
            }*/
        }
    }
};
int main()
{
    srand(114514);
    Validator v;
    v.check_all(1000);
    return 0;
}
