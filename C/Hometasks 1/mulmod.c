#include <stdio.h>

main(){

    unsigned long a = 0, b = 0, m = 1, B = 0, S=0;
    int i=1;
    scanf("%lu %lu %lu", &a, &b, &m);
    S = ((a%m)*((b>>63)%2)%m);
    for(i=62; i>=0; i--){
        S = ((S%m)*(2%m)%m) + (((a%m)*(((b>>i)%2))%m)%m);
        printf("%lu\n", S);

    }
    S%=m;

    printf("%lu", S);



}
