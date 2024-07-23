#include "opencv2/opencv.hpp"
#include <iostream>

using namespace cv;

String folder = "/home/aa/kdta_ROS2/opencv/data/";

int main()
{
    // Point 예제
    Point pt1;
    // Point2i pt1;
    pt1.x = 5;
    pt1.y = 10;
    Point pt2(6, 7);
    std::cout << pt1 << std::endl;
    std::cout << pt2 << std::endl;

    // Size 에제
    Size sz1;
    sz1.height = 10;
    sz1.width = 20;
    Size sz2(50, 100);

    std::cout << sz1 << std::endl;
    std::cout << sz2 << std::endl;
    std::cout << sz1.area() << "size2: " << sz2.area() << std::endl;

    return 0;
}