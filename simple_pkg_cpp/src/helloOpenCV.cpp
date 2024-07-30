#include "opencv2/opencv.hpp"

using namespace cv;

int main()
{
    Mat img(500, 500, CV_8UC1, Scalar(0));
    putText(img, "Hello, OpenCV!", Point(50, 250), FONT_HERSHEY_SIMPLEX, 1, Scalar(255), 2);
    imshow("img", img);
    waitKey(0);
    return 0;
}