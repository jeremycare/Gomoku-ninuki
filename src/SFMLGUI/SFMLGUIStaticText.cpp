//
// Created by julien vial-detambel on 29/12/2016.
//

#include <iostream>
#include "SFMLGUIStaticText.h"

SFMLGUIStaticText::SFMLGUIStaticText(const std::string &string,
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
    gridPosition_ = gridPosition;
}

SFMLGUIStaticText::~SFMLGUIStaticText() {
}

void SFMLGUIStaticText::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    states.transform *= getTransform();
    target.draw(text_, states);
}

void SFMLGUIStaticText::handleEvent(sf::Event &event) {
    (void)event;
}

void SFMLGUIStaticText::refresh() {
}