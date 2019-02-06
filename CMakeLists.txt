cmake_minimum_required(VERSION 3.9)
project(free_the_chick_cpp)

set(CMAKE_CXX_STANDARD 17)

set(EXECUTABLE_NAME "FreeTheChick")
add_executable(${EXECUTABLE_NAME} src/main.cpp include/Map.h src/Map.cpp)

# Detect and add SFML
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})
find_package(SFML REQUIRED system window graphics)
if(SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
    target_link_libraries(${EXECUTABLE_NAME} ${SFML_LIBRARIES})
endif()