#include "geometry_msgs/msg/pose_stamped.hpp"
#include "nav2_msgs/action/follow_waypoints.hpp"
#include "rclcpp/rclcpp.hpp"
#include "rclcpp_action/rclcpp_action.hpp"
#include "tf2/LinearMath/Matrix3x3.h"
#include "tf2/LinearMath/Quaternion.h"
#include <chrono>
#include <functional>
#include <memory>

using namespace std::chrono_literals;

class WaypointsAction : public rclcpp::Node
{
public:
    using FollowWaypoints = nav2_msgs::action::FollowWaypoints;
    using GoalHandleFollowWaypoints = rclcpp_action::ClientGoalHandle<FollowWaypoints>;

    WaypointsAction(const rclcpp::NodeOptions &options) : Node("waypoints_action_client", options)
    {
        using namespace std::placeholders;
        _action_client = rclcpp_action::create_client<FollowWaypoints>(this, "follow_waypoints");
        _timer = create_wall_timer(500ms, std::bind(&WaypointsAction::send_goal, this));
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
        auto goal_msg = FollowWaypoints::Goal();

        goal_msg.poses.push_back(get_pose_from_xy_theta(3.7, 0.0, 1.57));

        goal_msg.poses.push_back(get_pose_from_xy_theta(3.7, 1.0, 3.14));

        goal_msg.poses.push_back(get_pose_from_xy_theta(0, 1.0, -1.57));

        goal_msg.poses.push_back(get_pose_from_xy_theta(0, 0, 0.0));

        RCLCPP_INFO(get_logger(), "Sending goal request");

        auto send_goal_options = rclcpp_action::Client<FollowWaypoints>::SendGoalOptions();
        send_goal_options.goal_response_callback = std::bind(&WaypointsAction::goal_response_callback, this, _1);
        send_goal_options.feedback_callback = std::bind(&WaypointsAction::feedback_callback, this, _1, _2);
        send_goal_options.result_callback = std::bind(&WaypointsAction::result_callback, this, _1);
        _action_client->async_send_goal(goal_msg, send_goal_options);
    }

private:
    rclcpp_action::Client<FollowWaypoints>::SharedPtr _action_client;
    rclcpp::TimerBase::SharedPtr _timer;
    void goal_response_callback(const GoalHandleFollowWaypoints::SharedPtr &goal_handle)
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
        GoalHandleFollowWaypoints::SharedPtr,
        const std::shared_ptr<const FollowWaypoints::Feedback> feedback)
    {
        RCLCPP_INFO(get_logger(), "current waypoints: %d", feedback->current_waypoint);
    }

    void result_callback(const GoalHandleFollowWaypoints::WrappedResult &result)
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

        for (auto number : result.result->missed_waypoints)
        {
            RCLCPP_INFO(get_logger(), "missed_waypoints: %d", number);
        }
        rclcpp::shutdown();
    }
    geometry_msgs::msg::PoseStamped get_pose_from_xy_theta(const float &x, const float &y, const float &theta)
    {
        auto pose = geometry_msgs::msg::PoseStamped();
        tf2::Quaternion q;
        double _roll, _pitch, _yaw;
        _roll = 0.0;
        _pitch = 0.0;
        _yaw = theta;
        tf2::Matrix3x3(q).setRPY(_roll, _pitch, _yaw);

        pose.header.frame_id = "map";
        pose.header.stamp = rclcpp::Clock(RCL_ROS_TIME).now();
        pose.pose = geometry_msgs::msg::Pose();
        pose.pose.position.x = x;
        pose.pose.position.y = y;
        pose.pose.position.z = 0.0;
        pose.pose.orientation.x = 0.0;
        pose.pose.orientation.y = 0.0;
        pose.pose.orientation.z = 0.0;
        pose.pose.orientation.w = 1.0;
        return pose;
    }
};

int main(int argc, char *argv[])
{
    rclcpp::init(argc, argv);
    rclcpp::NodeOptions options;
    auto node = std::make_shared<WaypointsAction>(options);
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}
