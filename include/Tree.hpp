//
// Created by care_j on 2/11/16.
//

#ifndef TREE_H
# define TREE_H

#include <vector>
#include <algorithm>
#include "Goban.h"
#include "Rave.h"

#define EXPLORATION 0.8f

class Tree {

public:
  Tree(char color, int played, int win, char x, char y, float zonning);

  ~Tree();
  Tree &operator=(const Tree &ref);

  Cell getCell() const;
  std::vector<Tree*> nextPlays_;

  Tree *getFinalPlay() const;

  bool expand(int id, Goban &goban, Rave *rave);
  Tree *getBestPlay(Rave *pRave);
  std::vector<Tree *> getBestPlays(Rave *rave, int nb);

  char color_;
  int played_;
  int win_;
  char x_;
  char y_;
  float zonning_;

  bool simulation(Goban &goban, Rave *rave);
  char getNextPlayer(char color) const;


  float beta(int played) const;
  float evaluate(int dadPLayed, Rave *rave) const;
  void updateStats(bool win, Rave *rave);

  void addChild(Goban &goban);
  void addChildWthree(Goban &goban);


};


// <-------------UTILS---------------->

template <typename T>
void moveItemToBack(std::vector<T>& v, size_t itemIndex)
{
  auto it = v.begin() + itemIndex;
  std::rotate(it, it + 1, v.end());
}

#endif
