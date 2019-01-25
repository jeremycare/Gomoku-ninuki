//
// Created by julien vial-detambel on 11/01/2017.
//

#include "GameInfos.h"

GameInfos::GameInfos() {
    turnColor_ = EMPTY;
    whiteCaptures_ = 0;
    blackCaptures_ = 0;
    simulations_ = 0;
}

void GameInfos::setTurnColor(Color color) {
    turnColor_ = color;
}

void GameInfos::setWhiteCaptures(int whiteCaptures) {
    whiteCaptures_ = whiteCaptures;
}

void GameInfos::setBlackCaptures(int blackCaptures) {
    blackCaptures_ = blackCaptures;
}

void GameInfos::setSimulations(int simulations) {
    simulations_ = simulations;
}

const GameInfos::Color &GameInfos::getTurnColor() const {
    return turnColor_;
}

const int &GameInfos::getWhiteCaptures() const {
    return whiteCaptures_;
}

const int &GameInfos::getBlackCaptures() const {
    return blackCaptures_;
}

const int &GameInfos::getSimulations() const {
    return simulations_;
}
