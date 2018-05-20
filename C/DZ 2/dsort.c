#include <stdlib.h>
#include <stdio.h>

char *dsort(char *str){
    int a = 97;
    int N = strlen(str), M = 26, j = 0, i = 1;
    int *count = (int*)malloc(M*sizeof(int));
    for(int k=0; k<M; k++)count[k]=0;
    while(j<N){
        int k = str[j]-a;
        count[k]++;
        j++;
    }
    printf("%d\n", N);
    while(i<M){
        count[i]+=count[i-1];
        i++;
    }
    char *D = (char*)malloc(N*sizeof(char));
    D[0]=0;
    j = N - 1;
    while(j>=0){
        int k = str[j]-a;
        i = --count[k];
        D[i]=str[j];
        j--;
    }
    free(count);
    return D;
}

int main(){

    int N = 1000001;
    char *str = (char*)malloc(N*sizeof(char));
    str[0]=0;
    gets(str);
    int K = strlen(str);
    char *sort = dsort(str);
    for(int i =0; i<K; i++)printf("%c", sort[i]);
    free(str);
    free(sort);
    return 0;
}
