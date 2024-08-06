#ifndef OPERATOR_HPP
#define OPERATOR_HPP

#include "interface_example/srv/arithmetic_operator.hpp"
#include "rclcpp/rclcpp.hpp"
#include "rcutils/cmdline_parser.h"
#include <chrono>

using namespace std::chrono_literals;
class Operator : public rclcpp::Node
{
public:
    using ArithmeticOperator = interface_example::srv::ArithmeticOperator;
    Operator(const rclcpp::NodeOptions &options = rclcpp::NodeOptions());

private:
    rclcpp::Client<ArithmeticOperator>::SharedPtr _service;
    rclcpp::TimerBase::SharedPtr _timer;
    void timer_callback();
    void response_callback(rclcpp::Client<ArithmeticOperator>::SharedFuture future);
};
#endif // OPERATOR_HPP