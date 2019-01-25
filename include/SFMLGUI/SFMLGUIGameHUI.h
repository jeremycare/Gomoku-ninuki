//
// Created by julien vial-detambel on 07/01/2017.
//

#pragma once

#include "GameInfos.h"
#include "SFMLGUIComposition.h"

class SFMLGUIGameHUI : public SFMLGUIComposition {
public:
    SFMLGUIGameHUI();
    ~SFMLGUIGameHUI();
    void handleEvent(sf::Event &event);
    void draw(sf::RenderTarget &target, sf::RenderStates states) const;
    void update(const GameInfos &gameInfo);
    sf::String turnColorAsString() const;
    sf::String whiteCapturesAsString() const;
    sf::String blackCapturesAsString() const;
private:
    GameInfos gameInfos_;
};