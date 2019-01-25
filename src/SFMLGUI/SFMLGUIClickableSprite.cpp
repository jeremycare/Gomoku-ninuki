//
// Created by julien vial-detambel on 30/11/2016.
//

#include <iostream>
#include "SFMLGUIClickableSprite.h"

SFMLGUIClickableSprite::SFMLGUIClickableSprite(const sf::Vector2f &spriteSize,
                                               const std::function<void(SFMLGUIClickableSprite sprite)> &action,
                                               const sf::Vector2f &gridPosition) {
    sf::FloatRect widgetBounds;

    if (!texture_.create(spriteSize.x, spriteSize.y)) {
        std::cerr << "error: can't create texture" << std::endl;
        exit(EXIT_FAILURE);
    }
    sprite_.setTexture(texture_);
    sprite_.setScale(spriteSize.x / sprite_.getLocalBounds().width,
                     spriteSize.y / sprite_.getLocalBounds().height);
    widgetBounds = sprite_.getLocalBounds();
    sprite_.setOrigin(widgetBounds.left + widgetBounds.width / 2.f,
                      widgetBounds.top  + widgetBounds.height / 2.f);
    action_ = action;
    gridPosition_ = gridPosition;
}

SFMLGUIClickableSprite::SFMLGUIClickableSprite(const sf::Vector2f &spriteSize,
                                               const std::function<void(SFMLGUIClickableSprite sprite)> &action,
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
    action_ = action;
    gridPosition_ = gridPosition;
}

SFMLGUIClickableSprite::~SFMLGUIClickableSprite() {
}

void SFMLGUIClickableSprite::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    states.transform *= getTransform();
    target.draw(sprite_, states);
}

void SFMLGUIClickableSprite::handleEvent(sf::Event& event) {
    if (isClicked_(event)) {
        trigger_();
    }
}

void SFMLGUIClickableSprite::refresh() {
}

const sf::Vector2f SFMLGUIClickableSprite::getGridPosition() const {
    return gridPosition_;
}

bool SFMLGUIClickableSprite::isClicked_(sf::Event &event) {
    if (event.type == sf::Event::MouseButtonPressed) {
        if (event.mouseButton.button == sf::Mouse::Left) {
            return getTransform().transformRect(sprite_.getGlobalBounds())
                    .contains(event.mouseButton.x, event.mouseButton.y);
        }
    }
    return false;
}

void SFMLGUIClickableSprite::trigger_() {
    action_(*this);
}