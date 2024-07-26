#include "opencv2/opencv.hpp"
#include <iostream>

using namespace cv;
using namespace std;
String folder = "/home/aa/kdta_ROS2/opencv/data/";

int main()
{
    Mat img = imread(folder + "building.jpg", IMREAD_GRAYSCALE);
    Mat dst1, dst2;

    Mat edge;
    Canny(img, edge, 50, 150);

    vector<Vec2f> lines;
    HoughLines(edge, lines, 1, CV_PI / 100, 230);

    Point pt1, pt2;
    for (size_t i = 0; i < lines.size(); i++)
    {
        float rho = lines[i][0], theta = lines[i][1];
        float x0 = rho * cos(theta), y0 = rho * sin(theta);
        float x1000 = 1000 * (-sin(theta));
        float y1000 = 1000 * cos(theta);
        pt1.x = cvRound(x0 - x1000);
        pt1.y = cvRound(y0 - y1000);
        pt2.x = cvRound(x0 + x1000);
        pt2.y = cvRound(y0 + y1000);
        line(img, pt1, pt2, Scalar(255), 2);
    }

    imshow("img", img);
    imshow("dst1", edge);
    waitKey(0);

    return 0;
}