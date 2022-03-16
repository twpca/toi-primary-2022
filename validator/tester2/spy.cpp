#include<bits/stdc++.h>
#include "testlib.h"
#define REP(x,y,z) for(int x=y;x<=z;x++)
#define MSET(x,y) memset(x,y,sizeof(x))
using namespace std;
using LL = long long;
constexpr int MN_N[]  = {   2,    2,    2,   12,    2};
constexpr int MX_MN[] = {2000,   16, 2000, 2000, 2000};
constexpr int MX_N = 1000;
constexpr bool HAS_TWO[] = {false, false, true, false, false};

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
    int n = inf.readInt(MN_N[s], MX_N, "n");
    inf.readChar(' ');
    int m = inf.readInt(MN_N[s], MX_N, "n");
    inf.readChar('\n');
    inf.readEof();

    ensuref(n*m <= MX_MN[s], "mn should <= %d", MX_MN[s]);
    if (HAS_TWO[s]) {
        ensuref(n==2 || m==2, "m or n should = 2");
    }
    return 0;
}
