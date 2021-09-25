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

CameraMesh::CameraMesh(const string& mesh_file, double theta_x, double theta_y, double theta_z, 
    double delta_x, double delta_y, double delta_z): Mesh(mesh_file), T(4,4) {

    // Have to create camera transformation matrix T
    // Construct the rotation matrices
    Matrix Rx(3,3);
    Rx[0][0] = 1.0; Rx[0][1] = 0.0; Rx[0][2] = 0.0;
    Rx[1][0] = 0.0; Rx[1][1] = cos(theta_x); Rx[1][2] = -1.0*sin(theta_x);
    Rx[2][0] = 0.0; Rx[2][1] = sin(theta_x); Rx[2][2] = cos(theta_x);

    Matrix Ry(3,3);
    Ry[0][0] = cos(theta_y); Ry[0][1] = 0.0; Ry[0][2] = sin(theta_y);
    Ry[1][0] = 0.0; Ry[1][1] = 1.0; Ry[1][2] = 0.0;
    Ry[2][0] = -1.0*sin(theta_y); Ry[2][1] = 0.0; Ry[2][2] = cos(theta_y);

    Matrix Rz(3,3);
    Rz[0][0] = cos(theta_z); Rz[0][1] = -1.0*sin(theta_z); Rz[0][2] = 0.0;
    Rz[1][0] = sin(theta_z); Rz[1][1] = cos(theta_z); Rz[1][2] = 0.0;
    Rz[2][0] = 0.0; Rz[2][1] = 0.0; Rz[2][2] = 1.0;

    Matrix R = Rx*Ry*Rz;
    // R.print_matrix();

    // Fill in camera transformation matrix T
    // int i, j;
    T[0][0] = R[0][0]; T[0][1] = R[0][1]; T[0][2] = R[0][2]; T[0][3] = delta_x;
    T[1][0] = R[1][0]; T[1][1] = R[1][1]; T[1][2] = R[1][2]; T[1][3] = delta_y;
    T[2][0] = R[2][0]; T[2][1] = R[2][1]; T[2][2] = R[2][2]; T[2][3] = delta_z;
    T[3][0] = 0.0; T[3][1] = 0.0; T[3][2] = 0.0; T[3][3] = 1.0;
    // for(i = 0; i < 4; i++) {
    //     for(j = 0; j < 4; j++) {
    //         if(abs(T[i][j]) < 1.0e-10) {
    //             T[i][j] = 0.0;
    //         }
    //     }
    // }
    // T.print_matrix();



    // Transform the vertices of the mesh from world space to camera space
    Matrix Tinv = inverse(T);
    // Tinv.print_matrix();
    // Matrix Plocal(1,M.n_cols);
    Matrix Pworld(T.n_rows,1);
    // Loop through vertices and transform them from world coordinates to local coordinates
    int i, j;
    for(i = 0; i < n_faces; i++) {
        for(j = 0; j < 3; j++) {
            Pworld[0][0] = faces[i].vertices[j].coordinates[0];
            Pworld[1][0] = faces[i].vertices[j].coordinates[1];
            Pworld[2][0] = faces[i].vertices[j].coordinates[2];
            Pworld[3][0] = 1.0;
            Matrix Plocal = Tinv*Pworld;
            faces[i].vertices[j].coordinates[0] = Plocal[0][0];
            faces[i].vertices[j].coordinates[1] = Plocal[1][0];
            faces[i].vertices[j].coordinates[2] = Plocal[2][0];
        }
    }

    // Allocate memory for camera_points
    camera_points = new double**[n_faces];
    for(i = 0; i < n_faces; i++) {
        camera_points[i] = new double*[3];
        for(j = 0; j < 3; j++) {
            camera_points[i][j] = new double[2];
        }
    }
    // Fill in camera_points
    for(i = 0; i < n_faces; i++) {
        for(j = 0; j < 3; j++) {
            camera_points[i][j][0] = faces[i].vertices[j].coordinates[0]/(-1.0*faces[i].vertices[j].coordinates[2]);
            camera_points[i][j][1] = faces[i].vertices[j].coordinates[1]/(-1.0*faces[i].vertices[j].coordinates[2]);
        }
    }
}

CameraMesh::~CameraMesh() {
    int i, j;
    for(i = 0; i < n_faces; i++) {
        for(j = 0; j < 3; j++) {
            delete[] camera_points[i][j];
        }
        delete[] camera_points[i];
    }
    delete[] camera_points;
}

void CameraMesh::print_camera_points() {

    int i, j;
    for(i = 0; i < n_faces; i++) {
        for(j = 0; j < 3; j++) {
            cout << "Scaled Face " << i << ", "
            << "Vertex " << j << " = ("
            << camera_points[i][j][0] << ", "
            << camera_points[i][j][1] << ")" << endl;
        }
    }  
}