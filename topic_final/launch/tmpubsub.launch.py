# tmpubsub.launch.py
from launch import LaunchDescription
from launch_ros.actions import Node


def generate_launch_description():
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
             output='screen',)
        ])
