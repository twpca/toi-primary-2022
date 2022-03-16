#include<random>
#include<string>
#include<cassert>
#include<cstdio>
using namespace std;

#define FJ "ASDFGHJKL"
constexpr int Fj_len = sizeof FJ/sizeof*FJ - 1;
static_assert(Fj_len == 9);

mt19937_64 Rng;
using Unif = uniform_int_distribution<>;
Unif Upper_dis('A', 'Z');
char Rand_upper(){
   return static_cast<char>(Upper_dis(Rng));
}
char Rand_fj(){
   return FJ[Unif(0, Fj_len-1)(Rng)];
}

struct Gen{
   Gen() = default;
   constexpr void next() noexcept{
      ++subtask; file = 0;
   }
   int get_subtask() const noexcept{
      return subtask;
   }
   void gen(string s, string comment){
      static char fn_prefix[20];
      sprintf(fn_prefix, "%d_%02d_", subtask, ++file);
      FILE *fout = fopen((fn_prefix+comment+".in").data(), "wb");
      fprintf(fout, "%zu\n%s\n", s.size(), s.data());
      fclose(fout);
   }
   void gen_rand(int l, int r, char(*f)()){
      int size = Unif(l, r)(Rng);
      string s(size, ' ');
      for(int i=0; i<=size-1; ++i){
         s[i] = f();
      }
      gen(s, to_string(size));
   }
private:
   int subtask = 0, file = 0;
};

constexpr int N[]{10'000, 20, 10'000, 10'000};
#define ALFQ "ALFQ"
#define ALFA "ALFA"

int main(){
   Gen g;
   int subtask;

   g.next();
   g.gen("N", "N");
   g.gen("ALG", "ALG");
   g.gen(ALFQ, ALFQ);
   g.gen(ALFQ ALFQ ALFQ ALFQ ALFQ, "5" ALFQ);
   g.gen(ALFA, ALFA);
   g.gen("FJTNYBUVJF", "FJTNYBUVJF");
   for(int T=10; T-->0; ){
      Rng.seed(13540^T);
      g.gen_rand(20-T, 20-T, Rand_upper);
   }

   g.next();
   subtask = g.get_subtask();
   g.gen("ALG", "ALG");
   g.gen(ALFA, ALFA);
   assert(N[subtask] > 90);
   for(int T=10; T-->0; ){
      Rng.seed(50216^T);
      g.gen_rand(N[subtask]-Unif(0, 10*T)(Rng), N[subtask], Rand_fj);
   }

   g.next();
   subtask = g.get_subtask();
   assert(N[subtask] > 90);
   for(int T=10; T-->0; ){
      Rng.seed(0XC8763^T);
      g.gen_rand(N[subtask]-Unif(0, 10*T)(Rng), N[subtask], Rand_upper);
   }
}
