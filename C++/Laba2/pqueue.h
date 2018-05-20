// Mamaev 34
/*
PQueue<T, N> – очередь с приоритетом
максимального размера N с элементами типа T,
имеющая одновременно операцию удаления
максимального элемента и операцию удаления
минимального элемента. Указанные операции
должны работать за логарифмическое время.
В PQueue<bool, N> все операции должны
работать за константное время.
 */

#ifndef LABA2_PQUEUE_H
#define LABA2_PQUEUE_H


#include <bits/stdc++.h>
using namespace std;

//Очередь с приоритетами реализуется через АВЛ-дерево

template <typename T, size_t N>
class PQueue{

public:
    struct Tree{
        int balance;
        T v;
        Tree *parent;
        Tree *left;
        Tree *right;
    };
    PQueue();
    bool empty();
    T extractMin();
    T extractMax();
    void deleteNode(Tree *X);
    Tree* binaryInsert(T v);
    void insert(T v);
    void replaceNode(Tree *X, Tree *Y);
    Tree *succ(Tree *X);
    Tree *prec(Tree *X);
    Tree *minimum(Tree *Y);
    Tree *maximum(Tree *Y);
    void deleteEverything();
    void delette(Tree *Y);
    void rotateLeft(Tree *X);
    void rotateRight(Tree *X);
    void newDeleteNode(Tree *Y);

private:
    Tree *Node;
    Tree arr[N];
    int count;
};


template <typename T, size_t N>
PQueue<T, N>::PQueue(){
    Node = NULL;
    count = 0;
    //arr = new Tree[N];
}


template <typename T, size_t N>
bool PQueue<T, N>::empty(){
    return Node == NULL;
}

template <typename T, size_t N>
typename PQueue<T, N>::Tree *PQueue<T, N>::minimum(Tree *Y){
    if(Y == NULL)
        return NULL;
    Tree *X = Y;
    while(X->left != NULL){
        X = X->left;
    }
    return X;
}

template <typename T, size_t N>
typename PQueue<T, N>::Tree *PQueue<T, N>::maximum(Tree *Y){
    if(Y == NULL)
        return NULL;
    Tree *X = Y;
    while(X->right != NULL){
        X = X->right;
    }
    return X;
}

//Получение и удаление наименьшего элемента
template <typename T, size_t N>
T PQueue<T, N>::extractMin(){
    Tree *X = Node;
    while(X->left != NULL){
        X = X->left;
    }
    T t = X->v;
    newDeleteNode(X);
    return t;
}

//Получение и удаление наибольшего элемента
template <typename T, size_t N>
T PQueue<T, N>::extractMax(){
    Tree *X = Node;
    while(X->right != NULL){
        X = X->right;
    }
    T t = X->v;
    newDeleteNode(X);
    return t;
}

template <typename T, size_t N>
typename PQueue<T, N>::Tree* PQueue<T, N>::succ(Tree *X){
    if(X->right != NULL){
        return minimum(X->right);
    }
    Tree *Y = X->parent;
    while(Y!=NULL && X==Y->right){
        X=Y;
        Y=Y->parent;
    }
    return Y;
}


template <typename T, size_t N>
typename PQueue<T, N>::Tree* PQueue<T, N>::binaryInsert(T v){
    Tree *Y;
    Y = &arr[count++];
    //Y = (Tree*)malloc(sizeof(Tree));
    Y->v = v;
    Y->parent = Y->left = Y->right = NULL;
    if(Node == NULL)
        Node = Y;
    else{
        Tree *X = Node;
        while(1){
            if(v < X->v){
                if(X->left == NULL){
                    X->left = Y;
                    Y->parent = X;
                    break;
                }
                X = X->left;
            }
            else{
                if(X->right == NULL){
                    X->right = Y;
                    Y->parent = X;
                    break;
                }
                X = X->right;
            }
        }
    }
    return Node;
}

//Добавление элемента
template <typename T, size_t N>
void PQueue<T, N>::insert(T v) {
    Tree *A = binaryInsert(v);
    A->balance = 0;
    while(1){
        Tree *X = A->parent;
        if(X == NULL)
            break;
        if(A == X->left){
            X->balance--;
            if(X->balance == 0)
                break;
            if(X->balance == -2){
                if(A->balance == 1)
                    rotateLeft(A);
                rotateRight(X);
                break;
            }
        } else {
            X->balance++;
            if(X->balance == 0)
                break;
            if(X->balance == 2){
                if(A->balance == -1)
                    rotateRight(A);
                rotateRight(X);
                break;
            }
        }
        A = X;
    }
}

//Вспомогательные функции для балансирования дерева
template <typename T, size_t N>
void PQueue<T, N>::replaceNode(Tree *X, Tree *Y){
    if(X == Node){
        Node = Y;
        if(Y!=NULL){
            Y->parent = NULL;
        }
    }
    else{
        Tree *P = X->parent;
        if(Y!=NULL){
            Y->parent = P;
        }
        if(P->left==X){
            P->left = Y;
        }
        else{
            P->right = Y;
        }
    }
}


template <typename T, size_t N>
void PQueue<T, N>::newDeleteNode(Tree *Y){

    int balanceDelta;
    Tree *X;
    Tree *Z = Node;
    if(Z->left && Z->right){
        Tree *W = Z->right;
        while(W->left)
            W = W->left;
        if(W->parent == Z) {
            Y = W;
            balanceDelta = -1;
        } else {
            Y = W->parent;
            balanceDelta = 1;
        }
        this->replaceNode(W, W->right);

        W->left = Z->left;
        Z->left->parent = W;
        W->right = Z->right;
        if(Z->right)
            Z->right->parent = W;
        replaceNode(Z, W);
    } else {
        X = Z->parent;
        balanceDelta = (X != NULL && Y == X->left ? 1 : -1);
        if(!Z->left && !Z->right)
            replaceNode(Z, NULL);
        else if(!Z->left)
            this->replaceNode(Z, Z->right);
        else if(!Z->right)
            replaceNode(Z, Z->left);
    }

    while(Y){
        Y->balance += balanceDelta;

        Tree *X = Y->parent;
        balanceDelta = (X != NULL && Y == X->left ? 1 : -1);
        if(Y->balance == 2){
            if(Y->right->balance == -1)
                rotateRight(Y->right);
            rotateLeft(Y);
            if(Y->balance == 1)
                return;
            break;
        }
        else if(Y->balance == -2){
            if(Y->right->balance == 1)
                rotateLeft(Y->left);
            rotateRight(Y);
            if(Y->balance == -1)
                return;
            break;
        }
        else if(Y->balance == -1 || Y->balance == 1)
            return;
        Y = X;
    }

    //free(X);
}




template <typename T, size_t N>
void PQueue<T, N>::deleteNode(Tree *X){
    if(X->left == NULL && X->right == NULL){
        Tree *Z = X;
        while(Z!=Node){
            Z = Z->parent;
        }
        replaceNode(X, NULL);
    }
    else if(X->left==NULL){
        Tree *Z = X;
        while(Z!=Node){
            Z = Z->parent;
        }
        replaceNode(X, X->right);
    }
    else if(X->right==NULL){
        Tree *Z = X;
        while(Z!=Node){
            Z = Z->parent;
        }
        replaceNode(X, X->left);
    }
    else{
        Tree *Y = succ(X);
        Tree *Z = Y;
        while(Z!=Node){
            Z = Z->parent;
        }
        replaceNode(Y, Y->right);
        X->left->parent = Y;
        Y->left = X->left;
        if(X->right != NULL){
            X->right->parent = Y;
        }
        Y->right = X->right;
        replaceNode(X, Y);
    }
    //free(X);
}

template <typename T, size_t N>
void PQueue<T, N>::rotateLeft(Tree *X){
    Tree *Y = X->right;
    replaceNode(X, Y);
    Tree *B = Y->left;
    if(B != NULL)
        B->parent = X;
    X->right = B;
    X->parent = Y;
    Y->left = X;
    X->balance--;
    if(Y->balance > 0)
        X->balance -= Y->balance;
    Y->balance--;
    if(X->balance < 0)
        Y->balance += X->balance;
}

template <typename T, size_t N>
void PQueue<T, N>::rotateRight(Tree *X){
    Tree *Y = X->left;
    replaceNode(X, Y);
    Tree *B = Y->right;
    if(B != NULL)
        B->parent = X;
    X->left = B;
    X->parent = Y;
    Y->right = X;
    X->balance++;
    if(Y->balance < 0)
        X->balance -= Y->balance;
    Y->balance++;
    if(X->balance > 0)
        Y->balance += X->balance;
}


//Очищение памяти
template <typename T, size_t N>
void PQueue<T, N>::deleteEverything() {
    delette(Node);
    //delete arr;
}

template <typename T, size_t N>
void PQueue<T, N>::delette(Tree *Y) {
    if (Y != NULL) {
        delette(Y->left);
        delette(Y->right);
        free(Y);
    }
}

//Спецификация для булевских элементов
//Пусть true > false

template <size_t N>
class PQueue<bool, N>{
private:
    size_t nTrue, nFalse;
    size_t size, count;
public:
    PQueue();
    void insert(bool elem);
    bool extractMin();
    bool extractMax();
};

template <size_t N>
PQueue<bool, N>::PQueue() {
    size = N;
    count = 0;
    nTrue = nFalse = 0;
}

template <size_t N>
void PQueue<bool, N>::insert(bool elem) {
    elem ? nTrue++ : nFalse++;
    count++;
}

template <size_t N>
bool PQueue<bool, N>::extractMin() {
    if(count > 0)
        if(nFalse > 0)
            return nFalse-- == 0;
        else
            return nTrue-- > 0;
    else throw "NoSuchElementException";
}

template <size_t N>
bool PQueue<bool, N>::extractMax() {
    if(count > 0)
        if(nTrue > 0)
            return nTrue-- > 0;
        else
            return nFalse-- == 0;
    else throw "NoSuchElementException";
}




#endif //LABA2_PQUEUE_H
