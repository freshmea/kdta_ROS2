#include "opencv2/opencv.hpp"
#include <iostream>

using namespace cv;
using namespace std;
String folder = "/home/aa/kdta_ROS2/opencv/data/";

int main()
{
    Mat src = imread(folder + "rose.bmp", IMREAD_GRAYSCALE);
    vector<Mat> dsts;

    for (int ksize = 3; ksize <= 19; ksize += 2)
    {
        Mat dst;
        blur(src, dst, Size(ksize, ksize));
        dsts.push_back(dst);
    }

    imshow("src", src);
    // for (int i = 0; i < dsts.size(); i++)
    int i = 3;
    for (auto dst : dsts)
    {
        imshow("dst" + to_string(i), dst);
        i += 2;
    }
    waitKey(0);
    return 0;
}