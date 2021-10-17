// Implementations of geometry classes
#include "geometry.h"

// Vertex definitions
Vertex::Vertex() {
    coordinates[0] = 0.0; coordinates[1] = 0.0; coordinates[2] = 0.0;
}

Vertex::Vertex(double x, double y, double z) {
    coordinates[0] = x; coordinates[1] = y; coordinates[2] = z;
}

// Face Definitions
Face::Face() {
    Vertex v0, v1, v2;
    vertices[0] = v0; vertices[1] = v1; vertices[2] = v2;
}

Face::Face(const Vertex& v0, const Vertex& v1, const Vertex& v2) {
    vertices[0] = v0; vertices[1] = v1; vertices[2] = v2;
}
