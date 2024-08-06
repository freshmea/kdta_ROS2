#include "calculator/calculator.hpp"

Calculator::Calculator() : Node("calculator")
{
    auto qos_profile = rclcpp::QoS(rclcpp::KeepLast(10));
    _subscription = create_subscription<interface_example::msg::ArithmeticArgument>("arithmetic_argument", qos_profile, std::bind(&Calculator::sub_callback, this, _1));
}

void Calculator::sub_callback(const interface_example::msg::ArithmeticArgument::SharedPtr msg)
{
    _sub_a = msg->argument_a;
    _sub_b = msg->argument_b;
    RCLCPP_INFO(get_logger(), "Received: {a: %f, b: %f}", _sub_a, _sub_b);
}