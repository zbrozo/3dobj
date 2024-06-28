cmake_minimum_required(VERSION 3.16)

project(obj3d)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${obj3d_SOURCE_DIR}")
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")
set(CMAKE_BUILD_TYPE Debug)

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_ttf REQUIRED)

find_package(Boost COMPONENTS filesystem system unit_test_framework program_options log REQUIRED)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON CACHE INTERNAL "")

set(generator_SRC
  src/GeneratorMain.cpp
  src/ObjectFactoryBase.cpp
  src/ObjectFactories.cpp
  src/ComponentFactoryBase.cpp
  src/ComponentFactories.cpp
  src/Components.cpp
  src/AmigaFile.cpp
  src/Cube.cpp
  src/CubeExt.cpp
  src/Thorus.cpp
  src/Composite.cpp
  src/Face.cpp
  src/Rotation.cpp
  src/Vertex3D.cpp
  src/Vector3D.cpp
  src/Object3D.cpp
  src/Vertices.cpp
  src/Faces.cpp)

set(viewer_SRC
  src/ViewerMain.cpp
  src/AmigaFile.cpp
  src/Face.cpp
  src/Rotation.cpp
  src/Vertex3D.cpp
  src/Vector3D.cpp
  src/Object3D.cpp
  src/Vertices.cpp
  src/Faces.cpp)

set(tests_SRC
  src/Cube.cpp
  src/CubeExt.cpp
  src/Thorus.cpp
  src/Composite.cpp
  src/Components.cpp
  src/Face.cpp
  src/Rotation.cpp
  src/Vertex3D.cpp
  src/Vector3D.cpp
  src/Vertices.cpp
  src/Faces.cpp
  src/Object3D.cpp
  src/ObjectFactoryBase.cpp
  src/ObjectFactories.cpp
  src/ComponentFactoryBase.cpp
  src/ComponentFactories.cpp
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
target_link_libraries(viewer SDL2::Main SDL2::Image SDL2::TTF ${Boost_LIBRARIES})
target_link_libraries(tests ${Boost_LIBRARIES})

enable_testing()
add_test(
  NAME boost_test1
  COMMAND $<TARGET_FILE:tests>
)
