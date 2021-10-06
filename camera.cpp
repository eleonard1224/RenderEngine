// Implementation of Camera class
#include "camera.h"

// Camera definitions
Camera::Camera(double canvas_width, double canvas_height): canvas_width(canvas_width), canvas_height(canvas_height) {};

void Camera::render(const CameraMesh& camera_mesh, int pixel_width, int pixel_height, string output_file) {

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

    // // Calculate raster_points
    // double normalized_x, normalized_y;
    // double pixel_width_d = (double) pixel_width;
    // double pixel_height_d = (double) pixel_height;
    // for(i = 0; i < n_faces; i++) {
    //     for(j = 0; j < 3; j++) {
    //         normalized_x = (camera_mesh.camera_points[i][j][0] + (canvas_width/2.0))/canvas_width; 
    //         raster_points[i][j][0] = int(floor(normalized_x*pixel_width_d));
    //         normalized_y = (camera_mesh.camera_points[i][j][1] + (canvas_height/2.0))/canvas_height; 
    //         raster_points[i][j][1] = int(floor((1.0-normalized_y)*pixel_height_d));
    //     }
    // }



    // Calculate and time raster_points using multiple threads
    auto start = high_resolution_clock::now();
    int n_threads = thread::hardware_concurrency();
    int *start_faces = new int[n_threads];
    int *end_faces = new int[n_threads];
    int n_faces_per_thread = camera_mesh.n_faces/n_threads;
    for(i = 0; i < n_threads; i++) {
        start_faces[i] = n_faces_per_thread*i;
        end_faces[i] = start_faces[i] + n_faces_per_thread;
    }
    vector<thread> threads;
    for (i = 0; i < n_threads; i++) {
        threads.push_back(thread(&Camera::calculate_raster_points, this, camera_mesh.camera_points, start_faces[i], end_faces[i], raster_points, (double) pixel_width, (double) pixel_height));
    }
    for (auto &th : threads) {
        th.join();
    }
    // Loop over the remaining faces
    calculate_raster_points(camera_mesh.camera_points, end_faces[n_threads-1], camera_mesh.n_faces, raster_points, (double) pixel_width, (double) pixel_height);
    delete[] start_faces;
    delete[] end_faces;
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

void Camera::calculate_raster_points(double ***camera_points, int start_face, int end_face, int ***raster_points, double pixel_width, double pixel_height) {

    int i, j;
    double normalized_x, normalized_y;
    for(i = start_face; i < end_face; i++) {
        for(j = 0; j < 3; j++) {
            normalized_x = (camera_points[i][j][0] + (canvas_width/2.0))/canvas_width; 
            raster_points[i][j][0] = int(floor(normalized_x*pixel_width));
            normalized_y = (camera_points[i][j][1] + (canvas_height/2.0))/canvas_height; 
            raster_points[i][j][1] = int(floor((1.0-normalized_y)*pixel_height));
        }
    }
}