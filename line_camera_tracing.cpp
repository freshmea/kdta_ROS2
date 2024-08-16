#include <cv_bridge/cv_bridge.h>
#include <geometry_msgs/msg/twist.hpp>
#include <opencv2/imgcodecs.hpp> // For cv::imdecode
#include <opencv2/opencv.hpp>
#include <rclcpp/rclcpp.hpp>
#include <sensor_msgs/msg/compressed_image.hpp>

class RobotControlNode : public rclcpp::Node
{
public:
    RobotControlNode()
        : Node("robot_control_node"), turn_direction_("right")
    { // Default direction
        // Create a publisher for /cmd_vel
        cmd_vel_publisher_ = this->create_publisher<geometry_msgs::msg::Twist>("/cmd_vel", 10);

        // Create a subscription for camera images
        image_subscriber_ = this->create_subscription<sensor_msgs::msg::CompressedImage>(
            "camera1/compressed_image", 10,
            std::bind(&RobotControlNode::imageCallback, this, std::placeholders::_1));

        // Initialize OpenCV windows (optional)
        cv::namedWindow("Processed Image", cv::WINDOW_AUTOSIZE);
    }

private:
    void imageCallback(const sensor_msgs::msg::CompressedImage::SharedPtr msg)
    {
        try
        {
            // Convert CompressedImage to OpenCV Mat
            cv::Mat compressed_img = cv::imdecode(cv::Mat(msg->data), cv::IMREAD_COLOR);

            if (compressed_img.empty())
            {
                RCLCPP_ERROR(this->get_logger(), "Failed to decode image");
                return;
            }

            // Image processing (Convert to gray, blur, detect edges, etc.)
            cv::Mat gray, blurred, edges;
            cv::cvtColor(compressed_img, gray, cv::COLOR_BGR2GRAY);
            cv::GaussianBlur(gray, blurred, cv::Size(5, 5), 0);
            cv::Canny(blurred, edges, 50, 150);

            // Find contours
            std::vector<std::vector<cv::Point>> contours;
            cv::findContours(edges, contours, cv::RETR_TREE, cv::CHAIN_APPROX_SIMPLE);

            // Create a Twist message
            auto twist_msg = geometry_msgs::msg::Twist();

            if (!contours.empty())
            {
                // Find the largest contour (assuming the largest contour is the line we want to follow)
                std::vector<cv::Point> largest_contour = contours[0];
                double largest_area = cv::contourArea(largest_contour);

                for (const auto &contour : contours)
                {
                    double area = cv::contourArea(contour);
                    if (area > largest_area)
                    {
                        largest_area = area;
                        largest_contour = contour;
                    }
                }

                // Fit a line to the largest contour
                cv::Vec4f line_params;
                cv::fitLine(largest_contour, line_params, cv::DIST_L2, 0, 0.01, 0.01);

                // Extract line parameters
                float vx = line_params[0];
                float vy = line_params[1];
                float x0 = line_params[2];
                float y0 = line_params[3];

                // Compute the line's angle
                float angle = atan2(vy, vx);

                // Determine linear and angular velocity based on the angle
                float angle_deviation = fabs(angle - M_PI / 2); // Deviation from desired angle

                // Simple proportional controller for angular velocity
                float kp_angular = 1.0;
                twist_msg.angular.z = kp_angular * angle_deviation;

                // Move forward if the line is detected
                twist_msg.linear.x = 0.2; // Forward speed

                // Detect junctions (simple heuristic: multiple large contours)
                if (contours.size() > 1)
                {
                    // Example logic: Choose direction based on parameter
                    if (turn_direction_ == "right")
                    {
                        twist_msg.angular.z = -0.5; // Turn right
                    }
                    else if (turn_direction_ == "left")
                    {
                        twist_msg.angular.z = 0.5; // Turn left
                    }
                    twist_msg.linear.x = 0.0; // Stop moving forward while turning
                }
            }
            else
            {
                // Stop if no line is detected
                twist_msg.linear.x = 0.0;
                twist_msg.angular.z = 0.0;
            }

            // Publish the message
            cmd_vel_publisher_->publish(twist_msg);

            // Optional: Show processed image
            cv::imshow("Processed Image", edges);
            cv::waitKey(1);
        }
        catch (const cv_bridge::Exception &e)
        {
            RCLCPP_ERROR(this->get_logger(), "cv_bridge exception: %s", e.what());
        }
    }

    rclcpp::Publisher<geometry_msgs::msg::Twist>::SharedPtr cmd_vel_publisher_;
    rclcpp::Subscription<sensor_msgs::msg::CompressedImage>::SharedPtr image_subscriber_;
    std::string turn_direction_; // Parameter to decide turn direction
};

int main(int argc, char *argv[])
{
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<RobotControlNode>());
    rclcpp::shutdown();
    return 0;
}

// https://github.com/nunuki-crew/sigueme-esta/tree/5475b890108ca46c5b0c1bb88fd63924b7174e0a/src/el5206_gazebo