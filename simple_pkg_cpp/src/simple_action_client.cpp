#include "example_interfaces/action/fibonacci.hpp"
#include "rclcpp/rclcpp.hpp"
#include "rclcpp_action/rclcpp_action.hpp"
#include <chrono>
#include <functional>
#include <memory>
#include <thread>

using namespace std::chrono_literals;

class SimpleActionClient : public rclcpp::Node
{
public:
    using Fibonacci = example_interfaces::action::Fibonacci;
    using GoalHandleFibonacci = rclcpp_action::ServerGoalHandle<Fibonacci>;

    SimpleActionClient(const rclcpp::NodeOptions &options) : Node("fibonacci_action_client")
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
    }

private:
    rclcpp_action::Client<Fibonacci>::SharedPtr _action_client;
    rclcpp::TimerBase::SharedPtr _timer;
    void goal_response_callback(const GoalHandleFibonacci::SharedPtr &goal_handle)
    {
    }
    void feedback_callback(
        GoalHandleFibonacci::SharedPtr,
        const std::shared_ptr<const Fibonacci::Feedback> feedback)
    {
    }
    void result_callback(const GoalHandleFibonacci::WrappedResult &result)
    {
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
