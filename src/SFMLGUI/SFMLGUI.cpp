//
// Created by julien vial-detambel on 29/12/2016.
//

#include <iostream>
#include "SFMLGUI.h"
#include "SFMLGUIClickableSprite.h"

SFMLGUI::SFMLGUI() : window_(sf::VideoMode(1010, 800, 32), "Gomoku Ninuki") {
    std::function<void()> invertPlayerColor = std::bind(&SFMLGUISettingsMenu::invertPlayerColor, std::ref(settingsMenu_));
    std::function<sf::String()> getPlayerColor = std::bind(&SFMLGUISettingsMenu::playerColorAsString, std::ref(settingsMenu_));
    std::function<void()> nextDifficulty = std::bind(&SFMLGUISettingsMenu::nextDifficulty, std::ref(settingsMenu_));
    std::function<sf::String()> getDifficulty = std::bind(&SFMLGUISettingsMenu::difficultyAsString, std::ref(settingsMenu_));
    std::function<void()> submit = std::bind(&SFMLGUISettingsMenu::submit, std::ref(settingsMenu_));
    std::function<sf::String()> getTurnColor = std::bind(&SFMLGUIGameHUI::turnColorAsString, std::ref(gameHUI_));
    std::function<sf::String()> getWhiteCaptures = std::bind(&SFMLGUIGameHUI::whiteCapturesAsString, std::ref(gameHUI_));
    std::function<sf::String()> getBlackCaptures = std::bind(&SFMLGUIGameHUI::blackCapturesAsString, std::ref(gameHUI_));
    settingsMenu_.setWinSize(window_.getSize());
    settingsMenu_.setCompositionGrid(sf::Vector2u(3, 3));
    settingsMenu_.addStaticText("Player Color:", sf::Vector2f(0, 0), sf::Color::White,
                                "resources/SFMLGUI/fonts/OpenSans-Regular.ttf");
    settingsMenu_.addDynamicText(getPlayerColor, sf::Vector2f(1, 0), sf::Color::White,
                                 "resources/SFMLGUI/fonts/OpenSans-Regular.ttf");
    settingsMenu_.addClickableText("Change", invertPlayerColor, sf::Vector2f(2, 0), sf::Color::White,
                                   "resources/SFMLGUI/fonts/OpenSans-Bold.ttf");
    settingsMenu_.addStaticText("Difficulty:", sf::Vector2f(0, 1), sf::Color::White,
                                "resources/SFMLGUI/fonts/OpenSans-Regular.ttf");
    settingsMenu_.addDynamicText(getDifficulty, sf::Vector2f(1, 1), sf::Color::White,
                                 "resources/SFMLGUI/fonts/OpenSans-Regular.ttf");
    settingsMenu_.addClickableText("Change", nextDifficulty, sf::Vector2f(2, 1), sf::Color::White,
                                   "resources/SFMLGUI/fonts/OpenSans-Bold.ttf");
    settingsMenu_.addClickableText("Start", submit, sf::Vector2f(1, 2), sf::Color::White,
                                   "resources/SFMLGUI/fonts/OpenSans-Bold.ttf");
    messageLayout_.setWinSize(window_.getSize());
    messageLayout_.setCompositionGrid(sf::Vector2u(24, 1));
    messageLayout_.addStaticText("Initializing...", sf::Vector2f(13, 0), sf::Color::White,
                                 "resources/SFMLGUI/fonts/OpenSans-Bold.ttf");
    gameBoard_.setWinSize(window_.getSize());
    gameBoard_.setCompositionGrid(sf::Vector2u(24, 19));
    gameBoardBackGround_.setWinSize(window_.getSize());
    gameBoardBackGround_.setCompositionGrid(sf::Vector2u(1, 1));
    gameBoardBackGround_.addStaticSprite(sf::Vector2f(0, 0),
                                         "resources/SFMLGUI/textures/background.png");
    gameHUI_.setWinSize(window_.getSize());
    gameHUI_.setCompositionGrid(sf::Vector2u(5, 6));
    gameHUI_.addStaticText("Current\nTurn:", sf::Vector2f(4, 0), sf::Color::White,
                           "resources/SFMLGUI/fonts/OpenSans-Regular.ttf");
    gameHUI_.addDynamicText(getTurnColor, sf::Vector2f(4, 1), sf::Color::White,
                            "resources/SFMLGUI/fonts/OpenSans-Regular.ttf");
    gameHUI_.addStaticText("White\nCaptures:", sf::Vector2f(4, 2), sf::Color::White,
                           "resources/SFMLGUI/fonts/OpenSans-Regular.ttf");
    gameHUI_.addDynamicText(getWhiteCaptures, sf::Vector2f(4, 3), sf::Color::White,
                            "resources/SFMLGUI/fonts/OpenSans-Regular.ttf");
    gameHUI_.addStaticText("Black\nCaptures:", sf::Vector2f(4, 4), sf::Color::White,
                           "resources/SFMLGUI/fonts/OpenSans-Regular.ttf");
    gameHUI_.addDynamicText(getBlackCaptures, sf::Vector2f(4, 5), sf::Color::White,
                            "resources/SFMLGUI/fonts/OpenSans-Regular.ttf");
};

GameSettings SFMLGUI::requestSettings() {
    while (window_.isOpen()) {
        window_.clear(sf::Color::Black);
        while (window_.pollEvent(event_)) {
            if (event_.type == sf::Event::Closed) {
                window_.close();
            }
            settingsMenu_.handleEvent(event_);
        }
        window_.draw(settingsMenu_);
        window_.display();
        if (settingsMenu_.getSubmited()) {
            break;
        }
    }
    window_.clear(sf::Color::Black);
    window_.display();
    return settingsMenu_.getSettings();
}

void SFMLGUI::update(const Goban &goban, const GameInfos &gameInfos) {
    gameBoard_.update(goban.cell);
    gameHUI_.update(gameInfos);
    window_.clear(sf::Color::Black);
    window_.draw(gameBoardBackGround_);
    window_.draw(gameBoard_);
    window_.draw(gameHUI_);
    window_.display();
}

void SFMLGUI::messageOverlay(const sf::String &message, const sf::Color &color) {
    messageLayout_.update(message, color);
    window_.clear(sf::Color::Black);
    window_.draw(gameBoardBackGround_);
    window_.draw(gameBoard_);
    window_.draw(gameHUI_);
    window_.draw(messageLayout_);
    window_.display();
}

SFMLGUIGameBoard::Move SFMLGUI::requestMove(const int &color) {
    (void)color;
    //TODO: Refactor Request Move with additional Game Information displayed on GUI
    //updateGameBoard(goban);
    while (window_.isOpen()) {
        window_.clear(sf::Color::Black);
        while (window_.pollEvent(event_)) {
            if (event_.type == sf::Event::Closed) {
                window_.close();
            }
            gameBoard_.handleEvent(event_);
        }
        window_.draw(gameBoardBackGround_);
        window_.draw(gameBoard_);
        window_.draw(gameHUI_);
        window_.display();
        if (gameBoard_.getSubmited()) {
            break;
        }
    }
    gameBoard_.setSubmited(false);
    return gameBoard_.getMove();
}