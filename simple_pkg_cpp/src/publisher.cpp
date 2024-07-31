#include "simple_pkg_cpp/publisher.hpp"

HellowPublisher::HellowPublisher()
    : Node("hello_world"), _i(0)
{
    auto qos_profile = rclcpp::QoS(rclcpp::KeepLast(10));
    _pub = this->create_publisher<std_msgs::msg::String>("helloworld", qos_profile);
    _timer = this->create_wall_timer(1s, std::bind(&HellowPublisher::publish_helloworld_msg, this));
}

void HellowPublisher::publish_helloworld_msg()
{
    auto msg = std_msgs::msg::String();
    msg.data = "Hellow, World!" + to_string(_i);
    _pub->publish(msg);
    _i++;
}