#ifndef CALCULATOR_HPP
#define CALCULATOR_HPP

#include "interface_example/action/arithmetic_checker.hpp"
#include "rclcpp/rclcpp.hpp"
#include "rclcpp_action/rclcpp_action.hpp"
#include "rcutils/cmdline_parser.h"
#include <chrono>
#include <string>

using namespace std::chrono_literals;
using namespace std::placeholders;

class Checker : public rclcpp::Node
{
public:
    using ArithmeticChecker = interface_example::action::ArithmeticChecker;
    using GoalHandleArithmeticChecker = rclcpp_action::ClientGoalHandle<ArithmeticChecker>;

    Checker();
    float _goal_sum;
    const rclcpp::NodeOptions _node_options = rclcpp::NodeOptions();

private:
    rclcpp_action::Client<ArithmeticChecker>::SharedPtr _action_client;

    void send_goal_total_sum(float goal_sum);

    void get_arithmetic_action_response_callback(const GoalHandleArithmeticChecker::SharedPtr &future);
    void get_arithmetic_action_feedback(const GoalHandleArithmeticChecker::SharedPtr &goal_handle,
                                        const std::shared_ptr<const ArithmeticChecker::Feedback> feedback);
    void get_arithmetic_action_result(const GoalHandleArithmeticChecker::WrappedResult &result);
};

#endif // CALCULATOR_HPP
