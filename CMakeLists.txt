cmake_minimum_required(VERSION 3.10)

project(Psychic-Guacamole VERSION 0.1)

set(CUSTOM_INCLUDE_DIRECTORIES "include/")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -O0 -ggdb")

include_directories(${CUSTOM_INCLUDE_DIRECTORIES})
find_package(SDL2 REQUIRED)

# Application executable
file(GLOB_RECURSE Source CONFIGURE_DEPENDS src/*.cpp)

add_executable(psychic-guacamole ${Source})
target_include_directories(psychic-guacamole PUBLIC ${SDL2_INCLUDE_DIR})
target_link_libraries(psychic-guacamole PUBLIC ${SDL2_LIBRARIES})