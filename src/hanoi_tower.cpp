#include "game.h"
#include "hanoi_tower.h"

void startHanoiGame() {

    Game game;
    game.start();
    restore_terminal_mode();
}