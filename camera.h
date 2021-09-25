// Header file for Camera class
#ifndef CAMERA
#define CAMERA

#include "geometry.h"

class Camera {
private:
    double canvas_x;
    double canvas_y;
public:
    Camera(double canvas_x, double canvas_y);
    void render(const CameraMesh& camera_mesh);
};

#endif