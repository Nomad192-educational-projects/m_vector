cmake_minimum_required(VERSION 3.20)
project(m_vector_alena)

set(CMAKE_CXX_STANDARD 14)

add_executable(m_vector_alena main.cpp m_vector.h exception.cpp exception.h)