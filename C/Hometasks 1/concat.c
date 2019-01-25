#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char *concat(char **s, int n)
{
    int charnumber = 1; //+ 1 элемент для 0
    for(int i = 0; i<n; i++){
        int j = 0;
        while (s[i][j]!=0) {
            charnumber++;
            j++;
        }
    }
    char *str = (char*)malloc(charnumber*sizeof(char));
    str[0]=0;
    for(int i = 0; i<n; i++){
        *strcat(str, s[i]);
    }
    return str;
}

int main(){
    int n = 0;
    scanf("%d\n", &n);
    char s[n][100];

    for(int i=0; i<n; i++){
        gets(s[i]);
    }

    char *myfirst[n];
    for(int i = 0; i< n; i++) myfirst[i]=&s[i];
    char **mystr = &myfirst;

    char *str = concat(mystr, n);
    int i=0;
    for(int i = 0; i<strlen(str); i++) printf("%c", str[i]);
    free(str);
}
