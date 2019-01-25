#ifndef CONTROLLER_H
# define CONTROLLER_H

#include <string>
#include <iostream>
#include "Goban.h"
#include "AI.hpp"
#include "SFMLGUI.h"
#include "GameInfos.h"

class Controller
{
public:
	Controller();
	~Controller();
	void Start();
private:
	Goban goban_;
	SFMLGUI vue_;
	GameSettings gameSettings_;
	GameSettings::Color getNextPlayer(GameSettings::Color);
	GameInfos gameInfos_;
	void GameLoopIa();
};

#endif
