//
// Created by julien vial-detambel on 09/11/2016.
//

#pragma once

#include <functional>
#include "SFMLGUIWidget.h"

class SFMLGUIDynamicText : public SFMLGUIWidget {
public:
    SFMLGUIDynamicText(const std::function<sf::String()> &dynamicText,
                       const sf::Color &color,
                       const std::string &fontPath,
                       const sf::Vector2f &gridPosition);
    ~SFMLGUIDynamicText();
    void draw(sf::RenderTarget &target, sf::RenderStates states) const;
    void handleEvent(sf::Event &event);
    void refresh();
private:
    sf::Text text_;
    sf::Font font_;
    std::function<sf::String()> dynamicText_;
    sf::Vector2f gridPosition_;
};