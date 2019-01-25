//
// Created by julien vial-detambel on 30/11/2016.
//

#pragma once

#include <functional>
#include "SFMLGUIWidget.h"

class SFMLGUIClickableSprite : public SFMLGUIWidget {
public:
    SFMLGUIClickableSprite(const sf::Vector2f &spriteSize,
                           const std::function<void(SFMLGUIClickableSprite sprite)> &action,
                           const sf::Vector2f &gridPosition);
    SFMLGUIClickableSprite(const sf::Vector2f &spriteSize,
                           const std::function<void(SFMLGUIClickableSprite sprite)> &action,
                           const std::string &texturePath,
                           const sf::Vector2f &gridPosition);
    ~SFMLGUIClickableSprite();
    void draw(sf::RenderTarget &target, sf::RenderStates states) const;
    void handleEvent(sf::Event &event);
    void refresh();
    const sf::Vector2f getGridPosition() const;
private:
    bool isClicked_(sf::Event &event);
    void trigger_();
    sf::Texture texture_;
    sf::Sprite sprite_;
    std::function<void(SFMLGUIClickableSprite sprite)> action_;
    sf::Vector2f gridPosition_;
};