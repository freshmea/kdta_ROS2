#include "example_interfaces/action/fibonacci.hpp"
#include "rclcpp/rclcpp.hpp"
#include "rclcpp_action/rclcpp_action.hpp"
#include <functional>
#include <memory>
#include <thread>

class SimpleActionServer : public rclcpp::Node
{
public:
    using Fibonacci = example_interfaces::action::Fibonacci;
    using GoalHandleFibonacci = rclcpp_action::ServerGoalHandle<Fibonacci>;
    SimpleActionServer() : Node("fibonacci_action_server")
    {
        using namespace std::placeholders;
        _action_server = rclcpp_action::create_server<Fibonacci>(
            this, "fibonacci",
            std::bind(&SimpleActionServer::handle_goal, this, _1, _2),
            std::bind(&SimpleActionServer::handle_cancel, this, _1),
            std::bind(&SimpleActionServer::handle_accepted, this, _1));
    }

private:
    rclcpp_action::Server<Fibonacci>::SharedPtr _action_server;
    rclcpp_action::GoalResponse handle_goal(
        const rclcpp_action::GoalUUID &uuid,
        std::shared_ptr<const Fibonacci::Goal> goal)
    {
        RCLCPP_INFO(this->get_logger(), "Received goal request with order %d", goal->order);
        (void)uuid;
        return rclcpp_action::GoalResponse::ACCEPT_AND_EXECUTE;
    }
    rclcpp_action::CancelResponse handle_cancel(
        const std::shared_ptr<GoalHandleFibonacci> goal_handle)
    {
        RCLCPP_INFO(get_logger(), "Received request to cancel goal");
        (void)goal_handle;
        return rclcpp_action::CancelResponse::ACCEPT;
    }
    void handle_accepted(const std::shared_ptr<GoalHandleFibonacci> goal_handle)
    {
        std::thread{std::bind(&SimpleActionServer::execute, this, std::placeholders::_1), goal_handle}.detach();
    }
    void execute(const std::shared_ptr<GoalHandleFibonacci> goal_handle)
    {
        RCLCPP_INFO(get_logger(), "Executing goal");
        rclcpp::Rate loop_rate(1);
        const auto goal = goal_handle->get_goal();
        auto feedback = std::make_shared<Fibonacci::Feedback>();
        feedback->sequence.push_back(0);
        feedback->sequence.push_back(1);
        auto result = std::make_shared<Fibonacci::Result>();

        for (int i = 1; (i < goal->order) && rclcpp::ok(); ++i)
        {
            if (goal_handle->is_canceling())
            {
                result->sequence = feedback->sequence;
                goal_handle->canceled(result);
                RCLCPP_INFO(get_logger(), "Goal canceled");
                return;
            }
            feedback->sequence.push_back(feedback->sequence[i] + feedback->sequence[i - 1]);
            goal_handle->publish_feedback(feedback);
            RCLCPP_INFO(get_logger(), "Publish feedback");
            loop_rate.sleep();
        }
        if (rclcpp::ok())
        {
            result->sequence = feedback->sequence;
            goal_handle->succeed(result);
            RCLCPP_INFO(get_logger(), "Goal succeeded");
        }
    }
};

int main(int argc, char *argv[])
{
    rclcpp::init(argc, argv);
    auto node = std::make_shared<SimpleActionServer>();
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}
