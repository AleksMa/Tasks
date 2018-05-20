#include <stdio.h>
#include <string.h>
#define SIZE 4

int main(int argc, char **argv){


    if(argc!=SIZE){
        printf("Usage: frame <height> <width> <text>\n");
        return 0;
    }
    int m=atoi(argv[1]), n=atoi(argv[2]);
    int k=strlen(argv[3]);
    char str[k];
    for(int i = 0; i<k; i++){
        str[i]=argv[3][i];
    }
    if(k>n-2 || m<3){
        printf("Error\n");
        return 0;
    }

    int W, O, N, S;
    W=(n-k-2)/2;
    O=n-k-2-W;
    N=(m-1-2)/2;
    S=m-1-2-N;
    /*printf("%d %d %d %d %d\n", k, W, O, N, S);
    for(int i = 0; i<k; i++) printf("%c", str[i]);
    printf("\n");*/

    for(int i=0; i<m; i++){
        printf("*");
        for(int j=1; j<n-1; j++){
            if(i==0 || i==m-1) printf("*");
            else if(i==N+1){
                if(j<=W) printf(" ");
                else if(j>W && j<k+W+1)printf("%c", str[j-W-1]);
                else printf(" ");
            }
            else printf(" ");
        }
        printf("*\n");
    }

    return 0;
}
