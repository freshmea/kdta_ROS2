#include "opencv2/opencv.hpp"
#include <iostream>

using namespace cv;
using namespace std;
String folder = "/home/aa/kdta_ROS2/opencv/data/";

int main()
{
    Mat img = imread(folder + "neutrophils.png", IMREAD_GRAYSCALE);
    Mat dst;
    // threshold(img, dst, 180, 255, THRESH_BINARY);
    threshold(img, dst, 0, 255, THRESH_OTSU);

    imshow("img", img);
    imshow("dst", dst);
    waitKey(0);
    return 0;
}