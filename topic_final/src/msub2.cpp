#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"
#include <chrono>
#include <iostream>

using namespace std;
using namespace std::chrono_literals;

class Msub2 : public rclcpp::Node
{
public:
    Msub2() : Node("msub2")
    {
        auto qos_profile = rclcpp::QoS(rclcpp::KeepLast(10));
        _sub = this->create_subscription<std_msgs::msg::String>("message2", qos_profile, std::bind(&Msub2::sub_helloworld_msg, this, std::placeholders::_1));
    }

private:
    rclcpp::Subscription<std_msgs::msg::String>::SharedPtr _sub;
    void sub_helloworld_msg(const std_msgs::msg::String::SharedPtr msg)
    {
        RCLCPP_INFO(get_logger(), "I heard: '%s'", msg->data.c_str());
    }
};

int main(int argc, char *argv[])
{
    rclcpp::init(argc, argv);
    auto node = std::make_shared<Msub2>();
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}
