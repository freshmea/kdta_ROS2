#include "opencv2/opencv.hpp"
#include <iostream>

using namespace cv;

String folder = "/home/aa/kdta_ROS2/opencv/data/";

int main()
{
    // matrix Operation 2 roi
    Mat img1 = imread(folder + "lena.bmp");
    Rect rc(220, 120, 200, 200);
    Mat img2 = img1(rc);         // roi
    Mat img3 = img1(rc).clone(); // 새로운 이미지

    img2 = ~img2;
    // img2.setTo(Scalar(0, 255, 255));

    imshow("img1", img1);
    imshow("img2", img2);
    imshow("img3", img3);
    waitKey(0);

    return 0;
}