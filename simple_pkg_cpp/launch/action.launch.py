from launch import LaunchDescription
from launch_ros.actions import Node


def generate_launch_description():
    return LaunchDescription([
        Node(package='simple_pkg_cpp',
             executable='simple_action_server',
             output='screen',
             ),
        Node(package='simple_pkg_cpp',
             executable='simple_action_client',
             output='screen'
             )
        ])
