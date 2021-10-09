cmake_minimum_required(VERSION 3.10)

project(Test VERSION 1.0)

set(CUSTOM_INCLUDE_DIRECTORIES "include/")
if(DEFINED ENV{CPP_INCLUDES})
	set(CUSTOM_INCLUDE_DIRECTORIES "${CUSTOM_INCLUDE_DIRECTORIES};$ENV{CPP_INCLUDES}")
endif()

include_directories(${CUSTOM_INCLUDE_DIRECTORIES})
find_package(SDL2 REQUIRED)

# Application executable
add_executable(app main.cpp)
target_include_directories(app PUBLIC ${SDL2_INCLUDE_DIR})
target_link_libraries(app PUBLIC ${SDL2_LIBRARIES})