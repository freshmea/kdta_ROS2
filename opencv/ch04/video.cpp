#include "opencv2/opencv.hpp"
#include <iostream>

using namespace cv;
using namespace std;
String folder = "/home/aa/kdta_ROS2/opencv/data/";

int main()
{
    Mat frame, doubleFrame, reshapeFrame;
    VideoCapture cap(folder + "vtest.avi");
    // VideoCapture cap(0, CAP_V4L2);
    double fps = cap.get(CAP_PROP_FPS);
    int delay = cvRound(1000 / fps);

    // open check
    if (!cap.isOpened())
    {
        cerr << "Video open failed " << endl;
        return -1;
    }
    cout << "Video open" << endl;

    // frame image show
    while (true)
    {
        cap >> frame;
        imshow("frame", frame);
        if (waitKey(delay) == 27)
            break;
    }
    cap.release();
    return 0;
}