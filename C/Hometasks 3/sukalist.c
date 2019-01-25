#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

typedef struct Elem {
    struct Elem *next;
    int v;
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

void InsertBeforeHead(Elem **head, int data) {
    Elem *tmp = (Elem*) malloc(sizeof(Elem));
    tmp->v = data;
    tmp->next = (*head);
    (*head) = tmp;
}

void InitSingleLinkedList(Elem *L)
{
    L = NULL;
}


int DeleteHead(Elem **head) {
    Elem* prev = NULL;
    int val;
    prev = (*head);
    val = prev->v;
    (*head) = (*head)->next;
    free(prev);
    return val;
}


int bsort(Elem *l)
{
    Elem *n = l;
    Elem *node1, *node2;


    for(node1 = n; node1; node1 = node1->next )
        for( node2 = n; node2; node2 = node2->next )
            if( node1->v < node2->v ){ // если число из node меньше числа из node2 то переставляем их
                int i = node1->v;
                node1->v = node2->v;
                node2->v = i;
            }
}

int ListBubble(Elem *l)
{
    Elem *n;
    int change = 0;
    while(n = l->next){
        if(n->v < l->v){
            int v;
            v = l->v;
            l->v = n->v;
            n->v = v;
            change++;
        }
        l = n;
    }
    return change;
}

Elem* getLast(Elem *head) {
    if (head == NULL) {
        return NULL;
    }
    while (head->next) {
        head = head->next;
    }
    return head;
}

void pushBack(Elem *head, int value) {
    Elem *last = getLast(head);
    Elem *tmp = (Elem*) malloc(sizeof(Elem));
    tmp->v = value;
    tmp->next = NULL;
    last->next = tmp;
}

Elem *ListBSort(Elem *l)
{
    while(ListBubble(l));
}

int main(){
    //Elem MainList;
    Elem *L = NULL;
    //InitSingleLinkedList(L);
    int N = 0;
    scanf("%d", &N);
    for(int i=0; i<N; i++){
        int X = 0;
        scanf("%d", &X);
        if(!i)InsertBeforeHead(&L, X);
        else pushBack(L, X);
    }
    //ListBSort(L);
    bsort(L);
    for(int i=0; i<N; i++){
        printf("%d ", DeleteHead(&L));
    }
    return 0;
}
