#include "opencv2/opencv.hpp"
#include <iostream>

using namespace cv;
using namespace std;
String folder = "/home/aa/kdta_ROS2/opencv/data/";

int main()
{
    Mat src = imread(folder + "tekapo.bmp");
    Point2f srcPts[3], dstPts[3];
    // srcPts[0] = Point2f(0, 0);
    // srcPts[1] = Point2f(1, 0);
    // srcPts[2] = Point2f(1, 1);
    // dstPts[0] = Point2f(0, 0);
    // dstPts[1] = Point2f(2, 0);
    // dstPts[2] = Point2f(2, 2);
    srcPts[0] = Point2f(0, 0);
    srcPts[1] = Point2f(src.cols - 1, 0);
    srcPts[2] = Point2f(src.cols - 1, src.rows - 1);
    dstPts[0] = Point2f(50, 50);
    dstPts[1] = Point2f(src.cols - 1 + 50, 50);
    dstPts[2] = Point2f(src.cols - 1 + 50, src.rows - 1 + 50);

    Mat M = getAffineTransform(srcPts, dstPts);
    M.at<double>(0, 2) += 100;
    cout << M << endl;
    Mat dst;

    Size sz1 = src.size();
    warpAffine(src, dst, M, sz1);

    imshow("src", src);
    imshow("dst", dst);
    waitKey(0);
    return 0;
}