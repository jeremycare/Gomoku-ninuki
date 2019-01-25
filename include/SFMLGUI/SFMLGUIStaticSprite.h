//
// Created by julien vial-detambel on 02/01/2017.
//

#pragma once

#include <SFML/System.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include "SFMLGUIWidget.h"

class SFMLGUIStaticSprite : public SFMLGUIWidget {
public:
    SFMLGUIStaticSprite(const sf::Vector2f &spriteSize,
                        const std::string &texturePath,
                        const sf::Vector2f &gridPosition);
    ~SFMLGUIStaticSprite();
    void draw(sf::RenderTarget &target, sf::RenderStates states) const;
    void handleEvent(sf::Event &event);
    void refresh();
private:
    sf::Texture texture_;
    sf::Sprite sprite_;
    sf::Vector2f gridPosition_;
};
