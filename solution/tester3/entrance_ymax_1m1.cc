#include<unordered_map>
#include<cstdio>
using namespace std;

using i64 = long long;
constexpr i64 Y_MAX = 1'000'001;

int main(){
   int n, r;
   scanf("%d%d", &n, &r);
   unordered_map<i64, int> um;
   while(n-- > 0){
      int x, y;
      scanf("%d%d", &x, &y);
      for(int dx=-r; dx<=r; ++dx) for(int dy=-r; dy<=r; ++dy){
         if(dx*dx+dy*dy <= r*r){
            ++um[(x+dx)*Y_MAX+(y+dy)];
         }
      }
   }
   int ans = 0;
   for(auto [_, cnt]: um) if(cnt % 2){
      ++ans;
   }
   printf("%d\n", ans);
}
