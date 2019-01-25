//
// Created by julien vial-detambel on 08/11/2016.
//

#pragma once

#include <iostream>
#include <functional>
#include "SFMLGUIWidget.h"

class SFMLGUIClickableText : public SFMLGUIWidget {
public:
    SFMLGUIClickableText(const sf::String &string,
                         const std::function<void()> &action,
                         const sf::Color &color,
                         const std::string &fontPath,
                         const sf::Vector2f &gridPosition);
    ~SFMLGUIClickableText();
    void draw(sf::RenderTarget &target, sf::RenderStates states) const;
    void handleEvent(sf::Event &event);
    void refresh();
private:
    bool isClicked_(sf::Event &event);
    void trigger_();
    sf::Text text_;
    sf::Font font_;
    std::function<void()> action_;
    sf::Vector2f gridPosition_;
};
