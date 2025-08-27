#ifndef GAME_H
#define GAME_H

#include "canvas.h"

class Game
{
public:

    void start() const;

private:

    void process(Canvas& canvas) const;
    bool exit(const Canvas& canvas) const;
    void help(const Canvas& canvas) const;
    bool win(const Canvas& canvas) const;

};

#endif // GAME_H
