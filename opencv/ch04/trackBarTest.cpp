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
    Mat img = imread(folder + "lenna.bmp");
    int a = 0;

    namedWindow("img");
    createTrackbar("level", "img", &a, 255);
    while (true)
    {
        line(img, Point(0, 0), Point(a, a), red, 3);
        imshow("img", img);
        cout << a << endl;
        if (waitKey(100) == 27)
            break;
    }
    destroyAllWindows();
    return 0;
}
