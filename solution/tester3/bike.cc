#include<tuple>
#include<vector>
#include<cstdio>
#include<cstdlib>
using namespace std;
using i64 = long long;

struct Edge{
   int to, w;
   Edge() = default;
   constexpr Edge(int to, int w) noexcept: to(to), w(w){}
};

tuple<int, int, i64> dfs(int k, int const *w, vector<Edge> const *g, int u, int p){
   int size = 1, n_bike = w[u];
   i64 ans = 0;
   for(auto [v, d]: g[u]) if(v != p){
      auto [dsize, dn_bike, dans] = dfs(k, w, g, v, u);
      size += dsize;
      n_bike += dn_bike;
      ans += dans + d*abs(dsize*k-dn_bike);
   }
   return {size, n_bike, ans};
}

int main(){
   int n, k;
   scanf("%d%d", &n, &k);
   vector<int> w(n);
   for(int i=0; i<=n-1; ++i){
      scanf("%d", w.data()+i);
   }
   vector<vector<Edge>> g(n);
   for(int i=1; i<=n-1; ++i){
      int u, v, c;
      scanf("%d%d%d", &u, &v, &c);
      --u; --v;
      g[u].emplace_back(v, c);
      g[v].emplace_back(u, c);
   }
   printf("%lld\n", get<2>(dfs(k, w.data(), g.data(), 0, 0)));
}
