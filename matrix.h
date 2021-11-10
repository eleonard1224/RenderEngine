// Header file for Matrix class
#ifndef MATRIX
#define MATRIX

#include <iostream>

class Matrix {
public:
    Matrix(); // Default constructor
    Matrix(int n_rows, int n_cols); // Parameterized constructor
    Matrix(const Matrix & mat); // Copy constructor
    Matrix & operator = (const Matrix & mat); // Copy assignment
    Matrix(Matrix && mat); // Move constructor
    Matrix & operator = (Matrix && mat); // Move assignment
    ~Matrix();
    void print_matrix();
    Matrix operator * (const Matrix& factor) const;
    double* operator[]( int index ) const;
    int n_rows;
    int n_cols;
    double **matrix;
};

// For now, implement the inverse method only on 4x4 matrices
Matrix inverse(const Matrix& m);

#endif