//
// Created by care_j on 01/12/16.
//

#ifndef GOMOKU_NINUKI_RAVE_H
# define GOMOKU_NINUKI_RAVE_H

#include <tgmath.h>
#include "Goban.h"
#include "Rave.h"
#include "Tree.hpp"

class Rave {

public:
  struct Play {
    Play &operator=(const Play &ref);
    int x;
    int y;
    int win;
    int played;
    bool modified;
    float score;
  };

  Rave();
  Rave & operator=(const Rave & ref);
  ~Rave();

  float t_;
  Play *last_;

  std::vector<Play> Ocolor1_;
  std::vector<Play> Ocolor2_;
  std::vector<Play *> color1_;
  std::vector<Play *> color2_;
  std::vector<Play *> played1_;
  std::vector<Play *> played2_;
  std::vector<int> it1;
  std::vector<int> it2;

  void update(int x, int y, int color, bool win);

  int getWin(int x, int y, int color);
  int getPlayed(int x, int y, int color);
  int getIdx(int x, int y);

  Cell getNextPlay(int color);

  void setPlayed(int color);
  void ActualiseWins(int color);
  void ActualiseScore(Goban &goban);

  void SortVects(Goban &goban);

  void Merge(std::vector<Rave> &others, Goban &goban);
};

#endif //GOMOKU_NINUKI_RAVE_H
