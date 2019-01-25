//
// Created by julien vial-detambel on 07/01/2017.
//

#include <iostream>
#include "SFMLGUIGameHUI.h"

SFMLGUIGameHUI::SFMLGUIGameHUI() {
    gameInfos_.setTurnColor(GameInfos::WHITE);
}

SFMLGUIGameHUI::~SFMLGUIGameHUI() {
}

void SFMLGUIGameHUI::handleEvent(sf::Event &event) {
    for (auto widget: widgets_) {
        widget->handleEvent(event);
    }
    std::cout << "handleEvent" << std::endl;
}

void SFMLGUIGameHUI::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    for (auto widget: widgets_) {
        target.draw(*widget, states);
    }
}

void SFMLGUIGameHUI::update(const GameInfos &gameInfos) {
    gameInfos_ = gameInfos;
    for (auto widget: widgets_) {
        widget->refresh();
    }
}

sf::String SFMLGUIGameHUI::turnColorAsString() const {
    switch (gameInfos_.getTurnColor()) {
        case GameInfos::WHITE:
            return sf::String("White");
        case GameInfos::BLACK:
            return sf::String("Black");
        default:
            return sf::String("None");
    }
    return sf::String("");
}

sf::String SFMLGUIGameHUI::whiteCapturesAsString() const {
    return sf::String(std::to_string(gameInfos_.getBlackCaptures()));
}

sf::String SFMLGUIGameHUI::blackCapturesAsString() const {
    return sf::String(std::to_string(gameInfos_.getWhiteCaptures()));
}