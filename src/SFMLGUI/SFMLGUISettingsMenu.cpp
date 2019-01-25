//
// Created by julien vial-detambel on 18/11/2016.
//

#include <iostream>
#include "SFMLGUISettingsMenu.h"

SFMLGUISettingsMenu::SFMLGUISettingsMenu() {
    gameSettings_.setPlayerColor(GameSettings::WHITE);
    gameSettings_.setDifficulty(GameSettings::EASY);
    submited_ = false;
}

SFMLGUISettingsMenu::~SFMLGUISettingsMenu() {
}

void SFMLGUISettingsMenu::handleEvent(sf::Event &event) {
    for (auto widget: widgets_) {
        widget->refresh();
        widget->handleEvent(event);
    }
}

void SFMLGUISettingsMenu::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    for (auto widget: widgets_) {
        target.draw(*widget, states);
    }
}

void SFMLGUISettingsMenu::invertPlayerColor() {
    switch (gameSettings_.getPlayerColor()) {
        case GameSettings::WHITE:
            gameSettings_.setPlayerColor(GameSettings::BLACK);
            break;
        case GameSettings::BLACK:
            gameSettings_.setPlayerColor(GameSettings::WHITE);
            break;
        default:
            gameSettings_.setPlayerColor(GameSettings::EMPTY);
            break;
    }
}

void SFMLGUISettingsMenu::nextDifficulty() {
    switch (gameSettings_.getDifficulty()) {
        case GameSettings::EASY:
            gameSettings_.setDifficulty(GameSettings::MEDIUM);
            break;
        case GameSettings::MEDIUM:
            gameSettings_.setDifficulty(GameSettings::HARD);
            break;
        case GameSettings::HARD:
            gameSettings_.setDifficulty(GameSettings::EASY);
            break;
    }
}

void SFMLGUISettingsMenu::submit() {
    submited_ = true;
}

sf::String SFMLGUISettingsMenu::playerColorAsString() const {
    switch (gameSettings_.getPlayerColor()) {
        case GameSettings::WHITE:
            return sf::String("White");
        case GameSettings::BLACK:
            return sf::String("Black");
        case GameSettings::EMPTY:
            return sf::String("None");
    }
    return sf::String("");
}

sf::String SFMLGUISettingsMenu::difficultyAsString() const {
    switch (gameSettings_.getDifficulty()) {
        case GameSettings::EASY:
            return sf::String("Easy");
        case GameSettings::MEDIUM:
            return sf::String("Medium");
        case GameSettings::HARD:
            return sf::String("Hard");
    }
    return sf::String("");
}

const GameSettings &SFMLGUISettingsMenu::getSettings() const {
    return gameSettings_;
}

const bool &SFMLGUISettingsMenu::getSubmited() const {
    return submited_;
}