#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"
#include <chrono>
#include <iostream>

using namespace std;
using namespace std::chrono_literals;

int main()
{
    rclcpp::init(0, nullptr);
    int i;
    auto node = std::make_shared<rclcpp::Node>("hello_rclcpp");
    auto pub = node->create_publisher<std_msgs::msg::String>("helloworld", 10);
    auto timer = node->create_wall_timer(1s, [pub, &i]()
                                         {
        auto msg = std_msgs::msg::String();
        msg.data = "Hello, World!"+to_string(i);
        pub->publish(msg);
        i++; });
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}
