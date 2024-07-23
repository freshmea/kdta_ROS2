cmake_minimum_required(VERSION 3.0)
project(windows)

find_package(OpenCV REQUIRED)

add_executable(windows windows.cpp)
target_link_libraries(windows ${OpenCV_LIBS})
target_include_directories(windows PUBLIC ${OpenCV_LIB_DIR})