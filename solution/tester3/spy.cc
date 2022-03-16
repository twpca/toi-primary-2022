#include<utility>
#include<cstdio>
using namespace std;

int main(){
   int n, m;
   scanf("%d%d", &n, &m);
   bool t = n>m;
   if(t){
      swap(n, m);
   }
   int x[2]{};
   auto loli = [n, m, t, &x]{
      printf("%d %d\n", x[t]+1, x[!t]+1);
      x[0] = (x[0]+1)%n;
      if(x[0] == 0){
         x[1] = (x[1]+m-1)%m;
      }else if(x[0]%2 == 0){
         x[1] = (x[1]+m-2)%m;
      }else{
         x[1] = (x[1]+2)%m;
      }
   };
   if(n == 2){
      if(m <= 4){
         puts("-1"); return 0;
      }
      do{
         printf("%d %d\n", x[t]+1, x[!t]+1);
         x[0] = (x[0]+1)%n;
         if(x[0] == 0){
            x[1] = (x[1]+m-3)%m;
         }else{
            x[1] = (x[1]+2)%m;
         }
      }while(x[0] || x[1]);
   }else if(n == 3){
      if(m == 3){
         puts("-1"); return 0;
      }
      do
         loli();
      while(x[0] || x[1]);
   }else if(n == 4){
      if(m == 4){
         puts("1 1\n2 3\n3 1\n1 2\n2 4\n3 2\n1 3\n4 4\n2 1\n3 3\n1 4\n4 2\n3 4\n4 1\n2 2\n4 3");
      }else{
         do
            loli();
         while(x[0] || x[1]);
      }
   }else if(n%2 == 1){
      if(m == n){
         do{
            printf("%d %d\n", x[t]+1, x[!t]+1);
            x[0] = (x[0]+1)%n;
            if(x[0]==0 || x[0]%2==1){
               x[1] = (x[1]+2)%m;
            }else{
               x[1] = (x[1]+m-2)%m;
            }
         }while(x[0] || x[1]);
      }else{
         do
            loli();
         while(x[0] || x[1]);
      }
   }else{
      if(m == n){
         do{
            printf("%d %d\n", x[t]+1, x[!t]+1);
            x[0] = (x[0]+1)%n;
            if(x[0] == 0){
               x[1] = (x[1]+m-3)%m;
            }else if(x[0]%2 == 0){
               x[1] = (x[1]+m-2)%m;
            }else{
               x[1] = (x[1]+2)%m;
            }
         }while(x[0] || x[1]);
      }else{
         do
            loli();
         while(x[0] || x[1]);
      }
   }
   puts("1 1");
}
