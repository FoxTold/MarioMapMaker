cmake_minimum_required(VERSION 3.15)
project(MarioMapCreator)
message("${CMAKE_CURRENT_SOURCE_DIR}/build")
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/build")
list(APPEND CMAKE_PREFIX_PATH "${CMAKE_CURRENT_SOURCE_DIR}/build")

find_package(SFML 2.5.1 COMPONENTS graphics audio REQUIRED)

add_executable(${PROJECT_NAME} src/main.cpp)
target_link_libraries(${PROJECT_NAME} sfml-graphics sfml-audio)