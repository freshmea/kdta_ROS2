#ifndef OPERATOR_HPP
#define OPERATOR_HPP

#include "interface_example/srv/arithmetic_operator.hpp"
#include "rcl_interfaces/msg/parameter_event.hpp"
#include "rclcpp/rclcpp.hpp"
#include "rcutils/cmdline_parser.h"
#include <chrono>
#include <random>

using namespace std::chrono_literals;
class Operator : public rclcpp::Node
{
public:
    using ArithmeticOperator = interface_example::srv::ArithmeticOperator;
    Operator(const rclcpp::NodeOptions &options = rclcpp::NodeOptions());

private:
    bool _random_state;
    int8_t _arithmetic_operator;
    rclcpp::Subscription<rcl_interfaces::msg::ParameterEvent>::SharedPtr _parameter_event_sub;
    rclcpp::Client<ArithmeticOperator>::SharedPtr _service;
    rclcpp::TimerBase::SharedPtr _timer;
    void timer_callback();
    void response_callback(rclcpp::Client<ArithmeticOperator>::SharedFuture future);
    void param_event_callback(const rcl_interfaces::msg::ParameterEvent::SharedPtr event);
};
#endif // OPERATOR_HPP