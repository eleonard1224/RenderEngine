// Implementation of Input and Output classes
#include "io.h"

// Input definitions
void Input::read_inputs(const string& input_file, string& mesh_file, double& Rx, double& Ry, double& Rz, 
    double& Tx, double& Ty, double& Tz, string& output_file, double& canvas_width, double& canvas_height, 
    int& pixel_width, int& pixel_height) {

    // Read mesh information into csv_contents
    string filename(input_file);
    string file_contents;
    std::map<int, std::vector<string>> csv_contents;
    char delimiter = ':';

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
    
    // Load in inputs
    mesh_file = csv_contents[0][1];
    Rx = std::stod(csv_contents[1][1]);
    Ry = std::stod(csv_contents[2][1]);
    Rz = std::stod(csv_contents[3][1]);
    Tx = std::stod(csv_contents[4][1]);
    Ty = std::stod(csv_contents[5][1]);
    Tz = std::stod(csv_contents[6][1]);
    output_file = csv_contents[7][1];
    canvas_width = std::stod(csv_contents[8][1]);
    canvas_height = std::stod(csv_contents[9][1]);
    pixel_width = std::stoi(csv_contents[10][1]);
    pixel_height = std::stoi(csv_contents[11][1]);
}

std::map<int, std::vector<string>> Input::read_mesh(const string& mesh_file) {

    // Read mesh information into csv_contents
    string filename(mesh_file);
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
    return csv_contents;
}

string Input::readFileIntoString(const string& path)  {
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

// Output definitions
void Output::write_img_file(const string& output_file, const Mat& img) {
    imwrite(output_file, img);
}