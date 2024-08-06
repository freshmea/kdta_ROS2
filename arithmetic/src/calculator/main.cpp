#include "calculator/calculator.hpp"

void print_help()
{
    std::cout << "For argument node:" << std::endl;
    std::cout << "node_name [-h]" << std::endl;
    std::cout << "Options:" << std::endl;
    std::cout << "  -h  : Print this help function" << std::endl;
}

int main(int argc, char *argv[])
{
    if (rcutils_cli_option_exist(argv, argv + argc, "-h"))
    {
        print_help();
        return 0;
    }
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<Calculator>());
    rclcpp::shutdown();
    return 0;
}