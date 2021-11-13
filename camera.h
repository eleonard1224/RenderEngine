// Header file for Camera class
#ifndef CAMERA
#define CAMERA

#include <iostream>
#include <cmath>
#include <thread>
#include <vector>
#include <array>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "mesh.h"
#include "geometry.h"
#include "io.h"
using namespace cv;
using namespace std::chrono;

class Camera {
private:
    double canvas_width;
    double canvas_height;
public:
    Camera(double canvas_width, double canvas_height);
    template <class MeshElement> void render(const CameraMesh<MeshElement>& camera_mesh, int pixel_width, int pixel_height, string output_file);
};

// Camera definitions
Camera::Camera(double canvas_width, double canvas_height): canvas_width(canvas_width), canvas_height(canvas_height) {};

template <class MeshElement> void Camera::render(const CameraMesh<MeshElement>& camera_mesh, int pixel_width, int pixel_height, string output_file) {

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

    // Calculate and time raster_points using multiple threads
    auto start = high_resolution_clock::now();
    int n_threads = thread::hardware_concurrency();
    auto start_faces = make_unique<int[]>(n_threads);
    auto end_faces = make_unique<int[]>(n_threads);
    int n_faces_per_thread = camera_mesh.n_faces/n_threads;
    for(i = 0; i < n_threads; i++) {
        start_faces[i] = n_faces_per_thread*i;
        end_faces[i] = start_faces[i] + n_faces_per_thread;
    }
    auto calculate_raster_points = [*this, &camera_mesh, &raster_points](int start_face, int end_face, double pixel_width, double pixel_height){
        int i, j;
        double normalized_x, normalized_y;
        for(i = start_face; i < end_face; i++) {
            for(j = 0; j < 3; j++) {
                normalized_x = (camera_mesh.camera_points[i][j][0] + (canvas_width/2.0))/canvas_width; 
                raster_points[i][j][0] = int(floor(normalized_x*pixel_width));
                normalized_y = (camera_mesh.camera_points[i][j][1] + (canvas_height/2.0))/canvas_height; 
                raster_points[i][j][1] = int(floor((1.0-normalized_y)*pixel_height));
            }
        }
    };
    vector<thread> threads;
    for (i = 0; i < n_threads; i++) {
        threads.push_back(thread(calculate_raster_points,start_faces[i], end_faces[i], (double) pixel_width, (double) pixel_height));
    }
    for (auto &th : threads) {
        th.join();
    }
    // Loop over the remaining faces
    calculate_raster_points(end_faces[n_threads-1], camera_mesh.n_faces, (double) pixel_width, (double) pixel_height);
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    cout << "Time to Calculate Raster Points (microseconds) = " << duration.count() << endl;

    // Write out render to file
    Mat img(pixel_width, pixel_height, CV_8UC3, Scalar(0,0,0));
    int thickness = 1;
    for(i = 0; i < n_faces; i++) {
            Point p0(raster_points[i][0][0], raster_points[i][0][1]);
            Point p1(raster_points[i][1][0], raster_points[i][1][1]);
            Point p2(raster_points[i][2][0], raster_points[i][2][1]);
            line(img, p0, p1, Scalar(255, 255, 255), thickness, LINE_AA);
            line(img, p1, p2, Scalar(255, 255, 255), thickness, LINE_AA);
            line(img, p2, p0, Scalar(255, 255, 255), thickness, LINE_AA);
    }
    Output output_img;
    output_img.write_img_file(output_file,img);

    // De-allocate raster_points
    for(i = 0; i < n_faces; i++) {
        for(j = 0; j < 3; j++) {
            delete[] raster_points[i][j];
        }
        delete[] raster_points[i];
    }
    delete[] raster_points;
}

#endif