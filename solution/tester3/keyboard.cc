#include<algorithm>
#include<iostream>
#include<iterator>
#include<string>
#include<cstdio>
#include<cstring>
using namespace std;

constexpr int INF = 1'000'000'000;
int dis[26][26];

void init(){
   static char const *s[] = {"QWERTYUIOP", "ASDFGHJKL", "ZXCVBNM"};
   static int const len[] = {strlen(s[0]), strlen(s[1]), strlen(s[2])};
   for(int i=0; i<=25; ++i) for(int j=i+1; j<=25; ++j){
      dis[i][j] = dis[j][i] = INF;
   }
   for(int i=0; i<=2; ++i){
      for(int j=0; j+1<=len[i]-1; ++j){
         dis[s[i][j]-'A'][s[i][j+1]-'A'] = dis[s[i][j+1]-'A'][s[i][j]-'A'] = 1;
      }
   }
   for(int i=1; i<=2; ++i){
      for(int j=0; j<=len[i]-1; ++j){
         dis[s[i-1][j]-'A'][s[i][j]-'A'] = dis[s[i][j]-'A'][s[i-1][j]-'A'] = 1;
         dis[s[i-1][j+1]-'A'][s[i][j]-'A'] = dis[s[i][j]-'A'][s[i-1][j+1]-'A'] = 1;
      }
   }
   for(int i=0; i<=25; ++i) for(int j=0; j<=25; ++j) for(int k=0; k<=25; ++k){
      dis[j][k] = min(dis[j][k], dis[j][i]+dis[i][k]);
   }
}

int main(){
   init();
   int n; string s;
   cin >> n >> s;
   for(int i=0; i<=n-1; ++i){
      s[i] -= 'A';
   }
   int d[2][26];
   for(int i=0; i<=25; ++i){
      d[0][i] = min(dis['F'-'A'][s[0]]+dis['J'-'A'][i], dis['J'-'A'][s[0]]+dis['F'-'A'][i]);
   }
   for(int i=1; i<=n-1; ++i){
      fill(begin(d[i&1]), end(d[i&1]), INF);
      for(int j=0; j<=25; ++j){
         d[i&1][j] = min(d[i&1][j], d[i-1&1][j]+dis[s[i-1]][s[i]]);
         d[i&1][s[i-1]] = min(d[i&1][s[i-1]], d[i-1&1][j]+dis[j][s[i]]);
      }
   }
   int ans = *min_element(cbegin(d[n-1&1]), cend(d[n-1&1]));
   printf("%d\n", ans);
}
