// Header file for Camera class
#ifndef CAMERA
#define CAMERA


#include <iostream>
#include <cmath>
#include <thread>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "geometry.h"
#include "io.h"
using namespace cv;

class Camera {
private:
    double canvas_width;
    double canvas_height;
    void calculate_raster_points(double ***camera_points, int n_faces, int ***raster_points, double pixel_width, double pixel_height);
public:
    Camera(double canvas_width, double canvas_height);
    void render(const CameraMesh& camera_mesh, int pixel_width, int pixel_height, string output_file);
};
#endif