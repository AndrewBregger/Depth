cmake_minimum_required(VERSION 3.0)

project(test)

find_library(engine engine ../build/engine)

set(ENGINE_INCLUDE ../engine/ ../external/include)


file(GLOB TEST_SOURCES RELATIVE ${CMAKE_SOURCE_DIR}/unit  unit/*.cpp)

include_directories(${CMAKE_SOURCE_DIR} ${ENGINE_INCLUDE})
link_directories(../build/engine)


message(STATUS "TESTS ${TEST_SOURCES}")

foreach(test ${TEST_SOURCES})
	# get_filename_component(filename ${test} REALPATH BASE_DIR ${CMAKE_SOURCE_DIR}/tests/unit)
	string(REPLACE ".cpp" "" test_name ${test})
	add_executable(${test_name} unit/${test})
	target_link_libraries(${test_name} engine)
endforeach(test ${TEST_SOURCES})
