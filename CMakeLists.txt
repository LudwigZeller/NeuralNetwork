cmake_minimum_required(VERSION 3.22)
project(NodeNetwork)

set(CMAKE_CXX_STANDARD 23)

add_executable(NodeNetwork main.cpp Network/Node.cpp Network/Node.hpp Network/Layer.cpp Network/Layer.hpp Network/Network.cpp Network/Network.hpp)
