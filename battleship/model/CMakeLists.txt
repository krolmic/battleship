# set(CMAKE_AUTOMOC ON)

set(PROJECT_LIB model_lib)

set( SRC_LIST
    battleship_model.cpp
    connection.cpp
    connection_guest.cpp
    connection_host.cpp
    game.cpp
    game_guest.cpp
    game_host.cpp
    communicator.cpp
    player.cpp
    point.cpp
    ship.cpp
    coordinate_system.cpp
)
set( HEADER_LIST
    battleship_model.h
    connection.h
    connection_guest.h
    connection_host.h
    game.h
    game_guest.h
    game_host.h
    communicator.h
    player.h
    point.h
    ship.h
    coordinate_system.h
)

add_library(${PROJECT_LIB} STATIC ${SRC_LIST} ${HEADER_LIST})
target_link_libraries(${PROJECT_LIB} Qt5::Network common_lib)
