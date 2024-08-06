import os

from ament_index_python import get_package_share_directory
from launch import LaunchDescription
from launch.substitutions import LaunchConfiguration
from launch_ros.actions import Node


def generate_launch_description():
    param_dir = LaunchConfiguration('param_dir', default=os.path.join(
        get_package_share_directory('arithmetic'),
        'param',
        'arithmetic.yaml'
        ))
    return LaunchDescription([
        Node(package='arithmetic',
             executable='argument',
             output='screen',
             parameters=[param_dir]
             ),
        Node(package='arithmetic',
             executable='calculator',
             output='screen'
             ),
        Node(package='arithmetic',
             executable='operator',
             output='screen',
             parameters=[param_dir]
             )
        ])
