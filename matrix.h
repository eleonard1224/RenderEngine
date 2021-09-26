// Header file for Matrix class
#ifndef MATRIX
#define MATRIX

class Matrix {
public:
    Matrix(int n_rows, int n_cols);
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