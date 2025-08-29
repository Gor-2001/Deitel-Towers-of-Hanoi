#ifndef GAME_H
#define GAME_H

#include "canvas.h"

class Game
{
public:

    void start();

private:

    Canvas canvas;
    void makeNextMove(const unsigned int pause_time_ms = 500);
    void process();
    void help() const;
    bool win() const;
    bool exit() const;
    void solveRandom();
};

#endif // GAME_H
