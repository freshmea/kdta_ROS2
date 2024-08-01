#include "moveTSim/moveTurtle2.hpp"

int main(int argc, char *argv[])
{
    rclcpp::init(argc, argv);
    auto node = std::make_shared<MoveTurtlesim>();
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}
