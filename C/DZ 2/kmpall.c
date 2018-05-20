#include <stdio.h>
#include <string.h>
#include <stdlib.h>


int *Prefix(char *S){
    int len = strlen(S);
    int *pref = (int*)malloc(len*sizeof(int));
    int t = 0, i = 1;
    pref[0]=0;
    while(i<len){
        while(t>0 && S[t]!=S[i])
            t = pref[t-1];
        if(S[t]==S[i])
            t++;
        pref[i]=t;
        i++;
    }
    return pref;
}

int *KMPall(char *S, char *T){
    int *pref=Prefix(S);
    int q = 0, k = 0;
    int lenT=strlen(T), lenS=strlen(S);
    int *count = (int*)malloc((lenT+1)*sizeof(int));
    for(int i = 0; i<=lenT; i++)count[i]=0;
    int j = 0;
    while(k<lenT){
        while(q>0 && S[q]!=T[k])
            q = pref[q-1];
        if(S[q]==T[k])q++;
        if(q==lenS){
            count[j]=k-lenS+1;
            j++;
        }
        k++;
    }
    free(pref);
    return count;
}



int main(int argc, char **argv){
    int s=strlen(argv[1]), t = strlen(argv[2]);
    char *S = argv[1], *T = argv[2];
    int *count = KMPall(S, T);
    int i = 0;
    while(i==0 || count[i]!=0){
    //while(i<t && count[i]!=0){
        printf("%d ", count[i]);
        i++;
    }
    free(count);
    return 0;
}
