#project config

cmake_minimum_required(VERSION 3.10)

project(bar)

#set(CMAKE_UNITY_BUILD ON)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

file(GLOB bar_src_files
	"../src/*.h"
	"src/main.cpp"
)

add_executable(bar ${bar_src_files})

if(WIN32)

else()

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -Werror -fno-exceptions -fno-rtti -std=c++23 -fomit-frame-pointer -Wall -Wextra -O0")

endif()

include_directories("src/headers/")
include_directories("src/")
include_directories("./")

#destoer lib
include_directories("destoer-lib/src/")

