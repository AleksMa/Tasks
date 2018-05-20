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

void Union(int *base, int x, int n){
    for(int i = 0; i<n; i++)
        if(base[i]==0)base[i]=x;
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
        //printf("%d\n", sum);
        if(Power2(sum))return 1;
        return 0;
    }

    for(int i = start; i<n; i++){
        //printf("lol\n");
        if(n<m)return 0;

        Diff(q, i, n);
        kol+=Comb(q, m-1, sum+base[i], n-1, i);
    }
    return kol;
}

/*int Comb(int *base, int m, int *c, int qn, int cn){
    int supersum = 0;
    if(m==0){
        int sum = 0;
        for(int i = 0; i<cn; i++)sum+=c[i];
        return sum;
    }
    for(int i = 0; i<qn; i++){
        if(qn<m)return 0;
        int *q = base, *cq = c;
        Union(cq, q[i], cn);
        Diff(q, i, qn);
        Comb(q, m-1, Union(c, ))
    }

}*/

int main(){
    int n = 0;
    scanf("%d", &n);
    int array[n];
    for(int i = 0; i<n; i++)scanf("%d", &array[i]);
    //Diff(array, 2, n);
    //for(int i = 0; i<n; i++)printf("%d ", array[i]);
    printf("%d", KolComb(array, n));
    //printf("%d", Comb(array, 1, 0, n, 0));
}
