#include <geometry_msgs/msg/transform_stamped.hpp>
#include <rclcpp/rclcpp.hpp>
#include <tf2/LinearMath/Quaternion.h>
#include <tf2_ros/transform_broadcaster.h>

class TfPublisher : public rclcpp::Node
{
public:
    TfPublisher()
        : Node("tf_publisher"),
          tf_broadcaster_(std::make_shared<tf2_ros::TransformBroadcaster>(this))
    {
        // Timer to publish the transform at 15fps (66.67ms interval)
        timer_ = this->create_wall_timer(
            std::chrono::milliseconds(67),
            std::bind(&TfPublisher::broadcast_transform, this));
    }

private:
    void broadcast_transform()
    {
        geometry_msgs::msg::TransformStamped transform_stamped;

        transform_stamped.header.stamp = this->get_clock()->now();
        transform_stamped.header.frame_id = "map";
        transform_stamped.child_frame_id = "odom";

        // Set the transform (example values, should be replaced with actual data)
        transform_stamped.transform.translation.x = 0.0;
        transform_stamped.transform.translation.y = 0.0;
        transform_stamped.transform.translation.z = 0.0;
        tf2::Quaternion q;
        q.setRPY(0, 0, 0); // No rotation
        transform_stamped.transform.rotation.x = q.x();
        transform_stamped.transform.rotation.y = q.y();
        transform_stamped.transform.rotation.z = q.z();
        transform_stamped.transform.rotation.w = q.w();

        // Send the transform
        tf_broadcaster_->sendTransform(transform_stamped);
    }

    rclcpp::TimerBase::SharedPtr timer_;
    std::shared_ptr<tf2_ros::TransformBroadcaster> tf_broadcaster_;
};

int main(int argc, char *argv[])
{
    rclcpp::init(argc, argv);
    auto node = std::make_shared<TfPublisher>();
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}