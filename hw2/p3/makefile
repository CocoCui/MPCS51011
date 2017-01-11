p3: p3.c
	gcc-6 p3.c -o p3 -std=c99 -fopenmp

viewer: viewer.cpp
	g++ -O3 viewer.cpp -o viewer -I/usr/local/include/opencv -I/usr/local/include -L/usr/local/lib -lopencv_calib3d -lopencv_contrib -lopencv_core -lopencv_highgui -lopencv_imgproc
