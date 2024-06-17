cmake_minimum_required(VERSION 3.5)

project(obj3d)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${obj3d_SOURCE_DIR}")
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_ttf REQUIRED)

find_package(Boost COMPONENTS filesystem system unit_test_framework program_options REQUIRED)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON CACHE INTERNAL "")

set(generator_SRC
  src/GeneratorMain.cpp
  src/ObjectFactoryBase.cpp
  src/ObjectFactories.cpp
  src/ObjectComponents.cpp
  src/AmigaFile.cpp
  src/Cube.cpp
  src/CubeExt.cpp
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

set(tests_SRC
  src/Cube.cpp
  src/CubeExt.cpp
  src/Thorus.cpp
  src/ObjectComponents.cpp
  src/Face.cpp
  src/Vertices.cpp
  src/Vertex.cpp
  src/Rotation.cpp
  src/Vector3d.cpp
  src/Object3d.cpp
  src/ObjectFactoryBase.cpp
  src/ObjectFactories.cpp
  src/UnitTests.cpp
)

add_executable(generator ${generator_SRC})
add_executable(viewer ${viewer_SRC})

target_include_directories(viewer PRIVATE ${SDL2_INCLUDE_DIRS})
target_include_directories(viewer PRIVATE ${SDL2_IMAGE_INCLUDE_DIRS})
target_include_directories(viewer PRIVATE ${SDL2_TTF_INCLUDE_DIRS})

include_directories(${Boost_INCLUDE_DIRS})

add_executable(tests ${tests_SRC})

target_link_libraries(generator ${Boost_LIBRARIES})
target_link_libraries(viewer ${SDL2_LIBRARIES} ${SDL2_IMAGE_LIBRARIES} ${SDL2_TTF_LIBRARIES})
target_link_libraries(tests ${Boost_LIBRARIES})

enable_testing()
add_test(
  NAME boost_test1
  COMMAND $<TARGET_FILE:tests>
)
