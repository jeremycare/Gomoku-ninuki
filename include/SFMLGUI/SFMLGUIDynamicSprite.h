//
// Created by julien vial-detambel on 30/11/2016.
//

#pragma once

#include <functional>
#include "SFMLGUIWidget.h"

class SFMLGUIDynamicSprite : public SFMLGUIWidget {
public:
    SFMLGUIDynamicSprite(const std::function<sf::Sprite()> &dynamicSprite,
                         const sf::Vector2f &gridPosition);
    ~SFMLGUIDynamicSprite();
    void draw(sf::RenderTarget &target, sf::RenderStates states) const;
    void handleEvent(sf::Event &event);
    void refresh();
private:
    sf::Texture texture_;
    sf::Sprite sprite_;
    std::function<sf::Sprite()> dynamicSprite_;
    sf::Vector2f gridPosition_;
};