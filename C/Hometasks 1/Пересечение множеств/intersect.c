#include <stdio.h>

main()
{

    long A = 0, B = 0, nA = 0, nB = 0, Inter = 0, temp = 0;

    scanf("%ld\n", &nA);

    for (int i = 0; i < nA; i++) {
        scanf("%ld ", &temp);
        A = A | (1 << temp);
    }

    scanf("%ld\n", &nB);

    for (int i = 0; i < nB; i++) {
        scanf("%ld", &temp);
        B = B | (1 << temp);
    }

    Inter = A & B;
    int k = 0;
    for (int i = 0; i < 32; i++) {
        k = Inter % 2;
        if (k)
            printf("%ld ", i);
        Inter /= 2;
    }
}

