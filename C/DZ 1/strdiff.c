#include <stdio.h>

int strdiff(char *a, char *b){

    unsigned long ka = strlen(a)*sizeof(char)*8, kb =  strlen(b)*sizeof(char)*8;
    unsigned long max = ka>=kb?ka:kb;
    int A[max];
    int B[max];
    for(int i = 0; i<max; i++) A[i]=B[i]=0;
    for(int i = 0; i < strlen(a); i++){
        for(int j = 0; j<sizeof(char)*8; j++) A[8*i+j]=(a[i]>>j)%2;
    }
    for(int i = 0; i < strlen(b); i++){
        for(int j = 0; j<sizeof(char)*8; j++) B[8*i+j]=(b[i]>>j)%2;
    }
    int diff = 0;
    int i;
    for(i = 0; i<max; i++){
        if(A[i]==B[i])diff++;
        else break;
    }
    for(int j = 0; j< max; j++ )printf("%d", A[j]);
    printf("\n");
    for(int j = 0; j< max; j++ )printf("%d", B[j]);
    if(ka==kb && ka==diff)diff=-1;
    return diff;
}

int main(int argc, char **argv)
{
        char s1[1000], s2[1000];
        gets(s1);
        gets(s2);
        printf("\n%d\n", strdiff(s1, s2));

        return 0;
}
