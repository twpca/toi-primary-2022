// O( C(n0 + n2, n0) )
// Expect: subtask1 AC, subtask 2 TLE
#include<bits/stdc++.h>
#define REP(x,y,z) for(int x=y;x<=z;x++)
#define MSET(x,y) memset(x,y,sizeof(x))
#define M 1005
using namespace std;
int n0, n2, pw[2*M];
vector<string> ps;
void dfs(int m0, int m2, int mod, string cur) {
    if (m0 == 0 && m2 == 0) {
        if (mod == 0) ps.push_back(cur);
        return;
    }
    if (m0 > 0) dfs(m0-1, m2, mod, cur + "0");
    if (m2 > 0) dfs(m0, m2-1, (mod + 2*pw[m0 + m2 - 1]) % 11, cur + "2");
}
void print(string &s) {
    for (char c: s) {
        printf("%c", c);
    }
    puts("");
}
int main()
{
    pw[0] = 1;
    REP(i,1,2*M-1) pw[i] = pw[i-1] * 10 % 11;

    while (~scanf("%d %d", &n0, &n2)) {
        ps.clear();
        dfs(n0, n2, 0, "");

        if (ps.size() < 2) {
            puts("-1");
            continue;
        }
        print(ps[(int)ps.size()-2]);
        print(ps[1]);
    }
    return 0;
}
