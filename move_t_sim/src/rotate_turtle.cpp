#include "rclcpp/rclcpp.hpp"
#include "rclcpp_action/rclcpp_action.hpp"
#include "rcutils/cmdline_parser.h"
#include "turtlesim/action/rotate_absolute.hpp"
#include <chrono>
#include <functional>
#include <memory>
#include <sstream>
#include <thread>

using namespace std::chrono_literals;

class RotateTurtle : public rclcpp::Node
{
public:
    using RotateAbsolute = turtlesim::action::RotateAbsolute;
    using GoalHandleRotateAbsolute = rclcpp_action::ClientGoalHandle<RotateAbsolute>;

    RotateTurtle(int theta, const rclcpp::NodeOptions &options) : Node("rotate_turtle", options), _goal(theta)
    {
        using namespace std::placeholders;
        _action_client = rclcpp_action::create_client<RotateAbsolute>(this, "turtle1/rotate_absolute");
        _timer = create_wall_timer(500ms, std::bind(&RotateTurtle::send_goal, this));
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
        auto goal_msg = RotateAbsolute::Goal();
        // degree to radian

        goal_msg.theta = (float)_goal * M_PI / 180;
        RCLCPP_INFO(get_logger(), "Sending goal request");

        auto send_goal_options = rclcpp_action::Client<RotateAbsolute>::SendGoalOptions();
        send_goal_options.goal_response_callback = std::bind(&RotateTurtle::goal_response_callback, this, _1);
        send_goal_options.feedback_callback = std::bind(&RotateTurtle::feedback_callback, this, _1, _2);
        send_goal_options.result_callback = std::bind(&RotateTurtle::result_callback, this, _1);
        _action_client->async_send_goal(goal_msg, send_goal_options);
    }

private:
    int _goal;
    rclcpp_action::Client<RotateAbsolute>::SharedPtr _action_client;
    rclcpp::TimerBase::SharedPtr _timer;
    void goal_response_callback(const GoalHandleRotateAbsolute::SharedPtr &goal_handle)
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
        GoalHandleRotateAbsolute::SharedPtr,
        const std::shared_ptr<const RotateAbsolute::Feedback> feedback)
    {
        RCLCPP_INFO(get_logger(), "Remaining : %f", feedback->remaining);
    }

    void result_callback(const GoalHandleRotateAbsolute::WrappedResult &result)
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

        RCLCPP_INFO(get_logger(), "Delta: %f", result.result->delta);
        rclcpp::shutdown();
    }
};

void print_help()
{
    std::cout << "For argument node:" << std::endl;
    std::cout << "rotate_turtle [-h]" << std::endl;
    std::cout << "Options:" << std::endl;
    std::cout << "  -h  : Print this help function" << std::endl;
    std::cout << "  -g [number:0~360 degree]  : send turtlesim theta " << std::endl;
}

int main(int argc, char *argv[])
{
    if (rcutils_cli_option_exist(argv, argv + argc, "-h"))
    {
        print_help();
        return 0;
    }
    rclcpp::init(argc, argv);
    int goal_theta = 0;
    char *cli_option = rcutils_cli_get_option(argv, argv + argc, "-g");
    if (cli_option != nullptr)
    {
        goal_theta = atoi(cli_option);
    }
    rclcpp::NodeOptions options;
    rclcpp::spin(std::make_shared<RotateTurtle>(goal_theta, options));
    rclcpp::shutdown();
    return 0;
}
