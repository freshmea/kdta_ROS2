cmake_minimum_required(VERSION 3.8)
project(arithmetic)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()


find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(interface_example REQUIRED)
find_package(rclcpp_action REQUIRED)

include_directories(include)

#add executable
add_executable(calculator src/calculator/calculator.cpp src/calculator/main.cpp)
ament_target_dependencies(calculator rclcpp interface_example rclcpp_action)

add_executable(argument src/arithmetic/argument.cpp)
ament_target_dependencies(argument rclcpp interface_example)

add_executable(operator src/arithmetic/operator.cpp)
ament_target_dependencies(operator rclcpp interface_example)

#install
install(TARGETS
  calculator
  argument
  operator
  DESTINATION lib/${PROJECT_NAME}
)

install(DIRECTORY
  launch
  param
  DESTINATION share/${PROJECT_NAME})

if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  set(ament_cmake_copyright_FOUND TRUE)
  set(ament_cmake_cpplint_FOUND TRUE)
  ament_lint_auto_find_test_dependencies()
endif()

ament_package()
