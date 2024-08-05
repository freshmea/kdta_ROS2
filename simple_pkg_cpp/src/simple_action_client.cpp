#include "example_interfaces/action/fibonacci.hpp"
#include "rclcpp/rclcpp.hpp"
#include "rclcpp_action/rclcpp_action.hpp"
#include <chrono>
#include <functional>
#include <memory>
#include <sstream>
#include <thread>

using namespace std::chrono_literals;

class SimpleActionClient : public rclcpp::Node
{
public:
    using Fibonacci = example_interfaces::action::Fibonacci;
    using GoalHandleFibonacci = rclcpp_action::ClientGoalHandle<Fibonacci>;

    SimpleActionClient(const rclcpp::NodeOptions &options) : Node("fibonacci_action_client", options)
    {
        using namespace std::placeholders;
        _action_client = rclcpp_action::create_client<Fibonacci>(this, "fibonacci");
        _timer = create_wall_timer(500ms, std::bind(&SimpleActionClient::send_goal, this));
    }
    void send_goal()
    {
        using namespace std::placeholders;
        _timer->cancel();
        if (!_action_client->wait_for_action_server(10s))
        {
            RCLCPP_ERROR(get_logger(), "Action server not available after waiting");
            rclcpp::shutdown();
        }
        auto goal_msg = Fibonacci::Goal();
        goal_msg.order = 10;
        RCLCPP_INFO(get_logger(), "Sending goal request");

        auto send_goal_options = rclcpp_action::Client<Fibonacci>::SendGoalOptions();
        send_goal_options.goal_response_callback = std::bind(&SimpleActionClient::goal_response_callback, this, _1);
        send_goal_options.feedback_callback = std::bind(&SimpleActionClient::feedback_callback, this, _1, _2);
        send_goal_options.result_callback = std::bind(&SimpleActionClient::result_callback, this, _1);
        _action_client->async_send_goal(goal_msg, send_goal_options);
    }

private:
    rclcpp_action::Client<Fibonacci>::SharedPtr _action_client;
    rclcpp::TimerBase::SharedPtr _timer;
    void goal_response_callback(const GoalHandleFibonacci::SharedPtr &goal_handle)
    {
        if (!goal_handle)
        {
            RCLCPP_INFO(get_logger(), "Goal was rejected by server");
        }
        else
        {
            RCLCPP_INFO(get_logger(), "Goal accepted by server, waiting for result");
        }
    }

    void feedback_callback(
        GoalHandleFibonacci::SharedPtr,
        const std::shared_ptr<const Fibonacci::Feedback> feedback)
    {
        std::stringstream ss;
        ss << "Next number in sequence received: ";
        for (auto number : feedback->sequence)
        {
            ss << number << " ";
        }
        RCLCPP_INFO(get_logger(), ss.str().c_str());
    }

    void result_callback(const GoalHandleFibonacci::WrappedResult &result)
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
        std::stringstream ss;
        ss << "Result received: ";
        for (auto number : result.result->sequence)
        {
            ss << number << " ";
        }
        RCLCPP_INFO(get_logger(), ss.str().c_str());
        rclcpp::shutdown();
    }
};

int main(int argc, char *argv[])
{
    rclcpp::init(argc, argv);
    rclcpp::NodeOptions options;
    auto node = std::make_shared<SimpleActionClient>(options);
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}
