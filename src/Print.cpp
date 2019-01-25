#include <iostream>
#include <iomanip>
#include "Print.hpp"

Print::Print() {}

Print::~Print() {}

Cell Print::askPlay(Goban &goban, int color) {
  if (color == 1)
    std::cout << "You are WHITE" << '\n';
  else
    std::cout << "You are BLACK" << '\n';
  printplate(goban.cell, goban.black, goban.white);
  int x, y;
  std::cout << "Your play \nx : " << '\n';
  std::cin >> x;
  std::cout << "Your play \ny : " << '\n';
  std::cin >> y;
  Cell cell;
  cell.x = (char) (x);
  cell.y = (char) (y);
  return (cell);
}

void Print::printplate(std::string cells, int black, int white) {
  std::cout << "Black capture : " << black << " | White capture : " << white << "\n";
  std::string base = "0123456789ABCDEFGHI\n";
  std::cout << "  " + base;
  for (int y = 0; y < 19; y++) {
    std::cout << base[y] << " ";
    for (int x = 0; x < 19; x++) {
      if (cells[y * 19 + x] == 1 + '0')
        std::cout << "1";
      else if (cells[y * 19 + x] == 2 + '0')
        std::cout << "2";
      else
        std::cout << ".";
    }
    std::cout << "\n";
  }
  std::cout << "\n";
}

void Print::printStats(AI *ia) {
  std::string base = "0123456789ACDEFGHI\n";

  std::cout << "win : " << ia->monteCarlos.win_ << " played_ : " << ia->monteCarlos.played_ << "\n";
  for (int y = 0; y < 19; y++) {
    std::cout << base[y] << " ";
    for (int x = 0; x < 19; x++) {
      if (ia->current_.cell[y * 19 + x] == 1 + '0')
        std::cout << "[     W     ]";
      else if (ia->current_.cell[y * 19 + x] == 2 + '0')
        std::cout << "[     B     ]";
      else {
        bool print = false;
        for (auto &it : ia->monteCarlos.nextPlays_) {
          if (it->x_ == x && it->y_ == y) {
            print = true;
            std::cout << "[" << std::fixed << std::setw(5) << std::setprecision(2)
                    << /*it->evaluate(ia.monteCarlos.played_)*/ it->win_ << "-" << std::setw(5) << it->played_ << "]";
          }
        }
        if (!print) {
          std::cout << "[   .  ]";
        }
      }
    }
    std::cout << "|\n";
  };
}

void Print::printStats(std::string cell, std::vector<Tree *> nextPlays) {
  std::string base = "0123456789ABCDEFGHI\n";

  int i,j;
  i = j = 0;
  for (int y = 0; y < 19; y++) {
    std::cout << base[y] << " ";
    for (int x = 0; x < 19; x++) {
      if (cell[y * 19 + x] == 1 + '0')
        std::cout << "[     W     ]";
      else if (cell[y * 19 + x] == 2 + '0')
        std::cout << "[     B     ]";
      else {
        bool print = false;
        for (auto &it : nextPlays) {
          if (it->x_ == x && it->y_ == y) {
            print = true;
            std::cout << "[" << std::fixed << std::setw(5) << std::setprecision(2)
                      << /*it->evaluate(ia.monteCarlos.played_)*/ it->win_ << "-" << std::setw(5) << it->played_ << "]";
            if (it->win_ != 1)
              i += it->win_ - 1;
            if (it->played_ != 1)
              j += it->played_ - 1;
          }
        }
        if (!print) {
          std::cout << "[     .     ]";
        }
      }
    }
    std::cout << "|\n";
  };
  std::cout << "win : " << i << " played = " << j << "\n";
}

void Print::printStats(AI ia, Rave *rave) {
  std::vector<Tree*> nP = ia.monteCarlos.nextPlays_;
  Goban goban = ia.current_;
  std::string cells = goban.cell;
  std::string base = "0123456789ABCDEFGHI\n";

  std::cout << ia.monteCarlos.played_ << "\n";
  for (int y = 0; y < 19; y++) {
    std::cout << base[y] << " ";
    for (int x = 0; x < 19; x++) {
      if (cells[y * 19 + x] == 1 + '0')
        std::cout << "[   W   ]";
      else if (cells[y * 19 + x] == 2 + '0')
        std::cout << "[   B   ]";
      else {
        bool print = false;
        for (auto &it : nP) {
          if (it->x_ == x && it->y_ == y) {
            print = true;
            std::cout << "[" << std::fixed << std::setw(3) << std::setprecision(2) << /*it->evaluate(ia.monteCarlos.played_)*/ it->win_<< "-" << std::setw(3) << it->played_ << "]";
          }
        }
        if (!print) {
          std::cout << "[   .  ]";
        }
      }
    }
    std::cout << "\n";
  }
  for (int y = 0; y < 19; y++) {
    for (int x = 0; x < 19; x++) {
      if (cells[y * 19 + x] == 1 + '0')
        std::cout << "[   W   ]";
      else if (cells[y * 19 + x] == 2 + '0')
        std::cout << "[   B   ]";
      else {
        bool print = false;
        for (auto &it : nP) {
          if (it->x_ == x && it->y_ == y) {
            print = true;
            std::cout << "[" << std::fixed << std::setw(3) << std::setprecision(2) << rave->getWin(x, y, 1) << "-"
                      << std::setw(3) << rave->getPlayed(x, y, 1) << "]";
          }
        }
        if (!print) {
          std::cout << "[   .   ]";
        }
      }
    }
    std::cout << "\n";
  }
  std::cout << "--\n";
  nP.clear();
}

void Print::printRave(Rave *rave) {
  std::string base = "0123456789ABCDEFGHI\n";
  std::cout << "color 1 :" << "\n";
  for (int y = 0; y < 19; y++) {
    std::cout << base[y] << " ";
    for (int x = 0; x < 19; x++) {
      std::cout << "[" << std::fixed << std::setw(5) << std::setprecision(2) << rave->getWin(x, y, 1) << "-"
                << std::setw(5) << rave->getPlayed(x, y, 1)/* rave->getScore(x,y,1)*/ << "]";
    }
    std::cout << "\n";
  }
  std::cout << "\n";
  std::cout << "color 2 :" << "\n";
  for (int y = 0; y < 19; y++) {
    std::cout << base[y]<< " ";
    for (int x = 0; x < 19; x++) {
      std::cout << "[" << std::fixed << std::setw(5) << std::setprecision(2) << rave->getWin(x, y, 2) << "-"
                << std::setw(5) << rave->getPlayed(x, y, 2) /*rave->getScore(x,y,2)*/<< "]";
    }
    std::cout << "\n";
  }
  std::cout << "\n";
}