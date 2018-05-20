#include <stdio.h>
int main(){

    int m=0, n=0;
    scanf("%d%d", &m, &n);
    int a[m][n];
    int max[m], min[n];
    for(int i = 0; i<m; i++){
        for(int j = 0; j<n; j++){
            scanf("%d", &a[i][j]);
            max[i] = 0;
            min[j] = 0;
        }
    }
    for(int i = 0; i<m; i++){
        for(int j = 0; j<n; j++){
            if(a[i][j] > a[i][max[i]]) max[i] = j;
            if(a[i][j] < a[min[j]][j]) min[j] = i;
        }
    }

    for(int i = 0; i < m; i++){
        if(min[max[i]]==i) {
            printf("%d %d", i, max[i]);
            return 0;
        }
    }
    printf("none");
    return 0;

}
