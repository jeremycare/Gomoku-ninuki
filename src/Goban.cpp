//
// Created by care_j on 25/10/16.
//

#include <fstream>
#include <sstream>
#include <iostream>
#include "Goban.h"

bool operator==(const Cell & ref, const Cell &ref2) {
	return (ref2.x == ref.x && ref2.y == ref.y);
}

Goban::Goban()
{
	black = 0;
	white = 0;
	win = false;
	cell = std::string(361, '0');
	doubleThree_ = 0;
	totalStone_ = 0;
	breakable = false;
	vx = 0;
	vy = 0;
	zones_ = std::vector<bool> (361, false);
	zones_[180] = true;
}

Goban::Goban(const Goban & ref)
{
	black = ref.black;
	white = ref.white;
	win = ref.win;
	cell = ref.cell;
	doubleThree_ = ref.doubleThree_;
	totalStone_ = ref.totalStone_;
	whitePrisoner_ = ref.whitePrisoner_;
	blackPrisoner_ = ref.blackPrisoner_;
	breakable = ref.breakable;
	breakables = ref.breakables;
	vx = ref.vx;
	vy = ref.vy;
	zones_ = ref.zones_;
}

Goban &Goban::operator=(const Goban & ref)
{
	black = ref.black;
	white = ref.white;
	win = ref.win;
	cell = ref.cell;
	doubleThree_ = ref.doubleThree_;
	totalStone_ = ref.totalStone_;
	whitePrisoner_ = ref.whitePrisoner_;
	blackPrisoner_ = ref.blackPrisoner_;
	breakable = ref.breakable;
	breakables = ref.breakables;
	vx = ref.vx;
	vy = ref.vy;
	zones_ = ref.zones_;
	return *this;
}

Goban::~Goban() {}

bool Goban::IsLegalSimulation(char cX, char cY) {
	return GetIntersection(cX, cY) == EMPTY;
}

bool Goban::IsLegal(char cX, char cY, char color) {
	char v[3] = { -1, 0, 1 };

	if (breakable) {
		for (auto &it : breakables) {
			if (it.x == cX && it.y == cY) {
				return (true);
			}
		}
    return (false);
	}

/*	if (GetIntersection(cX, cY) == EMPTY) {
		SetGoban(cX, cY, color);

		for (int x = 0; x < 3; ++x) {
			for (int y = 0; y < 3; ++y) {
				if (!(v[x] == 0 && v[y] == 0)) {
					if (CheckDoubleThree(cX, cY, v[x], v[y])) {
						SetGoban(cX, cY, EMPTY);
            std::cout << "double trois\n";
						return false;
					}
				}
			}
		}
		SetGoban(cX, cY, EMPTY);
		doubleThree_ = 0;

		return true;
	}
	doubleThree_ = 0;

	return false;*/
	return (GetIntersection(cX, cY) == EMPTY);
}

bool Goban::IsLegalWthree(char cX, char cY) {

  if (breakable) {
    for (auto &it : breakables) {
      if (it.x == cX && it.y == cY) {
        return (true);
      }
    }
    return (false);
  }

  return (GetIntersection(cX, cY) == EMPTY);
}

bool Goban::IsWin(char cX, char cY, char playerColor) {

	if (CheckAlignment(cX, cY, playerColor)) {
		win = true;
	} else if (totalStone_ >= width_ * height_) {
		win = true;
	} else {
		for (const auto & it : whitePrisoner_) {
			++black;
			SetGoban(it.x, it.y, EMPTY);
		}
		whitePrisoner_.clear();
		for (const auto & it : blackPrisoner_) {
			++white;
			SetGoban(it.x, it.y, EMPTY);
		}
		blackPrisoner_.clear();
		if (black >= 10) {
			win = true;
		}
		else if (white >= 10) {
			win = true;
		}
	}
	return win;
}


bool Goban::IsWinAI(char cX, char cY, char color) {

  if (CheckAlignmentAI(cX, cY, color)) {
    win = true;
  } else if (totalStone_ >= width_ * height_) {
    win = true;
  } else {
    for (const auto & it : whitePrisoner_) {
      ++black;
      SetGoban(it.x, it.y, EMPTY);
    }
    whitePrisoner_.clear();
    for (const auto & it : blackPrisoner_) {
      ++white;
      SetGoban(it.x, it.y, EMPTY);
    }
    blackPrisoner_.clear();
    if (black >= 10) {
      win = true;
    }
    else if (white >= 10) {
      win = true;
    }
  }
  return win;
}


bool Goban::IsAlignAI(std::vector<Neighbor> &n) {
  int align = 0;
  int beginIndex = 0;
  int size = (int) n.size();

  for (int i = 0; i < size; i++) {
    if (n[i].value == n[POS].value) {
      beginIndex = align == 0 ? i : beginIndex;
      ++align;
      if (align == 5) {
          return true;
      }
    }
    else {
      align = 0;
    }
  }
  return false;
}

void Goban::CheckPrisoner(char cX, char cY, char playerColor) {
	char v[3] = { -1, 0, 1 };
	int p, p1, p2, p3;

	for (int x = 0; x < 3; ++x) {
		for (int y = 0; y < 3; ++y) {
			if (!(v[x] == 0 && v[y] == 0)) {
				p = GetIntersection(cX, cY);
				p1 = GetIntersection(cX + v[x], cY + v[y]);
				p2 = GetIntersection(static_cast<char>(cX + v[x] * 2), static_cast<char>(cY + v[y] * 2));
				p3 = GetIntersection(static_cast<char>(cX + v[x] * 3), static_cast<char>(cY + v[y] * 3));

				if (p == p3 && p1 == GetEnemyColor(playerColor) && p2 == GetEnemyColor(playerColor)) {

					if (playerColor == WHITE) {
						whitePrisoner_.push_back({static_cast<char>(cX + v[x]), static_cast<char>(cY + v[y])});
						whitePrisoner_.push_back({static_cast<char>(cX + v[x] * 2), static_cast<char>(cY + v[y] * 2)});
					} else if (playerColor == BLACK) {
						blackPrisoner_.push_back({static_cast<char>(cX + v[x]), static_cast<char>(cY + v[y])});
						blackPrisoner_.push_back({static_cast<char>(cX + v[x] * 2), static_cast<char>(cY + v[y] * 2)});
					}

				}
			}
		}
	}
}

std::vector<Cell> &Goban::GetLegalCells(char color) {
  legals_.clear();

  if (breakable) {
    return breakables;
  }
  for (char x = 0; x < width_; ++x) {
    for (char y = 0; y < height_; ++y) {
      if (IsLegal(x, y, color)) {
        legals_.push_back({ x, y });
      }
    }
  }
  return legals_;
}

std::vector<Cell> &Goban::GetLegalCellsAI() {
  legals_.clear();

  if (breakable) {
    return breakables;
  }
  for (char x = 0; x < width_; ++x) {
    for (char y = 0; y < height_; ++y) {
      if (IsLegalWthree(x, y)) {
        legals_.push_back({ x, y });
      }
    }
  }
  return legals_;
}

void Goban::SetGoban(char x, char y, char value) {
	cell[y * width_ + x] = value + '0';
	if (value == EMPTY) {
		--totalStone_;
	} else {
		++totalStone_;
	}
}

void Goban::SetNeighbor(std::vector<Neighbor> & neighbor, char cX, char cY, char vX, char vY) const {
	neighbor[PREV_3] = {static_cast<char>(cX - vX * 3), static_cast<char>(cY - vY * 3),
						GetIntersection(static_cast<char>(cX - vX * 3), static_cast<char>(cY - vY * 3))};
	neighbor[PREV_2] = {static_cast<char>(cX - vX * 2), static_cast<char>(cY - vY * 2),
						GetIntersection(static_cast<char>(cX - vX * 2), static_cast<char> (cY - vY * 2))};
	neighbor[PREV_1] = {static_cast<char>(cX - vX), static_cast<char>(cY - vY), GetIntersection(cX - vX, cY - vY) };
	neighbor[POS] = { cX, cY, GetIntersection(cX, cY) };
	neighbor[NEXT_1] = {static_cast<char>(cX + vX), static_cast<char>(cY + vY), GetIntersection(cX + vX, cY + vY) };
	neighbor[NEXT_2] = {static_cast<char> (cX + vX * 2), static_cast<char> (cY + vY * 2),
						GetIntersection(static_cast<char>(cX + vX * 2), static_cast<char>(cY + vY * 2))};
	neighbor[NEXT_3] = {static_cast<char> (cX + vX * 3), static_cast<char> (cY + vY * 3),
						GetIntersection(static_cast<char>(cX + vX * 3), static_cast<char>(cY + vY * 3))};
	neighbor[NEXT_4] = {static_cast<char> (cX + vX * 4), static_cast<char> (cY + vY * 4),
						GetIntersection(static_cast<char>(cX + vX * 4), static_cast<char>(cY + vY * 4))};
}

bool Goban::CheckAlignment(char cX, char cY, char playerColor) {
	char v[3] = { -1, 0, 1 };
	std::vector<Neighbor> n(8);

	for (int x = 0; x < 3; ++x) {
		for (int y = 0; y < 3; ++y) {
			if (!(v[x] == 0 && v[y] == 0)) {
				SetNeighbor(n, cX, cY, v[x], v[y]);

				if (IsAlign(n, playerColor)) {
					return true;
				}
			}
		}
	}
	return false;
}

bool Goban::CheckAlignmentAI(char cX, char cY, char color) {
  char v[8][2] = {{-1, -1},
                  {1,  1},
                  {-1, 0},
                  {1,  0},
                  {0, 1},
                  {0, -1},
                  {1,  -1},
                  {-1, 1}};
  char vd[5] = {1, 2, 3, 4};
  int count = 0;

  while (count < 8) {
    int cpt = 0;
    int i = 0;

    while (i < 4 && GetIntersection(cX + (vd[i] * v[count][0]), cY + (vd[i] * v[count][1])) == color) {
      ++cpt;
      ++i;
    }

    i = 0;
    while (i < 4 && GetIntersection(cX + (vd[i] * v[count + 1][0]), cY + (vd[i] * v[count + 1][1])) == color) {
      ++cpt;
      ++i;
    }
    if (cpt >= 4) {
      return true;
    }
    count += 2;
  }


  return false;
}


bool Goban::IsAlign(std::vector<Neighbor> &n, char playerColor) {
	int align = 0;
	int beginIndex = 0;
	int size = (int) n.size();

	for (int i = 0; i < size; i++) {
		if (n[i].value == n[POS].value) {
			beginIndex = align == 0 ? i : beginIndex;
			++align;
			if (align == 5) {
				if (!IsBreakable(n, beginIndex, i, playerColor)) {
					return true;
				}
				else {
					breakable = true;
				}
			}
		}
		else {
			align = 0;
		}
	}
	return false;
}

bool Goban::CheckDoubleThree(int x, int y, int vX, int vY) {
	int prev2 = GetIntersection(static_cast<char>(x - vX * 2), static_cast<char>(y - vY * 2));
	int prev = GetIntersection(static_cast<char>(x - vX), static_cast<char>(y - vY));
	int pos = GetIntersection(static_cast<char>(x), static_cast<char>(y));
	int next = GetIntersection(static_cast<char>(x + vX), static_cast<char>(y + vY));
	int next2 = GetIntersection(static_cast<char>(x + vX * 2), static_cast<char>(y + vY * 2));
	int next3 = GetIntersection(static_cast<char>(x + vX * 3), static_cast<char>(y + vY * 3));
	int next4 = GetIntersection(static_cast<char>(x + vX * 4), static_cast<char>(y + vY * 4));

	if (doubleThree_ >= 2) {
		doubleThree_ = 0;
		return (true);
	}

	// [_Xxx_] || [_xxX_]
	if (pos == next && pos == next2	&& prev == EMPTY && next3 == EMPTY) {
		++doubleThree_;
		//std::cerr << "Double three case 1 [_Xxx_]|| [_xxX_]" << std::endl;
		return CheckThreeAlign(x + vX, y + vY, vX, vY) || CheckThreeAlign(x + vX * 2, y + vY * 2, vX, vY);
	}

	//[_Xx_x_] || [_x_xX_]
	if (pos == next && pos == next3	&& prev == EMPTY && next4 == EMPTY) {
		++doubleThree_;
		//std::cerr << "Double three case 2 [_Xx_x_]|| [_x_xX_]" << std::endl;
		return CheckThreeAlign(x + vX, y + vY, vX, vY) || CheckThreeAlign(x + vX * 3, y + vY * 3, vX, vY);
	}

	//[_X_xx_] || [_xx_X_]
	if (pos == next2 && pos == next3 && prev == EMPTY && next4 == EMPTY) {
		++doubleThree_;
		//std::cerr << "Double three case 3 [_X_xx_] || [_xx_X_]" << std::endl;
		return CheckThreeAlign(x + vX * 2, y + vY * 2, vX, vY) || CheckThreeAlign(x + vX * 3, y + vY * 3, vX, vY);
	}

	//[_xXx_]
	if (pos == next && pos == prev && prev2 == EMPTY && next2 == EMPTY && (vx + vX != 0 || vy + vY != 0)) {
		++doubleThree_;
		//std::cout << "vX : " << vX << " vY : "  << vY << "\n";
    vx = vX;
    vy = vY;
		//std::cerr << "Double three case 4 [_x_Xx_] || [_xX_X_]" << std::endl;
		return CheckThreeAlign(x + vX, y + vY, vX, vY) || CheckThreeAlign(x - vX, y - vY, vX, vY);
	}

	//[_x_Xx_] || [_xX_x_]
	if (pos == next && pos == prev2	&& prev == EMPTY && next2 == EMPTY) {
		++doubleThree_;
		//std::cerr << "Double three case 5 [_x_Xx_] || [_xX_X_]" << std::endl;
		return CheckThreeAlign(x + vX, y + vY, vX, vY) || CheckThreeAlign(x - vX * 2, y - vY * 2, vX, vY);;
	}
	return false;
}

bool Goban::CheckThreeAlign(int boganX, int boganY, int vX, int vY) {
	int v[3] = { -1, 0, 1 };

	for (int x = 0; x < 3; ++x) {
		for (int y = 0; y < 3; ++y) {
			if (!(v[x] == 0 && v[y] == 0)
				  && !(v[x] == vX && v[y] == vY)
				  && !(v[x] == vX * -1 && v[y] == vY * -1)
				  && CheckDoubleThree(boganX, boganY, v[x], v[y])) {
				    return true;
			}
		}
	}
	return false;
}

char Goban::GetIntersection(char x, char y) const {

	if (x >= width_ || y >= height_ || x < 0 || y < 0) {
		return OUT;
	}
	return cell[y * width_ + x] - '0';
}

int Goban::GetEnemyColor(char color) const {
	return color == WHITE ? BLACK : WHITE;
}

bool Goban::IsInBreakables(int x, int y) {
  for (auto &it : breakables) {
    if (it.x == x && it.y == y)
      return true;
  }
  return false;
}

bool Goban::IsBreakable(const std::vector<Neighbor> & n, int beginIndex, int endIndex, char playerColor) {
  int v[3] = { -1, 0, 1 };
  char enemyColor = static_cast<char>(GetEnemyColor(playerColor));

  for (int it = beginIndex; it <= endIndex; ++it) {
    for (int x = 0; x < 3; ++x) {
      for (int y = 0; y < 3; ++y) {
        if (!(v[x] == 0 && v[y] == 0)) {
          int p02 = GetIntersection(static_cast<char>(n[it].x - v[x] * 2), static_cast<char>(n[it].y - v[y] * 2));
          int p01 = GetIntersection(static_cast<char>(n[it].x - v[x]), static_cast<char>(n[it].y - v[y]));
          int p = GetIntersection(n[it].x, n[it].y);
          int p1 = GetIntersection(static_cast<char>(n[it].x + v[x]), static_cast<char>(n[it].y + v[y]));
          int p2 = GetIntersection(static_cast<char>(n[it].x + v[x] * 2), static_cast<char>(n[it].y + v[y] * 2));


          if (p == p1) {
            if (p2 == enemyColor && p01 == EMPTY) {
              if (!IsInBreakables((n[it].x - v[x]), (n[it].y - v[y])))
                if (IsLegal(static_cast<char>(n[it].x - v[x]), static_cast<char>(n[it].y - v[y]), enemyColor))
                  breakables.push_back({static_cast<char>(n[it].x - v[x]), static_cast<char>(n[it].y -v[y])});
            }
            if (p2 == EMPTY && p01 == enemyColor) {
              if (!IsInBreakables((n[it].x + v[x] * 2), (n[it].y - v[y] * 2)))
                if (IsLegal(static_cast<char>(n[it].x + v[x] * 2), static_cast<char>(n[it].y + v[y] * 2), enemyColor))
                  breakables.push_back({static_cast<char>(n[it].x + v[x] * 2), static_cast<char>(n[it].y + v[y] * 2)});
            }
          }
          if (p == p01) {
            if (p02 == enemyColor && p1 == EMPTY) {
              if (!IsInBreakables((n[it].x + v[x]), (n[it].y + v[y])))
                if (IsLegal(static_cast<char>(n[it].x + v[x]), static_cast<char>(n[it].y + v[y]), enemyColor))
                  breakables.push_back({static_cast<char>(n[it].x + v[x]), static_cast<char>(n[it].y + v[y])});
            }
            if (p02 == EMPTY && p1 == enemyColor) {
              if (!IsInBreakables((n[it].x - v[x] * 2), (n[it].y - v[y] * 2)))
                if (IsLegal(static_cast<char>(n[it].x - v[x] * 2), static_cast<char>(n[it].y - v[y] * 2), enemyColor))
                  breakables.push_back({static_cast<char>(n[it].x - v[x] * 2), static_cast<char>(n[it].y - v[y] * 2)});
            }
          }
        }
      }
    }
  }
  if (!breakables.empty())
    breakable = true;
  return breakable;
}

bool Goban::PlayOnGoban(char x, char y, char color) {
  SetGoban(x, y, color);
  CheckPrisoner(x, y, color);
  breakable = false;
  breakables.clear();
  AddZone(x, y);
  return (IsWin(x, y, color));
}

bool Goban::PlayOnGobanAI(char x, char y, char color) {
  SetGoban(x, y, color);
  CheckPrisoner(x, y, color);
  breakable = false;
  breakables.clear();
  AddZone(x, y);
  return (IsWinAI(x, y, color));
}

bool Goban::PlayOnGobanSimulation(char x, char y, char color) {
  SetGoban(x, y, color);
  CheckPrisoner(x, y, color);
  breakable = false;
  breakables.clear();
  return (IsWinAI(x, y, color));
}

void Goban::AddZone(char x, char y) {
  std::vector<int> pos = {-2, -1, 0, 1, 2};

  for (int i = 0; i < static_cast<int>(pos.size()); ++i) {
    for (int j = 0; j < static_cast<int>(pos.size()); ++j) {
      int px = pos[j] + x;
      int py = pos[i] + y;
      if (px >= 0 && py < 19 && py >= 0 && py < 19) {
        int idx = (py * 19) + px;
        zones_[idx] = true;
      }
    }
  }
}

bool Goban::IsInZones(char x, char y) {
  int idx = x + y * 19;
	return zones_[idx];
}
