#include "simple_pkg_cpp/time_pub.hpp"

TimePublisher::TimePublisher()
    : Node("hello_world"), _i(0)
{
    auto qos_profile = rclcpp::QoS(rclcpp::KeepLast(10));
    _pub = this->create_publisher<std_msgs::msg::Header>("time_topic", qos_profile);
    _timer = this->create_wall_timer(1s, std::bind(&TimePublisher::publish_time_msg, this));
    _clock = rclcpp::Clock(RCL_ROS_TIME);
}

void TimePublisher::publish_time_msg()
{
    auto msg = std_msgs::msg::Header();
    msg.frame_id = "time" + to_string(_i);
    msg.stamp = _clock.now();
    _pub->publish(msg);
    _i++;
}