//
// Created by julien vial-detambel on 08/11/2016.
//

#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

class SFMLGUIWidget : public sf::Transformable, public sf::Drawable {
public:
    virtual void handleEvent(sf::Event &event) = 0;
    virtual void refresh() = 0;
};
