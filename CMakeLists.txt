
set(MY_PROJECT_NAME Hatching)
cmake_minimum_required(VERSION 3.17)
project(${MY_PROJECT_NAME})

set(CMAKE_CXX_STANDARD 17)

if (WIN32)
    set(PATH_TO_GLFW_HEADER C:/Users/cvoegele/Development/glfw-3.3.3/include)
    set(PATH_TO_GLFW_LIB C:/Users/cvoegele/Development/glfw-3.3.3/build/src/Release)
    set(GLFW_LIB_NAME glfw3.lib)
    set(ADDITIONAL_LIBS )
endif ()

if (APPLE)
    message ("-- Compiling on Mac OSX")
    set(PATH_TO_GLFW_HEADER ~/glfw-3.3.3.bin.MACOS/include)
    set(PATH_TO_GLFW_LIB ~/glfw-3.3.3.bin.MACOS/lib-x86_64)
    set(GLFW_LIB_NAME libglfw3.a)
    set(ADDITIONAL_LIBS )

    find_library(COCOA_LIBRARY Cocoa)
    find_library(OPENGL_LIBRARY OpenGL)
    find_library(IOKIT_LIBRARY IOKit)
    find_library(COREVIDEO_LIBRARY CoreVideo)
    set(ADDITIONAL_LIBS ${COCOA_LIBRARY} ${OPENGL_LIBRARY} ${IOKIT_LIBRARY} ${COREVIDEO_LIBRARY})
endif()

include_directories(./external ${PATH_TO_GLFW_HEADER})
link_directories(${PATH_TO_GLFW_LIB})

file(GLOB_RECURSE SRC_external
        RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_CURRENT_SOURCE_DIR}/external/*.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/external/*.c
        ${CMAKE_CURRENT_SOURCE_DIR}/external/*.h)

file(GLOB_RECURSE SRC_src
        RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/*.c
        ${CMAKE_CURRENT_SOURCE_DIR}/src/*.h)

source_group(external   FILES ${SRC_external})
source_group(src   FILES ${SRC_src})

add_executable(${MY_PROJECT_NAME} ${SRC_external} ${SRC_src} main.cpp src/Shader.cpp src/Shader.h src/Material.cpp src/Material.h src/Util.cpp src/Util.h src/Mesh.cpp src/Mesh.h src/Renderer.cpp src/Renderer.h src/Camera.cpp src/Camera.h src/Cube.cpp src/Cube.h src/Image.cpp src/Image.h src/Texture.cpp src/Texture.h)

target_link_libraries(${MY_PROJECT_NAME} ${GLFW_LIB_NAME} ${ADDITIONAL_LIBS})