 
cmake_minimum_required(VERSION 3.1.0)

project(battleship) #name of the project
set(PROJECT_LIB ${PROJECT_NAME}_lib) #name of library (we compile our application first as library)

# Options. Turn on with 'cmake -Dmyvarname=ON'.
# option(CREATE_TESTS "Build all tests." OFF)
option(CREATE_TESTS "Build all tests." ON)


add_definitions(-std=c++14 -Wall) #use c++11 standard (default is gnu++11 on gcc) and -Wall enables almost all the warnings 
# Find includes in corresponding build directories
# set(CMAKE_INCLUDE_CURRENT_DIR ON)
include_directories(${PROJECT_SOURCE_DIR})
# include_directories(${CMAKE_CURRENT_SOURCE_DIR})
# Instruct CMake to run moc automatically when needed.
set(CMAKE_AUTOMOC ON)

# Find the Qt library
find_package(Qt5 COMPONENTS Core Widgets Network REQUIRED)

set( SRC_LIST
    main.cpp
    battleship_controller.cpp
)
set( HEADER_LIST
    battleship_controller.h
)

add_subdirectory(common)
add_subdirectory(gui)
add_subdirectory(model)


# Key idea: SEPARATE OUT out main() function into its own file so it can be its
# own executable. Separating out main() means you can add this library to be
# used elsewhere. Like in this case in a Unit-Test
add_library(${PROJECT_LIB} ${SRC_LIST} ${HEADER_LIST})
# Use the Widgets module from Qt 5.
target_link_libraries(${PROJECT_LIB} Qt5::Widgets common_lib gui_lib model_lib)

add_executable(${PROJECT_NAME} WIN32 main.cpp)
target_link_libraries(${PROJECT_NAME} ${PROJECT_LIB})



################################
# Testing
################################
if (CREATE_TESTS)
  # This adds another subdirectory, which has 'project(gtest)'.
  add_subdirectory(lib/gtest-1.8.0)

  enable_testing()

  # Include the gtest library. gtest_SOURCE_DIR is available due to
  # 'project(gtest)' above.
  include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

  ##############
  # Unit Tests
  ##############
  add_executable(run_model_test test_model.cpp)

  # Standard linking to gtest stuff.
  target_link_libraries(run_model_test gtest gtest_main)

  # Extra linking for the project.
  target_link_libraries(run_model_test ${PROJECT_LIB})

  # This is so you can do 'make test' to see all your tests run, instead of
  # manually running the executable run_model_test to see those specific tests.
  add_test(NAME that-test-I-made COMMAND run_model_test)

  
  add_executable(run_connection_test test_connection.cpp)
  target_link_libraries(run_connection_test gtest gtest_main)
  target_link_libraries(run_connection_test ${PROJECT_LIB})
  add_test(NAME socket-test COMMAND run_connection_test)
  
  # You can also omit NAME and COMMAND. The second argument could be some other
  # test executable.
  #add_test(that-other-test-I-made run_model_test)
endif()
