// main file for render engine
#include <iostream>
#include "geometry.h"
#include "matrix.h"
#include "camera.h"
using namespace std;

int main(int argc, char *argv[]) {

    // for (int i = 0; i < argc; ++i)
    //     cout << argv[i] << "\n";
    string input_file = argv[1];
    cout << "input_file = " << input_file << endl;
    Input inputs;
    string mesh_file, output_file;
    double Rx, Ry, Rz, Tx, Ty, Tz, canvas_width, canvas_height;
    int pixel_width, pixel_height;
    inputs.read_inputs(input_file, mesh_file, Rx, Ry, Rz, Tx, Ty, Tz, output_file, canvas_width, canvas_height, pixel_width, pixel_height);
    cout << "mesh_file = " << mesh_file << ", Rx = " << Rx << 
    ", Ry = " << Ry << ", Rz = " << Rz 
    << ", Tx = " << Tx << ", Ty = " << Ty << ", Tz = " << Tz
    << ", output_file = " << output_file 
    << ", canvas_width = " << canvas_width 
    << ", canvas_height = " << canvas_height 
    << ", pixel_width = " << pixel_width 
    << ", pixel_height = " << pixel_height << endl;
    // cout << "return" << endl;

    // string mesh_file_0("meshes/monkey.csv");
    // CameraMesh camera_mesh(mesh_file_0, 0.90, 0.70, 0.6, 7.358890056610107, -6.925790786743164, 4.958309173583984);
    // Camera camera(0.5,0.5);
    // string output_file_0("monkey.png");
    // camera.render(camera_mesh, 512, 512, output_file_0);

    CameraMesh camera_mesh(mesh_file, Rx, Ry, Rz, Tx, Ty, Tz);
    Camera camera(canvas_width,canvas_height);
    camera.render(camera_mesh, pixel_width, pixel_height, output_file);

    return 0;
}