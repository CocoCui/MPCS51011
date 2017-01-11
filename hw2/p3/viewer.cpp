#include <cv.h>
#include <highgui.h>
#include <fstream>
#include <map>
#include <vector>
#include <sstream>

using namespace cv;
using namespace std;

void genpng(string input) {
    string i = input + ".txt", o = input + ".png";
    ifstream fin(i.c_str());
    int DIM, MAX_ITER;
    fin >> DIM;
    fin >> MAX_ITER;
    double pix, red, green, blue;
	Mat img(DIM, DIM, CV_8UC3);
	for(int i = 0; i < DIM; i++)
        for(int j = 0; j < DIM; j++) {
            fin >> pix;
            if(pix != MAX_ITER) {
                red = log(pix) * 0.9f / log(MAX_ITER) * 255 ;
                green = log(pix) * 0.3f / log(MAX_ITER) * 255;
                blue = log(pix) * 0.6f / log(MAX_ITER) * 255;
            } else {
                red = green = blue = 0;
            }
            img.at<Vec3b>(i, j) = Vec3b(blue, green, red);
        }
    imwrite(o.c_str(), img);
    fin.close();
}
int main( int argc, char** argv ){
    genpng("results");
    return 0;
}
