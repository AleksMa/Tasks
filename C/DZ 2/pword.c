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

int PWord(char *str, int lenS){
    int lenSTR = strlen(str);
    int *pref = Prefix(str);
    for(int i = lenSTR-1; i>=lenS; i--){
        if(pref[i]==0){
                free(pref);
                return 0;
        }
    }
    free(pref);
    //
    return 1;
}



int main(int argc, char **argv){
    int s=strlen(argv[1]), t = strlen(argv[2]);
    char *S = argv[1], *T = argv[2];
    char *ST[s+t];
    ST[0]=0;
    *strncat(ST, S, s);
    *strncat(ST, T, t);
    //*strncat(S, T, t);
    int ans = PWord(ST, s);
    if(ans)printf("yes");
    else printf("no");
    //free(ST);
    return 0;
}

