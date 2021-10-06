# RenderEngine
This repository contains code for a very basic render engine which displays the outlines of a mesh composed of triangular faces.  A sample render of a monkey mesh specified in `meshes/monkey.csv` is displayed in `monkey.png` while a render of the same mesh in Blender is displayed in `blender_monkey.png`.  A sample inputs file for the render engine is contained in `inputs.csv`.  For the compile instructions below the include path to opencv might have to be adjusted depending on the location of the opencv library.

The render engine incorporates multithreading on Lines 36-59 of `camera.cpp`.  To measure the speed-ups from multithreading, a high-poly version of the monkey mesh is stored in `meshes/monkey_high_polycount.csv` and the number of threads launched can be adjusted on Line 38 of `camera.cpp`.

## Compile Instructions
`g++-7 main.cpp geometry.cpp matrix.cpp camera.cpp io.cpp -std=c++17 -o renderengine -I/usr/include/opencv4/ -lopencv_core -lopencv_imgproc -lopencv_highgui -lopencv_imgcodecs -pthread`

## Run Instructions
`./renderengine inputs.csv`