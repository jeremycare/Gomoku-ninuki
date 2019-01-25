#include <fstream>
#include "Controller.h"

Controller::Controller()
{
}

Controller::~Controller()
{
}

void Controller::Start()
{
    gameSettings_ = vue_.requestSettings();
    GameLoopIa();
}

void Controller::GameLoopIa()
{
    GameSettings::Color turnColor = GameSettings::WHITE;
    bool endGame = false;
    bool isLegal;
    Cell play;
    int i = 0;

    while (!endGame) {
        gameInfos_.setTurnColor(static_cast<GameInfos::Color>(turnColor));
        gameInfos_.setWhiteCaptures(goban_.white);
        gameInfos_.setBlackCaptures(goban_.black);
        gameInfos_.setSimulations(gameSettings_.getSimulations());
        vue_.update(goban_, gameInfos_);
        isLegal = false;
        if (turnColor == gameSettings_.getPlayerColor()) {
            while (!isLegal) {
                SFMLGUIGameBoard::Move move = vue_.requestMove(turnColor);
                play.x = static_cast<char>(move.x);
                play.y = static_cast<char>(move.y);

                std::cout << (int)play.x << " x|y " <<(int)play.y << "\n";
                isLegal = goban_.IsLegal(play.x, play.y, turnColor);
                if (!isLegal)
                    std::cerr << "bad plays PLAYER";
            }
        }
        else {
            vue_.messageOverlay("Waiting for AI...", sf::Color::White);
            AI ai = AI(goban_, getNextPlayer(turnColor));
            while (!isLegal) {
                play = ai.playTurn(gameInfos_.getSimulations());
                isLegal = goban_.IsLegal(play.x, play.y, turnColor);
                if (!isLegal)
                    std::cerr << "bad plays IA";
            }
        }
        if (goban_.PlayOnGoban(play.x, play.y, (turnColor))) {
            std::cout << "COLOR : " << (int)turnColor << " Win the Game !\n";
            exit(0);
        }
        turnColor = getNextPlayer(turnColor);
        ++i;
    }
}

GameSettings::Color Controller::getNextPlayer(GameSettings::Color color) {
  if (color == GameSettings::WHITE)
    return GameSettings::BLACK;
  if (color == GameSettings::BLACK)
    return GameSettings::WHITE;
  return GameSettings::EMPTY;
}
