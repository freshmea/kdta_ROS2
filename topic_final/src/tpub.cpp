#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/header.hpp"
#include <chrono>
#include <iostream>

using namespace std;
using namespace std::chrono_literals;

class TimePub : public rclcpp::Node
{
public:
    TimePub()
        : Node("tpub"), _i(0)
    {
        auto qos_profile = rclcpp::QoS(rclcpp::KeepLast(10));
        _pub = this->create_publisher<std_msgs::msg::Header>("time", qos_profile);
        _timer = this->create_wall_timer(1s, std::bind(&TimePub::publish_time_msg, this));
        _clock = rclcpp::Clock(RCL_ROS_TIME);
    }

private:
    int _i;
    rclcpp::Publisher<std_msgs::msg::Header>::SharedPtr _pub;
    rclcpp::TimerBase::SharedPtr _timer;
    rclcpp::Clock _clock;
    void publish_time_msg()
    {
        auto msg = std_msgs::msg::Header();
        msg.stamp = _clock.now();
        msg.frame_id = "tpub" + to_string(_i);
        _pub->publish(msg);
        _i++;
    }
};

int main(int argc, char *argv[])
{
    rclcpp::init(argc, argv);
    auto node = std::make_shared<TimePub>();
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}
