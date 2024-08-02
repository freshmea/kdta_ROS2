cmake_minimum_required(VERSION 3.8)
project(simple_pkg_cpp)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(std_msgs REQUIRED)
find_package(OpenCV REQUIRED)
find_package(example_interfaces REQUIRED)
find_package(rcl_interfaces REQUIRED)

# include directories
include_directories(include)

# excutable
add_executable(helloword src/helloworld.cpp)

add_executable(helloOpenCV src/helloOpenCV.cpp)
target_link_libraries(helloOpenCV ${OpenCV_LIBS})

add_executable(hello_publisher src/hello_publisher.cpp)
ament_target_dependencies(hello_publisher rclcpp std_msgs)

add_executable(hello_publisher2 src/hello_publisher2.cpp)
ament_target_dependencies(hello_publisher2 rclcpp std_msgs)

add_executable(hello_publisher_class src/hello_publisher_class.cpp)
ament_target_dependencies(hello_publisher_class rclcpp std_msgs)

add_executable(hello_publisher_class2 src/hello_publisher_class2.cpp src/publisher.cpp)
ament_target_dependencies(hello_publisher_class2 rclcpp std_msgs)

add_executable(hello_subscriber_class src/hello_subscriber_class.cpp src/subscriber.cpp)
ament_target_dependencies(hello_subscriber_class rclcpp std_msgs)

add_executable(time_publisher_class src/time_publisher_class.cpp src/time_pub.cpp)
ament_target_dependencies(time_publisher_class rclcpp std_msgs)

add_executable(time_subscriber_class src/time_subscriber_class.cpp src/time_sub.cpp)
ament_target_dependencies(time_subscriber_class rclcpp std_msgs)

add_executable(simple_service_server src/simple_service_server.cpp)
ament_target_dependencies(simple_service_server rclcpp std_msgs example_interfaces)

add_executable(simple_service_client src/simple_service_client.cpp)
ament_target_dependencies(simple_service_client rclcpp std_msgs example_interfaces)

add_executable(simple_service_client2 src/simple_service_client2.cpp)
ament_target_dependencies(simple_service_client2 rclcpp std_msgs example_interfaces rcl_interfaces)

#install
install(TARGETS
  helloword
  helloOpenCV
  hello_publisher
  hello_publisher2
  hello_publisher_class
  hello_publisher_class2
  hello_subscriber_class
  time_publisher_class
  time_subscriber_class
  simple_service_server
  simple_service_client
  simple_service_client2
  DESTINATION lib/${PROJECT_NAME}
)

if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  set(ament_cmake_copyright_FOUND TRUE)
  set(ament_cmake_cpplint_FOUND TRUE)
  ament_lint_auto_find_test_dependencies()
endif()

ament_package()
