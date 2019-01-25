//
// Created by julien vial-detambel on 29/12/2016.
//

#pragma once

#include "SFMLGUIWidget.h"

class SFMLGUIStaticText : public SFMLGUIWidget {
public:
    SFMLGUIStaticText(const std::string &text,
                      const sf::Color &color,
                      const std::string &fontPath,
                      const sf::Vector2f &gridPosition);
    ~SFMLGUIStaticText();
    void draw(sf::RenderTarget &target, sf::RenderStates states) const;
    void handleEvent(sf::Event &event);
    void refresh();
private:
    sf::Text text_;
    sf::Font font_;
    sf::Vector2f gridPosition_;
};