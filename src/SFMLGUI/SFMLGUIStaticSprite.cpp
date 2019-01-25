//
// Created by julien vial-detambel on 02/01/2017.
//

#include <iostream>
#include "SFMLGUIStaticSprite.h"

SFMLGUIStaticSprite::SFMLGUIStaticSprite(const sf::Vector2f &spriteSize,
                                         const std::string &texturePath,
                                         const sf::Vector2f &gridPosition) {
    sf::FloatRect widgetBounds;

    if (!texture_.loadFromFile(texturePath)) {
        std::cerr << "error: can't open texture file." << std::endl;
        exit(EXIT_FAILURE);
    }
    sprite_.setTexture(texture_);
    sprite_.setScale(spriteSize.x / sprite_.getLocalBounds().width,
                     spriteSize.y / sprite_.getLocalBounds().height);
    widgetBounds = sprite_.getLocalBounds();
    sprite_.setOrigin(widgetBounds.left + widgetBounds.width / 2.f,
                      widgetBounds.top  + widgetBounds.height / 2.f);
    gridPosition_ = gridPosition;
}

SFMLGUIStaticSprite::~SFMLGUIStaticSprite() {
}

void SFMLGUIStaticSprite::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    states.transform *= getTransform();
    target.draw(sprite_, states);
}

void SFMLGUIStaticSprite::handleEvent(sf::Event &event) {
    (void)event;
}

void SFMLGUIStaticSprite::refresh() {
}