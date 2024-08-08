#include "cv_bridge/cv_bridge.h"
#include "opencv2/opencv.hpp"
#include "rclcpp/rclcpp.hpp"
#include "sensor_msgs/msg/image.hpp"
#include <chrono>
#include <iostream>

using namespace std;
using namespace std::chrono_literals;

class CannyCamera : public rclcpp::Node
{
public:
    CannyCamera()
        : Node("canny_camera")
    {
        auto qos_profile = rclcpp::QoS(rclcpp::KeepLast(10));
        _sub = create_subscription<sensor_msgs::msg::Image>("camera1/image_raw", qos_profile, std::bind(&CannyCamera::sub_img, this, std::placeholders::_1));
    }

private:
    rclcpp::Subscription<sensor_msgs::msg::Image>::SharedPtr _sub;
    void sub_img(const sensor_msgs::msg::Image msg)
    {
        cv_bridge::CvImagePtr cv_ptr;
        cv_ptr = cv_bridge::toCvCopy(msg, sensor_msgs::image_encodings::BGR8);
        cv::Mat img = cv_ptr->image;
        cv::Mat canny;
        cv::Canny(img, canny, 100, 200);
        cv::imshow("canny", canny);
        cv::waitKey(30);
    }
};

int main(int argc, char *argv[])
{
    rclcpp::init(argc, argv);
    auto node = std::make_shared<CannyCamera>();
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}
