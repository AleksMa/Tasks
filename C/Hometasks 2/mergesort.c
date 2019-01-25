#include <stdio.h>
#include <math.h>

void Merge(int k, int l, int m, int *array)
{
    int *T = (int*)malloc((m-k+1)*sizeof(int));
    int i = k;
    int j = l+1;
    int h = 0;
    while(h<m-k+1){
        if(j<=m && (i==l+1 || abs(array[j]) < abs(array[i]))){
            T[h]=array[j];
            j++;
        }
        else{
            T[h]=array[i];
            i++;
        }
        h++;
    }
    int t = 0;
    for(int i = k; i<=m; i++){
        if(t >= h)break;
        array[i]=T[t];
        t++;
    }
    free(T);
}

//void MergeSort(int n, int *array){
//    MergeSortRec(0, n-1, array);
//}

void MergeSortRec(int low, int high, int *array){

    if(low<high){
        int med = (low+high)/2;
        if(high-low+1<5){
            //printf("is %d %d\n", low, high);
            InsertSort(low, high, array);
            //for(int i = low; i<=high; i++)printf("%d ", array[i]);
        }
        else{
            //printf("ms %d %d\n", low, high);
            MergeSortRec(low, med, array);
            MergeSortRec(med+1, high, array);
            Merge(low, med, high, array);
        }
        //Merge(low, med, high, array);
    }

}

void InsertSort(int l, int h, int *array){
    int i = l+1;
    while(i<=h){
        int elem = array[i];
        int loc = i - 1;
        while(loc>= l && abs(array[loc])>abs(elem)){
            array[loc+1]=array[loc];
            loc--;
        }
        array[loc+1]=elem;
        i++;
    }
}


int main()
{
	int N = 0;
    scanf("%d", &N);
    int *array = (int*)malloc(N*sizeof(int));
    for (int i = 0; i < N; i++) scanf("%d", &array[i]);

	MergeSortRec(0, N-1, array);
    //printf("\n");
    for (int i = 0; i < N; i++) printf("%d ", array[i]);
    //printf("\n");
    free(array);
    return 0;
}
