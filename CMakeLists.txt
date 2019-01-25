cmake_minimum_required(VERSION 3.6)
project(gomoku_ninuki CXX)

set(INCLUDE_DIRECTORY "./include")
set(GUI_INCLUDE_DIRECTORY "./include/SFMLGUI")

include_directories(${INCLUDE_DIRECTORY})
include_directories(${GUI_INCLUDE_DIRECTORY})

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(SOURCE_FILES
        src/Goban.cpp ${INCLUDE_DIRECTORY}/Goban.h
        src/Controller.cpp ${INCLUDE_DIRECTORY}/Controller.h
        src/Tree.cpp ${INCLUDE_DIRECTORY}/Tree.hpp
        src/AI.cpp ${INCLUDE_DIRECTORY}/AI.hpp
        src/Print.cpp ${INCLUDE_DIRECTORY}/Print.hpp
        src/Rave.cpp ${INCLUDE_DIRECTORY}/Rave.h
        src/GameInfos.cpp ${INCLUDE_DIRECTORY}/GameInfos.h
        src/GameSettings.cpp ${INCLUDE_DIRECTORY}/GameSettings.h
        src/thread.cpp ${INCLUDE_DIRECTORY}/thread.h
        ${GUI_INCLUDE_DIRECTORY}/SFMLGUIWidget.h
        src/SFMLGUI/SFMLGUIClickableSprite.cpp ${GUI_INCLUDE_DIRECTORY}/SFMLGUIClickableSprite.h
        src/SFMLGUI/SFMLGUIClickableText.cpp ${GUI_INCLUDE_DIRECTORY}/SFMLGUIClickableText.h
        src/SFMLGUI/SFMLGUIClickableText.cpp ${GUI_INCLUDE_DIRECTORY}/SFMLGUIClickableText.h
        src/SFMLGUI/SFMLGUIDynamicText.cpp ${GUI_INCLUDE_DIRECTORY}/SFMLGUIDynamicText.h
        src/SFMLGUI/SFMLGUIComposition.cpp ${GUI_INCLUDE_DIRECTORY}/SFMLGUIComposition.h
        src/SFMLGUI/SFMLGUISettingsMenu.cpp ${GUI_INCLUDE_DIRECTORY}/SFMLGUISettingsMenu.h
        src/SFMLGUI/SFMLGUIClickableSprite.cpp ${GUI_INCLUDE_DIRECTORY}/SFMLGUIClickableSprite.h
        src/SFMLGUI/SFMLGUIDynamicSprite.cpp ${GUI_INCLUDE_DIRECTORY}/SFMLGUIDynamicSprite.h
        src/SFMLGUI/SFMLGUI.cpp ${GUI_INCLUDE_DIRECTORY}/SFMLGUI.h
        src/SFMLGUI/SFMLGUIStaticText.cpp ${GUI_INCLUDE_DIRECTORY}/SFMLGUIStaticText.h
        src/SFMLGUI/SFMLGUIGameBoard.cpp ${GUI_INCLUDE_DIRECTORY}/SFMLGUIGameBoard.h
        src/SFMLGUI/SFMLGUIMessageLayout.cpp ${GUI_INCLUDE_DIRECTORY}/SFMLGUIMessageLayout.h
        src/SFMLGUI/SFMLGUIStaticSprite.cpp ${GUI_INCLUDE_DIRECTORY}/SFMLGUIStaticSprite.h
        src/SFMLGUI/SFMLGUIBackGround.cpp ${GUI_INCLUDE_DIRECTORY}/SFMLGUIBackGround.h
        src/SFMLGUI/SFMLGUIGameHUI.cpp ${GUI_INCLUDE_DIRECTORY}/SFMLGUIGameHUI.h
        lib/ctpl/ctpl_stl.h
        src/main.cpp)

set(EXECUTABLE_NAME "gomoku_ninuki")
add_executable(${EXECUTABLE_NAME} ${SOURCE_FILES})

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})
find_package(SFML REQUIRED system window graphics network audio)
if(SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
    target_link_libraries(${EXECUTABLE_NAME} ${SFML_LIBRARIES})
endif()
