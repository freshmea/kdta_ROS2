from launch import LaunchDescription
from launch_ros.actions import Node


def generate_launch_description():
    return LaunchDescription([
        Node(package='arithmetic',
             executable='argument',
             output='screen',
             ),
        Node(package='arithmetic',
             executable='calculator',
             output='screen'
             ),
        Node(package='arithmetic',
             executable='operator',
             output='screen'
             )
        ])
