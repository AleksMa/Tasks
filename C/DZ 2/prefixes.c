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



int main(int argc, char **argv){
    int s=strlen(argv[1]);
    char *S = argv[1];
    int *pref=Prefix(S);
    int len = 0, k = 0;
    for(int i =0; i<s; i++){
        //printf("%d\n", s);
        if(pref[i]==0 || (i<s-1 && pref[i+1]==1))
            k = len = i+1;
        if(i<s-1 && pref[i+1]==pref[i] && pref[i]!=1){
            k++;
            len++;
        }

        if(pref[i]==len || pref[i]==k){
            k = i+1;
            printf("%d %d\n", k, (int)k/len);
        }
    }
    free(pref);
    return 0;
}

