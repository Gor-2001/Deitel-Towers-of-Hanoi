#ifndef GAME_H
#define GAME_H

#include "canvas.h"

class Game
{
public:

    void start();

private:

    Canvas canvas;

    // Game control
    void process();
    void help() const;
    bool win() const;
    bool exit() const;

    // Solution
    void solve();
    void solveState(unsigned int* pause_time_ms, char* ch);
    void makeNextMove(unsigned long pause_time_ms = 500);
};

#endif // GAME_H
