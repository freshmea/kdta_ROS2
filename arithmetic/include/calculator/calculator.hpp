#include "interface_example/msg/arithmetic_argument.hpp"
#include "rclcpp/rclcpp.hpp"
#include "rcutils/cmdline_parser.h"
#include <chrono>

using namespace std::chrono_literals;
using namespace std::placeholders;

class Calculator : public rclcpp::Node
{
public:
    Calculator();

private:
    float _sub_a;
    float _sub_b;
    rclcpp::Subscription<interface_example::msg::ArithmeticArgument>::SharedPtr _subscription;
    void sub_callback(const interface_example::msg::ArithmeticArgument::SharedPtr msg);
};