#include "moveTSim/moveTurtle2.hpp"

MoveTurtlesim::MoveTurtlesim()
    : Node("moveTutle_node"), _i(0)
{
    auto qos_profile = rclcpp::QoS(rclcpp::KeepLast(10));
    _pub = this->create_publisher<geometry_msgs::msg::Twist>("turtle1/cmd_vel", qos_profile);
    _sub = this->create_subscription<turtlesim::msg::Pose>("turtle1/pose", qos_profile, std::bind(&MoveTurtlesim::sub_turtlesim_pose, this, std::placeholders::_1));
    _timer = this->create_wall_timer(30ms, std::bind(&MoveTurtlesim::publish_turtlesim_msg, this));
}

void MoveTurtlesim::publish_turtlesim_msg()
{
    auto msg = geometry_msgs::msg::Twist();
    // 사각형으로 움직이기.
    switch (_i)
    {
    case 0:
        if (_pose_msg.x < 6.5)
        {
            // 직진
            msg.linear.x = 0.1;
            msg.angular.z = 0.0;
        }
        else if (_pose_msg.theta < 1.57)
        {
            // 회전
            msg.linear.x = 0.0;
            msg.angular.z = 1.8;
        }
        else
        {
            _i++;
        }
        break;
    case 1:
        if (_pose_msg.y < 6.5)
        {
            // 직진
            msg.linear.x = 0.1;
            msg.angular.z = 0.0;
        }
        else if (_pose_msg.theta < 3.14 && _pose_msg.theta > 0)
        {
            // 회전
            msg.linear.x = 0.0;
            msg.angular.z = 1.8;
        }
        else
        {
            _i++;
        }
        break;
    case 2:
        if (_pose_msg.x > 5.5)
        {
            // 직진
            msg.linear.x = 0.1;
            msg.angular.z = 0.0;
        }
        else if (_pose_msg.theta < -1.57)
        {
            // 회전
            msg.linear.x = 0.0;
            msg.angular.z = 1.8;
        }
        else
        {
            _i++;
        }
        break;
    case 3:
        if (_pose_msg.y > 5.5)
        {
            // 직진
            msg.linear.x = 0.1;
            msg.angular.z = 0.0;
        }
        else if (_pose_msg.theta < 0)
        {
            // 회전
            msg.linear.x = 0.0;
            msg.angular.z = 1.8;
        }
        else
        {
            _i++;
        }
        break;
    }
    _pub->publish(msg);
}

void MoveTurtlesim::sub_turtlesim_pose(const turtlesim::msg::Pose::SharedPtr msg)
{
    _pose_msg = *msg;
}