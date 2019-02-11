#include <stdio.h>
#include <string.h>

void csort(char* src, char* dest)
{
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
    int N = wcount(src), len = strlen(src);
    ;
    int* count = (int*)malloc(N * sizeof(int));
    int* wordlen = (int*)malloc(N * sizeof(int));
    for (int i = 0; i < N; i++)
        count[i] = wordlen[i] = 0;
    int k = 0;
    for (int i = 0; i < len; i++) {
        if (src[i] == ' ' && i != 0 && src[i - 1] != ' ') {
            k++;
            continue;
        }
        if (src[i] != ' ')
            wordlen[k]++;
    }
    int j = 0;
    while (j < N - 1) {
        int i = j + 1;
        while (i < N) {
            if (wordlen[i] < wordlen[j])
                count[j] += wordlen[i] + 1;
            else
                count[i] += wordlen[j] + 1;
            i++;
        }
        j++;
    }
    k = 0;
    int s = 0;
    for (int i = 0; i < len; i++) {
        if (src[i] == ' ' && i != 0 && src[i - 1] != ' ') {
            k++;
            s = 0;
            continue;
        }
        if (src[i] != ' ') {
            dest[s + count[k]] = src[i];
            s++;
        }
    }
    free(count);
    free(wordlen);
}

int main()
{
    char src[9999] = "";
    gets(src);
    unsigned long N = 0, len = strlen(src);
    for (int i = 1; i < len; i++) {
        if (src[i - 1] == ' ' && src[i] == ' ')
            continue;
        N++;
    }
    if (src[0] != ' ')
        N++;
    char* dest = (char*)malloc(N * sizeof(char));
    for (int i = 0; i < N; i++)
        dest[i] = ' ';
    csort(src, dest);
    for (int i = 0; i < N; i++)
        printf("%c", dest[i]);
    free(dest);
    return 0;
}

