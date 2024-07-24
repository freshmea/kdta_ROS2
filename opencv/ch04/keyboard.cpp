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
    Mat img2;
    int keycode;

    namedWindow("img");
    imshow("img", img);
    int fps = 30;
    int delay = cvRound(1000 / 30);
    Scalar a(0, 0, 0);

    while (true)
    {
        keycode = waitKey(delay);
        if (keycode != -1)
            cout << "keycode: " << keycode << endl;
        if (keycode == 27)
            break;
        if (keycode == 'i' || keycode == 'I')
        {
            img = ~img;
            imshow("img", img);
        }
        if (keycode == 'a' || keycode == 'A')
        {
            a = a + Scalar(1, 1, 1);
            img2 = img + a;
            imshow("img", img2);
        }
        if (keycode == 'b' || keycode == 'B')
        {
            a = a - Scalar(1, 1, 1);
            img2 = img + a;
            imshow("img", img2);
        }
    }

    return 0;
}