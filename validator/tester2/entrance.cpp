#include<bits/stdc++.h>
#include "testlib.h"
#define REP(x,y,z) for(int x=y;x<=z;x++)
#define MSET(x,y) memset(x,y,sizeof(x))
using namespace std;
constexpr int MN_R = 1;
constexpr int MX_R = 10;
constexpr int MN_N = 1;
constexpr int MX_N[] = {2'500, 1, 2'500, 2'500};
constexpr int MN_X[] = {-1'000'000, -1'000'000, -100, -1'000'000};
constexpr int MX_X[] = { 1'000'000,  1'000'000,  100,  1'000'000};
int subtask(int argc, char* argv[]) {
    for (int i=1; i<argc; i++) {
        if (!strcmp("--testcase", argv[i-1])) {
            return atoi(argv[i]);
        }
    }
    assert(0);
    return -1;
}
int main(int argc,char* argv[]) {
    registerValidation(argc, argv);
    int s = subtask(argc, argv);
    int n = inf.readInt(MN_N, MX_N[s], "n");
    inf.readChar(' ');
    int r = inf.readInt(MN_R, MX_R, "r");
    inf.readChar('\n');

    using P = pair<int,int>;
    map<P,bool> vis;
    REP(i,1,n) {
        int x = inf.readInt(MN_X[s], MX_X[s], "x");
        inf.readChar(' ');
        int y = inf.readInt(MN_X[s], MX_X[s], "y");
        inf.readChar('\n');

        P tmp = make_pair(x, y);
        ensuref(!vis[tmp], "(%d, %d) is duplicated", x, y);
        vis[tmp] = true;
    }
    inf.readEof();
    return 0;
}
