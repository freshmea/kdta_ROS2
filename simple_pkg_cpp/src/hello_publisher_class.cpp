#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"
#include <chrono>
#include <iostream>

using namespace std;
using namespace std::chrono_literals;

class HellowPublisher : public rclcpp::Node
{
public:
    HellowPublisher()
        : Node("hello_world"), _i(0)
    {
        auto qos_profile = rclcpp::QoS(rclcpp::KeepLast(10));
        _pub = this->create_publisher<std_msgs::msg::String>("helloworld", qos_profile);
        _timer = this->create_wall_timer(1s, std::bind(&HellowPublisher::publish_helloworld_msg, this));
    }

private:
    int _i;
    // std::shared_ptr<rclcpp::Publisher<std_msgs::msg::String, std::allocator<void>>> _pub;
    rclcpp::Publisher<std_msgs::msg::String>::SharedPtr _pub;
    rclcpp::TimerBase::SharedPtr _timer;
    void publish_helloworld_msg()
    {
        auto msg = std_msgs::msg::String();
        msg.data = "Hellow, World!" + to_string(_i);
        _pub->publish(msg);
        _i++;
    }
};

int main()
{
    rclcpp::init(0, nullptr);
    auto node = std::make_shared<HellowPublisher>();
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}
