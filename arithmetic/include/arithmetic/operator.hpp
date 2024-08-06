#ifndef OPERATOR_HPP
#define OPERATOR_HPP

#include "interface_example/srv/arithmetic_operator.hpp"
#include "rclcpp/rclcpp.hpp"
#include "rcutils/cmdline_parser.h"

class Operator : public rclcpp::Node
{
public:
    using ArithmeticOperator = interface_example::srv::ArithmeticOperator;
    Operator(const rclcpp::NodeOptions &options = rclcpp::NodeOptions());

private:
    rclcpp::Service<ArithmeticOperator>::SharedPtr _service;
};
#endif // OPERATOR_HPP