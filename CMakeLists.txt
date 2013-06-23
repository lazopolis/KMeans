project(kmeans)

cmake_minimum_required(VERSION 2.6)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC -Wconversion -Werror -fno-omit-frame-pointer")

include_directories(/home/george/Desktop/gtest-1.6.0/include)
include_directories(${CMAKE_SOURCE_DIR})

set(SRCS kmeans.cpp kmeans.h)

add_library(kmeanslib ${SRCS})

add_executable(tests ${CMAKE_SOURCE_DIR}/main.cpp)
target_link_libraries(tests kmeanslib gtest m pthread)
