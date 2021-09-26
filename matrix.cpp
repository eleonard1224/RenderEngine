// Implementation of Matrix class
#include <iostream>
#include "matrix.h"
using namespace std;

// Matrix definitions
Matrix::Matrix(int n_rows, int n_cols): n_rows(n_rows), n_cols(n_cols) {
    matrix = new double*[n_rows];
    for(int i = 0; i < n_rows; i++) {
        matrix[i] = new double[n_cols];
    }
}

Matrix::~Matrix() {
    int i;
    for(i = 0; i < n_rows; i++) {
        delete[] matrix[i];
    }
    delete[] matrix;
}

void Matrix::print_matrix() {
    int i, j;
    for(i = 0; i < n_rows; i++) {
        for(j = 0; j < n_cols; j++) {
            cout << "matrix[" << i << "][" << j << "] = " << matrix[i][j] << endl;
        }
    }
}

Matrix Matrix::operator * (const Matrix& factor) const {
    if (n_cols != factor.n_rows) {
        cerr << "No. of cols of 1st matrix not equal to no. or rows of 2nd matrix" << endl;
        exit(EXIT_FAILURE);
    }
    int i, j, k;
    Matrix product(n_rows, factor.n_cols);
    for(i = 0; i < product.n_rows; i++) {
        for(j = 0; j < product.n_cols; j++) {
            product[i][j] = 0.0;
            for(k = 0; k < n_cols; k++) {
                product[i][j] += matrix[i][k]*factor[k][j];
            }
        }
    } 
    return product;   
}

double* Matrix::operator[]( int index ) const {
    return matrix[index];
}

Matrix inverse(const Matrix& m) {
    if ((m.n_rows != 4) || (m.n_cols != 4)) {
        cerr << "Matrix is not 4x4" << endl;
        exit(EXIT_FAILURE);
    }

    Matrix im(m.n_rows,m.n_cols);
    double det;

    double A2323 = m[2][2] * m[3][3] - m[2][3] * m[3][2];
    double A1323 = m[2][1] * m[3][3] - m[2][3] * m[3][1];
    double A1223 = m[2][1] * m[3][2] - m[2][2] * m[3][1];
    double A0323 = m[2][0] * m[3][3] - m[2][3] * m[3][0];
    double A0223 = m[2][0] * m[3][2] - m[2][2] * m[3][0];
    double A0123 = m[2][0] * m[3][1] - m[2][1] * m[3][0];
    double A2313 = m[1][2] * m[3][3] - m[1][3] * m[3][2];
    double A1313 = m[1][1] * m[3][3] - m[1][3] * m[3][1];
    double A1213 = m[1][1] * m[3][2] - m[1][2] * m[3][1];
    double A2312 = m[1][2] * m[2][3] - m[1][3] * m[2][2];
    double A1312 = m[1][1] * m[2][3] - m[1][3] * m[2][1];
    double A1212 = m[1][1] * m[2][2] - m[1][2] * m[2][1];
    double A0313 = m[1][0] * m[3][3] - m[1][3] * m[3][0];
    double A0213 = m[1][0] * m[3][2] - m[1][2] * m[3][0];
    double A0312 = m[1][0] * m[2][3] - m[1][3] * m[2][0];
    double A0212 = m[1][0] * m[2][2] - m[1][2] * m[2][0];
    double A0113 = m[1][0] * m[3][1] - m[1][1] * m[3][0];
    double A0112 = m[1][0] * m[2][1] - m[1][1] * m[2][0];

    det = m[0][0] * ( m[1][1] * A2323 - m[1][2] * A1323 + m[1][3] * A1223 )
        - m[0][1] * ( m[1][0] * A2323 - m[1][2] * A0323 + m[1][3] * A0223 )
        + m[0][2] * ( m[1][0] * A1323 - m[1][1] * A0323 + m[1][3] * A0123 )
        - m[0][3] * ( m[1][0] * A1223 - m[1][1] * A0223 + m[1][2] * A0123 );
    det = 1 / det;

    im[0][0] = det *   ( m[1][1] * A2323 - m[1][2] * A1323 + m[1][3] * A1223 );
    im[0][1] = det * - ( m[0][1] * A2323 - m[0][2] * A1323 + m[0][3] * A1223 );
    im[0][2] = det *   ( m[0][1] * A2313 - m[0][2] * A1313 + m[0][3] * A1213 );
    im[0][3] = det * - ( m[0][1] * A2312 - m[0][2] * A1312 + m[0][3] * A1212 );
    im[1][0] = det * - ( m[1][0] * A2323 - m[1][2] * A0323 + m[1][3] * A0223 );
    im[1][1] = det *   ( m[0][0] * A2323 - m[0][2] * A0323 + m[0][3] * A0223 );
    im[1][2] = det * - ( m[0][0] * A2313 - m[0][2] * A0313 + m[0][3] * A0213 );
    im[1][3] = det *   ( m[0][0] * A2312 - m[0][2] * A0312 + m[0][3] * A0212 );
    im[2][0] = det *   ( m[1][0] * A1323 - m[1][1] * A0323 + m[1][3] * A0123 );
    im[2][1] = det * - ( m[0][0] * A1323 - m[0][1] * A0323 + m[0][3] * A0123 );
    im[2][2] = det *   ( m[0][0] * A1313 - m[0][1] * A0313 + m[0][3] * A0113 );
    im[2][3] = det * - ( m[0][0] * A1312 - m[0][1] * A0312 + m[0][3] * A0112 );
    im[3][0] = det * - ( m[1][0] * A1223 - m[1][1] * A0223 + m[1][2] * A0123 );
    im[3][1] = det *   ( m[0][0] * A1223 - m[0][1] * A0223 + m[0][2] * A0123 );
    im[3][2] = det * - ( m[0][0] * A1213 - m[0][1] * A0213 + m[0][2] * A0113 );
    im[3][3] = det *   ( m[0][0] * A1212 - m[0][1] * A0212 + m[0][2] * A0112 ); 
    return im;
}