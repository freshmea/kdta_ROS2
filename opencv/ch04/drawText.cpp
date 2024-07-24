#include "opencv2/freetype.hpp"
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
    Mat img(400, 600, CV_8UC3, Scalar(255, 255, 255));

    Ptr<freetype::FreeType2> ft2 = freetype::createFreeType2(); // smart pointer
    // ft2->loadFontData("/usr/share/fonts/truetype/nanum/NanumGothic.ttf", 0); // 개인사정에 맞게
    ft2->loadFontData("/usr/share/fonts/truetype/nanum/NanumGothic.ttf", 0); // 개인사정에 맞게
    String text = u8"안녕하세요. utf-8 텍스트입니다.";
    int fontHeight = 60;
    Size textSize = ft2->getTextSize(text, fontHeight, -1, 0);

    putText(img, "FONT_HERSHEY_SIMPLEX", Point(20, 50), FONT_HERSHEY_SIMPLEX, 1, green);
    putText(img, "폰트 한글 써질까요?", Point(20, 150), FONT_HERSHEY_PLAIN, 1, red);

    ft2->putText(img, text, Point(20, 250), fontHeight, red, -1, LINE_AA, true);

    imshow("img", img);
    waitKey(0);

    return 0;
}