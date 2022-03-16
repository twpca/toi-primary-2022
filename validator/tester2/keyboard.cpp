#include<bits/stdc++.h>
#include "testlib.h"
#define REP(x,y,z) for(int x=y;x<=z;x++)
#define MSET(x,y) memset(x,y,sizeof(x))
using namespace std;
constexpr int MN_N = 1;
constexpr int MX_N[]{10'000, 20, 10'000, 10'000};
const string CSET[] = {
    string("[A-Z]"),
    string("[A-Z]"),
    string("[ASDFGHJKL]"),
    string("[A-Z]")
};
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
    inf.readChar('\n');

    string pattern = CSET[s] + "{" + to_string(n) + "}";
    string in = inf.readToken(pattern, "s");
    inf.readChar('\n');
    inf.readEof();
    return 0;
}
