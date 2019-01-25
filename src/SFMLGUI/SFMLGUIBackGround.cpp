//
// Created by julien vial-detambel on 05/01/2017.
//

#include "SFMLGUIBackGround.h"

SFMLGUIBackGround::SFMLGUIBackGround() {
}

SFMLGUIBackGround::~SFMLGUIBackGround() {
}

void SFMLGUIBackGround::handleEvent(sf::Event &event) {
    for (auto widget: widgets_) {
        widget->handleEvent(event);
    }
}

void SFMLGUIBackGround::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    for (auto widget: widgets_) {
        target.draw(*widget, states);
    }
}