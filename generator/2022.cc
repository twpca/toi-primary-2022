#include<random>
#include<cassert>
#include<cstdio>
using namespace std;

constexpr int N[]{100'000, 10, 30, 300, 100'000, 100'000};

struct Gen{
   Gen() = default;
   constexpr void next() noexcept{
      ++subtask; file = 0;
   }
   int get_subtask() const noexcept{
      return subtask;
   }
   void gen(int n0, int n2){
      static char fn[30];
      sprintf(fn, "%d_%03d_%d_%d.in", subtask, ++file, n0, n2);
      FILE *fout = fopen(fn, "wb");
      fprintf(fout, "%d %d\n", n0, n2);
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

int main(){
   Gen g;
   int subtask;

   g.next();
   subtask = g.get_subtask();
   assert(subtask == 1);
   for(int n0=1; n0<=N[subtask]; ++n0) for(int n2=1; n2<=N[subtask]; ++n2){
      g.gen(n0, n2);
   }

   g.next();
   subtask = g.get_subtask();
   assert(subtask == 2);
   static_assert(N[1]%2==0 && N[2]-N[1]>=10);
   for(int n0=1; n0<=N[subtask-1]+5; ++n0) for(int n2=N[subtask-1]+1; n2<=N[subtask-1]+5; ++n2){
      g.gen(n0, n2);
   }
   for(int n0=N[subtask]-4; n0<=N[subtask]; ++n0) for(int n2=N[subtask-1]+1; n2<=N[subtask]; n2+=2){
      g.gen(n0, n2);
   }
   g.gen(N[subtask], N[subtask]);

   g.next();
   subtask = g.get_subtask();
   assert(subtask == 3);
   static_assert(N[3] > 10);
   for(int n0=N[subtask]-10; n0<=N[subtask]; ++n0) for(int n2=N[subtask]-9; n2<=N[subtask]; n2+=2){
      g.gen(n0, n2);
   }
   g.gen(N[subtask], N[subtask]);

   g.next();
   subtask = g.get_subtask();
   assert(subtask == 4);
   static_assert(N[4] >= 20);
   for(int n0=1; n0<=N[1]; ++n0) for(int n2=2; n2<=N[1]; n2+=2){
      g.gen(n0, n2);
   }
   for(int n0=1; n0<=N[1]+5; ++n0) for(int n2: {12, 14}){
      g.gen(n0, n2);
   }
   static_assert(N[2]%2 == 0);
   g.gen(N[2], N[2]);
   static_assert(N[3]%2 == 0);
   g.gen(N[3], N[3]);
   for(int T=20; T-->0; ){
      Rng.seed(58^T);
      int n0 = rand_intvl(N[subtask]/10*9, N[subtask]);
      int n2 = 2*rand_intvl(N[subtask]/20*9, N[subtask]/2);
      g.gen(n0, n2);
   }
   g.gen(N[subtask], N[subtask]-N[subtask]%2);

   g.next();
   subtask = g.get_subtask();
   assert(subtask == 5);
   static_assert(N[5] >= 20);
   for(int T=20; T-->0; ){
      Rng.seed(514^T);
      int n0 = rand_intvl(N[subtask]/10*9, N[subtask]);
      g.gen(n0, 11);
   }
   for(int T=20; T-->0; ){
      Rng.seed(2266^T);
      int n0 = rand_intvl(N[subtask]/10*9, N[subtask]);
      g.gen(n0, 13);
   }
   for(int T=20; T-->0; ){
      Rng.seed(7122^T);
      int n2 = 2*rand_intvl(N[subtask]/20*9, N[subtask]/2)-1;
      g.gen(10, n2);
   }
   for(int T=20; T-->0; ){
      Rng.seed(114514^T);
      int n2 = 2*rand_intvl(N[subtask]/20*9, N[subtask]/2)-1;
      g.gen(11, n2);
   }
   for(int T=20; T-->0; ){
      Rng.seed(0XC8763^T);
      int n0 = rand_intvl(N[subtask]/10*9, N[subtask]);
      int n2 = 2*rand_intvl(N[subtask]/20*9, N[subtask]/2)-1;
      g.gen(n0, n2);
   }
   g.gen(N[subtask], N[subtask]-(N[subtask]%2==0));
}
