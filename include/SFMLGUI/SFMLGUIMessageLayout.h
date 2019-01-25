//
// Created by julien vial-detambel on 02/01/2017.
//

#pragma once

#include "SFMLGUIComposition.h"

class SFMLGUIMessageLayout : public SFMLGUIComposition {
public:
    SFMLGUIMessageLayout();
    ~SFMLGUIMessageLayout();
    void handleEvent(sf::Event &event);
    void draw(sf::RenderTarget &target, sf::RenderStates states) const;
    void update(const sf::String &message, const sf::Color &color);
};