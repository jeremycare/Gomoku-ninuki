//
// Created by care_j on 2/11/16.
//

#include <iostream>
#include "Print.hpp"
#include "../lib/ctpl/ctpl_stl.h"
//#include <gperftools/profiler.h>

AI::AI(Goban &goban, char color)
        : current_(goban)
        , temporary_(goban)
        , monteCarlos(color , 1, 1, -1, -1, 1.f)
{
}

AI::~AI() {}


Cell AI::playTurn(int simulations) {
  auto t1 = std::chrono::high_resolution_clock::now();
  Rave mainRave;
  
  for (int i = 0; i < simulations; ++i) {
    temporary_ = current_;
    monteCarlos.expand(0, temporary_, &mainRave);
    mainRave.SortVects(current_);
  }
  auto t2 = std::chrono::high_resolution_clock::now();
  std::cout << "ia take : " << std::chrono::duration_cast<std::chrono::milliseconds>(t2-t1).count() << " ms\n";
  Print print;
  print.printRave(&mainRave);
  print.printStats(current_.cell, monteCarlos.nextPlays_);
  return (monteCarlos.getFinalPlay()->getCell());
}

/*Cell AI::playTurn() {
  auto t1 = std::chrono::high_resolution_clock::now();
  Rave mainRave;
  std::vector<Rave> copysRave(NB_THREADS);
  std::vector<Tree *> plays;
  int count = 0;
  std::vector<Goban> copysGoban(NB_THREADS);

 /monteCarlos.addChild(current_);
  mainRave.Merge(copysRave, current_);
  ctpl::thread_pool p(NB_THREADS);
  for (int i = 0; i < NUMBER_SIMULATION; i+= NB_THREADS) {
    for (auto &it : copysGoban) {
      it = current_;
    }
    plays = monteCarlos.getBestPlays(&mainRave, NB_THREADS);
    int raveNb = 0;
    for (auto &it : plays) {
      temporary_ = current_;
      p.push(LaunchThread, it, &(copysRave[raveNb]), temporary_);
      raveNb++;
    }
    while (p.n_idle() != NB_THREADS);
    if (count % 30 == 0) {
      mainRave.Merge(copysRave, current_);
    }

    count++;
  }
  mainRave.Merge(copysRave, current_);
 // ProfilerStop();
  auto t2 = std::chrono::high_resolution_clock::now();
  std::cout << "ia take : " << std::chrono::duration_cast<std::chrono::milliseconds>(t2-t1).count() << " ms\n";
  Print print;
  print.printRave(&mainRave);
  print.printStats(current_.cell, monteCarlos.nextPlays_);
  return (monteCarlos.getFinalPlay()->getCell());
}*/
