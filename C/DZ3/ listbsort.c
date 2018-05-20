#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#define MAX_LENGTH 1000001

typedef struct Elem {
    struct Elem *next;
    char *word;
}Elem;

void InitSingleLinkedList(Elem **L)
{
    (*L) = NULL;
}

int ListLength(Elem *L){
    int len = 0;
    struct Elem *X = L;
    while(X!=NULL){
        len++;
        X = X->next;
    }
    return len;
}

int ListEmpty(Elem *L){
    return L->next==NULL?1:0;
}

void InsertHead(Elem **L, char *data){
    int len = strlen(data)+1;
    char *word = malloc(len);
    for(int i = 0;i<len; i++)
        word[i] = data[i];
    Elem *tmp = (Elem*) malloc(sizeof(Elem));
    tmp->word = word;
    tmp->next = (*L);
    (*L) = tmp;
}

Elem* GetLast(Elem *L) {
    while (L->next) {
        L = L->next;
    }
    return L;
}

void InsertToTail(Elem *L, char *data) {
    int len = strlen(data)+1;
    char *word = malloc(len);
    for(int i = 0;i<len; i++)
        word[i] = data[i];
    Elem *last = GetLast(L);
    Elem *tmp = (Elem*) malloc(sizeof(Elem));
    tmp->word = word;
    tmp->next = NULL;
    last->next = tmp;
}


char *Delete(Elem **L) {
    Elem* prev = NULL;
    prev = (*L);
    int len = strlen(prev->word)+1;
    char *word = malloc(len);
    for(int i = 0;i<len; i++)
        word[i] = prev->word[i];
    (*L) = (*L)->next;
    free(prev->word);
    free(prev);
    return word;
}

Elem *bsort(Elem *L)
{
    int change = 0;
    do{
        Elem *l = L, *n;
        change = 0;
        while(n = l->next){
            if(strlen(n->word) < strlen(l->word)){
                char *w;
                w = l->word;
                l->word = n->word;
                n->word = w;
                change++;
            }
            l = n;
        }
    }while(change);
    return L;
}


int main(){
    Elem *L;
    InitSingleLinkedList(&L);
    char *S = (char*)malloc(MAX_LENGTH*sizeof(char));
    char C[1000]="";
    int K = 0, i = 0, M=0;
    gets(S);
    while(S[i]!=0){
        if(S[i]!=' '){
            C[K]=S[i];
            K++;
        }
        if(S[i]==' ' || S[i+1]==0){
            if(K>0){
                if(!M)InsertHead(&L, C);
                else InsertToTail(L, C);
                int j = 0;
                while(C[j]!=0)C[j++]=0;
                K=0;
                M++;
            }
        }
        i++;
    }
    L = bsort(L);
    while(ListLength(L)){
        char *answer = Delete(&L);
        printf("%s ", answer);
        free(answer);
    }
    free(S);
    return 0;
}
