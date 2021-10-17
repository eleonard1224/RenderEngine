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
using namespace std;
using std::string;

////////////////////  Class Declarations /////////////////////////////////////

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

#endif