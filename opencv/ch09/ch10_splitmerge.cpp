#include "opencv2/opencv.hpp"
#include <iostream>

using namespace cv;
using namespace std;
String folder = "/home/aa/kdta_ROS2/opencv/data/";

int main()
{
    Mat img = imread(folder + "candies.png");

    vector<Mat> bgr, b_planes, g_planes, r_planes;
    split(img, bgr);

    Mat empty(img.rows, img.cols, CV_8UC1, Scalar(0));
    b_planes = {bgr[0], empty, empty};
    g_planes = {empty, bgr[1], empty};
    r_planes = {empty, empty, bgr[2]};

    Mat bDst, gDst, rDst;
    merge(b_planes, bDst);
    merge(g_planes, gDst);
    merge(r_planes, rDst);

    imshow("img", img);
    imshow("bimg", bDst);
    imshow("gimg", gDst);
    imshow("rimg", rDst);
    waitKey(0);

    return 0;
}