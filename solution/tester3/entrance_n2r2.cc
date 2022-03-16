#include<algorithm>
#include<vector>
#include<cstdio>
using namespace std;
using i64 = long long;

struct Pt{
   int x, y;
   Pt() = default;
   constexpr Pt(int x, int y) noexcept: x(x), y(y){}
};

i64 hypot2(int x, int y) noexcept{
   return (i64)x*x+(i64)y*y;
}

int main(){
   int n, r;
   scanf("%d%d", &n, &r);
   vector<Pt> p(n);
   for(int i=0; i<=n-1; ++i){
      scanf("%d%d", &p[i].x, &p[i].y);
   }
   int ans = 0;
   for(int i=0; i<=n-1; ++i){
      for(int dx=-r; dx<=r; ++dx) for(int dy=-r; dy<=r; ++dy) if(hypot2(dx, dy) <= r*r){
         auto my_lambda = [r, x=p[i].x+dx, y=p[i].y+dy](Pt const &pj) noexcept{
            return hypot2(pj.x-x, pj.y-y) <= r*r;
         };
         ans += none_of(p.cbegin(), p.cbegin()+i, my_lambda) && count_if(p.cbegin()+i+1, p.cend(), my_lambda)%2==0;
      }
   }
   printf("%d\n", ans);
}
