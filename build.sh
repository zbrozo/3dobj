#g++ main.cpp generators.cpp object3d.cpp rotation.cpp -o main.exe
	
g++ main.cpp face.cpp cube.cpp thorus.cpp object3d.cpp rotation.cpp -o main.exe `sdl2-config --libs --cflags` -lSDL2_image -o sdl.exe

