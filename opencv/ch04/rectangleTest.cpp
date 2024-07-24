#include "opencv2/opencv.hpp"
#include <iostream>

using namespace cv;
using namespace std;
String folder = "/home/aa/kdta_ROS2/opencv/data/";

int main()
{
    Scalar white = Scalar(255, 255, 255);
    Scalar yellow = Scalar(0, 255, 255);
    Scalar blue = Scalar(255, 0, 0);
    Scalar green = Scalar(0, 255, 0);
    Scalar red = Scalar(0, 0, 255);
    Mat img(400, 600, CV_8UC3, Scalar(255, 255, 255));

    rectangle(img, Rect(50, 50, 100, 70), red, 2);
    rectangle(img, Point(50, 50), Point(100, 70), blue, 2);

    circle(img, Point(300, 120), 30, green, -1, LINE_AA);
    circle(img, Point(350, 120), 30, yellow, 3, LINE_AA);

    ellipse(img, Point(120, 200), Size(60, 30), 20, 0, 300, red, FILLED, LINE_AA);

    imshow("img", img);
    waitKey(0);

    return 0;
}