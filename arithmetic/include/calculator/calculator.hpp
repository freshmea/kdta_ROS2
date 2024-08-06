#ifndef CALCULATOR_HPP
#define CALCULATOR_HPP

#include "interface_example/msg/arithmetic_argument.hpp"
#include "interface_example/srv/arithmetic_operator.hpp"
#include "rclcpp/rclcpp.hpp"
#include "rcutils/cmdline_parser.h"
#include <chrono>
#include <string>

using namespace std::chrono_literals;
using namespace std::placeholders;

class Calculator : public rclcpp::Node
{
public:
    using ArithmeticArgument = interface_example::msg::ArithmeticArgument;
    using ArithmeticOperator = interface_example::srv::ArithmeticOperator;
    Calculator();
    void service_callback(const std::shared_ptr<ArithmeticOperator::Request> request, std::shared_ptr<ArithmeticOperator::Response> response);

private:
    float _sub_a;
    float _sub_b;
    int8_t _argument_operator;
    float _argument_result;
    rclcpp::Subscription<ArithmeticArgument>::SharedPtr _subscription;
    rclcpp::Service<ArithmeticOperator>::SharedPtr _service;
    void sub_callback(const interface_example::msg::ArithmeticArgument::SharedPtr msg);
};

#endif // CALCULATOR_HPP
