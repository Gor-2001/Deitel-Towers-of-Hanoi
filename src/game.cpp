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
    } while (ch != 13 && ch != 10);

    CLEAR_SCREEN();


    // Enter game starting mode
    std::cout <<
        "To continue the game, press 'b' for basic start and "
        "'r' for random start."
        << std::endl;

    do {
        ch = _getch();
    } while (ch != 'b' && ch != 'r' && ch != 13 && ch != 10);

    CLEAR_SCREEN();

    if (ch == 'r')
        game_starting_mode = gameStartingModeRandom;


    // Enter Disk Count
    std::cout <<
        "To start the game, enter the number from 1 to 9 to enter the disks count."
        << std::endl;

    do {
        ch = _getch();
    } while ((ch > '9' || ch < '1') && ch != 13 && ch != 10);

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

            // The following conditional block handles
            // the platform-specific behavior of arrow keys.
            // Since we are using WASD, this block is no longer needed
            // unless we want to support both arrow keys and WASD.
            #if defined(_WIN32) || defined(_WIN64)
                if (ch == 0 || ch == 224) { // Windows extended key
                    ch = _getch(); // Get the second part of the key code
                }
            #elif defined(__linux__)
                if (ch == 27) { // Linux escape sequence
                    // Read the next two characters
                    _getch(); // Read '['
                    ch = _getch(); // Read the final key code
                    
                    // Map the Linux key codes ('A', 'B', etc.)
                    // to the Windows codes (72, 80, etc.)
                    switch (ch) {
                        case 'A': ch = 72; break; // Up
                        case 'B': ch = 80; break; // Down
                        case 'C': ch = 77; break; // Right
                        case 'D': ch = 75; break; // Left
                        default: ch = 0; // Set to 0 if an unknown key is pressed
                    }
                }
            #endif

            // Now, the switch statement will handle both
            // platform's key codes correctly.
            switch (ch) {
                // Validate
            case 13:
            case 10: // Also check for Line Feed on Linux
                if (win(towers))
                    return;
                break;

                // Escape
            case 27:
                // Check if the escape key was pressed and not an arrow key
                #if defined(_WIN32) || defined(_WIN64)
                    exit();
                    return;
                #endif
                break;

                // Move Up (W)
            case 'w':
            case 'W':
                towers.diskMoveUp();
                break;

                // Move Left (A)
            case 'a':
            case 'A':
                towers.cursorMoveLeft();
                break;

                // Move Right (D)
            case 'd':
            case 'D':
                towers.cursorMoveRight();
                break;

                // Move Down (S)
            case 's':
            case 'S':
                towers.diskMoveDown();
                break;

                // Open help window (H)
            case 104: // You could also use 'h' and 'H' here
                help(towers);
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