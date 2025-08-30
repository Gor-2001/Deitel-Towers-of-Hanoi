#ifndef GAME_H
#define GAME_H

#include "canvas.h"

class Game
{
public:

    void start();

private:

    Canvas canvas;
    void makeNextMove(unsigned long pause_time_ms = 500);
    void process();
    void help() const;
    bool win() const;
    bool exit() const;
    void solveConcludingRandom();
    void solveConcluding();
    void solveInitial();
    void solve();
};

#endif // GAME_H
