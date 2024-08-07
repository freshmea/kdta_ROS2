cmake_minimum_required(VERSION 3.8)
project(move_t_sim)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(geometry_msgs REQUIRED)
find_package(nav_msgs REQUIRED)
find_package(turtlesim REQUIRED)
find_package(tf2 REQUIRED)
find_package(rclcpp_action REQUIRED)

include_directories(include)

#add excutable
add_executable(moveTurtleSim src/moveTurtleSim.cpp src/moveTurtle.cpp)
ament_target_dependencies(moveTurtleSim rclcpp geometry_msgs)

# add_executable(moveTurtleSim2 src/moveTurtleSim2.cpp src/moveTurtle2.cpp)
# ament_target_dependencies(moveTurtleSim2 rclcpp geometry_msgs turtlesim)

add_executable(moveTurtleBot src/moveTurtleBot.cpp src/moveTurtleBotcpp.cpp)
ament_target_dependencies(moveTurtleBot rclcpp geometry_msgs nav_msgs)

add_executable(moveTurtleBot2 src/moveTurtleBot2.cpp src/moveTurtleBotcpp2.cpp)
ament_target_dependencies(moveTurtleBot2 rclcpp geometry_msgs nav_msgs tf2)

add_executable(rotate_turtle src/rotate_turtle.cpp)
ament_target_dependencies(rotate_turtle rclcpp turtlesim rclcpp_action)

#install
install(TARGETS
  moveTurtleSim
  # moveTurtleSim2
  moveTurtleBot
  moveTurtleBot2
  rotate_turtle
  DESTINATION lib/${PROJECT_NAME}
)

if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  set(ament_cmake_copyright_FOUND TRUE)
  set(ament_cmake_cpplint_FOUND TRUE)
  ament_lint_auto_find_test_dependencies()
endif()

ament_package()
