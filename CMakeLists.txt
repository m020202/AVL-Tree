cmake_minimum_required(VERSION 3.27)
project(oss)

set(CMAKE_CXX_STANDARD 17)

# 헤더 파일 경로 지정 (header 폴더에 있는 헤더들을 포함)
include_directories(${CMAKE_SOURCE_DIR}/header)

# 소스 파일 목록 지정
set(SOURCES
        main.cpp
        source/avl_tree_adaptee.cc
        source/avl_tree_adapter.cc # 소스 폴더에 있는 소스 파일
)

# 실행 파일 생성
add_executable(oss ${SOURCES})