//
// Created by care_j on 2/11/16.
//

#ifndef AI_H
# define AI_H

#include "Goban.h"
#include "Tree.hpp"

# define NUMBER_SIMULATION 20000

class AI {
public:
  AI(Goban &goban, char color);
  ~AI();
  Cell playTurn(int simulations);

  Goban &current_;
  Goban temporary_;
  Tree monteCarlos;

};

#endif