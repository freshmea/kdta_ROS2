#include "opencv2/opencv.hpp"
#include <iostream>
#include <string>

std::string folder = "/home/aa/kdta_ROS2/opencv/first/";

int main()
{
    std::cout << "hello, world" << std::endl;
    cv::Mat img;
    img = cv::imread(folder + "lena.bmp");
    cv::imshow("image", img);
    cv::waitKey(0);
    return 0;
}