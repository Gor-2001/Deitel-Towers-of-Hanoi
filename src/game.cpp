#include "game.h"

void Game::start() const {

    unsigned int disk_count = 3;
    gameStartingMode_t game_starting_mode = gameStartingModeBasic;
    char ch;
    std::string allowedChars;
    std::string message;
    
    
    allowedChars.push_back(ENTER_VALUE);
    message = "To continue the game, press Enter. "
        "Also during the game, if you need help, press the 'h' key.";

    waitForInput(message, allowedChars);


    allowedChars = "rb";
    allowedChars.push_back(ENTER_VALUE);
    message = "To continue the game, press 'b' for basic start and "
        "'r' for random start.";

    ch = waitForInput(message, allowedChars);
    if (ch == 'r')
        game_starting_mode = gameStartingModeRandom;


    allowedChars = "123456789";
    allowedChars.push_back(ENTER_VALUE);
    message = "To start the game, enter the number from 1 to 9 to enter the disks count.";

    ch = waitForInput(message, allowedChars);
    if(ch >= '1' && ch <= '9')
        disk_count = ch - '0';


    // Tower Init and start the game
    Canvas canvas(disk_count, game_starting_mode);
    set_terminal_mode();
    process(canvas);
    restore_terminal_mode();
}

void Game::process(Canvas& canvas) const {
    volatile int ch; // Use volatile to prevent compiler optimizations
    
    while (true) {
        if (_KBHIT()) {
            ch = __GET_CH();

            switch (ch) {

            // Validate
            case ENTER_VALUE:
                if (win(canvas))
                    return;
                break;

            // Escape
            case 27:
                if(exit(canvas))
                    return;
                break;

            // Move Left (a)
            case 'a':
                canvas.cursorMoveLeft();
                break;

            // Move Right (d)
            case 'd':
                canvas.cursorMoveRight();
                break;

            // Open help window (h)
            case 'h':
                help(canvas);
                break;

            // Move Down (s)
            case 's':
                canvas.diskMoveDown();
                break;

            // Move Up (w)
            case 'w':
                canvas.diskMoveUp();
                break;

            default:
                break;
            }
        }
        SLEEP(10);
    }
}


bool Game::exit(const Canvas& canvas) const {

    char ch;
    std::string allowedChars;
    std::string message;

    allowedChars = "ny";
    message = "Do you really want to escape the game ? If yes press y if not press n.";

    ch = waitForInput(message, allowedChars);
    if(ch == 'n') {
        CLEAR_SCREEN();
        canvas.displayCanvas();
        return false;
    }
    else {
        CLEAR_SCREEN();
        std::cout << "ESC pressed. Exiting.\n";
        return true;
    }
}

bool Game::win(const Canvas& canvas) const {

    if(canvas.isWinningPosition()) {
        CLEAR_SCREEN();
        std::cout << "You Win.\n";
        return true;
    }

    return false;
}


void Game::help(const Canvas& canvas) const {

    set_terminal_mode();
    std::string allowedChars;
    std::string message;

    allowedChars = "h";
    message = "NAME\n"
    "\tTowers of Hanoi - a command-line puzzle game\n\n"
    "SYNOPSIS\n"
    "\tMove all disks to the right tower.\n\n"
    "CONTROLS\n"
    "\tTo move the cursor between towers:\n"
    "\t\t'd' Move cursor to the right\n"
    "\t\t'a' Move cursor to the left\n"
    "\t\t'u' Pick up a disk\n"
    "\t\t's' Place a disk\n"
    "\t\t ESC: Quit the game\n"
    "\t\t'h': Show this help menu\n\n"
    "\tTo validate a move:\n"
    "\t\tEnter: Validate your position and win if all disks are in the correct order.\n\n"
    "EXIT\n"
    "\tPress 'h' to return to the game.\n\n";

    waitForInput(message, allowedChars);
    canvas.displayCanvas();
    restore_terminal_mode();
}