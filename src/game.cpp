#include "game.h"

void Game::start() const {

    unsigned int disk_count = 3;
    gameStartingMode_t game_starting_mode = gameStartingModeBasic;

    CLEAR_SCREEN();

    //Starting instructions
    std::cout <<
        "To continue the game, press Enter. "
        "Also during the game, if you need help, press the 'h' key."
        << std::endl;

    char ch;
    bool flag;

    flag = true;

    while (flag) {
        if (_KBHIT()) {
            ch = __GET_CH();

            if (ch == ENTER_VALUE) {
                flag = false;
            }
        }
    }

    CLEAR_SCREEN();


    // Enter game starting mode
    std::cout <<
        "To continue the game, press 'b' for basic start and "
        "'r' for random start."
        << std::endl;

    flag = true;

    while (flag) {
        if (_KBHIT()) {
            ch = __GET_CH();

            if (ch == 'b' || ch == 'r' || ch == ENTER_VALUE) {
                flag = false;
            }
        }
    }

    CLEAR_SCREEN();

    if (ch == 'r')
        game_starting_mode = gameStartingModeRandom;


    // Enter Disk Count
    std::cout <<
        "To start the game, enter the number from 1 to 9 to enter the disks count."
        << std::endl;

    flag = true;

    while (flag) {
        if (_KBHIT()) {
            ch = __GET_CH();

            if ((ch >= '1' && ch <= '9') || ch == ENTER_VALUE) {
                flag = false;
            }
        }
    }

    CLEAR_SCREEN();

    if(ch >= '1' && ch <= '9')
        disk_count = ch - '0';

    // Tower Init and start the game
    Towers towers(disk_count, game_starting_mode);
    process(towers);
}

void Game::process(Towers& towers) const {
    volatile int ch; // Use volatile to prevent compiler optimizations
    
    while (true) {
        if (_KBHIT()) {
            ch = __GET_CH();

            switch (ch) {

            // Validate
            case ENTER_VALUE:
                if (win(towers))
                    return;
                break;

            // Escape
            case 27:
                if(exit(towers));
                    return;
                break;

            // Move Left (a)
            case 'a':
                towers.cursorMoveLeft();
                break;

            // Move Right (d)
            case 'd':
                towers.cursorMoveRight();
                break;

            // Open help window (h)
            case 'h':
                help(towers);
                break;

            // Move Down (s)
            case 's':
                towers.diskMoveDown();
                break;

            // Move Up (w)
            case 'w':
                towers.diskMoveUp();
                break;

            default:
                break;
            }
        }
        SLEEP(10);
    }
}


bool Game::exit(Towers& towers) const {

    CLEAR_SCREEN();

    std::cout <<
        "Do you really want to escape the game ? If yes press y if not press n."
        << std::endl;

    char ch;
    bool flag = true;

    while (flag) {
        if (_KBHIT()) {
            ch = __GET_CH();

            if (ch == 'n' || ch == 'y') {
                flag = false;
            }
        }
    }

    if(ch == 'n') {
        CLEAR_SCREEN();
        towers.displayTowers();
        return false;
    }
    else {
        CLEAR_SCREEN();
        std::cout << "ESC pressed. Exiting.\n";
        return true;
    }
}

bool Game::win(const Towers& towers) const {

    if(towers.isWinningPosition()) {
        CLEAR_SCREEN();
        std::cout << "You Win.\n";
        return true;
    }

    return false;
}


void Game::help(const Towers& towers) const {

    // Clear the screen and display help
    CLEAR_SCREEN();

    std::cout << "NAME\n";
    std::cout << "\tTowers of Hanoi - a command-line puzzle game\n\n";

    std::cout << "SYNOPSIS\n";
    std::cout << "\tMove all disks from the left tower to the right tower.\n\n";

    std::cout << "CONTROLS\n";
    std::cout << "\tTo move the cursor between towers:\n";
    std::cout << "\t\t'd' or Right Arrow: Move cursor to the right\n";
    std::cout << "\t\t'a' or Left Arrow: Move cursor to the left\n";
    std::cout << "\t\t'u' or Up Arrow: Pick up a disk\n";
    std::cout << "\t\t's' or Down Arrow: Place a disk\n";
    std::cout << "\t\t'q' or ESC: Quit the game\n";
    std::cout << "\t\t'h': Show this help menu\n\n";

    std::cout << "\tTo validate a move:\n";
    std::cout << "\t\tEnter: Validate your position and win if all disks are in the correct order.\n\n";

    std::cout << "EXIT\n";
    std::cout << "\tPress 'h' to return to the game.\n\n";

    // Wait for the 'h' key to be pressed to exit help mode
    char ch;
    bool flag = true;

    while (flag) {
        if (_KBHIT()) {
            ch = __GET_CH();

            if (ch == 'h') {
                flag = false;
            }
        }
    }

    // Clear the help screen and redraw the game state
    CLEAR_SCREEN();
    towers.displayTowers();
}