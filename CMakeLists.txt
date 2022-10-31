cmake_minimum_required(VERSION 3.21)
project(BigReal2)

set(CMAKE_CXX_STANDARD 17)

add_executable(BigReal2 main.cpp BigReal.cpp BigReal.h BigDecimalIntClass.cpp BigDecimalIntClass.h)
