 
cmake_minimum_required(VERSION 3.1.0)

project(battleship) #name of the project
set(PROJECT_LIB ${PROJECT_NAME}_lib) #name of library (we compile our application first as library)


add_definitions(-std=c++11 -Wall) #use c++11 standard (default is gnu++11 on gcc) and -Wall enables almost all the warnings 
# Find includes in corresponding build directories
# set(CMAKE_INCLUDE_CURRENT_DIR ON)
include_directories(${PROJECT_SOURCE_DIR})
# Instruct CMake to run moc automatically when needed.
set(CMAKE_AUTOMOC ON)

# Find the QtWidgets library
find_package(Qt5Widgets)
find_package(Qt5Network)

set( SRC_LIST
    main.cpp
    application.cpp
)
set( HEADER_LIST
    application.h
)

add_subdirectory(gui)
add_subdirectory(model)


# Key idea: SEPARATE OUT out main() function into its own file so it can be its
# own executable. Separating out main() means you can add this library to be
# used elsewhere. Like in this case in a Unit-Test
add_library(${PROJECT_LIB} ${SRC_LIST} ${HEADER_LIST})
# Use the Widgets module from Qt 5.
target_link_libraries(${PROJECT_LIB} Qt5::Widgets gui_lib model_lib)

add_executable(${PROJECT_NAME} WIN32 main.cpp)
target_link_libraries(${PROJECT_NAME} ${PROJECT_LIB})


