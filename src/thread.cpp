//
// Created by care_j on 08/01/17.
//

#include "Tree.hpp"
#include "thread.h"

void LaunchThread(int id, Tree* tree, Rave *rave, Goban goban) {
  rave->SortVects(goban);
  tree->expand(id, goban, rave);
}