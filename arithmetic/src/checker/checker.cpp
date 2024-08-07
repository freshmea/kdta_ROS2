#include "checker/checker.hpp"

Checker::Checker(float goal_sum, const rclcpp::NodeOptions &node_options)
    : Node("checker", node_options)
{
    _arithmetic_action_client = rclcpp_action::create_client<ArithmeticChecker>(
        this->get_node_base_interface(),
        this->get_node_graph_interface(),
        this->get_node_logging_interface(),
        this->get_node_waitables_interface(),
        "arithmetic_checker");

    send_goal_total_sum(goal_sum);
}

void Checker::send_goal_total_sum(float goal_sum)
{
    if (!_arithmetic_action_client)
    {
        RCLCPP_INFO(get_logger(), "Action client not initialized");
    }
    if (!_arithmetic_action_client->wait_for_action_server(10s))
    {
        RCLCPP_ERROR(get_logger(), "Action server not available after waiting");
        rclcpp::shutdown();
    }
    auto goal_msg = ArithmeticChecker::Goal();
    goal_msg.goal_sum = goal_sum;

    auto send_goal_options = rclcpp_action::Client<ArithmeticChecker>::SendGoalOptions();
    send_goal_options.goal_response_callback = std::bind(&Checker::get_arithmetic_action_response_callback, this, _1);
    send_goal_options.feedback_callback = std::bind(&Checker::get_arithmetic_action_feedback, this, _1, _2);
    send_goal_options.result_callback = std::bind(&Checker::get_arithmetic_action_result, this, _1);

    _arithmetic_action_client->async_send_goal(goal_msg, send_goal_options);
}

void Checker::get_arithmetic_action_response_callback(const GoalHandleArithmeticChecker::SharedPtr &future)
{
    if (!future)
    {
        RCLCPP_INFO(get_logger(), "Goal was rejected by server");
    }
    else
    {
        RCLCPP_INFO(get_logger(), "Goal accepted by server, waiting for result");
    }
}

void Checker::get_arithmetic_action_feedback(const GoalHandleArithmeticChecker::SharedPtr,
                                             const std::shared_ptr<const ArithmeticChecker::Feedback> feedback)
{
    RCLCPP_INFO(get_logger(), "Action feedback:");
    for (auto str : feedback->formula)
    {
        RCLCPP_INFO(get_logger(), str.c_str());
    }
}

void Checker::get_arithmetic_action_result(const GoalHandleArithmeticChecker::WrappedResult &result)
{
    switch (result.code)
    {
    case rclcpp_action::ResultCode::SUCCEEDED:
        break;
    case rclcpp_action::ResultCode::ABORTED:
        RCLCPP_INFO(get_logger(), "Goal was aborted");
        return;
    case rclcpp_action::ResultCode::CANCELED:
        RCLCPP_INFO(get_logger(), "Goal was canceled");
        return;
    case rclcpp_action::ResultCode::UNKNOWN:
        RCLCPP_INFO(get_logger(), "Goal result is unknown");
        return;
    }
    RCLCPP_INFO(get_logger(), "Action succeeded!");
    RCLCPP_INFO(get_logger(), "Result :");
    for (auto str : result.result->all_formula)
    {
        RCLCPP_INFO(get_logger(), str.c_str());
    }
    RCLCPP_INFO(get_logger(), "Total sum : %f", result.result->total_sum);
    rclcpp::shutdown();
}