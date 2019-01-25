//
// Created by julien vial-detambel on 02/01/2017.
//

#include "SFMLGUIMessageLayout.h"

SFMLGUIMessageLayout::SFMLGUIMessageLayout() {
}

SFMLGUIMessageLayout::~SFMLGUIMessageLayout() {
}

void SFMLGUIMessageLayout::handleEvent(sf::Event &event) {
    for (auto widget: widgets_) {
        widget->handleEvent(event);
    }
}

void SFMLGUIMessageLayout::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    for (auto widget: widgets_) {
        target.draw(*widget, states);
    }
}

void SFMLGUIMessageLayout::update(const sf::String &message, const sf::Color &color) {
    for (auto widget: widgets_) {
        delete (widget);
    }
    widgets_.clear();
    addStaticText(message, sf::Vector2f(9, 0), color, "./resources/SFMLGUI/fonts/OpenSans-Bold.ttf");
}