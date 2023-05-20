cmake_minimum_required(VERSION 3.18.4)

project(MyTaskQueue)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -pthread")
# target_link_libraries(pthread)
set(CMAKE_CXX_STANDARD 11)

file(GLOB src_files "${CMAKE_SOURCE_DIR}/*.cpp")

add_executable(${PROJECT_NAME} ${src_files})