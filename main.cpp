// main file for render engine
#include <iostream>
#include "geometry.h"
#include "mesh.h"
#include "matrix.h"
#include "camera.h"
using namespace std;

int main(int argc, char *argv[]) {

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