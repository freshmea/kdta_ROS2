#include "opencv2/opencv.hpp"
#include <iostream>

using namespace cv;
using namespace std;
String folder = "/home/aa/kdta_ROS2/opencv/data/";

int main()
{
    Mat img = imread(folder + "butterfly.jpg");

    for (int i = 0; i < 100; i++)
    {
        Vec3b &pixel = img.at<Vec3b>(i, i);
        uchar b1 = pixel[0];
        uchar g1 = pixel[0];
        uchar r1 = pixel[0];
        cout << pixel << endl;
        cout << b1 << g1 << r1 << endl;

        pixel[0] = 0;
        pixel[1] = 0;
        pixel[2] = 255;
        cout << pixel << endl;
    }

    imshow("img", img);
    waitKey(0);

    return 0;
}