#include <stdio.h>

main(){
    long P = 0, n = 0, an = 0, x = 0, f = 0;
    scanf("%ld %ld %ld", &n, &x, &an);
    P = an;
    f = an * n;
    for(int i = 1; i <= n; i++){
        scanf("%ld", &an);
        P = P*x + an;
        if(i == n) continue;
        f = f * x + an * (n - i);
    }
    printf("%ld %ld", P, f);
    return 0;
}

