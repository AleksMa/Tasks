#include <stdio.h>

main(){

    /*long F(int f){
        if(f<=3) return f;
        else return (F(f-1)+F(f-2));
    }*/

    unsigned long Max = 1, x = 0, FibB = 1, FibS = 1;


    scanf("%lu", &x);
    unsigned long X = x;



    while(FibB < x) {
        Max++;
        unsigned long c = FibB;
        FibB += FibS;
        FibS = c;
    }
    if(FibB > x){
        Max--;
        unsigned long c = FibS;
        FibS = FibB - FibS;
        FibB = c;
    }


    //Max = GetNumber(x);
    //FibB = F(Max);
    //FibS = F(Max-1);
    for(; Max > 0; Max--){
        if(FibB <= x){
            printf("1");
            x -= FibB;
        }
        else printf("0");
        unsigned long c = FibS;
        FibS = FibB - FibS;
        FibB = c;
    }
    if(X == 0) 
	printf("0");

}
