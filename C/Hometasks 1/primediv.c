#include <stdio.h>
#include <math.h>

int main(){

    int x = 0;
    scanf("%d", &x);
    int mprime = x = abs(x);
    int sq = sqrt(abs(x))+3; // +3 вследствие того, что индексы массива простых чисел для удобства будут начинаться с 2, а не с 0
    char *sieve = (char*)malloc(sq*sizeof(char)); //так как sqrt(2^31) < 2^24 - максимальный размер памяти в байтах,
                                                  // подобный массив не превысит ограничение
    for(int i = 2; i<sq; i++) sieve[i]=0;
    for(int i = 2; i<sq; i++){
        if(sieve[i]==0){
            if(x%i == 0) mprime = i;
            for(int j = i; j<sq; j+=i) {
                sieve[j]=1;
                if(x%i == 0) x/=i;
            }
        }
    }
    free(sieve);
    if(x>sq)mprime=x;
    printf("%d", mprime);
}
