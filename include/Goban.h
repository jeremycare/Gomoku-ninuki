//
// Created by care_j on 25/10/16.
//

#ifndef GOMOKU_NINUKI_GOBAN_H
# define GOMOKU_NINUKI_GOBAN_H


/*
 * Le parsing du goban dans l'odre:
 * Position du coup en x
 * Position du coup en y
 * Les pierres capturées par le joueur WHITE
 * Les pierres capturées par le joueur BLACK
 * Partie gagnée (1 == win, 0 == en cours)
 * La couleur du player actuel (1 == WHITE, 2 == BLACK) comme l'enum
 */

#include <string>
#include <vector>
#include <map>

#define SIZEZONE 4


struct Cell {
	char x;
	char y;
};

bool operator==(const Cell & ref, const Cell &ref2);


class Goban {
public:
	struct Neighbor {
		char x;
		char y;
		char value;
	};

  Goban();
  Goban(const Goban & ref);
  Goban & operator=(const Goban & ref);
  ~Goban();

	bool IsInZones(char x, char y);
	bool IsLegal(char coordX, char coordY, char color);
	bool IsLegalSimulation(char coordX, char coordY);
  bool IsWin(char coordX, char coordY, char color);
  void CheckPrisoner(char cX, char cY, char color);

  bool PlayOnGobanAI(char x, char y, char color);
  bool IsWinAI(char x, char y, char color);
  bool CheckAlignmentAI(char cX, char cY, char color);
  bool IsAlignAI(std::vector<Neighbor> &n);

	std::vector<Cell> & GetLegalCells(char color);
  bool IsLegalWthree(char cX, char cY);
  std::vector<Cell> &GetLegalCellsAI();

  void SetGoban(char x, char y, char value);
	bool PlayOnGoban(char x, char y, char value);
	bool PlayOnGobanSimulation(char x, char y, char color);

  const int width_ = 19;
  const int height_ = 19;

  int white;
  int black;
  bool win;
  std::string cell;
  bool breakable;

	int vx;
	int vy;

private:


  enum Status {
    EMPTY = 0,
    WHITE = 1,
    BLACK = 2,
    OUT = 3,
  };

  enum Position {
    PREV_3,
    PREV_2,
    PREV_1,
    POS,
    NEXT_1,
    NEXT_2,
    NEXT_3,
    NEXT_4,
  };

  void SetNeighbor(std::vector<Neighbor> &neighbor, char cX, char cY, char vX, char vY) const;

  bool CheckAlignment(char cX, char cY, char playerColor);
  bool IsAlign(std::vector<Neighbor> &n, char playerColor);
  bool IsBreakable(const std::vector<Neighbor> &n, int beginIndex, int endIndex, char playerColor);
  bool CheckDoubleThree(int x, int y, int vX, int vY);
  bool CheckThreeAlign(int x, int y, int vX, int vY);

  char GetIntersection(char x, char y) const;
  int GetEnemyColor(char color) const;

  int doubleThree_;
  int totalStone_;
  std::vector<Cell> whitePrisoner_;
  std::vector<Cell> blackPrisoner_;
  std::vector<Cell> legals_;
  std::vector<Cell> breakables;
	std::vector<bool> zones_;
  bool IsInBreakables(int x, int y);

	void AddZone(char x, char y);

};


#endif //GOMOKU_NINUKI_GOBAN_H
