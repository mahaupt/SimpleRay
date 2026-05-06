cmake_minimum_required(VERSION 3.16)

project(SimpleRay LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(OpenGL REQUIRED)

find_package(glfw3 QUIET)

if(NOT TARGET glfw)
  find_path(GLFW_INCLUDE_DIR GLFW/glfw3.h)
  find_library(GLFW_LIBRARY NAMES glfw glfw3)

  if(NOT GLFW_INCLUDE_DIR OR NOT GLFW_LIBRARY)
    message(FATAL_ERROR "GLFW 3 was not found. Install GLFW or set glfw3_DIR/GLFW_LIBRARY/GLFW_INCLUDE_DIR.")
  endif()
endif()

add_executable(simpleray
  src/main.cpp
  src/Camera.cpp
  src/Cube.cpp
  src/GameObject.cpp
  src/LightSource.cpp
  src/Quaternion.cpp
  src/RayTracer.cpp
  src/Scene.cpp
  src/Sphere.cpp
  src/Vector3.cpp
)

target_include_directories(simpleray PRIVATE src)

if(GLFW_INCLUDE_DIR)
  target_include_directories(simpleray PRIVATE "${GLFW_INCLUDE_DIR}")
endif()

if(TARGET glfw)
  target_link_libraries(simpleray PRIVATE glfw)
else()
  target_link_libraries(simpleray PRIVATE "${GLFW_LIBRARY}")
endif()

target_link_libraries(simpleray PRIVATE OpenGL::GL)

if(UNIX AND NOT APPLE)
  target_link_libraries(simpleray PRIVATE dl m pthread)
endif()
