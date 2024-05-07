cmake_minimum_required(VERSION 3.2)

project(obj3d)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${obj3d_SOURCE_DIR}")
set(CMAKE_EXPORT_COMPILE_COMMANDS ON CACHE INTERNAL "")

file(GLOB obj3d_SRC
    "${obj3d_SOURCE_DIR}/*.cpp"
)

add_executable(obj3d ${obj3d_SRC})

include_directories(obj3d ${SDL2_INCLUDE_DIRS})
include_directories(obj3d ${SDL2_IMAGE_INCLUDE_DIRS})

target_link_libraries(obj3d ${SDL2_LIBRARIES} ${SDL2_IMAGE_LIBRARIES})

