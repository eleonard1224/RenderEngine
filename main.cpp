// main file for render engine
#include <iostream>
#include "geometry.h"
#include "matrix.h"
#include "camera.h"
using namespace std;
using namespace std::chrono;

int main(int argc, char *argv[]) {

    string input_file = argv[1];
    Input inputs;
    string mesh_file, output_file;
    double Rx, Ry, Rz, Tx, Ty, Tz, canvas_width, canvas_height;
    int pixel_width, pixel_height;
    inputs.read_inputs(input_file, mesh_file, Rx, Ry, Rz, Tx, Ty, Tz, output_file, canvas_width, canvas_height, pixel_width, pixel_height);
    CameraMesh camera_mesh(mesh_file, Rx, Ry, Rz, Tx, Ty, Tz);
    Camera camera(canvas_width,canvas_height);
    // Time render
    // auto start = high_resolution_clock::now();
    camera.render(camera_mesh, pixel_width, pixel_height, output_file);
    // auto stop = high_resolution_clock::now();
    // auto duration = duration_cast<microseconds>(stop - start);
    // cout << "Time to Render Image (microseconds) = " << duration.count() << endl;
    return 0;
}