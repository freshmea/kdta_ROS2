cmake_minimum_required(VERSION 3.0)
project(HelloWorld)

find_package(OpenCV REQUIRED)

add_executable(helloworld helloworld.cpp)
target_link_libraries(helloworld ${OpenCV_LIBS})
target_include_directories(helloworld PUBLIC ${OpenCV_LIB_DIR})