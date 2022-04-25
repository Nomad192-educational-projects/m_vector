cmake_minimum_required(VERSION 3.20)
project(m_vector)

set(CMAKE_CXX_STANDARD 14)

add_executable(m_vector main.cpp m_vector.h exception.cpp exception.h)
