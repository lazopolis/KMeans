


cmake_minimum_required(VERSION 2.6)
project(ehixstests)



#set (CMAKE_CXX_FLAGS "-Wno-return-type-c-linkage -Wno-deprecated-writable-strings -Wno-delete-non-virtual-dtor ")
#set (CMAKE_CXX_FLAGS "-Wno-return-type-c-linkage -Wno-deprecated-writable-strings -Wno-delete-non-virtual-dtor ")


include_directories(
                    /Users/lazopolis/other_codes/gtest-1.6.0/include
                    )

link_directories(
               /Users/lazopolis/other_codes/gtest-1.6.0/build/
               )

add_library(kmeanslib
                    ../kmeans.cpp
                    )



add_executable(tests  ../main.cpp)
target_link_libraries(tests  kmeanslib gtest m)
                                        









