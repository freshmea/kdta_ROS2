#ifndef ARGUMENT_HPP_
#define ARGUMENT_HPP_

#include "interface_example/msg/arithmetic_argument.hpp"
#include "rcl_interfaces/msg/parameter_event.hpp"
#include "rcl_interfaces/msg/set_parameters_result.hpp"
#include "rclcpp/rclcpp.hpp"
#include "rcutils/cmdline_parser.h"
#include <chrono>
#include <random>

using namespace std::chrono_literals;

class Argument : public rclcpp::Node
{
public:
    Argument();

private:
    float _min_random_num;
    float _max_random_num;
    rclcpp::Publisher<interface_example::msg::ArithmeticArgument>::SharedPtr _publisher;
    rclcpp::Subscription<rcl_interfaces::msg::ParameterEvent>::SharedPtr _parameter_event_sub;
    rclcpp::TimerBase::SharedPtr _timer;
    void pub_callback();

    void param_event_callback(const rcl_interfaces::msg::ParameterEvent::SharedPtr event);
};

#endif // ARGUMENT_HPP_