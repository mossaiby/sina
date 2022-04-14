# CMake list for sina

cmake_minimum_required(VERSION 3.10.2)
project(sina)

message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")

# Enable OpenMP and code optimization if not in debug mode

if(NOT CMAKE_BUILD_TYPE MATCHES Debug)

  find_package(OpenMP)
  if(OPENMP_FOUND)
    message(STATUS "Enabling OpenMP")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${OpenMP_EXE_LINKER_FLAGS}")
  endif(OPENMP_FOUND)

  if(UNIX)
    message(STATUS "Optimizing for current hardware")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -march=native")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -march=native")
  endif(UNIX)

endif(NOT CMAKE_BUILD_TYPE MATCHES Debug)

# Use C++11 standard

set(CMAKE_CXX_STANDARD 11)

# Include directories

include_directories("${PROJECT_SOURCE_DIR}/src")

# Search for test files and add them

enable_testing()

file(GLOB TEST_FILES "${PROJECT_SOURCE_DIR}/test/*.cpp")
foreach(TEST_FILE ${TEST_FILES})
  get_filename_component(TEST_FILENAME ${TEST_FILE} NAME)
  string(REGEX REPLACE ".cpp" "" TEST_NAME ${TEST_FILENAME})
  add_executable(${TEST_NAME} ${TEST_FILE})
  add_test(${TEST_NAME} ${PROJECT_SOURCE_DIR}/build/${TEST_NAME})
  if(UNIX)
    add_custom_target(run-${TEST_NAME} COMMAND ${PROJECT_SOURCE_DIR}/build/${TEST_NAME} DEPENDS ${TEST_NAME})
    add_custom_target(gdb-${TEST_NAME} COMMAND gdb ${PROJECT_SOURCE_DIR}/build/${TEST_NAME} DEPENDS ${TEST_NAME})
    add_custom_target(valgrind-${TEST_NAME} COMMAND valgrind --leak-check=yes ${PROJECT_SOURCE_DIR}/build/${TEST_NAME} DEPENDS ${TEST_NAME})
  endif(UNIX)
  install(TARGETS ${TEST_NAME} DESTINATION "${PROJECT_SOURCE_DIR}/build")
endforeach(TEST_FILE ${TEST_FILES})