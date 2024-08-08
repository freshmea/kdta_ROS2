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
find_package(sensor_msgs REQUIRED)
find_package(cv_bridge REQUIRED)
find_package(OpenCV REQUIRED)


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

add_executable(canny_camera src/canny_camera.cpp)
ament_target_dependencies(canny_camera rclcpp sensor_msgs cv_bridge OpenCV)

add_executable(canny_camera2 src/canny_camera2.cpp)
ament_target_dependencies(canny_camera2 rclcpp sensor_msgs cv_bridge OpenCV)

add_executable(simple_ridar src/simple_ridar.cpp)
ament_target_dependencies(simple_ridar rclcpp sensor_msgs)

add_executable(stay_thirty src/stay_thirty.cpp)
ament_target_dependencies(stay_thirty rclcpp geometry_msgs sensor_msgs)

add_executable(follow_wall src/follow_wall.cpp)
ament_target_dependencies(follow_wall rclcpp geometry_msgs sensor_msgs)

#install
install(TARGETS
  moveTurtleSim
  # moveTurtleSim2
  moveTurtleBot
  moveTurtleBot2
  rotate_turtle
  canny_camera
  canny_camera2
  simple_ridar
  follow_wall
  DESTINATION lib/${PROJECT_NAME}
)

if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  set(ament_cmake_copyright_FOUND TRUE)
  set(ament_cmake_cpplint_FOUND TRUE)
  ament_lint_auto_find_test_dependencies()
endif()

ament_package()
