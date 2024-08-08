#include "geometry_msgs/msg/twist.hpp"
#include "rclcpp/rclcpp.hpp"
#include "sensor_msgs/msg/laser_scan.hpp"
#include <chrono>
#include <iostream>

using namespace std;
using namespace std::chrono_literals;

class LaserSensor : public rclcpp::Node
{
public:
    LaserSensor()
        : Node("laser_sensor")
    {
        auto qos_profile = rclcpp::SensorDataQoS();
        auto qos_profile2 = rclcpp::QoS(rclcpp::KeepLast(10));
        _sub = create_subscription<sensor_msgs::msg::LaserScan>("/scan", qos_profile, std::bind(&LaserSensor::sub_laser, this, std::placeholders::_1));
        _twist_pub = create_publisher<geometry_msgs::msg::Twist>("cmd_vel", qos_profile2);
        _pub_timer = create_wall_timer(30ms, std::bind(&LaserSensor::pub_twist, this));
        _update_timer = create_wall_timer(10ms, std::bind(&LaserSensor::update, this));
    }

private:
    bool _is_wall;
    sensor_msgs::msg::LaserScan _laser_data;
    geometry_msgs::msg::Twist _twist;
    rclcpp::Publisher<geometry_msgs::msg::Twist>::SharedPtr _twist_pub;
    rclcpp::TimerBase::SharedPtr _pub_timer;
    rclcpp::TimerBase::SharedPtr _update_timer;
    rclcpp::Subscription<sensor_msgs::msg::LaserScan>::SharedPtr _sub;
    void pub_twist()
    {
        restrain();
        _twist_pub->publish(_twist);
    }

    void sub_laser(const sensor_msgs::msg::LaserScan msg)
    {
        _laser_data = msg;
    }

    void update()
    {
        if (_laser_data.ranges.size() == 0)
        {
            return;
        }
        if (_is_wall)
        {
            if (_laser_data.ranges[0] < 0.4 || _laser_data.ranges[315] < 0.4)
            {
                _twist.linear.x = 0.0;
                _twist.angular.z = -0.2;
            }
            else if (_laser_data.ranges[45] > 0.4)
            {
                _twist.linear.x = 0.05;
                _twist.angular.z = 0.2;
            }
            else if (_laser_data.ranges[45] < 0.3)
            {
                _twist.linear.x = 0.05;
                _twist.angular.z = -0.2;
            }
            else
            {
                _twist.linear.x = 0.1;
                _twist.angular.z = 0.0;
            }
        }
        else
        {
            _twist.linear.x = 0.1;
            _twist.angular.z = 0.0;
            if (_laser_data.ranges[0] < 0.3)
            {
                _is_wall = true;
            }
        }
    }
    void restrain()
    {
        if (_twist.angular.z > 1.84)
            _twist.angular.z = 1.84;
        else if (_twist.angular.z < -1.84)
            _twist.angular.z = -1.84;
        if (_twist.linear.x > 0.20)
            _twist.linear.x = 0.20;
        else if (_twist.linear.x < -0.20)
            _twist.linear.x = -0.20;
    }
};

int main(int argc, char *argv[])
{
    rclcpp::init(argc, argv);
    auto node = std::make_shared<LaserSensor>();
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}
