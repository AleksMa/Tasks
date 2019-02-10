#include <stdio.h>

int wcount(char* s)
{
    unsigned long N = 0;
    int i = 0;
    while (s[i] != 0) {
        if ((i == 0 || s[i - 1] == ' ') && s[i] != ' ')
            N++;
        i++;
    }
    return N;
}

int main()
{
    char s[1000] = { 0 };
    gets(s);
    unsigned long N = wcount(s);
    printf("%lu", N);
    return 0;
}

