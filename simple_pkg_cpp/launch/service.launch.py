# tmpubsub.launch.py
import os

from ament_index_python import get_package_share_directory
from launch import LaunchDescription
from launch.substitutions import LaunchConfiguration
from launch_ros.actions import Node


def generate_launch_description():
    param_dir = LaunchConfiguration('param_dir', default=os.path.join(
        get_package_share_directory('simple_pkg_cpp'),
        'param',
        'service.yaml'
        ))

    return LaunchDescription([
        Node(package='simple_pkg_cpp',
             executable='simple_service_server',
             output='screen',
             ),
        Node(package='simple_pkg_cpp',
             executable='simple_service_client2',
             output='screen',
             parameters=[param_dir])
        ])
