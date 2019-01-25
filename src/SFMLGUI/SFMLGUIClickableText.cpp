//
// Created by julien vial-detambel on 08/11/2016.
//

#include <iostream>
#include <SFML/System/String.hpp>
#include <SFML/Graphics.hpp>
#include "SFMLGUIClickableText.h"

SFMLGUIClickableText::SFMLGUIClickableText(const sf::String &string,
                                           const std::function<void()> &action,
                                           const sf::Color &color,
                                           const std::string &fontPath,
                                           const sf::Vector2f &gridPosition) {
    sf::FloatRect widgetBounds;

    if (!font_.loadFromFile(fontPath)) {
        std::cerr << "error: can't open default font file." << std::endl;
        exit(EXIT_FAILURE);
    }
    text_.setString(string);
    text_.setColor(color);
    text_.setFont(font_);
    widgetBounds = text_.getLocalBounds();
    text_.setOrigin(widgetBounds.left + widgetBounds.width / 2.f,
                    widgetBounds.top  + widgetBounds.height / 2.f);
    action_ = action;
    gridPosition_ = gridPosition;
}

SFMLGUIClickableText::~SFMLGUIClickableText() {
}

void SFMLGUIClickableText::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    states.transform *= getTransform();
    target.draw(text_, states);
}

void SFMLGUIClickableText::handleEvent(sf::Event &event) {
    if (isClicked_(event)) {
        trigger_();
    }
}

void SFMLGUIClickableText::refresh() {
}

bool SFMLGUIClickableText::isClicked_(sf::Event &event) {
    if (event.type == sf::Event::MouseButtonPressed) {
        if (event.mouseButton.button == sf::Mouse::Left) {
            return getTransform().transformRect(text_.getGlobalBounds())
                    .contains(event.mouseButton.x, event.mouseButton.y);
        }
    }
    return false;
}

void SFMLGUIClickableText::trigger_() {
    action_();
}