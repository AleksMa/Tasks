#include <stdio.h>

int compare(int i, int j, int* array)
{
    return array[i] - array[j];
}

void swap(int i, int j, int* array)
{
    int t = array[i];
    array[i] = array[j];
    array[j] = t;
}

void SelectSort(int low, int high, int* array)
{
    int j = high;
    while (j > low) {
        int k = j, i = j - 1;
        while (i >= low) {
            if (compare(k, i, array) < 0)
                k = i;
            i--;
        }
        swap(j, k, array);
        j--;
    }
}

int Partition(int low, int high, int* array)
{
    int i = low, j = low;
    while (j < high) {
        if (compare(j, high, array) < 0) {
            swap(i, j, array);
            i++;
        }
        j++;
    }
    swap(i, high, array);
    return i;
}

void QuickSort(int low, int high, int* array, int m)
{
    int q = 0;
    while (high - low >= m - 1) {
        q = Partition(low, high, array);
        if (q - low <= high - q) {
            QuickSort(low, q - 1, array, m);
            low = q + 1;
        }
        else {
            QuickSort(q + 1, high, array, m);
            high = q - 1;
        }
    }
    SelectSort(low, high, array);
}

int main()
{
    int n = 0, m = 0;
    scanf("%d%d", &n, &m);
    int array[n];
    for (int i = 0; i < n; i++)
        scanf("%d", &array[i]);
    QuickSort(0, n - 1, array, m);
    for (int i = 0; i < n; i++)
        printf("%d ", array[i]);
}
