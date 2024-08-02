# tmpubsub.launch.py
import os

from ament_index_python import get_package_share_directory
from launch import LaunchDescription
from launch.substitutions import LaunchConfiguration
from launch_ros.actions import Node


def generate_launch_description():
    param_dir = LaunchConfiguration('param_dir', default=os.path.join(
        get_package_share_directory('topic_final'),
        'param',
        'turtlesim.yaml'
        ))

    return LaunchDescription([
        Node(package='topic_final',
             executable='mpub',
             output='screen',
             ),
        Node(package='topic_final',
             executable='msub',
             output='screen',
             ),
        Node(package='topic_final',
             executable='msub2',
             output='screen',
             ),
        Node(package='topic_final',
             executable='mtsub',
             output='screen',
             ),
        Node(package='topic_final',
             executable='tpub',
             output='screen',
             ),
        Node(package='turtlesim',
             executable='turtlesim_node',
             output='screen',
             parameters=[param_dir])
        ])
