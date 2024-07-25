#include "opencv2/opencv.hpp"
#include <iostream>

using namespace cv;
using namespace std;
String folder = "/home/aa/kdta_ROS2/opencv/data/";

int main()
{
    Mat src = imread(folder + "rose.bmp", IMREAD_GRAYSCALE);
    vector<Mat> dsts;

    for (int sigma = 1; sigma <= 19; sigma += 1)
    {
        Mat dst;
        GaussianBlur(src, dst, Size(0, 0), sigma);
        dsts.push_back(dst);
    }

    imshow("src", src);
    int i = 1;
    for (auto dst : dsts)
    {
        imshow("dst" + to_string(i), dst);
        i += 1;
    }
    waitKey(0);
    return 0;
}