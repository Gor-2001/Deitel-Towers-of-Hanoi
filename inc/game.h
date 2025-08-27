#ifndef GAME_H
#define GAME_H

#include "towers.h"

class Game
{
public:

    void start() const;

private:

    void process(Towers& towers) const;
    void exit() const;
    void help(const Towers& towers) const;
    bool win(const Towers& towers) const;

};

#endif
