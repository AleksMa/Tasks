//Mamaev 35

#include <bits/stdc++.h>

#ifndef NY9_CPP_LABS_DECLARATION_H
#define NY9_CPP_LABS_DECLARATION_H

using namespace std;


class StringSet {
private:

    std::string *a;
    std::size_t n;
public:
    StringSet();
    StringSet(int n);
    StringSet(std::string *a, int n);

    StringSet(const StringSet &str);

    size_t getN();

    virtual ~StringSet();
    std::string& operator[](int i);
    StringSet add(StringSet &str);
    StringSet mul(StringSet &str);
    void orderedSet();
    StringSet& operator= (StringSet src);
};

class Matrix {
private:
    StringSet **a;
    size_t n;

    class Row{
    private:
        Matrix *matrix;
        int i;
    public:
        Row(Matrix *matrix, int i){
            this->matrix = matrix;
            this->i = i;
        };
        StringSet& operator[] (int j){
            return matrix->a[i][j];
        };
    };

    /*
    Matrix::Row::Row(Matrix *matrix, int i) {
        this->matrix = matrix;
        this->i = i;
    }

    StringSet& Row::operator[](int j) {
        return matrix->a[i][j];
    }*/

public:
    Matrix(size_t n);

    virtual ~Matrix();

    Matrix(const Matrix &m);
    Matrix& operator= (Matrix m);

    size_t getN();

    StringSet& getLink(int i, int j);
    void square();

    Matrix::Row operator[](int i){
        return Row(this, i);
    }
};

#endif //NY9_CPP_LABS_DECLARATION_H