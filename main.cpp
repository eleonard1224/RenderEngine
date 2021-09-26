// main file for render engine
#include<iostream>
#include "geometry.h"
#include "matrix.h"
#include "camera.h"
using namespace std;

int main() {

    string mesh_file("meshes/monkey.csv");
    CameraMesh camera_mesh(mesh_file, 0.90, 0.70, 0.6, 7.358890056610107, -6.925790786743164, 4.958309173583984);
    Camera camera(0.5,0.5);
    camera.render(camera_mesh, 512, 512);
    return 0;
}