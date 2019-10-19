cmake_minimum_required(VERSION 3.0)
project(engine)

message(STATUS "Sources directory ${CMAKE_SOURCE_DIR}")

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_BUILD_TYPE Debug)

find_package(PkgConfig REQUIRED)

#add_library(STB_IMAGE ${CMAKE_SOURCE_DIR}/external/stbi/stb_image.cpp)

add_library(GLAD ${CMAKE_SOURCE_DIR}/external/glad/src/glad.c)


pkg_search_module(GLFW REQUIRED glfw3)
pkg_search_module(OpenGL REQUIRED gl)
pkg_search_module(GLM REQUIRED glm)

set(INCLUDE_DIRECTORY	${CMAKE_SOURCE_DIR}/engine/)
set(INCLUDE_EXTERNAL	${CMAKE_SOURCE_DIR}/external/include)
set(LIBS_EXTERNAL		${CMAKE_SOURCE_DIR}/external/lib)

message(STATUS "Includes: ${INCLUDE_DIRECTORY}\n${INCLUDE_EXTERNAL}")

include_directories(${GLFW_INCLUDE_DIRS} ${INCLUDE_DIRECTORY}
	${INCLUDE_EXTERNAL} ${GLM_INCLUDE_DIRS})

link_directories(${LIBS_EXTERNAL})

# Maybe add a source directory to the engine?
file(GLOB_RECURSE SOURCE_LIST 
	${CMAKE_SOURCE_DIR}/engine/*.cpp)

file(GLOB_RECURSE HEADER_LIST	
	${CMAKE_SOURCE_DIR}/engine/*.hpp)

message(STATUS "Sources found ${SOURCE_LIST} ${HEADER_LIST}")

add_library(${PROJECT_NAME} ${SOURCE_LIST} ${HEADER_LIST})

target_link_libraries(${PROJECT_NAME}
	PUBLIC
	${GLFW_STATIC_LIBRARIES}
	GL
	${spdlog}
	GLAD)

