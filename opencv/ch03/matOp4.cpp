#include "opencv2/opencv.hpp"
#include <iostream>

using namespace cv;
using namespace std;

String folder = "/home/aa/kdta_ROS2/opencv/data/";

int main()
{
    // matrix Operation 2 pixel change
    Mat mat1 = Mat::zeros(3, 4, CV_8UC1);
    cout << "Before mat1 : " << endl
         << mat1 << endl;

    for (int j = 0; j < mat1.rows; j++)
    {
        for (int i = 0; i < mat1.cols; i++)
        {
            // mat1.at<uchar>(j, i)++;
            mat1.at<uchar>(j, i) = mat1.at<uchar>(j, i) + 1;
        }
    }
    cout << "After mat1 : " << endl
         << mat1 << endl;

    for (int j = 0; j < mat1.rows; j++)
    {
        uchar *p = mat1.ptr<uchar>(j);
        for (int i = 0; i < mat1.cols; i++)
        {
            p[i]++;
        }
    }
    cout << "After ptr mat1 : " << endl
         << mat1 << endl;

    for (auto it = mat1.begin<uchar>(); it != mat1.end<uchar>(); it++)
    {
        (*it)++;
    }
    cout << "After iterator mat1 : " << endl
         << mat1 << endl;

    return 0;
}