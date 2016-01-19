cmake_minimum_required(VERSION 2.8)

project(kmeans)
find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
include_directories(${OPENGL_INCLUDE_DIRS} ${GLUT_INCLUDE_DIRS})
SET(CMAKE_CXX_FLAGS "-std=c++11")
add_executable(kmeans main.cpp kmeans.h type_traits.h zip.h distance.h)
target_link_libraries(kmeans ${OPENGL_LIBRARIES} ${GLUT_LIBRARY})
