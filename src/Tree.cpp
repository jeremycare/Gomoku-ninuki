//
// Created by care_j on 2/11/16.
//

#include <math.h>
#include <iostream>
#include "Tree.hpp"
#include "Rave.h"

Tree & Tree::operator=(const Tree &ref) {
  x_ = ref.x_;
  y_ = ref.y_;
  color_ = ref.color_;
  played_ = ref.played_;
  win_ = ref.win_;
  nextPlays_ = ref.nextPlays_;
  zonning_ = ref.zonning_;
  return *this;
}

Tree::Tree(char color, int played, int win, char x, char y, float zonning)
        : color_(color)
        , played_(played)
        , win_(win)
        , x_(x)
        , y_(y)
        , zonning_(zonning)
{
}


Tree::~Tree() {
  for (auto it : nextPlays_) {
    delete it;
  }
}

/**
 * Function for add All possible plays depending of the goban
 * @param goban for access to zonning.
 */

void Tree::addChild(Goban &goban) {
  char color = getNextPlayer(color_);
  std::vector<Cell>& legalPlays = goban.GetLegalCells(color);

  for (auto& it : legalPlays)
  {
    if (goban.IsInZones(it.x, it.y))
      nextPlays_.push_back(new Tree(color, 3, 1, it.x, it.y, 2.f));
    //else
    //  nextPlays_.push_back(new Tree(color, 3, 1, it.x, it.y, 0.01f));
  }
}

/**
 * Function for adding with soft Rules
 * @param goban for access to zonning
 */

void Tree::addChildWthree(Goban &goban) {
  char color = getNextPlayer(color_);
  std::vector<Cell>& legalPlays = goban.GetLegalCellsAI();

  for (auto& it : legalPlays)
  {
    if (goban.IsInZones(it.x, it.y))
      nextPlays_.push_back(new Tree(color, 3, 1, it.x, it.y, 2.f));
    //else
     // nextPlays_.push_back(new Tree(color, 3, 1, it.x, it.y, 0.01f));
  }
}

/**
 * update score
 * @param win true for win / false for loose
 * @param rave will be update at the same time
 */

void Tree::updateStats(bool win, Rave *rave) {
  if (x_ == -1)
    return;
  if (win)
    win_ += 1;
  ++played_;
  if (x_ != -1)
    rave->update(x_, y_, color_, win);
}

/**
 * Modified UBT for RAVE
 * @param how many time played in RAVE
 * @return result of the operation BETA
 */

float Tree::beta(int ravePlayed) const {
  float ni = (float) played_;
  float Rni = (float) ravePlayed;

  return (Rni / (ni + Rni + (4.f * 40.f * Rni * ni)));
}

/**
 * Function for evaluate a tree.
 * @param dadPLayed for the formula
 * @param rave for datas
 * @return the score
 */

float Tree::evaluate(int dadPLayed, Rave *rave) const {
  float wi = (float) win_;
  float ni = (float) played_;
  float Rwi = (float) rave->getWin(x_, y_, color_);
  float Rni = (float) rave->getPlayed(x_, y_, color_);
  float retb = beta(Rni);
  float t = (float) dadPLayed;
  float c = 10.f;

  return (zonning_ * (((1.f - retb) * (wi / ni) + (retb * (Rwi) / (Rni)) + (c * (float)sqrt(sqrt(t) / ni)))));
}

/**
 * get next player id, depend of the number of player
 * @param color
 * @return next played id
 */

char Tree::getNextPlayer(char color) const {
  return (char) (color == 1 ? 2 : 1);
}


/**
 * Simulation of the entire game
 * @param goban
 * @param rave
 * @return
 */

bool Tree::simulation(Goban &goban, Rave *rave) {
  char color = getNextPlayer(color_);
  Cell cell;

  while (42) {
    cell = rave->getNextPlay(color);
    while (!goban.IsLegalSimulation(cell.x, cell.y)) {
      cell = rave->getNextPlay(color);
    }
    rave->setPlayed(color);


    if (goban.PlayOnGobanSimulation(cell.x, cell.y, color)) {
      rave->ActualiseWins(color);
      if (color == color_) {
        updateStats(true, rave);
        return true;
      }
      else {
        updateStats(false, rave);
        return false;
      }
    } else
      color = getNextPlayer(color);
  }
}

Tree *Tree::getFinalPlay() const {
  float highscore = -1.f;
  float save;
  Tree *bestplay = nextPlays_[0];

  for (auto& it : nextPlays_) {
    if ((save = (((float)(it->win_)) / (float)(it->played_)) * zonning_) > highscore) {
      bestplay = it;
      highscore = save;
    }
  }
  return  bestplay;
}

Tree *Tree::getBestPlay(Rave *rave) {
  float highscore = -1.f;
  float save;
  Tree *bestplay = nextPlays_[0];

  for (auto &it : nextPlays_) {
      if ((save = it->evaluate(played_, rave)) > highscore) {
        bestplay = it;
        highscore = save;
      }
  }
  if (bestplay == NULL)
    return (nextPlays_[0]);
  return  bestplay;
}

std::vector<Tree *> Tree::getBestPlays(Rave *rave, int nb) {
  std::vector<Tree *> bestTrees;
  std::vector<float> scores (nb, 0);
  int bestNb = 0;
  for (auto &it : nextPlays_) {
    float score = it->evaluate(played_, rave);
    Tree *tmp = it;
      if (bestNb < nb) {
        bestTrees.push_back(tmp);
        scores[bestNb] = score;
        bestNb++;
      }
      else {
          for (int i = 0; i < nb; ++i) {
          if (scores[i] < score) {
            float tmpScore = scores[i];
            Tree *tmpTree = bestTrees[i];

            scores[i] = score;
            bestTrees[i] = tmp;
            tmp = tmpTree;
            score = tmpScore;
          }
        }
      }
  }
  return bestTrees;
}

bool Tree::expand(int id, Goban &goban, Rave *rave) {
  if (x_ != -1 && goban.PlayOnGobanAI(x_, y_, color_)) {
    rave->ActualiseWins(color_);
    updateStats(true, rave);
    return (true);
  }
  else {
    rave->t_ = played_ * 100;
  }
  if (!nextPlays_.empty()) {
    Tree *bestplay;
    bestplay = getBestPlay(rave);

    bool ret = !bestplay->expand(id, goban, rave);

    updateStats(ret, rave);
    return ret;
  }
  else
  {
    if (x_ != -1) {
      addChildWthree(goban);
    } else {
      addChild(goban);
    }
    Tree *bestplay = getBestPlay(rave);

    if (goban.PlayOnGobanAI(bestplay->x_, bestplay->y_, bestplay->color_)) {
      updateStats(false, rave);
      bestplay->updateStats(true, rave);
      return (false);
    }
    bool ret = !bestplay->simulation(goban, rave);
    updateStats(ret, rave);
    return (ret);
  }
}

Cell Tree::getCell() const {
  return {x_, y_};
}