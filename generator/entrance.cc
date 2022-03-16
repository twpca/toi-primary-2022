#include<algorithm>
#include<random>
#include<string>
#include<unordered_set>
#include<vector>
#include<cassert>
#include<cmath>
#include<cstdio>
using namespace std;
using i64 = long long;

constexpr int N = 2500;
constexpr int R = 10;
constexpr int X[]{1'000'000, 1'000'000, 100, 1'000'000};
constexpr i64 Y_MAX = 10'000'000;

struct Pt{
   int x, y;
   Pt() = default;
   constexpr Pt(int x, int y) noexcept: x(x), y(y){}
};
bool operator==(Pt const &p, Pt const &q) noexcept{
   return p.x==q.x && p.y==q.y;
}
namespace std{
   template<> struct hash<Pt>{
      size_t operator()(Pt const &p) const noexcept{
         return hash<i64>()(p.x*Y_MAX+p.y);
      }
   };
}

struct Gen{
   Gen() = default;
   constexpr void next() noexcept{
      ++subtask; file = 0;
   }
   int get_subtask() const noexcept{
      return subtask;
   }
   void gen(int r, vector<Pt> const &p, string comment = "random"){
      static char fn_prefix[20];
      sprintf(fn_prefix, "%d_%02d_", subtask, ++file);
      FILE *fout = fopen((fn_prefix+comment+".in").data(), "wb");
      fprintf(fout, "%zu %d\n", p.size(), r);
      for(auto [x, y]: p){
         fprintf(fout, "%d %d\n", x, y);
      }
      fclose(fout);
   }
private:
   int subtask = 0, file = 0;
};

mt19937_64 Rng;
using Unif = uniform_int_distribution<>;
int rand_intvl(int l, int r){
   return Unif(l, r)(Rng);
}
Pt rand_pt(int subtask){
   int x = rand_intvl(-X[subtask], X[subtask]);
   int y = rand_intvl(-X[subtask], X[subtask]);
   return {x, y};
}
// given p, generate other points to give a large test case
void gen_random(Gen &g, vector<Pt> &p, int seed, string comment = "random"){
   Rng.seed(seed);
   int subtask = g.get_subtask();
   unordered_set<Pt> s(p.cbegin(), p.cend());
   static_assert(N > 100);
   int n = N-rand_intvl(0, 100);
   while((int)s.size() < n){
      auto pi = rand_pt(subtask);
      if(s.insert(pi).second){
         p.push_back(pi);
      }
   }
   shuffle(p.begin(), p.end(), Rng);
   g.gen(R, p, comment);
   p.clear();
}

int main(){
   int const sqrtn = sqrt(N);
   Gen g;
   int subtask;
   vector<Pt> p; p.reserve(N);

   // subtask 1
   g.next();
   subtask = g.get_subtask();
   static_assert(R >= 4);
   // generate r = 1..R-4
   for(int r=1; r<=R-4; ++r){
      Rng.seed(38^r);
      static char comment[20];
      sprintf(comment, "r_eq_%d", r);
      g.gen(r, {rand_pt(subtask)}, comment);
   }
   // generate r = R-3..R
   Rng.seed(58);
   g.gen(R-3, {{-X[subtask]+rand_intvl(0, 5), X[subtask]-rand_intvl(0, 5)}}, "r_eq_7");
   Rng.seed(78);
   g.gen(R-2, {{X[subtask]-rand_intvl(0, 5), X[subtask]-rand_intvl(0, 5)}}, "r_eq_8");
   Rng.seed(87);
   g.gen(R-1, {{-X[subtask]+rand_intvl(0, 5), -X[subtask]+rand_intvl(0, 5)}}, "r_eq_9");
   Rng.seed(98);
   g.gen(R, {{X[subtask]-rand_intvl(0, 5), -X[subtask]+rand_intvl(0, 5)}}, "r_eq_10");

   // subtask 2
   g.next();
   subtask = g.get_subtask();
   g.gen(2, {{0, 0}, {-1, 0}, {2, 0}}, "sample");
   Rng.seed(426);
   for(int i=1; i<=sqrtn; ++i) for(int j=1; j<=sqrtn; ++j){
      p.emplace_back(i, j);
   }
   shuffle(p.begin(), p.end(), Rng);
   g.gen(R, p, "49_by_49_grid");
   p.clear();
   Rng.seed(689);
   for(int i=0; i<=sqrtn-1; ++i) for(int j=0; j<=sqrtn-1; ++j){
      int x = (2*i/(sqrtn-1.)-1)*X[subtask];
      int y = (2*j/(sqrtn-1.)-1)*X[subtask];
      p.emplace_back(x, y);
   }
   shuffle(p.begin(), p.end(), Rng);
   g.gen(R, p, "49_by_49_larger_grid");
   p.clear();
   // random
   for(int T=10; T-->0; ){
      gen_random(g, p, 765^T);
   }

   // subtask 3
   g.next();
   subtask = g.get_subtask();
   for(int i: {0, 1}) for(int j: {0, 1}){
      p.emplace_back(i*X[subtask], j*X[subtask]);
   }
   g.gen(R, p, "small_corner_case_1");
   p.clear();
   for(int i: {-1, 1}) for(int j: {-1, 1}){
      p.emplace_back(i*X[subtask], j*X[subtask]);
   }
   g.gen(R, p, "small_corner_case_2");
   p.clear();
   p.emplace_back(-1, -1);
   p.emplace_back(-1, 0);
   p.emplace_back(0, -1);
   for(int i: {0, 1}) for(int j: {0, 1}){
      p.emplace_back(i*X[subtask], j*X[subtask]);
   }
   g.gen(R, p, "small_corner_case_3");
   p.clear();
   for(int i: {-2, -1, 0}) for(int j: {-2, -1, 0}){
      p.emplace_back(i, j);
   }
   p.emplace_back(0, X[subtask]);
   p.emplace_back(X[subtask], 0);
   p.emplace_back(X[subtask], X[subtask]);
   g.gen(R, p, "small_corner_case_4");
   p.clear();
   // manual small corner case 1 + random
   for(int i: {0, 1}) for(int j: {0, 1}){
      p.emplace_back(i*X[subtask], j*X[subtask]);
   }
   gen_random(g, p, 5566, "large_corner_case_1");
   p.clear();
   // manual small corner case 2 + random
   for(int i: {-1, 1}) for(int j: {-1, 1}){
      p.emplace_back(i*X[subtask], j*X[subtask]);
   }
   gen_random(g, p, 7122, "large_corner_case_2");
   p.clear();
   // manual small corner case 3 + random
   p.emplace_back(-1, -1);
   p.emplace_back(-1, 0);
   p.emplace_back(0, -1);
   for(int i: {0, 1}) for(int j: {0, 1}){
      p.emplace_back(i*X[subtask], j*X[subtask]);
   }
   gen_random(g, p, 9487, "large_corner_case_3");
   p.clear();
   // manual small corner case 4 + random
   for(int i: {-2, -1, 0}) for(int j: {-2, -1, 0}){
      p.emplace_back(i, j);
   }
   p.emplace_back(0, X[subtask]);
   p.emplace_back(X[subtask], 0);
   p.emplace_back(X[subtask], X[subtask]);
   gen_random(g, p, 9527, "large_corner_case_4");
   p.clear();
   // manual large corner case, └, ┘, ┌, ┐ are placed in lower left, lower right, upper left, upper right, respectively
   Rng.seed(077777);
   constexpr int m = (N/4-1)/2;
   static_assert(m >= 1);
   for(int i: {-1, 1}) for(int j: {-1, 1}){
      p.emplace_back(i*X[subtask], j*X[subtask]);
      for(int k=1; k<=m; ++k){
         p.emplace_back(i*(X[subtask]-k), j*X[subtask]);
         p.emplace_back(i*X[subtask], j*(X[subtask]-k));
      }
   }
   shuffle(p.begin(), p.end(), Rng);
   g.gen(R, p, "large_corner_case_5");
   p.clear();
   // manual large corner case, a 49*49 grid with each side of length 20
   Rng.seed(114514);
   assert(2*(sqrtn-1)*R <= X[subtask]);
   for(int i=0; i<=sqrtn-1; ++i) for(int j=0; j<=sqrtn-1; ++j){
      p.emplace_back(-2*R*i, -2*R*j);
   }
   shuffle(p.begin(), p.end(), Rng);
   g.gen(R, p, "large_corner_case_6");
   p.clear();
   // random
   gen_random(g, p, 0XC8763);
}
