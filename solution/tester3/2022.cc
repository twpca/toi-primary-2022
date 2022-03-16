#include<string>
#include<cstdio>
using namespace std;

#define KISEKI "2020202020202020202"

int main(){
   int n0, n2;
   scanf("%d%d", &n0, &n2);
   if(n2%2 == 0){
      if(n0 == 1){
         puts((string(n2-2, '2')+"022").data());
         puts(("220"+string(n2-2, '2')).data());
      }else{
         puts((string(n2-1, '2')+"002"+string(n0-2, '0')).data());
         puts((string(n0-1, '0')+"220"+string(n2-2, '2')).data());
      }
   }else{
      if(n2<11 || n0<10){
         puts("-1");
         return 0;
      }
      n0 -= 10; n2 -= 11;
      if(n2 == 0){
         if(n0 == 0){
            puts("-1");
         }else if(n0 == 1){
            puts("0" KISEKI"02");
            puts(KISEKI"020");
         }else{
            puts((KISEKI"0002"+string(n0-2, '0')).data());
            puts((string(n0-1, '0')+KISEKI"020").data());
         }
      }else{
         if(n0 == 0){
            puts((string(n2-1, '2')+"022" KISEKI).data());
         }else if(n0 == 1){
            puts((string(n2, '2')+"0" KISEKI"02").data());
         }else{
            puts((string(n2, '2')+KISEKI"0002"+string(n0-2, '0')).data());
         }
         puts((string(n0, '0')+KISEKI"220"+string(n2-1, '2')).data());
      }
   }
}
