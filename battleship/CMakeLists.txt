 
cmake_minimum_required(VERSION 3.1.0)

project(battleship) #name of the project
set(PROJECT_LIB ${PROJECT_NAME}_lib) #name of library (we compile our application first as library)


add_definitions(-std=c++11 -Wall)
# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)
# Instruct CMake to run moc automatically when needed.
set(CMAKE_AUTOMOC ON)

# Find the QtWidgets library
find_package(Qt5Widgets)

set( SRC_LIST
    main.cpp
)
set( HEADER_LIST

)

add_subdirectory(gui)

# Tell CMake to create the helloworld executable
# add_executable(${PROJECT_NAME} WIN32 ${SRC_LIST} ${HEADER_LIST})
add_library(${PROJECT_LIB} ${SRC_LIST} ${HEADER_LIST})
# Use the Widgets module from Qt 5.
target_link_libraries(${PROJECT_LIB} Qt5::Widgets gui_lib)

add_executable(${PROJECT_NAME} main.cpp)
target_link_libraries(${PROJECT_NAME} ${PROJECT_LIB})
# Key idea: SEPARATE OUT your main() function into its own file so it can be its
# own executable. Separating out main() means you can add this library to be
# used elsewhere. Like in this case in a Unit-Test


