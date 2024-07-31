#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"
#include <chrono>
#include <iostream>

using namespace std;
using namespace std::chrono_literals;

class MessagePub : public rclcpp::Node
{
public:
    MessagePub()
        : Node("mpub"), _i(0)
    {
        auto qos_profile = rclcpp::QoS(rclcpp::KeepLast(10));
        _pub = this->create_publisher<std_msgs::msg::String>("message1", qos_profile);
        _pub2 = this->create_publisher<std_msgs::msg::String>("message2", qos_profile);
        _timer = this->create_wall_timer(1s, std::bind(&MessagePub::publish_helloworld_msg, this));
    }

private:
    int _i;
    rclcpp::Publisher<std_msgs::msg::String>::SharedPtr _pub;
    rclcpp::Publisher<std_msgs::msg::String>::SharedPtr _pub2;
    rclcpp::TimerBase::SharedPtr _timer;
    void publish_helloworld_msg()
    {
        auto msg = std_msgs::msg::String();
        msg.data = "from mpub!" + to_string(_i);
        _pub->publish(msg);
        _pub2->publish(msg);
        _i++;
    }
};

int main(int argc, char *argv[])
{
    rclcpp::init(argc, argv);
    auto node = std::make_shared<MessagePub>();
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}
