# RenderEngine
This repository contains code for a very basic render engine which displays the outlines of a mesh composed of triangular faces.  A sample render of a monkey mesh specified in `meshes/monkey.csv` is displayed in `monkey.png` while a render of the same mesh in Blender is displayed in `blender_monkey.png`.  A sample inputs file for the render engine is contained in `inputs.csv`.  For the compile instructions below the include path to opencv might have to be adjusted depending on the location of the opencv library.

`mesh.h` defines class templates for mesh classes which include the use of a vector container to store face information (Line 25 of `mesh.h`). 

The render engine incorporates multithreading on Lines 62-85 of `camera.h`.  To measure the speed-ups from multithreading, a high-poly version of the monkey mesh is stored in `meshes/monkey_high_polycount.csv` and the number of threads launched can be adjusted on Line 64 of `camera.h`.

## Compile Instructions
`g++ main.cpp geometry.cpp matrix.cpp io.cpp -std=c++17 -o renderengine -I/usr/include/opencv4/ -lopencv_core -lopencv_imgproc -lopencv_highgui -lopencv_imgcodecs -pthread`

## Run Instructions
`./renderengine inputs.csv`