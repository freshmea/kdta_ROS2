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
    while (waitKey(0) != -1)
    {
        // int key = waitKey(0);
        cout << "aaa" << endl;
        moveWindow("lena", 50, 0);
    }
    return 0;
}