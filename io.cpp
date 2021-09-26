// Implementation of Input and Output classes
#include "io.h"


// Output definitions
void Output::write_to_file(const string& output_file, const Mat& img) {
    imwrite(output_file, img);
}