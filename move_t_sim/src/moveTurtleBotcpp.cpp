#include "moveTSim/moveTurtleBotcpp.hpp"

MoveTurtleBot::MoveTurtleBot()
    : Node("moveTutleBot_node"), _i(0)
{
    auto qos_profile = rclcpp::QoS(rclcpp::KeepLast(10));
    // TODO: nav_msgs odom qos_profile
    _twist_pub = this->create_publisher<geometry_msgs::msg::Twist>("cmd_vel", qos_profile);
    _odom_sub = this->create_subscription<nav_msgs::msg::Odometry>("odom", qos_profile, std::bind(&MoveTurtleBot::sub_odom_msg, this, std::placeholders::_1));
    _timer = this->create_wall_timer(30ms, std::bind(&MoveTurtleBot::publish_turtlesim_msg, this));
}

void MoveTurtleBot::publish_turtlesim_msg()
{
}

void sub_odom_msg(const nav_msgs::msg::Odometry::SharedPtr msg)
{
}
