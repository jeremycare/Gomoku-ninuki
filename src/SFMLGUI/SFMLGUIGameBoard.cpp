//
// Created by julien vial-detambel on 02/01/2017.
//

#include <iostream>
#include "SFMLGUIGameBoard.h"

SFMLGUIGameBoard::SFMLGUIGameBoard() {
    submited_ = false;
}

SFMLGUIGameBoard::~SFMLGUIGameBoard() {
}

void SFMLGUIGameBoard::placeStone(SFMLGUIClickableSprite sprite) {
    move_.x = static_cast<unsigned int>(sprite.getGridPosition().x);
    move_.y = static_cast<unsigned int>(sprite.getGridPosition().y);
    submited_ = true;
}

void SFMLGUIGameBoard::update(std::string string) {
    std::function<void(SFMLGUIClickableSprite sprite)> placeStone = std::bind(&SFMLGUIGameBoard::placeStone,
                                                                              std::ref(*this),
                                                                              std::placeholders::_1);
    for (auto widget: widgets_) {
        delete (widget);
    }
    widgets_.clear();
    for (int j = 0; j < 19; j++) {
        for (int i = 0; i < 19; i++) {
            if (string[j * 19 + i] == 1 + '0') {
                addStaticSprite(sf::Vector2f(i, j), "./resources/SFMLGUI/textures/white_stone.png");
            }
            else if (string[j * 19 + i] == 2 + '0')
                addStaticSprite(sf::Vector2f(i, j), "./resources/SFMLGUI/textures/black_stone.png");
            else
                addClickableSprite(placeStone, sf::Vector2f(i, j));
        }
    }
}

void SFMLGUIGameBoard::handleEvent(sf::Event &event) {
    for (auto widget: widgets_) {
        widget->handleEvent(event);
    }
}

void SFMLGUIGameBoard::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    for (auto widget: widgets_) {
        target.draw(*widget, states);
    }
}

const SFMLGUIGameBoard::Move &SFMLGUIGameBoard::getMove() const {
    return move_;
}

void SFMLGUIGameBoard::setSubmited(bool submited) {
    submited_ = submited;
}

const bool &SFMLGUIGameBoard::getSubmited() const {
    return submited_;
}