#include "opencv2/opencv.hpp"
#include <iostream>

using namespace cv;
using namespace std;
String folder = "/home/aa/kdta_ROS2/opencv/data/";

int main()
{
    Mat src = imread(folder + "tekapo.bmp");
    Point2f srcPts[4], dstPts[4];
    srcPts[0] = Point2f(0, 0);
    srcPts[1] = Point2f(src.cols - 1, 0);
    srcPts[2] = Point2f(src.cols - 1, src.rows - 1);
    srcPts[3] = Point2f(0, src.rows - 1);
    dstPts[0] = Point2f(150, 50);
    dstPts[1] = Point2f(src.cols - 1 - 50, 150);
    dstPts[2] = Point2f(src.cols - 1 - 250, src.rows - 1 - 50);
    dstPts[3] = Point2f(50, src.rows - 1 + 150);

    Mat M = getPerspectiveTransform(srcPts, dstPts);
    cout << M << endl;
    Mat dst;
    warpPerspective(src, dst, M, Size());

    imshow("src", src);
    imshow("dst", dst);
    waitKey(0);
    return 0;
}