//
// Created by julien vial-detambel on 30/11/2016.
//

#include "SFMLGUIDynamicSprite.h"

SFMLGUIDynamicSprite::SFMLGUIDynamicSprite(const std::function<sf::Sprite()> &dynamicSprite,
                                           const sf::Vector2f &gridPosition) {
    sf::FloatRect widgetBounds;

    dynamicSprite_ = dynamicSprite;
    gridPosition_ = gridPosition;
}

SFMLGUIDynamicSprite::~SFMLGUIDynamicSprite() {
}

void SFMLGUIDynamicSprite::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    states.transform *= getTransform();
    target.draw(sprite_, states);
}

void SFMLGUIDynamicSprite::handleEvent(sf::Event &event) {
    (void)event;
}

void SFMLGUIDynamicSprite::refresh() {
    sf::FloatRect widgetBounds;

    sprite_ = dynamicSprite_();
    widgetBounds = sprite_.getLocalBounds();

    sprite_.setOrigin(widgetBounds.left + widgetBounds.width / 2.f,
                    widgetBounds.top  + widgetBounds.height / 2.f);
}