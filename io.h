// Header file for Input and Output classes
#ifndef INPUT_OUTPUT
#define INPUT_OUTPUT

#include <iostream>
#include <cmath>
#include <fstream>
#include <vector>
#include <sstream>
#include <map>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui/highgui.hpp>
using namespace std;
using namespace cv;

class Input {
public:
    std::map<int, std::vector<string>> read_mesh(const string& mesh_file);
    string readFileIntoString(const string& path);
};

class Output {
public:
    void write_img_file(const string& output_file, const Mat& img);
};

#endif