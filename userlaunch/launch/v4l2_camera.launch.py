from launch import LaunchDescription
from launch_ros.actions import Node
from launch.actions import DeclareLaunchArgument
from launch.substitutions import LaunchConfiguration
from ament_index_python.packages import get_package_share_directory
import os


def generate_launch_description():
    param_dir = LaunchConfiguration(
        "param_dir",
        default=os.path.join(
            get_package_share_directory("userlaunch"), "param", "v4l2_camera.yaml"
        ),
    )

    return LaunchDescription(
        [
            DeclareLaunchArgument(
                "param_dir",
                default_value=param_dir,
                description="Full path of parameter file",
            ),
            Node(
                package="v4l2_camera",
                executable="v4l2_camera_node",
                parameters=[param_dir],
                output="screen",
            ),
        ]
    )
