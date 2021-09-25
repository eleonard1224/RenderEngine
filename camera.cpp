// Implementation of Camera class
#include "camera.h"

// Camera definitions
Camera::Camera(double canvas_width, double canvas_height): canvas_width(canvas_width), canvas_height(canvas_height) {};

void Camera::render(const CameraMesh& camera_mesh, int pixel_width, int pixel_height) {

    // Allocate raster_points
    int i, j;
    int n_faces = camera_mesh.n_faces;
    int ***raster_points;
    raster_points = new int**[n_faces];
    for(i = 0; i < n_faces; i++) {
        raster_points[i] = new int*[3];
        for(j = 0; j < 3; j++) {
            raster_points[i][j] = new int[2];
        }
    }

    // Calculate raster_points
    double normalized_x, normalized_y;
    double pixel_width_d = (double) pixel_width;
    double pixel_height_d = (double) pixel_height;
    for(i = 0; i < n_faces; i++) {
        for(j = 0; j < 3; j++) {
            normalized_x = (camera_mesh.camera_points[i][j][0] + (canvas_width/2.0))/canvas_width; 
            raster_points[i][j][0] = int(floor(normalized_x*pixel_width_d));
            normalized_y = (camera_mesh.camera_points[i][j][1] + (canvas_height/2.0))/canvas_height; 
            raster_points[i][j][1] = int(floor(normalized_y*pixel_height_d));
            // std::cout << "x = " << raster_points[i][j][0] << ", y = " << raster_points[i][j][1] << std::endl; 
        }
    }

    // Write out render to file
    Mat img(512, 512, CV_8UC3, Scalar(255,0,255));
    // cv::Mat mat = cv::Mat::zeros(5, 5, CV_32FC(16));
    imwrite("test.png",  img);

    // De-allocate raster_points
    for(i = 0; i < n_faces; i++) {
        for(j = 0; j < 3; j++) {
            delete[] raster_points[i][j];
        }
        delete[] raster_points[i];
    }
    delete[] raster_points;
}