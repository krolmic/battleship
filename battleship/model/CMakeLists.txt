# set(CMAKE_AUTOMOC ON)

set(PROJECT_LIB model_lib)

set( SRC_LIST
    connection.cpp
    connection_guest.cpp
    connection_host.cpp
    game.cpp
    game_guest.cpp
    game_host.cpp
    testqobject.cpp
)
set( HEADER_LIST
    connection.h
    connection_guest.h
    connection_host.cpp
    game.h
    game_guest.h
    game_host.h
    testqobject.h
)

add_library(${PROJECT_LIB} STATIC ${SRC_LIST} ${HEADER_LIST})
target_link_libraries(${PROJECT_LIB} Qt5::Network)
