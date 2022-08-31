cmake_minimum_required(VERSION 3.23)
project(snake_game)

set(CMAKE_CXX_STANDARD 20)


add_link_options(-lglut -lGLU -lGL)
add_executable(snake_game src/main.cpp src/snake.cpp src/fruit.cpp)
find_package(OpenGL REQUIRED)
include_directories(${OPENGL_INCLUDE_DIRS})
find_package(GLUT REQUIRED)
include_directories( ${GLUT_INCLUDE_DIRS} )
find_package(GLEW REQUIRED)
include_directories(${GLEW_INCLUDE_DIRS})

target_link_libraries(snake_game ${OPENGL_LIBRARIES} ${GLUT_LIBRARY} ${GLEW_LIBRARIES})
