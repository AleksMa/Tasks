#include <stdio.h>

int main(){
    int n = 8;
    int a[n], b[n];
    for (int i=0; i<n; i++) scanf("%d", &a[i]);
    for (int i=0; i<n; i++) scanf("%d", &b[i]);

    for (int i=0; i<n; i++){
        int boo = 1, j = 0;
        while(boo && j<n){
            if(a[i]==b[j]){
                a[i]=b[j]=-1;
                boo=0;
            }
            j++;
        }
        if(boo){
            printf("no");
            return 0;
        }
    }
    printf("yes");
    return 0;

}
