#include "simple_pkg_cpp/time_pub.hpp"

int main(int argc, char *argv[])
{
    rclcpp::init(argc, argv);
    auto node = std::make_shared<TimePublisher>();
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}
