#include <stdio.h>
#include <stdlib.h>
#include <string.h>

unsigned long fib(int n)
{
    if (n < 3)
        return 1;
    else
        return (fib(n - 1) + fib(n - 2));
}

char* fibstr(int n)
{
    unsigned long fib(int n)
    {
        if (n < 3)
            return 1;
        else
            return (fib(n - 1) + fib(n - 2));
    }
    unsigned long N = fib(n);
    //char *str = (char*)malloc(N*sizeof(char));
    char* fibab(int n)
    {
        char* s = (char*)malloc((fib(n) + 1) * sizeof(char));
        s[0] = 0;
        if (n == 1)
            s[0] = 'a';
        else if (n == 2)
            s[0] = 'b';
        else {
            char* s1 = fibab(n - 2);
            char* s2 = fibab(n - 1);
            *strncat(s, s1, fib(n - 2));
            *strncat(s, s2, fib(n - 1));
            free(s1);
            free(s2);
        }
        return s;
    }
    char* str = fibab(n);
    return str;
}

int main()
{
    int n = 0;
    scanf("%d", &n);
    char* str = fibstr(n);
    for (int i = 0; i < fib(n); i++)
        printf("%c", str[i]);
    free(str);
}

