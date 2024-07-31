
source /opt/ros/humble/setup.bash
source ~/kdta_ws/install/local_setup.bash

alias rt='ros2 topic list'
alias cw='cd ~/kdta_ws'
alias cs='cd ~/kdta_ws/src'
alias cb='colcon build --symlink-install'
alias sb='source ~/.bashrc'
alias nb='sudo nano ~/.bashrc'

export ROS_DOMAIN_ID=20
export TURTLEBOT3_MODEL=burger
