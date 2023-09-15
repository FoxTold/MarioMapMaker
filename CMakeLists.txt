cmake_minimum_required(VERSION 3.15)
project(MarioMapCreator)

set(SFML_STATIC_LIBRARIES TRUE)
set(BUILD_SHARED_LIBS FALSE)
set(SFML_DIR "deps/SFML/")

add_subdirectory(deps/SFML)
add_executable(${PROJECT_NAME} src/main.cpp)
target_link_libraries(${PROJECT_NAME} sfml-graphics sfml-audio)