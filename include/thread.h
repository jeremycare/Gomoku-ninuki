//
// Created by care_j on 08/01/17.
//

#ifndef GOMOKU_NINUKI_THREAD_H
# define GOMOKU_NINUKI_THREAD_H


#define NB_THREADS 4

void LaunchThread(int id, Tree* tree, Rave *rave, Goban goban);

#endif //GOMOKU_NINUKI_THREAD_H
