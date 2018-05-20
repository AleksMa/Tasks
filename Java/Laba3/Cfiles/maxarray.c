#include <stdio.h>

unsigned int  array[4]={1, 2, 3, 4};
               // источник
    int A[1] = {-1};

    //2147483647

int main(){

    char *p = A;

    unsigned char byte_array[4];  // буфер назначения
    for(int i = 0; i<4; i++)byte_array[i]=0;
    memcpy(byte_array, p, 4);

    for(int i = 0; i<4; i++)printf("%d\n", byte_array[i]);
    return 0;
}

