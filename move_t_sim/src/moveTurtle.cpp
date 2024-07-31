#include "moveTSim/moveTurtle.hpp"

MoveTurtlesim::MoveTurtlesim()
    : Node("moveTutle_node"), _i(0)
{
    auto qos_profile = rclcpp::QoS(rclcpp::KeepLast(10));
    _pub = this->create_publisher<geometry_msgs::msg::Twist>("turtle1/cmd_vel", qos_profile);
    _pub2 = this->create_publisher<geometry_msgs::msg::Twist>("turtle2/cmd_vel", qos_profile);
    _timer = this->create_wall_timer(30ms, std::bind(&MoveTurtlesim::publish_turtlesim_msg, this));
}

void MoveTurtlesim::publish_turtlesim_msg()
{
    auto msg = geometry_msgs::msg::Twist();
    msg.linear.x = execelaration;
    msg.angular.z = 1.8;

    auto msg2 = geometry_msgs::msg::Twist();
    msg2.linear.x = execelaration;
    msg2.angular.z = 2.8;

    _pub->publish(msg);
    _pub2->publish(msg2);
    execelaration += 0.01;
    if (execelaration > 3.0)
    {
        execelaration = 0.0;
    }
}