#include <stdlib.h>
#include <stdio.h>

int *array;

int compare(unsigned long i, unsigned long j)
{
        if (i <= j) {
                printf("COMPARE␣%d␣%d\n", i, j);
        } else {
                printf("COMPARE␣%d␣%d\n", i, j);
        }

        if (array[i] == array[j]) return 0;
        return array[i] < array[j] ? -1 : 1;
}

void swap(unsigned long i, unsigned long j)
{
        if (i <= j) {
                printf("SWAP␣%d␣%d\n", i, j);
        } else {
                printf("SWAP␣%d␣%d\n", i, j);
        }

        int t = array[i];
        array[i] = array[j];
        array[j] = t;
}

void shellsort(unsigned long nel,
        int (*compare)(unsigned long i, unsigned long j),
        void (*swap)(unsigned long i, unsigned long j)){

    unsigned long FibB = 1, FibS = 1;
    while(FibB<nel){
        unsigned long c = FibB;
        FibB +=FibS;
        FibS = c;
    }
    unsigned long d = FibS;
    //printf("%d\n", d);
    while(d>0){
        unsigned long i = d;
        while(i < nel){
            long loc = i - d;
            while((loc>=0) && (compare(loc, loc+d)==1)){
                swap(loc, loc+d);
                loc-=d;
            }
            i+=1;
        }
        if(d==1) break;
        FibS=FibB-FibS;
        FibB=d;
        d = FibS;
    }


}

int main(int argc, char **argv)
{
        int i, n;
        scanf("%d", &n);

        array = (int*)malloc(n * sizeof(int));
        for (i = 0; i < n; i++) scanf("%d", array+i);

        shellsort(n, compare, swap);
        for (i = 0; i < n; i++) printf("%d␣", array[i]);
        printf("\n");

        free(array);
        return 0;
}
