#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>

typedef struct Tree {
  int k, count;
  char *v;
  struct Tree *parent;
  struct Tree *left;
  struct Tree *right;
} Tree;

Tree *InitBinaryTree() { return NULL; }

int EmptyTree(Tree *T) { return !T ? 1 : 0; }

Tree *Minimum(Tree *T) {
  if (EmptyTree(T)) return NULL;
  Tree *X = T;
  while (X->left != NULL) {
    X = X->left;
  }
  return X;
}

Tree *Succ(Tree *X) {
  if (X->right != NULL) {
    return Minimum(X->right);
  }
  Tree *Y = X->parent;
  while (Y != NULL && X == Y->right) {
    X = Y;
    Y = Y->parent;
  }
  return Y;
}

Tree *Descend(Tree *T, int k) {
  Tree *X = T;
  while (X != NULL && X->k != k) {
    if (k < X->k)
      X = X->left;
    else
      X = X->right;
  }
  return X;
}

char *Lookup(Tree *T, int k) {
  Tree *X = Descend(T, k);
  return X->v;
}

Tree *Insert(Tree *T, int k, char *v) {
  Tree *Y;
  Y = malloc(sizeof(Tree));
  Y->k = k;
  Y->count = 0;
  Y->v = malloc(10 * sizeof(char));
  strcpy(Y->v, v);
  Y->parent = Y->left = Y->right = NULL;
  if (T == NULL)
    T = Y;
  else {
    Tree *X = T;
    X->count++;
    while (1) {
      if (k < X->k) {
        if (X->left == NULL) {
          X->left = Y;
          Y->parent = X;
          break;
        }
        X = X->left;
        X->count++;
      } else {
        if (X->right == NULL) {
          X->right = Y;
          Y->parent = X;
          break;
        }
        X = X->right;
        X->count++;
      }
    }
  }
  return T;
}

Tree *ReplaceNode(Tree *T, Tree *X, Tree *Y) {
  if (X == T) {
    T = Y;
    if (Y != NULL) {
      Y->parent = NULL;
    }
  } else {
    Tree *P = X->parent;
    if (Y != NULL) {
      Y->parent = P;
    }
    if (P->left == X) {
      P->left = Y;
    } else {
      P->right = Y;
    }
  }
  return T;
}

Tree *Delete(Tree *T, int k) {
  Tree *X = Descend(T, k);
  if (X->left == NULL && X->right == NULL) {
    Tree *Z = X;
    while (Z != T) {
      Z = Z->parent;
      Z->count--;
    }
    T = ReplaceNode(T, X, NULL);
  } else if (X->left == NULL) {
    Tree *Z = X;
    while (Z != T) {
      Z = Z->parent;
      Z->count--;
    }
    T = ReplaceNode(T, X, X->right);
  } else if (X->right == NULL) {
    Tree *Z = X;
    while (Z != T) {
      Z = Z->parent;
      Z->count--;
    }
    T = ReplaceNode(T, X, X->left);
  } else {
    Tree *Y = Succ(X);
    Y->count = X->count - 1;
    Tree *Z = Y;
    while (Z != T) {
      Z = Z->parent;
      Z->count--;
    }
    T = ReplaceNode(T, Y, Y->right);
    X->left->parent = Y;
    Y->left = X->left;
    if (X->right != NULL) {
      X->right->parent = Y;
    }
    Y->right = X->right;
    T = ReplaceNode(T, X, Y);
  }
  free(X->v);
  free(X);
  return T;
}

void DeleteEverything(Tree *T) {
  if (!EmptyTree(T)) {
    DeleteEverything(T->left);
    DeleteEverything(T->right);
    free(T->v);
    free(T);
  }
}

char *SearchRank(Tree *T, int n) {
  int temp = !T->left ? 0 : (T->left->count + 1);
  if (n == temp)
    return T->v;
  else
    return (n > temp ? SearchRank(T->right, n - temp - 1)
                     : SearchRank(T->left, n));
}

int main() {
  Tree *T = InitBinaryTree();
  int N, K, i = 0;
  char V[10], command[6];
  scanf("%d", &N);
  for (i = 0; i < N; i++) {
    scanf("%s", &command);
    switch (command[0]) {
      case 'I':
        scanf("%d%s", &K, V);
        T = Insert(T, K, V);
        break;
      case 'L':
        scanf("%d", &K);
        char *ans = Lookup(T, K);
        printf("%s\n", ans);
        break;
      case 'D':
        scanf("%d", &K);
        T = Delete(T, K);
        break;
      case 'S':
        scanf("%d", &K);
        char *answer = SearchRank(T, K);
        printf("%s\n", answer);
        break;
    }
  }
  DeleteEverything(T);
}
