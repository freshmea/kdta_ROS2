cmake_minimum_required(VERSION 3.8)
project(moveTSim)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(geometry_msgs REQUIRED)

include_directories(include)

#add excutable
add_executable(moveTurtleSim src/moveTurtleSim.cpp src/moveTurtle.cpp)
ament_target_dependencies(moveTurtleSim rclcpp geometry_msgs)

#install
install(TARGETS
  moveTurtleSim
  DESTINATION lib/${PROJECT_NAME}
)

if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  set(ament_cmake_copyright_FOUND TRUE)
  set(ament_cmake_cpplint_FOUND TRUE)
  ament_lint_auto_find_test_dependencies()
endif()

ament_package()
