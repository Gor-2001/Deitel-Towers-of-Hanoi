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
    do {
        ch = _getch();
    } while (ch != ENTER_VALUE);

    CLEAR_SCREEN();


    // Enter game starting mode
    std::cout <<
        "To continue the game, press 'b' for basic start and "
        "'r' for random start."
        << std::endl;

    do {
        ch = _getch();
    } while (ch != 'b' && ch != 'r' && ch != ENTER_VALUE);

    CLEAR_SCREEN();

    if (ch == 'r')
        game_starting_mode = gameStartingModeRandom;


    // Enter Disk Count
    std::cout <<
        "To start the game, enter the number from 1 to 9 to enter the disks count."
        << std::endl;

    do {
        ch = _getch();
    } while ((ch > '9' || ch < '1') && ch != ENTER_VALUE);

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
        if (_kbhit()) {
            ch = _getch();

            switch (ch) {
                
            // Validate
            case ENTER_VALUE:
                if (win(towers))
                    return;
                break;

            // Escape
            case 27:
                exit();
                return;

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


void Game::exit() const {

    CLEAR_SCREEN();
    std::cout << "ESC pressed. Exiting.\n";
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
    do {
        ch = _getch();
    } while (ch != 'h');

    // Clear the help screen and redraw the game state
    CLEAR_SCREEN();
    towers.displayTowers();
}