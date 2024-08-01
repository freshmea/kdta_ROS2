#ifndef MOVETURTLE_HPP
#define MOVETURTLE_HPP

#include "geometry_msgs/msg/twist.hpp"
#include "rclcpp/rclcpp.hpp"
#include "turtlesim/msg/pose.hpp"
#include <chrono>

using namespace std;
using namespace std::chrono_literals;

class MoveTurtlesim : public rclcpp::Node
{
public:
    MoveTurtlesim();

private:
    int _i;
    float execelaration;
    rclcpp::Publisher<geometry_msgs::msg::Twist>::SharedPtr _pub;
    rclcpp::Subscription<turtlesim::msg::Pose>::SharedPtr _sub;
    rclcpp::TimerBase::SharedPtr _timer;
    void publish_turtlesim_msg();
    void sub_turtlesim_pose(const turtlesim::msg::Pose::SharedPtr msg);
    turtlesim::msg::Pose _pose_msg;
};

#endif // MOVETURTLE_HPP