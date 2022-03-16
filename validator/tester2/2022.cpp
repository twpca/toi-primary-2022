#include<bits/stdc++.h>
#include "testlib.h"
#define REP(x,y,z) for(int x=y;x<=z;x++)
#define MSET(x,y) memset(x,y,sizeof(x))
using namespace std;
using LL = long long;
constexpr int MN_N = 1;
constexpr int MX_N[] = {100'000, 10, 30, 300, 100'000, 100'000};
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
    int n0 = inf.readInt(MN_N, MX_N[s], "n0");
    inf.readChar(' ');
    int n2 = inf.readInt(MN_N, MX_N[s], "n2");
    inf.readChar('\n');

    inf.readEof();

    if (s == 4) {
        ensuref(n2 % 2 == 0, "n2 should be even");
    }
    return 0;
}
