//
// Created by julien vial-detambel on 05/01/2017.
//

#pragma once

#include "SFMLGUIComposition.h"

class SFMLGUIBackGround : public SFMLGUIComposition {
public:
    SFMLGUIBackGround();
    ~SFMLGUIBackGround();
    void handleEvent(sf::Event &event);
    void draw(sf::RenderTarget &target, sf::RenderStates states) const;
};