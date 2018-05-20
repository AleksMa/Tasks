#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#define LENGTH 1000001

typedef struct Elem {
    struct Elem *next;
    char *word;
}Elem;


int ListLength(Elem *L){
    int len = 0;
    struct Elem *X = L;
    while(X!=NULL){
        len++;
        X = X->next;
    }
    return len;
}

int ListEmpty(struct Elem *L){
    return L->next==NULL?1:0;
}

void InsertBeforeL(Elem **L, char *data){
    int len = strlen(data)+1;
    char *word = malloc(len);
    for(int i = 0;i<len; i++)
        word[i] = data[i];
    Elem *tmp = (Elem*) malloc(sizeof(Elem));
    tmp->word = word;
    tmp->next = (*L);
    //printf("kek\n");
    (*L) = tmp;
}

Elem* GetLast(Elem *L) {
    if (L == NULL) {
        return NULL;
    }
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

void InitSingleLinkedList(Elem **L)
{
    (*L) = NULL;
}


char *DeleteL(Elem **L) {
    Elem* prev = NULL;
    prev = (*L);
    int len = strlen(prev->word)+1;
    char *word = malloc(len);
    for(int i = 0;i<len; i++)
        word[i] = prev->word[i];
    (*L) = (*L)->next;
    free(prev->word);
    free(prev);
    //printf("%s ", word);
    return word;
}


int ListBubble(Elem *l)
{
    Elem * n;
    int change = 0;
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
    return change;
}
char *ListBSort(Elem *l)
{
    while(ListBubble(l));
}

int main(){
    //Elem MainList;
    Elem *L;
    InitSingleLinkedList(&L);
    char *S = (char*)malloc(LENGTH*sizeof(char));
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
                if(!M)InsertBeforeL(&L, C);
                else InsertToTail(L, C);
                int j = 0;
                while(C[j]!=0)C[j++]=0;
                K=0;
                M++;
            }
        }
        i++;
    }
    ListBSort(L);
    for(int i=0; i<M; i++){
        char *ans = DeleteL(&L);
        printf("%s ", ans);
        free(ans);
    }
    free(S);
    return 0;
}
