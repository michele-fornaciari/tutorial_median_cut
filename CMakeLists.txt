cmake_minimum_required(VERSION 3.16)

project(mcut LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(mcut
	src/main.cpp

	src/image3b.cpp
	src/image3b.h
	src/pixel.h	
	src/utils.cpp
	src/utils.h
	
	3rdparty/stb/stb_image.h	
	3rdparty/cimg/CImg.h
	3rdparty/cli11/CLI11.hpp
)

target_include_directories(mcut PRIVATE
	3rdparty
)

