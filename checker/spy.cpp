#include "testlib.h"
#include<bits/stdc++.h>
#define REP(x,y,z) for(int x=y;x<=z;x++)
#define MSET(x,y) memset(x,y,sizeof(x))
using namespace std;
int n, m;
int toid(int x,int y) {
    return x*m + y;
}
pair<int,int> toxy(int id) {
    return pair<int,int> (id/m, id%m);
}
bool has_edge(int a,int b) {
    auto [xa, ya] = toxy(a);
    auto [xb, yb] = toxy(b);
    return xa!=xb && ya!=yb && abs(xa-xb)!=abs(ya-yb);
}
int main(int argc, char * argv[])
{
    inf.maxFileSize = 1024 * 1024 * 1024; // 1024MB
    setName("spy special judge");
    registerTestlibCmd(argc, argv);

    n = inf.readInt();
    m = inf.readInt();

    // check if no ans
    int noans = ans.readInt();
    if (noans == -1) {
        ouf.readInt(-1, -1);
        quitf(_ok, "LGTM");
    }

    // has ans
    // read user input
    vector<int> user_ans(n*m+2, 0);
    for (int i=1; i <= n*m + 1; i++) {
        int x = ouf.readInt(1, n);
        int y = ouf.readInt(1, m);
        user_ans[i] = toid(x-1, y-1);
    }

    // check start and end
    if (user_ans[1] != user_ans[n*m + 1]) {
        quitf(_wa, "start != end vertex");
    }

    // check duplicated vertices
    vector<bool> vis(n*m+1, false);
    for (int i=1; i<=n*m; i++) {
        int cur = user_ans[i];
        if (vis[cur]) {
            quitf(_wa, "vertex %d is visited twice", cur);
        }
        vis[cur] = true;
    }

    // check connectivity
    for (int i=1; i<=n*m; i++) {
        int cur = user_ans[i];
        int nxt = user_ans[i+1];
        if (!has_edge(cur, nxt)) {
            quitf(_wa, "%d and %d not connected", cur, nxt);
        }
    }

    quitf(_ok, "LGTM");
    return 0;
}
