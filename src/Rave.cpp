//
// Created by care_j on 01/12/16.
//

#include <iostream>
#include <numeric>
#include "Goban.h"
#include "Print.hpp"

struct EntityComp {
  EntityComp() {}
  bool operator()(const Rave::Play *t1, const Rave::Play *t2) const {
    return t1->score > t2->score;
  }
};

Rave::Rave() {
  Ocolor1_ = std::vector<Play> (361);
  Ocolor2_ = std::vector<Play> (361);
  it1 = std::vector<int> (361);
  it2 = std::vector<int> (361);
  std::iota(it1.begin(), it1.end(), 0);
  std::iota(it2.begin(), it2.end(), 0);
  t_ = 1;
  for (int y = 0; y < 19; y++) {
    for (int x = 0; x < 19; x++) {
      int idx = y*19+x;
      Ocolor1_[idx] = {x, y, 1, 2, true, 0.5f};
      Ocolor2_[idx] = {x, y, 1, 2, true, 0.5f};
    }
  }
  for (int i = 0; i < 361; ++i) {
    color1_.push_back(&Ocolor1_[i]);
    color2_.push_back(&Ocolor2_[i]);
  }
  std::random_shuffle(color1_.begin(), color1_.end());
  std::random_shuffle(color2_.begin(), color2_.end());
}

Rave::~Rave() {
}

Rave &Rave::operator=(const Rave &ref) {
  Ocolor1_ = ref.Ocolor1_;
  Ocolor2_ = ref.Ocolor2_;
  t_ = ref.t_;
  color1_.clear();
  color2_.clear();
  for (int i = 0; i < 361; ++i) {
    color1_.push_back(&Ocolor1_[i]);
    color2_.push_back(&Ocolor2_[i]);
  }
  it1 = ref.it1;
  it2 = ref.it2;
  last_ = color1_[0];
  return *this;
}

Cell Rave::getNextPlay(int color) {
  Cell cell;

  std::vector<int> v = {0, 0, 0, 0, 0, 0, 1, 1, 2, 2};
  int i = v[rand() % 10];
  if (color == 1) {
    cell.x = (char) color1_[it1[i]]->x;
    cell.y = (char) color1_[it1[i]]->y;
    last_ = color1_[it1[i]];
    moveItemToBack(it1, i);
    return (cell);
  }
  else {
    cell.x = (char) color2_[it2[i]]->x;
    cell.y = (char) color2_[it2[i]]->y;
    last_ = color2_[it2[i]];
    moveItemToBack(it2, i);
    return (cell);
  }
}

void Rave::setPlayed(int color) {
  if (color == 1) {
    played1_.push_back(last_);
  } else {
    played2_.push_back(last_);
  }
}

void Rave::ActualiseWins(int color) {

  if (color == 1) {
    for (auto &it : played1_) {
      it->played++;
      it->win++;
    }
    for (auto &it : played2_) {
      it->played++;
    }
  }
  else {
    for (auto &it : played1_) {
      it->played++;
    }
    for (auto &it : played2_) {
      it->played++;
      it->win++;
    }
  }
  played2_.clear();
  played1_.clear();
}

void Rave::SortVects(Goban& goban) {
  t_+= 1;
  ActualiseScore(goban);
  std::sort(color1_.begin(), color1_.end(), EntityComp());
  std::sort(color2_.begin(), color2_.end(), EntityComp());
  std::iota(it1.begin(), it1.end(), 0);
  std::iota(it2.begin(), it2.end(), 0);
}

void Rave::update(int x, int y, int color, bool win) {
  int idx = getIdx(x, y);

  if (color == 1) {
    if (win)
      ++Ocolor1_[idx].win;
    ++Ocolor1_[idx].played;
  }
  else if (color == 2) {
    if (win)
      ++Ocolor2_[idx].win;
    ++Ocolor2_[idx].played;
  }
}

int Rave::getIdx(int x, int y) {
  return (y * 19 + x);
}

int Rave::getWin(int x, int y, int color) {
  int idx = getIdx(x, y);

  if (color == 1) {
    return Ocolor1_[idx].win;
  }
  else if (color == 2) {
    return Ocolor2_[idx].win;
  }
  else
    return (0);
}

int Rave::getPlayed(int x, int y, int color) {
  int idx = getIdx(x, y);

  if (color == 1) {
    return Ocolor1_[idx].played;
  }
  else if (color == 2) {
    return Ocolor2_[idx].played;
  }
  else
    return (0);
}

void Rave::ActualiseScore(Goban &goban) {
  for (int i = 0; i < 361; i++) {
    float wi;
    float ni;
    float zonning;

    if (goban.IsInZones((char) Ocolor1_[i].x, (char) Ocolor1_[i].y))
      zonning = 2.f;
    else
      zonning = 0.5f;
    wi = Ocolor1_[i].win;
    ni = Ocolor1_[i].played;
    if (zonning == 0.5f)
      Ocolor1_[i].score = 0;
    else
      Ocolor1_[i].score = zonning * ((wi / ni) + (1.f * (float) sqrt((sqrt(t_) / ni))));

    wi = Ocolor2_[i].win;
    ni = Ocolor2_[i].played;
    if (zonning == 0.5f)
      Ocolor2_[i].score = 0;
    else
      Ocolor2_[i].score = zonning * ((wi / ni) + (1.f * (float) sqrt((sqrt(t_) / ni))));
  }
}

void Rave::Merge(std::vector<Rave> &others, Goban &goban) {
  Rave tmp = *this;
  (void) goban;
  for (int i = 0; i < 361; ++i) {
    for (auto &it : others) {
      Ocolor1_[i].played += it.Ocolor1_[i].played - tmp.Ocolor1_[i].played;
      Ocolor1_[i].win += it.Ocolor1_[i].win - tmp.Ocolor1_[i].win;
      Ocolor2_[i].played += it.Ocolor2_[i].played - tmp.Ocolor2_[i].played;
      Ocolor2_[i].win += it.Ocolor2_[i].win - tmp.Ocolor2_[i].win;
    }
  }
  int size = (int) others.size();
  for (int j = 0; j < size; ++j) {
    others[j] = *this;
  }
  return ;
}

Rave::Play &Rave::Play::operator=(const Rave::Play &ref) {
  x = ref.x;
  y = ref.y;
  win = ref.win;
  played = ref.played;
  score = ref.score;
  modified = ref.modified;
  return *this;
}
