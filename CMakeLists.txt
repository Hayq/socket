cmake_minimum_required(VERSION 3.7)

set (CMAKE_CXX_FLAGS "-std=gnu++11 ${CMAKE_CXX_FLAGS}")

add_subdirectory( server )
add_subdirectory( client  )
