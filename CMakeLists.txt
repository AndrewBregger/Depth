cmake_minimum_required(VERSION 3.0)

project(game VERSION 0.0.1 LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 20)

find_package(PkgConfig REQUIRED)

add_subdirectory(engine)

set(ENGINE_INCLUDE ${CMAKE_SOURCE_DIR}/engine)

#add_library(STB_IMAGE ${CMAKE_SOURCE_DIR}/external/stbi/stb_image.cpp)

pkg_search_module(GLFW REQUIRED glfw3)
pkg_search_module(OpenGL REQUIRED gl)
pkg_search_module(GLM REQUIRED glm)


set(INCLUDE_DIRECTORY	${CMAKE_SOURCE_DIR}/src)
set(INCLUDE_EXTERNAL	${CMAKE_SOURCE_DIR}/external/include)
# set(LIBS_EXTERNAL		${CMAKE_SOURCE_DIR}/external/lib)

include_directories(${GLFW_INCLUDE_DIRS} ${INCLUDE_DIRECTORY}
	${INCLUDE_EXTERNAL} ${GLM_INCLUDE_DIRS} ${ENGINE_INCLUDE})

link_directories(${LIBS_EXTERNAL})

file(GLOB_RECURSE SOURCE_LIST 
	${CMAKE_SOURCE_DIR}/src/*.hpp
	${CMAKE_SOURCE_DIR}/src/*.cpp)

message(STATUS "Sources found ${SOURCE_LIST}")

add_executable(${PROJECT_NAME} ${SOURCE_LIST})

target_link_libraries(${PROJECT_NAME}
	${GLFW_STATIC_LIBRARIES}
	GL
	engine)


# set_target_properties(${PROJECT_NAME} PROPERTIES
#     VERSION ${PROJECT_VERSION}
#     SOVERSION 1)

# install(TARGETS ${PROJECT_NAME} EXPORT Engine2d 
#     ARCHIVE  DESTINATION ${CMAKE_INSTALL_LIBDIR}
#     LIBRARY  DESTINATION ${CMAKE_INSTALL_LIBDIR}
#     RUNTIME  DESTINATION ${CMAKE_INSTALL_BINDIR})
# install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/${PROJECT_NAME})

# install(EXPORT MyLibConfig DESTINATION share/MyLib/cmake)

# export(TARGETS ${PROJECT_NAME} FILE Engine2d.cmake)