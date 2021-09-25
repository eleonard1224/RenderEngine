// Header file with geometry class declarations
#ifndef GEOMETRY
#define GEOMETRY

#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <map>
#include "matrix.h"

using std::string;

class Vertex {
public:
    Vertex();
    Vertex(double x, double y, double z);
    //~Vertex();
    double coordinates[3];
};

class Face {
public:
    Face();
    Face(const Vertex& v0, const Vertex& v1, const Vertex& v2);
    //~Face();
    Vertex vertices[3];
};

class Mesh {
public:
    Mesh(const string& mesh_file);
    ~Mesh();
    string readFileIntoString(const string& path);
    void print_mesh();
    string mesh_file;
    int n_faces;
    Face *faces;
};

class CameraMesh: public Mesh {
public:
    CameraMesh(const string& mesh_file, double Rx, double Ry, double Rz, double Tx, double Ty, double Tz);
};

#endif