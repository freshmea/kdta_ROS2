#include "opencv2/opencv.hpp"
#include <iostream>

using namespace cv;
using namespace std;
String folder = "/home/aa/kdta_ROS2/opencv/data/";

int main()
{
    Mat src = imread(folder + "lenna.bmp", IMREAD_GRAYSCALE);
    src = src + (src - 125) * 1.0;
    Mat histo;
    int channels[] = {0};
    int dims = 1;
    const int histSize[] = {256};
    float graylevel[] = {0, 256};
    const float *ranges[] = {graylevel};

    calcHist(&src, 1, channels, noArray(), histo, dims, histSize, ranges);
    imshow("src", src);

    // make graph
    Mat graph(100, 256, CV_8U, Scalar(255));
    normalize(histo, histo, 0, 100, NORM_MINMAX);
    for (int i = 0; i < 256; i++)
    {
        line(graph, Point(i, 100), Point(i, 100 - cvRound(histo.at<float>(i))), Scalar(0));
    }

    imshow("graph", graph);
    waitKey(0);
    return 0;
}