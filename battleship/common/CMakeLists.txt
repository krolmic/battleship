# set(CMAKE_AUTOMOC ON)

set(PROJECT_LIB common_lib)

set( SRC_LIST
    user_friendly_exception.cpp
    user_info.cpp
)
set( HEADER_LIST
    user_friendly_exception.h
    user_info.h
    
    model_interface.h
    controller_interface.h
    battleship_observer.h
)

add_library(${PROJECT_LIB} STATIC ${SRC_LIST} ${HEADER_LIST})
target_link_libraries(${PROJECT_LIB} Qt5::Widgets)
