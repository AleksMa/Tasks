#include <stdio.h>

int Power2(int x){
    if(!x)return 0;
    while((x%2==0 || x==1) && x>0)x/=2;
    if(x)return 0;
    return 1;
}

void Diff(int *base, int i, int n){
    int k = 0;
    for(int j = 0; j<n-1; j++){
        if(i==j){
            base[j]=base[++k];
        }
        else base[j]=base[k];
        k++;
    }
    base[n-1]=0;
}


int KolComb(int *base, int n){
    int kol = 0;
    for(int m = 1; m<=n; m++)
        kol+=Comb(base, m, 0, n, 0);
    return kol;
}

int Comb(int *base, int m, int sum, int n, int start){
    int kol = 0;
    if(m==0){
        printf("sum%d\n", sum);
        return Power2(sum);

    }
    /*if(n-start==m){
        for(int j = start; j<n; j++)kol+=base[j];
        printf("kol%d\n", kol);
        return Power2(kol);
    }*/
    int q[n];
    for(int j = 0; j<n; j++)q[j]=base[j];
    for(int i = start; i<n; n--){
        if(n<m)break;
        //int q[n];
        //for(int j = 0; j<n; j++)q[j]=base[j];
        for(int j=0; j<n; j++)printf("%d ", q[j]);
        printf("\n");
        Diff(q, 0, n);
        for(int j=0; j<n; j++)printf("%d ", q[j]);
        printf("\n");
        //kol+=Comb(q, m-1, sum+base[i], n-1, i);
        kol+=Comb(q, m-1, sum+q[0], n-1, 0);
    }
    return kol;
}

int main(){
    int n = 0;
    scanf("%d", &n);
    int array[n];
    for(int i = 0; i<n; i++)scanf("%d", &array[i]);
    printf("%d", KolComb(array, n));
}
