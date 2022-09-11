cmake_minimum_required(VERSION 3.21)
project(p1)

set(CMAKE_CXX_STANDARD 14)

add_executable(p1 p1.cpp MemberList.cpp MemberList.h BookList.cpp BookList.h RatingList.cpp RatingList.h)
