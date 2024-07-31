#include "moveTSim/moveTurtle.hpp"

MoveTurtlesim::MoveTurtlesim()
    : Node("moveTutle_node"), _i(0)
{
    auto qos_profile = rclcpp::QoS(rclcpp::KeepLast(10));
    _pub = this->create_publisher<geometry_msgs::msg::Twist>("turtle1/cmd_vel", qos_profile);
    _timer = this->create_wall_timer(30ms, std::bind(&MoveTurtlesim::publish_turtlesim_msg, this));
}

void MoveTurtlesim::publish_turtlesim_msg()
{
    auto msg = geometry_msgs::msg::Twist();
    msg.linear.x = 2.0;
    msg.angular.z = 1.8;
    _pub->publish(msg);
    _i++;
}