# terrain-whacamole
Graphics simulation of a terrain with an island with snowy peaks in a sea implemented using a height map. 
Part of Graphics assignment for Computer Graphics course at RIT, Bangalore.

# To run the Simulation on linux:
Libraries to install:
SOIL (Simple-OpenGL-Image-Library), FreeImage, CMAKE 

# Steps to install packages:
Open the ubuntu terminal and paste the following:
1. sudo apt-get install freeglut3-dev
2. sudo apt-get install libfreeimage-dev
3. sudo apt-get install libglew-dev
4. sudo apt-get install libsoil-dev
5. sudo apt-get install libpthread-stubs0-dev
6. sudo apt-get install libglfw3-dev

# To run main.cpp: 
Open the ubuntu terminal and paste the following:
g++ -std=c++11 main.cpp -o test -lSOIL -lGLEW -lglfw -lGL -lX11 -lXi -lXrandr -lXxf86vm -lXinerama -lXcursor -lrt -lm -pthread

# Simulation Controls: 
1. K,L keys to start/stop rotation.
2. Up, Down arrow keys for increasing/decreasing the height of terrain.
