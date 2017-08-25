#cmake_minimum_required(VERSION 3.7)

project(cli)

add_executable(cli client/client.cpp
		client/client.hpp
		client/main.cpp)
