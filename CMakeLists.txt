# For SLD2 image: https://github.com/trenki2/SDL2Test

cmake_minimum_required(VERSION 3.5)

project(obj3d)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_ttf REQUIRED)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${obj3d_SOURCE_DIR}")
set(CMAKE_EXPORT_COMPILE_COMMANDS ON CACHE INTERNAL "")

set(generator_SRC
        src/GeneratorMain.cpp
        src/AmigaFile.cpp
        src/Cube.cpp
        src/Cube2.cpp
        src/Thorus.cpp
        src/Face.cpp
        src/Object3d.cpp
        src/Rotation.cpp
        src/Vector3d.cpp
        src/Vertex.cpp
        src/Vertices.cpp)

set(viewer_SRC
        src/ViewerMain.cpp
        src/AmigaFile.cpp
        src/Face.cpp
        src/Object3d.cpp
        src/Rotation.cpp
        src/Vector3d.cpp
        src/Vertex.cpp
        src/Vertices.cpp)

add_executable(generator ${generator_SRC})
add_executable(viewer ${viewer_SRC})

target_include_directories(viewer PRIVATE ${SDL2_INCLUDE_DIRS})
target_include_directories(viewer PRIVATE ${SDL2_IMAGE_INCLUDE_DIRS})
target_include_directories(viewer PRIVATE ${SDL2_TTF_INCLUDE_DIRS})

target_link_libraries(viewer ${SDL2_LIBRARIES} ${SDL2_IMAGE_LIBRARIES} ${SDL2_TTF_LIBRARIES})

