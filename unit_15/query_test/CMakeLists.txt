cmake_minimum_required(VERSION 3.10)

# 设置项目名称
project(QueryWordTest)

# 设置 C++ 标准
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# 收集当前文件夹下所有的 cpp 文件
file(GLOB SOURCES "*.cpp")

# 设置头文件路径
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

# 添加可执行文件
add_executable(${PROJECT_NAME} ${SOURCES})
