#include<bits/stdc++.h>
#include "testlib.h"
#define REP(x,y,z) for(int x=y;x<=z;x++)
#define MSET(x,y) memset(x,y,sizeof(x))
using namespace std;
using LL = long long;
constexpr int MN_N = 1;
constexpr int MX_N[] = {100'000, 100, 100'000, 100'000, 100'000};
constexpr int MN_K = 1;
constexpr int MX_K = 10;
constexpr int MN_D = 1;
constexpr int MX_D = 1000;
int n, k;
vector<int> w, deg;
vector<vector<int>> e;
int subtask(int argc, char* argv[]) {
    for (int i=1; i<argc; i++) {
        if (!strcmp("--testcase", argv[i-1])) {
            return atoi(argv[i]);
        }
    }
    assert(0);
    return -1;
}
int dfs(int cur, vector<bool>& vis) {
    int res = 1;
    vis[cur] = true;
    for (int i: e[cur]) if (!vis[i]) res += dfs(i, vis);
    return res;
}
bool is_tree() {
    vector<bool> vis(n+1, false);
    return dfs(1, vis) == n;
}
bool only_one_bigger_k() {
    int cnt = 0;
    REP(i,1,n) if (w[i] > k) cnt++;
    return cnt == 1;
}
bool is_line() {
    int c1=0, c2=0;
    REP(i,1,n) {
        if (deg[i] >= 3) return false;
        if (deg[i] <= 0) return false;
        if (deg[i] == 2) c2++;
        if (deg[i] == 1) c1++;
    }

    return c1==min(2,n) && c2==max(0,n-2);
}
int main(int argc,char* argv[]) {
    registerValidation(argc, argv);
    int s = subtask(argc, argv);
    n = inf.readInt(MN_N, MX_N[s], "n");
    inf.readChar(' ');
    k = inf.readInt(MN_K, MX_K, "k");
    inf.readChar('\n');

    w = vector<int> (n+1);
    REP(i,1,n) {
        w[i] = inf.readInt(0, n*k, "w_i");
        if (i==n) {
            inf.readChar('\n');
        } else {
            inf.readChar(' ');
        }
    }
    ensuref(accumulate(w.begin()+1, w.begin()+n+1, 0LL) == (LL)n*k, "sum of w should be nk");
    
    deg = vector<int> (n+1);
    e = vector<vector<int>> (n+1);
    REP(i,1,n-1) {
        int x = inf.readInt(1, n, "u");
        inf.readChar(' ');
        int y = inf.readInt(1, n, "v");
        inf.readChar(' ');
        int d = inf.readInt(MN_D, MX_D, "d");
        inf.readChar('\n');

        e[x].push_back(y);
        e[y].push_back(x);
        deg[x]++;
        deg[y]++;
    }
    inf.readEof();

    ensuref(is_tree(), "given graph should be a tree");
    if (s == 2) {
        ensuref(only_one_bigger_k(), "only one w[i] can bigger than k");
    }
    if (s == 3) {
        ensuref(is_line(), "given graph should be a line");
    }
    return 0;
}
