#include <stdio.h>
#include <math.h>

int compare(int i, int j, int *array)
{
        //if (array[i] == array[j]) return 0;
        return array[i] - array[j];
}

void swap(int i, int j, int *array)
{
        int t = array[i];
        array[i] = array[j];
        array[j] = t;
}




void SelectSort(int low, int high, int *array){
    int j = high;
    while(j>low){
        int k = j, i = j-1;
        while(i>=low){
            if(compare(k, i, array)<0)k=i;
            i--;
        }
        swap(j, k, array);
        j--;
    }
}

int Partition(int low, int high, int *array){
    int i = low, j = low;
    while(j<high){
        if(compare(j, high, array)<0){
            swap(i, j, array);
            i++;
        }
        j++;
    }
    swap(i, high, array);
    return i;
}

void QuickSort(int low, int high, int *array, int m){
    int q = 0;
    while(high-low>=m-1){
        q = Partition(low, high, array);
        if(q-low<=high-q){
            QuickSort(low, q-1, array, m);
            low = q+1;
        }
        else {
            QuickSort(q+1, high, array, m);
            high=q-1;
        }
    }
    SelectSort(low, high, array);
}

int main(){
    int n=0, m=0;
    scanf("%d%d", &n, &m);
    int array[m];
    for(int i=0; i<n; i++)scanf("%d", &array[i]);
    //swap(0, 1, array);
    //SelectSort(0, n-1, array);
    QuickSort(0, n-1, array, m);
    for(int i=0; i<n; i++)printf("%d ", array[i]);
}

void QuickSort2(int low, int high, int *array, int m){
    int q = 0;
    if(high-low<m-1)SelectSort(low, high, array);
    else{
        q = Partition(low, high, array);
        QuickSort(low, q-1, array, m);
        QuickSort(q+1, high, array, m);
    }
}

void SelectSort2(int n, int *array){
    int j = n-1;
    while(j>0){
        int k = j, i = j-1;
        while(i>=0){
            if(compare(k, i, array)<0)k=i;
            i--;
        }
        swap(j, k, array);
        j--;
    }
}


