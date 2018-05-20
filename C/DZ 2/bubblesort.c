#include <stdlib.h>
#include <stdio.h>

int *array;

int compare(unsigned long i, unsigned long j)
{
        if (i <= j) {
                printf("COMPARE␣%d␣%d\n", i, j);
        } else {
                printf("COMPARE␣%d␣%d\n", j, i);
        }

        if (array[i] == array[j]) return 0;
        return array[i] < array[j] ? -1 : 1;
}

void swap(unsigned long i, unsigned long j)
{
        if (i <= j) {
                printf("SWAP␣%d␣%d\n", i, j);
        } else {
                printf("SWAP␣%d␣%d\n", j, i);
        }

        int t = array[i];
        array[i] = array[j];
        array[j] = t;
}

void bubblesort(unsigned long nel,
        int (*compare)(unsigned long i, unsigned long j),
        void (*swap)(unsigned long i, unsigned long j))
{
    unsigned long t = nel - 1, s = 0;;
    while(t>0 && s<nel-1){
        unsigned long bound1 = t, bound2 = s, i=s, j=nel-1;
        t = 0;
        while(i<bound1){
            if(compare(i+1, i)==-1){
                swap(i+1, i);
                t=i;
            }
            i++;
        }
        //printf("%d %d\n", t, i);
        j=t;
        if(t==0)break;
        s = nel-1;
        while(j>bound2){
            if(compare(j, j-1)==-1){
                swap(j-1, j);
                s=j;
            }
            j--;
        }
        //printf("%d %d\n", s, j);
        //if(s==nel-1)break;
    }
}

int main(int argc, char **argv)
{
        int i, n;
        scanf("%d", &n);

        array = (int*)malloc(n * sizeof(int));
        for (i = 0; i < n; i++) scanf("%d", array+i);

        bubblesort(n, compare, swap);
        for (i = 0; i < n; i++) printf("%d␣", array[i]);
        printf("\n");

        free(array);
        return 0;
}
