#include "calculator/calculator.hpp"

Calculator::Calculator() : Node("calculator")
{
    auto qos_profile = rclcpp::QoS(rclcpp::KeepLast(10));
    _subscription = create_subscription<ArithmeticArgument>("arithmetic_argument", qos_profile, std::bind(&Calculator::sub_callback, this, _1));
    _service = create_service<ArithmeticOperator>("arithmetic_operator", std::bind(&Calculator::service_callback, this, _1, _2));
}

void Calculator::sub_callback(const ArithmeticArgument::SharedPtr msg)
{
    _sub_a = msg->argument_a;
    _sub_b = msg->argument_b;
    RCLCPP_INFO(get_logger(), "Received: {a: %f, b: %f}", _sub_a, _sub_b);
}

void Calculator::service_callback(const std::shared_ptr<ArithmeticOperator::Request> request, std::shared_ptr<ArithmeticOperator::Response> response)
{
    _argument_operator = request->arithmetic_operator;

    std::string operator_str;
    if (_argument_operator == request->PLUS)
    {
        _argument_result = _sub_a + _sub_b;
        operator_str = "+";
    }
    else if (_argument_operator == request->MINUS)
    {
        _argument_result = _sub_a - _sub_b;
        operator_str = "-";
    }
    else if (_argument_operator == request->MULTIPLY)
    {
        _argument_result = _sub_a * _sub_b;
        operator_str = "*";
    }
    else if (_argument_operator == request->DIVISION)
    {
        if (_sub_b == 0)
        {
            RCLCPP_ERROR(get_logger(), "Division by zero");
            _argument_result = 0;
            operator_str = "/";
        }
        else
        {
            _argument_result = _sub_a / _sub_b;
            operator_str = "/";
        }
    }
    else
    {
        RCLCPP_ERROR(get_logger(), "Unknown operator");
    }
    operator_str = std::to_string(_sub_a) + operator_str + std::to_string(_sub_b) + "=" + std::to_string(_argument_result);
    RCLCPP_INFO(get_logger(), "Result: %s", operator_str.c_str());
    response->arithmetic_result = _argument_result;
}