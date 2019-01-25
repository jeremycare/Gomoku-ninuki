//
// Created by julien vial-detambel on 09/11/2016.
//

#pragma once

#include <functional>
#include <vector>
#include "SFMLGUIWidget.h"
#include "SFMLGUIClickableSprite.h"

class SFMLGUIComposition : public sf::Drawable {
public:
    SFMLGUIComposition();
    ~SFMLGUIComposition();
    virtual void handleEvent(sf::Event &event) = 0;
    void addStaticText(const sf::String &string,
                       const sf::Vector2f &gridPosition,
                       const sf::Color &color,
                       const std::string &fontPath);
    void addClickableText(const sf::String &string,
                          const std::function<void()> &action,
                          const sf::Vector2f &gridPosition,
                          const sf::Color &color,
                          const std::string &fontPath);
    void addDynamicText(const std::function<sf::String()> &dynamicText,
                        const sf::Vector2f &gridPosition,
                        const sf::Color &color,
                        const std::string &fontPath);
    void addStaticSprite(const sf::Vector2f &gridPosition,
                         const std::string &texturePath);
    void addClickableSprite(const std::function<void(SFMLGUIClickableSprite sprite)> &action,
                            const sf::Vector2f &gridPosition,
                            const std::string &texturePath);
    void addClickableSprite(const std::function<void(SFMLGUIClickableSprite sprite)> &action,
                            const sf::Vector2f &gridPosition);
    void setWinSize(const sf::Vector2u &winSize);
    void setCompositionGrid(const sf::Vector2u &compositionGrid);
protected:
    sf::Vector2u winSize_;
    sf::Vector2u compositionGrid_;
    std::vector<SFMLGUIWidget*> widgets_;
    unsigned int cellXSize_;
    unsigned int cellYSize_;
};