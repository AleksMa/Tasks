#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

struct Elem {
  int v;
  struct Elem *prev, *next;
};

struct DoubleLinkedList {
  int v;
  struct Elem *prev, *next;
};

int ListEmpty(struct DoubleLinkedList *L) { return L->next == L ? 1 : 0; }

void InsertBefore(struct Elem *X, struct Elem *Y) {
  struct Elem *Z = Y->prev;
  X->next = Y;
  Y->prev = X;
  X->prev = Z;
  Z->next = X;
}
//Для списка можно реализовать следующий алгоритм сортировки вставками:
//Пусть неотсортированная часть последовательности - та "часть" списка, которая
//еще не входит в список
//Тогда каждый элемент списка можно ставить на правильное место в
//отсортированной последовательности, которая изначально пуста (значение
//ограничителя примем наименьшим int'ом)
void InsertBeforeGreater(struct DoubleLinkedList *L, int X) {
  struct Elem *E = malloc(sizeof(struct Elem));
  E->v = X;
  struct Elem *Current = L->next;
  while ((Current->v < X) && (Current != L)) Current = Current->next;
  InsertBefore(E, Current);
}

void InitDoubleLinkedList(struct DoubleLinkedList *L) {
  L->v = INT_MIN;
  L->prev = L;
  L->next = L;
}

int Delete(struct Elem *X) {
  struct Elem *Y = X->prev;
  struct Elem *Z = X->next;
  Y->next = Z;
  Z->prev = Y;
  int v = X->v;
  free(X);
  return v;
}

int main() {
  struct DoubleLinkedList MainList;
  struct DoubleLinkedList *L = &MainList;
  InitDoubleLinkedList(L);
  int N = 0;
  scanf("%d,", &N);
  for (int i = 0; i < N; i++) {
    int X = 0;
    scanf("%d", &X);
    InsertBeforeGreater(L, X);
  }
  for (int i = 0; i < N; i++) {
    printf("%d ", Delete(L->next));
  }
}
