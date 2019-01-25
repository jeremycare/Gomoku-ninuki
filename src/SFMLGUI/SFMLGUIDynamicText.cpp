//
// Created by julien vial-detambel on 09/11/2016.
//

#include <iostream>
#include "SFMLGUIDynamicText.h"

SFMLGUIDynamicText::SFMLGUIDynamicText(const std::function<sf::String()> &dynamicText,
                                       const sf::Color &color,
                                       const std::string &fontPath,
                                       const sf::Vector2f &gridPosition) {
    sf::FloatRect widgetBounds;

    if (!font_.loadFromFile(fontPath)) {
        std::cerr << "error: can't open default font file." << std::endl;
        exit(EXIT_FAILURE);
    }
    text_.setColor(color);
    text_.setFont(font_);
    widgetBounds = text_.getLocalBounds();
    text_.setOrigin(widgetBounds.left + widgetBounds.width / 2.f,
                    widgetBounds.top  + widgetBounds.height / 2.f);
    dynamicText_ = dynamicText;
    gridPosition_ = gridPosition;
}

SFMLGUIDynamicText::~SFMLGUIDynamicText() {
}

void SFMLGUIDynamicText::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    states.transform *= getTransform();
    target.draw(text_, states);
}

void SFMLGUIDynamicText::handleEvent(sf::Event &event) {
    (void)event;
}

void SFMLGUIDynamicText::refresh() {
    sf::FloatRect widgetBounds;

    text_.setString(dynamicText_());
    widgetBounds = text_.getLocalBounds();

    text_.setOrigin(widgetBounds.left + widgetBounds.width / 2.f,
                    widgetBounds.top  + widgetBounds.height / 2.f);
}