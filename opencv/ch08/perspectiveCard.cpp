#include "opencv2/opencv.hpp"
#include <iostream>

using namespace cv;
using namespace std;

void onMouse(int event, int x, int y, int flags, void *data);
String folder = "/home/aa/kdta_ROS2/opencv/data/";

Mat src;
Point2f srcPts[4], dstPts[4];
void calculateCardProperties(const Mat &transformMatrix, const Size &originalSize)
{
    // Define the corners of the original image
    vector<Point2f> originalCorners = {
        Point2f(0, 0),
        Point2f(originalSize.width - 1, 0),
        Point2f(originalSize.width - 1, originalSize.height - 1),
        Point2f(0, originalSize.height - 1)};

    // Transform the corners using the inverse of the transform matrix
    Mat inverseMatrix;
    invert(transformMatrix, inverseMatrix);
    vector<Point2f> transformedCorners(4);
    perspectiveTransform(originalCorners, transformedCorners, inverseMatrix);

    // Calculate the center of the card
    Point2f center(0, 0);
    for (const auto &point : transformedCorners)
    {
        center += point;
    }
    center *= (1.0 / transformedCorners.size());

    // Calculate the angle of the card
    double angle = atan2(transformedCorners[1].y - transformedCorners[0].y, transformedCorners[1].x - transformedCorners[0].x) * 180.0 / CV_PI;

    // Calculate the distance from the origin (0, 0) to the center of the card
    double distance = sqrt(center.x * center.x + center.y * center.y);

    // Output the results
    cout << "Center: " << center << endl;
    cout << "Angle: " << angle << " degrees" << endl;
    cout << "Distance from origin: " << distance << endl;
}

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
                calculateCardProperties(M, dst.size());
                cnt = 0;
            }
        }
    }
}