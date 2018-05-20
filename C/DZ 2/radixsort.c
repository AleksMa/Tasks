#include <stdio.h>

union Int32 {
    int x;
    unsigned char bytes[4];
};

void DistributionSort(int m, union Int32 *base, int n, int index){
    //printf("lol\n");
    int j = 0, i = 1;
    int count[m];
    for(int k=0; k<m; k++)count[k]=0;
    while(j<n){
        int k = base[j].bytes[index];
        //printf("%d\n", k);
        if(index<3)count[k]++;
        else count[(k+128)%256]++;
        //count[k]++;
        j++;
    }
    //printf("%d ", count[])
    while(i<m){
        count[i]+=count[i-1];
        i++;
    }
    //printf("ahah\n");
    union Int32 D[n];
    j = n - 1;
    //for(i = 0; i<m; i++)printf("%d ", count[i]);
    while(j>=0){
        int k = base[j].bytes[index];
        //i = --count[k];
        if(index<3)i = --count[k];
        else i = --count[(k+128)%256];
        D[i]=base[j];
        j--;
        //printf("\nkek\n");
    }
    //printf("\n");
    for(int i = 0; i<n; i++)base[i] = D[i];
    //free(D);
    //return D;
}

void RadixSort(int m, union Int32 *base, int n){

    int i = 0;
    int q = 4;
    while(i<q){
        DistributionSort(m, base, n, i);
        i++;
    }
}


int main(){
    int n = 0;
    scanf("%d", &n);
    union Int32 array[n];
    for(int i = 0; i<n; i++)scanf("%d", &array[i].x);
    /*for(int i = 0; i<n; i++){
        for(int j = 0; j<4; j++)
            printf("%d ", array[i].bytes[j]);
        printf("\n");
    }*/
    RadixSort(256, array, n);
    for(int i = 0; i<n; i++)printf("%d ", array[i].x);
    //for(int i = 0; i<n; i++){
    //    for(int j = 0; j<4; j++)
    //        printf("%d ", array[i].bytes[j]);
    //    printf("\n");
    //}

}
