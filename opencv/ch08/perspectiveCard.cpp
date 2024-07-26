#include "opencv2/opencv.hpp"
#include <iostream>

using namespace cv;
using namespace std;

void onMouse(int event, int x, int y, int flags, void *data);
String folder = "/home/aa/kdta_ROS2/opencv/data/";

Mat src;
Point2f srcPts[4], dstPts[4];

int main()
{
    src = imread(folder + "card.bmp");

    namedWindow("src");
    setMouseCallback("src", onMouse);

    imshow("src", src);
    waitKey(0);
    destroyAllWindows();
    return 0;
}

void onMouse(int event, int x, int y, int flags, void *data)
{
    static int cnt = 0;
    switch (event)
    {
    case EVENT_LBUTTONDOWN:
        if (cnt < 4)
        {
            srcPts[cnt++] = Point2f(x, y);
            circle(src, Point(x, y), 5, Scalar(0, 0, 255), -1);
            imshow("src", src);
            if (cnt == 4)
            {
                int w = 200, h = 300;
                dstPts[0] = Point2f(0, 0);
                dstPts[1] = Point2f(w - 1, 0);
                dstPts[2] = Point2f(w - 1, h - 1);
                dstPts[3] = Point2f(0, h - 1);

                Mat M = getPerspectiveTransform(srcPts, dstPts);
                Mat dst;
                warpPerspective(src, dst, M, Size(w, h));
                imshow("dst", dst);
                cnt = 0;
            }
        }
    }
}