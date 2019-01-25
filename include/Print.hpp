//
// Created by care_j on 2/11/16.
//

#ifndef PRINT_H
# define PRINT_H

#include "Goban.h"
#include "Tree.hpp"
#include "AI.hpp"

class Print {
public:
  Print();
  ~Print();
  Cell askPlay(Goban &goban, int color);
  void printplate(std::string cells, int black, int white);

  void printStats(AI ia, Rave *rave);
  void printRave(Rave *rave);
  void printStats(std::string cell, std::vector<Tree *> nextPlays);

  void printStats(AI *ia);
};

#endif
