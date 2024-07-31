#include "simple_pkg_cpp/time_sub.hpp"

int main(int argc, char *argv[])
{
    rclcpp::init(argc, argv);
    auto node = std::make_shared<TimeSubscriber>();
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}
