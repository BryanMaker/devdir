cmake_minimum_required(VERSION 2.6)
project(jsoncpp)

find_package(jsoncpp REQUIRED)

get_target_property(JSON_INC_PATH jsoncpp_lib INTERFACE_INCLUDE_DIRECTORIES)
include_directories(${JSON_INC_PATH})
add_executable(${PROJECT_NAME} jsoncpp.cpp)
target_link_libraries(${PROJECT_NAME} jsoncpp_lib)
target_include_directories(${PROJECT_NAME} PUBLIC ./)
