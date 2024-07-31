#ifndef PUBLISHER_HPP
#define PUBLISHER_HPP

#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"
#include <chrono>
#include <iostream>

using namespace std;
using namespace std::chrono_literals;

class HellowPublisher : public rclcpp::Node
{
public:
    HellowPublisher();

private:
    int _i;
    rclcpp::Publisher<std_msgs::msg::String>::SharedPtr _pub;
    rclcpp::TimerBase::SharedPtr _timer;
    void publish_helloworld_msg();
};

#endif // PUBLISHER_HPP