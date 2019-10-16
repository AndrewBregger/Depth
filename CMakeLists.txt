cmake_minimum_required(VERSION 3.0)

project(game)
set(CMAKE_CXX_STANDARD 20)

find_package(PkgConfig REQUIRED)

#add_library(STB_IMAGE ${CMAKE_SOURCE_DIR}/external/stbi/stb_image.cpp)

add_library(GLAD ${CMAKE_SOURCE_DIR}/external/glad/src/glad.c)


pkg_search_module(GLFW REQUIRED glfw3)
pkg_search_module(OpenGL REQUIRED gl)
pkg_search_module(GLM REQUIRED glm)

set(INCLUDE_DIRECTORY	${CMAKE_SOURCE_DIR}/src)
set(INCLUDE_EXTERNAL	${CMAKE_SOURCE_DIR}/external/include)
set(LIBS_EXTERNAL		${CMAKE_SOURCE_DIR}/external/lib)

include_directories(${GLFW_INCLUDE_DIRS} ${INCLUDE_DIRECTORY}
	${INCLUDE_EXTERNAL} ${GLM_INCLUDE_DIRS})

link_directories(${LIBS_EXTERNAL})

#aux_source_directory(./src/ SOURCE_LIST)
file(GLOB_RECURSE SOURCE_LIST 
	${CMAKE_SOURCE_DIR}/src/*.hpp
	${CMAKE_SOURCE_DIR}/src/*.cpp)

message(STATUS "Sources found ${SOURCE_LIST}")

add_executable(${PROJECT_NAME} ${SOURCE_LIST})
target_link_libraries(${PROJECT_NAME}
	${GLFW_STATIC_LIBRARIES}
	GL
	${spdlog}
	GLAD)

