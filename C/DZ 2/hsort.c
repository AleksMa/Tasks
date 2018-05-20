#include <stdio.h>
#include <string.h>

int compare(const void *a, const void *b){
    char *A = (char*)a, *B = (char*)b;
    int lenA = strlen(A), lenB = strlen(B), kolA = 0, kolB = 0;
    for(int i = 0; i<lenA; i++)if(A[i]=='a')kolA++;
    for(int i = 0; i<lenB; i++)if(B[i]=='a')kolB++;
    return kolA-kolB;
}
void swap(int i, int j, void *base, size_t width){
    char *p = base;
    for(int k = 0; k < width; k++)
    {
        char t = p[width*i+k];
        p[width*i+k] = p[width*j+k];
        p[width*j+k] = t;
    }
}

void hsort(void *base, size_t nel, size_t width,
        int (*compare)(const void *a, const void *b))
{
    void Heapify(int i, int n, void *base){
        int j = i;
        int k = 0;
        while(1){
            int l = 2*i +1;
            int r = l+1;
            j = i;
            if(l<n && compare(base+i*width, base+l*width) < 0) i = l;
            if(r<n && compare(base+i*width, base+r*width) < 0) i = r;
            if(i==j)break;
            swap(i, j, base, width);
        }
    }
    void BuildHeap(int n, void *base){
        int i = n/2 - 1;
        while(i>=0){
            Heapify(i, n, base);
            i--;
        }
    }
    BuildHeap(nel, base);
    int i = nel-1;
    while(i>0){
        swap(0, i, base, width);
        Heapify(0, i, base);
        i--;
    }
}

int main(){
    int n = 0;
    scanf("%d\n", &n);
    char s[n][100];
    for(int i=0; i<n; i++){
        gets(s[i]);
    }
    hsort(s, n, sizeof s[0], compare);
    for(int i=0; i<n; i++){
        int K = strlen(s[i]);
        for(int j=0; j<K;j++)printf("%c", s[i][j]);
        printf("\n");
    }
}
