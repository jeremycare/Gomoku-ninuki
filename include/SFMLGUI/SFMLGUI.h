//
// Created by julien vial-detambel on 29/12/2016.
//

#pragma once

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include "SFMLGUISettingsMenu.h"
#include "SFMLGUIGameBoard.h"
#include "SFMLGUIMessageLayout.h"
#include "SFMLGUIBackGround.h"
#include "SFMLGUIGameHUI.h"
#include "Goban.h"
#include "GameSettings.h"

class SFMLGUI {
public:
    SFMLGUI();
    GameSettings requestSettings();
    void update(const Goban &goban, const GameInfos &gameInfo);
    void messageOverlay(const sf::String &message, const sf::Color &color);
    SFMLGUIGameBoard::Move requestMove(const int &color);
private:
    sf::RenderWindow window_;
    sf::Event event_;
    SFMLGUISettingsMenu settingsMenu_;
    SFMLGUIGameBoard gameBoard_;
    SFMLGUIBackGround gameBoardBackGround_;
    SFMLGUIMessageLayout messageLayout_;
    SFMLGUIGameHUI gameHUI_;
};
