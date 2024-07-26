#include "opencv2/opencv.hpp"
#include <iostream>

using namespace cv;
using namespace std;
String folder = "/home/aa/kdta_ROS2/opencv/data/";

int main()
{
    // Mat img = imread(folder + "neutrophils.png", IMREAD_GRAYSCALE);
    Mat img = imread(folder + "sudoku.jpg", IMREAD_GRAYSCALE);
    Mat dst, dst2;
    threshold(img, dst2, 100, 255, THRESH_BINARY);
    adaptiveThreshold(img, dst, 255, ADAPTIVE_THRESH_MEAN_C, THRESH_BINARY, 33, 5);

    imshow("img", img);
    imshow("dst", dst);
    imshow("dst2", dst2);
    waitKey(0);
    return 0;
}