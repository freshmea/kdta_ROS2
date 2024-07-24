#include "opencv2/opencv.hpp"
#include <iostream>

using namespace cv;
using namespace std;
String folder = "/home/aa/kdta_ROS2/opencv/data/";

int main()
{
    Mat frame, doubleFrame, reshapeFrame;
    VideoCapture cap(0);
    if (!cap.isOpened())
    {
        cerr << "Video open failed " << endl;
        return -1;
    }
    cout << "Video open" << endl;
    cap.release();
    return 0;
}