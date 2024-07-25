#include "opencv2/opencv.hpp"
#include <iostream>

using namespace cv;
using namespace std;
String folder = "/home/aa/kdta_ROS2/opencv/data/";

int main()
{
    Mat src = imread(folder + "hawkes.bmp", IMREAD_GRAYSCALE);
    // src = src + (src - 125) * 1.0;
    Mat add, center, minmaxDst, dst;
    double gmin, gmax;

    add = src + 50;
    center = src + (src - 125) * 1.0;
    minMaxLoc(src, &gmin, &gmax);
    minmaxDst = (src - gmin) * 255 / (gmax - gmin);
    equalizeHist(src, dst);

    imshow("src", src);
    imshow("dst", dst);
    imshow("add", add);
    imshow("center", center);
    imshow("minmax", minmaxDst);
    waitKey(0);
    return 0;
}