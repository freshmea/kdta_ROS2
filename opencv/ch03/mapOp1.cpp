#include "opencv2/opencv.hpp"
#include <iostream>

using namespace cv;

String folder = "/home/aa/kdta_ROS2/opencv/data/";

int main()
{
    // matrix Operation 1 생성자 예제
    Mat img1;
    img1 = Scalar(10, 0, 0);
    Mat img2(400, 600, CV_8UC1);
    Mat img3(400, 600, CV_8UC3);
    Mat img4(Size(500, 500), CV_8UC3);

    Mat img5(300, 400, CV_8UC1, Scalar(0));
    Mat img6(300, 400, CV_8UC1, Scalar(255));

    imshow("img2", img2);
    imshow("img3", img3);
    imshow("img4", img4);
    imshow("img5", img5);
    imshow("img6", img6);
    waitKey(0);

    return 0;
}