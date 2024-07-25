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
    Mat lennaimg = imread(folder + "lenna.bmp");
    Mat maskSmile = imread(folder + "mask_smile.bmp", IMREAD_GRAYSCALE);

    lennaimg.setTo(yellow, maskSmile);

    imshow("img", lennaimg);
    waitKey(0);

    Mat airplanImg = imread(folder + "airplane.bmp");
    Mat maskAirplan = imread(folder + "mask_plane.bmp", IMREAD_GRAYSCALE);
    Mat sky = imread(folder + "field.bmp");

    airplanImg.copyTo(sky, maskAirplan);

    imshow("img", sky);
    waitKey(0);

    return 0;
}