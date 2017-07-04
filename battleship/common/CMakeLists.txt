# set(CMAKE_AUTOMOC ON)

set(PROJECT_LIB common_lib)

set( SRC_LIST
    user_friendly_exception.cpp
)
set( HEADER_LIST
    user_friendly_exception.h
    
    model_interface.h
    controller_interface.h
)

add_library(${PROJECT_LIB} STATIC ${SRC_LIST} ${HEADER_LIST})
target_link_libraries(${PROJECT_LIB})
