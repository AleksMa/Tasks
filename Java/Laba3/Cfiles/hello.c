#include <stdio.h>

main(){

    long F(int f){
        if(f<=3) return f;
        else return (F(f-1)+F(f-2));
    }

    int Get(int k){
        int j=1;
        while(F(j) < k) j++;
        if(F(j)>k) return j-1;
        else return j;
    }

    long x = 0, Inter = 0;
    unsigned long Sum = 0, Max = 0;
    scanf("%ld", &x);
    long X = x;
    Max = Get(x)-1;
    while(x>0){
        Inter = Get(x);
        Sum+=pow(2, Inter-1);
        x-=F(Inter);
    }
    if(X==0)printf("0");
    for(long i=Max; i>=0; i--){
        printf("%ld", ((Sum>>i)%2));
    }


}
