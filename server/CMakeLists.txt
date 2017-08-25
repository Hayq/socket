cmake_minimum_required(VERSION 2.9)

project(server)

add_executable(server server/main.cpp
		server/server.hpp
		server/server.cpp)
