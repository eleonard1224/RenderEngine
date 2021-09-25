// main file for render engine
#include<iostream>
#include "geometry.h"
#include "matrix.h"

using namespace std;

int main() {

    // Vertex v0(1.0, -1.0, 0.0);
    // Vertex v1(1.0, 1.0, 0.0);
    // Vertex v2(-1.0, 1.0, 0.0);
    // Face face(v0, v1, v2);

    // string mesh_file("meshes/square.csv");
    // CameraMesh camera_mesh(mesh_file);
    // camera_mesh.print_mesh();
    // cout << "Render Engine" << endl;
    // int n_rows_1 = 2; 
    // int n_cols_1 = 2;
    // Matrix matrix_1(n_rows_1, n_cols_1);
    // matrix_1[0][0] = 1.0; matrix_1[0][1] = 2.0; matrix_1[1][0] = 3.0; matrix_1[1][1] = 4.0;
    // // matrix_1.print_matrix();

    // int n_rows_2 = 2; 
    // int n_cols_2 = 1;
    // Matrix matrix_2(n_rows_2, n_cols_2);
    // matrix_2[0][0] = 2.0; matrix_2[1][0] = -2.0;
    // // matrix_2.print_matrix();

    // Matrix matrix_3 = matrix_1*matrix_2;
    // // matrix_3.print_matrix();

    // cout << "matrix_3[0][0] = " << matrix_3[0][0] << endl;

    // Matrix A(4,4);
    // A[0][0] = 1.25; A[0][1] = 4.44; A[0][2] = 1.36; A[0][3] = 2.42;
    // A[1][0] = 9.25; A[1][1] = 2.44; A[1][2] = 2.36; A[1][3] = 2.42;
    // A[2][0] = 3.25; A[2][1] = 15.44; A[2][2] = 3.36; A[2][3] = 3.42;
    // A[3][0] = 4.25; A[3][1] = 22.44; A[3][2] = 4.36; A[3][3] = 4.42;
    // Matrix B = inverse(A);
    // Matrix C = A*B;
    // C.print_matrix();

    // Matrix M(4,4);
    // M[0][0] = 0.6859206557273865; M[0][1] = -0.32401347160339355; M[0][2] = 0.6515582203865051; M[0][3] = 7.358891487121582;
    // M[1][0] = 0.7276763319969177; M[1][1] = 0.305420845746994; M[1][2] = -0.6141703724861145; M[1][3] = -6.925790786743164;
    // M[2][0] = 0.0; M[2][1] = 0.8953956365585327; M[2][2] = 0.44527140259742737; M[2][3] = 4.958309173583984;
    // M[3][0] = 0.0; M[3][1] = 0.0; M[3][2] = 0.0; M[3][3] = 1.0;

    // M[0][0] = 0.6859206557273865; M[0][1] = 0.7276763916015625; M[0][2] = 1.4901162970204496e-08; M[0][3] = -0.007881631143391132;
    // M[1][0] = -0.32401350140571594; M[1][1] = 0.3054208755493164; M[1][2] = 0.8953956961631775; M[1][3] = 0.060012366622686386;
    // M[2][0] = 0.6515582799911499; M[2][1] = -0.6141704320907593; M[2][2] = 0.44527143239974976; M[2][3] = -11.256155967712402;
    // M[3][0] = 0.0; M[3][1] = 0.0; M[3][2] = 0.0; M[3][3] = 1.0;

    string mesh_file("meshes/square.csv");
    CameraMesh camera_mesh(mesh_file, 1.1093189716339111, 0.0, 0.8149273890119403, 7.358890056610107, -6.925790786743164, 4.958309173583984);
    camera_mesh.print_scaled_mesh();

    return 0;
}