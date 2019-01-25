#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>

int m = 10;

typedef struct Elem{
    struct Elem *next;
    int k, v;
}Elem;

Elem *InitSingleLinkedList(){
    return NULL;
}

int ListEmpty(Elem *L){
    return L==NULL?1:0;
}

int ListLength(Elem *L){
    int len = 0;
    Elem *X = L;
    while(X!=NULL){
        len++;
        X=X->next;
    }
    return len;
}

Elem *ListSearch(Elem *L, int k){
    Elem *X = L;
    while(X!=NULL && X->k != k){
        X =X->next;
    }
    return X;
}

void InsertAfter(Elem *X, Elem *Y){
    Elem *Z = X->next;
    X->next = Y;
    Y->next = Z;
}

Elem *InsertBeforeHead(Elem *L, Elem *Y){
    Y->next = L;
    L = Y;
    return L;
}

void DeleteAfter(Elem *X){
    Elem *Y = X->next;
    X->next = Y->next;
    Y->next = NULL;
    //free(Y);
}

Elem *DeleteHead(Elem *L){
    Elem *Y = L;
    L = Y->next;
    Y->next = NULL;
    return L;
}

Elem *SearchAndDelete(Elem *L, int k){
    Elem *Y = NULL, *X = L;
    while(X!=NULL){
        if(X->k == k){
            if(Y == NULL)
                L = DeleteHead(L);
            else
                DeleteAfter(Y);
            return L;
        }
        Y = X;
        X =X->next;
    }
    return L;
}

int h(k){
    return k%m;
}

void PrintList(Elem *L){
    Elem *X = L;
    while(X!=NULL){
        printf("%d_%d ", X->k, X->v);
        X = X->next;
    }
}

void DeleteList(Elem *L){
    Elem *X = L;
    while(X!=NULL){
        Elem *Temp = X;
        X = Temp->next;
        free(Temp);
    }
}

Elem **InitHashTable(int m){
    Elem **T = malloc(m*sizeof(Elem*));
    for(int i = 0; i<m; i++)
        T[i] = InitSingleLinkedList();
    return T;
}

int MapEmpty(Elem **T){
    int i = 0;
    while(i<m){
        if(!ListEmpty(T[i++]))
            return 0;
    }
    return 1;
}

int Lookup(Elem **T, int k){
    Elem *P = ListSearch(T[h(k)], k);
    if(P == NULL)
        return 0;
    return P->v;
}

void Insert(Elem **T, int k, int v){
    int i = h(k);
    Elem *X = malloc(sizeof(Elem));
    X->k = k;
    X->v = v;
    T[i] = InsertBeforeHead(T[i], X);
}

void Delete(Elem **T, int k){
    int i = h(k);
    T[i] = SearchAndDelete(T[i], k);
}

void DeleteEverything(Elem **T){
    for(int i = 0; i<m; i++)
        DeleteList(T[i]);
}


int main(){
    int N, K, V;
    char command[6];
    scanf("%d", &N);
    scanf("%d", &m);
    Elem **T = InitHashTable(m);
    for(int i=0; i<N; i++){
        scanf("%s", &command);
        switch(command[1]){
        case 'S':
            scanf("%d%d", &K, &V);
            Insert(T, K, V);
            break;
        case 'T':
            scanf("%d", &K);
            int ans = Lookup(T, K);
            printf("%d\n", ans);
            break;
        }
    }
    DeleteEverything(T);
    free(T);
}


















