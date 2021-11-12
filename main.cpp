// main file for render engine
#include <iostream>
#include "geometry.h"
#include "mesh.h"
#include "matrix.h"
#include "camera.h"
using namespace std;

int main(int argc, char *argv[]) {

    // /* Begin Testing */
    // Matrix A{2,2};
    // A[0][0] = 1.2; A[0][1] = 2.3; A[1][0] = 3.3; A[1][1] = 4.5;

    // // Copy Constructor
    // // Matrix B{A};
    // // cout << "B[1][1] = " << B[1][1] << endl;

    // // // Copy assignment
    // // Matrix C;
    // // C = A;
    // // cout << "C[1][1] = " << C[1][1] << endl;

    // // Move constructor
    // // Matrix D(move(A));
    // // cout << "D[1][1] = " << D[1][1] << endl;

    // // Move assignment
    // Matrix E;
    // E = move(A);
    // cout << "E[1][1] = " << E[1][1] << endl;

    // /* End Testing */

    // Main code
    string input_file = argv[1];
    Input inputs;
    string mesh_file, output_file;
    double Rx, Ry, Rz, Tx, Ty, Tz, canvas_width, canvas_height;
    int pixel_width, pixel_height;
    inputs.read_inputs(input_file, mesh_file, Rx, Ry, Rz, Tx, Ty, Tz, output_file, canvas_width, canvas_height, pixel_width, pixel_height);
    CameraMesh<Face> camera_mesh(mesh_file, Rx, Ry, Rz, Tx, Ty, Tz);
    Camera camera(canvas_width,canvas_height);
    camera.render(camera_mesh, pixel_width, pixel_height, output_file);
    return 0;
}