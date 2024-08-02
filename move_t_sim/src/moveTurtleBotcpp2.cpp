#include "moveTSim/moveTurtleBotcpp2.hpp"

MoveTurtleBot::MoveTurtleBot()
    : Node("moveTutleBot_node"), _i(0)
{
    auto qos_profile = rclcpp::QoS(rclcpp::KeepLast(10));
    _twist_pub = this->create_publisher<geometry_msgs::msg::Twist>("cmd_vel", qos_profile);
    _odom_sub = this->create_subscription<nav_msgs::msg::Odometry>("odom", qos_profile, std::bind(&MoveTurtleBot::sub_odom_msg, this, std::placeholders::_1));
    _timer = this->create_wall_timer(30ms, std::bind(&MoveTurtleBot::publish_turtlesim_msg, this));
}

void MoveTurtleBot::publish_turtlesim_msg()
{
    auto msg = geometry_msgs::msg::Twist();
    // 사각형으로 움직이기.
    switch (_i)
    {
    case 0:
        if (_odom_msg.pose.pose.position.x < 0.3 && _theta > -0.1 && _theta < 0.1)
        {
            // 직진
            msg.linear.x = 0.1;
            msg.angular.z = 0.0;
        }
        else if (_odom_msg.pose.pose.position.x < 0.3 && _theta < -0.1)
        {
            // 회전
            msg.linear.x = 0.0;
            msg.angular.z = 0.3;
        }
        else if (_odom_msg.pose.pose.position.x < 0.3 && _theta > 0.1)
        {
            // 회전
            msg.linear.x = 0.0;
            msg.angular.z = -0.3;
        }
        else if (_theta < 1.57)
        {
            // 회전
            msg.linear.x = 0.0;
            msg.angular.z = 0.3;
        }
        else
        {
            _i++;
        }
        break;
    case 1:
        if (_odom_msg.pose.pose.position.y < 0.3 && _theta > 1.47 && _theta < 1.67)
        {
            // 직진
            msg.linear.x = 0.1;
            msg.angular.z = 0.0;
        }
        else if (_odom_msg.pose.pose.position.y < 0.3 && _theta < 1.47)
        {
            // 회전
            msg.linear.x = 0.0;
            msg.angular.z = 0.3;
        }
        else if (_odom_msg.pose.pose.position.y < 0.3 && _theta > 1.67)
        {
            // 회전
            msg.linear.x = 0.0;
            msg.angular.z = -0.3;
        }
        else if (_theta < 3.14 && _theta > 0)
        {
            // 회전
            msg.linear.x = 0.0;
            msg.angular.z = 0.3;
        }
        else
        {
            _i++;
        }
        break;
    case 2:
        if (_odom_msg.pose.pose.position.x > 0 && _theta > 3.04)
        {
            // 직진
            msg.linear.x = 0.1;
            msg.angular.z = 0.0;
        }
        else if (_odom_msg.pose.pose.position.x > 0 && _theta < -3.04)
        {
            // 직진
            msg.linear.x = 0.1;
            msg.angular.z = 0.0;
        }
        else if (_odom_msg.pose.pose.position.x > 0 && _theta < 3.04)
        {
            // 회전
            msg.linear.x = 0.0;
            msg.angular.z = 0.3;
        }
        else if (_odom_msg.pose.pose.position.x > 0 && _theta > -3.04)
        {
            // 회전
            msg.linear.x = 0.0;
            msg.angular.z = -0.3;
        }
        else if (_theta < -1.57)
        {
            // 회전
            msg.linear.x = 0.0;
            msg.angular.z = 0.3;
        }
        else
        {
            _i++;
        }
        break;
    case 3:
        if (_odom_msg.pose.pose.position.y > 0 && _theta < -1.47 && _theta > -1.67)
        {
            // 직진
            msg.linear.x = 0.1;
            msg.angular.z = 0.0;
        }
        else if (_odom_msg.pose.pose.position.y > 0 && _theta < -1.67)
        {
            // 회전
            msg.linear.x = 0.0;
            msg.angular.z = 0.3;
        }
        else if (_odom_msg.pose.pose.position.y > 0 && _theta > -1.47)
        {
            // 회전
            msg.linear.x = 0.0;
            msg.angular.z = -0.3;
        }
        else if (_theta < 0)
        {
            // 회전
            msg.linear.x = 0.0;
            msg.angular.z = 0.3;
        }
        else
        {
            _i = 0;
        }
        break;
    }
    _twist_pub->publish(msg);
}

void MoveTurtleBot::sub_odom_msg(const nav_msgs::msg::Odometry::SharedPtr msg)
{
    _odom_msg = *msg;
    tf2::Quaternion q(_odom_msg.pose.pose.orientation.x, _odom_msg.pose.pose.orientation.y, _odom_msg.pose.pose.orientation.z, _odom_msg.pose.pose.orientation.w);

    // _theta = q.getAngle() * 2 - 3.141592;
    double _roll, _pitch, _yaw;
    tf2::Matrix3x3(q).getRPY(_roll, _pitch, _yaw);
    _theta = _yaw;
    RCLCPP_INFO(get_logger(), "Position(x: %f, y: %f, z: %f, theta: %f)", _odom_msg.pose.pose.position.x, _odom_msg.pose.pose.position.y, _odom_msg.pose.pose.position.z, _theta);
}
