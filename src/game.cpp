#include "game.h"

void Game::start() const {

    unsigned int disk_count;
    gameStartingMode_t game_starting_mode;

    //Starting instructions
    std::cout <<
        "To continue the game, press Enter. "
        "Also during the game, if you need help, press the 'h' key."
        << std::endl;

    char ch;
    do {
        ch = _getch();
    } while (ch != 13);

    system("cls");


    // Enter game starting mode
    std::cout <<
        "To continue the game, press 'b' for basic start and "
        "'r' for random start."
        << std::endl;

    do {
        ch = _getch();
    } while (ch != 'b' && ch != 'r');

    system("cls");

    switch (ch)
    {
    case 'b':
        game_starting_mode = gameStartingModeBasic;
        break;
    case 'r':
        game_starting_mode = gameStartingModeRandom;
        break;
    default:
        assert((true) && "Game starting mode is invalid");
    }

    // Enter Disk Count
    std::cout <<
        "To start the game, enter the number from 1 to 9 to enter the disks count."
        << std::endl;

    do {
        ch = _getch();
    } while (ch > '9' || ch < '1');

    system("cls");
    disk_count = ch - '0';

    // Tower Init and start the game
    Towers towers(disk_count, game_starting_mode);
    process(towers);
}

void Game::process(Towers& towers) const {

    char ch;

    while (true) {
        if (_kbhit()) {
            ch = _getch();

            switch (ch) {

                // Validate
            case 13:
                if (win(towers))
                    return;
                break;

                // Escape
            case 27:
                exit();
                return;

                // Move Up
            case 72:
                towers.diskMoveUp();
                break;

                // Move Left
            case 75:
                towers.cursorMoveLeft();
                break;

                // Move Right
            case 77:
                towers.cursorMoveRight();
                break;

                // Move Down
            case 80:
                towers.diskMoveDown();
                break;

                // Open help window
            case 104:
                help(towers);
                break;

            default:
                break;
            }
        }
        Sleep(10);
    }
}

void Game::exit() const {

    system("cls");
    std::cout << "ESC pressed. Exiting.\n";
}

bool Game::win(const Towers& towers) const {

    if(towers.isWinningPosition()) {
        system("cls");
        std::cout << "You Win.\n";
        return true;
    }

    return false;
}


void Game::help(const Towers& towers) const {
    // Clear the screen and display help
    system("cls");

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
    system("cls");
    towers.displayTowers();
}