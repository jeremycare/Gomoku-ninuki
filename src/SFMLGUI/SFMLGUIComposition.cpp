//
// Created by julien vial-detambel on 16/11/2016.
//

#include "SFMLGUIDynamicText.h"
#include "SFMLGUIStaticText.h"
#include "SFMLGUIClickableText.h"
#include "SFMLGUIComposition.h"
#include "SFMLGUIClickableSprite.h"
#include "SFMLGUIStaticSprite.h"

SFMLGUIComposition::SFMLGUIComposition() {
}

SFMLGUIComposition::~SFMLGUIComposition() {
}

void SFMLGUIComposition::setWinSize(const sf::Vector2u &winSize) {
    winSize_ = winSize;
}

void SFMLGUIComposition::setCompositionGrid(const sf::Vector2u &compositionGrid) {
    compositionGrid_ = compositionGrid;
    cellXSize_ = winSize_.x / compositionGrid_.x;
    cellYSize_ = winSize_.y / compositionGrid_.y;
}

void SFMLGUIComposition::addStaticText(const sf::String &string,
                                       const sf::Vector2f &gridPosition,
                                       const sf::Color &color,
                                       const std::string &fontPath) {
    SFMLGUIWidget* text = new SFMLGUIStaticText(string,
                                                color,
                                                fontPath,
                                                gridPosition);

    text->setPosition(gridPosition.x * cellXSize_ + (cellXSize_ / 2),
                      gridPosition.y * cellYSize_ + (cellYSize_ / 2));
    widgets_.push_back(text);
}

void SFMLGUIComposition::addClickableText(const sf::String &string,
                                          const std::function<void()> &action,
                                          const sf::Vector2f &gridPosition,
                                          const sf::Color &color,
                                          const std::string &fontPath) {
    SFMLGUIWidget* text = new SFMLGUIClickableText(string,
                                                   action,
                                                   color,
                                                   fontPath,
                                                   gridPosition);

    text->setPosition(gridPosition.x * cellXSize_ + (cellXSize_ / 2),
                        gridPosition.y * cellYSize_ + (cellYSize_ / 2));
    widgets_.push_back(text);
}

void SFMLGUIComposition::addDynamicText(const std::function<sf::String()> &dynamicText,
                                        const sf::Vector2f &gridPosition,
                                        const sf::Color &color,
                                        const std::string &fontPath) {
    SFMLGUIWidget* text = new SFMLGUIDynamicText(dynamicText,
                                                 color,
                                                 fontPath,
                                                 gridPosition);

    text->setPosition(gridPosition.x * cellXSize_ + (cellXSize_ / 2),
                      gridPosition.y * cellYSize_ + (cellYSize_ / 2));
    widgets_.push_back(text);
}

void SFMLGUIComposition::addStaticSprite(const sf::Vector2f &gridPosition,
                                         const std::string &texturePath) {
    SFMLGUIWidget* sprite = new SFMLGUIStaticSprite(sf::Vector2f(cellXSize_, cellYSize_),
                                                    texturePath,
                                                    gridPosition);

    sprite->setPosition(gridPosition.x * cellXSize_ + (cellXSize_ / 2),
                        gridPosition.y * cellYSize_ + (cellYSize_ / 2));
    widgets_.push_back(sprite);
}

void SFMLGUIComposition::addClickableSprite(const std::function<void(SFMLGUIClickableSprite sprite)> &action,
                                            const sf::Vector2f &gridPosition,
                                            const std::string &texturePath) {
    SFMLGUIWidget* sprite = new SFMLGUIClickableSprite(sf::Vector2f(cellXSize_, cellYSize_),
                                                       action,
                                                       texturePath,
                                                       gridPosition);

    sprite->setPosition(gridPosition.x * cellXSize_ + (cellXSize_ / 2),
                        gridPosition.y * cellYSize_ + (cellYSize_ / 2));
    widgets_.push_back(sprite);
}

void SFMLGUIComposition::addClickableSprite(const std::function<void(SFMLGUIClickableSprite sprite)> &action,
                                            const sf::Vector2f &gridPosition) {
    SFMLGUIWidget* sprite = new SFMLGUIClickableSprite(sf::Vector2f(cellXSize_, cellYSize_),
                                                       action,
                                                       gridPosition);

    sprite->setPosition(gridPosition.x * cellXSize_ + (cellXSize_ / 2),
                        gridPosition.y * cellYSize_ + (cellYSize_ / 2));
    widgets_.push_back(sprite);
}