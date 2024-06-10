cmake_minimum_required(VERSION 3.10)

# 프로젝트 이름 설정
project(ScrollGame)

# C++ 표준 설정
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# 하위 디렉토리 추가
add_subdirectory(ScrollGame)
add_subdirectory(LogSystem)