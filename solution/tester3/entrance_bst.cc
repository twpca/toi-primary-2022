#include<map>
#include<cstdio>
using namespace std;

int main(){
   int n, r;
   scanf("%d%d", &n, &r);
   map<pair<int, int>, int> bst;
   while(n-- > 0){
      int x, y;
      scanf("%d%d", &x, &y);
      for(int dx=-r; dx<=r; ++dx) for(int dy=-r; dy<=r; ++dy){
         if(dx*dx+dy*dy <= r*r){
            ++bst[{x+dx, y+dy}];
         }
      }
   }
   int ans = 0;
   for(auto [_, cnt]: bst) if(cnt % 2){
      ++ans;
   }
   printf("%d\n", ans);
}
