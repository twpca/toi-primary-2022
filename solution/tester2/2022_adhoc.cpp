// O(n0 + n2)
// Expect: AC
#include<bits/stdc++.h>
#define REP(x,y,z) for(int x=y;x<=z;x++)
#define MSET(x,y) memset(x,y,sizeof(x))
#define M
using namespace std;
int n0,n2,l;
string repeat(int x, string s) {
    string res = "";
    REP(i,1,x) res += s;
    return res;
}
int main()
{
    while (~scanf("%d %d", &n0, &n2)) {
        l = n0 + n2;

        if (n2%2 == 0) {
            // big
            string big;
            if (n0 == 1) {
                big = string(n2-2, '2') + "022";
            } else {
                big = string(n2-2, '2') + "2002" + string(n0-2, '0');
            }

            //small
            string small = string(n0-1, '0') + "220" + string(n2-2, '2');
            printf("%s\n%s\n", big.c_str(), small.c_str());
        } else {
            if (n2<11 || n0<10) {
                puts("-1");
                continue;
            }
            if (n2==11 && n0==10) {
                puts("-1");
                continue;
            }

            // big
            string big;
            if (n0 == 10) {
                big = string(n2-13, '2') + "20222" + repeat(9, "02");
            } else if (n0 == 11) {
                big = string(n2-11, '2') + repeat(11, "02");
            } else {
                big = string(n2-11, '2') + "20202020202020202020002" + string(n0-12, '0');
            }

            // small
            string small;
            if (n2 == 11) {
                small = string(n0-11, '0') + repeat(11, "20");
            } else {
                small = string(n0-10, '0') + "20202020202020202022202" + string(n2-13, '2');
            }
            printf("%s\n%s\n", big.c_str(), small.c_str());
        }
    }
    return 0;
}
