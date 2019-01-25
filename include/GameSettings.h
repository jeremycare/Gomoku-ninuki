//
// Created by julien vial-detambel on 11/01/2017.
//

#pragma once

class GameSettings {
public:
    GameSettings();
    enum Color {EMPTY ,WHITE, BLACK};
    enum Difficulty {EASY, MEDIUM, HARD};
    void setPlayerColor(Color color);
    void setDifficulty(Difficulty difficulty);
    const Color &getPlayerColor() const;
    const Difficulty &getDifficulty() const;
    int getSimulations();
private:
    Color playerColor_;
    Difficulty difficulty_;
};