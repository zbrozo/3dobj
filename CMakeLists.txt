# For SLD2 image: https://github.com/trenki2/SDL2Test

cmake_minimum_required(VERSION 3.5)

project(obj3d)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${obj3d_SOURCE_DIR}")
set(CMAKE_EXPORT_COMPILE_COMMANDS ON CACHE INTERNAL "")

set(generator_SRC
        src/generator.cpp
        src/amigafile.cpp
        src/cube.cpp
        src/cube2.cpp
        src/thorus.cpp
        src/face.cpp
        src/object3d.cpp
        src/rotation.cpp
        src/vector3d.cpp
        src/vertex.cpp
        src/vertices.cpp)

set(viewer_SRC
        src/main.cpp
        src/amigafile.cpp
        src/cube.cpp
        src/cube2.cpp
        src/thorus.cpp
        src/face.cpp
        src/object3d.cpp
        src/rotation.cpp
        src/vector3d.cpp
        src/vertex.cpp
        src/vertices.cpp)

add_executable(generator ${generator_SRC})
add_executable(viewer ${viewer_SRC})

include_directories(viewer ${SDL2_INCLUDE_DIRS})
include_directories(viewer ${SDL2_IMAGE_INCLUDE_DIRS})

target_link_libraries(viewer ${SDL2_LIBRARIES} ${SDL2_IMAGE_LIBRARIES})

