//
// Created by julien vial-detambel on 18/11/2016.
//

#pragma once

#include "SFMLGUIComposition.h"
#include "GameSettings.h"

class SFMLGUISettingsMenu : public SFMLGUIComposition {
public:
    SFMLGUISettingsMenu();
    ~SFMLGUISettingsMenu();
    void handleEvent(sf::Event &event);
    void draw(sf::RenderTarget &target, sf::RenderStates states) const;
    void invertPlayerColor();
    void nextDifficulty();
    void submit();
    //Design leading to Clumsy getters returning non const variables
    sf::String playerColorAsString() const;
    sf::String difficultyAsString() const;
    const GameSettings &getSettings() const;
    const bool &getSubmited() const;
private:
    GameSettings gameSettings_;
    bool submited_;
};