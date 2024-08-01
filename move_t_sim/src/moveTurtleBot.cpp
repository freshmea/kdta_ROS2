#include "moveTSim/moveTurtleBotcpp.hpp"

int main(int argc, char *argv[])
{
    rclcpp::init(argc, argv);
    auto node = std::make_shared<MoveTurtleBot>();
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}
