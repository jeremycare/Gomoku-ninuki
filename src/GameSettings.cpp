//
// Created by julien vial-detambel on 11/01/2017.
//

#include "GameSettings.h"

GameSettings::GameSettings() {
}

void GameSettings::setPlayerColor(GameSettings::Color color) {
    playerColor_ = color;
}

void GameSettings::setDifficulty(GameSettings::Difficulty difficulty) {
    difficulty_ = difficulty;
}

const GameSettings::Color &GameSettings::getPlayerColor() const {
    return playerColor_;
}

const GameSettings::Difficulty &GameSettings::getDifficulty() const {
    return difficulty_;
}

int GameSettings::getSimulations() {
    switch (difficulty_) {
        case EASY:
            return 20000;
        case MEDIUM:
            return 40000;
        case HARD:
            return 60000;
    }
    return 20000;
}
