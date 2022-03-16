#include<unordered_map>
#include<cstdio>
using namespace std;

template<typename T, typename U> struct hash<pair<T, U>>{
   size_t operator()(pair<T, U> const &p) const noexcept{
      return hash<T>()(p.first) ^ hash<U>()(p.second);
   }
};

int main(){
   int n, r;
   scanf("%d%d", &n, &r);
   unordered_map<pair<int, int>, int> um;
   while(n-- > 0){
      int x, y;
      scanf("%d%d", &x, &y);
      for(int dx=-r; dx<=r; ++dx) for(int dy=-r; dy<=r; ++dy){
         if(dx*dx+dy*dy <= r*r){
            ++um[{x+dx, y+dy}];
         }
      }
   }
   int ans = 0;
   for(auto [_, cnt]: um) if(cnt % 2){
      ++ans;
   }
   printf("%d\n", ans);
}
