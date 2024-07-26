#include "opencv2/opencv.hpp"
#include <iostream>

using namespace cv;
using namespace std;
String folder = "/home/aa/kdta_ROS2/opencv/data/";

int main()
{
    VideoCapture cap(folder + "vtest.avi");

    HOGDescriptor hog;
    hog.setSVMDetector(HOGDescriptor::getDefaultPeopleDetector());
    Mat frame;
    while (true)
    {
        cap >> frame;
        vector<Rect> detected;
        hog.detectMultiScale(frame, detected);
        for (auto re : detected)
        {
            rectangle(frame, re, Scalar(0, 0, 255), 3);
        }
        imshow("frame", frame);
        if (waitKey(100) == 27)
            break;
    }
    return 0;
}