// Header file with geometry class declarations
#ifndef GEOMETRY
#define GEOMETRY

#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <map>
#include <cmath>
#include "matrix.h"
#include "io.h"
using std::string;

class Vertex {
public:
    Vertex();
    Vertex(double x, double y, double z);
    double coordinates[3];
};

class Face {
public:
    Face();
    Face(const Vertex& v0, const Vertex& v1, const Vertex& v2);
    Vertex vertices[3];
};

class Mesh {
public:
    Mesh(const string& mesh_file);
    ~Mesh();
    void print_mesh();
    int n_faces;
    Face *faces;
};

class CameraMesh: public Mesh {
public:
    CameraMesh(const string& mesh_file, double theta_x, double theta_y, double theta_z, 
        double delta_x, double delta_y, double delta_z);
    ~CameraMesh();
    void print_camera_points();
    Matrix T;
    double ***camera_points;
};

#endif