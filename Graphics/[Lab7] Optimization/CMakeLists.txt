cmake_minimum_required(VERSION 3.13)
project(Lab6)

set(CMAKE_CXX_FLAGS "-lSOIL ${CMAKE_CXX_FLAGS}")
set(CMAKE_CXX_STANDARD 11)
# add_library(-lGL -lGLEW -lglfw3)
set(CMAKE_PREFIX_PATH /usr/local/lib/cmake/glfw3)

find_package (PkgConfig REQUIRED)
find_package (OpenGL REQUIRED)
find_package (glfw3 REQUIRED)
find_package (GLEW REQUIRED STATIC)

add_executable(Lab6 main.cpp SOIL.h Sphere.cpp Sphere.h Config.cpp Config.h Mesh.cpp Mesh.h Base.cpp Base.h Cube.cpp Cube.h Polygon.h defines.h)

#Pain/SuthHodgClip/main.cpp

target_link_libraries (Lab6 glfw SOIL ${OPENGL_LIBRARIES} ${GLFW3_LIBRARY}
        ${GLEW_LIBRARY})