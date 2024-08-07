#include "checker/checker.hpp"

void print_help()
{
    std::cout << "For argument node:" << std::endl;
    std::cout << "checker [-h]" << std::endl;
    std::cout << "Options:" << std::endl;
    std::cout << "  -h  : Print this help function" << std::endl;
    std::cout << "  -g [number]  : send goal number " << std::endl;
}

int main(int argc, char *argv[])
{
    if (rcutils_cli_option_exist(argv, argv + argc, "-h"))
    {
        print_help();
        return 0;
    }
    rclcpp::init(argc, argv);
    float goal_total_sum = 50.0;
    char *cli_option = rcutils_cli_get_option(argv, argv + argc, "-g");
    if (cli_option != nullptr)
    {
        goal_total_sum = atof(cli_option);
    }
    rclcpp::NodeOptions options;
    rclcpp::spin(std::make_shared<Checker>(goal_total_sum, options));
    rclcpp::shutdown();
    return 0;
}