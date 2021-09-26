// Header file for Input and Output classes
#ifndef INPUT_OUTPUT
#define INPUT_OUTPUT

#include <iostream>
#include <cmath>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui/highgui.hpp>
using namespace std;
using namespace cv;

class Output {
public:
    void write_to_file(const string& output_file, const Mat& img);
};

#endif