set(PROJECT_LIB gui_lib)

set( SRC_LIST
    battleship_view.cpp
    playerform.cpp
    setshipsform.cpp
    coordinatesystem.cpp
    gameform.cpp
    player.cpp
    digitalclock.cpp
    settingshipscoordinatesystem.cpp
    gamecoordinatesystem.cpp
)
set( HEADER_LIST
    battleship_view.h
    playerform.h
    setshipsform.h
    coordinatesystem.h
    gameform.h
    player.h
    digitalclock.h
    settingshipscoordinatesystem.h
    gamecoordinatesystem.h
)

add_library(${PROJECT_LIB} STATIC ${SRC_LIST} ${HEADER_LIST})
target_link_libraries(${PROJECT_LIB} Qt5::Widgets)
