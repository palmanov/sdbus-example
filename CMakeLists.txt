cmake_minimum_required(VERSION 3.18)
project(sdbus_example)

set(CMAKE_CXX_STANDARD 17)

find_package(sdbus-c++ REQUIRED)

add_executable(sdbus_example main.cpp
               udisks2-adaptor.h udisks2-proxy.h)
target_link_libraries(sdbus_example PRIVATE SDBusCpp::sdbus-c++)