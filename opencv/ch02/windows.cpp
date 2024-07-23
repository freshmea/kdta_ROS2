#include "opencv2/opencv.hpp"
#include <iostream>
using namespace std;
using namespace cv;

string folder = "/home/aa/kdta_ROS2/opencv/data/";

int main()
{
    Mat img;
    img = imread(folder + "lena.bmp");
    namedWindow("lena");
    imshow("lena", img);
    int key = waitKey(0);
    cout << key << endl;
    Size size;
    size.height = 100;
    size.width = 100;
    resizeWindow("lena", size);
    waitKey(0);
    return 0;
}