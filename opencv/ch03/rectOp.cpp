#include "opencv2/opencv.hpp"
#include <iostream>

using namespace cv;

String folder = "/home/aa/kdta_ROS2/opencv/data/";

int main()
{
    // Rect 예제
    Rect rc1;
    rc1.x = 1;
    rc1.y = 1;
    rc1.width = 10;
    rc1.height = 10;
    Rect rc2(20, 30, 500, 400);

    std::cout << rc2.tl() << std::endl;
    std::cout << rc2.br() << std::endl;

    // RotatedRect 예제
    Point pt1(10, 20);
    Size sz1(100, 100);
    RotatedRect rr1(pt1, sz1, 30);
    Point2f pts[4];
    rr1.points(pts);
    std::cout << pts[0] << std::endl;
    std::cout << pts[1] << std::endl;
    std::cout << pts[2] << std::endl;
    std::cout << pts[3] << std::endl;

    return 0;
}