
#include <iostream>
#include <ctime>
//#include <gperftools/profiler.h>
#include "Goban.h"
#include "Controller.h"

//Goban TODO:
#include "Tree.hpp"

//TODO: Add defeat condition when goban is full
//TODO: Force defend strike when alignement detected
//TODO: Add ai bool in file
//TODO: Remove useless condition and print

// int main() {
// 	Controller ctrl;
//   Goban goban;
//
//   srand(time(NULL));
//   ctrl.Init(goban);
//   if (ctrl.Play(goban)) {
// 	  std::cerr << "Play allowed" << std::endl;
// 	  system("PAUSE");
// 	  return (1);
//   }
//   std::cerr << "Play refused" << std::endl;
// 	system("PAUSE");
//   return 0;
// }

int main() {
    Controller ctrl;
    srand(time(NULL));
    ctrl.Start();
}
