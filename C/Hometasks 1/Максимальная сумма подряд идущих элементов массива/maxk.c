#include <stdio.h>

int main()
{

    int n = 0, k = 0, max = 0, max1 = 0;
    ;
    scanf("%d", &n);
    int a[n];
    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }
    scanf("%d", &k);
    for (int i = 0; i < k; i++) {
        max += a[i];
    }
    max1 = max;
    for (int i = 0; i < n - k; i++) {
        max1 = max1 - a[i] + a[i + k];
        if (max1 > max)
            max = max1;
    }
    printf("%d", max);
    return 0;
}
