// Implementations of geometry classes
#include "geometry.h"

using namespace std;

// Vertex definitions
Vertex::Vertex() {
    // cout << "Default Vertex Constructor" << endl;
    coordinates[0] = 0.0; coordinates[1] = 0.0; coordinates[2] = 0.0;
}

Vertex::Vertex(double x, double y, double z) {
    // cout << "Vertex Constructor" << endl;
    coordinates[0] = x; coordinates[1] = y; coordinates[2] = z;
}

// Vertex::~Vertex() {
//     cout << "Vertex Destructor" << endl;
// }

// Face Definitions
Face::Face() {
    Vertex v0, v1, v2;
    vertices[0] = v0; vertices[1] = v1; vertices[2] = v2;
}

Face::Face(const Vertex& v0, const Vertex& v1, const Vertex& v2) {
    // cout << "Face Constructor" << endl;
    vertices[0] = v0; vertices[1] = v1; vertices[2] = v2;
}

// Face::~Face() {
//     cout << "Face Destructor Called" << endl;
// }

// Mesh definitions
Mesh::Mesh(const string& mesh_file): mesh_file(mesh_file) {

    // Read mesh information into csv_contents
    string filename(this->mesh_file);
    string file_contents;
    std::map<int, std::vector<string>> csv_contents;
    char delimiter = ',';

    file_contents = readFileIntoString(filename);

    istringstream sstream(file_contents);
    std::vector<string> items;
    string record;

    int counter = 0;
    while (std::getline(sstream, record)) {
        istringstream line(record);
        while (std::getline(line, record, delimiter)) {
            items.push_back(record);
        }

        csv_contents[counter] = items;
        items.clear();
        counter += 1;
    }

    // Now read mesh information into faces
    n_faces = csv_contents.size();
    // cout << "n_faces = " << n_faces << endl;
    // faces = NULL;
    faces = new Face[n_faces];
    int i, j;
    for(i = 0; i < n_faces; i++) {
        for(j = 0; j < 3; j++) {
            faces[i].vertices[j].coordinates[0] = std::stod(csv_contents[i][3*j]);
            faces[i].vertices[j].coordinates[1] = std::stod(csv_contents[i][3*j+1]);
            faces[i].vertices[j].coordinates[2] = std::stod(csv_contents[i][3*j+2]);
        }
    }

}

Mesh::~Mesh() {
    delete[] faces;
}

string Mesh::readFileIntoString(const string& path)  {
    auto ss = ostringstream{};
    ifstream input_file(path);
    if (!input_file.is_open()) {
        cerr << "Could not open the file - '"
             << path << "'" << endl;
        exit(EXIT_FAILURE);
    }
    ss << input_file.rdbuf();
    return ss.str();
}

void Mesh::print_mesh() {

    int i, j;
    for(i = 0; i < n_faces; i++) {
        for(j = 0; j < 3; j++) {
            cout << "Face " << i << ", "
            << "Vertex " << j << " = ("
            << faces[i].vertices[j].coordinates[0] << ", "
            << faces[i].vertices[j].coordinates[1] << ", "
            << faces[i].vertices[j].coordinates[2] << ")" << endl;
        }
    }
}

// CameraMesh definitions
// CameraMesh::CameraMesh(const string& mesh_file, const Matrix& M): Mesh(mesh_file) {

//     Matrix Minv = inverse(M);
//     // Matrix Plocal(1,M.n_cols);
//     Matrix Pworld(M.n_rows,1);
//     // Loop through vertices and transform them from world coordinates to local coordinates
//     int i, j;
//     for(i = 0; i < n_faces; i++) {
//         for(j = 0; j < 3; j++) {
//             Pworld[0][0] = faces[i].vertices[j].coordinates[0];
//             Pworld[1][0] = faces[i].vertices[j].coordinates[1];
//             Pworld[2][0] = faces[i].vertices[j].coordinates[2];
//             Pworld[3][0] = 0;
//             Matrix Plocal = Minv*Pworld;
//             faces[i].vertices[j].coordinates[0] = Plocal[0][0];
//             faces[i].vertices[j].coordinates[1] = Plocal[1][0];
//             faces[i].vertices[j].coordinates[2] = Plocal[2][0];
//         }
//     }
// }

CameraMesh::CameraMesh(const string& mesh_file, double Rx, double Ry, double Rz, double Tx, double Ty, double Tz): Mesh(mesh_file) {


}