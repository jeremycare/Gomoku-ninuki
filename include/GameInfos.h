//
// Created by julien vial-detambel on 11/01/2017.
//

#pragma once

class GameInfos {
public:
    GameInfos();
    enum Color {EMPTY, WHITE, BLACK};
    void setTurnColor(Color color);
    void setWhiteCaptures(int whiteCaptures);
    void setBlackCaptures(int blackCaptures);
    void setSimulations(int simulations);
    const Color &getTurnColor() const;
    const int &getWhiteCaptures() const;
    const int &getBlackCaptures() const;
    const int &getSimulations() const;
private:
    Color turnColor_;
    int whiteCaptures_;
    int blackCaptures_;
    int simulations_;
};