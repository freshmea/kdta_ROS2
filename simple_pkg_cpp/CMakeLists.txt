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

#install
install(TARGETS
  helloword
  helloOpenCV
  hello_publisher
  hello_publisher2
  hello_publisher_class
  DESTINATION lib/${PROJECT_NAME}
)

if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  set(ament_cmake_copyright_FOUND TRUE)
  set(ament_cmake_cpplint_FOUND TRUE)
  ament_lint_auto_find_test_dependencies()
endif()

ament_package()
