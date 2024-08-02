#ifndef MOVETURTLEBOT_HPP
#define MOVETURTLEBOT_HPP

#include "geometry_msgs/msg/twist.hpp"
#include "nav_msgs/msg/odometry.hpp"
#include "rclcpp/rclcpp.hpp"
#include <chrono>
// include tf2 for quaternion yaw
#include "tf2/LinearMath/Quaternion.h"
using namespace std;
using namespace std::chrono_literals;

class MoveTurtleBot : public rclcpp::Node
{
public:
    MoveTurtleBot();

private:
    int _i;
    float execelaration;
    rclcpp::Publisher<geometry_msgs::msg::Twist>::SharedPtr _twist_pub;
    rclcpp::Subscription<nav_msgs::msg::Odometry>::SharedPtr _odom_sub;
    rclcpp::TimerBase::SharedPtr _timer;
    void publish_turtlesim_msg();
    void sub_odom_msg(const nav_msgs::msg::Odometry::SharedPtr msg);
    nav_msgs::msg::Odometry _odom_msg;
    float _theta;
};

#endif // MOVETURTLEBOT_HPP