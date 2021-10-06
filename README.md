# RenderEngine
This repository contains code for a very basic render engine which displays the outlines of a mesh composed of triangular faces.  A sample render of a monkey is displayed in `monkey.png` while a render of the same mesh in Blender is displayed in `blender_monkey.png`.  A sample inputs file for the render engine is contained in `inputs.csv`.  For the compile instructions below the include path to opencv might have to be adjusted depending on the location of the opencv library.

## Compile Instructions
`g++-7 main.cpp geometry.cpp matrix.cpp camera.cpp io.cpp -std=c++17 -o renderengine -I/usr/include/opencv4/ -lopencv_core -lopencv_imgproc -lopencv_highgui -lopencv_imgcodecs -pthread`

## Run Instructions
`./renderengine inputs.csv`