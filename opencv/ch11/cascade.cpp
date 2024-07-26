#include "opencv2/opencv.hpp"
#include <iostream>

using namespace cv;
using namespace std;
String folder = "/home/aa/kdta_ROS2/opencv/data/";

int main()
{
    Mat img = imread(folder + "kids.png");
    CascadeClassifier classifier(folder + "haarcascade_frontalface_default.xml");
    vector<Rect> face;
    classifier.detectMultiScale(img, face);

    for (auto rect : face)
    {
        rectangle(img, rect, Scalar(0, 0, 255), 3);
    }
    imshow("img", img);
    waitKey(0);
    return 0;
}